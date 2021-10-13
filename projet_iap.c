#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define maxTournois 10                                      // nb maximum de tournois
#define nbMatchTournoi 127                                  // nb de matchs par tournois
#define nbJoueusesTournoi 128                               // nb joueuses par tournois
#define lgMot 30                                            // nb de caractères max


// Définition du type Joueuse
typedef struct{
    unsigned char nomJoueuse;                               // Nom de la joueuse
    int pointsCummules;                                     // nb points cummulés
}Joueuse;

// Définition du type Match
typedef struct{
    unsigned int idxGagnante;                               // Index de la gagnante
    unsigned int idxPerdante;                               // Index de la perdante
}Match;

// Définition du type Tournoi
typedef struct{
    char *nomTournoi[lgMot];                                // Nom du tournoi
    char *dateTournoi[lgMot];                               // Date du tournoi
    Match *dataMatch[nbMatchTournoi];                       // Tableau des 127 matchs
}Tournoi;

// Définition du type TournoisWTA
typedef struct{
    Tournoi *dataTournois[maxTournois];                     // Tableau de l'ensemble des matchs pour un tournoi
    Joueuse *dataJoueuses[maxTournois*nbJoueusesTournoi];   // Tableau de l'ensemble des jouseuses, tout tournois confondus
}TournoisWTA;


// Déclarations et initialisations de quelques varables :
int nbTournois;                                             // Déclaration du nombre de tournois
unsigned int numeroTournoi = 0;                             // Initialisation de l'index du tournoi "actuel" à définir
char *mot[lgMot+1];                                         // Chaîne de caractères (mot) de taille max lgMot contenant la commande
TournoisWTA *TournoiWTA;                                    // Déclaration de la variable contenant... tout


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
            //affichage_match_tournoi();
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
    scanf("%s", &TournoiWTA->dataTournois[numeroTournoi]->nomTournoi);
    scanf("%s", &TournoiWTA->dataTournois[numeroTournoi]->dateTournoi);
    
    // numeroTournoi est incrémenté. Ainsi, un prochain appel de la fonction n'écrasera pas les données des tournois précédants
    numeroTournoi++;
    
    // L'index du match actuel est noté
    unsigned int i = 0;

    // Pour les 64 premiers matchs (64èmes de finales) :
    for (; i<64; i++){

        // Les noms des joueuses sont directement inscrites dans nomJoueuses, car c'est la première fois qu'on a les noms
        scanf("%s", &TournoiWTA->dataJoueuses[numeroTournoi*nbMatchTournoi + i*2]->nomJoueuse);
        scanf("%s", &TournoiWTA->dataJoueuses[numeroTournoi*nbMatchTournoi + i*2 + 1]->nomJoueuse);

        // L'index des joueuse par match est simple pour les 64e : l'ordre est respecté
        TournoiWTA->dataTournois[numeroTournoi]->dataMatch[i]->idxGagnante = i*2;
        TournoiWTA->dataTournois[numeroTournoi]->dataMatch[i]->idxPerdante = i*2+1;

        // Les perdants des 64e sont incrémentés de 10 points, car elles ont terminé la compétition
        TournoiWTA->dataJoueuses[numeroTournoi*nbMatchTournoi + i*2+1]->pointsCummules += 10;
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
        
        unsigned int indexRecuperes = 0;

        // Afin de trouver l'index de ces noms, on fait un balayage de la liste de joueuse
        for (unsigned int j=0; j<nbJoueusesTournoi; i++){

            // Si c'est le nom de la joueuse gagnante qui est trouvé, son index est noté
            if (nomGagnante == TournoiWTA->dataJoueuses[numeroTournoi*nbMatchTournoi + j]){
                indexGagnante = TournoiWTA->dataJoueuses[numeroTournoi*nbMatchTournoi + j];
                indexRecuperes++;
            }

            // Sinon, si c'est le nom de la joueuse perdante, il est lui aussi noté
            else if (nomPerdante == TournoiWTA->dataJoueuses[numeroTournoi*nbMatchTournoi + j]) {
                indexPerdante = TournoiWTA->dataJoueuses[numeroTournoi*nbMatchTournoi + j];
                indexRecuperes++;
            }

            // Dès que les deux index dont récupérés, on sort de la boucle
            if (indexRecuperes == 2){
                break;
            }
        }
        
        // Les index des joueuses sont ajoutés aux matchs correspondant
        TournoiWTA->dataTournois[numeroTournoi]->dataMatch[i]->idxGagnante = indexGagnante;
        TournoiWTA->dataTournois[numeroTournoi]->dataMatch[i]->idxPerdante = indexPerdante;

        // Pour les 32 matchs suivants (32e de finale), les perdantes recoivent leurs 45 points
        if (64 <= i && i <= 64+32){
            TournoiWTA->dataJoueuses[indexPerdante]->pointsCummules += 45;
        }

        // Pour les 16 matchs suivants (16e de finale), les perdantes recoivent leurs 90 points
        else if (64+32 <= i && i <= 64+32+16){
            TournoiWTA->dataJoueuses[indexPerdante]->pointsCummules += 90;
        }

        // Pour les 8 matchs suivants (8e de finale), les perdantes recoivent 180 points
        else if (64+32+16 <= i && i <= 64+32+16+8){
            TournoiWTA->dataJoueuses[indexPerdante]->pointsCummules += 180;
        }

        // Pour les 4 matchs suivants (quarts de finale), les perdantes recoivent 360 points
        else if (64+32+16+8 <= i && i <= 64+32+16+8+4){
            TournoiWTA->dataJoueuses[indexPerdante]->pointsCummules += 360;
        }
        
        // Pour les 2 matchs suivants (demi-finale), les perdantes recoivent 720 points
        else if (64+32+16+8+4 <= i && i <= 64+32+16+8+4+2){
            TournoiWTA->dataJoueuses[indexPerdante]->pointsCummules += 720;
        }

        // Pour le dernier match (finale), la perdante recoit 1 200 points et la gagnante 2 000 points
        else {
            TournoiWTA->dataJoueuses[indexPerdante]->pointsCummules += 1200;
            TournoiWTA->dataJoueuses[indexGagnante]->pointsCummules += 2000;
        }
    }
}

// Fonction d'affichage des participantes pour chaque match d'un tournoi
void affichage_match_tournoi(){
    
    char nom[lgMot];
    char date[lgMot];
    
    for(int i=0; i<maxTournois; i++){
        if (TournoiWTA->dataTournois[i]->nomTournoi == nom && TournoiWTA->dataTournois[i]->dateTournoi == date ){
            printf("%s %s", nom, date);
            for(int j=0; j < nbMatchTournoi; j++){
                    printf("%s %s",  TournoiWTA->dataJoueuses[i]->nomJoueuse == nom && TournoiWTA->dataTournois[i]->dateTournoi == date );        
            }
        }
    }
}