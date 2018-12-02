#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <limits.h>
#include <fcntl.h>

void new_shell_line() {
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    printf("\x1b[32m%s\x1b[31m>\x1b[0m ", cwd); // print current working directory
    fflush(stdout); // flushes buffer without printing newline (for active_sig_handler)
}

static void active_sig_handler(int n) {
    printf("\n");
    new_shell_line();
}

static void passive_sig_handler(int n) {
    printf("\n");
}

void redirect(int direction, int flag, char *file_name, int *fd_location) {
    int flags[2] = {O_CREAT | O_WRONLY, O_APPEND | O_CREAT | O_WRONLY}, directions[3] = {STDOUT_FILENO, STDIN_FILENO,
                                                                                         STDERR_FILENO};
    *fd_location = open(file_name, flags[flag], 0777);
    dup2(*fd_location, directions[direction]);
}

int main() {
    signal(SIGINT, active_sig_handler);
    while (1) {
        new_shell_line();
        char *line = calloc(1000, sizeof(char));
        fgets(line, 1000, stdin);
        line[strlen(line) - 1] = '\0'; // strip newline
        char *prev;
        while ((prev = strsep(&line, ";"))) { // iterate by semicolon
            char *command = prev;
            int p[2], READ = 0, WRITE = 1, in = STDIN_FILENO;
            while ((prev = strsep(&command, "|"))) { // iterate by pipe
                pipe(p);
                int stdout_fd = dup(STDOUT_FILENO), stdin_fd = dup(STDIN_FILENO), fd = 0, i = 0, status;
                char **args = calloc(10, sizeof(char *));
                for (; prev; i += 1) {
                    while (*prev == ' ') prev++; // skip through consecutive whitespace
                    args[i] = strsep(&prev, " ");
                    if (i && !strcmp(args[i - 1], ">")) redirect(0, 0, args[i], &fd);
                    else if (i && !strcmp(args[i - 1], ">>")) redirect(0, 1, args[i], &fd);
                    else if (i && !strcmp(args[i - 1], "2>")) redirect(2, 0, args[i], &fd);
                    else if (i && !strcmp(args[i - 1], "2>>")) redirect(2, 1, args[i], &fd);
                    else if (i && !strcmp(args[i - 1], "<")) redirect(1, 0, args[i], &fd);
                    if (fd) args[i - 1] = NULL;
                }
                if (!*(args[0])) continue; // takes care of empty commands
                if (!*(args[i - 1])) args[(i--) - 1] = NULL; // takes care of trailing whitespace
                if (!strcmp(args[0], "exit")) return 0;
                else if (!strcmp(args[0], "cd")) chdir(args[1]);
                else {
                    if (!fork()) {
                        dup2(in, STDIN_FILENO);
                        if (command) dup2(p[WRITE], STDOUT_FILENO);
                        close(p[READ]);
                        execvp(args[0], args); // if execvp fails,
                        exit(1); // the program will continue so we need to exit indicating an error
                    }
                    signal(SIGINT, passive_sig_handler);
                    if (strcmp(args[i - 1], "&")) {
                        wait(&status); // wait for child to finish, check exit code for failure
                        if (WEXITSTATUS(status)) printf("%s failed\n", args[0]);
                    }
                    signal(SIGINT, active_sig_handler);
                    close(p[WRITE]);
                    in = p[READ];
                }
                close(fd);
                dup2(stdout_fd, STDOUT_FILENO);
                dup2(stdin_fd, STDIN_FILENO);
            }
        }
    }
}
