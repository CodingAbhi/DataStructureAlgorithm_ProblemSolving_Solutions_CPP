#include <bits/stdc++.h>
using namespace std;

struct Order
{
    bool is_buy = false;
    int qty = 0;
    double price = 0.0;
};

ostream& operator <<(ostream& os, const Order& order)
{
    return os << (order.is_buy ? "buy " : "sell ")
        << order.qty << "@$" << setprecision(1)
        << fixed << order.price;
}

bool operator <(const Order& a, const Order& b)
{
     return a.price < b.price;
};

class OrderBook {
public:
    OrderBook() = default;
    
    // formats and prints the orders as the test cases expect.
    ~OrderBook() {
        auto itr = splitIntoBuyAndSellOrders();
        std::sort(begin(orders), itr);
        std::sort(itr, end(orders));
        print();
    }

    // checks the opposing side's available orders.
    // for a buy order, look at existing sell orders, and vice versa.
    // if a trade is possible, update the order book accordingly.
    // otherwise, insert the order into the book.
    void add(Order order);
    
    // print the order book
    // IMPORTANT: the test cases depend on this method.
    // please make sure this is the ONLY ouput that gets printed to stdout.
    void print();

private:
    // returns an iterator to the best "match" for a given order.
    // for buy orders, this would be the lowest sell price.
    // for sell orders, the highest buy price.
    // if no orders meet the criteria, return orders.end()
    vector<Order>::iterator findTrade(const Order& order);
    
    // split orders into buy and sell orders.
    // return an iterator to the first sell order.
    // all orders before the iterator are buy orders.
    // all orders after are sell orders.
    vector<Order>::iterator splitIntoBuyAndSellOrders();
    
    vector<Order> orders;
};

vector<Order>::iterator OrderBook::splitIntoBuyAndSellOrders() {
        return stable_partition(begin(orders),
                                end(orders),
                                [](const Order& order) { return order.is_buy; });
    }

void OrderBook::print() {
    for (const auto& order : orders)
        cout << order << endl;
}


void OrderBook::add(Order order)
{
    auto other = findTrade(order);
    if (other == end(orders)) {
        orders.push_back(order);
    } else {
 int trade_qty = min(order.qty, other->qty);
  order.qty -= trade_qty;
   other->qty -= trade_qty;
   
    if (other->qty == 0) {
         orders.erase(other);
    }
    
     if (order.qty > 0) {
          orders.push_back(order);
     }
     
        }
}

vector<Order>::iterator OrderBook::findTrade(const Order& order)
{
    
     for (auto it = orders.begin(); it != orders.end(); ++it) {
          if (order.is_buy != it->is_buy && ((order.is_buy && order.price >= it->price) || (!order.is_buy && order.price <= it->price))) {
               return it;
          }
     }
      return end(orders);
          
     
}

void parse(OrderBook book) {
    string word;
    while (true) {
        cin >> word;
        if (word == "end")
            break;

        Order* order = new Order;
        order->is_buy = word == "buy";
        cin >> order->qty;
        cin >> order->price;
        book.add(*order);
    }
}
int main() {
    OrderBook book;
    parse(book);
    Order order = {true, 10, 10.0};
    book.add(order);
}