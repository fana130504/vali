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

FILE* ouvrirFichier(const char *nomFichier) {
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier\n");
        exit(1);
    }
    return fichier;
}

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

void extraireInfos(const char *ligne, char *nom, char *prenom) {
    char *deuxPoints = strchr(ligne, ':');
    if (deuxPoints != NULL) {
        *deuxPoints = '\0';
        strcpy(nom, ligne);
        strcpy(prenom, deuxPoints + 1);
    }
}

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
            printf("Numero invalide.numero entre 1 a %d .\n", j);
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
void enregistrement(const Etudiant *eleve, int j) {
    FILE *fichier = fopen("resultat.html", "w");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier presence.txt\n");
        exit(1);
    }
    
    fprintf(fichier, "<html>\n<head>\n<title>Fiche de présence</title>\n");
    fprintf(fichier, "<style>\n");
    fprintf(fichier, "table { border-collapse: collapse; margin: 0 auto; }\n");
    fprintf(fichier, "th, td { border: 1px solid #000; padding: 5px; text-align: center; }\n");
    fprintf(fichier, "body { background: rgb(154, 100, 198); background-size: cover; }\n");
    fprintf(fichier, "div { background: linear-gradient(#6717cd, #2871fa); border-top-left-radius: 50px; border-bottom-right-radius: 50px; padding: 10px 30px; margin: 15px 100px; box-shadow: 10px -10px 20px #437adf; }\n");
    fprintf(fichier, ".image-container { position: absolute; top: 10px; left: 10px; width: 4cm; height: 4cm; }\n");
   fprintf(fichier, ".image-container img { width: 100%%; height: 100%%; object-fit: cover; }\n");
        fprintf(fichier, ".date{text-align: center;}\n");
    fprintf(fichier, "</style>\n</head>\n<body>\n");
  
    // Insérer l'image
    fprintf(fichier, "<div class='image-container'><img src=/home/fanantenana/toutes les leçon de MIT/misa.jpg alt='Image'></div>\n");

    // Écriture de la date d'exécution
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    fprintf(fichier, "<div>\n");
    fprintf(fichier, "<p class='date'><br>Date de présence : %d-%02d-%02d<br></p>\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    // Écriture des informations des étudiants dans le fichier
    fprintf(fichier, "<table>\n<tr>\n<th>Numero</th>\n<th>Nom</th>\n<th>Prenom</th>\n<th>Machine</th>\n</tr>\n");
    for (int i = 0; i < j; i++) {
        const char *etatMachine;
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
                etatMachine = "ABSENT";
                break;
        }
        fprintf(fichier, "<tr>\n<td>%d</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n</tr>\n", eleve[i].numero, eleve[i].nom, eleve[i].prenom, etatMachine);
    }
    fprintf(fichier, "</table>\n");
    fprintf(fichier, "</div>\n</body>\n</html>");
    fclose(fichier);
}


