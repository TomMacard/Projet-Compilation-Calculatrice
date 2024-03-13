/*
 * Fichier: pile.c
 * Auteurs: Nicolas FOND-MASSANY
 *          Tom MACARD
 * ---------------------
 * fonctions utilitaires pour la pile
 */



#include "pile.h"
#include <stdlib.h>
#include <stdio.h>

// Création de la pile
Stack* createStack() {
  Stack* stack = (Stack*)malloc(sizeof(Stack));
  if (stack == NULL) {
    printf("Allocation de mémoire pour la pile échouée\n");
    return NULL;
  }

  stack->capacity = STACK_CAPACITY;
  stack->top = -1;
  stack->array = (char**)malloc(stack->capacity * sizeof(char*));

  if (stack->array == NULL) {
    printf("Allocation de mémoire pour le tableau de la pile échouée\n");
    return NULL;
  }

  return stack;
}

// Vérifie si la pile est vide
int isEmpty(Stack* stack) {
  return stack->top == -1;
}

// Vérifie si la pile est pleine
int isFull(Stack* stack) {
  return stack->top == stack->capacity - 1;
}

// Push (empile) un élément dans la pile
void push(Stack* stack, char* item) {
  if (isFull(stack)) {
    printf("La pile est pleine\n");
    return ;
  }

  stack->array[++stack->top] = item;
}

// Pop (dépile) un élément de la pile
char* pop(Stack* stack) {
  if (isEmpty(stack)) {
    printf("La pile est vide\n");
    return NULL;
  }

  return stack->array[stack->top--];
}

// Retourne le sommet de la pile (sans dépiler)
char* top(Stack* stack) {
  if (isEmpty(stack)) {
    printf("La pile est vide\n");
    return NULL;
  }

  return stack->array[stack->top];
}

// Fonction pour inverser une pile
void reverseStack(Stack* stack) {
  // Création d'un tableau temporaire pour stocker les éléments de la pile
  char** temp_array = (char**)malloc(stack->capacity * sizeof(char*));
  if (temp_array == NULL) {
    printf("Allocation de mémoire pour le tableau temporaire échouée\n");
    return;
  }

  // Transfert des éléments de la pile dans le tableau temporaire
  int index = 0;
  while (!isEmpty(stack)) {
    temp_array[index++] = pop(stack);
  }

  // Rétablissement de l'ordre inverse dans la pile
  for (int i = 0; i < index; i++) {
    push(stack, temp_array[i]);
  }

  // Libération de la mémoire allouée pour le tableau temporaire
  free(temp_array);
}

// Libère la mémoire allouée pour la pile
void destroyStack(Stack* stack) {
  free(stack->array);
  free(stack);
}

// Fonction pour afficher le contenu de la pile
void printStack(Stack* stack) {
  printf("STACK: ");
  
  for(int i = stack->top; i != -1; i--) {
    printf(" %s ", stack->array[i]);
  }

  printf("\n");
}
