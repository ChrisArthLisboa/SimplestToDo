// What to do:
// 1. Create the task;
// 2. Complete the task;
// 3. Delete the task;
// 4. Schedule the task;

#include <asm-generic/errno-base.h>
#include <asm-generic/errno.h>
#include <sqlite3.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdbool.h>

#define DIRPATH "~/.config/simplestTodo"
#define DBPATH "~/.config/simplestTodo/todo.db"
#define HOMEDIRSIZE 256



void fix_path(char* path, char* dest) {

    if (sizeof(path) == 0 || path[0] != '~') {
        
        return;

    }

    
    char *home = getenv("HOME");

    strcat(home, (path + 1));

    int i = 0;
    while (home[i] != '\0') {

        dest[i] = home[i];
        i++;

    }
    dest[i+1] = '\0';

}


/*
 * 
 * check if the db already exists
 * if not create it
 *
 * */
bool start_up() {

    struct stat sb;

    char dirpath[HOMEDIRSIZE];
    fix_path(DIRPATH, dirpath);
    int res = mkdirat(AT_FDCWD, dirpath, S_IRWXU);


    if (
        access(DBPATH, 0)
    ) {
        creat(DBPATH, S_IRWXU);
    } 
    else {
        printf("File already exists\n");
    }

    return true;

}

// 1
// needed:
// 1. Sqlite

bool createTask() {

    

}

