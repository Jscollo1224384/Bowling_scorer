//
// Created by Joseph-Scollo on 5/9/25.
//

#include <stdlib.h>
#include <printf.h>
#include <string.h>
#include "game_attributes.h"

game_t create_game(void) {
    game_t game;
    memset(&game, 0, sizeof(game_t));
    return game;
}

void destroy_game(game_t game) {

    for (int i = 0; i < NUM_OF_FRAMES; ++i) {
        game.frames[i].roll_1 = 0;
        game.frames[i].roll_2 = 0;
        game.frames[i].extra_roll = 0;
    }
}

int handle_strike(game_t game, int frame_number) {
    int score = 0;
    int next_frame_first_roll              = game.frames[NEXT_FRAME(frame_number)].roll_1;
    int frame_after_next_first_roll        = game.frames[NEXT_FRAME(NEXT_FRAME(frame_number))].roll_1;
    int next_frame_second_roll             = game.frames[NEXT_FRAME(frame_number)].roll_2;

    int combined_consecutive_frames_roll_1 = next_frame_first_roll + frame_after_next_first_roll;
    int combined_rolls_of_next_frame       = next_frame_first_roll + next_frame_second_roll;

    if (STRIKE(game.frames[frame_number].roll_1)){
        if(   STRIKE(game.frames[NEXT_FRAME(frame_number)].roll_1) == false
           || STRIKE(game.frames[NEXT_FRAME(frame_number)].roll_1) && NEXT_FRAME(frame_number) == LAST_FRAME)
        {
            score += 10 + combined_rolls_of_next_frame;
        }
        else{
            score += 10 + combined_consecutive_frames_roll_1;
        }
    }
    return score;
}

int handle_open_frame(game_t game, int frame_number) {
    int score = 0;

    if (OPEN_FRAME(game.frames[frame_number].roll_1, game.frames[frame_number].roll_2)){
        score += game.frames[frame_number].roll_1 + game.frames[frame_number].roll_2;
    }
    return score;
}

int handle_tenth_frame(game_t game) {
    int score = 0;
    if (STRIKE(game.frames[LAST_FRAME].roll_1) || SPARE(game.frames[LAST_FRAME].roll_1, game.frames[LAST_FRAME].roll_2)) {
        score += game.frames[LAST_FRAME].roll_1 + game.frames[LAST_FRAME].roll_2 + game.frames[LAST_FRAME].extra_roll;
    }
    return score;
}

int handle_spare(game_t game, int frame_number) {
    int score = 0;
    if (SPARE(game.frames[frame_number].roll_1, game.frames[frame_number].roll_2)) {
        score += 10 + game.frames[NEXT_FRAME(frame_number)].roll_1;
    }
    return score;
}

static void print_score_board(game_t game, int frame_number) {
    if (frame_number < 0 || frame_number >= NUM_OF_FRAMES) {
        return; // Invalid game or frame number
    }

    if(frame_number != 9) {
        if (game.frames[frame_number].roll_1 == 10) {
            printf(" |-|X|      ");
        } else if (game.frames[frame_number].roll_1 + game.frames[frame_number].roll_2 == 10 &&
                   game.frames[frame_number].roll_1 != 10) {
            printf(" |%d|/|      ", game.frames[frame_number].roll_2);
        } else {
            printf(" |%d|%d|      ", game.frames[frame_number].roll_1, game.frames[frame_number].roll_2);
        }
    }
    if(frame_number == 9){
        if(   game.frames[frame_number].roll_1 == 10
           && game.frames[frame_number].roll_2 == 10
           && game.frames[frame_number].extra_roll == 10)
        {
            printf(" |X|X|X|");
        }
        else if(   game.frames[frame_number].roll_1 + game.frames[frame_number].roll_2 == 10
                && game.frames[frame_number].roll_1 != 10
                && game.frames[frame_number].extra_roll == 10)
        {
            printf(" |%d|/|X|", game.frames[frame_number].roll_2);
        }
        else if(   game.frames[frame_number].roll_1 + game.frames[frame_number].roll_2 == 10
                   && game.frames[frame_number].roll_1 == 10
                   && game.frames[frame_number].extra_roll == 10)
        {
            printf(" |X|%d|/|",game.frames[frame_number].roll_2);
        }
        else{
            printf(" |%d|%d| |", game.frames[frame_number].roll_1, game.frames[frame_number].roll_2);
        }
    }


}

int update_score(game_t game, int frame_number)
{
    if (frame_number < 0 || frame_number >= NUM_OF_FRAMES) {
        return 0; // Invalid game or frame number
    }

    int score = 0;
    for (int i = 0; i < NUM_OF_FRAMES; ++i) {
        printf("Frame: %d    ", i + 1);
    }
    printf("\n");

    for (int i = 0; i <= frame_number; i++) {
        print_score_board(game, i);
    }
    printf("\n");

    score = 0;

    for (int i = 0; i <= frame_number ; ++i) {
        if (i == 9) {
            score += handle_tenth_frame(game);
        }
        if(i < 9) {
            score += handle_strike(game, i);
            score += handle_spare(game, i);
        }
        score += handle_open_frame(game, i);

        if(score > 99) {
            if(i != 9) {
                printf("  %d       ", score);
            }
            else{
                printf("   %d     ", score);
            }
        }
        else{
            printf("  %d        ", score);
        }
    }
    printf("\n\n");

    return score;
}

static int (check_for_invalid_rolls)(int roll, game_t *game, int frame_number) {
    if (roll < 0 ) {
        return 0;
    }
    if (roll > 10) {
        printf("Invalid roll1\n");
        return 10;
    }
    if (frame_number != 9 && (game->frames[frame_number].roll_1 + roll) > 10) {
        printf("Invalid roll2\n");
        return 10 - game->frames[frame_number].roll_1;
    }
    if (   frame_number == 9
        && (game->frames[frame_number].roll_1 + game->frames[frame_number].roll_2) != 10
        && (game->frames[frame_number].extra_roll > 0)) {
        printf("Invalid roll3\n");
        printf("roll_1: %d, roll_2: %d\n", game->frames[frame_number].roll_1, game->frames[frame_number].roll_2);
        printf("roll: %d\n", roll);
        return 10;
    }
    return roll;
}

void record_roll(game_t *game, int roll, int frame_number, int roll_number)
{
    if(roll_number == 0 && frame_number != 9){
        game->frames[frame_number].roll_1 = check_for_invalid_rolls(roll, game, frame_number);
        return;
    }
    if(roll_number == 1 && frame_number != 9){
        game->frames[frame_number].roll_2 = check_for_invalid_rolls(roll, game, frame_number);
        return;
    }
    if(frame_number == 9 && roll_number == 0)
    {
        game->frames[frame_number].roll_1 = check_for_invalid_rolls(roll, game, frame_number);
        return;
    }
    if(frame_number == 9 && roll_number == 1){
        game->frames[frame_number].roll_2 = check_for_invalid_rolls(roll, game, frame_number);
        return;
    }
    if(frame_number == 9 && roll_number == 2){
        game->frames[frame_number].extra_roll = check_for_invalid_rolls(roll, game, frame_number);
        return;
    }
}

int record_frames(game_t game, int rolls[10][3])
{
    int score = 0;
    for (int i = 0; i < NUM_OF_FRAMES; i++) {
        for (int j = 0; j < 3; ++j) {
            record_roll(&game, rolls[i][j], i, j);
        }
        score = update_score(game, i);
    }
    return score;
}

