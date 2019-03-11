#include "Card.h"
#include <string>

Card::Card(std::string suit, std::string value)
{
    this->suit = suit;
    this->value = value;
}