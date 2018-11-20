#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <limits.h>

int main() {
    printf("Welcome to CShell\n");
    while (1) {
        char cwd[PATH_MAX];
        getcwd(cwd, sizeof(cwd));
        printf("%s> ", cwd); // todo: colors
        char *command = calloc(1000, sizeof(char));
        scanf(" %[^\n]", command);
        char *prev;
        while ((prev = strsep(&command, ";"))) {
            // todo: support spaces after
            char **args = calloc(6, sizeof(char *));
            for (int i = 0; prev; ++i) args[i] = strsep(&prev, " ");
            if (!strcmp(args[0], "exit")) return 0;
            else if (!strcmp(args[0], "cd")) chdir(args[1]);
            else if (!fork()) {
                execvp(args[0], args);
                exit(1); // todo: strerror
            }
            int status;
            wait(&status);
            if (WEXITSTATUS(status)) printf("cshell error: %s failed\n", args[0]);
        }
    }
}