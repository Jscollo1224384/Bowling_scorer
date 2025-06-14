#include <stdio.h>
#include "Unity-2.6.1/src/unity.h"
#include "game_attributes.h"

struct{
    int expected_score;
    int game[10][3];

} sample_games[] = {
        {.expected_score = 258,
                .game = {
                        {10,  0,  0},   // Frame 1: Strike
                        { 7,  3,  0},   // Frame 2: Spare
                        { 9,  0,  0},   // Frame 3: Open frame
                        {10,  0,  0},   // Frame 4: Strike
                        {10,  0,  0},   // Frame 5: Strike
                        {10,  0,  0},   // Frame 6: Strike
                        {10,  0,  0},   // Frame 7: Strike
                        {10,  0,  0},   // Frame 8: Strike
                        {10,  0,  0},   // Frame 9: Strike
                        {10, 10, 10}    // Frame 10: Strike + bonus rolls
                }},
        {.expected_score = 87,
                .game = {
                        {10,  0,  0},   // Frame  1: Strike
                        { 7,  3,  0},   // Frame  2: Spare
                        { 9,  0,  0},   // Frame  3: Open frame
                        { 0,  0,  0},   // Frame  4: Open frame
                        { 0,  3,  0},   // Frame  5: Open frame
                        { 8,  2,  0},   // Frame  6: Spare
                        { 6,  0,  0},   // Frame  7: Open frame
                        { 1,  2,  0},   // Frame  8: Open frame
                        { 3,  0,  0},   // Frame  9: Open frame
                        { 5,  3,  0}    // Frame 10: Open frame Total score: 87
                }},
        {.expected_score = 290,
                .game = {
                        {10,  0,  0},   // Frame 1: Strike
                        {10,  0,  0},   // Frame 2: Spare
                        {10,  0,  0},   // Frame 3: Open frame
                        {10,  0,  0},   // Frame 4: Strike
                        {10,  0,  0},   // Frame 5: Strike
                        {10,  0,  0},   // Frame 6: Strike
                        {10,  0,  0},   // Frame 7: Strike
                        {10,  0,  0},   // Frame 8: Strike
                        {10,  0,  0},   // Frame 9: Strike + bonus rolls
                        {10,  10, 0}    // Frame 10: Strike + bonus rolls
                }},
        {.expected_score = 280,
                .game = {
                        {10,  0,  0},   // Frame 1: Strike
                        {10,  0,  0},   // Frame 2: Spare
                        {10,  0,  0},   // Frame 3: Open frame
                        {10,  0,  0},   // Frame 4: Strike
                        {10,  0,  0},   // Frame 5: Strike
                        {10,  0,  0},   // Frame 6: Strike
                        {10,  0,  0},   // Frame 7: Strike
                        {10,  0,  0},   // Frame 8: Strike
                        {10,  0,  0},   // Frame 9: Strike + bonus rolls
                        {10,  0, 10}    // Frame 10: Strike + bonus rolls
                }},
        {.expected_score = 270,
                .game = {
                        {10,  0,  0},   // Frame 1: Strike
                        {10 , 0,  0},   // Frame 2: Spare
                        {10,  0,  0},   // Frame 3: Open frame
                        {10,  0,  0},   // Frame 4: Strike
                        {10,  0,  0},   // Frame 5: Strike
                        {10,  0,  0},   // Frame 6: Strike
                        {10,  0,  0},   // Frame 7: Strike
                        {10,  0,  0},   // Frame 8: Strike
                        {10,  0,  0},   // Frame 9: Strike + bonus rolls
                        { 0, 10, 10}    // Frame 10: Strike + bonus rolls
                }},
        {.expected_score = 279,
                .game = {
                        {10,  0,  0},   // Frame 1: Strike
                        {10,  0,  0},   // Frame 2: Spare
                        {10,  0,  0},   // Frame 3: Open frame
                        {10,  0,  0},   // Frame 4: Strike
                        {10,  0,  0},   // Frame 5: Strike
                        {10,  0,  0},   // Frame 6: Strike
                        {10,  0,  0},   // Frame 7: Strike
                        {10,  0,  0},   // Frame 8: Strike
                        {10,  0,  0},   // Frame 9: Strike + bonus rolls
                        { 9,  1, 10}    // Frame 10: Strike + bonus rolls
                }},
};


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

/********************************* ALL INVALID ENTRIES WILL RESULT IN A ROLL OF 0**********************/

void test_a_roll_cant_exceed_10(void)
{
    int roll_to_record = 11;
    game_t game = create_game();
    record_roll(&game, roll_to_record, 0, 0);
    TEST_ASSERT_EQUAL(0, game.frames[0].roll_1);

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

void test_the_sum_of_the_two_rolls_are_not_greater_than_10(void)
{
    int roll_to_record = 7;
    int roll_to_record_2 = 5;

    game_t game = create_game();
    record_roll(&game, roll_to_record, 0, 0);
    record_roll(&game, roll_to_record_2, 0, 1);

    TEST_ASSERT_LESS_THAN(10, (game.frames[0].roll_1 + game.frames[0].roll_2));

    destroy_game(game);
}

/****************************************************************************************/

void test_10_between_two_rolls_is_a_spare(void)
{
    int roll_to_record = 7;
    int roll_to_record_2 = 3;
    game_t game = create_game();
    record_roll(&game, roll_to_record, 0, 0);
    record_roll(&game, roll_to_record_2, 0, 1);
    TEST_ASSERT_EQUAL(10, game.frames[0].roll_1 + game.frames[0].roll_2);

    destroy_game(game);
}

void test_10_on_the_first_roll_is_a_strike(void)
{
    int roll_to_record = 10;
    game_t game = create_game();
    record_roll(&game, roll_to_record, 0, 0);
    TEST_ASSERT_EQUAL(10, game.frames[0].roll_1);
    destroy_game(game);
}

void test_less_than_10_between_two_rolls_is_an_open_frame(void)
{
    int roll_to_record = 5;
    int roll_to_record_2 = 4;
    game_t game = create_game();
    record_roll(&game, roll_to_record, 0, 0);
    record_roll(&game, roll_to_record_2, 0, 1);
    TEST_ASSERT_LESS_THAN(10, game.frames[0].roll_1 + game.frames[0].roll_2);
    destroy_game(game);
}


void test_a_strike_adds_the_score_of_the_next_two_rolls__next_frame_is_open(void)
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

void test_a_strike_adds_the_score_of_the_next_two_rolls__next_frame_is_spare(void)
{
    int roll_to_record = 10;
    int roll_to_record_2 = 7;
    int roll_to_record_3 = 3;
    game_t game = create_game();
    record_roll(&game, roll_to_record, 0, 0);
    record_roll(&game, roll_to_record_2, 1, 0);
    record_roll(&game, roll_to_record_3, 1, 1);
    int score = handle_strike(game, 0);
    TEST_ASSERT_EQUAL(20, score);

    destroy_game(game);
}

void test_a_strike_adds_the_score_of_the_next_two_rolls__next_frame_is_strike(void)
{
    int roll_to_record = 10;
    int roll_to_record_2 = 10;
    int roll_to_record_3 = 5;
    game_t game = create_game();
    record_roll(&game, roll_to_record, 0, 0);
    record_roll(&game, roll_to_record_2, 1, 0);
    record_roll(&game, roll_to_record_3, 2, 0);
    int score = handle_strike(game, 0);
    TEST_ASSERT_EQUAL(25, score);

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
    int score = record_frames(game, rolls_perfect_game,1);
    TEST_ASSERT_EQUAL(expected_score,score);
    destroy_game(game);
}

void test_the_score_of_a_game_is_as_expected(void)
{
   for (int i = 0; i < 5; i++) {
       int expected_score = 258;
       game_t game = create_game();
       int score = record_frames(game, sample_games[i].game, 1);
       TEST_ASSERT_EQUAL(sample_games[i].expected_score, score);
       destroy_game(game);
    }
}

void run_tests(void)
{
    UnityBegin("Running Tests");

    RUN_TEST(test_a_game_has_ten_frames);
//  RUN_TEST(test_a_frame_has_two_rolls);       // Not testable yet.
    RUN_TEST(test_a_roll_cant_exceed_10);
    RUN_TEST(test_a_roll_cant_be_less_than_0);
    RUN_TEST(test_the_sum_of_the_two_rolls_are_not_greater_than_10);

//  RUN_TEST(test_zero_on_any_roll_is_a_gutter_ball); // Not testable yet.
    RUN_TEST(test_10_on_the_first_roll_is_a_strike);
//  RUN_TEST(test_three_strikes_in_a_row_is_a_turkey); // Not testable yet.
    RUN_TEST(test_10_between_two_rolls_is_a_spare);
    RUN_TEST(test_less_than_10_between_two_rolls_is_an_open_frame);



    RUN_TEST(test_a_strike_adds_the_score_of_the_next_two_rolls__next_frame_is_open);
    RUN_TEST(test_a_strike_adds_the_score_of_the_next_two_rolls__next_frame_is_spare);
    RUN_TEST(test_a_strike_adds_the_score_of_the_next_two_rolls__next_frame_is_strike);

    RUN_TEST(test_a_spare_adds_the_score_of_the_next_roll);
    RUN_TEST(test_a_spare_adds_the_score_of_the_next_roll_in_last_frame);

    /** Not Testable yet. Will likely become testable if app is upgraded to take user input*/
//  RUN_TEST(test_the_tenth_frame_can_have_three_rolls);
//  RUN_TEST(test_a_strike_on_the_first_roll_yields_two_more_rolls);
//  RUN_TEST(test_a_spare_produces_a_third_roll_in_the_tenth_frame);


    RUN_TEST(test_the_score_of_a_perfect_game_is_300);
    RUN_TEST(test_the_score_of_a_game_is_as_expected);
    UnityEnd();

}