#ifndef DIAMOND_H
#define DIAMOND_H

#include "string"
#include "vector"

using namespace std;

class Diamond
{
private:
	int posx; // Γραμμή της θέσης του πετραδιού
	int posy; // Στήλη της θέσης του πετραδιού
	int remainingMoves; // Εναπομείνασες κινήσεις, προκειμένου να αλλάξει θέση.
public:
	Diamond();
	bool spawn(vector<string> &map, int lines, int columns); // Μέθοδος για την επιλογή θέσης του Πετραδιού. 
	void reduceMoves(); // Μέθοδος για την μείωση των εναπομεινασών κινήσεων. Καλείται κάθε φορά που κινείται ο Ποτερίδης από τον χρήστη
	
	int getPosx(); // Μέθοδος για την λήψη της γραμμής στην οποία βρίσκεται το πετράδι.
	int getPosy(); // Μέθοδος για την λήψη της στήλης στην οποία βρίσκεται το πετράδι.
	void InitRemainingMoves(); // Μέθοδος για τον μηδενισμό των εναπομεινασών κινήσεων. Καλείται από την μέθοδο Maze::Replay() μετά το τέλος οποιουδήποτε γύρου. 
};
#endif
