#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <limits.h>
#include <fcntl.h>

void new_shell_line();

static void active_sig_handler(int n);

static void passive_sig_handler(int n);

void redirect(int direction, int flag, char *file_name, int *fd_location);

int main();
