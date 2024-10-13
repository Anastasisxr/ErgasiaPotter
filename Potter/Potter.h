#ifndef POTTER_INCLUDED
#define POTTER_INCLUDED
#include <string>
#include "Moving.h"

//η κλάση potter ελέγχει την κίνηση του χρήστη στον χάρτι και το score καθός
class Potter:public Moving{

	protected:
		int gemCount;
		bool flagGet;
		bool validMove;
		
	public:
		Potter();
		char** moveCharacter(int, char**);//μετακίνηση του χαρακτήρα στον χάρτη
		
		//setters
		void setgemCount(int);
		void setflagGet(bool);
		void setvalidMove(bool);
		
		//getters
		bool getflagGet();
		bool getvalidMove();
		int getgemCount();
};


#endif