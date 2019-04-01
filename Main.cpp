#include <algorithm> // std::random_shuffle
#include <ctime>     // std::time
#include <cstdlib>   // std::srand
#include "debug.h"
//#include "Player.h"

void initGame(std::vector<Card> &deck, std::vector<Player> &players, int playerMoney); // first game initializer
void fillDeck(std::vector<Card> &deck);
void dealCards(std::vector<Card> &deck, std::vector<Player> &playerList, int playerMoney);
void displayPlayerCards(Player p);
void displayCurrentPot(int pot);
int displayOptionMenu(Player p, bool isMaxBet);
void preFlop(std::vector<Player> &playerList, int &pot, const int BIG_BLIND, const int SMALL_BLIND, bool &isGameRunning, int numNeededToFold);
void flop(std::vector<Player> &playerList, int &pot, bool &isGameRunning);
void turn(std::vector<Player> &playerList, int &pot, bool &isGameRunning);
void river(std::vector<Player> &playerList, int &pot, bool &isGameRunning);

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
    initGame(deck, playerList, 100);
    int numNeededToFold = playerList.size() - 1;
    bool isGameRunning = true;
    int gameState = 1;
    int pot = 0;
    const int BIG_BLIND = 2;
    const int SMALL_BLIND = 1;

    while (isGameRunning) {
        switch (gameState) {
        case 1: // preFlop
            preFlop(playerList, pot, BIG_BLIND, SMALL_BLIND, isGameRunning, numNeededToFold);
            gameState = 2;
            break;
        case 2: // flop
            gameState = 3;
            break;
        case 3: // turn
            gameState = 4;
            break;
        case 4: // river
            break;
        }
    }

    return 0;
}

void initGame(std::vector<Card> &deck, std::vector<Player> &playerList, int playerMoney)
{
    playerList[0].setHuman(true);
    for (int i = 1; i < playerList.size(); i++) {
        playerList[i].setHuman(false);
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

    for (int i = 0; i < playerList.size(); i++) {
        playerList[i].setFolded(false);
        playerList[i].initBetAmount();
    }

    dealCards(deck, playerList, playerMoney);
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

void dealCards(std::vector<Card> &deck, std::vector<Player> &playerList, int playerMoney)
{
    for (int i = 0; i < playerList.size(); i++) {
        playerList[i].setCards(deck[0], deck[1]);
        playerList[i].setMoney(playerMoney);
        deck.erase(deck.begin(), deck.begin() + 2);
    }
}

void displayPlayerCards(Player p)
{
    std::cout << "Your cards: \n";
    std::cout << p.getCard1().getValue() << " of " << p.getCard1().getSuit() << std::endl;
    std::cout << p.getCard2().getValue() << " of " << p.getCard2().getSuit() << std::endl;
    std::cout << "\n";
}

void displayCurrentPot(int pot)
{
    std::cout << "Current Pot: " << pot << std::endl;
}

int displayOptionMenu(Player p, bool isMaxBet)
{
    std::cout << "Your cards:\n";
    std::cout << p.getCard1().getValue() << " of " << p.getCard1().getSuit() << std::endl;
    std::cout << p.getCard2().getValue() << " of " << p.getCard2().getSuit() << std::endl;
    std::cout << "\nOptions:\n";
    if (isMaxBet) {
        std::cout << "1. Fold, 2. Call, 3. Raise, 4. Check\n";
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
    else {
        std::cout << "1. Fold, 2. Call, 3. Raise\n";
        std::cout << "Choice: ";
        int option;
        do {
            std::cin >> option;
            if (option < 1 || option > 3) {
                std::cout << "Invalid choice.\n";
            }
            else {
                return option;
            }
        } while (option < 1 || option > 3);
    }
}

void preFlop(std::vector<Player> &playerList, int &pot, const int BIG_BLIND, const int SMALL_BLIND, bool &isGameRunning, int numNeededToFold)
{
    playerList[0].changeMoney(-BIG_BLIND);
    playerList[0].changeBetAmount(BIG_BLIND);
    pot += BIG_BLIND;
    playerList[1].changeMoney(-SMALL_BLIND);
    playerList[1].changeBetAmount(SMALL_BLIND);
    pot += SMALL_BLIND;

    int maxBet = BIG_BLIND;
    int numFolded = 0;

    for (int i = playerList.size() - 1; i >= 0; i--) {
        if (playerList[i].isHuman()) {
            int optionChoice;
            displayCurrentPot(pot);
            if (playerList[i].getBetAmount() < maxBet) {
                optionChoice = displayOptionMenu(playerList[i], true);
            }
            else {
                optionChoice = displayOptionMenu(playerList[i], false);
            }
            switch (optionChoice) {
            case 1: // fold
                playerList[i].fold();
                numFolded++;
                std::cout << "You fold.\n";
                break;
            case 2: // call
                playerList[i].changeMoney(-(maxBet - playerList[i].getBetAmount()));
                playerList[i].changeBetAmount(maxBet - playerList[i].getBetAmount());
                std::cout << "You call.\n";
                break;
            case 3: // raise
                playerList[i].humanRaise(maxBet);
                break;
            case 4: // check
                std::cout << "You check.\n";
                break;
            }
        }
        else {

        }

        if (numFolded == numNeededToFold) {
            isGameRunning = false;
            break;
        }
    }
}
