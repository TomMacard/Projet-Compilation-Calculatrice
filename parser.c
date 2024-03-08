#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "lexer.h"
#include "parser.h"

// Table est définie en dur
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




void empiler(TokenListe **liste, Token *token) {
    TokenListe *nouveau = (TokenListe *)malloc(sizeof(TokenListe));
    nouveau->token = token;
    nouveau->suivant = *liste;
    *liste = nouveau;
}

Token *depiler(TokenListe **liste) {
    if (*liste == NULL) {
        return NULL;
    }
    TokenListe *temp = *liste;
    Token *token = temp->token;
    *liste = temp->suivant;
    free(temp);
    return token;
}


int table_E(int entree) {
    switch (entree) {
        case 0:
            return 1;
        case 2:
            return 6;
        case 4:
            return 7;
        case 5:
            return 8;
        default:
            printf("(ERREUR) Table Goto\n");
            exit(1);
    }
}


bool analyse_syntaxique(TokenListe liste) {
    int etat = 0;
    TokenListe *pil = NULL;
    while (true) {
        printf("(DEBUG) Etat : %d\n", etat);
        
        //token tete de pile d'entree
        Token token_actuel = *liste.token;
        empiler(&pil, &token_actuel);

        // Type du token tel que défini dans lexer.h = colonne dans la table SLR
        int action = token_actuel.type; 
        
        // Recupere case de l'action dans la table SLR
        TableSLR RecupTable = Table[etat][action];

        // Normalement action jamais a 0, si 0 alors pas bon
        printf("(DEBUG) Action : %d\n", action);

        switch (RecupTable.action) {
            case ERREUR:
                printf("Entrée non correcte\n");
                return false;
            case ACCEPT:
                printf("Entrée correcte\n");
                return true;
            case DECALE:
                printf("(DEBUG) Décalage\n");
                // Recupere l'etat suivant
                etat = RecupTable.etatSuivant;
                //printf("(DEBUG) Etat : %d\n", etat);
                //ajoute le token à la pile
                empiler(&pil, &token_actuel);
                //enleve le token de la liste d'enytrée
                liste = *liste.suivant;
                break;
            case REDUIR:
                printf("(DEBUG) Réduction\n");
                // r1, r2, r3, r4 dans la table
                switch (RecupTable.etatSuivant) {
                    case 1:
                        // E → E + E
                        Token E1_plus = *depiler(&pil); //1er E
                        Token Eplus = *depiler(&pil); //signe +
                        Token E2_plus = *depiler(&pil); //2eme E

                        // creation du token resultat
                        Token Eres_plus;
                        Eres_plus.type = TOKEN_E;
                        Eres_plus.valeur = E1_plus.valeur + E2_plus.valeur;
                        empiler(&pil, &Eres_plus);
                        etat=table_E(etat);
                        break;
                    case 2:
                        // E → E * E
                        Token E1_mul = *depiler(&pil); //1er E
                        Token Emul = *depiler(&pil); //signe *
                        Token E2_mul = *depiler(&pil); //2eme E

                        // creation du token resultat
                        Token Eres_mul;
                        Eres_mul.type = TOKEN_E;
                        Eres_mul.valeur = E1_mul.valeur * E2_mul.valeur;
                        empiler(&pil, &Eres_mul);
                        etat=table_E(etat);
                        break;
                    case 3:
                        // E → (E)
                        Token PO = *depiler(&pil);
                        Token E = *depiler(&pil);
                        Token PF = *depiler(&pil);
                        empiler(&pil, &E);
                        etat=table_E(etat);
                        break;
                    case 4:
                        // E → val
                        Token Eval = *depiler(&pil);
                        Eval.type= TOKEN_E;
                        empiler(&pil, &Eval);
                        etat=table_E(etat);
                        break;
                    default:
                        printf("(ERREUR) Reduction ratée\n");
                        return false;
                }
                break;
            default:
                printf("(ERREUR) Action non reconnue\n");
                return false;
        }

        // Passe au token suivant
        if (liste.suivant == NULL) {
            printf("(ERREUR) Fin de liste token atteinte sans erreur ou acceptation\n");
            return false;
        }
    }

    printf("(ERREUR) Impossible d'arriver ici normalement?\n");
    return false;
}

