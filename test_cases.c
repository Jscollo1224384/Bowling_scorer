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
    destroy_game(game);
}

void test_first_roll_of_frame_was_recorded(void)
{
    int roll_to_record = 5;

    game_t *game = create_game();
    record_roll(game, roll_to_record, 0);
    TEST_ASSERT_EQUAL(roll_to_record, game->frames[0]->roll_1);

    destroy_game(game);
}

void test_second_roll_of_frame_was_recorded(void)
{
    int roll_to_record = 6;
    game_t *game = create_game();
    record_roll(game, 4, 0);
    record_roll(game, roll_to_record, 0);
    TEST_ASSERT_EQUAL(roll_to_record, game->frames[0]->roll_2);

    destroy_game(game);
}
void run_tests(void)
{
    UnityBegin("Running Tests");
    RUN_TEST(test_a_game_has_ten_frames);
    RUN_TEST(test_first_roll_of_frame_was_recorded);
    RUN_TEST(test_second_roll_of_frame_was_recorded);
    UnityEnd();
}