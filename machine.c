#include "machine.h"
int main() {
    const char *liste = "liste.txt";
    Etudiant *eleve=NULL;
    int numero_eleve = 0,
        nombre_eleve=75;

    eleve=allocation(nombre_eleve);
    lireFichier(liste, eleve, &numero_eleve);
    saisirInfoMachine(eleve, numero_eleve);
    afficherListeAvecMachine(eleve, numero_eleve);
    enregistrement(eleve, numero_eleve);

    return 0;
}
Etudiant* allocation(int nombre_eleve){
        Etudiant* eleve=(Etudiant*)malloc(nombre_eleve *sizeof(Etudiant));
        return eleve;
}
/*premier fonction 2*/
FILE* ouvrirFichier(const char *nomFichier) {
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier\n");
        exit(1);
    }

    return fichier;
}
/*premier fonction 1*/
void lireFichier(const char *nomFichier, Etudiant *eleve, int *j) {
    FILE *fichier = ouvrirFichier(nomFichier);
    char ligne[300];

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        char *nvLigne = strchr(ligne, '\n');
        if (nvLigne != NULL ) {
            *nvLigne = '\0';
        }
        char nom[100], prenom[100];
        extraireInfos(ligne, nom, prenom);

        eleve[*j].numero = *j + 1;
        strcpy(eleve[*j].nom, nom);
        strcpy(eleve[*j].prenom, prenom);
        eleve[*j].machine = -1;
        (*j)++;
    }
    fclose(fichier);
}
/*premier fonction 3*/
void extraireInfos(const char *ligne, char *nom, char *prenom) {
    char *deuxPoints = strchr(ligne, ':');
    if (deuxPoints != NULL) {
        *deuxPoints = '\0';
        strcpy(nom, ligne);
        strcpy(prenom, deuxPoints + 1);
    }
}
/*premier fonction 4*/
void afficherEtudiants(const Etudiant *eleve, int j) {
    const char *etatMachine;
    printf("%s\n", "__DATE__");
    printf("%-6s %-30s %-30s %-10s\n", "Numero", "Nom", "Prenom", "Machine");
    printf("\n");
    for (int i = 0; i < j; i++) {
        switch (eleve[i].machine) {
            case NON:
                etatMachine = "NON";
                break;
            case OUI:
                etatMachine = "OUI";
                break;
            case PERSO:
                etatMachine = "PERSO";
                break;
            default:
                etatMachine = "";
                break;
        }
        printf("%-6d %-30s %-30s %-10s\n", eleve[i].numero, eleve[i].nom, eleve[i].prenom, etatMachine);
    }
}

/*premier fonction 5*/
void saisirInfoMachine(Etudiant *eleve, int j) {
    int numero;
    int choix;

    while (1) {
        printf("Entrez le numéro de l'étudiant : \n (0 pour afficher la fiche de presence) : ");
        scanf("%d", &numero);
        if (numero == 0) {
            break;
        }
        if (numero < 1 || numero > j){
        printf("Numero invalide.numero entre 1 a %d .\n",j);

        }

        printf("Etudiant %d : %s %s\n", eleve[numero - 1].numero, eleve[numero - 1].nom, eleve[numero - 1].prenom);
        printf("1. OUI\n2. NON\n3. PERSO\n");
        printf("Entrez votre choix (1 pour OUI, 2 pour NON, 3 pour PERSO) : ");
        scanf("%d", &choix);
        switch (choix) {
            case 1:
                eleve[numero - 1].machine = OUI;
                break;
            case 2:
                eleve[numero - 1].machine = NON;
                break;
            case 3:
                eleve[numero - 1].machine = PERSO;
                break;
            default:
                printf("ERREUR ! \n");
                break;
        }
    }
}
/*premier fonction 6*/
void afficherListeAvecMachine(const Etudiant *eleve, int j) {
    const char *etatMachine;

    printf("\n%-6s %-30s %-30s %-10s\n", "Numero", "Nom", "Prenom", "Machine");
    for (int i = 0; i < j; i++) {
        switch (eleve[i].machine) {
            case NON:
                etatMachine = "NON";
                break;
            case OUI:
                etatMachine = "OUI";
                break;
            case PERSO:
                etatMachine = "PERSO";
                break;
            default:
                etatMachine = "";
                break;
        }
        printf("%-6d %-30s %-30s %-10s\n", eleve[i].numero, eleve[i].nom, eleve[i].prenom, etatMachine);
    }
}

// Fonction pour enregistrer les informations dans le fichier presence.txt
void enregistrement(const Etudiant *eleve, int j) {
    FILE *fichier = fopen("presence.html", "w");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier presence.html\n");
        exit(1);
    }
    fprintf(fichier,"<html>\n");
    fprintf(fichier,"<head><titre><center><main><font size='20px' color='blue' >Fiche de presence</font></main></center></titre></head></br></br>\n");
    fprintf(fichier,"<style>");
    fprintf(fichier," titre{ font-style:oblique; text-decoration:underline;  }");
    fprintf(fichier,"body{ background:url(misa1.jpeg) center/cover;}");
    fprintf(fichier,"th{ background-color:pink;}");
    fprintf(fichier,"th ,td{ border:1px solid black;}");
    fprintf(fichier,"table{ background-collapse:collapse; background: rgba( 245, 245, 245, 0,9); border: 2px solid rgb(0, 140, 255); boreder-radius: 15px 15px 15x 15x; box-shadow: 0px 0px 20px 4px #81cfc6; heigth:200px; width:1000x;}");
    fprintf(fichier," main{  margin: 0 auto; border:2px solid rgb(0, 140, 255); border-radius: 25px 25px 0 0;}");
    fprintf(fichier,"</style>");
    fprintf(fichier,"<body>");
    // Écriture de la date d'exécution
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    fprintf(fichier, "<p>Date de presence : %d-%02d-%02d \n\n</p></br></br>",
            tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
     fprintf(fichier,"<center><table>\n");
    // Écriture des informations des étudiants dans le fichier
    fprintf(fichier,"<tr><th>Numero</th><th>Nom</th><th>Prenom</th><th>Machine</th></tr>");
  //  fprintf(fichier, "%-6s %-30s %-30s %-10s\n", "Numero", "Nom", "Prenom", "Machine");

    for (int i = 0; i < j; i++) {
        const char *etatMachine;
        switch (eleve[i].machine){
            case NON:
                etatMachine = "<font size=4 color='red'>NON</font>";
                break;
            case OUI:
                etatMachine = "<font size=4 color='#00ffff'> OUI</font>";
                break;
            case PERSO:
                etatMachine = "<font size=4 color='#00ff9d'> PERSO</font>";
                break;
            default:
                etatMachine = "<font size=4 color=''>ABSENT</font>";
                break;
        }
        fprintf(fichier, "<tr><td>%-6d</td> <td>%-30s</td> <td>%-30s</td> <td>%-10s</td>\n", eleve[i].numero, eleve[i].nom, eleve[i].prenom, etatMachine);

    }
    fprintf(fichier,"</table></center>");
    fprintf(fichier,"</body>");
    fprintf(fichier,"</html>");
        fclose(fichier);
}
