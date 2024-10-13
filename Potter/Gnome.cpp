#include "Gnome.h"
#include "Moving.h"

Gnome::Gnome():Moving(){

}

//η εύρεση του καλήτερου μονοπατιού προς τον παίχτη
int Gnome::findShortestPath(int** map, int potterY, int potterX){

	bool moveFound = false;
	int i,j, counter;
	int tempx, tempy, min = 9999;
	int move = 1;

	//αρχικοποίηση των πρώτων αριθμών τριγυρω απο τον παίκτη
	if(map[potterY][potterX + 1] == 0)
		map[potterY][potterX + 1] = 1;

	if(map[potterY][potterX - 1] >= 0)
		map[potterY][potterX - 1] = 1;

	if(map[potterY + 1][potterX] >= 0)
		map[potterY + 1][potterX] = 1;

	if(map[potterY - 1][potterX] >= 0)
		map[potterY - 1][potterX] = 1;

	counter = 1;

	//έλεγχος σε περίπτωση που το τέρας είναι δίπλα απο τον παίκτη
	//αν ναι κάνε return προς την κατάλληλη κατεύθυνση
	if(map[this->possY][this->possX+1] == -4){
		move = 1; //'Right'
		return move;

	}else if(map[this->possY][this->possX-1] == -4){
		move = 2; //'Left'
		return move;

	}else if(map[this->possY+1][this->possX] == -4){
		move = 3; //'Up'
		return move;

	}else if(map[this->possY-1][this->possX] == -4){
		move = 4; //'Down'
		return move;
	}

	//συμπλήρωμα των αριθμών μέχρι να φτάσει στο τέρας
	while(!moveFound){
	for(i = 0; i<this->mapy; i++)
		for(j = 0; j<this->mapx; j++)
			if(counter == map[i][j])
			{
				if(map[i][j+1] == -2)
					moveFound = true;
				else if(map[i][j+1] == 0)
					map[i][j+1] = counter+1;

				if(map[i][j-1] == -2)
					moveFound = true;
				else if(map[i][j-1] == 0)
					map[i][j-1] = counter+1;

				if(map[i+1][j] == -2)
					moveFound = true;
				else if(map[i+1][j] == 0)
					map[i+1][j] = counter+1;

				if(map[i-1][j] == -2)
					moveFound = true;
				else if(map[i-1][j] == 0)
					map[i-1][j] = counter+1;
			}		
		
	counter++;
	}

	//επιλογή του καλύτερου μονοπατιόυ και return
	if(map[this->possY][this->possX+1] > 0 && min > map[this->possY][this->possX+1])
	{
		move = 1; //'Right'
		min = map[this->possY][this->possX+1];
	}

	if(map[this->possY][this->possX-1] > 0 && min > map[this->possY][this->possX-1])
	{
		move = 2; //'Left'
		min = map[this->possY][this->possX-1];
	}

	if(map[this->possY+1][this->possX] > 0 && min > map[this->possY+1][this->possX])
	{
		move = 3; //'Up'
		min = map[this->possY+1][this->possX];
	}

	if(map[this->possY-1][this->possX] > 0 && min > map[this->possY-1][this->possX])
	{
		move = 4; //'Down'
		min = map[this->possY-1][this->possX];
	}

	return move;

}

char** Gnome::moveCharacter(int gnomeMove, char** map){

	int gnomeX, gnomeY;

	gnomeX = this->possX;
	gnomeY = this->possY;

	//flags για τη περίπτωση που το τέρας είναι επάνω σε διαμάντη ή το scroll
	if(monsterOverDiamond == true){
		map[this->possY][this->possX] = 'D';
		monsterOverDiamond = false;
	}

	if(monsterOverScroll == true){
		map[this->possY][this->possX] = 'S';
		monsterOverScroll = false;
	}

	//επιλογή της κατεύθυνσης τη κίνησης
	switch(gnomeMove)
	{
		case 1 : gnomeX++; break;
		case 2 : gnomeX--; break;
		case 3 : gnomeY++; break;
		case 4 : gnomeY--; break;
	}

	if(map[gnomeY][gnomeX] == 'T'){
		return map;
	}
	//έλεγχος στη περίπτωση που το τέρας πάει επάνω στον παίκτη
	if(map[gnomeY][gnomeX] == 'P'){
		potterEaten = true;
		return map;
	}
	
	//έλεγχος στη περίπτωση που το τέρας πάει επάνω σε διαμάντη
	if(map[gnomeY][gnomeX] == 'D'){
		monsterOverDiamond = true;
	}

	//έλεγχος στη περίπτωση που το τέρας πάει επάνω σε scroll
	if(map[gnomeY][gnomeX] == 'S'){
		monsterOverScroll = true;
	}

	//μετακίνιση του τέρατος στην επόμενη θέση και κατάλληλη διαχείριση
	//της προιγούμενης θέσης
	if(map[this->possY][this->possX] == 'G')
		map[this->possY][this->possX] = ' ';

	map[gnomeY][gnomeX] = 'G';
	this->possX = gnomeX;
	this->possY = gnomeY;


	return map;
}