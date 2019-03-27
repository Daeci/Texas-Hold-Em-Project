#pragma once
#include <iostream>
#include <string>
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