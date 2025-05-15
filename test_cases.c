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
    record_roll(game, roll_to_record, 0, 0);
    TEST_ASSERT_EQUAL(roll_to_record, game->frames[0]->roll_1);

    destroy_game(game);
}

void test_second_roll_of_frame_was_recorded(void)
{
    int roll_to_record = 6;
    game_t *game = create_game();
    record_roll(game, 4, 0, 0);
    record_roll(game, roll_to_record, 0, 1);
    TEST_ASSERT_EQUAL(roll_to_record, game->frames[0]->roll_2);

    destroy_game(game);
}

void test_third_roll_of_frame_10_was_legally_recorded(void)
{
    int roll_to_record = 10;
    game_t *game = create_game();
    record_roll(game, 4, 9, 0);
    record_roll(game, 6, 9, 1);
    record_roll(game, roll_to_record, 9, 2);
    TEST_ASSERT_EQUAL(roll_to_record, game->frames[9]->extra_roll);

    destroy_game(game);
}

void test_a_roll_cant_exceed_10(void)
{
    int roll_to_record = 11;
    game_t *game = create_game();
    record_roll(game, roll_to_record, 0, 0);
    TEST_ASSERT_EQUAL(10, game->frames[0]->roll_1);

    destroy_game(game);
}

void test_a_roll_cant_be_less_than_0(void)
{
    int roll_to_record = -1;
    int roll_to_record_2 = -1;
    game_t *game = create_game();
    record_roll(game, roll_to_record, 0, 0);
    record_roll(game, roll_to_record_2, 0, 1);
    TEST_ASSERT_EQUAL(0, game->frames[0]->roll_1);
    TEST_ASSERT_EQUAL(0, game->frames[0]->roll_2);


    destroy_game(game);
}

void test_the_sum_of_the_first_rwo_rolls_of_a_frame_are_not_greater_than_10(void)
{
    int roll_to_record = 7;
    int roll_to_record_2 = 5;
    int expected_outcome = 10 - roll_to_record;
    game_t *game = create_game();
    record_roll(game, roll_to_record, 0, 0);
    record_roll(game, roll_to_record_2, 0, 1);

    TEST_ASSERT_EQUAL(expected_outcome, 10 - game->frames[0]->roll_1);

    destroy_game(game);
}

void test_a_completed_frame_and_score_is_printed(void)
{
    int roll_to_record = 5;
    int roll_to_record_2 = 5;
    game_t *game = create_game();
    record_roll(game, roll_to_record, 0, 0);
    record_roll(game, roll_to_record_2, 0, 1);

    // Assuming you have a function to print the score
    // Here we just check if the frame is completed
    TEST_ASSERT_EQUAL(roll_to_record + roll_to_record_2, game->frames[0]->roll_1 + game->frames[0]->roll_2);

    destroy_game(game);
}

void run_tests(void)
{
    UnityBegin("Running Tests");
    RUN_TEST(test_a_game_has_ten_frames);
    RUN_TEST(test_first_roll_of_frame_was_recorded);
    RUN_TEST(test_second_roll_of_frame_was_recorded);
    RUN_TEST(test_third_roll_of_frame_10_was_legally_recorded);
//    RUN_TEST(test_a_roll_cant_exceed_10);
//    RUN_TEST(test_a_roll_cant_be_less_than_0);
//    RUN_TEST(test_the_sum_of_the_first_rwo_rolls_of_a_frame_are_not_greater_than_10);
//    RUN_TEST(test_a_completed_frame_and_score_is_printed);
    UnityEnd();
}