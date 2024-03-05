#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>

int main() {

    char* input;
    while (true) {

        //afficher le prompt
        printf(">");

        // lire l'entrée de l'utilisateur
        fgets(input, sizeof(input), stdin);

        // Si "q" -> quitter
        if (strcmp(input, "q\n") == 0) {
            break;
        }

        // afficher l'entrée de l'utilisateur
        printf("Input: %s", input);
    }
}