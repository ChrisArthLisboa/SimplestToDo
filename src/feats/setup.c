// What to do:
// 1. Create the task;
// 2. Complete the task;
// 3. Delete the task;
// 4. Schedule the task;

#include <asm-generic/errno-base.h>
#include <asm-generic/errno.h>
#include <sqlite3.h>

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdbool.h>

#define DIRPATH "~/.config/simplestTodo"
#define HOMEDIRSIZE 256


/* 
 * Created to fix relative
 * file paths
 *
 */
void fix_path(char* path, char** dest, unsigned long* size_returned) {

    if (sizeof(path) == 0 || path[0] != '~') {
        return;
    }

    unsigned long path_size = strlen(path) + strlen(getenv("HOME"));
    *dest = malloc(path_size);

    strcpy(*dest , getenv("HOME"));

    strcat(*dest, (path + 1));

    return;

}


/*
 * set up files
 *
 * */
bool set_up() {

    struct stat sb;

    unsigned long path_size;
    char *dirpath;
    fix_path(DIRPATH, &dirpath, &path_size);

    int res = mkdir(dirpath, S_IRWXU);

    if (res == -1) {
        
        switch (errno) {
            
            case EACCES: {
                exit(EXIT_FAILURE);
                return false;
                break;
            }

            case ENAMETOOLONG: {
                exit(EXIT_FAILURE);
                return false;
                break;
            }
        }
    }
    dirpath = realloc(dirpath, path_size+8);

    strcat(dirpath, "/todo.db");
    creat(dirpath, S_IRWXU);

    free(dirpath);

    return true;

}

/*
 * checks if the setup 
 * files exists
 */

bool checker() {

    struct stat sb;
    
    unsigned long path_size;
    char *dirpath;

    fix_path(DIRPATH, &dirpath, &path_size);

    dirpath = realloc(dirpath, path_size+8);
    strcat(dirpath, "/todo.db");

    if (
        access(dirpath, 0)
    ) {
        return false;
    }

    free(dirpath);
    return true;

}


// 1
// needed:
// 1. Sqlite

bool createTask() {

    

}

