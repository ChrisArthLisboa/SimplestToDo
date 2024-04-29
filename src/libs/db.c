// What to do:
// 1. Create the task; v
// 2. Complete the task; 
// 3. Delete the task; v
// 4. Schedule the task;
//
#include "constants.h"
#include "structs.h"
#include "utils.h"

#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


int get_rowid(struct Task task) {

    int id;

    char* dirpath;
    fix_path(DBPATH, &dirpath);

    struct sqlite3 *db;
    int rc = sqlite3_open(dirpath, &db);
    struct sqlite3_stmt *sql_response;
    
    if (rc != SQLITE_OK) {
        sqlite3_close(db);

        return -1;
    }

    char *query;
    
    // SELECT id FROM Task WHERE title = '' AND description = '' AND priority = ;
    query = (char*) malloc(
        
        72 +
        strlen(task.title) +
        strlen(task.description) +
        8

    );

    sprintf(query, "SELECT rowid FROM Task WHERE title = '%s' AND description = '%s' AND priority = %d ;",
            task.title, task.description, task.priority);
    
    rc = sqlite3_prepare_v2(db, query, -1, &sql_response, 0);

    if (rc != SQLITE_OK) {
        /* printf("Error ocurred| Database: %s", sqlite3_errmsg(db)); */
        sqlite3_close(db);

        return -1;
    }

    rc = sqlite3_step(sql_response);

    if (rc == SQLITE_ROW) {

        id = sqlite3_column_int(sql_response, 0);

    } else {
        return -1;
    }
    
    sqlite3_finalize(sql_response);
    sqlite3_close(db);
    
    return id;

}

bool create_task(struct Task task, char* error_return) {

    if (get_rowid(task) != -1) {
        error_return = (char*) malloc(strlen("Task already exists") + 10);
        strcpy(error_return, "Task already exists");
        return false;
    }

    char* dirpath;
    fix_path(DBPATH, &dirpath);

    struct sqlite3 *db;
    int rc = sqlite3_open(dirpath, &db);
    struct sqlite3_stmt *sql_response;
    
    if (rc != SQLITE_OK) {
        error_return = (char*) malloc(strlen("Error ocurred| Database: ") + strlen(sqlite3_errmsg(db)) + 10);
        sprintf(error_return, "Error ocurred| Database: %s", sqlite3_errmsg(db));
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

    int task_id = get_rowid(task);
    if (task_id == -1) { 
        error_return = (char*) malloc(strlen("Couldnt get the new task_id") + 10);
        strcpy(error_return, "Couldnt get the new task_id");
        return false;
    }

    unsigned long max = 0;

    if (task.tags[0] != NULL) {
        int i = 0;

        while (task.tags[i] != NULL) {

            if (strlen(task.tags[i]) > max) {
                max = strlen(task.tags[i]);
            }
            i++;
        }
        i = 0;

        query = (char*) malloc( 
            75 + 4 + max
        );
        while(task.tags[i] != NULL) {

            sprintf(query, "INSERT INTO Tag(task_id, name) VALUES (\'%d\', \'%s\')", task_id, task.tags[i]);
            rc = sqlite3_prepare_v2(db, query, -1, &sql_response, 0);
            rc = sqlite3_step(sql_response);

            i++;

        }

    }

    sqlite3_finalize(sql_response);
    sqlite3_close(db);

    return true;

}

bool remove_task(struct Task task, char* error_return) {

    char* dirpath;
    fix_path(DBPATH, &dirpath);

    struct sqlite3 *db;
    int rc = sqlite3_open(dirpath, &db);
    struct sqlite3_stmt *sql_response;

    if (rc != SQLITE_OK) {
        error_return = (char*) malloc(strlen("Error at checking DB | Database: %s") + strlen(sqlite3_errmsg(db)) + 10);
        sprintf(error_return, "Error at checking DB | Database: %s", sqlite3_errmsg(db));
        return false;
    }

    int task_id = get_rowid(task);

    if (task_id == -1) {
        error_return = (char*) malloc(strlen("task not found") + 10);
        strcpy(error_return, "task not found");
        return false;
    } 

    char *query;

    query = (char*) malloc(
        34 + 8
    );

    // DELETE FROM Task WHERE rowid = %d;
    sprintf(query, "DELETE FROM Task WHERE rowid = %d", task_id);

    rc = sqlite3_prepare_v2(db, 
            query,
            -1, &sql_response, 0);

    if (rc != SQLITE_OK) {
        error_return = (char*) malloc(strlen("Error ocurred| Database: ") + strlen(sqlite3_errmsg(db)) + 10);
        sprintf(error_return, "Error ocurred| Database: %s", sqlite3_errmsg(db));
        sqlite3_close(db);

        return false;
    }

    rc = sqlite3_step(sql_response);

    if (rc != SQLITE_OK || rc != 101) {
        error_return = (char*) malloc(strlen("Error ocurred| Database: ") + strlen(sqlite3_errmsg(db)) + 10);
        sprintf(error_return, "Error ocurred| Database: %s", sqlite3_errmsg(db));
        sqlite3_close(db);

        return false;
    }

    free(query);

    sqlite3_finalize(sql_response);
    sqlite3_close(db);

    return true;

}


