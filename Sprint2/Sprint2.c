#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#pragma warning (disable:4996)

#define maxTournois 10                                      // nb maximum de tournois
#define nbMatchTournoi 127                                  // nb de matchs par tournois
#define nbJoueusesTournoi 128                               // nb joueuses par tournois
#define lgMot 30                                            // nb de caractères max

#define index64eFinale 0                                    // Index du début des 64e de finale dans le tableau des matchs
#define index32eFinale 64                                   // Index du début des 32e de finale dans le tableau des matchs
#define index16eFinale 96                                   // Index du début des 16e de finale dans le tableau des matchs
#define index8eFinale 112                                   // Index du début des 8e de finale dans le tableau des matchs
#define indexQuartFinale 120                                // Index du début des quarts de finale dans le tableau des matchs
#define indexDemiFinale 124                                 // Index du début des demi-finale dans le tableau des matchs
#define indexFinale 126                                     // Index de la finale dans le tableau des matchs

#define nbPoints64eFinale 10                                // nb de points accordé à une perdante en 64e de finale
#define nbPoints32eFinale 45                                // nb de points accordé à une perdante en 32e de finale
#define nbPoints16eFinale 90                                // nb de points accordé à une perdante en 16e de finale
#define nbPoints8eFinale 180                                // nb de points accordé à une perdante en 8e de finale
#define nbPointsQuartFinale 360                             // nb de points accordé à une perdante en quart de finale
#define nbPointsDemiFinale 720                              // nb de points accordé à une perdante en demi finale
#define nbPointsFinale 1200                                 // nb de points accordé à une perdante en finale
#define nbPointsChampionne 2000                             // nb de points accordé à une gagnante d'un tournoi

// Définition du type Joueuse
typedef struct{
    unsigned char nomJoueuse[lgMot];                        // Nom de la joueuse
    unsigned int pointsCummules;                            // nb points cummulés
}Joueuse;

// Définition du type Match
typedef struct{
    unsigned int idxGagnante;                               // Index de la gagnante
    unsigned int idxPerdante;                               // Index de la perdante
}Match;

// Définition du type Tournoi
typedef struct{
    char nomTournoi[lgMot];                                 // Nom du tournoi
    char dateTournoi[lgMot];                                // Date du tournoi
    Match dataMatch[nbMatchTournoi];                        // Tableau des 127 matchs
}Tournoi;

// Définition du type TournoisWTA
typedef struct{
    Tournoi dataTournois[maxTournois];                      // Tableau de l'ensemble des matchs pour un tournoi
    Joueuse dataJoueuses[maxTournois*nbJoueusesTournoi];    // Tableau de l'ensemble des jouseuses, tout tournois confondus
    unsigned int nbTournois;                                // Nombre de tournois définis
    unsigned int idxT;                                      // Index du tounoi "actuel" sur lequel on travaille
    unsigned int idxJ;                                      // Index de la joueuse "actuelle" sur laquelle on travaille
}TournoisWTA;


// Fonction de définition du nombre de tournoi dans la compétition
void definir_nombre_tournois(TournoisWTA *listeTournois){
    scanf("%d", &listeTournois->nbTournois);
}

// Fonction d'enregistrement d'un tournoi, identifiable par son nom et sa date
void enregistrement_tournoi(TournoisWTA *listeTournois){

    // Le nom et la date du tournoi sont notés directement dans l'index de la variable dataTournois correspondante
    scanf("%s", &listeTournois->dataTournois[listeTournois->idxT].nomTournoi);
    scanf("%s", &listeTournois->dataTournois[listeTournois->idxT].dateTournoi);
    
    // L'index du match actuel est noté
    unsigned int i = 0;

    // Pour les 64 premiers matchs (64èmes de finale) :
    for (; i<index32eFinale; i++){

        // Les noms des joueuses sont directement inscrites dans nomJoueuses, car c'est la première fois qu'on a les noms
        /*  Note : listeTournois->idxT*nbMatchTournoi pour se trouver dans la bonne partie des index contenant le tournoi actuel,
        auquel on ajoute i*2 pour toucher les gagnantes, car elles sont toujours avant les perdantes dans la définition d'un match,
        (et ont donc un index paire), et i*2+1 pour les perdantes. Ainsi, les 2 joueuses d'un même match sont traitées en même temps*/
        scanf("%s", &listeTournois->dataJoueuses[listeTournois->idxT*nbMatchTournoi + i*2].nomJoueuse);
        scanf("%s", &listeTournois->dataJoueuses[listeTournois->idxT*nbMatchTournoi + i*2+1].nomJoueuse);

        // L'index des joueuses par match est simple pour les 64e : l'ordre est égal à l'ordre de rentrée des joueuses par match
        listeTournois->dataTournois[listeTournois->idxT].dataMatch[i].idxGagnante = i*2;
        listeTournois->dataTournois[listeTournois->idxT].dataMatch[i].idxPerdante = i*2+1;

        // Les perdants des 64e sont incrémentés de 10 points, car elles ont terminé la compétition (pas de points supplémentaires à gagner)
        listeTournois->dataJoueuses[listeTournois->idxT*nbMatchTournoi + i*2+1].pointsCummules = nbPoints64eFinale;
    }
    
    // Des variables de transition contenant les futurs noms des participantes des prochains matchs sont créées
    char nomGagnante[lgMot];
    char nomPerdante[lgMot];
    
    // Des variables de transition contenant l'index des joueuses pour les prochains matchs sont créées
    unsigned int indexGagnante;
    unsigned int indexPerdante;

    for (; i<nbMatchTournoi; i++){

        // Les noms des participantes au match sont notées
        scanf("%s", &nomGagnante);
        scanf("%s", &nomPerdante);
        
        // Vérifie si les 2 index ont été récupérés
        unsigned int indexRecuperes = 0;

        // Afin de trouver l'index de ces noms, on fait un balayage de la liste de joueuse dans la partie du tournoi actuel
        for (unsigned int indexJoueuse=listeTournois->idxT*nbJoueusesTournoi; indexJoueuse<(listeTournois->idxT+1)*(nbJoueusesTournoi-1); indexJoueuse++){

            // Si c'est le nom de la joueuse gagnante qui est trouvé, son index est noté dans sa variable attribuée
            if (strcmp(nomGagnante, listeTournois->dataJoueuses[indexJoueuse].nomJoueuse) == 0){
                indexGagnante = indexJoueuse;
                indexRecuperes++;
            }

            // Sinon, si c'est le nom de la joueuse perdante, il est lui aussi noté dans sa variable attribuée
            else if (strcmp(nomPerdante, listeTournois->dataJoueuses[indexJoueuse].nomJoueuse) == 0){
                indexPerdante = indexJoueuse;
                indexRecuperes++;
            }

            // Dès que les deux index sont récupérés, on sort de la boucle
            if (indexRecuperes == 2){
                break;
            }
        }
        
        // Les index des joueuses sont ajoutés aux matchs correspondants
        listeTournois->dataTournois[listeTournois->idxT].dataMatch[i].idxGagnante = indexGagnante;
        listeTournois->dataTournois[listeTournois->idxT].dataMatch[i].idxPerdante = indexPerdante;
        
        // Pour les 32 matchs suivants (32e de finale), les perdantes recoivent leurs 45 points
        if (index32eFinale <= i && i <= index16eFinale){
            listeTournois->dataJoueuses[indexPerdante].pointsCummules = nbPoints32eFinale;
        }
    
        // Pour les 16 matchs suivants (16e de finale), les perdantes recoivent leurs 90 points
        else if (index16eFinale <= i && i <= index8eFinale){
            listeTournois->dataJoueuses[indexPerdante].pointsCummules = nbPoints16eFinale;
        }

        // Pour les 8 matchs suivants (8e de finale), les perdantes recoivent leurs 180 points
        else if (index8eFinale <= i && i <= indexQuartFinale){
            listeTournois->dataJoueuses[indexPerdante].pointsCummules = nbPoints8eFinale;
        }

        // Pour les 4 matchs suivants (quarts de finale), les perdantes recoivent leurs 360 points
        else if (indexQuartFinale <= i && i <= indexDemiFinale){
            listeTournois->dataJoueuses[indexPerdante].pointsCummules = nbPointsQuartFinale;
        }
        
        // Pour les 2 matchs suivants (demi-finale), les perdantes recoivent leurs 720 points
        else if (indexDemiFinale <= i && i <= indexFinale){
            listeTournois->dataJoueuses[indexPerdante].pointsCummules = nbPointsDemiFinale;
        }

        // Pour le dernier match (finale), la perdante recoit ses 1 200 points et la gagnante ses 2 000 points
        else {
            listeTournois->dataJoueuses[indexPerdante].pointsCummules = nbPointsFinale;
            listeTournois->dataJoueuses[indexGagnante].pointsCummules = nbPointsChampionne;
        }
    }
    // idxT est incrémenté. Ainsi, un prochain appel de la fonction n'écrasera pas les données des tournois précédants
    listeTournois->idxT++;
}

// Fonction d'affichage des participantes pour chaque match d'un tournoi
void affichage_matchs_tournoi(const TournoisWTA *listeTournois){
    
    char nom[lgMot];
    char date[lgMot];

    scanf("%s", nom);
    scanf("%s", date);

    unsigned int testTournoiInconnu = 1;                    // Passe à zéro si le tournoi est connu
    
    for (unsigned int i=0; i<listeTournois->idxT; i++){
        // Si le nom et la date correspondent pour un même tounoi, alors il ne peut s'agir (en théorie) que de celui-ci :
        if (strcmp(listeTournois->dataTournois[i].nomTournoi, nom) == 0 && strcmp(listeTournois->dataTournois[i].dateTournoi, date) == 0){

            testTournoiInconnu = 0;                         // Suppression de l'ordre d'afficher "tournoi inconnu" 
            printf("%s %s\n", nom, date);                   // Affiche le nom et la date du tournoi

            // Création de variables d'index des joueuses, afin de faciliter la compréhension de la lecture du printf :
            unsigned int indexGagnante;
            unsigned int indexPerdante;

            for (int j=0; j<nbMatchTournoi; j++){
                // Si l'index du match correspond au début des 64e, 32e, etc, alors afficher 64emes de finales, etc
                switch (j){
                    case index64eFinale   : printf("64emes de finale\n"); break;
                    case index32eFinale   : printf("32emes de finale\n"); break;
                    case index16eFinale   : printf("16emes de finale\n"); break;
                    case index8eFinale    : printf("8emes de finale\n"); break;
                    case indexQuartFinale : printf("quarts de finale\n"); break;
                    case indexDemiFinale  : printf("demi-finales\n"); break;
                    case indexFinale      : printf("finale\n"); break;
                }
                indexGagnante = listeTournois->dataTournois[i].dataMatch[j].idxGagnante;
                indexPerdante = listeTournois->dataTournois[i].dataMatch[j].idxPerdante;

                printf("%s %s\n", listeTournois->dataJoueuses[indexGagnante].nomJoueuse, listeTournois->dataJoueuses[indexPerdante].nomJoueuse);
            }
        }
    }
    // Si le tournoi n'a pas été trouvé, alors afficher "tournoi inconnu" :
    if (testTournoiInconnu == 1){
        printf("tournoi inconnu\n");
    }
}

// Fonction d'affichage des matchs d'une participante donnée d'un tournoi donné
void afficher_matchs_joueuse(const TournoisWTA *listeTournois){
    
    char nomTournoi[lgMot];
    char dateTournoi[lgMot];
    char nomJoueuse[lgMot];

    scanf("%s", &nomTournoi);
    scanf("%s", &dateTournoi);
    scanf("%s", &nomJoueuse);

    unsigned int testTournoiInconnu = 1;                        // Passe à zéro si le tournoi est connu
    unsigned int testJoueuseInconnue = 1;                       // Passe à zéro si la joueuse est connue
    
    unsigned int numeroTournoi = 0;

    for (unsigned int i=0; i<listeTournois->idxT; numeroTournoi++){
        if (strcmp(listeTournois->dataTournois[i].nomTournoi, nomTournoi) == 0 && strcmp(listeTournois->dataTournois[i].dateTournoi, dateTournoi) == 0){
            testTournoiInconnu = 0;
            numeroTournoi = i;
            break;
        }
    }

    for (unsigned int i=0; i<nbJoueusesTournoi*listeTournois->nbTournois; i++){
        if (strcmp(listeTournois->dataJoueuses[i].nomJoueuse, nomJoueuse) == 0){
            testJoueuseInconnue = 0;
            for (unsigned int j=0; j<nbMatchTournoi; j++){
                if (listeTournois->dataTournois[numeroTournoi].dataMatch[j].idxGagnante == i || listeTournois->dataTournois[numeroTournoi].dataMatch[j].idxPerdante == i){                   
                    unsigned int indexGagnante = listeTournois->dataTournois[numeroTournoi].dataMatch[j].idxGagnante;
                    unsigned int indexPerdante = listeTournois->dataTournois[numeroTournoi].dataMatch[j].idxPerdante;
                    printf("%s %s\n", listeTournois->dataJoueuses[indexGagnante].nomJoueuse, listeTournois->dataJoueuses[indexPerdante].nomJoueuse); 
                }
            }
            break;
        }
    }
    // Si le tournoi n'a pas été trouvé, alors afficher "tournoi inconnu" :
    if (testTournoiInconnu == 1){
        printf("tournoi inconnu\n");
    }

    // Si la joueuse n'a pas été trouvée, alors afficher "joueuse inconnu" :
    if (testJoueuseInconnue == 1){
        printf("joueuse inconnue\n");
    }
}


int main() {

    // Déclarations/initialisations de quelques variables :
    TournoisWTA listeTournois;                              // Variable contenant... tout
    listeTournois.idxT = 0;                                 // L'index du tournoi "actuel" est par défaut à zéro
    listeTournois.idxJ = 0;                                 // L'index de la joueuse "actuelle" est par défaut à zéro
    char* mot[lgMot + 1];                                     // Chaîne de caractères (mot) de taille max lgMot contenant la commande

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

        // Si la commande rentrée est "afficher_matchs_joueuse" :
        else if (strcmp(mot, "afficher_matchs_joueuse") == 0) {
            afficher_matchs_joueuse(&listeTournois);
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
