#include <stdio.h>
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
    game_t game = create_game();
    int actual_frames = 0;
    for (int i = 0; i < NUM_OF_FRAMES; i++) {
        if (game.frames[i].roll_1 == 0 && game.frames[i].roll_2 == 0 && game.frames[i].extra_roll == 0) {
            actual_frames++;
        }
    }
    TEST_ASSERT_EQUAL(expected_frames, actual_frames);

    destroy_game(game);

}

void test_first_roll_of_frame_was_recorded(void)
{
    int roll_to_record = 5;

    game_t game = create_game();
    record_roll(&game, roll_to_record, 0, 0);
    TEST_ASSERT_EQUAL(roll_to_record, game.frames[0].roll_1);

    destroy_game(game);
}

void test_second_roll_of_frame_was_recorded(void)
{
    int roll_to_record = 6;
    game_t game = create_game();
    record_roll(&game, 4, 0, 0);
    record_roll(&game, roll_to_record, 0, 1);
    TEST_ASSERT_EQUAL(roll_to_record, game.frames[0].roll_2);

    destroy_game(game);
}

void test_third_roll_of_frame_10_was_legally_recorded(void)
{
    int roll_to_record = 10;
    game_t game = create_game();
    record_roll(&game, 4, 9, 0);
    record_roll(&game, 6, 9, 1);
    record_roll(&game, roll_to_record, 9, 2);
    TEST_ASSERT_EQUAL(roll_to_record, game.frames[9].extra_roll);

    destroy_game(game);
}

void test_a_roll_cant_exceed_10(void)
{
    int roll_to_record = 11;
    game_t game = create_game();
    record_roll(&game, roll_to_record, 0, 0);
    TEST_ASSERT_EQUAL(10, game.frames[0].roll_1);

    destroy_game(game);
}

void test_a_roll_cant_be_less_than_0(void)
{
    int roll_to_record = -1;
    int roll_to_record_2 = -1;
    game_t game = create_game();
    record_roll(&game, roll_to_record, 0, 0);
    record_roll(&game, roll_to_record_2, 0, 1);
    TEST_ASSERT_EQUAL(0, game.frames[0].roll_1);
    TEST_ASSERT_EQUAL(0, game.frames[0].roll_2);


    destroy_game(game);
}

void test_the_sum_of_the_first_rwo_rolls_of_a_frame_are_not_greater_than_10(void)
{
    int roll_to_record = 7;
    int roll_to_record_2 = 5;
    int expected_outcome = 10 - roll_to_record;
    game_t game = create_game();
    record_roll(&game, roll_to_record, 0, 0);
    record_roll(&game, roll_to_record_2, 0, 1);

    TEST_ASSERT_EQUAL(expected_outcome, 10 - game.frames[0].roll_1);

    destroy_game(game);
}
void test_roll_is_a_spare(void)
{
    int roll_to_record = 7;
    int roll_to_record_2 = 3;
    game_t game = create_game();
    record_roll(&game, roll_to_record, 0, 0);
    record_roll(&game, roll_to_record_2, 0, 1);
    TEST_ASSERT_EQUAL(10, game.frames[0].roll_1 + game.frames[0].roll_2);

    destroy_game(game);
}

void test_roll_is_a_strike(void)
{
    int roll_to_record = 10;
    game_t game = create_game();
    record_roll(&game, roll_to_record, 0, 0);
    TEST_ASSERT_EQUAL(10, game.frames[0].roll_1);
    destroy_game(game);
}

void test_roll_is_a_strike_in_last_frame(void)
{
    int roll_to_record = 10;
    game_t game = create_game();
    record_roll(&game, roll_to_record, 9, 0);
    record_roll(&game, roll_to_record, 9, 1);
    record_roll(&game, roll_to_record, 9, 2);
    TEST_ASSERT_EQUAL(10, game.frames[9].roll_1);
    TEST_ASSERT_EQUAL(10, game.frames[9].roll_2);
    TEST_ASSERT_EQUAL(10, game.frames[9].extra_roll);
    destroy_game(game);
}

void test_a_strike_adds_the_score_of_the_next_two_rolls(void)
{
    int roll_to_record = 10;
    int roll_to_record_2 = 5;
    int roll_to_record_3 = 4;
    game_t game = create_game();
    record_roll(&game, roll_to_record, 0, 0);
    record_roll(&game, roll_to_record_2, 1, 0);
    record_roll(&game, roll_to_record_3, 1, 1);
    int score = handle_strike(game, 0);
    TEST_ASSERT_EQUAL(19, score);

    destroy_game(game);
}

void test_a_spare_adds_the_score_of_the_next_roll(void)
{
    int roll_to_record = 7;
    int roll_to_record_2 = 3;
    int roll_to_record_3 = 4;
    game_t game = create_game();
    record_roll(&game, roll_to_record, 0, 0);
    record_roll(&game, roll_to_record_2, 0, 1);
    record_roll(&game, roll_to_record_3, 1, 0);
    int score = handle_spare(game, 0);
    TEST_ASSERT_EQUAL(14, score);

    destroy_game(game);
}

void test_a_strike_adds_the_score_of_the_next_two_rolls_in_last_frame(void)
{
    int roll_to_record = 10;
    int roll_to_record_2 = 5;
    int roll_to_record_3 = 4;
    game_t game = create_game();
    record_roll(&game, roll_to_record, 9, 0);
    record_roll(&game, roll_to_record_2, 9, 1);
    record_roll(&game, roll_to_record_3, 9, 2);
    int score = handle_tenth_frame(game);
    TEST_ASSERT_EQUAL(19, score);

    destroy_game(game);
}

void test_a_spare_adds_the_score_of_the_next_roll_in_last_frame(void)
{
    int roll_to_record = 7;
    int roll_to_record_2 = 3;
    int roll_to_record_3 = 4;
    game_t game = create_game();
    record_roll(&game, roll_to_record, 9, 0);
    record_roll(&game, roll_to_record_2, 9, 1);
    record_roll(&game, roll_to_record_3, 9, 2);
    int score = handle_tenth_frame(game);
    TEST_ASSERT_EQUAL(14, score);

    destroy_game(game);
}

void test_the_score_of_a_perfect_game_is_300(void)
{
    int rolls_perfect_game[10][3] = {
            {10, 0, 0}, // Frame 1: Strike
            {10, 0, 0}, // Frame 2: Strike
            {10, 0, 0}, // Frame 3: Strike
            {10, 0, 0}, // Frame 4: Strike
            {10, 0, 0}, // Frame 5: Strike
            {10, 0, 0}, // Frame 6: Strike
            {10, 0, 0}, // Frame 7: Strike
            {10, 0, 0}, // Frame 8: Strike
            {10, 0, 0}, // Frame 9: Strike
            {10, 10, 10} // Frame 10: Strike + bonus rolls
    };
    int expected_score = 300;
    game_t game = create_game();
    int score = record_frames(game, rolls_perfect_game);
    TEST_ASSERT_EQUAL(expected_score,score);
    destroy_game(game);
}

void test_the_score_of_a_game_is_258(void)
{
    int rolls_game[10][3] = {
            {10, 0, 0}, // Frame 1: Strike
            {7, 3, 0}, // Frame 2: Spare
            {9, 0, 0}, // Frame 3: Open frame
            {10, 0, 0}, // Frame 4: Strike
            {10, 0, 0}, // Frame 5: Strike
            {10, 0, 0}, // Frame 6: Strike
            {10, 0, 0}, // Frame 7: Strike
            {10, 0, 0}, // Frame 8: Strike
            {10, 0, 0}, // Frame 9: Strike
            {10, 10, 10} // Frame 10: Strike + bonus rolls
    };
    int expected_score = 258;
    game_t game = create_game();
    int score = record_frames(game, rolls_game);
    TEST_ASSERT_EQUAL(expected_score,score);
    destroy_game(game);
}

void run_tests(void)
{
    UnityBegin("Running Tests");
    RUN_TEST(test_a_game_has_ten_frames);
    RUN_TEST(test_first_roll_of_frame_was_recorded);
    RUN_TEST(test_second_roll_of_frame_was_recorded);
    /** Bob: I would like to discuss how I am handling this block of tests ***************/
    RUN_TEST(test_third_roll_of_frame_10_was_legally_recorded);
    RUN_TEST(test_a_roll_cant_exceed_10);
    RUN_TEST(test_a_roll_cant_be_less_than_0);
    RUN_TEST(test_the_sum_of_the_first_rwo_rolls_of_a_frame_are_not_greater_than_10);
    /*************************************************************************************/
    RUN_TEST(test_roll_is_a_spare);
    RUN_TEST(test_roll_is_a_strike);
    RUN_TEST(test_roll_is_a_strike_in_last_frame);
    RUN_TEST(test_a_strike_adds_the_score_of_the_next_two_rolls);
    RUN_TEST(test_a_strike_adds_the_score_of_the_next_two_rolls_in_last_frame);
    RUN_TEST(test_a_spare_adds_the_score_of_the_next_roll);
    RUN_TEST(test_a_spare_adds_the_score_of_the_next_roll_in_last_frame);
    RUN_TEST(test_the_score_of_a_perfect_game_is_300);
    RUN_TEST(test_the_score_of_a_game_is_258);

UnityEnd();
}