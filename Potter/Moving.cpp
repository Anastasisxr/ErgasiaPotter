#include "Moving.h"



Moving::Moving(){

}

//απο λειτουργίες η Moving υλοποιεί μόνο την αρχικοποίηση των χαρακτήρων στον
//χάρτη και τα setters με getters όπου χρειάζονται

void Moving::setStaringPoss(int mapy, int mapx, char** map){

	int i,j;
	bool done = false;

	srand (time(NULL));

	//με χρήση της rand βρές δύο συντεταγμένες μέσα στα όρια του χάρη
	//και εάν είναι κενή η θέση βάλε τον ανάλογο χαρακτήρα
	do{
		i = rand() % ((mapx-1) + 1);
		j = rand() % ((mapy-1) + 1);

		if(map[j][i] == ' ')
		{
			map[j][i] = this->symbol;
			done = true;
		}

	}while(!done);

	this->possX = i;
	this->possY = j;
}

char** Moving::moveCharacter(int move, char** map){

	return NULL;
}

//setters
void Moving::setX(int possX){
	this->possX = possX;
}

void Moving::setY(int possY){
	this->possY = possY;
}

void Moving::setMapx(int mapx){
	this->mapx = mapx;
}

void Moving::setMapy(int mapy){
	this->mapy = mapy;
}

void Moving::setSymbol(const char symbol){
	this->symbol = symbol;
}

void Moving::setpotterEaten(bool potterEaten){
	this->potterEaten = potterEaten;
}

void Moving::setmonsterOverDiamond(bool monsterOverDiamond){
	this->monsterOverDiamond = monsterOverDiamond;
}

void Moving::setmonsterOverScroll(bool monsterOverScroll){
	this->monsterOverScroll = monsterOverScroll;
}

//getters
int Moving::getX(){
	return this->possX;
}

int Moving::getY(){
	return this->possY;
}
		
bool Moving::getpotterEaten(){
	return this->potterEaten;
}
