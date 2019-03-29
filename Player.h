#pragma once
#include "Card.h"

class Player {
private:
    Card c1;
    Card c2;
    int money;
    int playerNumber;
    bool isHuman;
    bool isBigBlind;
    bool isSmallBlind;
public:
    Player() { /* place holder */ }
    Player(Card c1, Card c2, int startingMoney) { this->c1 = c1; this->c2 = c2; money = startingMoney; }
    Card getCard1() { return c1; }
    Card getCard2() { return c2; }
    void setHuman(bool b) { isHuman = b; }
    void setPlayerNumber(int num) { playerNumber = num; }
    void setBigBlind(bool b) { isBigBlind = b; }
    void setSmallBlind(bool b) { isSmallBlind = b; }
    friend std::ostream& operator<<(std::ostream &os, const Player&);
};
