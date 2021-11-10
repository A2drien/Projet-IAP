#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#pragma warning (disable:4996)

#define maxTournois 10                                                                              // Nombre maximum de tournois
#define nbMatchTournoi 127                                                                          // Nombre de matchs par tournois
#define nbJoueusesTournoi 128                                                                       // Nombre joueuses par tournois
#define lgMot 30                                                                                    // Nombre de caractères max

#define idx64eFinale 0                                                                            // idx du début des 64e de finale dans le tableau des matchs
#define idx32eFinale 64                                                                           // idx du début des 32e de finale dans le tableau des matchs
#define idx16eFinale 96                                                                           // idx du début des 16e de finale dans le tableau des matchs
#define idx8eFinale 112                                                                           // idx du début des 8e de finale dans le tableau des matchs
#define idxQuartFinale 120                                                                        // idx du début des quarts de finale dans le tableau des matchs
#define idxDemiFinale 124                                                                         // idx du début des demi-finale dans le tableau des matchs
#define idxFinale 126                                                                             // idx de la finale dans le tableau des matchs

#define nbPoints64eFinale 10                                                                        // Nombre de points accordé à une perdante en 64e de finale
#define nbPoints32eFinale 45                                                                        // Nombre de points accordé à une perdante en 32e de finale
#define nbPoints16eFinale 90                                                                        // Nombre de points accordé à une perdante en 16e de finale
#define nbPoints8eFinale 180                                                                        // Nombre de points accordé à une perdante en 8e de finale
#define nbPointsQuartFinale 360                                                                     // Nombre de points accordé à une perdante en quart de finale
#define nbPointsDemiFinale 720                                                                      // Nombre de points accordé à une perdante en demi finale
#define nbPointsFinale 1200                                                                         // Nombre de points accordé à une perdante en finale
#define nbPointsChampionne 2000                                                                     // Nombre de points accordé à une gagnante d'un tournoi

// Définition du type Joueuse
typedef struct{
    unsigned char nomJoueuse[lgMot+1];                                                              // Nom de la joueuse
    unsigned int pointsCummules;                                                                    // Nombre points cummulés
}Joueuse;

// Définition du type Match
typedef struct{
    unsigned int idxGagnante;                                                                       // idx de la gagnante
    unsigned int idxPerdante;                                                                       // idx de la perdante
}Match;

// Définition du type Tournoi
typedef struct{
    char nomTournoi[lgMot+1];                                                                       // Nom du tournoi
    char dateTournoi[lgMot+1];                                                                      // Date du tournoi
    Match dataMatch[nbMatchTournoi];                                                                // Tableau des 127 matchs
}Tournoi;

// Définition du type TournoisWTA
typedef struct{
    Tournoi dataTournois[maxTournois];                                                              // Tableau de l'ensemble des matchs pour un tournoi
    Joueuse dataJoueuses[maxTournois*nbJoueusesTournoi];                                            // Tableau de l'ensemble des jouseuses, tout tournois confondus
    unsigned int nbTournois;                                                                        // Nombre de tournois définis
    unsigned int idxT;                                                                              // idx du tounoi "actuel" sur lequel on travaille
    unsigned int idxJ;                                                                              // idx de la joueuse "actuelle" sur laquelle on travaille
}TournoisWTA;


// Déclaration de fonctions
void definir_nombre_tournois(TournoisWTA *);
void enregistrement_tournoi(TournoisWTA *);
void affichage_matchs_tournoi(const TournoisWTA *);


int main() {

    // Initialisation de quelques variables :
    TournoisWTA listeTournois;                                                                      // Variable contenant... tout
    listeTournois.idxT = 0;                                                                         // L'idx du tournoi "actuel" est par défaut à zéro
    listeTournois.idxJ = 0;                                                                         // L'idx de la joueuse "actuelle" est par défaut à zéro
    char* mot[lgMot+1];                                                                             // Chaîne de caractères (mot) de taille max lgMot (+1 pour le \0) contenant la commande

    while (1) {

        // Entrée de la commande
        scanf("%s", &mot);

        // Si la commande rentrée est "definir_nombre_tournois" :
        if (strcmp(mot, "definir_nombre_tournois") == 0) {
            definir_nombre_tournois(&listeTournois);
        }

        // Si la commande rentrée est "enregistrement_tournoi" :
        else if (strcmp(mot, "enregistrement_tournoi") == 0) {
            enregistrement_tournoi(&listeTournois);
        }

        // Si la commande rentrée est "affichage_matchs_tournoi" :
        else if (strcmp(mot, "affichage_matchs_tournoi") == 0) {
            affichage_matchs_tournoi(&listeTournois);
        }

        // Si la commande rentrée est "exit" :
        else if (strcmp(mot, "exit") == 0) {
            exit(0);
        }
    }

    // Fin du programme
    system("pause");
    return 0;
}


// Fonction de définition du nombre de tournoi dans la compétition
void definir_nombre_tournois(TournoisWTA* listeTournois) {
    scanf("%d", &listeTournois->nbTournois);
}

// Fonction d'enregistrement d'un tournoi, identifiable par son nom et sa date
void enregistrement_tournoi(TournoisWTA* listeTournois) {

    unsigned int idxT = listeTournois->idxT;

    scanf("%s", &listeTournois->dataTournois[idxT].nomTournoi);
    scanf("%s", &listeTournois->dataTournois[idxT].dateTournoi);

    unsigned int idxGagnante;
    unsigned int idxPerdante;

    for (unsigned int i = 0; i < idx32eFinale; i++) {

        idxGagnante = idxT * nbJoueusesTournoi + i * 2;
        idxPerdante = idxT * nbJoueusesTournoi + i * 2 + 1;

        scanf("%s", &listeTournois->dataJoueuses[idxGagnante].nomJoueuse);
        scanf("%s", &listeTournois->dataJoueuses[idxPerdante].nomJoueuse);

        listeTournois->dataTournois[idxT].dataMatch[i].idxGagnante = idxGagnante;
        listeTournois->dataTournois[idxT].dataMatch[i].idxPerdante = idxPerdante;

        listeTournois->dataJoueuses[idxPerdante].pointsCummules = nbPoints64eFinale;
    }

    char nomGagnante[lgMot+1];
    char nomPerdante[lgMot+1];

    for (unsigned int i = idx32eFinale; i < nbMatchTournoi; i++) {

        scanf("%s", &nomGagnante);
        scanf("%s", &nomPerdante);

        unsigned int idxRecuperes = 0;

        for (unsigned int idxJoueuse = idxT * nbJoueusesTournoi; idxJoueuse < (idxT + 1) * nbJoueusesTournoi; idxJoueuse++) {

            if (strcmp(nomGagnante, listeTournois->dataJoueuses[idxJoueuse].nomJoueuse) == 0) {
                idxGagnante = idxJoueuse;
                idxRecuperes++;
            }

            else if (strcmp(nomPerdante, listeTournois->dataJoueuses[idxJoueuse].nomJoueuse) == 0) {
                idxPerdante = idxJoueuse;
                idxRecuperes++;
            }

            if (idxRecuperes == 2) {
                break;
            }
        }

        listeTournois->dataTournois[idxT].dataMatch[i].idxGagnante = idxGagnante;
        listeTournois->dataTournois[idxT].dataMatch[i].idxPerdante = idxPerdante;

        if (idx32eFinale <= i && i < idx16eFinale) {
            listeTournois->dataJoueuses[idxPerdante].pointsCummules = nbPoints32eFinale;
        }

        else if (idx16eFinale <= i && i < idx8eFinale) {
            listeTournois->dataJoueuses[idxPerdante].pointsCummules = nbPoints16eFinale;
        }

        else if (idx8eFinale <= i && i < idxQuartFinale) {
            listeTournois->dataJoueuses[idxPerdante].pointsCummules = nbPoints8eFinale;
        }

        else if (idxQuartFinale <= i && i < idxDemiFinale) {
            listeTournois->dataJoueuses[idxPerdante].pointsCummules = nbPointsQuartFinale;
        }

        else if (idxDemiFinale <= i && i < idxFinale) {
            listeTournois->dataJoueuses[idxPerdante].pointsCummules = nbPointsDemiFinale;
        }

        else {
            listeTournois->dataJoueuses[idxPerdante].pointsCummules = nbPointsFinale;
            listeTournois->dataJoueuses[idxGagnante].pointsCummules = nbPointsChampionne;
        }
    }
    listeTournois->idxT++;
    listeTournois->idxJ += nbJoueusesTournoi;
}

// Fonction d'affichage des participantes pour chaque match d'un tournoi
void affichage_matchs_tournoi(const TournoisWTA* listeTournois) {
    char nom[lgMot+1];
    char date[lgMot+1];

    scanf("%s", nom);
    scanf("%s", date);

    unsigned int testTournoiInconnu = 1;                                                            // Passe à zéro si le tournoi est connu

    for (unsigned int i = 0; i < listeTournois->idxT; i++) {
        if (strcmp(listeTournois->dataTournois[i].nomTournoi, nom) == 0 && strcmp(listeTournois->dataTournois[i].dateTournoi, date) == 0) {
            testTournoiInconnu = 0;                                                                 // Suppression de l'ordre d'afficher "tournoi inconnu"
            printf("%s %s\n", nom, date);                                                           // Affiche le nom et la date du tournoi
            unsigned int idxGagnante;
            unsigned int idxPerdante;

            for (int j = 0; j < nbMatchTournoi; j++) {
                switch (j) {
                    case idx64eFinale:    printf("64emes de finale\n");   break;
                    case idx32eFinale:    printf("32emes de finale\n");   break;
                    case idx16eFinale:    printf("16emes de finale\n");   break;
                    case idx8eFinale:     printf("8emes de finale\n");    break;
                    case idxQuartFinale:  printf("quarts de finale\n");   break;
                    case idxDemiFinale:   printf("demi-finales\n");       break;
                    case idxFinale:       printf("finale\n");             break;
                }

                idxGagnante = listeTournois->dataTournois[i].dataMatch[j].idxGagnante;
                idxPerdante = listeTournois->dataTournois[i].dataMatch[j].idxPerdante;
                printf("%s %s\n", listeTournois->dataJoueuses[idxGagnante].nomJoueuse, listeTournois->dataJoueuses[idxPerdante].nomJoueuse);

            }
            break;
        }
    }
    if (testTournoiInconnu == 1) {
        printf("tournoi inconnu\n");
    }
}
