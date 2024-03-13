#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "pile.h"

// Fonction pour vérifier si une chaîne de caractères est un nombre valide
int isNumber(const char* str) {
  float result = strtof(str, NULL);
  return result != 0.0;
}


// Fonction pour évaluer une pile d'éléments en notation polonaise inversée (NPI)
double evaluateNPI(Stack* stack) {
  Stack* result_stack = createStack();
  double result;
  
  for (int i = stack->top+1; i != 0; i--) {
    // Prendre le haut de la pile
    char* token = top(stack);
    
    // Si le token est un digit
    if (isNumber(token)) {
      // On push le float dans la pile de résultat
      push(result_stack, token);
      // On enlève l'opérande de la pile NPI
      pop(stack);
    }
    // Si le token est un operande
    else {
      // Récupère les deux opérande en haut de pile
      double operand2 = strtof(pop(result_stack), NULL);
      double operand1 = strtof(pop(result_stack), NULL);

      switch (*token) {
      case '+':
	result = operand1 + operand2;
	break;
      case '*':
	result = operand1 * operand2;
	break;
      default:
	printf("Opérateur non valide : %s\n", token);
	return -1;
      }

      // Ajoute le résultat en haut de la pile
      char result_str[20];
      snprintf(result_str, 20, "%.2f", result);
      push(result_stack, result_str);
      
      // On enlève l'opérande de la pile npi
      pop(stack);
    }
  }

  // Le résultat final est au sommet de la pile
  double final_result = atof(pop(result_stack));

  return final_result;
}
