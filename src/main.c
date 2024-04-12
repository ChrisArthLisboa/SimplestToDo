
#include <stdio.h>
#include "feats/setup.h"

int main() {

    if (checker()) {
        printf("Files already exists\n");
    } else {
        set_up();
        printf("creating files\n");
    }

    return 0;

}

