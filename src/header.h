#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
/** Macro qui associe la valeur 51 à l'identifcateur LINE_MAX_SIZE **/
#define LINE_MAX_SIZE 51

/** Macro qui associe la valeur 100 à l'identifcateur NB_LINES **/
#define NB_LINES 100

/** Macro qui associe la valeur 20 à l'identifcateur STRING_MAX_SIZE **/
#define STRING_MAX_SIZE 20




/** Définition de la structure Equipe **/
typedef struct equipe{
    int id;                         // Identifiant spécifique à l'équipe
    char *nom;      // Nom de l'équipe
    char *champ;    // Championnat
    short att;                      // Attribut Attaque
    short mil;                      // Attribut Milieu
    short def;                      // Attribut Défense
    short gen;                      // Note génerale
    float note;                     // Note de l'équipe /5
}Equipe;

typedef struct{
    int nbEquipes;
    Equipe* equipes;
}TabEquipes;

typedef struct match{
    int id1;            /**id de la première équipe**/
    int id2;            /**id de la deuxième équipe**/
    float score1;       /**Score de la première équipe**/
    float score2;       /**Score de la deuxième équipe**/
} Match;

typedef struct {
    Match* matchs;          /**Tableau de matchs**/
    int nbMatchs;           /**Nombre de matchs**/
} TabMatchs;

typedef struct tour{
    TabEquipes* tabequipes; /**Tableau de toutes les équipes**/
    TabMatchs* tabmatchs;   /**Tableau de tous les matchs**/
    int *gagnants;          /**Tableau de gagnants**/
    int nbGagnants;         /**Nombre de gagnants**/
}Tour;



typedef Equipe TElement;

TabEquipes rand_generate_squads(int nbEquipesEnLice, TabEquipes tabequipes, int affEquipes);
int estVideTabEquipes(TabEquipes tabequipes);
Equipe initEquipe();
TabEquipes initTabEquipes(int nbEquipes);
void allocMemTab(int n, TElement **tab);
void afficheEquipes(TabEquipes tabequipes);
TabEquipes csv_to_tab_struct(char* chemin, int affEquipes);
void conf_extract(char* chemin, char* cheminCSV, int* nbEquipesEnLice, char *tournamentName, int* dureeMatch);
int estExisteEquipe(TabEquipes tabequipes, int equipeId);
char *strextract(char *chaine, char debut, char fin);
void jouerMatch(Equipe* equipe1, Equipe* equipe2, int num1, int num2, float *s1, float *s2);
int verifierNbEquipes(TabEquipes tabequipes);
int estPuissanceDeDeux(int n);
void simulerMatchs(TabEquipes *tabequipes);
void libereTabEquipes(TabEquipes *tabequipes);
Equipe* getEquipeById(int id, TabEquipes* tabequipes);
void simulerTour(void* args);
TabMatchs* generateMatchsGagnants(int* gagnants, int nbGagnants);
TabMatchs* generateMatchs(TabEquipes *tabequipes);
Equipe* getEquipeById(int id, TabEquipes* tabequipes);


#endif // HEADER_H_INCLUDED
