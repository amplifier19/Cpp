#include "Pottery.h"
#include "Player.h"
#include "ncurses.h"

#define SPACE_KEY 32

Pottery::Pottery()
{
	spawned = false;
}

bool Pottery::validMove(const int ch)
{
	if (ch == KEY_UP)
	{
		newX = currentX - 1;
		newY = currentY;
		return true;
	}
	else if (ch == KEY_DOWN)
	{
		newX = currentX + 1;
		newY = currentY;
		return true;
	}
	else if (ch == KEY_RIGHT)
		{
		newY = currentY + 1;
		newX = currentX;
		return true;
	}
	else if (ch == KEY_LEFT)
	{
		newY = currentY - 1;
		newX = currentX;
		return true;
	}
	else if (ch == SPACE_KEY)
	{
		newX = currentX;
		newY = currentY;
		return true;	
	}
	return false;
}

int Pottery::hasWon(int diamondX, int diamondY)
{
	if (currentX == diamondX && currentY == diamondY)
		return 1;
	return 0;
}

