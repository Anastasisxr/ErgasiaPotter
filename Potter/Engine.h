#ifndef ENGINE_INCLUDED
#define ENGINE_INCLUDED
#include <string>
#include <cstring>
#include <iostream>
#include <curses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include "Traal.h"
#include "Gnome.h"
#include "Potter.h"
#include "HiScore.h"
#include "Moving.h"

using namespace std;

//η κλάση Engine διαχειρίζεται όλες τις λειτουργίες του παιχνιδιού
//έχει αντικείμενα απο όλες τις άλλες κλάσεις και είναι υπεύθυνη
//για την εκτέλεση των κατάλληλων εντολών για την ορθή λειτουργία
//του παιχνιδιού καθώσ και την σωστή εμφάνισή του στην οθόνη

class Engine{

	protected:
		WINDOW * primaryScreen;

		Traal traal;
		Gnome gnome;
		Potter potter;
		HiScore score;
		char** map;
		int** secondaryMap;
		int mapx;
		int mapy;


	public:
		void startScreen();
		void cleanMap();
		void readMap(string); //διάβασμα του χάρτη απο το αρχείο
		void printScreen(); //εμφάνισει του παιχνιδιού στην οθόνη
		void setPrimaryScreen(); //αρχικοποίηση του ncurses
		void closeScreen(); //κλήσημο της οθόνης
		void initializeChars(); //αρχικοποίηση των χαρακτήρων στην οθόνη
		void initializeGems(); //αρχικοποίηση των διαμαντιών στην αθόνη
		void gameWin(int); //τελική οθόνη νίκης
		void gameLose(int, const char*); //τελική οθόνη ήττας
		void gameStart(); //εκκίνηση του παιχνιδιού
		~Engine();

};

#endif