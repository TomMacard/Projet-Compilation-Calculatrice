#ifndef PILE_H
#define PILE_H

#define STACK_CAPACITY 300

// Structure de la pile
typedef struct Stack {
  int capacity;
  int top;
  char** array;
} Stack;

// Crée une pile vide
Stack* createStack();

// Vérifie si la pile est vide
int isEmpty(Stack* stack);

// Vérifie si la pile est pleine
int isFull(Stack* stack);

// Empile un élément dans la pile
void push(Stack* stack, char* item);

// Dépile un élément de la pile
char* pop(Stack* stack);

// Retourne le sommet de la pile (sans dépiler)
char* top(Stack* stack);

// Fonction pour inverser une pile
void reverseStack(Stack* stack);

// Libère la mémoire allouée pour la pile
void destroyStack(Stack* stack);

// Fonction pour afficher le contenu de la pile
void printStack(Stack* stack);

#endif /* PILE_H */
