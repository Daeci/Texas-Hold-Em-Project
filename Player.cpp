#include "Player.h"

std::ostream& operator<<(std::ostream &os, const Player& p)
{
    os << "Player " << p.playerNumber << std::endl;
}
