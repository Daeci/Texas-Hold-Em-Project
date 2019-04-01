#include "Player.h"

std::ostream& operator<<(std::ostream &os, const Player& p)
{
    os << "Player " << p.playerNumber << std::endl;
}

void Player::humanRaise(int maxBet)
{
    std::cout << "Remaining money: " << money;
    int raiseAmount = 0;
    do {
        std::cout << "Raise amount: ";
        std::cin >> raiseAmount;
        if (raiseAmount <= (maxBet - betAmount)) {
            std::cout << "Raise needs to be higher than the max bet!\n";
        }
    } while (raiseAmount <= (maxBet - betAmount));
}

void Player::computerRaise()
{

}
