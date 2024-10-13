#ifndef MOVING_INCLUDED
#define MOVING_INCLUDED
#include <string>
#include <stdlib.h>
#include <time.h>
#include <curses.h>

//η κλάση moving περιέχει όλες τις βασικές μεταβλητές και λειτουργίες που θα κληρονομήσουν τα αντικείμενα Potter, Gnome και Traal

using namespace std;

class Moving {

	protected:
		int possY;
		int possX;
		char symbol;
		int mapx;
		int mapy;
		bool potterEaten;
		bool monsterOverDiamond;
		bool monsterOverScroll;

	public:
		Moving();
		void setStaringPoss(int, int, char**); //βάζει τον χαρακτήρα σε μία αρχεική θέση στον χάρτη
		virtual char** moveCharacter(int, char**); // η συνάρτηση μετακίνησης του χαρακτήρα
		
		//setters
		void setX(int);
		void setY(int);
		void setMapx(int);
		void setMapy(int);
		void setSymbol(const char);
		void setpotterEaten(bool);
		void setmonsterOverDiamond(bool);
		void setmonsterOverScroll(bool);
		
		//getters
		bool getpotterEaten();
		int getX();
		int getY();

};

#endif