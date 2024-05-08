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
#include <time.h>


int get_rowid(struct Task task) {

    int id;

    char* dirpath;
    fix_path(DBPATH, &dirpath);

    struct sqlite3 *db;
    int rc = sqlite3_open(dirpath, &db);
    
    if (rc != SQLITE_OK) {
        sqlite3_close(db);

        return -1;
    }

    struct sqlite3_stmt *sql_response;


    
    // SELECT id FROM Task WHERE title = '' AND description = '' AND priority = ;
    char *query = "SELECT rowid FROM Task WHERE title = @taskTitle AND description = @taskDescription AND priority = @taskPriority";
    
    rc = sqlite3_prepare_v2(db, query, -1, &sql_response, 0);

    if (rc == SQLITE_OK) {
        
        int task_title = sqlite3_bind_parameter_index(sql_response, "@taskTitle");
        sqlite3_bind_text(
                sql_response, 
                task_title, 
                task.title, 
                -1,
                NULL);

        int task_description = sqlite3_bind_parameter_index(sql_response, "@taskDescription");
        sqlite3_bind_text(
                sql_response, 
                task_description, 
                task.description, 
                -1,
                NULL);

        int task_priority = sqlite3_bind_parameter_index(sql_response, "@taskPriority");
        sqlite3_bind_int(sql_response, task_priority, task.priority);

    } else {
        sqlite3_finalize(sql_response);
        sqlite3_close(db);

        return -1;
    }

    rc = sqlite3_step(sql_response);

    if (rc == SQLITE_ROW) {

        id = sqlite3_column_int(sql_response, 0);

    } else {

        sqlite3_finalize(sql_response);
        sqlite3_close(db);

        return -1;
    }
    
    sqlite3_finalize(sql_response);
    sqlite3_close(db);
    
    return id;

}


int n = 0;
char** temp_tags;
int get_tags_callback(void* _4param, int amount_collumns, char** collumn_values, 
                char** name_collumns) {

    temp_tags = (char**) realloc(temp_tags, n+1);
    if (temp_tags == NULL) {

        printf("error");
        return 1;

    }
    temp_tags[n] = (char*) calloc(sizeof(char*), strlen(collumn_values[0])+2);
    if (temp_tags == NULL) {

        printf("error");
        return 1;

    }

    strcpy(temp_tags[n], collumn_values[0]);
    n++;

    return 0;

}

struct Task get_task(int rowid) {

    struct Task task;
    
    char* dirpath;
    fix_path(DBPATH, &dirpath);


    struct sqlite3 *db;
    int rc = sqlite3_open(dirpath, &db);
    
    if (rc != SQLITE_OK) {
        printf("error opening db | Database: %s", sqlite3_errmsg(db));
        sqlite3_close(db);

        exit(1);
    }

    struct sqlite3_stmt *sql_response;

    char *query = "SELECT * FROM Task WHERE rowid = ?";
    
    rc = sqlite3_prepare_v2(db, query, -1, &sql_response, 0);
    if (rc != SQLITE_OK) {
        printf("error preparing query: %s", sqlite3_errmsg(db));
        sqlite3_close(db);

        exit(1);
    }
    rc = sqlite3_bind_int(sql_response, 1, rowid);

    rc = sqlite3_step(sql_response);

    if (rc == SQLITE_ROW) {
        
        task.title = (char*) sqlite3_column_text(sql_response, 0);
        task.description = (char*) sqlite3_column_text(sql_response, 1);
        task.date = (char*) sqlite3_column_text(sql_response, 2);
        task.priority = sqlite3_column_int(sql_response, 3);

    } else {
        printf("error at getting task | Database: %s", sqlite3_errmsg(db));
        sqlite3_close(db);

        exit(1);
    }

    query = malloc(36);

    if (query == NULL) {

        printf("error at allocating");
        exit(1);
    }

    sprintf(query, "SELECT name FROM Tag WHERE task_id = %d", rowid);
    char* error_Msg;

    rc = sqlite3_exec(db, query, get_tags_callback, 0, &error_Msg); 


    if (rc != SQLITE_OK) {
        printf("Failed to get Tags: \n");
        printf("%s", error_Msg);

        sqlite3_free(&error_Msg);
        sqlite3_close(db);

        exit(1);
    }

    task.tags = temp_tags; // Maybe memory leak

    free(query);
    sqlite3_close(db);

    return task;

}


bool create_task(struct Task task) {

    if (get_rowid(task) != -1) {
        return false;
    }

    char* dirpath;
    fix_path(DBPATH, &dirpath);

    struct sqlite3 *db;
    int rc = sqlite3_open(dirpath, &db);
    
    if (rc != SQLITE_OK) {
        printf("Error ocurred| Database: %s", sqlite3_errmsg(db));

        sqlite3_close(db);

        exit(1);
    }

    struct sqlite3_stmt *sql_response;

    char *query = "INSERT INTO Task(title, description, task_date, priority) VALUES (@taskTitle, @taskDesc, @taskDate, @taskPriority)";


    rc = sqlite3_prepare_v2(db, 
            query,
            -1, &sql_response, 0);

    if (rc == SQLITE_OK) {

        int index = sqlite3_bind_parameter_index(sql_response, "@taskTitle");
        sqlite3_bind_text(
                sql_response, 
                index, 
                task.title, 
                -1,
                NULL);

        index = sqlite3_bind_parameter_index(sql_response, "@taskDesc");
        sqlite3_bind_text(
                sql_response, 
                index, 
                task.description, 
                -1,
                NULL);

        index = sqlite3_bind_parameter_index(sql_response, "@taskDate");
        sqlite3_bind_text(
                sql_response, 
                index, 
                task.date, 
                -1,
                NULL);

        index = sqlite3_bind_parameter_index(sql_response, "@taskPriority");
        sqlite3_bind_int(sql_response, index, task.priority);

    } else {
        
        printf("error checking | Database: %s", sqlite3_errmsg(db));

        sqlite3_close(db);

        exit(1);

    }

    rc = sqlite3_step(sql_response);

    int task_id = get_rowid(task);
    if (task_id == -1) { 
        printf("Couldnt get the new task_id");

        sqlite3_finalize(sql_response);
        sqlite3_close(db);

        exit(1);
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

        char *query = "INSERT INTO Tag(task_id, name) VALUES (@taskId, @tagName)";

        while(task.tags[i] != NULL) {

            rc = sqlite3_prepare_v2(db, query, -1, &sql_response, 0);

            int task_id = sqlite3_bind_parameter_index(sql_response, "@taskId");
            sqlite3_bind_int(sql_response, task_id, get_rowid(task));

            int tag_name = sqlite3_bind_parameter_index(sql_response, "@tagName");
            sqlite3_bind_text(sql_response, tag_name, task.tags[i], -1, NULL);

            rc = sqlite3_step(sql_response);

            i++;

        }


    }

    sqlite3_finalize(sql_response);
    sqlite3_close(db);

    return true;

}

bool remove_task(int rowid) {

    char* dirpath;
    fix_path(DBPATH, &dirpath);

    struct sqlite3 *db;
    int rc = sqlite3_open(dirpath, &db);
    struct sqlite3_stmt *sql_response;

    if (rc != SQLITE_OK) {
        printf("Error at checking DB | Database: %s", sqlite3_errmsg(db));

        sqlite3_close(db);

        exit(1);
    }

    char *query = "DELETE FROM Task WHERE rowid = ?";

    rc = sqlite3_prepare_v2(db, 
            query,
            -1, &sql_response, 0);

    if (rc != SQLITE_OK) {
        printf("Error ocurred| Database: %s", sqlite3_errmsg(db));

        sqlite3_close(db);

        exit(1);
    }

    sqlite3_bind_int(sql_response, 1, rowid);

    rc = sqlite3_step(sql_response);

    if (rc != SQLITE_OK && rc != SQLITE_DONE) {
        printf("-- Error ocurred | Database: %s\n", sqlite3_errmsg(db)); 
        sqlite3_finalize(sql_response);
        sqlite3_close(db);

        exit(1);
    }

    query = "DELETE FROM Tag WHERE task_id = ?";

    rc = sqlite3_prepare_v2(db, 
            query,
            -1, &sql_response, 0);

    if (rc != SQLITE_OK) {
        printf("Error ocurred| Database: %s", sqlite3_errmsg(db));

        sqlite3_close(db);

        exit(1);
    }
    
    sqlite3_bind_int(sql_response, 1, rowid);

    rc = sqlite3_step(sql_response);

    if (rc != SQLITE_OK && rc != SQLITE_DONE) {
        printf("Error ocurred | Database: %s", sqlite3_errmsg(db));

        sqlite3_finalize(sql_response);
        sqlite3_close(db);

        exit(1);
    }

    sqlite3_finalize(sql_response);
    sqlite3_close(db);

    return true;

}


