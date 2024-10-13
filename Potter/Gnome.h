#ifndef GNOME_INCLUDED
#define GNOME_INCLUDED
#include <string>
#include "Moving.h"

//η κλάση gnome κληρονομή τις όλα τα στοιχεία της απο την κλάση Moving 
//και έχει την δική της υλοποίηση για την έυρεση του παίχτη καθός και
//την μετακίνηση του χαρακτήρα

class Gnome:public Moving {

	public:
		Gnome();
		int findShortestPath(int**, int, int);
		char** moveCharacter(int, char**);

};


#endif