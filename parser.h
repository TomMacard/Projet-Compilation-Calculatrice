#ifndef PARSER_H
#define PARSER_H

// Définition de la tableSLR
#define TABLE_SIZE 10
#define TOKEN_COUNT 6

typedef struct {
  enum { ERREUR, DECALE, REDUIR, ACCEPT } type ;
  int value;
} TableSLR;

int computeSLR(char** input_tokens, int token_count, TableSLR tableSLR[TABLE_SIZE][TOKEN_COUNT]);

#endif /* PARSER_H */
