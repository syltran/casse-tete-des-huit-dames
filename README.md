# Casse-tête des huit dames

**Auteurs :** Tran Sylvain, Thai Kevin

**Date :** 2022 (L2, semestre 4)

**Objectif :**  
Réaliser en C le jeu du casse-tête des huit dames avec la bibliothèque graphique `ncurses`.  
Ce mini-Projet/TP avait surtout pour but de manipuler et de se familiariser avec les opérations bit à bit.

**Principe du jeu :**  
Le principe est de réussir à placer huit dames sur un échiquier de 8x8 cases sans qu’aucune n’attaque une autre. Sachant qu'une dame attaque sur ses deux diagonales et sur toute sa ligne et sa colonne.

---

## Prérequis :
La bibliothèque graphique `ncurses`.  
Peut être installée avec la commande : `sudo apt-get install libncurses5-dev libncursesw5-dev`

## Usage :
Pour lancer le jeu, tapez :  
```
make
./Dames
```
Vous pouvez taper `make clean` pour nettoyer le projet.

**Comment jouer ? :**  
Pour savoir comment jouer, regardez la documentation utilisateur.

**Documentation Technique et Utilisateur :**  
Voir le fichier [rapport.pdf](https://github.com/syltran/casse-tete-des-huit-dames/blob/master/rapport.pdf)