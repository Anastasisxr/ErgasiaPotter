#include <iostream>
#include "Engine.h"
#include "Traal.h"
#include "Gnome.h"
#include "Potter.h"
#include "HiScore.h"
#include "Moving.h"

using namespace std;

// η main συνάρτηση του προγράμματος δημιουργεί ένα αντικειμενο Engine και εκτελεί
// την συνάρτηση για το διαβασμα του χάρτη και την εκκίνηση του παιχνιδιού

int main(int argc, char** argv)
{

	Engine eng;

	eng.readMap("map.txt");//διάβασμα του χάρτη απο αρχείο
	
	return 0;
}