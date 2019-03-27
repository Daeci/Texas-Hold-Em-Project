#include <algorithm> // std::random_shuffle
#include <ctime>     // std::time
#include <cstdlib>   // std::srand
#include "debug.h"

void fillDeck(std::vector<Card> &deck);
void dealCards(std::vector<Card> &deck, Player &p1, Player &p2);

int main()
{
    std::srand(unsigned(std::time(0)));
    std::vector<Card> deck;
    fillDeck(deck);
    std::random_shuffle(deck.begin(), deck.end());

    Player human, computer;
    dealCards(deck, human, computer);
}

void fillDeck(std::vector<Card> &deck)
{
    Card temp;
    for (int i = 1; i <= 4; i++) {
        switch (i) {
        case 1:
            temp.setSuit("Clubs");
            break;
        case 2:
            temp.setSuit("Diamonds");
            break;
        case 3:
            temp.setSuit("Hearts");
            break;
        case 4:
            temp.setSuit("Spades");
            break;
        }
        for (int j = 1; j <= 13; j++) {
            switch (j) {
            case 1:
                temp.setValue("2");
                break;
            case 2:
                temp.setValue("3");
                break;
            case 3:
                temp.setValue("4");
                break;
            case  4:
                temp.setValue("5");
                break;
            case 5:
                temp.setValue("6");
                break;
            case 6:
                temp.setValue("7");
                break;
            case 7:
                temp.setValue("8");
                break;
            case 8:
                temp.setValue("9");
                break;
            case 9:
                temp.setValue("10");
                break;
            case 10:
                temp.setValue("Jack");
                break;
            case 11:
                temp.setValue("Queen");
                break;
            case 12:
                temp.setValue("King");
                break;
            case 13:
                temp.setValue("Ace");
                break;
            }
            deck.push_back(temp);
        }
    }
}

void dealCards(std::vector<Card> &deck, Player &p1, Player &p2)
{
    p1 = Player(deck[0], deck[1]);
    deck.erase(deck.begin(), deck.begin() + 2);
    
    p2 = Player(deck[0], deck[1]);
    deck.erase(deck.begin(), deck.begin() + 2);
}
