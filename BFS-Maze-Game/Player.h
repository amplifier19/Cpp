#ifndef PLAYER_H
#define PLAYER_H

#include "string"
#include "vector"

class Player
{
protected:
	int currentX; // Τρέχουσα γραμμή όπου βρίσκεται ο Παίκτης.
	int currentY; // Τρέχουσα στήλη όπου βρίσκεται ο Παίκτης.
	int newX; // Γραμμή της επόμενης θέσης όπου θα μετακινηθεί ο Παίκτης.
	int newY; // Στήλη της επόμενης θέσης όπου θα μετακινηθεί ο Παίκτης.
	bool spawned; // Μέλος για τον έλεγχο αρχικοποίησης της θέσης του Παίκτη.
	
public:
	void spawn(vector<string> &map, int lines, int columns); // Μέθοδος για την επιλογή θέσης του κάθε Παίκτη. Καλείται από την μέθοδο Maze::draw().
	virtual bool validMove(const int ch) = 0; //Pure virtual μέθοδος για τον έλεγχο της κίνησης του Παίκτη. Καλείται από την μέθοδο Maze::handleTrigger().
	bool move(vector<string> &map); // Μέθοδος για την κίνηση του κάθε Παίκτη. Καλείται από την μέθοδο Maze::handleTrigger().
	virtual int hasWon(int diamondX, int diamondY) = 0; // Pure virtual μέθοδος για τον έλεγχο της νίκης του κάθε Παίκτη.
	int getCurrentX(); // Μέθοδος για την λήψη της γραμμής που βρίσκεται ο κάθε Παίκτης στον πίνακα-χάρτη.
	int getCurrentY(); // Μέθοδος για την λήψη της στήλης που βρίσκεται ο κάθε Παίκτης στον πίνακα-χάρτη.
	void setCurrentX(int X); // Μέθοδος για την ανάθεση τιμής στο μέλος currentX.
	void setCurrentY(int Y); // Μέθοδος για την ανάθεση τιμής στο μέλος currentΥ.
	void setSpawned(bool s); // Μέθοδος για την ανάθεση τιμής στο μέλος spawned.
};

#endif 
