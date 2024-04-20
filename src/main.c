
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

    struct Task task = {
        .title = "Teste",
        .date = "20/04/24",
        .priority = 0,
        .description = "A test todo",
        .tags = tags
    };

    create_task(task);
    

    return 0;

}

