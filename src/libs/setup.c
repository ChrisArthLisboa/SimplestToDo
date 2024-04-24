// What to do:
// 1. Create the task;
// 2. Complete the task;
// 3. Delete the task;
// 4. Schedule the task;

#include "constants.h"
#include "utils.h"

#include <asm-generic/errno-base.h>
#include <asm-generic/errno.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdbool.h>
#include <time.h>

#include <sqlite3.h>



/*
 * set up files
 *
 * */
bool set_up() {

    struct stat sb;

    char *dirpath;
    fix_path(DIRPATH, &dirpath);

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

    unsigned long path_size = strlen(dirpath);

    dirpath = (char*) realloc(dirpath, path_size+8);

    strcat(dirpath, "/todo.db");
    creat(dirpath, S_IRWXU);

    sqlite3 *db;
    sqlite3_stmt *sql_response;

    int rc = sqlite3_open(dirpath, &db);

    if (rc != SQLITE_OK) {

        printf("Error ocurred| Database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        return false;
    }
    
    rc = sqlite3_prepare_v2(db,
            "Create table if not exists Task(id INT auto increment primary key, title varchar(30), description TEXT, task_date DATE, priority INT)",
            -1, &sql_response, 0);
    rc = sqlite3_step(sql_response);

    rc = sqlite3_prepare_v2(db,
            "Create table if not exists Tag(id INT auto increment, task_id INT, name varchar(20), description TEXT)",
            -1, &sql_response, 0);
    rc = sqlite3_step(sql_response);

    sqlite3_close(db);
    free(dirpath);
    return true;

}

/*
 * checks if the setup 
 * files exists
 */

bool checker() {

    struct stat sb;
    
    char *dirpath;

    fix_path(DBPATH, &dirpath);

    if (
        access(dirpath, 0)
    ) {
        return false;
    }

    free(dirpath);
    return true;

}
