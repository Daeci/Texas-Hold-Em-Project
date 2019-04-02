#include <algorithm> // std::random_shuffle
#include <ctime>     // std::time
#include <cstdlib>   // std::srand
#include <random>    // std::random_device, std::mt19937, std::uniform_int_distribution
#include <vector>    // std::vector
#include "Player.h"

void initGame(std::vector<Card> &deck, std::vector<Player> &players, int playerMoney); // first game initializer
void fillDeck(std::vector<Card> &deck);
void dealCards(std::vector<Card> &deck, std::vector<Player> &playerList, int playerMoney);
void displayPlayerCards(Player p);
void displayCurrentPot(int pot);
void displayCurrentRiver(std::vector<Card> riverDeck);
int displayOptionMenu(Player p, int maxBet, std::vector<Card> riverDeck);

void preFlop(std::vector<Player> &playerList, int &maxBet, int &pot, const int BIG_BLIND, const int SMALL_BLIND, bool &isGameRunning, std::vector<Card> riverDeck);
void flop(std::vector<Player> &playerList, int &maxBet, int &pot, bool &isGameRunning, std::vector<Card> riverDeck);
void turn(std::vector<Player> &playerList, int &maxBet, int &pot, bool &isGameRunning, std::vector<Card> riverDeck);
void river(std::vector<Player> &playerList, int &maxBet, int &pot, bool &isGameRunning, std::vector<Card> riverDeck);

void flopDraw(std::vector<Card> &deck, std::vector<Card> &riverDeck, int pot);
void turnDraw(std::vector<Card> &deck, std::vector<Card> &riverDeck, int pot);
void riverDraw(std::vector<Card> &deck, std::vector<Card> &riverDeck, int pot);

void resetChecked(std::vector<Player> &playerList);
void resetCheckedAfterMaxBetChangeAfterFlop(std::vector<Player> &playerList, int playerIndex);
bool areEnoughFolded(std::vector<Player> playerList, int numNeededToFold);
bool areEnoughAllin(std::vector<Player> playerList, int enoughAllin);
bool areAllChecked(std::vector<Player> playerList);

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
    std::vector<Card> riverDeck;
    bool isGameRunning = true;
    int gameState = 1; // start with preFlop
    int pot = 0;
    int maxBet = 0;
    const int BIG_BLIND = 2;
    const int SMALL_BLIND = 1;

    do {
        switch (gameState) {
        case 1: // preFlop
            preFlop(playerList, maxBet, pot, BIG_BLIND, SMALL_BLIND, isGameRunning, riverDeck);
            gameState = 2;
            break;
        case 2: // flop
            flopDraw(deck, riverDeck, pot);
            resetChecked(playerList);
            flop(playerList, maxBet, pot, isGameRunning, riverDeck);
            gameState = 3;
            break;
        case 3: // turn
            turnDraw(deck, riverDeck, pot);
            resetChecked(playerList);
            turn(playerList, maxBet, pot, isGameRunning, riverDeck);
            gameState = 4;
            break;
        case 4: // river
            riverDraw(deck, riverDeck, pot);
            resetChecked(playerList);
            river(playerList, maxBet, pot, isGameRunning, riverDeck);
            isGameRunning = false;
            break;
        }
    } while (isGameRunning);

    /* Scoring thingy goes here */

    return 0;
}

void initGame(std::vector<Card> &deck, std::vector<Player> &playerList, int playerMoney)
{
    playerList[0].setHuman(true);
    playerList[0].setPlayerNumber(1);
    for (int i = 1; i < playerList.size(); i++) {
        playerList[i].setHuman(false);
        playerList[i].setPlayerNumber(i+1);
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
        playerList[i].initAllin();
        playerList[i].initFolded();
        playerList[i].initChecked();
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

void displayCurrentRiver(std::vector<Card> riverDeck)
{
    if (!riverDeck.size() == 0) {
        std::cout << "\n";
        std::cout << "Current river:\n";
        for (int i = 0; i < riverDeck.size(); i++) {
            std::cout << riverDeck[i].getValue() << " of " << riverDeck[i].getSuit() << std::endl;
        }
    }
}

int displayOptionMenu(Player p, int maxBet, std::vector<Card> riverDeck)
{
    std::cout << "\n------------------------";
    displayCurrentRiver(riverDeck);
    std::cout << "\nCurrent max bid: $" << maxBet << std::endl;
    std::cout << "Your current bid: $" << p.getBetAmount() << std::endl << std::endl;
    displayPlayerCards(p);
    std::cout << "Options:\n";
    std::cout << "1. Fold, 2. Call/Check, 3. Raise\n";
    std::cout << "------------------------\n";
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

void resetChecked(std::vector<Player> &playerList)
{
    for (int i = 0; i < playerList.size(); i++) {
        playerList[i].setChecked(false);
    }
}

void resetCheckedAfterMaxBetChangeAfterFlop(std::vector<Player> &playerList, int playerIndex)
{
    for (int i = 0; i < playerList.size(); i++) {
        if (i != playerIndex) {
            playerList[i].setChecked(false);
        }
    }
}

bool areEnoughFolded(std::vector<Player> playerList, int numNeededToFold)
{
    int numFolded = 0;
    for (int i = 0; i < playerList.size(); i++) {
        if (playerList[i].isFolded()) {
            numFolded++;
        }
    }

    if (numFolded == numNeededToFold) {
        return true;
    }
    else {
        return false;
    }
}

bool areEnoughAllin(std::vector<Player> playerList, int enoughAllin)
{
    int count = 0;
    for (int i = 0; i < playerList.size(); i++) {
        if (playerList[i].isAllin()) {
            count++;
        }
    }

    if (count == enoughAllin) {
        return true;
    }
    else {
        return false;
    }
}

bool areAllChecked(std::vector<Player> playerList)
{
    int count = 0;
    for (int i = 0; i < playerList.size(); i++) {
        if (playerList[i].isChecked()) {
            count++;
        }            
    }
    
    if (count == playerList.size()) {
        return true;
    }
    else {
        return false;
    }
}

void preFlop(std::vector<Player> &playerList, int &maxBet, int &pot, const int BIG_BLIND, const int SMALL_BLIND, bool &isGameRunning, std::vector<Card> riverDeck)
{
    playerList[0].changeMoney(-BIG_BLIND);
    playerList[0].changeBetAmount(BIG_BLIND);
    pot += BIG_BLIND;
    playerList[1].changeMoney(-SMALL_BLIND);
    playerList[1].changeBetAmount(SMALL_BLIND);
    pot += SMALL_BLIND;

    maxBet = BIG_BLIND;
    bool allChecked = false;
    bool enoughAllin = false;

    do {
        for (int i = playerList.size() - 1; i >= 0; i--) {
            if (!playerList[i].isFolded() && !playerList[i].isAllin()) {
                if (playerList[i].isHuman()) {
                    int optionChoice;
                    optionChoice = displayOptionMenu(playerList[i], maxBet, riverDeck);
                    switch (optionChoice) {
                    case 1: // fold
                        playerList[i].fold();
                        std::cout << "\n * You fold\n";
                        break;
                    case 2: // call/check
                        if (playerList[i].getBetAmount() == maxBet) {
                            std::cout << "\n * You check\n";
                        }
                        else {
                            int callMoney = (maxBet - playerList[i].getBetAmount());
                            if (playerList[i].getMoney() - callMoney <= 0) {
                                callMoney = playerList[i].getMoney();
                                playerList[i].setAllin(true);
                                std::cout << "\n * You call and are all in\n";
                            }
                            else {
                                std::cout << "\n * You call\n";
                            }
                            playerList[i].changeMoney(-callMoney);
                            playerList[i].changeBetAmount(callMoney);
                            pot += callMoney;
                        }
                        playerList[i].check();
                        break;
                    case 3: // raise
                        int raise = playerList[i].humanRaise(maxBet);
                        playerList[i].changeMoney(-raise);
                        playerList[i].changeBetAmount(raise);
                        pot += raise;
                        maxBet = playerList[i].getBetAmount();
                        if (playerList[i].getMoney() == 0) {
                            std::cout << "\n * You raise $" << raise << " and are all in\n";
                            playerList[i].setAllin(true);
                        }
                        else {
                            std::cout << "\n * You raise $" << raise << std::endl;
                        }
                        playerList[i].check();
                        resetChecked(playerList);
                        break;
                    }
                }
                else {
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_int_distribution<> dis(1, 100);
                    int random = dis(gen);
                    int optionChoice;
                    if (random >= 15) {
                        optionChoice = 2; //85% chance to call/check
                    }
                    else {
                        optionChoice = 3; //15% chance to raise
                    }

                    switch (optionChoice) {
                    case 1: // fold
                        playerList[i].fold();
                        std::cout << " * " << playerList[i] << " folds\n";
                        break;
                    case 2: // call/check
                        if (playerList[i].getBetAmount() == maxBet) {
                            std::cout << " * " << playerList[i] << " checks\n";
                        }
                        else {
                            int callMoney = (maxBet - playerList[i].getBetAmount());
                            if (playerList[i].getMoney() - callMoney <= 0) {
                                callMoney = playerList[i].getMoney();
                                playerList[i].setAllin(true);
                                std::cout << " * " << playerList[i] << " calls and is all in\n";
                            }
                            else {
                                std::cout << " * " << playerList[i] << " calls\n";
                            }
                            playerList[i].changeMoney(-callMoney);
                            playerList[i].changeBetAmount(callMoney);
                            pot += callMoney;
                        }
                        playerList[i].check();
                        break;
                    case 3: // raise
                        int raise = playerList[i].computerRaise(maxBet);
                        playerList[i].changeMoney(-raise);
                        playerList[i].changeBetAmount(raise);
                        pot += raise;
                        maxBet = playerList[i].getBetAmount();
                        if (playerList[i].getMoney() == 0) {
                            std::cout << " * " << playerList[i] << " raises $" << raise << " and is all in\n";
                            playerList[i].setAllin(true);
                        }
                        else {
                            std::cout << " * " << playerList[i] << " raises $" << raise << std::endl;
                        }                        
                        playerList[i].check();
                        resetChecked(playerList);
                        break;
                    }
                }
            }

            if (areEnoughFolded(playerList, playerList.size() - 1)) {
                isGameRunning = false;
                break;
            }
            if (areEnoughAllin(playerList, playerList.size() - 1)) {
                enoughAllin = true;
                break;
            }
            if (areAllChecked(playerList)) {
                allChecked = true;
                break;
            }
        }
    } while (!allChecked && isGameRunning && !enoughAllin);
}

void flop(std::vector<Player> &playerList, int &maxBet, int &pot, bool &isGameRunning, std::vector<Card> riverDeck)
{
    bool allChecked = false;
    bool enoughAllin = false;

    do {
        for (int i = playerList.size() - 1; i >= 0; i--) {
            if (!playerList[i].isFolded() && !playerList[i].isAllin()) {
                if (playerList[i].isHuman()) {
                    int optionChoice;
                    optionChoice = displayOptionMenu(playerList[i], maxBet, riverDeck);
                    switch (optionChoice) {
                    case 1: // fold
                        playerList[i].fold();
                        std::cout << "\n * You fold\n";
                        break;
                    case 2: // call/check
                        if (playerList[i].getBetAmount() == maxBet) {
                            std::cout << "\n * You check\n";
                        }
                        else {
                            int callMoney = (maxBet - playerList[i].getBetAmount());
                            if (playerList[i].getMoney() - callMoney <= 0) {
                                callMoney = playerList[i].getMoney();
                                playerList[i].setAllin(true);
                                std::cout << "\n * You call and are all in\n";
                            }
                            else {
                                std::cout << "\n * You call\n";
                            }
                            playerList[i].changeMoney(-callMoney);
                            playerList[i].changeBetAmount(callMoney);
                            pot += callMoney;
                        }
                        playerList[i].check();
                        break;
                    case 3: // raise
                        int raise = playerList[i].humanRaise(maxBet);
                        playerList[i].changeMoney(-raise);
                        playerList[i].changeBetAmount(raise);
                        pot += raise;
                        maxBet = playerList[i].getBetAmount();
                        if (playerList[i].getMoney() == 0) {
                            std::cout << "\n * You raise $" << raise << " and are all in\n";
                            playerList[i].setAllin(true);
                        }
                        else {
                            std::cout << "\n * You raise $" << raise << std::endl;
                        }
                        playerList[i].check();
                        resetCheckedAfterMaxBetChangeAfterFlop(playerList, i);
                        break;
                    }
                }
                else {
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_int_distribution<> dis(1, 100);
                    int random = dis(gen);
                    int optionChoice;
                    if (random >= 15) {
                        optionChoice = 2; //85% chance to call/check
                    }
                    else {
                        optionChoice = 3; //15% chance to raise
                    }

                    switch (optionChoice) {
                    case 1: // fold
                        playerList[i].fold();
                        std::cout << " * " << playerList[i] << " folds\n";
                        break;
                    case 2: // call/check
                        if (playerList[i].getBetAmount() == maxBet) {
                            std::cout << " * " << playerList[i] << " checks\n";
                        }
                        else {
                            int callMoney = (maxBet - playerList[i].getBetAmount());
                            if (playerList[i].getMoney() - callMoney <= 0) {
                                callMoney = playerList[i].getMoney();
                                playerList[i].setAllin(true);
                                std::cout << " * " << playerList[i] << " calls and is all in\n";
                            }
                            else {
                                std::cout << " * " << playerList[i] << " calls\n";
                            }
                            playerList[i].changeMoney(-callMoney);
                            playerList[i].changeBetAmount(callMoney);
                            pot += callMoney;
                        }   
                        playerList[i].check();
                        break;
                    case 3: // raise
                        int raise = playerList[i].computerRaise(maxBet);
                        playerList[i].changeMoney(-raise);
                        playerList[i].changeBetAmount(raise);
                        pot += raise;
                        maxBet = playerList[i].getBetAmount();
                        if (playerList[i].getMoney() == 0) {
                            std::cout << " * " << playerList[i] << " raises $" << raise << " and is all in\n";
                            playerList[i].setAllin(true);
                        }
                        else {
                            std::cout << " * " << playerList[i] << " raises $" << raise << std::endl;
                        }
                        playerList[i].check();
                        resetCheckedAfterMaxBetChangeAfterFlop(playerList, i);
                        break;
                    }
                }
            }
            if (areEnoughFolded(playerList, playerList.size() - 1)) {
                isGameRunning = false;
                break;
            }
            if (areEnoughAllin(playerList, playerList.size() - 1)) {
                enoughAllin = true;
                break;
            }
            if (areAllChecked(playerList)) {
                allChecked = true;
                break;
            }
        }
    } while (!allChecked && isGameRunning && !enoughAllin);
}

void turn(std::vector<Player> &playerList, int &maxBet, int &pot, bool &isGameRunning, std::vector<Card> riverDeck)
{
    bool allChecked = false;
    bool enoughAllin = false;

    do {
        for (int i = playerList.size() - 1; i >= 0; i--) {
            if (!playerList[i].isFolded() && !playerList[i].isAllin()) {
                if (playerList[i].isHuman()) {
                    int optionChoice;
                    optionChoice = displayOptionMenu(playerList[i], maxBet, riverDeck);
                    switch (optionChoice) {
                    case 1: // fold
                        playerList[i].fold();
                        std::cout << "\n * You fold\n";
                        break;
                    case 2: // call/check
                        if (playerList[i].getBetAmount() == maxBet) {
                            std::cout << "\n * You check\n";
                        }
                        else {
                            int callMoney = (maxBet - playerList[i].getBetAmount());
                            if (playerList[i].getMoney() - callMoney <= 0) {
                                callMoney = playerList[i].getMoney();
                                playerList[i].setAllin(true);
                                std::cout << "\n * You call and are all in\n";
                            }
                            else {
                                std::cout << "\n * You call\n";
                            }
                            playerList[i].changeMoney(-callMoney);
                            playerList[i].changeBetAmount(callMoney);
                            pot += callMoney;
                        }
                        playerList[i].check();
                        break;
                    case 3: // raise
                        int raise = playerList[i].humanRaise(maxBet);
                        playerList[i].changeMoney(-raise);
                        playerList[i].changeBetAmount(raise);
                        pot += raise;
                        maxBet = playerList[i].getBetAmount();
                        if (playerList[i].getMoney() == 0) {
                            std::cout << "\n * You raise $" << raise << " and are all in\n";
                            playerList[i].setAllin(true);
                        }
                        else {
                            std::cout << "\n * You raise $" << raise << std::endl;
                        }
                        playerList[i].check();
                        resetCheckedAfterMaxBetChangeAfterFlop(playerList, i);
                        break;
                    }
                }
                else {
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_int_distribution<> dis(1, 100);
                    int random = dis(gen);
                    int optionChoice;
                    if (random >= 15) {
                        optionChoice = 2; //85% chance to call/check
                    }
                    else {
                        optionChoice = 3; //15% chance to raise
                    }

                    switch (optionChoice) {
                    case 1: // fold
                        playerList[i].fold();
                        std::cout << " * " << playerList[i] << " folds\n";
                        break;
                    case 2: // call/check
                        if (playerList[i].getBetAmount() == maxBet) {
                            std::cout << " * " << playerList[i] << " checks\n";
                        }
                        else {
                            int callMoney = (maxBet - playerList[i].getBetAmount());
                            if (playerList[i].getMoney() - callMoney <= 0) {
                                callMoney = playerList[i].getMoney();
                                playerList[i].setAllin(true);
                                std::cout << " * " << playerList[i] << " calls and is all in\n";
                            }
                            else {
                                std::cout << " * " << playerList[i] << " calls\n";
                            }
                            playerList[i].changeMoney(-callMoney);
                            playerList[i].changeBetAmount(callMoney);
                            pot += callMoney;
                        }
                        playerList[i].check();
                        break;
                    case 3: // raise
                        int raise = playerList[i].computerRaise(maxBet);
                        playerList[i].changeMoney(-raise);
                        playerList[i].changeBetAmount(raise);
                        pot += raise;
                        maxBet = playerList[i].getBetAmount();
                        if (playerList[i].getMoney() == 0) {
                            std::cout << " * " << playerList[i] << " raises $" << raise << " and is all in\n";
                            playerList[i].setAllin(true);
                        }
                        else {
                            std::cout << " * " << playerList[i] << " raises $" << raise << std::endl;
                        }
                        playerList[i].check();
                        resetCheckedAfterMaxBetChangeAfterFlop(playerList, i);
                        break;
                    }
                }
            }
            if (areEnoughFolded(playerList, playerList.size() - 1)) {
                isGameRunning = false;
                break;
            }
            if (areEnoughAllin(playerList, playerList.size() - 1)) {
                enoughAllin = true;
                break;
            }
            if (areAllChecked(playerList)) {
                allChecked = true;
                break;
            }
        }
    } while (!allChecked && isGameRunning && !enoughAllin);
}

void river(std::vector<Player> &playerList, int &maxBet, int &pot, bool &isGameRunning, std::vector<Card> riverDeck)
{
    bool allChecked = false;
    bool enoughAllin = false;

    do {
        for (int i = playerList.size() - 1; i >= 0; i--) {
            if (!playerList[i].isFolded() && !playerList[i].isAllin()) {
                if (playerList[i].isHuman()) {
                    int optionChoice;
                    optionChoice = displayOptionMenu(playerList[i], maxBet, riverDeck);
                    switch (optionChoice) {
                    case 1: // fold
                        playerList[i].fold();
                        std::cout << "\n * You fold\n";
                        break;
                    case 2: // call/check
                        if (playerList[i].getBetAmount() == maxBet) {
                            std::cout << "\n * You check\n";
                        }
                        else {
                            int callMoney = (maxBet - playerList[i].getBetAmount());
                            if (playerList[i].getMoney() - callMoney <= 0) {
                                callMoney = playerList[i].getMoney();
                                playerList[i].setAllin(true);
                                std::cout << "\n * You call and are all in\n";
                            }
                            else {
                                std::cout << "\n * You call\n";
                            }
                            playerList[i].changeMoney(-callMoney);
                            playerList[i].changeBetAmount(callMoney);
                            pot += callMoney;
                        }
                        playerList[i].check();
                        break;
                    case 3: // raise
                        int raise = playerList[i].humanRaise(maxBet);
                        playerList[i].changeMoney(-raise);
                        playerList[i].changeBetAmount(raise);
                        pot += raise;
                        maxBet = playerList[i].getBetAmount();
                        if (playerList[i].getMoney() == 0) {
                            std::cout << "\n * You raise $" << raise << " and are all in\n";
                            playerList[i].setAllin(true);
                        }
                        else {
                            std::cout << "\n * You raise $" << raise << std::endl;
                        }
                        playerList[i].check();
                        resetCheckedAfterMaxBetChangeAfterFlop(playerList, i);
                        break;
                    }
                }
                else {
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_int_distribution<> dis(1, 100);
                    int random = dis(gen);
                    int optionChoice;
                    if (random >= 15) {
                        optionChoice = 2; //85% chance to call/check
                    }
                    else {
                        optionChoice = 3; //15% chance to raise
                    }

                    switch (optionChoice) {
                    case 1: // fold
                        playerList[i].fold();
                        std::cout << " * " << playerList[i] << " folds\n";
                        break;
                    case 2: // call/check
                        if (playerList[i].getBetAmount() == maxBet) {
                            std::cout << " * " << playerList[i] << " checks\n";
                        }
                        else {
                            int callMoney = (maxBet - playerList[i].getBetAmount());
                            if (playerList[i].getMoney() - callMoney <= 0) {
                                callMoney = playerList[i].getMoney();
                                playerList[i].setAllin(true);
                                std::cout << " * " << playerList[i] << " calls and is all in\n";
                            }
                            else {
                                std::cout << " * " << playerList[i] << " calls\n";
                            }
                            playerList[i].changeMoney(-callMoney);
                            playerList[i].changeBetAmount(callMoney);
                            pot += callMoney;
                        }
                        playerList[i].check();
                        break;
                    case 3: // raise
                        int raise = playerList[i].computerRaise(maxBet);
                        playerList[i].changeMoney(-raise);
                        playerList[i].changeBetAmount(raise);
                        pot += raise;
                        maxBet = playerList[i].getBetAmount();
                        if (playerList[i].getMoney() == 0) {
                            std::cout << " * " << playerList[i] << " raises $" << raise << " and is all in\n";
                            playerList[i].setAllin(true);
                        }
                        else {
                            std::cout << " * " << playerList[i] << " raises $" << raise << std::endl;
                        }
                        playerList[i].check();
                        resetCheckedAfterMaxBetChangeAfterFlop(playerList, i);
                        break;
                    }
                }
            }
            if (areEnoughFolded(playerList, playerList.size() - 1)) {
                isGameRunning = false;
                break;
            }
            if (areEnoughAllin(playerList, playerList.size() - 1)) {
                enoughAllin = true;
                break;
            }
            if (areAllChecked(playerList)) {
                allChecked = true;
                break;
            }
        }
    } while (!allChecked && isGameRunning && !enoughAllin);
}

void flopDraw(std::vector<Card> &deck, std::vector<Card> &riverDeck, int pot)
{
    std::cout << "\n";
    deck.erase(deck.begin()); // burn card
    riverDeck.push_back(deck[0]);
    deck.erase(deck.begin(), deck.begin() + 2); // erase moved card + burn card
    riverDeck.push_back(deck[0]);
    deck.erase(deck.begin(), deck.begin() + 2); // erase moved card + burn card
    riverDeck.push_back(deck[0]);
    deck.erase(deck.begin()); // erase moved card
    std::cout << "Current pot: $" << pot << std::endl;
    std::cout << "Flop cards drawn.\n\n";
    system("pause");
    system("cls");
}

void turnDraw(std::vector<Card> &deck, std::vector<Card> &riverDeck, int pot)
{
    std::cout << "\n";
    deck.erase(deck.begin()); // burn card
    riverDeck.push_back(deck[0]);
    deck.erase(deck.begin()); // erase moved card
    std::cout << "Current pot: $" << pot << std::endl;
    std::cout << "Turn card drawn.\n\n";
    system("pause");
    system("cls");
}

void riverDraw(std::vector<Card> &deck, std::vector<Card> &riverDeck, int pot)
{
    std::cout << "\n";
    deck.erase(deck.begin()); // burn card
    riverDeck.push_back(deck[0]);
    deck.erase(deck.begin()); // erase moved card
    std::cout << "Current pot: $" << pot << std::endl;
    std::cout << "River card drawn.\n\n";
    system("pause");
    system("cls");
}
