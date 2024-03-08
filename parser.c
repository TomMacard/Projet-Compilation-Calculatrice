#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "lexer.h"
#include "parser.h"


TableSLR Table[10][6] = {
    { {ERREUR, 0}, {ERREUR, 0}, {DECALE, 2}, {ERREUR, 0}, {DECALE, 3}, {ERREUR, 0}}
  , { {DECALE, 4}, {DECALE, 5}, {ERREUR, 0}, {ERREUR, 0}, {ERREUR, 0}, {ACCEPT, 0}}
  , { {ERREUR, 0}, {ERREUR, 0}, {DECALE, 2}, {ERREUR, 0}, {DECALE, 3}, {ERREUR, 0}}
  , { {REDUIR, 4}, {REDUIR, 4}, {ERREUR, 0}, {REDUIR, 4}, {ERREUR, 0}, {REDUIR, 4}}
  , { {ERREUR, 0}, {ERREUR, 0}, {DECALE, 2}, {ERREUR, 0}, {DECALE, 3}, {ERREUR, 0}}
  , { {ERREUR, 0}, {ERREUR, 0}, {DECALE, 2}, {ERREUR, 0}, {DECALE, 3}, {ERREUR, 0}}
  , { {DECALE, 4}, {DECALE, 5}, {ERREUR, 0}, {DECALE, 9}, {ERREUR, 0}, {ERREUR, 0}}
  , { {REDUIR, 1}, {DECALE, 5}, {ERREUR, 0}, {REDUIR, 1}, {ERREUR, 0}, {REDUIR, 1}}
  , { {REDUIR, 2}, {REDUIR, 2}, {ERREUR, 0}, {REDUIR, 2}, {ERREUR, 0}, {REDUIR, 2}}
  , { {REDUIR, 3}, {REDUIR, 3}, {ERREUR, 0}, {REDUIR, 3}, {ERREUR, 0}, {REDUIR, 3}} 
};


bool analyse_syntaxique(TokenListe liste) {
    int etat = 0;
    while (true) {
        Token token_actuel = *liste.token;
        int action = token_actuel.type;

        TableSLR RecupTable=Table[etat][action];
        printf("%d",action);

        etat = RecupTable.etatSuivant;

        printf("%d",etat);

        switch (RecupTable.action) {
            case ERREUR:
                return false;
            case ACCEPT:
                return true;
            case DECALE:



                break;
            case REDUIR:



                break;
            default:
                return false;
        }

        // On pass au token suivant
        liste.token=liste.suivant;
        break;

    }
}

