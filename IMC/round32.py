import numpy as np
import json
from datamodel import OrderDepth, TradingState, Order, Trade
from typing import Dict, List, Any









class Trader:
    def __init__(self,
                 fair_value_method: str = "MA",   # Method to estimate fair value: "MA" (Moving Average) or "VWAP" (Volume Weighted Average Price).
                 ma_length: int = 50,             # Window size (number of ticks) for calculating the Moving Average fair value. Longer windows smooth more but react slower.
                 vwap_depth: int = 30,            # Number of price levels on each side (bid/ask) to consider when calculating VWAP fair value.
                 penny_offset: int = 1,           # How many price ticks away from the best bid/ask to place passive limit orders (e.g., 1 means place buy at best_ask - 1). Increased default penny offset.
                 soft_limit_factor: float = 0.8,  # A factor applied to scale down order volume, potentially used as position approaches limit (currently applied multiplicatively with risk scaling).
                 risk_vol_threshold: float = 4.0, # The volatility (standard deviation of recent mid-prices) threshold. If current volatility exceeds this, order volume is scaled down.
                 position_limit: Dict[str, int] = { # Product-specific position limits
                     "AMETHYSTS": 20,
                     "STARFRUIT": 20,
                     "ORCHIDS": 100,
                     "CHOCOLATE": 250,
                     "STRAWBERRIES": 350,
                     "ROSES": 60,
                     "GIFT_BASKET": 60,
                 },
                 max_volume: Dict[str, int] = { # Product-specific max order volumes
                     "AMETHYSTS": 10,
                     "STARFRUIT": 10,
                     "ORCHIDS": 50,
                     "CHOCOLATE": 100,
                     "STRAWBERRIES": 100,
                     "ROSES": 30,
                     "GIFT_BASKET": 30,
                 },
                 arb_margin: float = 150.0,        # Minimum profit threshold for GIFT_BASKET arbitrage. Adjusted based on typical spreads.
                 dead_zone: float = 0.5,           # Default minimum absolute difference required between the current mid-price and the estimated fair value to consider placing a trade. Helps filter out noise.
                 orchid_regression_params: Dict[str, float] = { # Placeholder for regression coefficients for ORCHIDS
                     'intercept': 1000.0, # Example value, needs calibration
                     'sunlight': 0.0,     # Example value, needs calibration
                     'humidity': 0.0,     # Example value, needs calibration
                     'transport': -1.0,   # Example value, needs calibration (expect negative correlation)
                     'import_tariff': -1.0, # Example value, needs calibration (expect negative correlation)
                     'export_tariff': -1.0, # Example value, needs calibration (expect negative correlation)
                 },
                 orchid_std_dev: float = 10.0 # Estimated standard deviation of ORCHIDS price prediction error
                 ):
        self.fair_value_method = fair_value_method
        self.ma_length = ma_length
        self.vwap_depth = vwap_depth
        self.penny_offset = penny_offset
        self.soft_limit_factor = soft_limit_factor
        self.risk_vol_threshold = risk_vol_threshold
        self.position_limit = position_limit
        self.max_volume = max_volume
        self.arb_margin = arb_margin
        self.dead_zone = dead_zone
        self.orchid_regression_params = orchid_regression_params
        self.orchid_std_dev = orchid_std_dev # Store std dev for Orchid pricing

        self.price_history: Dict[str, List[float]] = {}
        self.volatility: Dict[str, float] = {}
        # Cache precomputed best bid/ask to lower latency
        self.quote_cache: Dict[str, Dict[str, float]] = {}  # {product: {'best_bid':..., 'best_ask':...}}
        self.last_mid_price: Dict[str, float] = {} # Cache last mid price for fair value fallback

        # Orchid specific state
        self.orchid_observations: Dict[str, float] = {}

    def _get_mid_price(self, product: str, order_depth: OrderDepth) -> float | None:
        """Safely computes the mid-price, returns None if not possible."""
        if product in self.quote_cache:
            return (self.quote_cache[product]['best_bid'] + self.quote_cache[product]['best_ask']) / 2
        best_bid = max(order_depth.buy_orders.keys()) if order_depth.buy_orders else None
        best_ask = min(order_depth.sell_orders.keys()) if order_depth.sell_orders else None
        if best_bid is not None and best_ask is not None and best_ask > best_bid:
            self.quote_cache[product] = {'best_bid': best_bid, 'best_ask': best_ask}
            return (best_bid + best_ask) / 2
        elif best_bid is not None and best_ask is not None: # Crossed book, use average
             self.quote_cache[product] = {'best_bid': best_bid, 'best_ask': best_ask}
             return (best_bid + best_ask) / 2
        # Fallback to last known mid-price if book is empty or invalid
        return self.last_mid_price.get(product, None)

    def _get_best_bid_ask(self, product: str, order_depth: OrderDepth) -> tuple[float | None, float | None]:
         """Safely gets best bid and ask."""
         best_bid = max(order_depth.buy_orders.keys()) if order_depth.buy_orders else None
         best_ask = min(order_depth.sell_orders.keys()) if order_depth.sell_orders else None
         if product in self.quote_cache:
             return self.quote_cache[product]['best_bid'], self.quote_cache[product]['best_ask']
         if best_bid is not None and best_ask is not None:
             self.quote_cache[product] = {'best_bid': best_bid, 'best_ask': best_ask}
             return best_bid, best_ask
         return None, None


    def estimate_fair_value(self, product: str, order_depth: OrderDepth) -> float | None:
        mid_price = self._get_mid_price(product, order_depth)
        if mid_price is None:
            return self.last_mid_price.get(product, None) # Return last known mid if current is unavailable

        # Update price history
        if product not in self.price_history:
            self.price_history[product] = []
        self.price_history[product].append(mid_price)
        # Keep history length manageable, considering MA length
        max_hist_len = max(self.ma_length, 100) # Keep at least 100 ticks or MA length
        self.price_history[product] = self.price_history[product][-max_hist_len:]
        self.last_mid_price[product] = mid_price # Update cache

        # Calculate fair value based on method
        if self.fair_value_method.upper() == "VWAP":
            bid_prices = sorted(order_depth.buy_orders.keys(), reverse=True)[:self.vwap_depth]
            ask_prices = sorted(order_depth.sell_orders.keys())[:self.vwap_depth]
            if not bid_prices or not ask_prices:
                return mid_price # Fallback to mid-price if one side is empty

            bid_vols = np.array([order_depth.buy_orders[p] for p in bid_prices])
            ask_vols = np.array([-order_depth.sell_orders[p] for p in ask_prices]) # Use negative volume for asks

            total_bid_vol = np.sum(bid_vols)
            total_ask_vol = np.sum(ask_vols)

            if total_bid_vol == 0 and total_ask_vol == 0:
                 return mid_price # Fallback if no volume

            if total_bid_vol == 0:
                 ask_vwap = np.sum(np.array(ask_prices) * ask_vols) / total_ask_vol
                 return ask_vwap # Use only ask VWAP if no bids

            if total_ask_vol == 0:
                 bid_vwap = np.sum(np.array(bid_prices) * bid_vols) / total_bid_vol
                 return bid_vwap # Use only bid VWAP if no asks


            bid_vwap = np.sum(np.array(bid_prices) * bid_vols) / total_bid_vol
            ask_vwap = np.sum(np.array(ask_prices) * ask_vols) / total_ask_vol

            # Weighted average based on volume, or simple average if volumes are zero
            total_vol = total_bid_vol + total_ask_vol
            if total_vol > 0:
                 return (bid_vwap * total_bid_vol + ask_vwap * total_ask_vol) / total_vol
            else:
                 return (bid_vwap + ask_vwap) / 2 # Simple average if total volume is zero (shouldn't happen if checks above pass)


        elif self.fair_value_method.upper() == "MA":
            # Use moving average from price history.
            if product in self.price_history and len(self.price_history[product]) >= self.ma_length:
                return np.mean(self.price_history[product][-self.ma_length:])
            elif product in self.price_history and len(self.price_history[product]) > 0:
                 return np.mean(self.price_history[product]) # Use available history if less than ma_length
            else:
                return mid_price # Fallback to current mid-price if no history
        else:
             # Default/Fallback: Use mid-price if method is unknown or history is insufficient
             return mid_price


    def update_volatility(self, product: str, window: int) -> float:
        if product in self.price_history and len(self.price_history[product]) >= window:
            vol = np.std(self.price_history[product][-window:])
            self.volatility[product] = vol
            return vol
        elif product in self.price_history and len(self.price_history[product]) > 1:
             # Calculate volatility with available data if less than window but more than 1 point
             vol = np.std(self.price_history[product])
             self.volatility[product] = vol
             return vol
        return 0.0 # Return 0 if not enough data

    def compute_order_volume(self, product: str, side: str, current_pos: int, fair_value: float, market_price: float) -> int:
        """Computes order volume considering position limits, max volume, and risk."""
        pos_limit = self.position_limit.get(product, 20) # Default limit if not specified
        max_vol = self.max_volume.get(product, 10) # Default max volume

        if side == "BUY":
            available_limit = pos_limit - current_pos
        elif side == "SELL":
            available_limit = pos_limit + current_pos # Available space for shorting
        else:
            return 0 # Invalid side

        if available_limit <= 0:
            return 0 # Cannot place order if limit is reached or exceeded

        # Basic volume is max_volume
        base_volume = max_vol

        # --- Risk Scaling (Volatility) ---
        current_vol = self.volatility.get(product, 0.0)
        risk_vol = self.risk_vol_threshold # Using the class attribute directly
        vol_scale = 1.0
        if risk_vol > 0 and current_vol > risk_vol:
            # Scale down volume proportionally to how much current vol exceeds threshold
            vol_scale = max(0.1, risk_vol / current_vol) # Ensure scale doesn't go below 0.1

        # --- Position Scaling (Soft Limit) ---
        # Scale down as position approaches limit (using soft_limit_factor)
        pos_scale = 1.0
        if pos_limit > 0:
             # Calculate how close we are to the limit as a fraction
             limit_proximity = abs(current_pos) / pos_limit
             # Apply scaling more aggressively as we get closer to the limit
             # Example: if soft_limit_factor is 0.8, scaling starts reducing volume when position > 0
             # and becomes more aggressive. If position is 80% of limit, scale might be (1 - 0.8) = 0.2
             # We can use a simpler approach: scale linearly based on remaining capacity
             remaining_capacity_ratio = 1.0 - limit_proximity
             # Apply soft_limit_factor influence - e.g., scale down faster
             pos_scale = max(0.1, remaining_capacity_ratio * self.soft_limit_factor + (1-self.soft_limit_factor)) # Blend between full scale and scaled based on proximity


        # Combine scaling factors
        final_scale = vol_scale * pos_scale

        # Calculate final volume
        volume = int(base_volume * final_scale)
        volume = max(1, volume) # Ensure minimum volume of 1 if scaling is very high
        volume = min(volume, available_limit) # Ensure volume doesn't exceed available limit

        return volume


    def _handle_amethysts_starfruit(self, product: str, order_depth: OrderDepth, position: int) -> List[Order]:
        """Market making logic for Amethysts and Starfruit."""
        orders = []
        pos_limit = self.position_limit.get(product, 20)
        max_vol = self.max_volume.get(product, 10)

        best_bid, best_ask = self._get_best_bid_ask(product, order_depth)
        if best_bid is None or best_ask is None or best_ask <= best_bid:
            return orders # Skip if book is invalid or empty

        mid_price = (best_bid + best_ask) / 2
        fair_value = self.estimate_fair_value(product, order_depth)
        if fair_value is None:
            fair_value = mid_price # Fallback if estimation fails

        current_vol = self.update_volatility(product, self.ma_length) # Use MA length for vol window

        # Skip trading if volatility is excessively high (e.g., > 5 * threshold) - safety break
        if self.risk_vol_threshold > 0 and current_vol > self.risk_vol_threshold * 5:
             print(f"Skipping {product} due to extreme volatility: {current_vol:.2f}")
             return orders


        diff = mid_price - fair_value
        current_dead_zone = self.dead_zone # Use default dead zone for these products

        # --- Placing Orders ---
        # Buy Orders
        if diff < -current_dead_zone: # Fair value is significantly above mid-price -> good to buy
            buy_price = best_ask - self.penny_offset # Penny the ask
            buy_volume = self.compute_order_volume(product, "BUY", position, fair_value, buy_price)
            if buy_volume > 0:
                orders.append(Order(product, buy_price, buy_volume))
                # print(f"Placing BUY for {product}: {buy_volume} @ {buy_price}")


        # Sell Orders
        if diff > current_dead_zone: # Fair value is significantly below mid-price -> good to sell
            sell_price = best_bid + self.penny_offset # Penny the bid
            sell_volume = self.compute_order_volume(product, "SELL", position, fair_value, sell_price)
            if sell_volume > 0:
                orders.append(Order(product, sell_price, -sell_volume))
                # print(f"Placing SELL for {product}: {sell_volume} @ {sell_price}")


        # --- Passive Market Making (if not aggressively trading) ---
        # Place passive orders closer to fair value if we didn't place aggressive orders
        # This part can be refined - maybe always place passive orders further out?
        # Or only place passive if position is near zero?

        # Passive Buy Order (if position allows and no aggressive buy placed)
        available_buy_limit = pos_limit - position
        if available_buy_limit > 0 and not any(o.quantity > 0 for o in orders):
             passive_buy_price = min(best_bid + 1, int(fair_value - self.penny_offset)) # Place below fair value or just above best bid
             passive_buy_volume = min(max_vol // 2, available_buy_limit) # Smaller volume for passive
             passive_buy_volume = max(1, passive_buy_volume) # Ensure at least 1
             if passive_buy_volume > 0 and passive_buy_price < best_ask: # Ensure valid price
                 orders.append(Order(product, passive_buy_price, passive_buy_volume))
                 # print(f"Placing Passive BUY for {product}: {passive_buy_volume} @ {passive_buy_price}")


        # Passive Sell Order (if position allows and no aggressive sell placed)
        available_sell_limit = pos_limit + position
        if available_sell_limit > 0 and not any(o.quantity < 0 for o in orders):
             passive_sell_price = max(best_ask - 1, int(fair_value + self.penny_offset)) # Place above fair value or just below best ask
             passive_sell_volume = min(max_vol // 2, available_sell_limit) # Smaller volume
             passive_sell_volume = max(1, passive_sell_volume)
             if passive_sell_volume > 0 and passive_sell_price > best_bid: # Ensure valid price
                 orders.append(Order(product, passive_sell_price, -passive_sell_volume))
                 # print(f"Placing Passive SELL for {product}: {passive_sell_volume} @ {passive_sell_price}")


        return orders


    def _handle_gift_basket(self, state: TradingState) -> List[Order]:
        """Arbitrage logic for GIFT_BASKET and its components."""
        orders = []
        basket = "GIFT_BASKET"
        strawberries = "STRAWBERRIES"
        chocolate = "CHOCOLATE"
        roses = "ROSES"
        components = [strawberries, chocolate, roses]
        required_qty = {strawberries: 4, chocolate: 6, roses: 1}

        # Ensure all necessary order depths are present
        if not all(p in state.order_depths for p in [basket] + components):
            return orders

        # Get best bid/ask for all components and the basket
        basket_bb, basket_ba = self._get_best_bid_ask(basket, state.order_depths[basket])
        straw_bb, straw_ba = self._get_best_bid_ask(strawberries, state.order_depths[strawberries])
        choc_bb, choc_ba = self._get_best_bid_ask(chocolate, state.order_depths[chocolate])
        rose_bb, rose_ba = self._get_best_bid_ask(roses, state.order_depths[roses])

        # Check if all prices are available
        if None in [basket_bb, basket_ba, straw_bb, straw_ba, choc_bb, choc_ba, rose_bb, rose_ba]:
            return orders

        # Calculate cost to buy components (using best asks)
        cost_to_buy_components = (required_qty[strawberries] * straw_ba +
                                  required_qty[chocolate] * choc_ba +
                                  required_qty[roses] * rose_ba)

        # Calculate revenue from selling components (using best bids)
        revenue_from_selling_components = (required_qty[strawberries] * straw_bb +
                                           required_qty[chocolate] * choc_bb +
                                           required_qty[roses] * rose_bb)

        # --- Arbitrage Opportunity 1: Buy components, Sell basket ---
        # If we can sell the basket for more than it costs to buy the components + margin
        profit_buy_comps_sell_basket = basket_bb - cost_to_buy_components
        if profit_buy_comps_sell_basket > self.arb_margin:
            # Determine max volume based on position limits and available liquidity
            pos_basket = state.position.get(basket, 0)
            pos_straw = state.position.get(strawberries, 0)
            pos_choc = state.position.get(chocolate, 0)
            pos_rose = state.position.get(roses, 0)

            limit_basket = self.position_limit.get(basket, 60)
            limit_straw = self.position_limit.get(strawberries, 350)
            limit_choc = self.position_limit.get(chocolate, 250)
            limit_rose = self.position_limit.get(roses, 60)

            # Max volume we can sell basket / buy components based on limits
            vol_limit_basket = limit_basket + pos_basket # Space to short basket
            vol_limit_straw = limit_straw - pos_straw # Space to long strawberries
            vol_limit_choc = limit_choc - pos_choc   # Space to long chocolate
            vol_limit_rose = limit_rose - pos_rose     # Space to long roses

            # Convert component limits to equivalent basket units
            vol_limit_comp_equiv = min(vol_limit_straw // required_qty[strawberries],
                                       vol_limit_choc // required_qty[chocolate],
                                       vol_limit_rose // required_qty[roses])

            # Max volume based on available liquidity at best prices
            liq_basket_sell = state.order_depths[basket].buy_orders.get(basket_bb, 0)
            liq_straw_buy = -state.order_depths[strawberries].sell_orders.get(straw_ba, 0) # Sell orders have negative volume
            liq_choc_buy = -state.order_depths[chocolate].sell_orders.get(choc_ba, 0)
            liq_rose_buy = -state.order_depths[roses].sell_orders.get(rose_ba, 0)

             # Convert component liquidity to equivalent basket units
            liq_comp_equiv = min(liq_straw_buy // required_qty[strawberries],
                                 liq_choc_buy // required_qty[chocolate],
                                 liq_rose_buy // required_qty[roses])


            # Determine final trade volume
            max_trade_volume = min(vol_limit_basket, vol_limit_comp_equiv, liq_basket_sell, liq_comp_equiv, self.max_volume[basket])
            max_trade_volume = max(0, int(max_trade_volume)) # Ensure non-negative integer

            if max_trade_volume > 0:
                print(f"Arbitrage: Buy Comps, Sell Basket. Profit: {profit_buy_comps_sell_basket:.2f}, Vol: {max_trade_volume}")
                orders.append(Order(basket, basket_bb, -max_trade_volume))
                orders.append(Order(strawberries, straw_ba, max_trade_volume * required_qty[strawberries]))
                orders.append(Order(chocolate, choc_ba, max_trade_volume * required_qty[chocolate]))
                orders.append(Order(roses, rose_ba, max_trade_volume * required_qty[roses]))
                # Immediately update quote cache to reflect our potential fills
                self.quote_cache.pop(basket, None)
                self.quote_cache.pop(strawberries, None)
                self.quote_cache.pop(chocolate, None)
                self.quote_cache.pop(roses, None)


        # --- Arbitrage Opportunity 2: Buy basket, Sell components ---
        # If we can buy the basket for less than we get from selling components - margin
        profit_buy_basket_sell_comps = revenue_from_selling_components - basket_ba
        if profit_buy_basket_sell_comps > self.arb_margin:
            pos_basket = state.position.get(basket, 0)
            pos_straw = state.position.get(strawberries, 0)
            pos_choc = state.position.get(chocolate, 0)
            pos_rose = state.position.get(roses, 0)

            limit_basket = self.position_limit.get(basket, 60)
            limit_straw = self.position_limit.get(strawberries, 350)
            limit_choc = self.position_limit.get(chocolate, 250)
            limit_rose = self.position_limit.get(roses, 60)

            # Max volume we can buy basket / sell components based on limits
            vol_limit_basket = limit_basket - pos_basket # Space to long basket
            vol_limit_straw = limit_straw + pos_straw # Space to short strawberries
            vol_limit_choc = limit_choc + pos_choc   # Space to short chocolate
            vol_limit_rose = limit_rose + pos_rose     # Space to short roses

            # Convert component limits to equivalent basket units
            vol_limit_comp_equiv = min(vol_limit_straw // required_qty[strawberries],
                                       vol_limit_choc // required_qty[chocolate],
                                       vol_limit_rose // required_qty[roses])

            # Max volume based on available liquidity at best prices
            liq_basket_buy = -state.order_depths[basket].sell_orders.get(basket_ba, 0) # Sell orders have negative volume
            liq_straw_sell = state.order_depths[strawberries].buy_orders.get(straw_bb, 0)
            liq_choc_sell = state.order_depths[chocolate].buy_orders.get(choc_bb, 0)
            liq_rose_sell = state.order_depths[roses].buy_orders.get(rose_bb, 0)

             # Convert component liquidity to equivalent basket units
            liq_comp_equiv = min(liq_straw_sell // required_qty[strawberries],
                                 liq_choc_sell // required_qty[chocolate],
                                 liq_rose_sell // required_qty[roses])

            # Determine final trade volume
            max_trade_volume = min(vol_limit_basket, vol_limit_comp_equiv, liq_basket_buy, liq_comp_equiv, self.max_volume[basket])
            max_trade_volume = max(0, int(max_trade_volume)) # Ensure non-negative integer

            if max_trade_volume > 0:
                print(f"Arbitrage: Buy Basket, Sell Comps. Profit: {profit_buy_basket_sell_comps:.2f}, Vol: {max_trade_volume}")
                orders.append(Order(basket, basket_ba, max_trade_volume))
                orders.append(Order(strawberries, straw_bb, -max_trade_volume * required_qty[strawberries]))
                orders.append(Order(chocolate, choc_bb, -max_trade_volume * required_qty[chocolate]))
                orders.append(Order(roses, rose_bb, -max_trade_volume * required_qty[roses]))
                 # Immediately update quote cache to reflect our potential fills
                self.quote_cache.pop(basket, None)
                self.quote_cache.pop(strawberries, None)
                self.quote_cache.pop(chocolate, None)
                self.quote_cache.pop(roses, None)

        # Also add market making orders for individual components if no arb trade happened for them
        component_orders = {}
        arb_products = {o.symbol for o in orders} # Products involved in arb trades

        for comp in components:
             if comp not in arb_products:
                 comp_pos = state.position.get(comp, 0)
                 comp_orders = self._handle_amethysts_starfruit(comp, state.order_depths[comp], comp_pos) # Reuse basic MM logic
                 orders.extend(comp_orders)

        # Add basic MM for basket if no arb trade happened for it
        if basket not in arb_products:
             basket_pos = state.position.get(basket, 0)
             basket_mm_orders = self._handle_amethysts_starfruit(basket, state.order_depths[basket], basket_pos)
             orders.extend(basket_mm_orders)


        return orders


    def _handle_orchids(self, state: TradingState) -> List[Order]:
        """Handles trading ORCHIDS based on observations and order book."""
        orders = []
        product = "ORCHIDS"
        order_depth = state.order_depths[product]
        position = state.position.get(product, 0)
        pos_limit = self.position_limit.get(product, 100)
        max_vol = self.max_volume.get(product, 50)

        # --- 1. Estimate Fair Value using Observations ---
        obs = state.observations.conversionObservations.get(product)
        if obs is None:
             print("Warning: No observations found for ORCHIDS.")
             # Fallback to standard market making if no observations
             return self._handle_amethysts_starfruit(product, order_depth, position)


        # Update cached observations
        self.orchid_observations['transport'] = obs.transportFees
        self.orchid_observations['export'] = obs.exportTariff
        self.orchid_observations['import'] = obs.importTariff
        self.orchid_observations['sunlight'] = obs.sunlight
        self.orchid_observations['humidity'] = obs.humidity

        # Predict fair value using a simple linear model (coefficients need calibration)
        # This model is a placeholder and likely needs significant improvement/calibration
        params = self.orchid_regression_params
        predicted_value = (params['intercept'] +
                           params['sunlight'] * obs.sunlight +
                           params['humidity'] * obs.humidity +
                           params['transport'] * obs.transportFees +
                           params['import_tariff'] * obs.importTariff +
                           params['export_tariff'] * obs.exportTariff)

        # --- 2. Get Market Prices ---
        best_bid, best_ask = self._get_best_bid_ask(product, order_depth)
        if best_bid is None or best_ask is None:
            return orders # Cannot trade without market prices

        mid_price = (best_bid + best_ask) / 2
        # Update price history for volatility calculation (optional, could use prediction error)
        self.last_mid_price[product] = mid_price
        if product not in self.price_history: self.price_history[product] = []
        self.price_history[product].append(mid_price)
        self.price_history[product] = self.price_history[product][-100:] # Keep limited history


        # --- 3. Determine Trading Signal ---
        # Compare predicted value to market prices
        # Use a confidence interval around the prediction (e.g., +/- 1 standard deviation)
        buy_threshold = predicted_value - self.orchid_std_dev
        sell_threshold = predicted_value + self.orchid_std_dev

        # --- 4. Place Orders ---
        # Buy if best ask is below our buy threshold (market price is cheap)
        if best_ask < buy_threshold:
            buy_volume = self.compute_order_volume(product, "BUY", position, predicted_value, best_ask)
            # Make volume potentially dependent on the difference (stronger signal = more volume?)
            signal_strength = (buy_threshold - best_ask) / self.orchid_std_dev # How many std devs away
            scaled_volume = int(buy_volume * min(1.5, max(0.5, signal_strength))) # Scale volume by signal strength (capped)
            final_volume = min(buy_volume, scaled_volume, -order_depth.sell_orders.get(best_ask, 0)) # Consider liquidity
            final_volume = max(1, final_volume) # Ensure min 1

            if final_volume > 0 and position + final_volume <= pos_limit :
                print(f"Placing BUY for {product}: {final_volume} @ {best_ask} (Pred: {predicted_value:.1f}, Thresh: {buy_threshold:.1f})")
                orders.append(Order(product, best_ask, final_volume))
                self.quote_cache.pop(product, None) # Invalidate cache after aggressive order


        # Sell if best bid is above our sell threshold (market price is expensive)
        elif best_bid > sell_threshold:
            sell_volume = self.compute_order_volume(product, "SELL", position, predicted_value, best_bid)
            signal_strength = (best_bid - sell_threshold) / self.orchid_std_dev
            scaled_volume = int(sell_volume * min(1.5, max(0.5, signal_strength)))
            final_volume = min(sell_volume, scaled_volume, order_depth.buy_orders.get(best_bid, 0)) # Consider liquidity
            final_volume = max(1, final_volume)

            if final_volume > 0 and position - final_volume >= -pos_limit:
                print(f"Placing SELL for {product}: {final_volume} @ {best_bid} (Pred: {predicted_value:.1f}, Thresh: {sell_threshold:.1f})")
                orders.append(Order(product, best_bid, -final_volume))
                self.quote_cache.pop(product, None) # Invalidate cache

        # Optional: Add passive market making orders around the predicted value if no aggressive trade
        # Example: Place buy order at predicted_value - offset, sell at predicted_value + offset
        # This requires careful consideration of spreads and prediction accuracy.
        # For now, focus on directional trades based on prediction vs market.

        return orders


    def run(self, state: TradingState) -> tuple[dict[str, list[Order]], int, str]:
        """Main trading logic loop."""
        result: Dict[str, List[Order]] = {}
        self.quote_cache = {} # Clear cache at the start of the tick

        trader_data = "" # Optional data to persist state

        # --- Pre-process Observations (for Orchids) ---
        # Store latest observations if available
        # Check if observations and conversionObservations exist before accessing
        if state.observations and hasattr(state.observations, 'conversionObservations'):
             product = "ORCHIDS" # Define product here or pass it if needed elsewhere
             if product in state.observations.conversionObservations:
                 obs = state.observations.conversionObservations[product]
                 self.orchid_observations['transport'] = obs.transportFees
                 self.orchid_observations['export'] = obs.exportTariff
                 self.orchid_observations['import'] = obs.importTariff
                 self.orchid_observations['sunlight'] = obs.sunlight
                 self.orchid_observations['humidity'] = obs.humidity


        # --- Handle Gift Basket Arbitrage ---
        gift_basket_orders = self._handle_gift_basket(state)
        for order in gift_basket_orders:
            if order.symbol not in result:
                result[order.symbol] = []
            result[order.symbol].append(order)

        # --- Handle Other Products ---
        products_in_arb = {"GIFT_BASKET", "STRAWBERRIES", "CHOCOLATE", "ROSES"}
        for product, order_depth in state.order_depths.items():
            # Skip products already handled by arbitrage logic
            if product in products_in_arb:
                # Ensure the product key exists in the result even if no new orders were added
                if product not in result:
                    result[product] = []
                continue

            position = state.position.get(product, 0)

            if product == "ORCHIDS":
                # Use dedicated Orchid handler which uses observations
                orchid_orders = self._handle_orchids(state)
                result[product] = orchid_orders
            elif product in ["AMETHYSTS", "STARFRUIT"]:
                # Use standard market making logic
                mm_orders = self._handle_amethysts_starfruit(product, order_depth, position)
                result[product] = mm_orders
            else:
                 # Default fallback or handler for unexpected products
                 # Maybe use the basic MM logic as a default
                 print(f"Warning: No specific handler for product {product}. Using default MM.")
                 default_orders = self._handle_amethysts_starfruit(product, order_depth, position)
                 result[product] = default_orders


        # --- Post-processing / Trader Data ---
        # Example: Persist orchid model parameters or state if needed
        # trader_data = json.dumps({"orchid_params": self.orchid_regression_params})


        conversions = 0 # Set conversions request (e.g., for Orchids if needed)
        return result, conversions, trader_data