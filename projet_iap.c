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
    unsigned int idxGagnante;               // index de la gagnante
    unsigned int idxPerdante;               // index de la perdante
}Match;

typedef struct{
    char *nomTournoi[lgMot];                // nom du tournoi
    char *dateTournoi[lgMot];               // date du tournoi
    Match *dataMatch[nbMatchTournoi];       // tableau des 127 matchs
}Tournoi;

typedef struct{
    Tournoi *dataTournois[maxTournois];     // tableau de l'ensemble des matchs pour un tournoi
    Joueuse *dataJoueuses[maxTournois*nbJoueusesTournoi];
}TournoisWTA;


int nbTournois;
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

        // Si la commande rentrée est "enregistrement_tournoi" :
        else if (strcmp(mot, "enregistrement_tournoi") == 0){
            enregistrement_tournoi();
        }

        // Si la commande rentrée est "affichage_matchs_tournoi" :
        else if (strcmp(mot, "affichage_matchs_tournoi") == 0){
            affichage_match_tournoi();
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
    scanf("%d", &nbTournois);
}

void enregistrement_tournoi(){
    scanf("%s", &TournoiWTA->dataTournois[numero_tournoi]->nomTournoi);
    scanf("%s", &TournoiWTA->dataTournois[numero_tournoi]->dateTournoi);
    numero_tournoi++;

    unsigned int i = 0;
    //  Pour les 64 premiers matchs (64èmes de finales) :
    for (; i<64; i++){
        scanf("%s", &TournoiWTA->dataJoueuses[numero_tournoi*nbMatchTournoi + i*2]->nomJoueuse);
        scanf("%s", &TournoiWTA->dataJoueuses[numero_tournoi*nbMatchTournoi + i*2 + 1]->nomJoueuse);

        TournoiWTA->dataTournois[numero_tournoi]->dataMatch[i]->idxGagnante = i*2;
        TournoiWTA->dataTournois[numero_tournoi]->dataMatch[i]->idxPerdante = i*2+1;

        TournoiWTA->dataJoueuses[numero_tournoi*nbMatchTournoi + i*2]->pointsCummules = 45;
        TournoiWTA->dataJoueuses[numero_tournoi*nbMatchTournoi + i*2+1]->pointsCummules = 10;
    }
    
    char nomGagnante[lgMot];
    char nomPerdante[lgMot];
    
    unsigned int indexGagnante;
    unsigned int indexPerdante;

    unsigned int indexRecuperes;
    for (; i<nbMatchTournoi; i++){
        scanf("%s", &nomGagnante);
        scanf("%s", &nomPerdante);
        
        unsigned int indexRecuperes = 0;
        for (unsigned int j=0; j<nbMatchTournoi; i++){
            if (nomGagnante == TournoiWTA->dataJoueuses[numero_tournoi*nbMatchTournoi + j]){
                indexGagnante = TournoiWTA->dataJoueuses[numero_tournoi*nbMatchTournoi + j];
                indexRecuperes++;
            }

            else if (nomPerdante == TournoiWTA->dataJoueuses[numero_tournoi*nbMatchTournoi + j]) {
                indexPerdante = TournoiWTA->dataJoueuses[numero_tournoi*nbMatchTournoi + j];
                indexRecuperes++;
            }

            if (indexRecuperes == 2){
                break;
            }
        }
        
        TournoiWTA->dataTournois[numero_tournoi]->dataMatch[i]->idxGagnante = indexGagnante;
        TournoiWTA->dataTournois[numero_tournoi]->dataMatch[i]->idxPerdante = indexPerdante;

        // Pour les 16 matchs suivants (16e de finale)
        if (64 <= i && i <= 64+32){
            TournoiWTA->dataJoueuses[indexGagnante]->pointsCummules = 90;
        }

        // Pour les 8 matchs suivants (8e de finale)
        else if (64+32 <= i && i <= 64+32+16){
            TournoiWTA->dataJoueuses[indexGagnante]->pointsCummules = 180;
        }

        // Pour les 4 matchs suivants (quarts de finale)
        else if (64+32+16 <= i && i <= 64+32+16+8){
            TournoiWTA->dataJoueuses[indexGagnante]->pointsCummules = 860;
        }

        // Pour les 4 
        else if (64+32+16+8 <= i && i <= 64+32+16+8+4){
            TournoiWTA->dataJoueuses[indexGagnante]->pointsCummules = 720;
        }
        
        // Pour les 2 matchs suivants (demi-finale)
        else if (64+32+16+8+4 <= i && i <= 64+32+16+8+4+2){
            TournoiWTA->dataJoueuses[indexGagnante]->pointsCummules = 1200;
        }

        // Pour le dernier match (finale)
        else {
            TournoiWTA->dataJoueuses[indexGagnante]->pointsCummules = 2000;
        }
    }
}

// Note pour Cedric : met colle ta fonction ici :
int affichage_match_tournoi(){
    return 0;
}