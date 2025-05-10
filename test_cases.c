#include <stdio.h>
#include <stdlib.h>
#include "Unity-2.6.1/src/unity.h"
#include "game_attributes.h"

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

void test_a_game_has_ten_frames(void)
{
    int expected_frames = 10;
    game_t *game = create_game();
    if (game == NULL) {
        TEST_FAIL_MESSAGE("Failed to create game");
    }
    int actual_frames = 0;
    for (int i = 0; i < NUM_OF_FRAMES; i++) {
        if (game->frames[i] != NULL) {
            actual_frames++;
        }
    }
    TEST_ASSERT_EQUAL(expected_frames, actual_frames);
}
void run_tests(void)
{
    UnityBegin("Running Tests");
    RUN_TEST(test_a_game_has_ten_frames);
    UnityEnd();
}