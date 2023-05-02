#include "header.h"
#define MAX_LIGNE 100



/**
 * Cette fonction transforme un fichier csv en tableau de structures d'équipes.
 *
 * Pour réaliser la transformation le programme ouvre le fichier à l'aide du
 * chemin de fichier passé en paramètre et lit son contenu à l'aide de la
 * fonction :
 * FILE *fopen (const char *__restrict __filename, const char *__restrict __modes);
 * qui ouvre un fichier en précisant un mode (en l'occurence dans notre cas en mode
 * lecture). Ensuite le programme stocke toutes les lignes du fichier dans un tableau
 * de chaines de caractères à l'aide de la fonction:
 * char *fgets(char *restrict s, int size, FILE *restrict stream);
 * Après le programme traduit ce dernier tableau en un tableau
 * de structures
 *
 * @param chemin : chemin vers le fichier
 * @param affEquipes : booléen qui permet d'afficher ou non la structure
 * @return equipes : Tableau de 'Equipe' (struct equipe)
 *
 * */

TabEquipes csv_to_tab_struct(char* chemin, int affEquipes){
    // Variables locales de parcours
    short i = 0, j = 0, k = 0, m = 0;

    FILE* f; // Pointeur vers un flux

    char *ligne = NULL; // Variable de Chaine de caractères locale

    size_t len;

    int read;

    char **lignes = NULL; // Variable qui va contenir le contenu du fichier csv

    Equipe equipes[NB_LINES] ; // Tableau d'équipe
    int nbEquipes = 0;  // nombre d'équipes

    TabEquipes tabequipes;
    char* endPtr = NULL; // variable intermédiaire (chaine de caractères -> float)
    char tmpstr[4]; // variable intermédiaire pour faire la transforamtion

    f = fopen(chemin, "r");


    if(f == NULL){
        perror("Erreur d'ouverture du fichier");
        exit(0);
    }

    // allouer de la mémoire pour le tableau de lignes
    lignes = (char**) malloc(91 * sizeof(char*));

    while((read = getline(&ligne, &len, f)) != -1) {
        lignes[i] = ligne;
        ligne = NULL;  // réinitialiser la variable line pour la prochaine allocation de mémoire
        i++;
    }
    nbEquipes = i - 1;


    // Stockage des équipes dans un tableau de structures Equipe
    for(i=1; i<nbEquipes+1; i++){
        // Initialisation de la structure
        equipes[k] = initEquipe(k);

        j = m = 0;
        // Nom de l'équipe
        while (lignes[i][j] != ';'){
            equipes[k].nom[m] = lignes[i][j];
            m++;
            j++;
        }
        j++;
        // Championnat
        m = 0;
        while (lignes[i][j] != ';'){
            equipes[k].champ[m] = lignes[i][j];
            m++;
            j++;
        }
        j++;
        // Attribut Attaque
        equipes[k].att += (short)( ((lignes[i][j] - '0') * 10) + (lignes[i][j+1] - '0'));
        j += 3;

        // Attribut Millieu
        equipes[k].mil += (short)( ((lignes[i][j] - '0') * 10) + (lignes[i][j+1] - '0'));
        j += 3;

        // Attribut Défense
        equipes[k].def += (short)( ((lignes[i][j] - '0') * 10) + (lignes[i][j+1] - '0'));
        j += 3;

        // Attribut Géneral
        equipes[k].gen += (short)( ((lignes[i][j] - '0') * 10) + (lignes[i][j+1] - '0'));
        j += 3;

        // Nombre d'étoiles/5
        m = 0;
        while(lignes[i][j] != '/'){
            tmpstr[m] = lignes[i][j];
            j++;
            m++;
        }
        equipes[k].note = strtof(tmpstr, &endPtr);
        k++;
    }
    nbEquipes = i-1;

    // Affectation des equipes dans une structure TabEquipes
    tabequipes.equipes = equipes;
    tabequipes.nbEquipes = nbEquipes;

    // Affichage des attributs des équipes
    if(affEquipes)
        afficheEquipes(tabequipes);

    // libérer la mémoire allouée
    for (int i = 0; i < 91; i++) {
        free(lignes[i]);
    }
    free(lignes);
    free(ligne);
    fclose(f);


    return tabequipes;
}



/** \brief
 *
 * \param chemin : chemin vers le fichier csv
 * \param nbEquipeEnLice : le nombres d'equipes en lice
 * \param nomDuTournoi : un char qui retourne le nom du tournoi
 * \param dureeMatch : la duree du match
 *
 */


void conf_extract(char* chemin, char* cheminCSV, int* nbEquipesEnLice, char *nomDuTournoi, int *dureeMatch){
    FILE *fichier;
    char ligne[MAX_LIGNE];

    fichier = fopen(chemin, "r");

    if (fichier == NULL) {
        perror("Erreur d'ouverture du fichier");
        exit(0);
    }

    while (fgets(ligne, MAX_LIGNE, fichier)) {
        char *cle = strtok(ligne, "=");
        char *valeur = strtok(NULL, "=");

        if (cle != NULL && valeur != NULL) {
            if (strcmp(cle, "data") == 0) {
                strncpy(cheminCSV, valeur, 50*sizeof(char));
            }
            else if (strcmp(cle, "nbSquads") == 0) {
                *nbEquipesEnLice = atoi(valeur);
            }
            else if (strcmp(cle, "TournamentName") == 0) {
                strncpy(nomDuTournoi, valeur, 50*sizeof(char));
            }
            else if (strcmp(cle, "matchDuration") == 0) {
                *dureeMatch = atoi(valeur);
            }
        }
    }

    fclose(fichier);

}
