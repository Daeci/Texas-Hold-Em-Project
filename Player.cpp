/*
* Created by: Sascha Scheidegger and Mitchell Caughron
*/
#include <random>
#include "Player.h"

std::ostream& operator<<(std::ostream &os, const Player& p)
{
    return os << "Player " << p.playerNumber;
}

int Player::humanRaise(int maxBet)
{
    std::cout << "Remaining money to raise with: $" << money << std::endl;
    int raiseAmount = 0;
    do {
        std::cout << "Raise amount: ";
        std::cin >> raiseAmount;
        if (!std::cin) {
            throw("You were only supposed to input a number. Shame on you.\n");
        }
        else if (raiseAmount <= (maxBet - betAmount)) {
            std::cout << "Raise needs to be higher than the max bet!\n";
        }
        else if (raiseAmount > money) {
            std::cout << "You cannot raise more than what you have!\n";
        }
        else {
            return raiseAmount;
        }
    } while (raiseAmount <= (maxBet - betAmount) || raiseAmount > money);
}

int Player::computerRaise(int maxBet)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    int minRaise = (maxBet - betAmount + 1);
    std::uniform_int_distribution<> dis(minRaise, money);
    return dis(gen);
}
