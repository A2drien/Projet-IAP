const unsigned int maxTournois = 10;        // nb maximum de tournois
const unsigned int nbMatch = 127;           // nb de matchs par tournois
const unsigned int nbJoueuses = 128;        // nb joueuses par tournois
const unsigned int lgMot = 30;              // nb de caractères max
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
        scanf("%c", mot);                   // entrée de la commande
        commande(&mot);                     // analyse de la commande
    }
}

// Analyse de la commande rentrée
int commande(char* mot){
    char text;
    for (int i=0; i<lgMot; i++){
        text += mot[i];

        // La commande rentrée est definir_nombre_tournois ?
        if (text == "definir_nombre_tournois"){
            char charnbTournois[3];     // charnbTournois contient la chaine de caractère du nombre de tournois
            for(int j=0; j<3 ;j++){
                charnbTournois[j] = mot[i+j+1];
            }
            nbTournois = atoi(charnbTournois);
                   
            // Non terminée !
        }

        // La commande rentrée est enregistrement_tournois ?
        else if (text == "enregistrement_tournoi"){
            // Non terminée !
        }

        else if (text == "affichage_matchs_tournois"){  

        }
        // La commande rentrée est exit ?
        else if (text == "exit"){
            // Attention, pas sûr de ce qui est 
            return 0;                   // sortie de la fonction et de la boucle
        }                               // infinie, fin du programme
    }
}

