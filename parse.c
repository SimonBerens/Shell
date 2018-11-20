#include <string.h>
#include <stdlib.h>
#include "parse.h"

char **parse_args(char *line) {
    char *cpy = calloc(strlen(line), sizeof(char));
    strcpy(cpy, line);
    char **arr = calloc(6, sizeof(char *));
    for (int i = 0; cpy; ++i) arr[i] = strsep(&cpy, " ");
    return arr;
}