
#include <stdio.h>
#include "feats/main.c"


int main() {

    if (checker()) {
        printf("Files already exists");
    } else {
        set_up();
        printf("creating files");
    }

    return 0;

}

