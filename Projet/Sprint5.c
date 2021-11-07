#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#pragma warning (disable:4996)

#define maxTournois 10
#define nbMatchTournoi 127
#define nbJoueusesTournoi 128
#define lgMot 30
#define tailleTableauCopieJoueuse nbJoueusesTournoi*4

// Index des différents types de matchs
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

int rechercheTournoi(char *, char *, const TournoisWTA *);

void affichageTypeMatch(int, const TournoisWTA *);

void affichage_matchs_tournoi(const TournoisWTA *);

void affichageMatchJoueuse(char *, int, const TournoisWTA *);

void afficher_matchs_joueuse(const TournoisWTA *);

void triParSelectionOrdreLexicographique(Joueuse *);

void affichage_joueuses_tournoi(const TournoisWTA *);

void copieTableauJoueuse(unsigned int, unsigned int, Joueuse *, 
                         const TournoisWTA *);

void triParSelectionClassement(unsigned int, unsigned int, Joueuse *);

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


/*  Inscrit le nombre maximum de tournois à enregistrer
 *  [in-out] listeTournois */
void definir_nombre_tournois(TournoisWTA *t) {
    scanf("%d", &t->nbTournois);
}

/*  Crée les joueuses et donne 10 points aux perdantes en 64e
 *  [in-out] t (listeTournois) */
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


/*  Recherche l'index de la joueuse donnée du tournoi actuel
 *  [in] t (listeTournois)
 *  [out] i (index de la joueuse recherchée) */
unsigned int rechercheIndexJoueuse(const TournoisWTA *t) {
    const unsigned int idxJ = t->idxJ;
    char nomJoueuse[lgMot + 1];

    scanf("%s", &nomJoueuse);

    for (unsigned int i = idxJ; i < idxJ + nbJoueusesTournoi; i++) {
        if (strcmp(nomJoueuse, t->dataJoueuses[i].nomJoueuse) == 0) {
            return i;
        }
    }
}


/*  Assigne les points correspondants à chaque joueuse
 *  [in-out] t (listeTournois) */
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


/*  Ordonne l'enregistrement d'un tournoi et de ses joueuses
 *  [in-out] t (listeTournoi) */
void enregistrement_tournoi(TournoisWTA* t) {
    unsigned int idxT = t->idxT;

    scanf("%s", &t->dataTournois[idxT].nomTournoi);
    scanf("%s", &t->dataTournois[idxT].dateTournoi);

    creationJoueuses(t);
    assignationPointsJoueuses(t);

    t->idxT++;
    t->idxJ += nbJoueusesTournoi;
}


/*  Recherche le tournoi donné en argument, affiche "tournoi inconnu" s'il
 *  n'existe pas
 *  [in] nom, date, t (listeTournois)
 *  [out] i (index du tournoi), ou -1 (si non trouvé) */
int rechercheTournoi(char *nom, char *date, const TournoisWTA *t) {
    unsigned int testTournoiInconnu = 1;
    for (unsigned int i = 0; i < t->idxT; i++) {
        if (strcmp(t->dataTournois[i].nomTournoi, nom) == 0 &&
            strcmp(t->dataTournois[i].dateTournoi, date) == 0) {
            testTournoiInconnu = 0;
            return i;
        }
    }

    if (testTournoiInconnu){
        printf("tournoi inconnu\n");
        return -1;
    }
}


/*  Affiche les matchs du tournoi demandé, ainsi que la "position" des matchs
 *  [in] idxT, t (listeTournois) */
void affichageTypeMatch(int idxT, const TournoisWTA *t) {
    unsigned int idxGagnante = 0, idxPerdante = 0;

    for (unsigned int j = 0; j < nbMatchTournoi; j++) {
        switch (j) {
            case idx64eFinale:    printf("64emes de finale\n");   break;
            case idx32eFinale:    printf("32emes de finale\n");   break;
            case idx16eFinale:    printf("16emes de finale\n");   break;
            case idx8eFinale:     printf("8emes de finale\n");    break;
            case idxQuartFinale:  printf("quarts de finale\n");   break;
            case idxDemiFinale:   printf("demi-finales\n");       break;
            case idxFinale:       printf("finale\n");             break;
        }
        idxGagnante = t->dataTournois[idxT].dataMatch[j].idxGagnante;
        idxPerdante = t->dataTournois[idxT].dataMatch[j].idxPerdante;

        printf("%s %s\n", t->dataJoueuses[idxGagnante].nomJoueuse,
                          t->dataJoueuses[idxPerdante].nomJoueuse);
    }
}


/*  Recherche le tournoi demandé et demande à afficher l'ensemble de ses matchs
 *  [in] t (listeTournois) */
void affichage_matchs_tournoi(const TournoisWTA* t) {
    char nom[lgMot+1], date[lgMot+1];
    
    scanf("%s", nom);
    scanf("%s", date);

    int idxT = rechercheTournoi(&nom, &date, t);

    if (idxT != -1) {
        printf("%s %s\n", nom, date);
        affichageTypeMatch(idxT, t);
    }
}


/*  Affiche l'ensemble des matchs auquel a participé une joueuse dans un tournoi
 *  donné
 *  [in] nomJoueuse, idxT, t (listeTournois) */
void affichageMatchJoueuse(char *nomJoueuse, int idxT, const TournoisWTA *t) {
    unsigned int idxJ = t->idxJ, testJoueuseInconnue = 1;

    for (unsigned int i = 0; i < idxJ; i++) {
        if (strcmp(t->dataJoueuses[i].nomJoueuse, nomJoueuse) == 0) {
            for (unsigned int j = 0; j < nbMatchTournoi; j++) {
                if (t->dataTournois[idxT].dataMatch[j].idxGagnante == i ||
                    t->dataTournois[idxT].dataMatch[j].idxPerdante == i) {
                    
                    testJoueuseInconnue = 0;

                    unsigned int idxGagnante =
                    t->dataTournois[idxT].dataMatch[j].idxGagnante;
                    unsigned int idxPerdante =
                    t->dataTournois[idxT].dataMatch[j].idxPerdante;

                    printf("%s %s\n", t->dataJoueuses[idxGagnante].nomJoueuse,
                                      t->dataJoueuses[idxPerdante].nomJoueuse);
                }
            }
        }
    }
    if (testJoueuseInconnue == 1) {
        printf("joueuse inconnue\n");
    }
}


// !!! Pas de recherche de la joueuse si pas de tournoi

/*  Ordonne d'afficher l'ensemble des matchs auquel a participé une joueuse
 *  Affiche "tournoi inconnu" si le tournoi donné n'existe pas
 *  [in] t (listeTournois) */
void afficher_matchs_joueuse(const TournoisWTA* t) {
    char nomTournoi[lgMot+1], dateTournoi[lgMot+1], nomJoueuse[lgMot+1];

    scanf("%s", &nomTournoi);
    scanf("%s", &dateTournoi);
    scanf("%s", &nomJoueuse);

    int idxT = rechercheTournoi(nomTournoi, dateTournoi, t);

    if (idxT == -1) {
        printf("tournoi inconnu\n");
    }

    else {
        affichageMatchJoueuse(nomJoueuse, idxT, t);
    }
}


/*  Tri par ordre lexicographique le tableau de joueuse donné et affiche les
 *  les joueuses triées
 *  [in-out] tableauJoueuse */
void triParSelectionOrdreLexicographique(Joueuse *tableauJoueuse){
    unsigned int idxMin = 0;
    Joueuse tmp;
    for (unsigned int i = 0; i < nbJoueusesTournoi; i++) {
        idxMin = i;
        for (unsigned int j = i + 1; j < nbJoueusesTournoi; j++) {
            if (strcmp(tableauJoueuse[j].nomJoueuse,
                       tableauJoueuse[idxMin].nomJoueuse) < 0) {
                idxMin = j;
            }
        }
        tmp = tableauJoueuse[i];
        tableauJoueuse[i] = tableauJoueuse[idxMin];
        tableauJoueuse[idxMin] = tmp;
        printf("%s %d\n", tableauJoueuse[i].nomJoueuse,
                          tableauJoueuse[i].nbPoints);
    }
}


/*  Ordonne d'afficher les joueuses d'un tournoi donné
 *  [in] t (listeTournois) */
void affichage_joueuses_tournoi(const TournoisWTA* t) {
    char nomTournoi[lgMot+1],  dateTournoi[lgMot+1];
    unsigned int testTournoiInconnu = 1;

    scanf("%s", &nomTournoi);
    scanf("%s", &dateTournoi);

    Joueuse tableauJoueuse[nbJoueusesTournoi];

    int idxT = rechercheTournoi(&nomTournoi, &dateTournoi, t);

    if (idxT != -1) {
        printf("%s %s\n", nomTournoi, dateTournoi);
        for (unsigned int j = 0; j < nbJoueusesTournoi; j++) {
            tableauJoueuse[j] = t->dataJoueuses[idxT * nbJoueusesTournoi + j];
        }
        triParSelectionOrdreLexicographique(&tableauJoueuse);
    }
}


/*  Copie lgTab dernières joueuses de t (listeToournois) dans tableauJoueuse
 *  [in] lgTab, idxDebut, t (listeTournois)
 *  [in-out] tableauJoueuse */
void copieTableauJoueuse(unsigned int lgTab, unsigned int idxDebut,
                         Joueuse *tableauJoueuse, const TournoisWTA *t){
    for (unsigned int i = 0; i < lgTab; i++) {
        tableauJoueuse[i] = t->dataJoueuses[idxDebut + i];
        for (unsigned int j = 0; j < i; j++) {
            if (strcmp(tableauJoueuse[j].nomJoueuse,
                tableauJoueuse[i].nomJoueuse) == 0) {
                tableauJoueuse[j].nbPoints += tableauJoueuse[i].nbPoints;
                strcpy(tableauJoueuse[i].nomJoueuse, " ");
                tableauJoueuse[i].nbPoints = 0;
            }
        }
    }
}


/*  Tri par nombre de points tableauJoueuse
 *  [in] i (index de l'élement à déplacer), lgTab
 *  [in-out] tableauJoueuse */
void triParSelectionClassement(unsigned int i, unsigned int lgTab,
                               Joueuse *tableauJoueuse){
    Joueuse tmp;
    unsigned int idxMax = i, nbPointsJoueuse = 0;
    unsigned int nbPointsMax = tableauJoueuse[idxMax].nbPoints;

    char nomJoueuseMax[lgMot + 1], nomJoueuse[lgMot + 1];
    strcpy(nomJoueuseMax, tableauJoueuse[idxMax].nomJoueuse);

    for (unsigned int j = i + 1; j < lgTab; j++) {
        nbPointsJoueuse = tableauJoueuse[j].nbPoints;
        strcpy(nomJoueuse, tableauJoueuse[j].nomJoueuse);
        if (nbPointsJoueuse > nbPointsMax || (nbPointsJoueuse == nbPointsMax
            && strcmp(nomJoueuse, nomJoueuseMax) < 0)) {
            idxMax = j;
            nbPointsMax = nbPointsJoueuse;
            strcpy(nomJoueuseMax, nomJoueuse);
        }
    }
    tmp = tableauJoueuse[idxMax];
    tableauJoueuse[idxMax] = tableauJoueuse[i];
    tableauJoueuse[i] = tmp;
}


/*  Ordonne d'afficher le classement des joueuses (seulement les 4 derniers 
 *  tournois)
 *  [in] t (listeTournois) */
void afficher_classement(const TournoisWTA* t) {
    unsigned int idxT = t->idxT, idxDebut = 0;

    if (idxT == 0) {
        printf("pas de classement\n");
    }

    else if (idxT >= 4) {
        idxDebut = (idxT - 4) * nbJoueusesTournoi;
    }

    unsigned int lgTab = idxT * nbJoueusesTournoi - idxDebut;
    Joueuse tableauJoueuse[tailleTableauCopieJoueuse];
    
    copieTableauJoueuse(lgTab, idxDebut, &tableauJoueuse, t);
    
    for (unsigned int i = 0; i < lgTab; i++) {
        triParSelectionClassement(i, lgTab, &tableauJoueuse);
        if (tableauJoueuse[i].nbPoints != 0) {
            printf("%s %d\n", tableauJoueuse[i].nomJoueuse,
                              tableauJoueuse[i].nbPoints);
        }
    }   
}