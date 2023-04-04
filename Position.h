
#ifndef __POSITION__
#define __POSITION__

typedef enum{
    /* une "Case" représente une case de l'échiquier (il y a 64 cases). */
    H1 = 56, H2 = 57, H3 = 58, H4 = 59, H5 = 60, H6 = 61, H7 = 62, H8 = 63,
    G1 = 48, G2 = 49, G3 = 50, G4 = 51, G5 = 52, G6 = 53, G7 = 54, G8 = 55,
    F1 = 40, F2 = 41, F3 = 42, F4 = 43, F5 = 44, F6 = 45, F7 = 46, F8 = 47,
    E1 = 32, E2 = 33, E3 = 34, E4 = 35, E5 = 36, E6 = 37, E7 = 38, E8 = 39,
    D1 = 24, D2 = 25, D3 = 26, D4 = 27, D5 = 28, D6 = 29, D7 = 30, D8 = 31,
    C1 = 16, C2 = 17, C3 = 18, C4 = 19, C5 = 20, C6 = 21, C7 = 22, C8 = 23,
    B1 = 8, B2 = 9, B3 = 10, B4 = 11, B5 = 12, B6 = 13, B7 = 14, B8 = 15,
    A1 = 0, A2 = 1, A3 = 2, A4 = 3, A5 = 4, A6 = 5, A7 = 6, A8 = 7
} Case;

typedef unsigned long long Position;
/* une "Position" donne l'état de l'échiquier (c'est-à-dire la position de toutes les dames) à un instant donné */

static Position tab_cases_attaquees[64];
/* tab_cases_attaquees[i] donne les cases attaquées par une dame lorsqu'elle est placée à la case i. 
Si une case est attaquée, elle est mise à 1, 0 sinon. 
Voir le fichier exemple.png pour mieux comprendre */


void mettre_a_1(Position *pos, Case c);
void mettre_a_0(Position *pos, Case c);
int est_case_occupee(Position pos, Case c);
int placer_dame_position(Position *pos, Case c);
void afficher_position(Position pos);

void ligne(Position *pos, Case c);
void colonne(Position *pos, Case c);
void diagonale_droite(Position *pos, Case c);
void diagonale_gauche(Position *pos, Case c);
int calculer_cases_attaquees(Position *pos, Case c);

void initialiser_tab_cases_attaquees();
int est_sans_attaque_mutuelle(Position pos);

#endif