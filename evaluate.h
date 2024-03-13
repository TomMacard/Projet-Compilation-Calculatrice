/*
 * Fichier: evaluate.h
 * Auteurs: Nicolas FOND-MASSANY
 *          Tom MACARD
 * ---------------------
 * Evaluateur d'expression (utilisé apres l'analyseur syntaxique)
 */

#ifndef EVALUATE_H
#define EVALUATE_H

// Fonction pour évaluer une pile d'éléments en notation polonaise inversée (NPI)
double evaluateNPI(Stack* stack);

#endif /* EVAULATE_H */
