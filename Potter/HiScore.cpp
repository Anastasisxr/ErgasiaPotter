#include "HiScore.h"

HiScore::HiScore(){

	//αρχικοποίηση των βοηθητικών μεταβλητών με τερματικούς χαρακτήρες
	strcpy(tempname, "\0\0\0\0\0\0\0\0\0\0\0");
	strcpy(sortNameHelper,"\0\0\0\0\0\0\0\0\0\0\0");

}

void HiScore::readScores(){

	//διάβασε απο το αρχείο Score.dat χωριστά τα ονόματα και τα scores και βάλτα στους ανάλογους πίνακες
	ifstream filePointer("Score.dat", ios::in | ios::binary);

	for(int i = 0; i<5; i++){
			filePointer.read((char *)&names[i], sizeof(char)*11);
			filePointer.read((char *)&scores[i], sizeof(int));
		}

		filePointer.close();

}


void HiScore::printScores(){

	//γράψε χωριστά στο αρχείο Score.dat τα ονόματα και τα scores
	ofstream filePointer("Score.dat", ios::out | ios::binary);

	for(int i = 0; i<5; i++){
			filePointer.write((char *)&names[i], sizeof(char)*11);
			filePointer.write((char *)&scores[i], sizeof(int));
		}

	filePointer.close();

}

void HiScore::sortScores(){

	//ταξινόμηση τα scores κατα φθίνουσα σειρά και βάλε το νέο score στην κατάλληλη θέση
	for(int i = 0; i<5; i++)
		if(tempscore>=scores[i]){
			sortScoreHelper = scores[i]; 
			scores[i] = tempscore;
			tempscore = sortScoreHelper;


			strcpy(sortNameHelper,names[i]);
			strcpy(names[i], tempname);
			strcpy(tempname, sortNameHelper);
		}


	this->printScores();
}

//η υπερφόρτωση του τελεστή << για να πάρουμε το όνομα του καινούργιου score
//και να το βάλουμε σε έναν βοηθητικό πίνακα
HiScore HiScore::operator<<(const char* name){
	
	strcpy(tempname, name);

	return *this;
	
}

//η υπερφόρτωση του τελεστή << για να πάρουμε το score
//και να το βάλουμε σε μία βοηθητική μεταβλητή
void HiScore::operator<<(int score){

	this->tempscore = score;

	this->sortScores();

}

//getters
char* HiScore::getNames(int i){
	return this->names[i];
}

int HiScore::getScores(int i){
	return this->scores[i];
}