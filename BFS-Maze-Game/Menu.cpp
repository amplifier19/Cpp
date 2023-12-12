#include "ncurses.h"
#include "Menu.h"
#include "string"

#define UP_KEY 65
#define DOWN_KEY 66

using namespace std;

Menu::Menu(WINDOW *win, int inum)
{
	this->win = win;
	Items = new string[inum];
	Items[0] = "PLAY";
	Items[1] = "EXIT";
	ItemPos = 0;
	numItems = inum;
	won = 0;
}

Menu::~Menu()
{
	delete[] Items;
	delete win;
}

bool Menu::handleTrigger(const int Trigger)
{
	if (Trigger == '\n') return true;
	if (Trigger == KEY_DOWN)
	{
		if (ItemPos == numItems-1) ItemPos = -1;
		++ItemPos;
	}
	if (Trigger == KEY_UP)
	{
		if (ItemPos == 0) ItemPos = numItems;
		--ItemPos;
	}
	return false;
}

void Menu::draw(int xmax, int ymax)
{	
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);

		wattron(win, A_BOLD);
		mvwprintw(win, 0.3*ymax, 0.5*xmax, "************************************************************");
		mvwprintw(win, (0.3*ymax)+1, 0.5*xmax, "*");
		wattron(win, COLOR_PAIR(1));
		mvwprintw(win, (0.3*ymax)+1, (0.5*xmax)+1, "   ///||\\\\\\ ||  | ||||    |\\\\  /||   /\\\\   /////   ||||   ");
		wattroff(win, COLOR_PAIR(1));
		mvwprintw(win, (0.3*ymax)+1, (0.5*xmax)+59, "*");
		mvwprintw(win, (0.3*ymax)+2, 0.5*xmax, "*");
		wattron(win, COLOR_PAIR(1));
		mvwprintw(win, (0.3*ymax)+2, (0.5*xmax)+1, "      ||    ||==| |==     | \\\\/ ||  /==\\\\     /    |==    ");
		wattroff(win, COLOR_PAIR(1));
		mvwprintw(win, (0.3*ymax)+2, (0.5*xmax)+59, "*");
		mvwprintw(win, (0.3*ymax)+3, 0.5*xmax, "*");
		wattron(win, COLOR_PAIR(1));
		mvwprintw(win, (0.3*ymax)+3, (0.5*xmax)+1, "      ||    ||  | ||||    |     || /    \\\\   ///// ||||   ");
		wattroff(win, COLOR_PAIR(1));
		mvwprintw(win, (0.3*ymax)+3, (0.5*xmax)+59, "*");
		mvwprintw(win, (0.3*ymax)+4, 0.5*xmax, "************************************************************");	
		
	if (won == 1)
	{
		init_pair(2, COLOR_GREEN, COLOR_BLACK);
		mvwprintw(win, (0.3*ymax)+7, 0.7*xmax, "***************************************");
		mvwprintw(win, (0.3*ymax)+8, 0.7*xmax, "*");
		wattron(win, COLOR_PAIR(2));
		mvwprintw(win, (0.3*ymax)+8, (0.7*xmax)+1, "  \\\\// /|\\ || |   \\\\ || / /|\\ ||\\ |  ");
		wattroff(win, COLOR_PAIR(2));
		mvwprintw(win, (0.3*ymax)+8, (0.7*xmax)+38, "*");
		mvwprintw(win, (0.3*ymax)+9, 0.7*xmax, "*");
		wattron(win, COLOR_PAIR(2));
		mvwprintw(win, (0.3*ymax)+9, (0.7*xmax)+1, "   ||  \\|/ ||_|    \\\\/\\/  \\|/ || \\|  ");
		wattroff(win, COLOR_PAIR(2));
		mvwprintw(win, (0.3*ymax)+9, (0.7*xmax)+38, "*");
		mvwprintw(win, (0.3*ymax)+10, 0.7*xmax, "***************************************");
	}
	else if (won == 2)
	{
		init_pair(3, COLOR_RED, COLOR_BLACK);
		mvwprintw(win, (0.3*ymax)+7, 0.7*xmax, "*****************************************");
		mvwprintw(win, (0.3*ymax)+8, 0.7*xmax, "*");
		wattron(win, COLOR_PAIR(3));
		mvwprintw(win, (0.3*ymax)+8, (0.7*xmax)+1, "  \\\\// /|\\ || |   ||   /|\\ //_  //|\\\\  ");
		wattroff(win, COLOR_PAIR(3));
		mvwprintw(win, (0.3*ymax)+8, (0.7*xmax)+40, "*");
		mvwprintw(win, (0.3*ymax)+9, 0.7*xmax, "*");
		wattron(win, COLOR_PAIR(3));
		mvwprintw(win, (0.3*ymax)+9, (0.7*xmax)+1, "   ||  \\|/ ||_|   ||__ \\|/   //   |    ");
		wattroff(win, COLOR_PAIR(3));
		mvwprintw(win, (0.3*ymax)+9, (0.7*xmax)+40, "*");
		mvwprintw(win, (0.3*ymax)+10, 0.7*xmax, "*****************************************");	
	}
	
	for (int i = 0; i < numItems; i++)
	{	
		if (ItemPos == i) wattron(win, A_STANDOUT);
		
		mvwprintw(win, (ymax)+i, xmax, Items[i].c_str());
		wattroff(win, A_STANDOUT);	
	}
	wattroff(win, A_BOLD);
}
	
int Menu::getItemPos() 
{
	return ItemPos;
}  

void Menu::setWon(int w)
{
	won = w;
}
