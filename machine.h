#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum Utilisation Utilisation;
typedef struct MachineEtudiant Etudiant;

enum Utilisation {
    NON,
    OUI,
    PERSO
};

struct MachineEtudiant {
    int numero;
    char nom[100];
    char prenom[100];
    Utilisation machine;
};

FILE* ouvrirFichier(const char *nomFichier);
Etudiant* allocation(int nombre_eleve);
void lireFichier(const char *nomFichier, Etudiant *eleve, int *nombre);
void extraireInfos(const char *ligne, char *nom, char *prenom);
void afficherEtudiants(const Etudiant *eleve, int nombre);
void saisirInfoMachine(Etudiant *eleve, int nombre);
void afficherListeAvecMachine(const Etudiant *eleve, int nombre);
void enregistrement(const Etudiant *eleve, int nombre);
