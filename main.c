#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#include "lexer.h"
#include "parser.h"




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

        debug_afficher_tokens(tokens);

        bool resultat_parser = analyse_syntaxique(*tokens);

        if (resultat_parser) {
            printf ("Parser: valide\n");
        }
        else {
            printf("Parser :non valide\n");
        }


        // (DEGUG) Affiche liste tokens
        //
        
        


    }
}

