#include <stdio.h>
#include <string.h>
#include "test_cases.h"
#include "Unity-2.6.1/src/unity.h"

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "debug") == 0) {
        printf("Debug mode enabled.\n");
        run_tests();
    } else {
        printf("Running in normal mode.\n");
    }

    return 0;
}
