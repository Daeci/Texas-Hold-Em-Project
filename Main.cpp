#include <iostream>
#include <vector>    // std::vector
#include <string>
#include <algorithm> // std::random_shuffle
#include <ctime>     // std::time
#include <cstdlib>   // std::rand, std::srand

class Card {
    std::string suit;
    std::string value;
public:
    Card(std::string suit = "", std::string value = "");
    ~Card() { /* nothing */ }
    void setSuit(std::string suit) { this->suit = suit; }
    std::string getSuit() { return suit; }
    void setValue(std::string value) { this->value = value; }
    std::string getValue() { return value; }
};

void fillDeck(std::vector<Card> &deck);

int main()
{
    std::srand(unsigned(std::time(0)));
    std::vector<Card> deck;
    fillDeck(deck);
    std::random_shuffle(deck.begin(), deck.end());


}

Card::Card(std::string suit, std::string value)
{
    this->suit = suit;
    this->value = value;
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
