/*
 * Fichier: main.c
 * Auteurs: Nicolas FOND-MASSANY
 *          Tom MACARD
 * ---------------------
 * Fichier main de la calulatrice
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "parser.h"
#include "lexer.h"
#include "pile.h"
#include "evaluate.h"

TableSLR tableSLR[TABLE_SIZE][TOKEN_COUNT] = {
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

char* E[] = {"1", "-1", "6", "-1", "7", "8", "-1", "-1", "-1", "-1"};

int main() {
  int token_count, parserResult;
  double result;
  char input[420];
  Stack* stackNpi = createStack();

  while(1) {
    // Affiche le prompt
    printf("> ");

    // lire l'entrée de l'utilisateur
    fgets(input, 420, stdin);

    // Si "q" -> quitter
    if(strcmp(input, "q\n") == 0)
      break;
    
    // Lexer
    char** tokens = tokenize(input, &token_count);

    // Parser
    parserResult = computeSLR(tokens, token_count, tableSLR, E, &stackNpi);

    // Si le parsing n'a pas rencontré de problème
    if(parserResult == 0) {
      // Inverser la pile npi
      reverseStack(stackNpi);

      // Evaluer l'expression
      result = evaluateNPI(stackNpi);
      printf("%f\n", result);
    }
  }
  
  return 0;
}
