// What to do:
// 1. Create the task;
// 2. Complete the task;
// 3. Delete the task;
// 4. Schedule the task;
//
#include "constants.h"
#include "setup.h"
#include "structs.h"

#include <sqlite3.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


int get_task_id(struct Task task) {

    char* dirpath;
    fix_path(DIRPATH, &dirpath);

    struct sqlite3 *db;
    int rc = sqlite3_open(dirpath, &db);
    struct sqlite3_stmt *sql_response;

    if (rc != SQLITE_OK) {
        printf("Error at checking DB | Database: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    char *query;

    query = (char*) malloc(67 +
            8 +
            strlen(task.title) +
            strlen(task.description) +
            8);

    sprintf(query, "SELECT id FROM Task WHERE title = \'%s\' && description = \'%s\' && priority = %d", task.title, task.description, task.priority);


    rc = sqlite3_prepare_v2(db, query, -1, &sql_response, 0);
    rc = sqlite3_step(sql_response);



    free(query);
}


bool create_task(struct Task task) {

    char* dirpath;
    fix_path(DIRPATH, &dirpath);

    struct sqlite3 *db;
    int rc = sqlite3_open(dirpath, &db);
    struct sqlite3_stmt *sql_response;
    
    if (rc != SQLITE_OK) {
        printf("Error ocurred| Database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        return false;
    }

    char *query;

    query = (char*) malloc( 87+
            strlen(task.title)+
            strlen(task.description)+
            strlen(task.date)+
            8 );

    sprintf(query, "INSERT INTO Task(title, description, task_date, priority) VALUES (\'%s\', \'%s\', \'%s\', %d)",
            task.title, task.description, task.date, task.priority);

    rc = sqlite3_prepare_v2(db, 
            query,
            -1, &sql_response, 0);
    rc = sqlite3_step(sql_response);
    free(query);

    int task_id = get_task_id(task); // check if null

    int i = 0;
    while(task.tags[i] != NULL) {

        query = (char*) malloc( 
            
            53

        );

        sprintf(query, "INSERT INTO Tag(task_id, name, description) VALUES ()");

    }

    sqlite3_finalize(sql_response);
    sqlite3_close(db);

    return true;

}

