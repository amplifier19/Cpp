#include "Diamond.h"
#include "ctime"
#include "cstdlib"
#include "string"
#include "vector"

using namespace std;

Diamond::Diamond()
{
	remainingMoves = 0; 
}

bool Diamond::spawn(vector<string> &map, int lines, int columns)
{
	if (remainingMoves == 0)
	{
		srand(time(0));
		do 
		{
			posx = (rand() % (lines / 2)) + (lines / 2) - 1;
			posy = (rand() % (columns - 1)) + 1;
		}
		while (map[posx][posy] != '.');
		remainingMoves = (rand() % 12) + 33;
		return true;
	}
	return false;
}

void Diamond::reduceMoves()
{
	if (remainingMoves > 0) --remainingMoves;
}

int Diamond::getPosx()
{
	return posx;
}

int Diamond::getPosy()
{
	return posy;
}

void Diamond::InitRemainingMoves()
{
	remainingMoves = 0;
}
