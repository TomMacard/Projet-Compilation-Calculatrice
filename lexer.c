#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define OPERATORS "+-*/"

// Fonction pour vérifier si un caractère est un opérateur arithmétique
int is_operator(char c) {
  return strchr(OPERATORS, c) != NULL;
}

// Fonction pour séparer la chaîne en tokens
char** tokenize(char* expression, int* token_count) {
  // Initialisation de la mémoire pour stocker les tokens
  char** tokens = (char**)malloc(strlen(expression) * sizeof(char*));
  if (tokens == NULL) {
    printf("Allocation de mémoire échouée\n");
    exit(EXIT_FAILURE);
  }

  int i = 0;
  char* token = expression;
  while (*token != '\0') {
    // Si le caractère est un espace, passer au suivant
    if (isspace(*token)) {
      token++;
      continue;
    }

    // Si le caractère est un opérateur, le considérer comme un token
    if (is_operator(*token)) {
      tokens[i] = (char*)malloc(2 * sizeof(char));
      if (tokens[i] == NULL) {
	printf("Allocation de mémoire échouée\n");
	exit(EXIT_FAILURE);
      }
      tokens[i][0] = *token;
      tokens[i][1] = '\0';
      token++;
      i++;
    } else { // Sinon, trouver le prochain opérateur ou espace
      char* start = token;
      while (*token != '\0' && !isspace(*token) && !is_operator(*token)) {
	token++;
      }
      int length = token - start;
      tokens[i] = (char*)malloc((length + 1) * sizeof(char));
      if (tokens[i] == NULL) {
	printf("Allocation de mémoire échouée\n");
	exit(EXIT_FAILURE);
      }
      strncpy(tokens[i], start, length);
      tokens[i][length] = '\0';
      i++;
    }
  }

  *token_count = i; // Nombre total de tokens

  return tokens;
}
