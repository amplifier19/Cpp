#ifndef MALFOY_H
#define MALFOY_H

#include "Player.h"

class Malfoy : public Player
{
public:
	Malfoy();// Κατασκευαστής
	bool validMove(const int ch); // Η μέθοδος Malfoy:validMove() δεν θα χρησιμοποιηθεί από το πρόγραμμα, υλοποιείται για λόγους μεταγλώττισης.
	int hasWon(int diamondX, int diamondY);// Η μέθοδος Player::Malfoy::hasWon() ελέγχει εάν ο Μαλφόης κέρδισε το παιχνίδι.
						// Επιστρέφει 2 στην περίπτωση που κέρδισε και 0 σε άλλη περίπτωση.
};

#endif
