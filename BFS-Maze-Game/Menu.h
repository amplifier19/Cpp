#ifndef MENU_H
#define MENU_H

#include "string"
#include "fstream"
#include "ncurses.h"

using namespace std;

class Menu 
{
private:
	WINDOW *win; // Δείτης τύπου WINDOW ο οποίος δείχνει στο παράθυρο του παιχνιδιού.
	string *Items; // Αποθήκευση των k στοιχείων του Μενού στον πίνακα Items[k].
	int ItemPos; // Θέση του στοιχείου το οποίο τυπώνεται με το χαρακτηριστικό A_STANDOUT στο παράθυρο.
	int numItems; // Αριθμός των στοιχέιων 
	int won; // Μέλος το οποίο καθορίζει τον 'τύπο' της νίκης. 
	
public:
	Menu(WINDOW *win, int inum); // Κατασκευαστής
	~Menu(); // Καταστροφέας
	bool handleTrigger(const int Trigger); // Μέθοδος για τον χειρισμό του πλήκτρου που πατήθηκε από τον χρήστη.
	void draw(int xmax, int ymax); // Μέθοδος για τον σχεδιασμό του Μενού στο παράθυρο.
	int getItemPos(); // Μέθοδος για την λήψη της θέσης του στοιχείου με το χαρακτηριστικό A_STANDOUT
	void setWon(int w); // Μέθοδος για την ανάθεση τιμής στο μέλος won.
};

#endif
