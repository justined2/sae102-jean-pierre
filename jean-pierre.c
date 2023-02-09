/**
 * @file    jean-pierre.c
 * @brief   Programme qui donne vie à Jean-Pierre
 * @author  Justine Verger, 1D2
 * @version 1.0
 * @date    décembre 2022 -janvier 2023
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

/* CONSTANTES */
#define NB_LIGNES 6
#define NB_COLONNES 7
#define PION_A 'X'
#define PION_B 'O'
#define VIDE ' '
#define INCONNU ' '

/* TYPES */
typedef int Grille[NB_LIGNES][NB_COLONNES];
typedef int Tab7[NB_COLONNES];                                                  // AJOUT ##########

/****************************/
/* PROTOTYPES DES FONCTIONS */
/****************************/
    // Programme principal
void initGrille(Grille laGrille);
void afficher(Grille laGrille, char pion);
bool grillePleine(Grille laGrille);
void faireJouerA(Grille laGrille, char pion, int * ligne, int * colonne);
void faireJouerB(Grille laGrille, char pion, int * ligne, int * colonne);
int choisirColonne(Grille laGrille);
int chercherLigne(Grille laGrille, int colonne);
bool estVainqueur(Grille laGrille, int ligne, int colonne);
void finDePartie(char vainqueur);
    // stratégies basiques -- séance 1 
int choisirColonneStrategie1(Grille laGrille);
int choisirColonneStrategie2(Grille laGrille);
int choisirColonneStrategie3(Grille laGrille);
int choisirColonneStrategie4(Grille laGrille);
    // Jean-Pierre
int choisirColonneStrateJP(Grille laGrille);                 // AJOUT ##########
int joueAuMilieu(Grille laGrille);
int deuxiemeTourJP(Grille laGrille);
bool verifHauteurSol(Grille laGrille, int l, int c);
int chercheHauteurLigne(Grille laGrille);
int rechercheAlign3(Grille laGrille, char pion);
int rechercheAlign3Sep(Grille laGrille, char pion);
void rechercheAlign2encadre(Grille laGrille, Tab7 t_coupsPossibles, char pion);
void rechercheAlign2(Grille laGrille, Tab7 t_coupsPossibles, char pion);
void eviterBadMove(Grille laGrille, Tab7 t_colonnesInterdites, char pion);
void comparePossibilites(Grille laGrille, Tab7 t_colonnesInterdites, Tab7 t_coupsPossibles, char pionJP, char pionAdv);
bool verifierCoupsPossiblesPresents(Grille laGrille, Tab7 t_coupsPossibles);
int colonneAuHasardParmi(Grille laGrille, Tab7 t_coupsPossibles);
int choisirColonneAleatoire(Grille laGrille);

/***********************/
/* PROGRAMME PRINCIPAL */
/***********************/
int main()
{

    srand(time(NULL));
    Grille laGrille;
    char vainqueur=INCONNU;
    int ligne, colonne;
    int cpt=0;

    // for (int i = 0; i <= 500; i++)
    // {
        vainqueur=INCONNU;
        // compteur_tour = 0; //////////////////////////////////////

        initGrille(laGrille);
        afficher(laGrille, PION_A);
        while (vainqueur==INCONNU && !grillePleine(laGrille))// && (i != 500))
        {
            faireJouerA(laGrille, PION_A, &ligne, &colonne);
            // compteur_tour++;                                                        // AJOUT ##########
            afficher(laGrille, PION_B);
            if (estVainqueur(laGrille, ligne, colonne) ){
                vainqueur = PION_A;
                // printf("tour %d", cpt);
            } else if (!grillePleine(laGrille)){
                faireJouerB(laGrille, PION_B, &ligne, &colonne);
                // compteur_tour++;                                                    // AJOUT ##########
                afficher(laGrille, PION_A);
                if (estVainqueur(laGrille, ligne, colonne)){
                    vainqueur = PION_B;
                    // cpt = cpt + 1;
                }
            }       
        // }
        // finDePartie(vainqueur);
    }
    // printf("JP a gagné %d fois sur 500. ", cpt);  
    system(EXIT_SUCCESS); 
}

/************************************/
/* FONCTIONS DU PROGRAMME PRINCIPAL */
/************************************/

void initGrille(Grille laGrille){
    int l, c;
    for (l=0 ; l<NB_LIGNES ; l++){
        for (c=0 ; c<NB_COLONNES ; c++){
            laGrille[l][c] = VIDE;
        }
    }
}

void afficher(Grille laGrille, char pion){
    int l, c;
    system("clear");
    printf("\t");
    printf("  %c\n", pion);
    printf("\t");
    for (c=0; c<NB_COLONNES ; c++){
        printf("----");
    }
    printf("-\n");
    for (l=0 ; l<NB_LIGNES ; l++){
        printf("\t");
        for (c=0; c<NB_COLONNES ; c++){
            printf("| %c ", laGrille[l][c]);
        }
        printf("|\n");
        printf("\t");
        for (c=0; c<NB_COLONNES ; c++){
            printf("----");
        }
        printf("-\n");
    }
    printf("\t");
    for (c=0; c<NB_COLONNES ; c++){
            printf("  %d ",c);
    }
    printf("\n\n");

}

bool grillePleine(Grille laGrille){
    bool pleine = true;
    int c = 0;
    while (pleine && c<NB_COLONNES){
        if (laGrille[0][c] == VIDE){
            pleine = false;
        }
        c++;
    }
    return pleine;
}

void faireJouerA(Grille laGrille, char pion, int * ligne, int * colonne){
   *ligne = -1;
    do {
        *colonne = choisirColonne(laGrille);
        *ligne = chercherLigne(laGrille, *colonne);
    }while (*ligne==-1);
    laGrille[*ligne][*colonne] = pion;
}

void faireJouerB(Grille laGrille, char pion, int * ligne, int * colonne){
   *ligne = -1;
    do {
        *colonne = choisirColonneStrateJP(laGrille);
        *ligne = chercherLigne(laGrille, *colonne);
    }while (*ligne==-1);
    laGrille[*ligne][*colonne] = pion;
}

// Laisse jouer l'Homme 💪
int choisirColonne(Grille laGrille){
    int col;
    
    do{
        printf("Numero de colonne ? ");
        scanf("%d", &col);
    } while (col<0 ||col>6);
    return col;
}

int chercherLigne(Grille laGrille, int col){
    int ligne = -1;

    while (ligne<NB_LIGNES-1 && laGrille[ligne+1][col]==VIDE){
        ligne++;
    }
    return ligne;
}

bool estVainqueur(Grille laGrille, int lig, int col){
    // consiste à regarder si une ligne de 4 pions s'est formé autour du pion qui vient de tomber en (lig, col)
    char lePion = laGrille[lig][col];
    int cpt,i,j;

    // regarder la verticale, en comptant le nombre de pions au Sud (inutile de regarder au Nord du pion qui vient de tomber)
    i = lig;
    cpt = 0;
    while (i<NB_LIGNES && laGrille[i][col]==lePion){
        cpt++;
        i++;
    }
    if (cpt>=4){
        return true;
    }
    // regarder l'horizontale, en comptant le nombre de pions Ã  l'Est et Ã  l'Ouest
    j = col;
    cpt = 0;
    // on regarde Ã  l'est
    while (j>=0 && laGrille[lig][j]==lePion){
        cpt++;
        j--;
    }
    j = col+1;
    // on regarde Ã  l'ouest
    while (j<NB_COLONNES && laGrille[lig][j]==lePion){
        cpt++;
        j++;
    }
    if (cpt>=4 ){
        return true;
    }
    // regarder la diagonale descendante, en comptant le nombre de pions au Nord Ouest et au Sud Est
    i = lig;
    j = col;
    cpt = 0;
    // on regarde au Nord Ouest
    while (j>=0 && i>=0 && laGrille[i][j]==lePion){
        cpt++;
        i--;
        j--;
    }
    i = lig+1;
    j = col+1;
    // on regarde au Sud Est
    while (i<NB_LIGNES && j<NB_COLONNES && laGrille[i][j]==lePion){
        cpt++;
        i++;
        j++;
    }
    if (cpt>=4 ){
        return true;
    }
    // regarder la diagonale descendante, en comptant le nombre de pions au Nord Est et au Sud Ouest
    i = lig;
    j = col;
    cpt = 0;
    // on regarde au Nord Est
    while (j<NB_COLONNES && i>=0 && laGrille[i][j]==lePion){
        cpt++;
        i--;
        j++;
    }
    i = lig+1;
    j = col-1;
    // on regarde au Sud Ouest
    while (i<NB_LIGNES && j>=0 && laGrille[i][j]==lePion){
        cpt++;
        i++;
        j--;
    }
    if (cpt>=4 ){
        return true;
    }
    return false;
}

void finDePartie(char vainqueur){
    if (vainqueur != INCONNU){
        printf("Joueur %c vainqueur\n", vainqueur);
    } else {
        printf("MATCH NUL");
    }
}


//***********************************************
// FONCTION PRINCIPALE DE CE SACRÉ JEAN-PIERRE 👨🏻
//***********************************************
int choisirColonneStrateJP(Grille laGrille)
{
    Tab7 t_colonnesInterdites = {-1, -1, -1, -1, -1, -1, -1};   // tableau recensant les numéros des colonnes dans lesquelles ne pas poser de pièces
    Tab7 t_coupsPossibles = {-1, -1, -1, -1, -1, -1, -1};       // tableau rencensant les numéros des colonnes dans lesquelles un coup est possible
    char pionJP = INCONNU;
    char pionAdv = INCONNU;
    int colonne = 0;
    int compteur_tour = 0;

    for (int c = 0; c < NB_COLONNES; c++)
    {
        if (laGrille[NB_LIGNES - 1][c] != VIDE)
        {
            compteur_tour = compteur_tour + 1;
        }
    }

    // Attribution des pions en fonction du tour des joueurs :
    if (compteur_tour % 2 == 0){                    // Cas où JP commence
        pionJP = PION_A;                            // Il joue les pions A (= X)
        pionAdv = PION_B;                           // Son adversaire joue les pions B (= O)
    }
    else if (compteur_tour % 2 == 1){               // Cas où JP ne commence pas
        pionJP = PION_B;                            // Il joue les pions B (= O)
        pionAdv = PION_A;                           // Son adversaire joue les pions A (= X)
    }

    // Cas particulier du premier tour : (JP a commencé)
    if (compteur_tour == 0){
        colonne = joueAuMilieu(laGrille);
    }
    // Cas particulier du deuxième tour : (JP n'a pas commencé)
    else if (compteur_tour == 1){
        colonne = deuxiemeTourJP(laGrille);
    }
    // Aux tours suivants
    else if (compteur_tour > 1){
        if (rechercheAlign3(laGrille, pionJP) != -1){                                                       // si une victoire potentielle a été détectée (alignement de 3),
            colonne = rechercheAlign3(laGrille, pionJP);                                                        // priorité à la victoire
        }
        else if (rechercheAlign3Sep(laGrille, pionJP) != -1){                                               // si une victoire potentielle a été détectée (alignement "caché" de 3),
            colonne = rechercheAlign3Sep(laGrille, pionJP);                                                     // priorité à la victoire
        }
        else if (rechercheAlign3(laGrille, pionJP) == -1){                                                  // si aucune victoire potentielle n'a été détectée,
            if (rechercheAlign3(laGrille, pionAdv) != -1){                                                      // si un contre est possible, 
                colonne = rechercheAlign3(laGrille, pionAdv);                                                       // JP contre
            }
            else if (rechercheAlign3Sep(laGrille, pionAdv) != -1){                                              // si un contre est possible (alignement "caché" de 3), 
                colonne = rechercheAlign3Sep(laGrille, pionAdv);                                                    // JP contre
            }
            else if (rechercheAlign3(laGrille, pionAdv) == -1){                                                 // si aucun contre n'est à faire,
                eviterBadMove(laGrille, t_colonnesInterdites, pionAdv);
                rechercheAlign2encadre(laGrille, t_coupsPossibles, pionAdv);
                comparePossibilites(laGrille, t_colonnesInterdites, t_coupsPossibles, pionJP, pionAdv);             // on vérifie qu'un indice de colonne n'est pas présent à la fois dans les coups possibles et interdits
                if (verifierCoupsPossiblesPresents(laGrille, t_coupsPossibles)){                                    // on regarde si un ou des coup/s est/sont suggéré/s
                    colonne = colonneAuHasardParmi(laGrille, t_coupsPossibles);                                         // si oui, on tire au hasard parmi ces coups
                }
                else if (!verifierCoupsPossiblesPresents(laGrille, t_coupsPossibles)){                              // si on n'a pas trouvé d'alignements de 2 (encadré par des cellules vides) (le tableau est rempli de -1)
                    rechercheAlign2(laGrille, t_coupsPossibles, pionJP);                                                // on cherche un alignement de 2 "classique" pour JP
                    rechercheAlign2(laGrille, t_coupsPossibles, pionAdv);                                               // on cherche un alignement de 2 "classique" pour l'adversaire
                    comparePossibilites(laGrille, t_colonnesInterdites, t_coupsPossibles, pionJP, pionAdv);             // on vérifie qu'un indice de colonne n'est pas présent à la fois dans les coups possibles et interdits
                    if (verifierCoupsPossiblesPresents(laGrille, t_coupsPossibles)){                                    // on regarde si un ou des coup/s est/sont suggéré/s
                        colonne = colonneAuHasardParmi(laGrille, t_coupsPossibles);                                         // si oui, on tire au hasard parmi ces coups
                    }
                    else if (!verifierCoupsPossiblesPresents(laGrille, t_coupsPossibles)){                          // si pas de coups possibles de suggérés
                        colonne = choisirColonneAleatoire(laGrille);                                                // JP remet son destin entre les mains du hasard 😈
                    }
                }
            }
        }
    }
    return colonne;
}

// Place le pion au milieu de la grille
int joueAuMilieu(Grille laGrille)
{    
    int colonne = NB_COLONNES/2;

    return colonne;
}

// Fait jouer JP au deuxième tour (encercle l'ennemi)
int deuxiemeTourJP(Grille laGrille)
{
    int colonne = 0;
    int c = 0;
    int arretBoucle = 0;
    int positionPionAdverse = 0;    // position colonne du pion adverse
    int aleatoire = rand()%3;

    for (c = 0; c < NB_COLONNES; c++)           // on parcourt les colonnes une par une
    {
        if ((laGrille[NB_LIGNES - 1][c] != VIDE) && (arretBoucle == 0)) // seulement dans la ligne du bas (indice 5)
        {
            positionPionAdverse = c;            // pour trouver où le pion adverse a été placé
            arretBoucle = 1;                              // on arrête quand on a trouvé
        }
    }
    if ((positionPionAdverse != 0) && (positionPionAdverse != NB_COLONNES-1))   // si le pion adverse n'a pas été placé dans une des deux colonnes du bord
    {
        aleatoire = rand()%2;                       // on fait un tirage aléatoire entre 0 et 1 [CHANGEMENT PAR RAPPORT À LA STRATÉGIE INITIALE : JP pose seulement sur les côtés, pas sur le dessus]
        if (aleatoire == 0)                         // si jamais on tire 0
        {
            aleatoire = -1;                         // on remplace par -1
        } 
        colonne = positionPionAdverse + aleatoire;  // on additionne à la position du pion adverse le numéro aléatoire pour positionner notre pion au hasard autour
    }
    else if (positionPionAdverse == 0)              // si le joueur adverse a placé son pion dans la première colonne
    {
        aleatoire = rand()%2;                       // on fait un tirage aléatoire entre 0 et 1
        colonne = positionPionAdverse + aleatoire; 
    }
    else // if (positionPionAdverse == NB_COLONNES-1)  // si le joueur adverse a placé son pion dans la dernière colonne
    {
        aleatoire = rand()%2;                       // on fait un tirage aléatoire entre 0 et 1
        if (aleatoire == 1)                         // si on tire 1
        {
            aleatoire = -1;                         // on remplace par -1
        }
        colonne = positionPionAdverse + aleatoire;
    }

    return colonne;
}

// Vérifie si la case du dessous contient une pièce ou s'il s'agit de la dernière ligne (bas de la grille), pour être sûre de pouvoir y poser un pion (sans qu'il ne tombe plus bas)
bool verifHauteurSol(Grille laGrille, int l, int c)
{
    bool placementPossible = false;

    if ((l == NB_LIGNES - 1) || (laGrille[l + 1][c] != VIDE)) // si on se trouve sur la ligne du bas de la grille ou que la case du dessous est occupée
    {
        placementPossible = true;
    }
    return placementPossible;
}

// Détermine la hauteur de ligne atteinte par les pièces empilées dans la grille
int chercheHauteurLigne(Grille laGrille)
{
    int hauteurLigne = 0; // numéro de la ligne du plus haut jeton posé (par défaut, la ligne du haut)
    int l;

    for (l = 0; l < NB_LIGNES ; l++)    
    {
        if ((laGrille[l][0] == VIDE) && (laGrille[l][1] == VIDE) && (laGrille[l][2] == VIDE) && (laGrille[l][3] == VIDE) && (laGrille[l][4] == VIDE) && (laGrille[l][5] == VIDE) && (laGrille[l][6] == VIDE))
        {
            hauteurLigne = l ;
        }
    }
    return hauteurLigne;
}

// Vérifie si un alignement de trois pièces n'est pas possible
int rechercheAlign3(Grille laGrille, char pion)
{   
    int colonne = -1;
    int ligne = -1; //////////////////////
    int l, c;
    int hauteurLigne = chercheHauteurLigne(laGrille);
    bool hauteur; //////////////////////

    // alignement horizontal ↔️
    for (l = (NB_LIGNES - 1) ; l >= hauteurLigne ; l--)
    {
        //  vers la droite ➡️
        for (c = 0 ; c <= NB_COLONNES/2 ; c++)
        {
            hauteur = verifHauteurSol(laGrille, l, c);
            if ((laGrille[l][c] == VIDE) && (hauteur == true)) /////////////////////////
            {
                if ((laGrille[l][c + 1] == pion) && (laGrille[l][c + 2] == pion) && (laGrille[l][c + 3] == pion))
                {
                    colonne = c;
                    ligne = l;
                }
            }
        }
        // vers la gauche ⬅️
        for (c = NB_COLONNES - 1 ; c >= NB_COLONNES/2 ; c--)
        {
            hauteur = verifHauteurSol(laGrille, l, c);
            if ((laGrille[l][c] == VIDE) && (hauteur == true)) ////////////////////////
            {
                if ((laGrille[l][c - 1] == pion) && (laGrille[l][c - 2] == pion) && (laGrille[l][c - 3] == pion))
                {
                    colonne = c;
                    ligne = l;
                }
            }
        }
    }
    // alignement vertical ↕️
    for (c = 0 ; c < NB_COLONNES ; c++)
    {
        if (hauteurLigne <= NB_LIGNES/2)
        {
            for (l = NB_LIGNES/2 - 1 ; l >= 0 ; l--)
            {
                if (laGrille[l][c] == VIDE)
                {
                    if ((laGrille[l + 1][c] == pion) && (laGrille[l + 2][c] == pion) && (laGrille[l + 3][c] == pion))
                    {
                        colonne = c;
                        ligne = l;
                    }
                }
            }
        } 
    }
    // alignement diagonal 
    for (l = (NB_LIGNES - 1) ; l >= NB_LIGNES/2 ; l--)
    {
        // vers le nord-est ↗️
        for (c = 0 ; c <= NB_COLONNES/2 ; c++)
        {
            if ((laGrille[l][c] == VIDE) && (verifHauteurSol(laGrille, l, c)))
            {
                if ((laGrille[l - 1][c + 1] == pion) && (laGrille[l - 2][c + 2] == pion) && (laGrille[l - 3][c + 3] == pion))
                {
                    colonne = c;
                    ligne = l;
                }
            }
        }
        // vers le nord-ouest ↖️
        for (c = NB_COLONNES - 1 ; c >= NB_COLONNES/2 ; c--)
        {
            if ((laGrille[l][c] == VIDE) && (verifHauteurSol(laGrille, l, c)))
            {
                if ((laGrille[l - 1][c - 1] == pion) && (laGrille[l - 2][c - 2] == pion) && (laGrille[l - 3][c - 3] == pion))
                {
                    colonne = c;
                    ligne = l;
                }
            }
        }
    } 
    for (l = 0 ; l <= NB_LIGNES/2 - 1; l++)
    {
        // vers le sud-est ↘️
        for (c = 0 ; c <= NB_COLONNES/2 ; c++)
        {
            if ((laGrille[l][c] == VIDE) && (verifHauteurSol(laGrille, l, c)))
            {
                if ((laGrille[l + 1][c + 1] == pion) && (laGrille[l + 2][c + 2] == pion) && (laGrille[l + 3][c + 3] == pion))
                {
                    colonne = c;
                    ligne = l;
                }
            }
        }
        // vers le sud-ouest ↙️
        for (c = NB_COLONNES - 1 ; c >= NB_COLONNES/2 ; c--)
        {
            if ((laGrille[l][c] == VIDE) && (verifHauteurSol(laGrille, l, c)))
            {
                if ((laGrille[l + 1][c - 1] == pion) && (laGrille[l + 2][c - 2] == pion) && (laGrille[l + 3][c - 3] == pion))
                {
                    colonne = c;
                    ligne = l;
                }
            }
        }
    }
    if (chercherLigne(laGrille, colonne) == ligne){
        // printf("ca marche connard ");
        return colonne; 
    }
    else
    {
    //     printf("de la merde ce JAYPEE ");
        return -1;
    }
}

// Vérifie si un alignement de trois pièces "caché" (trois pièces séparées par une case vide) n'est pas possible
int rechercheAlign3Sep(Grille laGrille, char pion)
{
    int colonne = -1;
    int ligne = -1;
    int l, c;
    int hauteurLigne = chercheHauteurLigne(laGrille);

    // alignement horizontal caché
    for (l = (NB_LIGNES - 1) ; l >= hauteurLigne ; l--)
    {
        for (c = 1 ; c < NB_COLONNES ; c++)
        {
            if ((laGrille[l][c] == VIDE) && (verifHauteurSol(laGrille, l, c)))
            {
                if (((laGrille[l][c - 1] == pion) && (laGrille[l][c + 1] == pion) && (laGrille[l][c + 2] == pion)) 
                || ((laGrille[l][c - 2] == pion) && (laGrille[l][c - 1] == pion) && (laGrille[l][c + 1] == pion)))
                {
                    colonne = c;
                    ligne = l;
                }
            }
        }
    }
    // alignement diagonal caché
    for (l = (NB_LIGNES - 2) ; l >= NB_LIGNES/2 ; l--)
    {
        // vers le nord-est ↗️
        for (c = 1 ; c <= NB_COLONNES-1 ; c++)
        {
            if ((laGrille[l][c] == VIDE) && (verifHauteurSol(laGrille, l, c)))
            {
                if (((laGrille[l + 1][c - 1] == pion) && (laGrille[l - 1][c + 1] == pion) && (laGrille[l - 2][c + 2] == pion)) 
                || ((laGrille[l + 2][c - 2] == pion) && (laGrille[l + 1][c - 1] == pion) && (laGrille[l - 1][c + 1] == pion)))
                {
                    colonne = c;
                    ligne = l;
                }
            }
        }
        // vers le nord-ouest ↖️
        for (c = (NB_COLONNES - 2) ; c >= 1 ; c--)
        {
            if ((laGrille[l][c] == VIDE) && (verifHauteurSol(laGrille, l, c)))
            {
                if (((laGrille[l + 1][c + 1] == pion) && (laGrille[l - 1][c - 1] == pion) && (laGrille[l - 2][c - 2] == pion)) 
                || ((laGrille[l - 1][c - 1] == pion) && (laGrille[l + 1][c + 1] == pion) && (laGrille[l + 2][c + 2] == pion)))
                {
                    colonne = c;
                    ligne = l;
                }
            }
        }
    }
    if (chercherLigne(laGrille, colonne) == ligne){
        // printf("ca marche connard SEP ");
        return colonne; 
    }
    else
    {
        // printf("de la merde ce JAYPEE SEP ");
        return -1;
    }
}

// Recherche un alignement de deux pièces encadrées par des cellules vides (contre) et place le résultat dans un tableau
void rechercheAlign2encadre(Grille laGrille, Tab7 t_coupsPossibles, char pion)
{
    int l, c;
    int hauteurLigne = chercheHauteurLigne(laGrille);

    // alignement horizontal
    for (l = (NB_LIGNES - 1) ; l >= hauteurLigne ; l--)
    {
        for (c = 0 ; c < NB_COLONNES/2 ; c++)
        {
            if ((laGrille[l][c] == VIDE) && (verifHauteurSol(laGrille, l, c)))
            {
                if (((laGrille[l][c + 1] == pion) && (laGrille[l][c + 2] == pion) && (laGrille[l][c + 3] == VIDE)))
                {
                    t_coupsPossibles[c] = c;
                    if (verifHauteurSol(laGrille, l, (c + 3)))
                    {
                        t_coupsPossibles[c + 3] = c + 3;
                    }
                }
            }
        }
    }
    // alignement diagonal direction sud-est ↘️
    for (l = (NB_LIGNES - 1) ; l >= hauteurLigne ; l--)
    {
        for (c = 0 ; c < NB_COLONNES/2 ; c++)
        {
            if ((laGrille[l][c] == VIDE) && (verifHauteurSol(laGrille, l, c)))
            {
                if (((laGrille[l + 1][c + 1] == pion) && (laGrille[l + 2][c + 2] == pion) && (laGrille[l + 3][c + 3] == VIDE)))
                {
                    t_coupsPossibles[c] = c;
                    if (verifHauteurSol(laGrille, (l + 3), (c + 3)))
                    {
                        t_coupsPossibles[c + 3] = c + 3;
                    }
                }
            }
        }
    }
    // alignement diagonal direction nord-est ↗️
    for (l = (NB_LIGNES - 1) ; l >= hauteurLigne ; l--)
    {
        for (c = 0 ; c < NB_COLONNES/2 ; c++)
        {
            if ((laGrille[l][c] == VIDE) && (verifHauteurSol(laGrille, l, c)))
            {
                if (((laGrille[l - 1][c + 1] == pion) && (laGrille[l - 2][c + 2] == pion) && (laGrille[l - 3][c + 3] == VIDE)))
                {
                    t_coupsPossibles[c] = c;
                    if (verifHauteurSol(laGrille, (l - 3), (c + 3)))
                    {
                        t_coupsPossibles[c + 3] = c + 3;
                    }
                }
            }
        }
    }
}

// Recherche un alignement de deux pions consécutifs précédés ou suivis de deux cellules vides
void rechercheAlign2(Grille laGrille, Tab7 t_coupsPossibles, char pion)
{
    int l, c;
    int hauteurLigne = chercheHauteurLigne(laGrille);

    // alignement horizontal ↔️
    for (l = (NB_LIGNES - 1) ; l >= hauteurLigne ; l--)
    {
        //  vers la droite ➡️
        for (c = 0 ; c < NB_COLONNES/2 ; c++)
        {
            if ((laGrille[l][c] == VIDE) && (verifHauteurSol(laGrille, l, c)))
            {
                if (((laGrille[l][c + 1] == VIDE) && (laGrille[l][c + 2] == pion) && (laGrille[l][c + 3] == pion)))
                {
                    t_coupsPossibles[c] = c;
                    if (verifHauteurSol(laGrille, l, (c + 1)))
                    {
                        t_coupsPossibles[c + 1] = c + 1;
                    }
                }
            }
        }
        // vers la gauche ⬅️
        for (c = NB_COLONNES - 1 ; c >= NB_COLONNES/2 ; c--)
        {
            if ((laGrille[l][c] == VIDE) && (verifHauteurSol(laGrille, l, c)))
            {
                if (((laGrille[l][c - 1] == VIDE) && (laGrille[l][c - 2] == pion) && (laGrille[l][c - 3] == pion)))
                {
                    t_coupsPossibles[c] = c;
                    if (verifHauteurSol(laGrille, l, (c - 1)))
                    {
                        t_coupsPossibles[c - 1] = c - 1;
                    }
                }
            }
        }
    }
    // alignement diagonal 
    for (l = (NB_LIGNES - 1) ; l >= hauteurLigne ; l--)
    {
        // vers le sud-est ↘️
        for (c = 0 ; c < NB_COLONNES/2 ; c++)
        {
            if ((laGrille[l][c] == VIDE) && (verifHauteurSol(laGrille, l, c)))
            {
                if (((laGrille[l + 1][c + 1] == VIDE) && (laGrille[l + 2][c + 2] == pion) && (laGrille[l + 3][c + 3] == pion)))
                {
                    t_coupsPossibles[c] = c;
                    if (verifHauteurSol(laGrille, (l + 1), (c + 1)))
                    {
                        t_coupsPossibles[c + 1] = c + 1;
                    }
                }
            }
        }
        // vers le sud-ouest ↙️
        for (c = NB_COLONNES - 1 ; c >= NB_COLONNES/2 ; c--)
        {
            if ((laGrille[l][c] == VIDE) && (verifHauteurSol(laGrille, l, c)))
            {
                if (((laGrille[l + 1][c - 1] == VIDE) && (laGrille[l + 2][c - 2] == pion) && (laGrille[l + 3][c - 3] == pion)))
                {
                    t_coupsPossibles[c] = c;
                    if (verifHauteurSol(laGrille, (l + 1), (c - 1)))
                    {
                        t_coupsPossibles[c - 1] = c - 1;
                    }
                }
            }
        }
    }
    for (l = (NB_LIGNES - 1) ; l >= hauteurLigne ; l--)
    {
        // vers nord-est ↗️
        for (c = 0 ; c < NB_COLONNES/2 ; c++)
        {
            if ((laGrille[l][c] == VIDE) && (verifHauteurSol(laGrille, l, c)))
            {
                if (((laGrille[l - 1][c + 1] == VIDE) && (laGrille[l - 2][c + 2] == pion) && (laGrille[l - 3][c + 3] == pion)))
                {
                    t_coupsPossibles[c] = c;
                    if (verifHauteurSol(laGrille, (l - 1), (c + 1)))
                    {
                        t_coupsPossibles[c + 1] = c + 1;
                    }
                }
            }
        }
        // vers le nord-ouest ↖️
        for (c = NB_COLONNES - 1 ; c >= NB_COLONNES/2 ; c--)
        {
            if ((laGrille[l][c] == VIDE) && (verifHauteurSol(laGrille, l, c)))
            {
                if (((laGrille[l - 1][c - 1] == VIDE) && (laGrille[l - 2][c - 2] == pion) && (laGrille[l - 3][c - 3] == pion)))
                {
                    t_coupsPossibles[c] = c;
                    if (verifHauteurSol(laGrille, (l - 1), (c - 1)))
                    {
                        t_coupsPossibles[c - 1] = c - 1;
                    }
                }
            }
        }
    }
}

// Cherche à "anticiper" un mauvais placement
void eviterBadMove(Grille laGrille, Tab7 t_colonnesInterdites, char pion)
{
    int l, c;
    int hauteurLigne = chercheHauteurLigne(laGrille);

    for (l = (NB_LIGNES - 1) ; l >= hauteurLigne ; l--)
    {
        for (c = 0 ; c < NB_COLONNES ; c++)
        {
            if ((laGrille[l][c] == VIDE) && (verifHauteurSol(laGrille, l, c)))
            {
                // bad move horizontal
                if (((laGrille[l - 1][c + 1] == pion) && (laGrille[l - 1][c + 2] == pion) && (laGrille[l - 1][c + 3] == pion))
                || ((laGrille[l - 1][c - 1] == pion) && (laGrille[l - 1][c + 1] == pion) && (laGrille[l - 1][c + 2] == pion))
                || ((laGrille[l - 1][c - 2] == pion) && (laGrille[l - 1][c - 1] == pion) && (laGrille[l - 1][c + 1] == pion))
                || ((laGrille[l - 1][c - 3] == pion) && (laGrille[l - 1][c - 2] == pion) && (laGrille[l - 1][c - 1] == pion))
                // bad move diagonal
                || ((laGrille[l - 2][c - 1] == pion) && (laGrille[l - 3][c - 2] == pion) && (laGrille[l - 4][c - 3] == pion))
                || ((laGrille[l - 2][c + 1] == pion) && (laGrille[l - 3][c + 2] == pion) && (laGrille[l - 4][c + 3] == pion))
                || ((laGrille[l][c + 1] == pion) && (laGrille[l - 2][c - 1] == pion) && (laGrille[l - 3][c - 2] == pion))
                || ((laGrille[l][c - 1] == pion) && (laGrille[l - 2][c + 1] == pion) && (laGrille[l - 3][c + 2] == pion))
                || ((laGrille[l - 2][c - 1] == pion) && (laGrille[l][c + 1] == pion) && (laGrille[l + 1][c + 2] == pion))
                || ((laGrille[l + 1][c - 2] == pion) && (laGrille[l][c - 1] == pion) && (laGrille[l - 2][c + 1] == pion))
                || ((laGrille[l][c + 1] == pion) && (laGrille[l + 1][c + 2] == pion) && (laGrille[l + 2][c + 3] == pion))
                || ((laGrille[l + 2][c - 3] == pion) && (laGrille[l - 1][c - 2] == pion) && (laGrille[l][c - 1] == pion))){
                    t_colonnesInterdites[c] = c;
                }
            }
        }
    }
}

// Vérifie si un coup interdit n'est pas présent dans le tableau des coups possibles et corrige le tir éventuellement
void comparePossibilites(Grille laGrille, Tab7 t_colonnesInterdites, Tab7 t_coupsPossibles, char pionJP, char pionAdv)
{
    int c;

    for (c = 0; c < NB_COLONNES; c++)
    {
        if ((t_colonnesInterdites[c] == c) && (t_coupsPossibles[c] == c))           // si la coordonnée d'une cellule se trouve à la fois dans le tableau colonneInterdites et dans coupsPossibles, 
        {
            t_coupsPossibles[c] = -1 ;                                             // on le retire des coups possibles
        }
    }
}

// Regarde si un coup est suggéré dans le tableau 
bool verifierCoupsPossiblesPresents(Grille laGrille, Tab7 t_coupsPossibles)
{
    bool coupsPossibles = false; // on part du principe qu'il n'y a pas de coups suggérés dans le tableau (rempli de -1)
    int c;

    for (c = 0; c < NB_COLONNES; c++)
    {
        if ((t_coupsPossibles[c] != -1) && (coupsPossibles == false))
        {
            coupsPossibles = true;     // Dès qu'une valeur différente de -1 a été trouvée
        }
    }
    return coupsPossibles;
}

// Joue une colonne au hasard parmi les coups possibles
int colonneAuHasardParmi(Grille laGrille, Tab7 t_coupsPossibles)
{
    int a;
    int colonne;

    do
    {
        a = rand()%7;
    } 
    while (t_coupsPossibles[a] == VIDE);
    colonne = a;

    return colonne;
}

// Joue une colonne aléatoire
int choisirColonneAleatoire(Grille laGrille)
{
    int colonne = rand()%7;

    return colonne;
}


//*****************************
// STRATS À FAIRE À LA SÉANCE 1
//*****************************

// Stratégie qui consiste à choisir la colonne la plus à gauche 🦾
int choisirColonneStrategie1(Grille laGrille)
{
    int colonne = 0;
    int resultat;

    resultat = chercherLigne(laGrille, colonne);

    while (resultat == -1)
    {
        colonne++;
        resultat = chercherLigne(laGrille, colonne);
    }
    return colonne;
}

// Stratégie qui consiste à choisir la colonne la moins remplie 🦾
int choisirColonneStrategie2(Grille laGrille)
{
    Tab7 tablo;
    Tab7 tablo2 = {VIDE, VIDE, VIDE, VIDE, VIDE, VIDE, VIDE};
    int c, l;
    int colonne = 0; 
    int colAlea;

    for (c = 0; c < NB_COLONNES; c++)
    {
        for (l = 0; l < NB_LIGNES; l++)
        {
            if (laGrille[l][c] == VIDE)
            {
                tablo[c] = l;
            }
        }
    }

    for (c = 0; c < NB_COLONNES; c++)
    {
        if (tablo[c] > colonne)
        {
            colonne = tablo[c];
        }
    }

    for (c = 0; c < NB_COLONNES; c++)
    {
        if (tablo[c] == colonne)
        {
            tablo2[c] = c;
        }
    }

    do
    {
        colAlea = rand()%7;
    } 
    while (tablo2[colAlea] == VIDE);
    colonne = colAlea;

    return colonne;
}

// Stratégie qui consiste à choisir la colonne la plus au milieu 🦾
int choisirColonneStrategie3(Grille laGrille)
{
    typedef int tabAlea[2];
    tabAlea t;
    int colAlea;
    int colonne = NB_COLONNES/2;

    if ((laGrille[0][NB_COLONNES/2] != VIDE) && ((laGrille[0][NB_COLONNES/2 - 1] == VIDE) || (laGrille[0][NB_COLONNES/2 + 1 == VIDE])))
    {
        t[0] = NB_COLONNES/2 - 1;
        t[1] = NB_COLONNES/2 + 1;
        colAlea = rand()%2;
        colonne = t[colAlea];
    }
    else if ((laGrille[0][NB_COLONNES/2] != VIDE) && (laGrille[0][NB_COLONNES/2 - 1] != VIDE) && (laGrille[0][NB_COLONNES/2 + 1 != VIDE]) && ((laGrille[0][NB_COLONNES/2 - 2] == VIDE) || (laGrille[0][NB_COLONNES/2 + 2 == VIDE])))
    {
        t[0] = NB_COLONNES/2 - 2;
        t[1] = NB_COLONNES/2 + 2;
        colAlea = rand()%2;
        colonne = t[colAlea];
    }
    else if ((laGrille[0][NB_COLONNES/2] != VIDE) && (laGrille[0][NB_COLONNES/2 - 1] != VIDE) && (laGrille[0][NB_COLONNES/2 + 1 != VIDE]) && (laGrille[0][NB_COLONNES/2 - 2] != VIDE) && (laGrille[0][NB_COLONNES/2 + 2 != VIDE]) 
    && ((laGrille[0][NB_COLONNES/2 - 3] == VIDE) || (laGrille[0][NB_COLONNES/2 + 3 == VIDE])))
    {
        t[0] = NB_COLONNES/2 - 3;
        t[1] = NB_COLONNES/2 + 3;
        colAlea = rand()%2;
        colonne = t[colAlea];
    }
    return colonne;
}

// Stratégie qui consiste à choisir la colonne de manière aléatoire 🦾
int choisirColonneStrategie4(Grille laGrille)
{
    int colonne = rand() % 7 + 1;           // Pourquoi ? 7 + 1 <=> 1, 2, 3, 4, 5, 6

    return colonne;
}