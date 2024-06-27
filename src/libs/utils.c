#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <stdbool.h>
#include <sqlite3.h>

/* 
 * Fix relative
 * file paths
 *
 */
void fix_path(char* path, char** dest) {

    if (sizeof(path) == 0 || path[0] != '~') {
        return;
    }

    unsigned long path_size = strlen(path) + strlen(getenv("HOME"));
    *dest = (char*) malloc(path_size);

    strcpy(*dest , getenv("HOME"));

    strcat(*dest, (path + 1));

    return;

}

/* 
 * Help function
 */
void help_cmd() {

    printf(
        "\n--help : -h        request help\n"
        "--create : -c      create a task\n"
        "--remove : -r      remove task\n"
        "--get : -g         get all tasks\n"
    );

}
