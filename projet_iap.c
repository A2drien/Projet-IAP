#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define maxTournois 10                      // nb maximum de tournois
#define nbMatchTournoi 127                  // nb de matchs par tournois
#define nbJoueusesTournoi 128               // nb joueuses par tournois
#define lgMot 30                            // nb de caractères max


typedef struct{
    unsigned char nomJoueuse;               // nom de la joueuse
    int pointsCummules;                     // nb points cummulés
}Joueuse;

typedef struct{
    unsigned int idxGagnante;             // index de la gagnante
    unsigned int idxPerdante;             // index de la perdante
}Match;

typedef struct{
    unsigned char *nomTournoi[lgMot];       // nom du tournoi
    unsigned char *dateTournoi[lgMot];      // date du tournoi
    Match *dataMatch[nbMatchTournoi];       // tableau des 127 matchs
}Tournoi;

typedef struct{
    Tournoi *dataTournois[maxTournois];     // tableau de l'ensemble des matchs
    Joueuse *dataJoueuses[maxTournois*nbJoueusesTournoi];
}TournoisWTA;


unsigned int nbTournois;
unsigned int numero_tournoi = 0;
char *mot[lgMot+1];                         // chaîne de caractères (mot) de taille max lgMot contenant la commande
TournoisWTA *TournoiWTA;


int main(){
    while (1){
        scanf("%s", &mot);                   // entrée de la commande

        // Si la commande rentrée est "definir_nombre_tournois" :
        if (strcmp(mot, "definir_nombre_tournois") == 0){
            definir_nombre_tournois();
        }

        // Si la commande rentrée est "enregistrement_tournois" :
        else if (strcmp(mot, "enregistrement_tournoi") == 0){
            enregistrement_tournoi();
        }

        // Si la commande rentrée est "affichage_matchs_tournois" :
        else if (strcmp(mot, "affichage_matchs_tournoi") == 0){
            affichage_matchs_tournoi();
        }
    
        // Si la commande rentrée est "exit" :
        else if (strcmp(mot, "exit") == 0) {
            exit(0);
        }
    }
    system("pause");
    return 0;
}

void definir_nombre_tournois(){
    nbTournois = atoi(scanf("%s", &mot));
}

void enregistrement_tournoi(){
    char nom[lgMot] = scanf("%s", &mot);
    for (int i=0; i<strlen(nom); i++){
        TournoiWTA->dataTournois[numero_tournoi]->nomTournoi[i] = nom[i];
    }

    char date[lgMot] = scanf("%s", &mot);
    for (int i=0; i<strlen(date); i++){
        TournoiWTA->dataTournois[numero_tournoi]->dateTournoi[i] = date[i];
    }
    numero_tournoi++;

    for (int i=0; i<64; i++){
        char nomGagnante[lgMot] = scanf("%s", &mot);
        char nomPerdante[lgMot] = scanf("%s", &mot);

        TournoiWTA->dataJoueuses[numero_tournoi*nbMatchTournoi + i*2]->nomJoueuse = nomGagnante;
        TournoiWTA->dataJoueuses[numero_tournoi*nbMatchTournoi + i*2 + 1]->nomJoueuse = nomPerdante;

        TournoiWTA->dataTournois[numero_tournoi]->dataMatch[i]->idxGagnante = i*2;
        TournoiWTA->dataTournois[numero_tournoi]->dataMatch[i]->idxPerdante = i*2+1;
        
        TournoiWTA->dataJoueuses[numero_tournoi*nbMatchTournoi + i]->pointsCummules = 10;
    }

    for (int i=64; i<nbMatchTournoi; i++){
        
    }
    
}