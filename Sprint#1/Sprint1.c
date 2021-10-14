#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define maxTournois 10                                      // nb maximum de tournois
#define nbMatchTournoi 127                                  // nb de matchs par tournois
#define nbJoueusesTournoi 128                               // nb joueuses par tournois
#define lgMot 30                                            // nb de caractères max

#define index64efinale 0                                    // Index du début des 64e de finales dans le tableau des matchs
#define index32efinale 64                                   // Index du début des 32e de finales dans le tableau des matchs
#define index16efinale 96                                   // Index du début des 16e de finales dans le tableau des matchs
#define index8efinale 112                                   // Index du début des 8e de finales dans le tableau des matchs
#define index4efinale 120                                   // Index du début des 4e de finales dans le tableau des matchs
#define indexdemifinale 124                                 // Index du début des demi-finales dans le tableau des matchs
#define indexfinale 126                                     // Index de la finale dans le tableau des matchs

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
}TournoisWTA;


// Déclarations et initialisations de quelques varables :
int nbTournois;                                             // Nombre de tournois
unsigned int numeroTournoi = 0;                             // Index du tournoi sur lequel on travaille actuellement
char *mot[lgMot+1];                                         // Chaîne de caractères (mot) de taille max lgMot contenant la commande
TournoisWTA TournoiWTA;                                     // Variable contenant... tout


int main(){
    
    // Définition du fichier de sortie
    FILE* fichier = NULL;
    fichier = fopen("run.txt", "w");
    
    while (1){

        // Entrée de la commande
        scanf("%s", &mot);

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
            affichage_matchs_tournoi();
        }
    
        // Si la commande rentrée est "exit" :
        else if (strcmp(mot, "exit") == 0) {
            exit(0);
        }
    }

    // Fermeture du fichier, fin du programme
    fclose(fichier);
    system("pause");
    return 0;
}


// Fonction de définition du nombre de tournoi dans la compétition
void definir_nombre_tournois(){
    scanf("%d", &nbTournois);
}

// Fonction d'enregistrement d'un tournoi, identifiable par son nom et sa date
void enregistrement_tournoi(){

    // Le nom et la date du tournoi sont notés directement dans l'index de la variable dataTournois correspondante
    scanf("%s", &TournoiWTA.dataTournois[numeroTournoi].nomTournoi);
    scanf("%s", &TournoiWTA.dataTournois[numeroTournoi].dateTournoi);
    
    // L'index du match actuel est noté
    unsigned int i = 0;

    // Pour les 64 premiers matchs (64èmes de finales) :
    for (; i<index32efinale; i++){

        // Les noms des joueuses sont directement inscrites dans nomJoueuses, car c'est la première fois qu'on a les noms
        scanf("%s", &TournoiWTA.dataJoueuses[numeroTournoi*nbMatchTournoi + i*2].nomJoueuse);
        scanf("%s", &TournoiWTA.dataJoueuses[numeroTournoi*nbMatchTournoi + i*2 + 1].nomJoueuse);

        // L'index des joueuse par match est simple pour les 64e : l'ordre est respecté
        TournoiWTA.dataTournois[numeroTournoi].dataMatch[i].idxGagnante = i*2;
        TournoiWTA.dataTournois[numeroTournoi].dataMatch[i].idxPerdante = i*2+1;

        // Les perdants des 64e sont incrémentés de 10 points, car elles ont terminé la compétition
        TournoiWTA.dataJoueuses[numeroTournoi*nbMatchTournoi + i*2+1].pointsCummules = 10;
    }
    
    // Des variables de transition contenant les futurs noms des participantes des prochains matchs
    char nomGagnante[lgMot];
    char nomPerdante[lgMot];
    
    // Des variables de transition contenant l'index des joueuses pour les prochains matchs sont crés
    unsigned int indexGagnante;
    unsigned int indexPerdante;

    // Une variable de fin de boucle for est également crée
    unsigned int indexRecuperes;
    for (; i<nbMatchTournoi; i++){

        // Les noms des participantes au match sont notés
        scanf("%s", &nomGagnante);
        scanf("%s", &nomPerdante);
        
        // Vérifie si les 2 index ont été récupérés
        unsigned int indexRecuperes = 0;

        // Afin de trouver l'index de ces noms, on fait un balayage de la liste de joueuse dans la partie du tournoi actuel
        for (unsigned int indexJoueuse=numeroTournoi*nbJoueusesTournoi; indexJoueuse<(numeroTournoi+1)*(nbJoueusesTournoi-1); indexJoueuse++){

            // Si c'est le nom de la joueuse gagnante qui est trouvé, son index est noté
            if (strcmp(nomGagnante, TournoiWTA.dataJoueuses[indexJoueuse].nomJoueuse) == 0){
                indexGagnante = indexJoueuse;
                indexRecuperes++;
            }

            // Sinon, si c'est le nom de la joueuse perdante, il est lui aussi noté
            else if (strcmp(nomPerdante, TournoiWTA.dataJoueuses[indexJoueuse].nomJoueuse) == 0){
                indexPerdante = indexJoueuse;
                indexRecuperes++;
            }

            // Dès que les deux index dont récupérés, on sort de la boucle
            if (indexRecuperes == 2){
                break;
            }
        }
        
        // Les index des joueuses sont ajoutés aux matchs correspondant
        TournoiWTA.dataTournois[numeroTournoi].dataMatch[i].idxGagnante = indexGagnante;
        TournoiWTA.dataTournois[numeroTournoi].dataMatch[i].idxPerdante = indexPerdante;
        
        // Pour les 32 matchs suivants (32e de finale), les perdantes recoivent leurs 45 points
        if (index32efinale <= i && i <= index16efinale){
            TournoiWTA.dataJoueuses[indexPerdante].pointsCummules = 45;
        }
    
        // Pour les 16 matchs suivants (16e de finale), les perdantes recoivent leurs 90 points
        else if (index16efinale <= i && i <= index8efinale){
            TournoiWTA.dataJoueuses[indexPerdante].pointsCummules = 90;
        }

        // Pour les 8 matchs suivants (8e de finale), les perdantes recoivent 180 points
        else if (index8efinale <= i && i <= index4efinale){
            TournoiWTA.dataJoueuses[indexPerdante].pointsCummules = 180;
        }

        // Pour les 4 matchs suivants (quarts de finale), les perdantes recoivent 360 points
        else if (index4efinale <= i && i <= indexdemifinale){
            TournoiWTA.dataJoueuses[indexPerdante].pointsCummules = 360;
        }
        
        // Pour les 2 matchs suivants (demi-finale), les perdantes recoivent 720 points
        else if (indexdemifinale <= i && i <= indexfinale){
            TournoiWTA.dataJoueuses[indexPerdante].pointsCummules = 720;
        }

        // Pour le dernier match (finale), la perdante recoit 1 200 points et la gagnante 2 000 points
        else {
            TournoiWTA.dataJoueuses[indexPerdante].pointsCummules = 1200;
            TournoiWTA.dataJoueuses[indexGagnante].pointsCummules = 2000;
        }
    }
    
    // numeroTournoi est incrémenté. Ainsi, un prochain appel de la fonction n'écrasera pas les données des tournois précédants
    numeroTournoi++;
}

// Fonction d'affichage des participantes pour chaque match d'un tournoi
void affichage_matchs_tournoi(){
    
    char nom[lgMot];
    char date[lgMot];

    scanf("%s", nom);
    scanf("%s", date);

    // Reste à zéro si le tournoi est inconnu
    unsigned int test_tournois_inconnus = 1;
    
    for (int i=0; i<numeroTournoi; i++){
        if (strcmp(TournoiWTA.dataTournois[i].nomTournoi, nom) == 0 && strcmp(TournoiWTA.dataTournois[i].dateTournoi, date) == 0){
            test_tournois_inconnus = 0;
            printf("%s %s\n", nom, date);

            for (int j=0; j < nbMatchTournoi; j++){
                switch (j){
                    case index64efinale  : printf("64emes de finale\n"); break;
                    case index32efinale  : printf("32emes de finale\n"); break;
                    case index16efinale  : printf("16emes de finale\n"); break;
                    case index8efinale   : printf("8emes de finale\n"); break;
                    case index4efinale   : printf("quarts de finale\n"); break;
                    case indexdemifinale : printf("demi-finales\n"); break;
                    case indexfinale     : printf("finale\n"); break;
                }
                printf("%s %s\n", TournoiWTA.dataJoueuses[TournoiWTA.dataTournois[i].dataMatch[j].idxGagnante].nomJoueuse, TournoiWTA.dataJoueuses[TournoiWTA.dataTournois[i].dataMatch[j].idxPerdante].nomJoueuse);
            }
        }
    }
    if (test_tournois_inconnus == 1){
        printf("Tournois Inconnus/n");
    }
 }
