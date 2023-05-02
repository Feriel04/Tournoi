#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <math.h>
#include "header.h"

void jouerMatch(Equipe* equipe1, Equipe* equipe2, int num1, int num2, float *s1, float *s2) {
    FILE* f = fopen("resultats.txt", "a");  // Ouverture du fichier en mode ajout
    int score1, score2, peno1 = 0, peno2 = 0;
    printf("Match en cours : Equipe %d (%s) vs Equipe %d (%s)\n", num1, equipe1->nom, num2, equipe2->nom);
    fprintf(f, "Match en cours : Equipe %d (%s) vs Equipe %d (%s)\n", num1, equipe1->nom, num2, equipe2->nom);

    // simulation du match
    srand((unsigned int)time(NULL)+ num1); // réinitialisation de la graine
    score1 = rand() % 5;
    srand((unsigned int)time(NULL) + num2); // réinitialisation de la graine
    score2 = rand() % 5;

    if (score1 > score2) {
        printf("Equipe %d (%s) a gagné le match !\nScore : %d-%d\n", num1, equipe1->nom, score1, score2);
        fprintf(f, "Equipe %d (%s) a gagné le match !\nScore : %d-%d\n", num1, equipe1->nom, score1, score2);
    } else if (score2 > score1) {
        printf("Equipe %d (%s) a gagné le match !\nScore : %d-%d\n", num2, equipe2->nom, score1, score2);
        fprintf(f, "Equipe %d (%s) a gagné le match !\nScore : %d-%d\n", num2, equipe2->nom, score1, score2);
    } else {
        printf("Match nul !\nScore : %d-%d\n", score1, score2);
        fprintf(f, "Match nul !\nScore : %d-%d\n", score1, score2);
        srand((unsigned int)time(NULL)+ num1); // réinitialisation de la graine
        peno1 = rand() % 5;
        srand((unsigned int)time(NULL) + num2); // réinitialisation de la graine
        peno2 = rand() % 5;
        if(peno1 == peno2){
            peno1 = rand() % 1 + peno1;
            if(peno1 == peno2){
               peno2++;
            }
        }

        printf("Séance de tirs aux buts : (%d-%d)\n", peno1, peno2);
        fprintf(f, "Séance de tirs aux buts : (%d-%d)\n", peno1, peno2);

        if(peno1 > peno2){
            printf("Equipe %d (%s) a gagné le match !\n", num1, equipe1->nom);
            fprintf(f, "Equipe %d (%s) a gagné le match !\n", num1, equipe1->nom);
        }
        else{
            printf("Equipe %d (%s) a gagné le match !\n", num2, equipe2->nom);
            fprintf(f, "Equipe %d (%s) a gagné le match !\n", num2, equipe2->nom);
        }
    }


    *s1 = (float)(score1 + ((float)peno1/10));
    *s2 = (float)(score2 + ((float)peno2/10));
    printf("score : %f, %f\n", *s1, *s2);
    fprintf(f, "score : %f, %f\n", *s1, *s2);
    fclose(f);
}

void simulerTour(void* args){
    Tour* infoTour = (Tour*)args;
    int i, id1, id2, j, n = infoTour->tabmatchs->nbMatchs;
    int vainqueur;
    Equipe* equipeVainqueur;
    //infoTour->gagnants = (int*)malloc(((int)n/2)*sizeof(int));
    /*if(infoTour->gagnants == NULL){
        perror("Allocation mémoire échouée");
        exit(4);
    }*/
    infoTour->nbGagnants = n;
    float score1, score2;
    for(i = 0; i < n; i++){
        infoTour->gagnants[i] = -1;
    }

    // Execution des matchs du même tour
    for(i = 0, j = 0; i < n; i++, j++){
        id1 = infoTour->tabmatchs->matchs[i].id1;
        id2 = infoTour->tabmatchs->matchs[i].id2;
        score1 = infoTour->tabmatchs->matchs[i].score1;
        score2 = infoTour->tabmatchs->matchs[i].score2;

        //Jouer un seul match
        jouerMatch(getEquipeById(id1, infoTour->tabequipes), getEquipeById(id2, infoTour->tabequipes), 2*i, 2*i+1, &score1, &score2);
        //printf("score : %f, %f\n", score1, score2);
        if(score1 > score2)
            infoTour->gagnants[j] = id1;
        else
            infoTour->gagnants[j] = id2;
    }
    if(infoTour->nbGagnants == 1){
        vainqueur = infoTour->gagnants[0];
        equipeVainqueur = getEquipeById(vainqueur, infoTour->tabequipes);

        printf("===========================================================\n\n");
        printf("Le vainqueur est %s !!!!\n", equipeVainqueur->nom);
        printf("===========================================================\n\n");
    }
    pthread_exit(NULL);
}

void simulerMatchs(TabEquipes* tabequipes) {
    int i, j, n = tabequipes->nbEquipes;
    //Gagnant gagnants[n];
    int numTour = 1;
    int gagnants[n/2];
    //int nbGagnants = 0;
    int nbTours = log2(n);

    pthread_t tours[nbTours];

    for(i = 0; i < nbTours; i++){
        tours[i] = (pthread_t)-1;
    }

    //Boucle des tours
    for (i = 0; i < nbTours; i++) {
        Tour infoTour;
        infoTour.tabequipes = tabequipes;
        infoTour.gagnants = gagnants;
        infoTour.tabmatchs = NULL;
        if(i != 0){
            infoTour.tabmatchs = generateMatchsGagnants(infoTour.gagnants, infoTour.nbGagnants);
        }
        else{
            infoTour.nbGagnants = 0;
            infoTour.tabmatchs = generateMatchs(tabequipes);
        }

        //Création du thread
        //simulerTour((void*) &infoTour);
        printf("====================Tour %d a commencé====================\n\n", i);
        pthread_create(&tours[i], NULL, (void*)simulerTour, (void*) &infoTour);
        sleep(2);
        printf("====================Tour %d est terminé====================\n\n", i);

        //nbGagnants = infoTour.nbGagnants;
        numTour++;
        for(j = 0; j < i; j++){
            pthread_join(tours[j], NULL);
        }

        free(infoTour.tabmatchs->matchs);
        free(infoTour.tabmatchs);
    }


}


TabMatchs* generateMatchs(TabEquipes *tabequipes){
int i, j, n = tabequipes->nbEquipes;
Equipe* equipes = tabequipes->equipes;
TabMatchs *tabmatchs = (TabMatchs*)malloc(sizeof(TabMatchs));
    //Initialisation
    tabmatchs->nbMatchs = n/2;
    tabmatchs->matchs = (Match*)malloc((n/2)*sizeof(Match));
    //Remplissage
    for(i = 0, j = 0; j < n; j+=2, i++){
        tabmatchs->matchs[i].id1 = equipes[j].id;
        tabmatchs->matchs[i].id2 = equipes[j+1].id;
        tabmatchs->matchs[i].score1 = 0;
        tabmatchs->matchs[i].score2 = 0;
    }
    return tabmatchs;
}

TabMatchs* generateMatchsGagnants(int* gagnants, int nbGagnants){
int i;
int* ptr;
int* ptrMax = gagnants + nbGagnants;
TabMatchs *tabmatchs = (TabMatchs*)malloc(sizeof(TabMatchs));
    //Initialisation
    tabmatchs->nbMatchs = nbGagnants/2;
    tabmatchs->matchs = (Match*)malloc((nbGagnants/2)*sizeof(Match));
    //Remplissage
    for(i = 0, ptr = gagnants; ptr < ptrMax; ptr+=2, i++){
        tabmatchs->matchs[i].id1 = *ptr;
        tabmatchs->matchs[i].id2 = *(ptr+1);
        tabmatchs->matchs[i].score1 = 0;
        tabmatchs->matchs[i].score2 = 0;
    }
    return tabmatchs;
}


