#include "Position.h"

#include <stdio.h>


/* met un bit à '1' sur la case c de la position pos */
void mettre_a_1(Position *pos, Case c){
    *pos = *pos | (1ULL << c);
}

/* met un bit à '0' sur la case c de la position pos */
void mettre_a_0(Position *pos, Case c){
    *pos = *pos & (~(1ULL << c));
}


/* renvoie 1 si la case c de la position pos est occupée par une dame, 0 sinon */
int est_case_occupee(Position pos, Case c){
    return ((pos >> c) & 1);
}

/* place une dame sur la case c de le position pos (càd qu'on met un bit à '1' sur c) */
int placer_dame_position(Position *pos, Case c){
    if (c < 0 || c > 63){
        return 0;
    }

    mettre_a_1(&(*pos), c);
    return 1;
}

/* affiche la position pos sur le terminal */
void afficher_position(Position pos){
    int i, j;

    for (i = 56; i >= 0; i -= 8){
        for (j = 0; j < 8; j++){
            if (est_case_occupee(pos, (i + j))){
                printf("+");
            } else{
                printf(".");
            }
        }
        printf("\n");
    }
}



/* met des bits à '1' sur les cases situées sur la rangée de la dame en c */
void ligne(Position *pos, Case c){
    int i;
    int debut, fin;

    debut = c - (c % 8);
    fin = debut + 7;

    for (i = debut; i <= fin; i++){
        if (i != c){
            mettre_a_1(&(*pos), i);
        }
    }
}

/* met des bits à '1' sur les cases situées sur la colonne de la dame en c */
void colonne(Position *pos, Case c){
    int i;

    for (i = c % 8; i < 64; i += 8){
        if (i != c){
            mettre_a_1(&(*pos), i);
        }
    }
}

/* met des bits à '1' sur les cases situées sur la diagonale droite de la dame en c */
void diagonale_droite(Position *pos, Case c){
    int i;
    i = c;
    while(1){
        i -= 9;
        if (!((i + 9) % 8) || (i < 0)){
            break;
        }
        mettre_a_1(&(*pos), i);
    }
    
    i = c;
    while(1){
        i += 9;
        if ((((i - 9) % 8) == 7) || (i > 63)){
            break;
        }
        mettre_a_1(&(*pos), i);
    }
}

/* met des bits à '1' sur les cases situées sur la diagonale gauche de la dame en c */
void diagonale_gauche(Position *pos, Case c){
    int i;
    i = c;
    while(1){
        i -= 7;
        if ((((i + 7) % 8) == 7) || (i <= 0)){
            break;
        }
        mettre_a_1(&(*pos), i);
    }

    i = c;
    while(1){
        i += 7;
        if (!((i - 7) % 8) || (i > 63)){
            break;
        }
        mettre_a_1(&(*pos), i);
    }
}


/* met des bits à '1' sur les cases attaquées par la dame située sur la case c */
int calculer_cases_attaquees(Position *pos, Case c){
    Position lig, col, diag_g, diag_d;
    lig = 0; col = 0; diag_g = 0, diag_d = 0;

    if (c < 0 || c > 63){
        return 0;
    }
    ligne(&lig, c);
    colonne(&col, c);
    diagonale_gauche(&diag_g, c);
    diagonale_droite(&diag_d, c);

    *pos = lig | col | diag_g | diag_d;
    return 1;
}


/* initialise le tableau tab_cases_attaquees */
void initialiser_tab_cases_attaquees(){
    int i;
    for (i = 0; i < 64; i++){
        calculer_cases_attaquees(&tab_cases_attaquees[i], i);
    }
}


/* renvoie 1 si les dames de la position pos ne s'attaquent pas mutuellement, 0 sinon */
int est_sans_attaque_mutuelle(Position pos){
    int i;
    Position attaques;
    attaques = 0;

    for (i = 0; i < 64; i++){
        if (est_case_occupee(pos, i)){
            attaques = attaques | tab_cases_attaquees[i];
        }
    }

    /* teste si pos et attaques possèdent au moins un bit à '1' situé en un même indice */
    if (pos & attaques){
        return 0;
    }
    return 1;
}