#include "Position.h"
#include "Interface.h"

#include <ncurses.h>
#include <unistd.h>


int main(){
    Position pos; /* Position de l'échiquier, amenée à changer au fur et à mesure que le joueur place ses dames */
    Case c;
    int touche; /* touche pressée par le joueur */
    int nb_dame_place; /* nombre de dames correctement placée */

    pos = 0;
    c = 0;
    initialiser_tab_cases_attaquees();
    nb_dame_place = 0;

    initscr();
    cbreak(); /* permet d'éviter que l'action définit par une touche ne se repète lorsque l'on reste appuyé dessus */
    noecho(); /* permet de ne pas afficher la touche renvoyée par getch() */
    curs_set(FALSE); /* pour que le curseur ne soit pas affiché dans la fenêtre */
    nodelay(stdscr, TRUE); /* pour que getch() renvoie ERR si aucune touche n'est entrée */
    keypad(stdscr, TRUE); /* permet d'utiliser les touches du clavier */
    start_color();
    /* initialise des paires de couleurs */
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_BLACK, COLOR_RED);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
    init_pair(4, COLOR_BLACK, COLOR_YELLOW);


    while (nb_dame_place != 8){ /* tant qu'on n'a pas placé 8 dames correctement */
        afficher_interface(pos, c);

        touche = getch();
        deplacer(&c, touche);
        poser_dame(&pos, &c, &nb_dame_place, touche);
        usleep(10000);
    }
    
    afficher_gagnant();
    getch(); /* attente d'une touche quelconque pour quitter */
    endwin();
    return 0;
}