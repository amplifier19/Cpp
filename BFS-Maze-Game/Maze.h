#ifndef MAZE_H
#define MAZE_H

#include "Diamond.h"
#include "ncurses.h"
#include "string"
#include "Player.h"
#include "Pottery.h"
#include "Malfoy.h"
#include "vector"
#include "stack"

using namespace std;

class Maze 
{
private:
	WINDOW *win; // Δείτης τύπου WINDOW ο οποίος δείχνει στο παράθυρο του παιχνιδιού.
	
	int lines; // Αριθμός γραμμών που περιέχει ο χάρτης.
	int columns; // Αριθμός στηλών που περιέχει ο χάρτης.
	vector<string> map; // Διάνυσμα αλφαριθμητικών για την αποθήκευση της κάθε γραμμής του πίνακα-χάρτη.
	vector<int> *adj; //Αποθήκευση των γειτονικών κόμβων του κάθε κόμβου σε διανύσματα.
	stack<int> path; // Αποθήκευση των κόμβων, οι οποίοι συνθέτουν το κοντινότερο μονοπάτι.
	Diamond diamond; // Πετράδι
	Player *pottery; // Δείκτης τύπου Player ο οποίος δείχνει σε αντικείμενο της κλάσης Player::Pottery.
	Player *malfoy; // Δείκτης τύπου Player ο οποίος δείχνει στο αντικείμενο Player::Malfoy.
public:
	Maze(WINDOW *w, int lines, int columns, Player *pot, Player *mal); // Κατασκευαστής
	Maze(WINDOW *w, Player *pot, Player *mal); // Κατασκευαστής 
	~Maze(); // Καταστροφέας
	bool readMap(const char* fileName); // Μέθοδος για το διάβασμα του χάρτη από αρχείο κειμένου και αποθήκευσή του στον πίνακα map. 
	void draw(bool firstDraw); // Μέθοδος για την σχεδίαση του παραθύρου.
	int handleTrigger(const int ch); // Μέθοδος για τον χειρισμό του πλήκτρο που πατήθηκε από τον παίκτη Ποτείδη.
	void findNeighbours(); // Ανίχνευση των γειτονικών κόμβων. Για κάθε κόμβο i, οι k γειτονικοί κόμβοι αποθηκεύονται στο διάνυσμα adj[i][k]. Καλείται από την μέθοδο Maze::draw().
	void BFS(int src, int dest, vector<int> &parent, vector<int> &dist); // Αναζήτηση του πετραδιού κατα πλάτος. Καλείται από την μέθοδο Maze::findShortestPath().
	void findShortestPath(int s, int dest); // Μέθοδος για εύρεση του συντομότερου μονοπατιού. Καλείται από την μέθοδο Maze::draw()
	int getMalfoyNextX(); // Μέθοδος για τον υπολογισμό της γραμμής στην οποία θα κατευθυνθεί ο Μαλφόης.
	int getMalfoyNextY(); // Μέθοδος για τον υπολογισμό της στήλης οπου θα κατευθυνθεί ο Μαλφόης.
	void Replay(); // Μέθοδος για τροποποίηση των αντικειμένων diamond, pottery, malfoy προκειμένου να επαναληφθεί το παιχνίδι.
	int getLines();
	int getColumns();
};

#endif
