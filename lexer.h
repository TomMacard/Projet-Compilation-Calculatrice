#ifndef TOKENIZER_H
#define TOKENIZER_H

// Fonction pour vérifier si un caractère est un opérateur arithmétique
int is_operator(char c);

// Fonction pour séparer la chaîne en tokens
char** tokenize(char* expression, int* token_count);

#endif /* TOKENIZER_H */
