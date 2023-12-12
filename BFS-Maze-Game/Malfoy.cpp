#include "Malfoy.h"
#include "Player.h"

Malfoy::Malfoy()
{
	spawned = false;
}

int Malfoy::hasWon(int diamondX, int diamondY)
{
	if (currentX == diamondX && currentY == diamondY) return 2;
	return 0;
}

bool Malfoy::validMove(const int ch)
{
	return true;
}
