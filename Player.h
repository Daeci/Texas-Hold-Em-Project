#pragma once
/*
 * Created by: Sascha Scheidegger and Mitchell Caughron
 */
#include "Card.h"

class Player {
private:
    Card c1;
    Card c2;
    int money{ 0 };
    int playerNumber{ 0 };
    int betAmount{ 0 };
    bool human{ false };
    bool folded{ false };
    bool checked{ false };
    bool allin{ false };
    bool bigBlind{ false };
    bool smallBlind{ false };
public:
    Player() { /* place holder */ }
    Player(Card c1, Card c2, int startingMoney) { this->c1 = c1; this->c2 = c2; money = startingMoney; }
    ~Player() { /* place holder */ }
    Card getCard1() { return c1; }
    Card getCard2() { return c2; }
    void setHuman(bool b) { human = b; }
    void setBigBlind() { bigBlind = true; }
    void setSmallBlind() { smallBlind = true; }
    void setCards(Card c1, Card c2) { this->c1 = c1; this->c2 = c2; }
    void setMoney(int money) { this->money = money; }
    void setPlayerNumber(int number) { playerNumber = number; }
    void setChecked(bool b) { checked = b; }
    void setAllin(bool b) { allin = b; }
    void resetBlinds() { bigBlind = false; smallBlind = false; }
    void changeMoney(int money) { this->money += money; }
    void changeBetAmount(int amount) { betAmount += amount; }
    bool isHuman() { return human; }
    bool isFolded() { return folded; }
    bool isChecked() { return checked; }
    bool isAllin() { return allin; }
    int getMoney() { return money; }
    int getBetAmount() { return betAmount; }
    friend std::ostream& operator<<(std::ostream &os, const Player&);
    void fold() { folded = true; }
    void check() { checked = true; }
    int humanRaise(int maxBet);
    int computerRaise(int maxBet);
};
