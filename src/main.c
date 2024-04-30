
#include <stdbool.h> 
#include <stdio.h>
#include "libs/setup.h"
#include "libs/db.h"

int main() {

    if (checker()) {
        printf("Files already exists\n");
    } else {
        set_up();
        printf("creating files\n");
    }

    char* tags[2] = {"testing", "string"}; 

    char* db_error_message;
    struct Task task = {
        .title = "Buniteza",
        .date = "20/04/24",
        .priority = 0,
        .description = "A test todo",
        .tags = tags
    };


    /* if (!create_task(task, db_error_message)) { */
    /*     printf("Erro: %s", db_error_message); */
    /* } */
    if (!remove_task(task, db_error_message)) {
        printf("Erro: %s", db_error_message);
    }
    
    

    return 0;

}

