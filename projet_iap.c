#include <stdlib.h>

#define maxTournois 10                      // nb maximum de tournois
#define nbMatch 127                         // nb de matchs par tournois
#define nbJoueuses 128                      // nb joueuses par tournois
#define lgMot 30                            // nb de caractères max


unsigned int nbTournois;

char mot[lgMot+1];                          // chaîne de caractères (mot) de taille max lgMot contenant la commande

typedef struct{
    unsigned char nomJoueuse;               // nom de la joueuse
    int pointsCummules;                     // nb points cummulés
}Joueuse;

typedef struct{
    unsigned int indexGagnante;             // index de la gagnante
    unsigned int indexPerdante;             // index de la perdante
}Match;

typedef struct{
    unsigned char nomTournoi;               // nom du tournoi
    unsigned int date;                      // date du tournoi
    Match tableauMatchs[nbMatch+1];         // tableau des 127 matchs
}Tournoi;

typedef struct{
    Tournoi tableauTournois[maxTournois+1]; // tableau des tournois
}TournoisWTA;


int main(){
    while(1){
        scanf("%s", mot);                   // entrée de la commande

        // Si la commande rentrée est "definir_nombre_tournois" :
        if (strcmp(mot, "definir_nombre_tournois") == 0){
            // Non terminée !
        }

        // Si la commande rentrée est enregistrement_tournois" :
        else if (strcmp(mot, "enregistrement_tournoi") == 0){
            // Non terminée !
        }

        // Si la commande rentrée est "affichage_matchs_tournois" :
        else if (strcmp(mot, "affichage_matchs_tournoi") == 0){  

        }
    
        // Si la commande rentrée est "exit" :
        else if (strcmp(mot, "exit") == 0) {
            exit(0);
        }
    }
}
