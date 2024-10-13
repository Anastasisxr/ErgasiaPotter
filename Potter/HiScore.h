#ifndef HISCORE_INCLUDED
#define HISCORE_INCLUDED
#include <string>
#include <fstream>
#include <stdio.h>
#include <string.h>

using namespace std;

//η κλάση HiScore διαβάζει, ταξινομεί και γράφει τα 5 μεγαλύτερα
//scores σε ένα δυαδικό αρχείο

class HiScore{

	protected:
		char names[5][11];
		int scores[5];
		char tempname[11];
		int tempscore;
		char sortNameHelper[11];
		int sortScoreHelper;


	public:

		HiScore();
		void readScores();// διαβάζει τα scores απο το αρχείο
		void printScores();//γράφει τα scores στο αρχείο
		void sortScores();//ταξινομεί τα scores
		HiScore operator<<(const char*);//υπερφόρτωση του τελεστή << για χαρακτήρες
		void operator<<(int);//υπερφόρτωση του τελεσή << για ακέραιους
		
		//getters
		char* getNames(int);
		int getScores(int);
};

#endif