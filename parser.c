#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "parser.h"
#include "pile.h"

int tokenToIndexSLR(char* token) {
  if (isdigit(*token)) {
    return 4; // Nombre
  } else {
    switch (*token) {
    case '+':
      return 0;
    case '*':
      return 1;
    case '(':
      return 2;
    case ')':
      return 3;
    default:
      return -1; // Token non reconnu
    }
  }
}


// Fonction pour exécuter l'algorithme SLR
int computeSLR(char** input_tokens, int token_count, TableSLR tableSLR[TABLE_SIZE][TOKEN_COUNT]) {
  int index = 0;
  char state[10] = "0";
  Stack* stack = createStack(); // Création de la pile
  push(stack, state);

  while (1) {
    char* currentToken = input_tokens[index];
    char* tos = top(stack); // Top of the stack

    // Vérification de l'index et du token
    if (index >= token_count) {
      printf("Erreur: Fin prématurée de l'entrée\n");
      return 1;
    }

    // Obtention de l'action à partir de la tableSLR
    TableSLR action = tableSLR[atoi(tos)][tokenToIndexSLR(currentToken)];

    printf("table[%d][%d] = %d\n", atoi(tos), tokenToIndexSLR(currentToken), action.type);

    switch (action.type) {
    case ACCEPT:
      printf("Accepté\n");
      return 0;
    case ERREUR:
      printf("Erreur\n");
      return 1;
    case DECALE:
      printf("décaler\n");
      index++;
      push(stack, currentToken);
      push(stack, state);
      sprintf(state, "%d", action.value);
      break;
      // Ajouter le cas pour réduire ici
    default:
      printf("Action inconnue\n");
      return 1;
    }
  }

  destroyStack(stack); // Libération de la mémoire de la pile
  return 0;
}
