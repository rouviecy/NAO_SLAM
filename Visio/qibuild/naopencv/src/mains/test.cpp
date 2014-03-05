#include "../NAO_flux.h"

using namespace std;

int main(){

	char key = 'a';					// clef de contrôle du programme
	NAO_flux flux("127.0.0.1", 1, 40, 3, 1);	// initialisation du flux NAO

	// boucle d'exécution : appuyer sur 'q' pour quitter
	while(key != 'q'){
		key = flux.Get_key();
		// mettre à jour les images du flux
		flux.Update();
	}

	return 0;

}
