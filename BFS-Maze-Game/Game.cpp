#include "Menu.cpp"
#include "Maze.cpp"
#include "stdio.h"
#include "stdlib.h"
#include "string"
#include "string.h"
#include "fstream"
#include "ncurses.h"
#include"iostream"
#include "sstream"
#include "unistd.h"
#include "signal.h"

#define menuItems 2

using namespace std;

int main (int argc, char *argv[])
{

// Αρχικοποίηση Οθόνης και Παραθύρου
	cout << "\e[8;45;150t";
	cout.flush();
	sleep(1);
	initscr();
	try
	{
		if (!has_colors()) throw "Το τερματικό δεν υποστιρίζει χρώματα";
	}
	catch (char const* exc)
	{
		endwin();
		cout << "\nΕξαίρεση " << exc << "\n\n";
		return 0;
	}
	start_color();
	curs_set(0);
	noecho();
	
	int yMax, xMax;
		
	getmaxyx(stdscr, yMax, xMax);
	WINDOW *win = newwin(34, 117, yMax/8, xMax/8);
	keypad(win, TRUE);
	set_escdelay(0);


// Διάβασμα χάρτη
	bool FileOpened;
	bool EXIT_MENU = false;
	bool EXIT_GAME = false;
	int ch;
	int won;
	
	Maze maze(win, new Pottery(), new Malfoy());
	FileOpened = maze.readMap(argv[1]);
	try
	{	
		if (!FileOpened) throw "Σφάλμα κατά το άνοιγμα του αρχείου.";
	}
	catch (char const* exc)
	{
		endwin();
		cout << "\nΕξαίρεση: " << exc << "\n\n";
		return 0;
	}
	
	Menu menu(win, menuItems);
	menu.draw(117/2, 39/2);
	wrefresh(win);

	
// Βρόγχος του Μενού
	while(!EXIT_MENU)
	{
		wresize(win, 34, 117);
		wrefresh(win);
		box(win, '#', '#');
		menu.draw(117/2, 39/2);
		ch = wgetch(win);
		EXIT_MENU = menu.handleTrigger(ch);
		
		if (EXIT_MENU && menu.getItemPos() == 0)
		{	
			werase(win);
			wrefresh(win);
			wresize(win, maze.getLines(), maze.getColumns()*3);
			wrefresh(win);
			maze.draw(true);
			wrefresh(win);
			
		// Βρόγχος του Παιχνιδιού
			while(!EXIT_GAME)
			{	
				won = 0;
				ch = wgetch(win);
				won = maze.handleTrigger(ch);
				box(win, 0, 0);
				maze.draw(false);
				
				if(won > 0)
				{
					EXIT_GAME = true;
					menu.setWon(won);
				}
				else if (won < 0)
				{
					EXIT_GAME = true;
					menu.setWon(0);
				}
					 
			}
			werase(win);
			wrefresh(win);
			maze.Replay();
			EXIT_MENU = false;
			EXIT_GAME = false;
		}
		
	}
		
	endwin();
	delete win;
	return 0;

} 
