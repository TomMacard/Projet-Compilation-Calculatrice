#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>




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


bool analyse_syntaxique(TokenListe liste);