#include "debug.h"

void debugDeckDisplay(std::vector<Card> deck)
{
    std::cout << "Deck:\n";
    int count = 0;
    for (int i = 0; i < deck.size(); i++) {
        std::cout << deck[i].getValue() << " of " << deck[i].getSuit() << std::endl;
        ++count;
    }
    std::cout << "Total cards in deck: " << count << std::endl;
    std::cout << "\n";
}

void debugPlayerCardsDisplay(Player p, std::string name)
{
    std::cout << name << "'s cards:\n";
    std::cout << p.getCard1().getValue() << " of " << p.getCard1().getSuit() << std::endl;
    std::cout << p.getCard2().getValue() << " of " << p.getCard2().getSuit() << std::endl;
    std::cout << "\n";
}

void debugRiverDeckDisplay(std::vector<Card> riverDeck)
{
    std::cout << "River Deck:\n";
    for (int i = 0; i < riverDeck.size(); i++) {
        std::cout << riverDeck[i].getValue() << " of " << riverDeck[i].getSuit() << std::endl;
    }
    std::cout << "\n";
}
