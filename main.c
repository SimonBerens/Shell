#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <limits.h>

#define RED     "\x1b[31m"
#define BLUE    "\x1b[34m"
#define RESET   "\x1b[0m"

int main() {
    while (1) {
        char cwd[PATH_MAX];
        getcwd(cwd, sizeof(cwd));
        printf(BLUE"%s" RED "> " RESET, cwd);
        char *command = calloc(1000, sizeof(char));
        scanf(" %[^\n]", command);
        char *prev;
        while ((prev = strsep(&command, ";"))) {
            char **args = calloc(10, sizeof(char *));
            for (int i = 0; prev; i += 1){
                while (*prev == ' ') prev++;
                args[i] = strsep(&prev, " ");
            }
            if (!strcmp(args[0], "exit")) return 0;
            else if (!strcmp(args[0], "cd")) chdir(args[1]);
            else if (!fork()) {
                execvp(args[0], args);
                exit(1);
            }
            int status;
            wait(&status);
            if (WEXITSTATUS(status)) printf("cshell error: %s failed\n", args[0]);
        }
    }
}