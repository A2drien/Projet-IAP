#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// Sprint4.exe <../Sprint#1/inSp1.txt> run1.txt <../Sprint#2/inSp2.txt> run2.txt <../Sprint#3/inSp3.txt> run3.txt <../Sprint#4/inSp4.txt> run4.txt <../Sprint#4/inSp4.txt> run4.txt

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
    unsigned char nomJoueuse[lgMot];                                                                // Nom de la joueuse
    unsigned int nbPoints;                                                                          // Nombre points cummulés
}Joueuse;

// Définition du type Match
typedef struct{
    unsigned int idxGagnante;                                                                       // Index de la gagnante
    unsigned int idxPerdante;                                                                       // Index de la perdante
}Match;

// Définition du type Tournoi
typedef struct{
    char nomTournoi[lgMot];                                                                         // Nom du tournoi
    char dateTournoi[lgMot];                                                                        // Date du tournoi
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


int main(){

    // Déclarations/initialisations de quelques variables :
    TournoisWTA listeTournois;                              // Variable contenant... tout
    listeTournois.idxT = 0;                                 // L'index du tournoi "actuel" est par défaut à zéro
    listeTournois.idxJ = 0;                                 // L'index de la joueuse "actuelle" est par défaut à zéro
    char *mot[lgMot+1];                                     // Chaîne de caractères (mot) de taille max lgMot contenant la commande
    
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

        else if (strcmp(mot, "afficher_classement") == 0){
            afficher_classement(&listeTournois);
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
void definir_nombre_tournois(TournoisWTA *listeTournois){
    scanf("%d", &listeTournois->nbTournois);                                                        // La valeur rentrée après definir_nombre_tournois est donnée à nbTournois
    assert(1 <= listeTournois->nbTournois <= 10);                                                   // Si nbTournois n'est pas compris entre 1 et 10, stopper le programme (valeur aberrante)
}

/// Fonction d'enregistrement d'un tournoi, identifiable par son nom et sa date
void enregistrement_tournoi(TournoisWTA *listeTournois){
    unsigned int idxTournois = listeTournois->idxT;                                                 // Variable stockant l'index du tournoi actuel, afin de faciliter la future lecture du code
    unsigned int idxJoueuse = listeTournois->idxJ;                                                  // Variable stockant l'index de la joueuse actuelle, afin de faciliter la future lecture du code
    
    char nomGagnante[lgMot];
    char nomPerdante[lgMot];

    unsigned int joueuseGagnanteExiste;
    unsigned int joueusePerdanteExiste;

    assert(idxTournois < listeTournois->nbTournois);                                                // On vérifie que l'on peut en effet enregistrer le tournoi

    scanf("%s", &listeTournois->dataTournois[idxTournois].nomTournoi);                              // Le nom du tournoi cherché est stocké
    scanf("%s", &listeTournois->dataTournois[idxTournois].dateTournoi);                             // La date du tournoi cherché est stocké

    // Pour les 64 premiers matchs (64èmes de finale) :
    for (unsigned int i=0; i<nbMatchTournoi; i++){
        scanf("%s", &nomGagnante);                                                                  // Le nom de la gagnante est stockée     
        scanf("%s", &nomPerdante);                                                                  // Le nom de la perdante est stockée
        
        joueuseGagnanteExiste = 0;
        joueusePerdanteExiste = 0;

        for (unsigned int j=idxJoueuse; j>0; j--){
            // Si le nom de la joueuse perdante existe, lui donner les points correspondants
            if (strcmp(nomPerdante, listeTournois->dataJoueuses[j].nomJoueuse) == 0){
                // Les perdants des 64e sont incrémentés de 10 points, car elles ont terminé la compétition (pas de points supplémentaires à gagner)
                if (index64eFinale <= i && i <= index32eFinale){listeTournois->dataJoueuses[j].nbPoints += nbPoints64eFinale;}
                
                // Pour les 32 matchs suivants (32e de finale), les perdantes recoivent leurs 45 points
                else if (index32eFinale <= i && i <= index16eFinale){listeTournois->dataJoueuses[j].nbPoints += nbPoints32eFinale;}
    
                // Pour les 16 matchs suivants (16e de finale), les perdantes recoivent leurs 90 points
                else if (index16eFinale <= i && i <= index8eFinale){listeTournois->dataJoueuses[j].nbPoints += nbPoints16eFinale;}

                // Pour les 8 matchs suivants (8e de finale), les perdantes recoivent leurs 180 points
                else if (index8eFinale <= i && i <= indexQuartFinale){listeTournois->dataJoueuses[j].nbPoints += nbPoints8eFinale;}

                // Pour les 4 matchs suivants (quarts de finale), les perdantes recoivent leurs 360 points
                else if (indexQuartFinale <= i && i <= indexDemiFinale){listeTournois->dataJoueuses[j].nbPoints += nbPointsQuartFinale;}
        
                // Pour les 2 matchs suivants (demi-finale), les perdantes recoivent leurs 720 points
                else if (indexDemiFinale <= i && i <= indexFinale){listeTournois->dataJoueuses[j].nbPoints += nbPointsDemiFinale;}

                // Pour le dernier match (finale), la perdante recoit ses 1 200 points
                else {listeTournois->dataJoueuses[j].nbPoints += nbPointsFinale;}

                listeTournois->dataTournois->dataMatch[idxTournois*nbMatchTournoi+i].idxPerdante = j;
                joueusePerdanteExiste = 1;
            }

            else if (strcmp(nomGagnante, listeTournois->dataJoueuses[j].nomJoueuse) == 0){
                if (i == indexFinale+1){listeTournois->dataJoueuses[j].nbPoints += nbPointsChampionne;}
                listeTournois->dataTournois[idxTournois].dataMatch[idxTournois*nbMatchTournoi+i].idxGagnante = j;
                joueuseGagnanteExiste = 1;
            }
        }
        if (joueuseGagnanteExiste == 0){
            strcpy(listeTournois->dataJoueuses[idxJoueuse].nomJoueuse, nomGagnante);
            listeTournois->dataTournois[idxTournois].dataMatch[0].idxGagnante = idxJoueuse;
            idxJoueuse++;
        }
        
        if (joueusePerdanteExiste == 0){
            strcpy(listeTournois->dataJoueuses[idxJoueuse].nomJoueuse, nomPerdante);
            listeTournois->dataJoueuses[idxJoueuse].nbPoints = 10;
            listeTournois->dataTournois[idxTournois*nbMatchTournoi+i].dataMatch[idxTournois*nbMatchTournoi+i].idxPerdante = idxJoueuse;
            idxJoueuse++;
        }
    }
    listeTournois->idxT++;                                                                          // idxT est incrémenté
    listeTournois->idxJ = idxJoueuse;
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
            unsigned int idxGagnante;
            unsigned int idxPerdante;

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
                idxGagnante = listeTournois->dataTournois[i].dataMatch[j].idxGagnante;
                idxPerdante = listeTournois->dataTournois[i].dataMatch[j].idxPerdante;

                printf("%s %s\n", listeTournois->dataJoueuses[idxGagnante].nomJoueuse, listeTournois->dataJoueuses[idxPerdante].nomJoueuse);
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
    
    unsigned int numeroTournoi;

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
                    unsigned int idxGagnante = listeTournois->dataTournois[numeroTournoi].dataMatch[j].idxGagnante;
                    unsigned int idxPerdante = listeTournois->dataTournois[numeroTournoi].dataMatch[j].idxPerdante;
                    printf("%s %s\n", listeTournois->dataJoueuses[idxGagnante].nomJoueuse, listeTournois->dataJoueuses[idxPerdante].nomJoueuse); 
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

// Fonction d'affichage joueuse tournois
void affichage_joueuses_tournoi(TournoisWTA *listeTournois){

    char nomTournoi[lgMot];
    char dateTournoi[lgMot];
    unsigned int testTournoiInconnu = 1;

    scanf("%s", &nomTournoi);
    scanf("%s", &dateTournoi);

    Joueuse tableauJoueuse[nbJoueusesTournoi];
    Joueuse tmp;


    for (unsigned int i=0; i<nbJoueusesTournoi; i++){
        tableauJoueuse[i] = listeTournois->dataJoueuses[i];
    }

    for (unsigned int i=0; i<listeTournois->idxT; i++){
        if (strcmp(listeTournois->dataTournois[i].nomTournoi, nomTournoi) == 0 && strcmp(listeTournois->dataTournois[i].dateTournoi, dateTournoi) == 0){
            testTournoiInconnu = 0;
            printf("%s %s\n", nomTournoi, dateTournoi);
            unsigned int idxMin;
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

void afficher_classement(){/*
    unsigned int doublon;
    char nomJoueuse[lgMot];

    // Il faut supprmier les éventuels doublons de noms :
    for (unsigned int i=0; i<listeTournois->idxJ; i++){
        doublon = 0;
        //nomJoueuse = listeTournois->dataJoueuses[i].nomJoueuse;
        for (unsigned int j=0; j<i; j++){
            if (strcmp(listeTournois->dataJoueuses[j].nomJoueuse, nomJoueuse) == 0){

            }
        }

    }     
    char nom[lgMot];
    char date[lgMot];

    scanf("%s", nom);
    scanf("%s", date);

    unsigned int testTournoiInconnu = 1;                    // Passe à zéro si le tournoi est connu
    Joueuse copieDataJoueuse[listeTournois->idxJ+1];        // Le tableau a autant d'éléments que de joueuses déjà déclarées


    // Il faut trier par nombre de points puis par ordre lexicographique
    unsigned int indexMinimum = 0;
    unsigned int nbDoublons;
    Joueuse tmp;

    unsigned int nbPointsMinimum = listeTournois->dataJoueuses[indexMinimum].nbPoints;
    char nomJoueuseMinimum[lgMot] = listeTournois->dataJoueuses[indexMinimum].nomJoueuse;

    unsigned int nbPointsJoueuse;

    // On trie ensuite le tableau par ordre lexicographique, puis par ordre de points par égalité, par un tri par selection
    for (unsigned int i=0; i<listeTournois->idxJ; i++){
        for (unsigned int j=i+1; j<listeTournois->idxJ; i++){
            
            unsigned int nbPointsJoueuse = listeTournois->dataJoueuses[j].nbPoints;
            char nomJoueuse[lgMot] = listeTournois->dataJoueuses[j].nomJoueuse;
            
            if (nbPointsJoueuse < nbPointsMinimum || (nbPointsJoueuse == nbPointsMinimum && strcmp(nomJoueuse, nomJoueuseMinimum) < 0)){
                indexMinimum = j;
                nbPointsMinimum = listeTournois->dataJoueuses[j].nbPoints;
                nomJoueuseMinimum[lgMot] = listeTournois->dataJoueuses[j].nomJoueuse;
            }
        }
        tmp = listeTournois->dataJoueuses[indexMinimum];
        listeTournois->dataJoueuses[indexMinimum] = listeTournois->dataJoueuses[i];
        listeTournois->dataJoueuses[i] = tmp;
        printf("%s, %d", tmp.nomJoueuse, tmp.nbPoints);
    }
*/
printf("");
}