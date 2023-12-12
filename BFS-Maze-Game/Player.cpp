#include "Player.h"
#include "string"
#include "ctime"
#include "cstdlib"
#include "vector"

void Player::spawn(vector<string> &map, int lines, int columns)
{
	if(spawned == false)
	{
		srand(time(0));
		do 
		{
			currentX = (rand() % ((lines / 2) - 1)) + 1;
			currentY = (rand() % (columns - 1)) + 1;
		}
		while (map[currentX][currentY] != '.');
		spawned = true;
	}
}

bool Player::move(vector<string> &map)
{	
	if (map[newX][newY] == '.')
	{
		currentX = newX;
		currentY = newY;
		return true;
	}
	return false;
}

int Player::getCurrentX()
{
	return currentX;
}

int Player::getCurrentY()
{
	return currentY;
}

void Player::setCurrentX(int X)
{
	currentX = X;
}

void Player::setCurrentY(int Y)
{
	currentY = Y;
}

void Player::setSpawned(bool s)
{
	spawned = s; 
}
