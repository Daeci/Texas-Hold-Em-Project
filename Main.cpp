#include <algorithm> // std::random_shuffle
#include <ctime>     // std::time
#include <cstdlib>   // std::srand
#include "debug.h"
//#include "Player.h"

void initGame(std::vector<Player> &players); // first game initializer
void fillDeck(std::vector<Card> &deck);
void dealCards(std::vector<Card> &deck, Player &p1, Player &p2);
void displayPlayerCards(Player p);
void dealWholeRiver(std::vector<Card> &deck, std::vector<Card> &riverDeck);
void displayCurrentPot(int pot);
int displayOptionMenu();
void playerBet();
void playerRaise();
void preFlop(std::vector<Player> &playerList, int pot);
void flop();
void turn();
void river();

int main()
{
    std::srand(unsigned(std::time(0)));
    std::vector<Card> deck;
    fillDeck(deck);
    std::random_shuffle(deck.begin(), deck.end());

    Player player1, player2;
    std::vector<Player> playerList;
    playerList.push_back(player1);
    playerList.push_back(player2);
    initGame(playerList);

    return 0;
}

void initGame(std::vector<Player> &playerList) 
{
    playerList[0].setHuman(true);
    playerList[0].setPlayerNumber(1);
    for (int i = 1; i < playerList.size(); i++) {
        playerList[i].setHuman(false);
        playerList[i].setPlayerNumber(i + 1);
    }

    std::random_shuffle(playerList.begin(), playerList.end()); //shuffle player order
    playerList[0].setBigBlind(true);
    playerList[0].setSmallBlind(false);
    playerList[1].setBigBlind(false);
    playerList[1].setSmallBlind(true);
    for (int i = 2; i < playerList.size(); i++) {
        playerList[i].setBigBlind(false);
        playerList[i].setSmallBlind(false);
    }
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
    p1 = Player(deck[0], deck[1], 100);
    deck.erase(deck.begin(), deck.begin() + 2);

    p2 = Player(deck[0], deck[1], 100);
    deck.erase(deck.begin(), deck.begin() + 2);
}

void displayPlayerCards(Player p)
{
    std::cout << "Your cards: \n";
    std::cout << p.getCard1().getValue() << " of " << p.getCard1().getSuit() << std::endl;
    std::cout << p.getCard2().getValue() << " of " << p.getCard2().getSuit() << std::endl;
    std::cout << "\n";
}

void dealWholeRiver(std::vector<Card> &deck, std::vector<Card> &riverDeck)
{
    const int RIVER_SIZE = 5;
    for (int i = 0; i < RIVER_SIZE; i++) {
        riverDeck.push_back(deck[i]);
    }
    deck.erase(deck.begin(), deck.begin() + 5);
}

void displayCurrentPot(int pot)
{
    std::cout << "Current Pot: " << pot << std::endl;
}

int displayOptionMenu()
{
    std::cout << "Options:\n";
    std::cout << "1. Fold, 2. Check, 3. Bet, 4. Raise\n";
    std::cout << "Choice: ";
    int option;
    do {
        std::cin >> option;
        if (option < 1 || option > 4) {
            std::cout << "Invalid choice.\n";
        }
        else {
            return option;
        }
    } while (option < 1 || option > 4);
}

void preFlop(std::vector<Player> playerList, int pot)
{
    
}
