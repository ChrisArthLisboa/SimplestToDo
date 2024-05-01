
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
    struct Task task1 = {
        .title = "Uai",
        .date = "20/04/25",
        .priority = 0,
        .description = "A test",
        .tags = tags
    };
    struct Task task2 = {
        .title = "Buniteza",
        .date = "20/04/24",
        .priority = 0,
        .description = "A test todo",
        .tags = tags
    };

    create_task(task1);
    create_task(task2);

    return 0;

}

