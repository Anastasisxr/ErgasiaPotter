#include "Engine.h"


void Engine::readMap(string mapFileLoc){

	string line;

	ifstream mapFile ("map.txt", ios::in);

	int j = 0;
		int i = 0;
	this->mapx = 0;
	this->mapy = 0;
	char temp;

	//διάβασε το αρχείο του χάρτη δύο φορές
	//μία για να βρέις τις διαστάσης και μία για να βάλεις τον χάρτη στον pointer
	if (mapFile.is_open()) 
	{
	     while(  getline (mapFile, line)){
	        this->mapy++;
	        this->mapx = line.length();
	              
	  }
	}

	mapFile.clear();
	mapFile.seekg(0);

	this->map = new char*[this->mapy];
	for(int i = 0; i<this->mapy ; i++)
	    map[i] = new char[this->mapx]; 

	for(i = 0; i<this->mapy; i++)
	    for(j = 0; j<this->mapx+1; j++){
	    	mapFile.get(temp);
	    	if(temp != '\n')
	    		this->map[i][j] = temp;
	    }

	mapFile.close(); 

	//βασικές συναρτήσεις για την ορθή λειτουργία του ncurses

	initscr();

	cbreak();
    noecho();
    keypad (stdscr, TRUE);
    curs_set(0);

	refresh();

	this->primaryScreen = newwin(mapy+8,mapx+8,3,3);

	box(this->primaryScreen,0,0);

	//εκτέλεση της συνάρτησης για την αρχική οθόνη του παίχνιδιού

	this->startScreen();
}


void Engine::printScreen(){

	int i,j, endGame;
	char playerName[10];

	//εύρεση του score για να εμφανίζεται στην οθόνη
	int gemsAndFlag = potter.getgemCount() * 10;
	
	if(potter.getflagGet() == true)
		gemsAndFlag = gemsAndFlag +100;
	string temp = "Score: " + to_string(gemsAndFlag);	
	const char* printScore = temp.c_str();	

	//εμφάνισε την κατάλλιλη οθόνη ανάλογα με την κατάσταση του παιχνιδιού
	if(gemsAndFlag != 200 && this->gnome.getpotterEaten() == false && this->traal.getpotterEaten() == false){
		for(i = 0; i<this->mapy; i++)
			for(j = 0; j<this->mapx; j++)
				mvwaddch(this->primaryScreen, i+3, j+4, this->map[i][j]);
				

		mvwaddstr(this->primaryScreen, i+5, j-6, printScore);
		mvwaddstr(this->primaryScreen, i+5, j-42, "Press ESC to Exit");
		wrefresh(this->primaryScreen);	

	}else if(this->gnome.getpotterEaten() == true || this->traal.getpotterEaten() == true){

		wclear(this->primaryScreen);
		this->gameLose(gemsAndFlag, printScore);	

	}else{

		wclear(this->primaryScreen);
		this->gameWin(gemsAndFlag);
	}

}


void Engine::setPrimaryScreen(){

	//αρχικοποίηση της οθόνης
	initscr();

	cbreak();
    noecho();
    intrflush (stdscr, FALSE);
    keypad (stdscr, TRUE);
    curs_set(0);

	refresh();

	this->primaryScreen = newwin(mapy+8,mapx+8,3,3);

	box(this->primaryScreen,0,0);

	wrefresh(this->primaryScreen);

	this->printScreen();
}


void Engine::closeScreen(){
	
	//κλείσιμο της οθόνης

	endwin();
	exit(0);
}


void Engine::initializeChars(){
	
	//αρχικοποίηση του παιχνιδιού
	
	//διάβασμα των scores απο το αρχείο
	score.readScores();

	//αρχικοποίηση των χαρακτήρων
	potter.setSymbol('P');
	potter.setgemCount(0);
	potter.setvalidMove(true);
	potter.setStaringPoss(this->mapy, this->mapx, this->map);
	traal.setSymbol('T');
	traal.setpotterEaten(false);
	traal.setmonsterOverDiamond(false);
	traal.setmonsterOverScroll(false);
	traal.setMapx(this->mapx);
	traal.setMapy(this->mapy);
	traal.setStaringPoss(this->mapy, this->mapx, this->map);
	gnome.setSymbol('G');
	gnome.setpotterEaten(false);
	gnome.setmonsterOverDiamond(false);
	gnome.setmonsterOverScroll(false);
	gnome.setMapx(this->mapx);
	gnome.setMapy(this->mapy);
	gnome.setStaringPoss(this->mapy, this->mapx, this->map);

}


void Engine::initializeGems(){

	//αρχικοποίηση των διαμαντιών
	int i,j;
	bool done = false;

	srand (time(NULL));

	do{
		i = rand() % ((this->mapx-1) + 1);
		j = rand() % ((this->mapy-1) + 1);

		if(this->map[j][i] == ' ')
		{
			this->map[j][i] = 'D';
			done = true;
		}

	}while(!done);

}


void Engine::gameStart(){
	
	//εκίνιση του παιχνιδιού
	int potterMove, monsterMove;
	int potterX,potterY;
	bool gemflag = false;
	bool done = false;
	int i,j;
	
	//δημιουργία δεύτερου πίνακα για την εύρεση κίνησης των τεράτων
	this->secondaryMap = new int*[this->mapy];
	for(i = 0; i<this->mapy ; i++)
    	secondaryMap[i] = new int[this->mapx]; 

	do{
		//μετακίνηση του χρήστη στην οθόνη
		while(1){
			potterMove = getch();
			if((potterMove == KEY_UP)||(potterMove == KEY_LEFT)||(potterMove == KEY_RIGHT)||(potterMove == KEY_DOWN))
			{
				this->map = potter.moveCharacter(potterMove, this->map);
				break;
			}
			if(potterMove == 27)
				break;
		}
		
		//κατάλλιλη σημπλήρωση του δεύτερου πίνακα
		for(i = 0; i<this->mapy ; i++)
			for(j = 0; j<this->mapx; j++)
				switch(this->map[i][j]){
				case '*':	
						this->secondaryMap[i][j] = -1;
						break;

				case ' ':	
						this->secondaryMap[i][j] = 0;
						break;

				case 'P':	
						this->secondaryMap[i][j] = -4;
						break;

				case 'D':	
						this->secondaryMap[i][j] =  0;
						break;
						
				case 'T':	
						this->secondaryMap[i][j] = -3;
						break;

				case 'G':	
						this->secondaryMap[i][j] = -2;
						break;	

				case 'S': 	
						this->secondaryMap[i][j] = 0;
						break;
				}

		//εάν ο χρήστης έκανε μία επιτρεπτή κίνηση τότε να μετακινηθούν και τα τέρατα
		if(potter.getvalidMove() == true){
			monsterMove = gnome.findShortestPath(this->secondaryMap, potter.getY(), potter.getX());

			this->map = gnome.moveCharacter(monsterMove, this->map);

			monsterMove = traal.findShortestPath(this->secondaryMap, potter.getY(), potter.getX());

			this->map = traal.moveCharacter(monsterMove, this->map);
		}

		//εάν ο χρήστης έχει πάρει 10 διαμάντια εμφάνισε το scroll στον χάρτη
		if(!gemflag)
			if(potter.getgemCount() == 10)
			{
				do{
				i = rand() % ((this->mapx-1) + 1);
				j = rand() % ((this->mapy-1) + 1);

				if(this->map[j][i] ==' ')
				{
					this->map[j][i] = 'S';
					done = true;
				}
				}while(!done);
				gemflag = true;
			}
		//κάλεσε την primaryScreen για την ανανέωση της οθόνης
		this->printScreen();

	}while(potterMove != 27);

	this->closeScreen();
	
}

Engine::~Engine() {
	
	for(int i=0; i<this->mapy ;i++)
    	delete[] this->secondaryMap[i];
	
	delete[] secondaryMap;

	for(int i=0; i<this->mapy ;i++)
    	delete[] this->map[i];
	
	delete[] map;

}


void Engine::gameWin(int gemsAndFlag){

	char endGame, tempLetter;
	string tempString;
	string tempName;
	
	box(this->primaryScreen, 0, 0);
	
	//εμφάνηση της οθόνης νίκης
	mvwaddstr(this->primaryScreen, this->mapy/6, (this->mapx/2)-10, "YOU ESCAPED THE MAZE!!!");
	mvwaddstr(this->primaryScreen, (this->mapy/2)-4, (this->mapx/2)-5, "SCORE BOARD");
	mvwaddstr(this->primaryScreen, (this->mapy/2)-3, (this->mapx/2)-7, "---------------");
	
	//εμφάνιση των ήδη υπάρχων score απο το αρχείο
	for(int i = 0; i<5; i++){
		int tempScore = score.getScores(i);
		tempString = score.getNames(i);
		tempString = tempString + "  ";
		tempString = tempString + to_string(tempScore);
		const char* tempPrint = tempString.c_str();

		mvwaddstr(this->primaryScreen, ((this->mapy/2)-2)+i,((this->mapx/2)-6), tempPrint);
	}

	mvwaddstr(this->primaryScreen, (this->mapy/2)+10, (this->mapx/2)-16, "TYPE YOUR NAME UP TO 10 CHARACTERS");
	mvwaddstr(this->primaryScreen, (this->mapy/2)+11, (this->mapx/2)-16, "AND PRESS ENTER: ");

	mvwaddstr(this->primaryScreen, this->mapy+4, this->mapx-42, "Press ESC to return");
	mvwaddstr(this->primaryScreen, this->mapy+5, this->mapx-42, "to the Starting Screen");

	wrefresh(this->primaryScreen);

	//διάβασμα του ονόματος του παίκτι
	for(int i = 0; i<10; i++){
		tempLetter = getch();
		if(tempLetter == 27 ){
			endGame = 27;
			break;
		}
		if(tempLetter == 10 ){
			break;
		}

		tempName += tempLetter;
		const char* tempPrint = tempName.c_str();
		mvwaddstr(this->primaryScreen, (this->mapy/2)+11, (this->mapx/2)+1, tempPrint);
		wrefresh(this->primaryScreen);
	}

	//εισαγωγή του score στην κλάση score για την κατάλληλη επεξεργασία
	if(endGame != 27){
		const char* tempPrint = tempName.c_str();
		score << tempPrint << gemsAndFlag;
	}
	
	while(endGame != 27){
		endGame = getch();
	};

	this->cleanMap();

	wclear(this->primaryScreen);
	box(this->primaryScreen, 0, 0);
	this->startScreen();

}

void Engine::gameLose(int gemsAndFlag, const char* printScore){

	char endGame, tempLetter;
	string tempString;
	string tempName;

	box(this->primaryScreen, 0, 0);

	//εμφάνηση της οθόνης ήττας
	mvwaddstr(this->primaryScreen, this->mapy/6, (this->mapx/2)-13, "YOU WHERE KILLED BY A MONSTER");
	mvwaddstr(this->primaryScreen, (this->mapy/2)-4, (this->mapx/2)-5, "SCORE BOARD");
	mvwaddstr(this->primaryScreen, (this->mapy/2)-3, (this->mapx/2)-7, "---------------");
	
	//εμφάνιση των ήδη υπάρχων score απο το αρχείο
	for(int i = 0; i<5; i++){
		int tempScore = score.getScores(i);
		tempString = score.getNames(i);
		tempString = tempString + "  ";
		tempString = tempString + to_string(tempScore);
		const char* tempPrint = tempString.c_str();

		mvwaddstr(this->primaryScreen, ((this->mapy/2)-2)+i,((this->mapx/2)-6), tempPrint);
	}

	mvwaddstr(this->primaryScreen, (this->mapy/2)+10, (this->mapx/2)-16, "TYPE YOUR NAME UP TO 10 CHARACTERS");
	mvwaddstr(this->primaryScreen, (this->mapy/2)+11, (this->mapx/2)-16, "AND PRESS ENTER: ");

	mvwaddstr(this->primaryScreen, this->mapy+4, this->mapx-42, "Press ESC to return");
	mvwaddstr(this->primaryScreen, this->mapy+5, this->mapx-42, "to the Starting Screen");
	mvwaddstr(this->primaryScreen, this->mapy+5, this->mapx-10, printScore);

	wrefresh(this->primaryScreen);

	//διάβασμα του ονόματος του παίκτι
	for(int i = 0; i<10; i++){
		tempLetter = getch();
		if(tempLetter == 27 ){
			endGame = 27;
			break;
		}
		if(tempLetter == 10 ){
			break;
		}

		tempName += tempLetter;
		const char* tempPrint = tempName.c_str();
		mvwaddstr(this->primaryScreen, (this->mapy/2)+11, (this->mapx/2)+1, tempPrint);
		wrefresh(this->primaryScreen);
	}

	//εισαγωγή του score στην κλάση score για την κατάλληλη επεξεργασία
	if(endGame != 27){
		const char* tempPrint = tempName.c_str();
		score << tempPrint << gemsAndFlag;
	}
	
	while(endGame != 27){
		endGame = getch();
	};

	this->cleanMap();

	wclear(this->primaryScreen);
	box(this->primaryScreen, 0, 0);
	this->startScreen();
}


void Engine::startScreen(){

	initializeChars();//αρχικοποίηση των χαρακτήρων

	for(int i = 0; i<10 ; i++) // αρχικοποίηση των διαμαντιών στο χάρτη
		initializeGems();

	//σχεδίαση ενός γραφικού ώς αρχική οθόνη του παιχνιδιού

	mvwaddstr(this->primaryScreen, (this->mapy/2)-6, (this->mapx/2)-6, "Mpampis Potteridis");
	mvwaddstr(this->primaryScreen, (this->mapy/2)-5, (this->mapx/2)-8, "And the Last Challenge");

	mvwaddstr(this->primaryScreen, (this->mapy/2)-2, (this->mapx/2)-6, "       ______");
	mvwaddstr(this->primaryScreen, (this->mapy/2)-1, (this->mapx/2)-6, "    .-,;='';_),-.");
	mvwaddstr(this->primaryScreen, (this->mapy/2), (this->mapx/2)-6, "     \\_\\(),()/_/");
	mvwaddstr(this->primaryScreen, (this->mapy/2)+1, (this->mapx/2)-6, "       (,___,)");
	mvwaddstr(this->primaryScreen, (this->mapy/2)+2, (this->mapx/2)-6, "      ,-/`~`\\-,___");
	mvwaddstr(this->primaryScreen, (this->mapy/2)+3, (this->mapx/2)-6, "     / /).:.('--._)");
	mvwaddstr(this->primaryScreen, (this->mapy/2)+4, (this->mapx/2)-6, "    {_[ (_,_)");
	mvwaddstr(this->primaryScreen, (this->mapy/2)+5, (this->mapx/2)-6, "        | Y |");
	mvwaddstr(this->primaryScreen, (this->mapy/2)+6, (this->mapx/2)-6, "       /  |  \\");
	mvwaddstr(this->primaryScreen, (this->mapy/2)+7, (this->mapx/2)-6, "       \"\"\" \"\"\"");
	mvwaddstr(this->primaryScreen, (this->mapy/2)+10, (this->mapx/2)-9, "Press ENTER to START the game");
	mvwaddstr(this->primaryScreen, (this->mapy/2)+11, (this->mapx/2)-6, "or ESC to EXIT the game");


	wrefresh(this->primaryScreen);

	// Με επιλογή του χρήση ξεκίνα το παιχνίδι ή κλείσε το πρόγραμμα

	int choice;

	while(1)
	{
	
		choice = wgetch(this->primaryScreen);

		if(choice == 10)
			break;

		if(choice == 27)
			this->closeScreen();
	}

	wclear(this->primaryScreen);
	box(this->primaryScreen, 0, 0);
	this->printScreen();
	wrefresh(this->primaryScreen);
	gameStart();
	
}

void Engine::cleanMap(){
	//καθαρισμός του χάρτη

	for(int i = 0; i<this->mapy ; i++)
		for(int j = 0; j<this->mapx; j++)
			if(this->map[i][j] != '*')
				this->map[i][j] = ' ';
}