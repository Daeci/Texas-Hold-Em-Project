#pragma once
#include "Card.h"

class Player {
private:
    Card c1;
    Card c2;
    int money;
    int playerNumber;
    int betAmount;
    bool human;
    bool folded;
    bool bigBlind;
    bool smallBlind;
public:
    Player() { /* place holder */ }
    Player(Card c1, Card c2, int startingMoney) { this->c1 = c1; this->c2 = c2; money = startingMoney; }
    Card getCard1() { return c1; }
    Card getCard2() { return c2; }
    void setHuman(bool b) { human = b; }
    void setBigBlind(bool b) { bigBlind = b; }
    void setSmallBlind(bool b) { smallBlind = b; }
    void setCards(Card c1, Card c2) { this->c1 = c1; this->c2 = c2; }
    void setMoney(int money) { this->money = money; }
    void changeMoney(int money) { this->money += money; }
    void initFolded() { folded = false; }
    void initBetAmount() { betAmount = 0; }
    void changeBetAmount(int amount) { betAmount += amount; }
    bool isHuman() { return human; }
    bool isFolded() { return folded; }
    int getMoney() { return money; }
    int getBetAmount() { return betAmount; }
    friend std::ostream& operator<<(std::ostream &os, const Player&);
    void fold() { folded = true; }
    void humanRaise(int maxBet);
    void computerRaise();
};
