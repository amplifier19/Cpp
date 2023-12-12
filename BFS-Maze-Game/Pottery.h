#ifndef POTTERY_H
#define POTTERY_H

#include "Player.h"
#include "string"

class Pottery : public Player
{
public:
	Pottery(); // Κατασκευαστής
	bool validMove(const int ch); // Δήλωση της μεθόδου η οποία κληρονομείται από την κλάση πατέρα Player για τον έλεγχο της κίνησης του Παίκτη. Καλείται από τη μέθοδο Maze::handleTrigger()
	int hasWon(int diamondX, int diamondY); // Η μέθοδος Player::Malfoy::hasWon() ελέγχει εάν ο Ποτερίδης κέρδισε το παιχνίδι.
						 // Επιστρέφει 1 στην περίπτωση που κέρδισε και 0 σε άλλη περίπτωση. Καλείται από τη μέθοδο Maze::handleTrigger()
};

#endif
