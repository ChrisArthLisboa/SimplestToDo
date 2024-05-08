
#include <stdbool.h> 
#include <stdio.h>
#include "libs/setup.h"
#include "libs/db.h"
#include "libs/structs.h"

int main() {

    if (checker()) {
        printf("Files already exists\n");
    } else {
        set_up();
        printf("creating files\n");
    }

    /* char* tags[2] = {"Test", "Hi"}; */

    /* struct Task task = { */
    /*     .title = "Test", */
    /*     .priority = 2, */
    /*     .description = "a task for test", */
    /*     .date = "20/04/2020", */
    /*     .tags = tags */
    /* }; */

    /* create_task(task); */
    
    /* remove_task(1); */

    return 0;

}

