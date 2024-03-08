#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "parser.h"
#include "lexer.h"

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

int main() {
  char expression[] = "2*3";
  int token_count;

  // lexer
  char** tokens = tokenize(expression, &token_count);

  // Affichage des tokens séparés
  printf("Tokens :\n");
  for (int i = 0; i < token_count; i++) {
    printf("%s\n", tokens[i]);
  }

  // parser
  computeSLR(tokens, token_count, tableSLR);
  
  // Libérer la mémoire allouée pour les tokens
  for (int i = 0; i < token_count; i++) {
    free(tokens[i]);
  }
  free(tokens);

  return 0;
}
