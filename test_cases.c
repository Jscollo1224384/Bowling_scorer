#include <stdio.h>
#include <stdlib.h>
#include "Unity-2.6.1/src/unity.h"

// Define empty setUp and tearDown functions
void setUp(void)
{
    // No setup required
}

void tearDown(void)
{
    // No teardown required
}

/* Test Suite */
void run_tests(void)
{
    UnityBegin("Running Tests");

    UnityEnd();
}