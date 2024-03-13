/*
 * Fichier: parser.h
 * Auteurs: Nicolas FOND-MASSANY
 *          Tom MACARD
 * ---------------------
 * Contient la structure dela table SLR
 * 
 */

#ifndef PARSER_H
#define PARSER_H

#include "pile.h"

// Définition de la tableSLR
#define TABLE_SIZE 10
#define TOKEN_COUNT 6

typedef struct {
  enum { ERREUR, DECALE, REDUIR, ACCEPT } type ;
  int value;
} TableSLR;

int computeSLR(char** input_tokens, int token_count, TableSLR tableSLR[TABLE_SIZE][TOKEN_COUNT], char** E, Stack** stackNpi);

#endif /* PARSER_H */
