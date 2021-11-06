#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#pragma warning (disable:4996)

#define maxTournois 10
#define nbMatchTournoi 127
#define nbJoueusesTournoi 128
#define lgMot 30
#define tailleTableauCopieJoueuse nbJoueusesTournoi*4

// idx des différents types de matchs
#define idx64eFinale 0
#define idx32eFinale 64
#define idx16eFinale 96
#define idx8eFinale 112
#define idxQuartFinale 120
#define idxDemiFinale 124
#define idxFinale 126

// Points des joueuse par classement
#define nbPoints64eFinale 10
#define nbPoints32eFinale 45
#define nbPoints16eFinale 90
#define nbPoints8eFinale 180
#define nbPointsQuartFinale 360
#define nbPointsDemiFinale 720
#define nbPointsFinale 1200
#define nbPointsChampionne 2000

/* Stocke le nom de la joueuse pour un tournoi et le
 * nombre de points pour ce tournoi */
typedef struct {
    unsigned char nomJoueuse[lgMot+1];
    unsigned int nbPoints;
}Joueuse;

/* Stocke l'idx de la gagnante et de la perdante du match */
typedef struct {
    unsigned int idxGagnante;
    unsigned int idxPerdante;
}Match;

/* Stocke le nom du tournoi, sa date, mais aussi
 * l'ensemble de ses matchs */
typedef struct {
    char nomTournoi[lgMot+1];
    char dateTournoi[lgMot+1];
    Match dataMatch[nbMatchTournoi];
}Tournoi;

// Définition du type TournoisWTA
typedef struct {
    Tournoi dataTournois[maxTournois];
    Joueuse dataJoueuses[maxTournois * nbJoueusesTournoi];
    unsigned int nbTournois;
    unsigned int idxT;
    unsigned int idxJ;
}TournoisWTA;


// Déclarations de fonctions
void definir_nombre_tournois(TournoisWTA *);

void creationJoueuses(TournoisWTA *);

unsigned int rechercheIndexJoueuse(const TournoisWTA *);

void assignationPointsJoueuses(TournoisWTA *);

void enregistrement_tournoi(TournoisWTA *);

void affichageTypeMatch(unsigned int);

void affichage_matchs_tournoi(const TournoisWTA *);

void afficher_matchs_joueuse(const TournoisWTA *);

void affichage_joueuses_tournoi(const TournoisWTA *);

void afficher_classement(const TournoisWTA *);


int main() {
    TournoisWTA listeTournois;

    listeTournois.idxT = 0;
    listeTournois.idxJ = 0;
    
    char mot[lgMot+1];

    while (1) {
        scanf("%s", &mot);

        if (strcmp(mot, "definir_nombre_tournois") == 0) {
            definir_nombre_tournois(&listeTournois);
        }

        else if (strcmp(mot, "enregistrement_tournoi") == 0) {
            enregistrement_tournoi(&listeTournois);
        }

        else if (strcmp(mot, "affichage_matchs_tournoi") == 0) {
            affichage_matchs_tournoi(&listeTournois);
        }

        else if (strcmp(mot, "afficher_matchs_joueuse") == 0) {
            afficher_matchs_joueuse(&listeTournois);
        }

        else if (strcmp(mot, "affichage_joueuses_tournoi") == 0) {
            affichage_joueuses_tournoi(&listeTournois);
        }

        else if (strcmp(mot, "afficher_classement") == 0) {
            afficher_classement(&listeTournois);
        }
        
        else if (strcmp(mot, "exit") == 0) {
            exit(0);
        }
    }
    system("pause");
    return 0;
}


/* Inscrit le nombre maximum de tournois à enregistrer
 * [in out] listeTounois */
void definir_nombre_tournois(TournoisWTA *t) {
    scanf("%d", &t->nbTournois);
}


void creationJoueuses(TournoisWTA *t) {
    unsigned int idxJ = t->idxJ, idxT = t->idxT;
    unsigned int idxGagnante = 0, idxPerdante = 0;

    for (unsigned int i = 0; i < idx32eFinale; i++) {
        idxGagnante = idxJ + i * 2;
        idxPerdante = idxJ + i * 2 + 1;

        scanf("%s", &t->dataJoueuses[idxGagnante].nomJoueuse);
        scanf("%s", &t->dataJoueuses[idxPerdante].nomJoueuse);

        t->dataTournois[idxT].dataMatch[i].idxGagnante = idxGagnante;
        t->dataTournois[idxT].dataMatch[i].idxPerdante = idxPerdante;

        t->dataJoueuses[idxPerdante].nbPoints = nbPoints64eFinale;
    }
}


/* Recherche l'idx de la joueuse du tournoi
 * [in] idxT, listeTournoi
 * [out] i */
unsigned int rechercheIndexJoueuse(const TournoisWTA *t) {
    const unsigned int idxJ = t->idxJ;
    /// !!!
    unsigned int joueuseExiste = 0;
    char nomJoueuse[lgMot + 1];

    scanf("%s", &nomJoueuse);

    for (unsigned int i = idxJ; i < idxJ + nbJoueusesTournoi; i++) {
        if (strcmp(nomJoueuse, t->dataJoueuses[i].nomJoueuse) == 0) {
            joueuseExiste = 1;
            return i;
        }
    }
    /// !!!
    if (joueuseExiste == 0){
        return -1;
    }
}


/* Assigne les points correspondants à chaque joueuse
* [in] 
 * */
void assignationPointsJoueuses(TournoisWTA* t) {
    unsigned int idxT = t->idxT;
    unsigned int idxGagnante = 0, idxPerdante = 0;

    for (unsigned int i = idx32eFinale; i < nbMatchTournoi; i++) {
        idxGagnante = rechercheIndexJoueuse(t);
        idxPerdante = rechercheIndexJoueuse(t);

        t->dataTournois[idxT].dataMatch[i].idxGagnante = idxGagnante;
        t->dataTournois[idxT].dataMatch[i].idxPerdante = idxPerdante;

        if (idx32eFinale <= i && i < idx16eFinale) {
            t->dataJoueuses[idxPerdante].nbPoints = nbPoints32eFinale;
        }

        else if (idx16eFinale <= i && i < idx8eFinale) {
            t->dataJoueuses[idxPerdante].nbPoints = nbPoints16eFinale;
        }

        else if (idx8eFinale <= i && i < idxQuartFinale) {
            t->dataJoueuses[idxPerdante].nbPoints = nbPoints8eFinale;
        }

        else if (idxQuartFinale <= i && i < idxDemiFinale) {
            t->dataJoueuses[idxPerdante].nbPoints = nbPointsQuartFinale;
        }

        else if (idxDemiFinale <= i && i < idxFinale) {
            t->dataJoueuses[idxPerdante].nbPoints = nbPointsDemiFinale;
        }

        else {
            t->dataJoueuses[idxPerdante].nbPoints = nbPointsFinale;
            t->dataJoueuses[idxGagnante].nbPoints = nbPointsChampionne;
        }
    }
}


/* Fonction d'enregistrement d'un tournoi, identifiable par son nom et sa date
 * [in out] listeTournoi */
void enregistrement_tournoi(TournoisWTA* t) {
    unsigned int idxT = t->idxT;

    scanf("%s", &t->dataTournois[idxT].nomTournoi);
    scanf("%s", &t->dataTournois[idxT].dateTournoi);

    creationJoueuses(t);
    assignationPointsJoueuses(t);

    t->idxT++;
    t->idxJ += nbJoueusesTournoi;
}


void affichageTypeMatch(unsigned int idxMatch) {
    switch (idxMatch) {
        case idx64eFinale:    printf("64emes de finale\n");   break;
        case idx32eFinale:    printf("32emes de finale\n");   break;
        case idx16eFinale:    printf("16emes de finale\n");   break;
        case idx8eFinale:     printf("8emes de finale\n");    break;
        case idxQuartFinale:  printf("quarts de finale\n");   break;
        case idxDemiFinale:   printf("demi-finales\n");       break;
        case idxFinale:       printf("finale\n");             break;
    }
}


// Fonction d'affichage des participantes pour chaque match d'un tournoi
void affichage_matchs_tournoi(const TournoisWTA* t) {
    unsigned int testTournoiInconnu = 1;
    char nom[lgMot+1], date[lgMot+1];
    
    scanf("%s", nom);
    scanf("%s", date);

    for (unsigned int i = 0; i < t->idxT; i++) {
        if (strcmp(t->dataTournois[i].nomTournoi, nom) == 0 &&
            strcmp(t->dataTournois[i].dateTournoi, date) == 0) {
            testTournoiInconnu = 0;

            unsigned int idxGagnante = 0;
            unsigned int idxPerdante = 0;

            printf("%s %s\n", nom, date);

            for (unsigned int j = 0; j < nbMatchTournoi; j++) {
                affichageTypeMatch(j);

                idxGagnante = t->dataTournois[i].dataMatch[j].idxGagnante;
                idxPerdante = t->dataTournois[i].dataMatch[j].idxPerdante;

                printf("%s %s\n", t->dataJoueuses[idxGagnante].nomJoueuse,
                                  t->dataJoueuses[idxPerdante].nomJoueuse);
            }
        }
    }
    if (testTournoiInconnu == 1) {
        printf("tournoi inconnu\n");
    }
}


// Fonction d'affichage des matchs d'une participante donnée d'un tournoi donné
void afficher_matchs_joueuse(const TournoisWTA* t) {
    char nomTournoi[lgMot+1], dateTournoi[lgMot+1], nomJoueuse[lgMot+1];

    scanf("%s", &nomTournoi);
    scanf("%s", &dateTournoi);
    scanf("%s", &nomJoueuse);

    unsigned int testTournoiInconnu = 1;
    unsigned int testJoueuseInconnue = 1;

    unsigned int idxT = 0;

    for (unsigned int i = 0; i < t->idxT; i++) {
        if (strcmp(t->dataTournois[i].nomTournoi, nomTournoi) == 0 &&
            strcmp(t->dataTournois[i].dateTournoi, dateTournoi) == 0) {
            testTournoiInconnu = 0;
            idxT = i;
        }
    }

    if (testTournoiInconnu == 1) {
        printf("tournoi inconnu\n");
    }

    else {
        for (unsigned int i = 0; i < nbJoueusesTournoi * (idxT + 1); i++) {
            if (strcmp(t->dataJoueuses[i].nomJoueuse, nomJoueuse) == 0) {

                testJoueuseInconnue = 0;

                for (unsigned int j = 0; j < nbMatchTournoi; j++) {
                    if (t->dataTournois[idxT].dataMatch[j].idxGagnante == i || t->dataTournois[idxT].dataMatch[j].idxPerdante == i) {
                        unsigned int idxGagnante = t->dataTournois[idxT].dataMatch[j].idxGagnante;
                        unsigned int idxPerdante = t->dataTournois[idxT].dataMatch[j].idxPerdante;
                        printf("%s %s\n", t->dataJoueuses[idxGagnante].nomJoueuse, t->dataJoueuses[idxPerdante].nomJoueuse);
                    }
                }
            }
        }
    }

    if (testJoueuseInconnue == 1) {
        printf("joueuse inconnue\n");
    }
}


// Fonction d'affichage joueuse tournois
void affichage_joueuses_tournoi(TournoisWTA* t) {

    char nomTournoi[lgMot];
    char dateTournoi[lgMot];
    unsigned int testTournoiInconnu = 1;

    scanf("%s", &nomTournoi);
    scanf("%s", &dateTournoi);

    Joueuse tableauJoueuse[nbJoueusesTournoi];
    Joueuse tmp;

    for (unsigned int i = 0; i < t->idxT; i++) {
        if (strcmp(t->dataTournois[i].nomTournoi, nomTournoi) == 0 && strcmp(t->dataTournois[i].dateTournoi, dateTournoi) == 0) {
            testTournoiInconnu = 0;
            printf("%s %s\n", nomTournoi, dateTournoi);
            unsigned int idxMin;

            for (unsigned int j = 0; j < nbJoueusesTournoi; j++) {
                tableauJoueuse[j] = t->dataJoueuses[i * nbJoueusesTournoi + j];
            }

            for (unsigned int j = 0; j < nbJoueusesTournoi; j++) {
                idxMin = j;
                for (unsigned int k = j + 1; k < nbJoueusesTournoi; k++) {
                    if (strcmp(tableauJoueuse[k].nomJoueuse, tableauJoueuse[idxMin].nomJoueuse) < 0) {
                        idxMin = k;
                    }
                }
                tmp = tableauJoueuse[j];
                tableauJoueuse[j] = tableauJoueuse[idxMin];
                tableauJoueuse[idxMin] = tmp;
                printf("%s %d\n", tableauJoueuse[j].nomJoueuse, tableauJoueuse[j].nbPoints);
            }
            break;
        }
    }

    // Si le tournoi n'a pas été trouvé, alors afficher "tournoi inconnu" :
    if (testTournoiInconnu == 1) {
        printf("tournoi inconnu\n");
    }
}


void afficher_classement(const TournoisWTA* t) {
    unsigned int idxT = t->idxT;
    unsigned int idxDebut = 0;

    if (idxT == 0) {
        printf("pas de classement\n");
    }

    else if (idxT >= 4) {
        idxDebut = (idxT - 4) * nbJoueusesTournoi;
    }

    unsigned int lgTab = idxT * nbJoueusesTournoi - idxDebut;
    Joueuse tableauJoueuse[tailleTableauCopieJoueuse];

    // Il faut supprmier les éventuels doublons de noms :
    for (unsigned int i = 0; i < lgTab; i++) {
        tableauJoueuse[i] = t->dataJoueuses[idxDebut + i];
        for (unsigned int j = 0; j < i; j++) {
            if (strcmp(tableauJoueuse[j].nomJoueuse, tableauJoueuse[i].nomJoueuse) == 0) {
                tableauJoueuse[j].nbPoints += tableauJoueuse[i].nbPoints;
                strcpy(tableauJoueuse[i].nomJoueuse, " ");
                tableauJoueuse[i].nbPoints = 0;
            }
        }
    }

    Joueuse tmp;

    unsigned int idxMax;
    unsigned int nbPointsJoueuse;
    unsigned int nbPointsMax;

    char nomJoueuseMax[lgMot + 1];
    char nomJoueuse[lgMot + 1];

    for (unsigned int i = 0; i < lgTab; i++) {
        idxMax = i;
        nbPointsMax = tableauJoueuse[idxMax].nbPoints;
        strcpy(nomJoueuseMax, tableauJoueuse[idxMax].nomJoueuse);

        for (unsigned int j = i + 1; j < lgTab; j++) {
            nbPointsJoueuse = tableauJoueuse[j].nbPoints;
            strcpy(nomJoueuse, tableauJoueuse[j].nomJoueuse);

            if (nbPointsJoueuse > nbPointsMax || (nbPointsJoueuse == nbPointsMax && strcmp(nomJoueuse, nomJoueuseMax) < 0)) {
                idxMax = j;
                nbPointsMax = nbPointsJoueuse;
                strcpy(nomJoueuseMax, nomJoueuse);
            }
        }

        tmp = tableauJoueuse[idxMax];
        tableauJoueuse[idxMax] = tableauJoueuse[i];
        tableauJoueuse[i] = tmp;

        if (tableauJoueuse[i].nbPoints != 0) {
            printf("%s %d\n", tableauJoueuse[i].nomJoueuse, tableauJoueuse[i].nbPoints);
        }
    }
}