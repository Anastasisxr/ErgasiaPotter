#ifndef TRAAL_INCLUDED
#define TRAAL_INCLUDED
#include <string>
#include "Moving.h"

//η κλάση traal κληρονομή τις όλα τα στοιχεία της απο την κλάση Moving 
//και έχει την δική της υλοποίηση για την έυρεση του παίχτη καθός και
//την μετακίνηση του χαρακτήρα

class Traal:public Moving{

	public:
		Traal();
		int findShortestPath(int**, int, int);
		char** moveCharacter(int, char**);

};


#endif