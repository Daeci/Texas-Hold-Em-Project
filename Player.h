#pragma once
#include "Card.h"

class Player {
    Card c1;
    Card c2;
public:
    Player() { /* place holder */ }
    Player(Card c1, Card c2) { this->c1 = c1; this->c2 = c2; }
    Card getCard1() { return c1; }
    Card getCard2() { return c2; }
};