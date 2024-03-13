#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "lexer.h"

Token *get_token_suivant(char **input) {

    // Elimine les blancs
    while (**input == ' ') (*input)++;


    // Analyse tokens
    // Seul le token NUM a une valeur
    if (**input == '\n' || **input == '\0') {
        Token *token = malloc(sizeof(Token));
        token->type = TOKEN_EOI;
        return token;
    }
    if (**input == '+') {
        (*input)++;
        Token *token = malloc(sizeof(Token));
        token->type = TOKEN_PLUS;
        return token;
    }
    if (**input == '*') {
        (*input)++;
        Token *token = malloc(sizeof(Token));
        token->type = TOKEN_MUL;
        return token;
    }
    if (**input == '(') {
        (*input)++;
        Token *token = malloc(sizeof(Token));
        token->type = TOKEN_PO;
        return token;
    }
    if (**input == ')') {
        (*input)++;
        Token *token = malloc(sizeof(Token));
        token->type = TOKEN_PF;
        return token;
    }
    if (**input >= '0' && **input <= '9') {
        char *fin;
        // On fait le choix de tout convertir en flottant, même s'il s'agit d'opérations entre entiers
        float val = strtof(*input, &fin);
        *input = fin;

        Token *token = malloc(sizeof(Token));
        token->type = TOKEN_NUM;
        token->valeur = val;
        return token;
    }

    printf("(ERREUR) Caractère Invalide : %c\n", **input);
    exit(1);
}


TokenListe *analyse_lexicale(char *input) {
    TokenListe *tete = NULL;
    TokenListe *queue = NULL;

    while (true) {
        Token *token = get_token_suivant(&input);
        TokenListe *noeud = malloc(sizeof(TokenListe));
        if (noeud == NULL) {
            printf("(ERREUR) Allocation mémoire noeud\n");
            exit(1);
        }
        noeud->token = token;
        noeud->suivant = NULL;

        if (tete == NULL) {
            tete = noeud;
            queue = noeud;
        } else {
            queue->suivant = noeud;
            queue = noeud;
        }
        if (token->type == TOKEN_EOI) {
            break;
        }
    }
    return tete;
}


void debug_afficher_tokens(TokenListe *tokens) {
    TokenListe *actuel = tokens;
    while (actuel != NULL) {
        switch (actuel->token->type) {
            case TOKEN_EOI:
                printf("EOI");
                break;
            case TOKEN_PLUS:
                printf("PLUS");
                break;
            case TOKEN_MUL:
                printf("MUL");
                break;
            case TOKEN_PO:
                printf("PO");
                break;
            case TOKEN_PF:
                printf("PF");
                break;
            case TOKEN_NUM:
                printf("(NUM: %f)", actuel->token->valeur);
                break;
            case TOKEN_ETAT:
                printf("ETAT: %f", actuel->token->valeur);
                break;
            default:
                printf("(ERREUR) Type Inconnu : %d\n", actuel->token->type);
                break;
        }
        printf(", ");
        actuel = actuel->suivant;
    }
    printf("\n");
}