#include "header.h"
#include<time.h>



int main(int argc, char** argv) {
    int nEq, nbEquipesEnLice = 100;

    /** Conversion d'un fichier csv en structure contenant un tableau de structure d'équipes **/
    TabEquipes *tabequipes = (TabEquipes*)malloc(sizeof(TabEquipes));
    char* cheminCSV;

    if(argc == 2){
        cheminCSV = argv[1];
    }
    else if(argc <= 1){
        cheminCSV = "data/squads_test.csv";
    }
    else {
        printf("Veuillez donnez ou non un seul argument pour le fichier csv des équipes.");
    }

    *tabequipes = csv_to_tab_struct(cheminCSV, 0);

    srand(time(NULL));

    while(nbEquipesEnLice > 90 || !estPuissanceDeDeux(nbEquipesEnLice)){
        printf("Combien d'equipes voulez-vous faire jouer ? ");
        scanf("%d", &nbEquipesEnLice);
        if(nbEquipesEnLice > 90){
            printf("Veuillez donner un nombre d'équipes inférieur à 90");
        }
        else if(!estPuissanceDeDeux(nbEquipesEnLice)){
            printf("Veuillez donner un nombre d'équipes de puissance de 2");
        }
    }

    /** Choix aléatoire parmi les équipes récupérées précedemment **/
    *tabequipes = rand_generate_squads(nbEquipesEnLice, *tabequipes, 0);
    //afficheEquipes(*tabequipes);

    nEq = tabequipes->nbEquipes;
    // Vérifier si le nombre d'équipes est une puissance de deux
    if(!estPuissanceDeDeux(nEq)) {
        printf("Le nombre d'équipes n'est pas une puissance de deux.\n");
        return 1;
    } else {
        printf("Le nombre d'équipes est une puissance de deux.\n");
    }

    // Simulation des matchs
    simulerMatchs(tabequipes);

    libereTabEquipes(tabequipes);
    // Libérer la mémoire allouée pour le tableau d'Equipe
    free(tabequipes);

    return 0;
}
