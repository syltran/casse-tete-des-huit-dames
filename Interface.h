
#ifndef __INTERFACE__
#define __INTERFACE__

#include "Position.h"


void afficher_echiquier();
void afficher_dames(Position pos);
void afficher_deplacement(Case c);
void afficher_interface(Position pos, Case c);

void effacer_ligne(int y);
void afficher_gagnant();

void deplacer(Case *c, int touche);
void poser_dame(Position *pos, Case *c, int *nb_dame_place, int touche);

#endif