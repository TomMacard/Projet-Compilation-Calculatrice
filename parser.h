#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


// Structures

typedef enum {
    DECALE,
    REDUIR,
    ACCEPT,
    ERREUR
} Action;


typedef struct {
    Action action;
    int etatSuivant;
} TableSLR;


// Fonctions

bool analyse_syntaxique(TokenListe *liste);
bool analyse_syntaxique_original(TokenListe liste);