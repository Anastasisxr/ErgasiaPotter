#include "Potter.h"
#include "Moving.h"


Potter::Potter():Moving(){

}

char** Potter::moveCharacter(int potterMove, char** map){

	int potterX,potterY;

	//επιλογή της κατάλλιλης κίνησης ανάλογα με το input του χρήστη
	potterX = this->possX;
	potterY = this->possY;


	switch(potterMove)
	{
		case KEY_UP : potterY--; break;
		case KEY_DOWN : potterY++; break;
		case KEY_LEFT: potterX--; break;
		case KEY_RIGHT: potterX++; break;
	}

	
	//έλεγχος για το άν είναι valid η κίνηση καθός και για το άν υπάρχει διαμάντι/scroll στην επόμενη θέση
	if(map[potterY][potterX] != '*' && map[potterY][potterX] != 'G' && map[potterY][potterX] != 'T')
		if(map[potterY][potterX] == 'D'){
			map[this->possY][this->possX] = ' ';
			map[potterY][potterX] = 'P';
			this->possX = potterX;
			this->possY = potterY;
			this->gemCount++;
			validMove = true;
		}
		else if(map[potterY][potterX] == 'S'){
			map[this->possY][this->possX] = ' ';
			map[potterY][potterX] = 'P';
			this->possX = potterX;
			this->possY = potterY;
			this->flagGet = true;
			validMove = true;
		}
		else{
			map[this->possY][this->possX] = ' ';
			map[potterY][potterX] = 'P';
			this->possX = potterX;
			this->possY = potterY;
			validMove = true;
		}

	//εάν στην επόμενη θέση υπάρχει τίχος κατέβασε το flag για την valid κίνηση
	if(map[potterY][potterX] == '*')
		validMove = false;

	return map;
}

//setters
void Potter::setgemCount(int gemCount){
	this->gemCount = gemCount;
}

void Potter::setflagGet(bool flagGet){
	this->flagGet = flagGet;
}

void Potter::setvalidMove(bool validMove){
	this->validMove = validMove;
}

//getters
int Potter::getgemCount(){
	return this->gemCount;
}

bool Potter::getflagGet(){
	return this->flagGet;
}

bool Potter::getvalidMove(){
	return this->validMove;
}