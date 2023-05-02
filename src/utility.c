#include "header.h"
#include <time.h>

#define NB_SQUADS_MAX NB_LINES


/** @brief
 *
 * @param un caractere de chaine
 * @param un caractere de debut de chaine
 * @param un caractere de fin de chaine
 * @return retourne debut de chaine
 *
 */

char *strextract(char *chaine, char debut, char fin) {
    char *debut_ch = strchr(chaine, debut);
    char *fin_ch = strchr(chaine, fin);

    if (debut_ch == NULL || fin_ch == NULL || fin_ch < debut_ch) {
        return NULL;
    }

    debut_ch++;  // On avance d'un caractère pour ne pas inclure le caractère de début
    *fin_ch = '\0';  // On remplace le caractère de fin par un caractère de fin de chaîne

    return debut_ch;
}

int estPuissanceDeDeux(int n) {
    if (n == 0) {
        return 0;
    }
    while (n != 1) {
        if (n % 2 != 0) {
            return 0;
        }
        n = n / 2;
    }
    return 1;
}

int verifierNbEquipes(TabEquipes tabequipes) {
    int n = tabequipes.nbEquipes;
    if (estPuissanceDeDeux(n)) {
        return 1;
    }
    return 0;
}


Equipe* getEquipeById(int id, TabEquipes* tabequipes){
int n = tabequipes->nbEquipes;

Equipe* ptr = tabequipes->equipes;
Equipe* ptrMax = ptr + n;

    while(ptr < ptrMax && ptr->id != id){
        ptr++;
    }
    if (ptr < ptrMax)
        return ptr;
    else
        return NULL;
}

/** @brief
 *
 * @param TabEquipes : un tableau d'equipe
 * @param affEquipe : l'affichage d'equipes
 * @param nbEquipesEnLice : le nombres d'equipes qui sont en lice
 * @return tableau d'equipe en lice
 *
 */


typedef Equipe TElement;


TabEquipes rand_generate_squads(int nbEquipesEnLice, TabEquipes tabequipes, int affEquipes){

    srand(time(NULL) + nbEquipesEnLice);
    TabEquipes tabEEL = initTabEquipes(nbEquipesEnLice);

    int randnum;
    Equipe randEquipe;

    int n = tabequipes.nbEquipes; // On récupère le nombre d'équipes dans une variable n.
    int i;

    for(i = 0; i < nbEquipesEnLice; i++){

        do{
            randnum = rand() % (n) - 1;
        }while(estExisteEquipe(tabEEL, tabequipes.equipes[randnum].id));

        randEquipe = tabequipes.equipes[randnum];

        tabEEL.equipes[i].nom = randEquipe.nom;
        tabEEL.equipes[i].champ = randEquipe.champ;

        tabEEL.equipes[i].id = randEquipe.id;
        tabEEL.equipes[i].att = randEquipe.att;
        tabEEL.equipes[i].mil = randEquipe.mil;
        tabEEL.equipes[i].def = randEquipe.def;
        tabEEL.equipes[i].gen = randEquipe.gen;
        tabEEL.equipes[i].note = randEquipe.note;
    }

    if(affEquipes)
        afficheEquipes(tabEEL);

    return tabEEL;
}




/**
 * Fonction qui vérifie si une équipe existe dans un { @link TabEquipes }
 *
 * @param tabequipes : une structure Tableau d'equipes
 * @param id : identifiant de l'equipe
 *
 * @return Booleen qui indique si une equipe existe dans le tableau d'equipess
 *
 **/
int estExisteEquipe(TabEquipes tabequipes, int equipeId){
Equipe* equipes = tabequipes.equipes;
int i = 0, n = tabequipes.nbEquipes;

Equipe* ptr = equipes;
Equipe* ptrMax = equipes + n;

    if(!estVideTabEquipes(tabequipes)){
        while(ptr < ptrMax && equipes[i].id != equipeId){
            i++;
        }

        return ptr < ptrMax;
    }
    return 0;
}

/**
 * Cette fonction vérifie si une structure TabEquipe est vide.
 *
 * @return un booleen qui vérifie si une structure TabEquipes
 * */
int estVideTabEquipes(TabEquipes tabequipes){
    return tabequipes.nbEquipes;
}


