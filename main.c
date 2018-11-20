#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <limits.h>

int main() {
    while (1) {
        char cwd[PATH_MAX];
        getcwd(cwd, sizeof(cwd));
        printf("\x1b[34m%s\x1b[31m>\x1b[0m", cwd); // print current working directory
        char *command = calloc(1000, sizeof(char));
        scanf(" %[^\n]", command);
        char *prev;
        while ((prev = strsep(&command, ";"))) { // iterate through
            char **args = calloc(10, sizeof(char *));
            for (int i = 0; prev; i += 1){
                while (*prev == ' ') prev++; // skip through consecutive whitespace
                args[i] = strsep(&prev, " ");
            }
            if (!strcmp(args[0], "exit")) return 0;
            else if (!strcmp(args[0], "cd")) chdir(args[1]);
            else if (!fork()) {
                execvp(args[0], args); // if execvp fails,
                exit(1); // the program will continue so we need to exit indicating an error
            }
            int status;
            wait(&status); // wait for child to finish, check exit code for failure
            if (WEXITSTATUS(status)) printf("cshell error: %s failed\n", args[0]);
        }
    }
}