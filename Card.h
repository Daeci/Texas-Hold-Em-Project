#pragma once
#include <string>

class Card {
    std::string suit;
    std::string value;
public:
    Card();
    Card(std::string suit, std::string value);

};