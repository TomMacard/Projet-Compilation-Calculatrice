#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "parser.h"
#include "pile.h"

// Même ordre que dans la table SLR
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
    case '\n':
      return 5;
    default:
      return -1; // Token non reconnu
    }
  }
}

// Fonction pour exécuter l'algorithme SLR
int computeSLR(char** input_tokens, int token_count, TableSLR tableSLR[TABLE_SIZE][TOKEN_COUNT], char** E) {
  int index = 0;
  input_tokens[token_count] = "\n";
  char* actionReduction = calloc(2, sizeof(char)), *state;
  Stack* stack = createStack(); // Création de la pile

  // On commence par le premiere état de la table SLR
  push(stack, "0");

  while (1) {
    printStack(stack);
    char* currentToken = input_tokens[index];
    char* tos = top(stack); // Top of the stack

    // Vérification de l'index et du token
    if (index > token_count) {
      printf("Erreur: Fin prématurée de l'entrée\n");
      return 1;
    }

    // Obtention de l'action à partir de la tableSLR
    TableSLR action = tableSLR[atoi(tos)][tokenToIndexSLR(currentToken)];

    printf("action.type : %d, currentTokenIndex: %d \n", action.type, tokenToIndexSLR(currentToken));

    switch (action.type) {
    case ACCEPT:
      printf("accept\n");
      return 0;
    case DECALE:
      state = calloc(2, sizeof(char)); // chaine de caractère pour l'état a ajouter à la pile pour decale
      printf("decale\n");
      index++;
      push(stack, currentToken);
      printf("DÉCALÉ ");
      printStack(stack);
      // Mémoire du précédent state de la pile écrasé pour être remplacé par celui ci
      sprintf(state, "%d", action.value);
      printf("DÉCALÉ after ");
      printStack(stack);
      push(stack, state);
      break;
    case REDUIR:
      printf("réduit\n");
      // Condition en fonction du nombre d'élements de la grammaire
      if(action.value == 4) {
	// Dépiler 2 éléments de la pile
	for(size_t i = 0; i<2; i++)
	  pop(stack);
      }
      else if(action.value >= 1 || action.value <= 3 ) {
	// Dépiler 6 éléments de la pile
	for(size_t i = 0; i<6; i++)
	  pop(stack);
      }

      actionReduction = E[atoi(top(stack))];

      push(stack, "E");
      push(stack, actionReduction);
      break;
    case ERREUR:
      printf("Erreur\n");
      return 1;
    default:
      printf("Action inconnue\n");
      return 1;
    }
  }

  destroyStack(stack); // Libération de la mémoire de la pile
  return 0;
}
