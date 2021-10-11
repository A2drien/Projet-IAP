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
    unsigned int indexGagnante;             // index de la gagnante
    unsigned int indexPerdante;             // index de la perdante
}Match;

typedef struct{
    unsigned char *nomTournoi[lgMot];       // nom du tournoi
    unsigned char *date[lgMot];             // date du tournoi
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
    while(1){
        scanf("%s", mot);                   // entrée de la commande

        // Si la commande rentrée est "definir_nombre_tournois" :
        if (strcmp(mot, "definir_nombre_tournois") == 0){
            definir_nombre_tournois(&mot);
        }

        // Si la commande rentrée est "enregistrement_tournois" :
        else if (strcmp(mot, "enregistrement_tournoi") == 0){
            enregistrement_tournoi(&mot);
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

void definir_nombre_tournois(char *mot){
    char charNbTournois[3];
    unsigned int longueurCommande = strlen("definir_nombre_tournois")+1;
    for (int i=longueurCommande; i<lgMot; i++){
        charNbTournois[i-longueurCommande] = mot[i];
    }
    nbTournois = atoi(charNbTournois);
}

void enregistrement_tournoi(char *mot){
    unsigned int i = strlen("enregistrement_tournoi")+1;
    unsigned int j = 0;
    while (mot[i] != " "){
        TournoiWTA->dataTournois[numero_tournoi]->nomTournoi[j] = mot[i];
        i++; j++;
    }
    numero_tournoi++; i++;
    j = 0;
    while (mot[i] != " " || i == lgMot || mot[i] == "\0"){
        TournoiWTA->dataTournois[numero_tournoi]->date[j] = mot[i];
        i++; j++;
    }
}