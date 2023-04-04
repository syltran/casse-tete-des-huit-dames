#include "Interface.h"

#include <stdio.h>
#include <ncurses.h>
#define DIM 8 /* Dimention d'un échiquier : 8 cases de côtés */


/* affiche l'échiquier */
void afficher_echiquier(){
    int i, j;

    /* affiche l'échiquier */
    for (i = 0; i < DIM; i++){
        for (j = 1; j <= DIM; j++){
            attron(COLOR_PAIR((i + j - 1) % 2 + 1));
            mvaddch(i, j, ' ');
            attroff(COLOR_PAIR((i + j - 1) % 2 + 1));
        }
    }

    attron(COLOR_PAIR(3));
    /* affiche les chiffres de 1 à 8 sur le côté gauche */
    for (i = 0; i < DIM; i++){
        mvaddch(i, 0, (56 - i)); /* 56 = code ASCII de 8 */
    }
    /* affiche les lettres de a à h en dessous */
    for (j = 1; j <= DIM; j++){
        mvaddch(DIM, j, (97 - 1 + j));
    }
    attroff(COLOR_PAIR(3));
}


/* affiche les dames de la position pos sur l'échiquier */
void afficher_dames(Position pos){
    Case c;
    int i, j;
    c = 0;

    for (i = DIM - 1; i >= 0; i--){
        for (j = 1; j <= DIM; j++){
            if (est_case_occupee(pos, c)){
                attron(COLOR_PAIR((i + j + 1) % 2 + 1));
                mvaddch(i, j, 'D');
                attroff(COLOR_PAIR((i + j + 1) % 2 + 1));
            }
            c++;
        }
    }
}


/* affiche le déplacement de la dame que le joueur essaye de poser */
void afficher_deplacement(Case c){
    Case tmp;
    int i, j;

    tmp = 0;
    for (i = DIM - 1; i >= 0; i--){
        for (j = 1; j <= DIM; j++){
            if (c == tmp){
                attron(COLOR_PAIR(4));
                mvaddch(i, j, 'D');
                attroff(COLOR_PAIR(4));
            }
            tmp++;
        }
    }
}


/* affiche l'interface du problème */
void afficher_interface(Position pos, Case c){
    afficher_echiquier();
    afficher_dames(pos);
    afficher_deplacement(c);
    refresh();
}

/* efface la ligne y */
void effacer_ligne(int y){
    int i;
    for (i = 0; i < COLS; i++){
        mvaddch(y, i, ' ');
    }
    refresh();
}

/* affiche un message indiquant au joueur qu'il a réussi */
void afficher_gagnant(){
    nodelay(stdscr, FALSE);
    mvprintw(DIM + 2, 0, "Bravo ! Vous avez trouvé une solution au problème");
    mvprintw(DIM + 3, 0, "Appuyer sur une touche quelconque pour quitter");
    refresh();
}



/* permet de se déplacer dans l'échiquier */
void deplacer(Case *c, int touche){

    switch(touche){
        case 'z': /* en haut */
        effacer_ligne(DIM + 1);
        if (*c <= 55){
            *c += 8;
        } break;

        case 'q': /* à gauche */
        effacer_ligne(DIM + 1);
        if ((*c % 8) != 0){
            *c -= 1; 
        } break;

        case 's': /* en bas */
        effacer_ligne(DIM + 1);
        if (*c >= 8){
            *c -= 8;
        } break;

        case 'd': /* à droite */
        effacer_ligne(DIM + 1);
        if ((*c % 8) != 7){
            *c += 1;
        } break;

        default : ;
    }
}


/* gère la pose des dames sur l'échiquier */
void poser_dame(Position *pos, Case *c, int *nb_dame_place, int touche){
    if (touche == '\n'){ /* touche entrée */
        /* si la case c de l'échiquier n'est pas déjà occupée par une dame */
        if (!est_case_occupee(*pos, *c)){
            /* on place une dame à la case c */
            placer_dame_position(&(*pos), *c);

            /* si l'ajout de cette dame entraîne des attaques mutuelles entre dames, on la supprime */
            if (!est_sans_attaque_mutuelle(*pos)){
                mvprintw(DIM + 1, 0, "Votre placement est illégal ! Réessayez");
                refresh();
                mettre_a_0(&(*pos), *c); /* on met la case c à '0' pour supprimer la dame */
            } else{
                *nb_dame_place += 1;
            }
            *c = 0;
        }
    }
}