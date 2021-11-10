#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#pragma warning (disable:4996)

#define maxTournois 10                                                                              // Nombre maximum de tournois
#define nbMatchTournoi 127                                                                          // Nombre de matchs par tournois
#define nbJoueusesTournoi 128                                                                       // Nombre joueuses par tournois
#define lgMot 30                                                                                    // Nombre de caractères max

#define index64eFinale 0                                                                            // Index du début des 64e de finale dans le tableau des matchs
#define index32eFinale 64                                                                           // Index du début des 32e de finale dans le tableau des matchs
#define index16eFinale 96                                                                           // Index du début des 16e de finale dans le tableau des matchs
#define index8eFinale 112                                                                           // Index du début des 8e de finale dans le tableau des matchs
#define indexQuartFinale 120                                                                        // Index du début des quarts de finale dans le tableau des matchs
#define indexDemiFinale 124                                                                         // Index du début des demi-finale dans le tableau des matchs
#define indexFinale 126                                                                             // Index de la finale dans le tableau des matchs

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
    unsigned int nbPoints;                                                                          // Nombre points cummulés
}Joueuse;

// Définition du type Match
typedef struct{
    unsigned int idxGagnante;                                                                       // Index de la gagnante
    unsigned int idxPerdante;                                                                       // Index de la perdante
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
    unsigned int idxT;                                                                              // Index du tounoi "actuel" sur lequel on travaille
    unsigned int idxJ;                                                                              // Index de la joueuse "actuelle" sur laquelle on travaille
}TournoisWTA;


// Déclaration de fonctions
void definir_nombre_tournois(TournoisWTA *);
void enregistrement_tournoi(TournoisWTA *);
void affichage_matchs_tournoi(const TournoisWTA *);
void afficher_matchs_joueuse(const TournoisWTA *);
void affichage_joueuses_tournoi(const TournoisWTA*);


int main(){

    // Initialisation de quelques variables :
    TournoisWTA listeTournois;                                                                      // Variable contenant... tout
    listeTournois.idxT = 0;                                                                         // L'index du tournoi "actuel" est par défaut à zéro
    listeTournois.idxJ = 0;                                                                         // L'index de la joueuse "actuelle" est par défaut à zéro
    char* mot[lgMot+1];                                                                             // Chaîne de caractères (mot) de taille max lgMot (+1 pour le \0) contenant la commande

    while (1){

        // Entrée de la commande
        scanf("%s", &mot);

        // Si la commande rentrée est "definir_nombre_tournois" :
        if (strcmp(mot, "definir_nombre_tournois") == 0){
            definir_nombre_tournois(&listeTournois);
        }

        // Si la commande rentrée est "enregistrement_tournoi" :
        else if (strcmp(mot, "enregistrement_tournoi") == 0){
            enregistrement_tournoi(&listeTournois);
        }

        // Si la commande rentrée est "affichage_matchs_tournoi" :
        else if (strcmp(mot, "affichage_matchs_tournoi") == 0){
            affichage_matchs_tournoi(&listeTournois);
        }

        // Si la commande rentrée est "afficher_matchs_joueuse" :
        else if (strcmp(mot, "afficher_matchs_joueuse") == 0){
            afficher_matchs_joueuse(&listeTournois);
        }

        // Si la commande rentrée est "affichage_joueuses_tournoi"
        else if (strcmp(mot, "affichage_joueuses_tournoi") == 0){
            affichage_joueuses_tournoi(&listeTournois);
        }

        // Si la commande rentrée est "exit" :
        else if (strcmp(mot, "exit") == 0){
            exit(0);
        }
    }

    // Fin du programme
    system("pause");
    return 0;
}


// Fonction de définition du nombre de tournoi dans la compétition
void definir_nombre_tournois(TournoisWTA *listeTournois){
    scanf("%d", &listeTournois->nbTournois);
}

// Fonction d'enregistrement d'un tournoi, identifiable par son nom et sa date
void enregistrement_tournoi(TournoisWTA *listeTournois){

    unsigned int idxT = listeTournois->idxT;

    // Le nom et la date du tournoi sont notés directement dans l'index de la variable dataTournois correspondante
    scanf("%s", &listeTournois->dataTournois[idxT].nomTournoi);
    scanf("%s", &listeTournois->dataTournois[idxT].dateTournoi);

    // Des variables de transition contenant l'index des joueuses pour les prochains matchs sont créées
    unsigned int indexGagnante;
    unsigned int indexPerdante;

    // Pour les 64 premiers matchs (64èmes de finale) :
    for (unsigned int i = 0; i < index32eFinale; i++){

        indexGagnante = idxT * nbJoueusesTournoi + i * 2;
        indexPerdante = idxT * nbJoueusesTournoi + i * 2 + 1;

        // Les noms des joueuses sont directement inscrites dans nomJoueuses, car c'est la première fois qu'on a les noms
        scanf("%s", &listeTournois->dataJoueuses[indexGagnante].nomJoueuse);
        scanf("%s", &listeTournois->dataJoueuses[indexPerdante].nomJoueuse);

        // L'index des joueuses par match est simple pour les 64e : l'ordre est égal à l'ordre de rentrée des joueuses par match
        listeTournois->dataTournois[idxT].dataMatch[i].idxGagnante = indexGagnante;
        listeTournois->dataTournois[idxT].dataMatch[i].idxPerdante = indexPerdante;

        // Les perdants des 64e sont incrémentés de 10 points, car elles ont terminé la compétition (pas de points supplémentaires à gagner)
        listeTournois->dataJoueuses[indexPerdante].nbPoints = nbPoints64eFinale;
    }


    // Des variables de transition contenant les futurs noms des participantes des prochains matchs sont créées
    char nomGagnante[lgMot+1];
    char nomPerdante[lgMot+1];

    for (unsigned int i = index32eFinale; i < nbMatchTournoi; i++){

        // Les noms des participantes au match sont notées
        scanf("%s", &nomGagnante);
        scanf("%s", &nomPerdante);

        // Vérifie si les 2 index ont été récupérés
        unsigned int indexRecuperes = 0;

        // Afin de trouver l'index de ces noms, on fait un balayage de la liste de joueuse dans la partie du tournoi actuel
        for (unsigned int indexJoueuse = idxT * nbJoueusesTournoi; indexJoueuse < (idxT + 1) * nbJoueusesTournoi; indexJoueuse++){

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
        listeTournois->dataTournois[idxT].dataMatch[i].idxGagnante = indexGagnante;
        listeTournois->dataTournois[idxT].dataMatch[i].idxPerdante = indexPerdante;

        // Pour les 32 matchs suivants (32e de finale), les perdantes recoivent leurs 45 points
        if (index32eFinale <= i && i < index16eFinale){
            listeTournois->dataJoueuses[indexPerdante].nbPoints = nbPoints32eFinale;
        }

        // Pour les 16 matchs suivants (16e de finale), les perdantes recoivent leurs 90 points
        else if (index16eFinale <= i && i < index8eFinale){
            listeTournois->dataJoueuses[indexPerdante].nbPoints = nbPoints16eFinale;
        }

        // Pour les 8 matchs suivants (8e de finale), les perdantes recoivent leurs 180 points
        else if (index8eFinale <= i && i < indexQuartFinale){
            listeTournois->dataJoueuses[indexPerdante].nbPoints = nbPoints8eFinale;
        }

        // Pour les 4 matchs suivants (quarts de finale), les perdantes recoivent leurs 360 points
        else if (indexQuartFinale <= i && i < indexDemiFinale){
            listeTournois->dataJoueuses[indexPerdante].nbPoints = nbPointsQuartFinale;
        }

        // Pour les 2 matchs suivants (demi-finale), les perdantes recoivent leurs 720 points
        else if (indexDemiFinale <= i && i < indexFinale){
            listeTournois->dataJoueuses[indexPerdante].nbPoints = nbPointsDemiFinale;
        }

        // Pour le dernier match (finale), la perdante recoit ses 1 200 points et la gagnante ses 2 000 points
        else {
            listeTournois->dataJoueuses[indexPerdante].nbPoints = nbPointsFinale;
            listeTournois->dataJoueuses[indexGagnante].nbPoints = nbPointsChampionne;
        }
    }

    // idxT est incrémenté. Ainsi, un prochain appel de la fonction n'écrasera pas les données des tournois précédants
    listeTournois->idxT++;
}

// Fonction d'affichage des participantes pour chaque match d'un tournoi
void affichage_matchs_tournoi(const TournoisWTA *listeTournois){

    char nom[lgMot+1];
    char date[lgMot+1];

    scanf("%s", nom);
    scanf("%s", date);

    unsigned int testTournoiInconnu = 1;                                                            // Passe à zéro si le tournoi est connu

    // Balayage de la liste des tournois
    for (unsigned int i = 0; i < listeTournois->idxT; i++){

        // Si le nom et la date correspondent pour un même tounoi, alors il ne peut s'agir (en théorie) que de celui-ci :
        if (strcmp(listeTournois->dataTournois[i].nomTournoi, nom) == 0 && strcmp(listeTournois->dataTournois[i].dateTournoi, date) == 0){

            testTournoiInconnu = 0;                                                                 // Suppression de l'ordre d'afficher "tournoi inconnu"

            printf("%s %s\n", nom, date);                                                           // Affiche le nom et la date du tournoi

            unsigned int indexGagnante;                                                             // Index de la joueuse gagnante (sert à la compréhention du code)
            unsigned int indexPerdante;                                                             // Index de la joueuse perdante (sert à la compréhention du code)

            for (int j = 0; j < nbMatchTournoi; j++){

                // Si l'index du match correspond au début des 64e, 32e, etc, alors afficher 64emes de finales, etc
                switch (j){
                case index64eFinale:    printf("64emes de finale\n");   break;
                case index32eFinale:    printf("32emes de finale\n");   break;
                case index16eFinale:    printf("16emes de finale\n");   break;
                case index8eFinale:     printf("8emes de finale\n");    break;
                case indexQuartFinale:  printf("quarts de finale\n");   break;
                case indexDemiFinale:   printf("demi-finales\n");       break;
                case indexFinale:       printf("finale\n");             break;
                }

                indexGagnante = listeTournois->dataTournois[i].dataMatch[j].idxGagnante;
                indexPerdante = listeTournois->dataTournois[i].dataMatch[j].idxPerdante;

                printf("%s %s\n", listeTournois->dataJoueuses[indexGagnante].nomJoueuse, listeTournois->dataJoueuses[indexPerdante].nomJoueuse);
            }
            break;
        }
    }

    // Si le tournoi n'a pas été trouvé, alors afficher "tournoi inconnu" :
    if (testTournoiInconnu == 1){
        printf("tournoi inconnu\n");
    }
}

// Fonction d'affichage des matchs d'une participante donnée d'un tournoi donné
void afficher_matchs_joueuse(const TournoisWTA *listeTournois){
    char nomTournoi[lgMot+1];                                                                       // Nom du tournoi recherché
    char dateTournoi[lgMot+1];                                                                      // Date du tournoi recherché
    char nomJoueuse[lgMot+1];                                                                       // Nom de la joueuse recherchée

    scanf("%s", &nomTournoi);
    scanf("%s", &dateTournoi);
    scanf("%s", &nomJoueuse);
    //printf("\nnom : %s\n", nomJoueuse);

    unsigned int testTournoiInconnu = 1;                                                            // Passe à zéro si le tournoi est connu
    unsigned int testJoueuseInconnue = 1;                                                           // Passe à zéro si la joueuse est connue

    unsigned int idxT = 0;                                                                          // Sert à noter l'index du possible tournoi

    for (unsigned int i = 0; i < listeTournois->idxT; i++){

        // Si le nom et la date du tournoi rentrés correspondent à un même tournoi, noter l'index de ce tournoi :
        if (strcmp(listeTournois->dataTournois[i].nomTournoi, nomTournoi) == 0 && strcmp(listeTournois->dataTournois[i].dateTournoi, dateTournoi) == 0){
            testTournoiInconnu = 0;                                                                 // Indique que le tournoi n'est pas inconnu                         
            idxT = i;                                                                               // Sauvegarde l'index du tournoi
            break;                                                                                  // Sort de la boucle de recherche : l'unique tournoi a été trouvé
        }
    }

    // Si le tournoi n'a pas été trouvé, alors afficher "tournoi inconnu" :
    if (testTournoiInconnu == 1){
        printf("tournoi inconnu\n");
    }

    // Si le tournoi existe, lancer la recherche de la joueuese :
    else {

        // Balayage de la liste des joueueses existantes
        for (unsigned int i = 0; i < nbJoueusesTournoi * (idxT + 1); i++){

            // Si le nom de la joueuse a déjà été rentré :
            if (strcmp(listeTournois->dataJoueuses[i].nomJoueuse, nomJoueuse) == 0){

                testJoueuseInconnue = 0;                                                            // Indique que la joueuse n'est pas inconnue

                // Balayage de la liste des joueuses du tournoi correspondant
                for (unsigned int j = 0; j < nbMatchTournoi; j++){

                    // Si L'index d'une des joueses d'un match correspondant à celui de la joueuse demandée, alors afficher le match
                    if (listeTournois->dataTournois[idxT].dataMatch[j].idxGagnante == i || listeTournois->dataTournois[idxT].dataMatch[j].idxPerdante == i){
                        unsigned int indexGagnante = listeTournois->dataTournois[idxT].dataMatch[j].idxGagnante;
                        unsigned int indexPerdante = listeTournois->dataTournois[idxT].dataMatch[j].idxPerdante;
                        printf("%s %s\n", listeTournois->dataJoueuses[indexGagnante].nomJoueuse, listeTournois->dataJoueuses[indexPerdante].nomJoueuse);
                    }
                }
            }
        }
    }

    // Si la joueuse n'a pas été trouvée, alors afficher "joueuse inconnu" :
    if (testJoueuseInconnue == 1){
        printf("joueuse inconnue\n");
    }
}

// Fonction d'affichage joueuse tournois
void affichage_joueuses_tournoi(TournoisWTA *listeTournois){

    char nomTournoi[lgMot];
    char dateTournoi[lgMot];
    unsigned int testTournoiInconnu = 1;

    scanf("%s", &nomTournoi);
    scanf("%s", &dateTournoi);

    Joueuse tableauJoueuse[nbJoueusesTournoi];
    Joueuse tmp;

    for (unsigned int i=0; i<listeTournois->idxT; i++){
        if (strcmp(listeTournois->dataTournois[i].nomTournoi, nomTournoi) == 0 && strcmp(listeTournois->dataTournois[i].dateTournoi, dateTournoi) == 0){
            testTournoiInconnu = 0;
            printf("%s %s\n", nomTournoi, dateTournoi);
            unsigned int idxMin;

            for (unsigned int j = 0; j < nbJoueusesTournoi; j++) {
                tableauJoueuse[j] = listeTournois->dataJoueuses[i*nbJoueusesTournoi+j];
            }

            for (unsigned int j=0; j<nbJoueusesTournoi; j++){
                idxMin = j;
                for (unsigned int k=j+1; k<nbJoueusesTournoi; k++){
                    if (strcmp(tableauJoueuse[k].nomJoueuse, tableauJoueuse[idxMin].nomJoueuse) < 0){
                        idxMin = k;
                    }
                }
                tmp = tableauJoueuse[j];
                tableauJoueuse[j] =  tableauJoueuse[idxMin];
                tableauJoueuse[idxMin] = tmp;
                printf("%s %d\n", tableauJoueuse[j].nomJoueuse, tableauJoueuse[j].nbPoints);
            }
            break;
        }
    }

    // Si le tournoi n'a pas été trouvé, alors afficher "tournoi inconnu" :
    if (testTournoiInconnu == 1){
        printf("tournoi inconnu\n");
    } 
}
