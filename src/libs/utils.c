#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* 
 * Created to fix relative
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

