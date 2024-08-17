#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fonction pour analyser les données de la requête GET
void parse_query_string(char *query, int *a, int *b) {
    sscanf(query, "nombre1=%d&nombre2=%d", a, b);
}

int main(void) {
    // Variables pour stocker les nombres
    int nombre1 = 0, nombre2 = 0, somme = 0;

    // Récupérer la chaîne de requête (QUERY_STRING) envoyée par le formulaire HTML
    char *query_string = getenv("QUERY_STRING");

    if (query_string != NULL && strlen(query_string) > 0) {
        // Analyser la chaîne de requête pour obtenir les valeurs des nombres
        parse_query_string(query_string, &nombre1, &nombre2);
        somme = nombre1 + nombre2;
    }

    // Générer la réponse HTTP
    printf("Content-type: text/html\n\n");
    printf("<html><body>\n");
    printf("<h1> Resultat de la Somme </h1>\n");

    if (query_string != NULL && strlen(query_string) > 0) {
        printf("<p>La somme de %d et %d est %d.</p>\n", nombre1, nombre2, somme);
    } else {
        printf("<p>Erreur : Aucune donnée reçue.</p>\n");
    }

    printf("</body></html>\n");

    return 0;
}

