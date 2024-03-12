#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "pile.h"

// Fonction pour vérifier si une chaîne de caractères est un nombre valide
int isNumber(const char* str) {
  int dot_count = 0;
  int digit_count = 0;

  // Parcours de chaque caractère de la chaîne
  while (*str) {
    // Vérifier si le caractère est un chiffre
    if (isdigit(*str)) {
      digit_count++;
    }
    // Vérifier si le caractère est un point décimal
    else if (*str == '.') {
      dot_count++;
    }
    // Si le caractère n'est ni un chiffre ni un point décimal, la chaîne n'est pas un nombre
    else {
      return 0;
    }
    str++;
  }

  // La chaîne doit contenir au moins un chiffre et peut contenir au plus un point décimal
  return digit_count > 0 && dot_count <= 1;
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
      double operand2 = atof(pop(result_stack));
      double operand1 = atof(pop(result_stack));

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
