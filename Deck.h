#pragma once
#include "Card.h"
#include <vector>

class Deck : public Card{
public:
    void fillDeck(std::vector<Card> *deck);
};
