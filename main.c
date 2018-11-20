#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "parse.h"

int main() {
    printf("Welcome to CShell\n");
    while (1) {
        printf("> ");
        char command[1000];
        scanf(" %[^\n]", command);
        if (!fork()) {
            char ** args = parse_args(command);
            execvp(args[0], args);
            exit(0); // todo: strerror
        }
        if (!strcmp(command, "exit")) return 0;
    }
}