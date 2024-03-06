#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#include "lexer.h"




int main() {

    char input[256];
    while (true) {

        //afficher le prompt
        printf("> ");

        // lire l'entrée de l'utilisateur
        fgets(input, 256, stdin);

        // Si "q" -> quitter
        if (strcmp(input, "q\n") == 0) {
            break;
        }

        // (DEBUG) afficher entrée utilisateur
        //printf("Input: %s", input);

        // Tokenize l'entrée de l'utilisateur
        TokenListe *tokens = analyse_lexicale(input);

        // (DEGUG) Affiche liste tokens
        debug_afficher_tokens(tokens);
        
        


    }
}

