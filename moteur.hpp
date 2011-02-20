#ifndef H_MOTEUR
#define H_MOTEUR

class Moteur;

#include <fstream>

#include "constants.hpp"
#include "menu.hpp"
#include "jeu.hpp"

class Moteur
{
	private:
		Menu * menu;
		Jeu *jeu;
		bool dansMenu;
	public:
		Moteur();
		~Moteur();

		void clic(int , int);
		void aff(SDL_Surface *screen);

		bool init();

		void initJeu();
		void setFonctionsJeu();
		void setFonctionsMenu();
		void echangeFonctions();
		
		void fin();
		void verif();
};

#endif
