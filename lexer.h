#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Structures


// mettre dans rapport structure: réordonné les enum de token pour correspondre à la table SLR
typedef enum { 
    TOKEN_PLUS,
    TOKEN_MUL,
    TOKEN_PO,
    TOKEN_PF,
    TOKEN_NUM,
    TOKEN_EOI,
    TOKEN_E     // Ajoute le non terminal
} TokenType;

typedef struct {
    TokenType type;
    float valeur;
} Token;

typedef struct TokenListe {
    Token *token;
    struct TokenListe *suivant;
} TokenListe;


// Fonctions

Token *get_token_suivant(char **input);
TokenListe *analyse_lexicale(char *input);
void debug_afficher_tokens(TokenListe *tokens);