#include "header.h"


/**
 * Cette fonction initialise une structure Equipe (struct equipe).
 * @param l'identifiant de l'equipe
 * @return Une structure equipe
 * */
Equipe initEquipe(int id){
Equipe equipe;
    equipe.nom = (char*)malloc(STRING_MAX_SIZE*sizeof(char));
    equipe.champ = (char*)malloc(STRING_MAX_SIZE*sizeof(char));
    equipe.id = id;
    equipe.att = 0;
    equipe.mil = 0;
    equipe.def = 0;
    equipe.gen = 0;
    equipe.note = 0;
    return equipe;
}

/**
 * Cette procédure alloue de la mémoire pour un tableau.
 *
 * @param n : Taille d'un tableau
 * @param tab: Tableau de 'Equipe' (Chane de caractères)
 *
 * */
void allocMemTab(int n, TElement** tab){
    *tab = (TElement*)malloc(n*sizeof(TElement));
    if(*tab == NULL){
        perror("Erreur d'allocation mémoire");
        exit(0);
    }
}



/**
 * Cette procédure affiche un tableau d'équipes.
 *
 * @param tabequipes : structure Tableau d'équipes { @link TabEquipes }
 *
 * */

void afficheEquipes(TabEquipes tabequipes){
Equipe* ptr;
Equipe* ptrF = tabequipes.equipes + tabequipes.nbEquipes;

    for(ptr = tabequipes.equipes; ptr < ptrF; ptr++){
        printf("Équipe : %s\nChampionnat : %s\nAttaque : %d\nMilieu : %d\nDéfense : %d\nNote Génerale : %d\nNote/5: %2.1f\n\n", ptr->nom, ptr->champ, ptr->att, ptr->mil, ptr->def, ptr->gen, ptr->note);
    }

}

/**
 * Cette fonction initialise une structure Equipe (struct equipe).
 *
 * @return Une structure equipe
 * */
void libereTabEquipes(TabEquipes *tabequipes){
    // Libérer la mémoire allouée pour chaque chaîne de caractères
    for(int i = 0; i < tabequipes->nbEquipes; i++){
        free(tabequipes->equipes[i].nom);
        free(tabequipes->equipes[i].champ);
    }

    // Mettre le nombre d'équipes à zéro
    tabequipes->nbEquipes = 0;
}



void libereTabMatchs(TabMatchs* tabmatchs) {
int i;
    for(i=0; i<tabmatchs->nbMatchs; i++) {
        free(tabmatchs->matchs+i);
    }
    free(tabmatchs);
}


/**
 * Cette fonction initialise une structure TabEquipe.
 *
 * @return Une structure TabEquipe
 * */
TabEquipes initTabEquipes(int nbEquipes){
TabEquipes tabequipes;
    allocMemTab(nbEquipes, &tabequipes.equipes);
    tabequipes.nbEquipes = nbEquipes;
    return tabequipes;
}
