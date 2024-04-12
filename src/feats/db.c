// What to do:
// 1. Create the task;
// 2. Complete the task;
// 3. Delete the task;
// 4. Schedule the task;
//
#include "constants.h"
#include "setup.h"

#include <sqlite3.h>
#include <stdbool.h>

bool create_task() {

    char* dirpath;
    fix_path(DIRPATH, &dirpath);

    struct sqlite3 *db;
    sqlite3_open(dirpath, &db);
    





    sqlite3_close(db);

    return true;

}

