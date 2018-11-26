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
    fflush(stdout); // flushes buffer without printing newline (for sig_handler)
}

static void sig_handler(int n) {
    printf("\n");
    new_shell_line();
}

int redirect(int direction, int flag, char * file_name, int * fd_location){
  int flags[2] = {O_CREAT|O_WRONLY, O_APPEND|O_CREAT|O_WRONLY}, directions[3] = {STDOUT_FILENO, STDIN_FILENO, STDERR_FILENO};
  *fd_location = open(file_name, flags[flag], 0777);
  dup2(*fd_location, directions[direction]);
  return *fd_location;
}

int main() {
    signal(SIGINT, sig_handler);
    while (1) {
        new_shell_line();
        char *command = calloc(1000, sizeof(char));
        fgets(command, 1000, stdin);
        command[strlen(command)-1] = '\0'; // strip newline
        char *prev;
        while ((prev = strsep(&command, ";"))) { // iterate through
            int stdout_fd = dup(STDOUT_FILENO), stdin_fd = dup(STDIN_FILENO), fd = 0;
            char **args = calloc(10, sizeof(char *));
            for (int i = 0; prev; i += 1){
                while (*prev == ' ') prev++; // skip through consecutive whitespace
                args[i] = strsep(&prev, " ");
                if (i && !strcmp(args[i - 1],">")) fd = redirect(0, 0, args[i], &fd);
                else if (i && !strcmp(args[i - 1],">>")) fd = redirect(0, 1, args[i], &fd);
                else if (i && !strcmp(args[i - 1], "2>")) fd = redirect(2, 0, args[i], &fd);
                else if (i && !strcmp(args[i - 1], "2>>")) fd = redirect(2, 1, args[i], &fd);
                else if (i && !strcmp(args[i - 1], "<")) fd = redirect(1, 0, args[i], &fd);
                if (fd) args[--i] = args[i + 1];
            }
            if (!*(args[0])) continue; // takes care of empty commands
            else if (!strcmp(args[0], "exit")) return 0;
            else if (!strcmp(args[0], "cd")) chdir(args[1]);
            else if (!fork()) {
                execvp(args[0], args); // if execvp fails,
                exit(errno); // the program will continue so we need to exit indicating an error
            }
            int status;
            wait(&status); // wait for child to finish, check exit code for failure
            if (WEXITSTATUS(status)) printf("%s\n", strerror(WEXITSTATUS(status)));
            close(fd);
            dup2(stdout_fd, STDOUT_FILENO);
            dup2(stdin_fd, STDIN_FILENO);
        }
    }
}
