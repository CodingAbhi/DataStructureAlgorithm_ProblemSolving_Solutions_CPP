import random

def initialize_deck():
    card_categories = ['Hearts', 'Diamonds', 'Clubs', 'Spades']
    cards_list = ['Ace', '2', '3', '4', '5', '6', '7', '8', '9', '10', 'Jack', 'Queen', 'King']
    deck = [(card, category) for category in card_categories for card in cards_list]
    random.shuffle(deck)
    return deck

def card_value(card):
    if card[0] in ['Jack', 'Queen', 'King']:
        return 10
    elif card[0] == 'Ace':
        return 11
    else:
        return int(card[0])

def parse_cards(card_string):
    # Convert string like 'H10;S8;D7;CQ' into list of tuples [('10', 'Hearts'), ('8', 'Spades'), ('7', 'Diamonds'), ('Queen', 'Clubs')]
    card_map = {'H': 'Hearts', 'D': 'Diamonds', 'C': 'Clubs', 'S': 'Spades'}
    cards = []
    for card in card_string.split(';'):
        value, suit = card[1:], card[0]
        cards.append((value, card_map[suit]))
    return cards

def main():
    test_cases = [
        'H10;S8;D7;CQ', 'H10;S7;D8;CQ', 'H10;S7;D7;CQ', 'H10;S7;D7;CQ', 'H8;S7;D7;CQ;DA;S3',
        'H8;S7;D7;C7;DA;S3;CA;HA;H5', 'H8;S7;D7;CQ;D10', 'H10;S7;D7;C7;D10', 'H7;S7;D7;C7;HJ;HQ'
    ]

    for test in test_cases:
        deck = initialize_deck()  # Reset the deck for each test case
        player_card = parse_cards(test)  # Parse the input string into player's cards
        dealer_card = [deck.pop(), deck.pop()]  # Draw two cards for dealer
        player_score = sum(card_value(card) for card in player_card)
        dealer_score = sum(card_value(card) for card in dealer_card)

        print("Test Case:", test)
        print("Cards Player Has:", player_card)
        print("Score Of The Player:", player_score)
        print("Cards Dealer Has:", dealer_card)
        print("Score Of The Dealer:", dealer_score)
        print("\n")

        # Evaluate the outcome based on the scores
        if player_score > 21:
            print("Dealer wins (Player Loss Because Player Score is exceeding 21)")
        elif dealer_score > 21 or player_score > dealer_score:
            print("Player wins")
        elif dealer_score > player_score:
            print("Dealer wins")
        else:
            print("It's a tie.")

if __name__ == "__main__":
    main()
