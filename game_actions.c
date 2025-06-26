//
// Created by Joseph-Scollo on 5/9/25.
//

#include <stdlib.h>
#include <printf.h>
#include <string.h>
#include "game_attributes.h"
#define FRAME_WIDTH 10

void create_game(game_t *game) {
    memset(game, 0, sizeof(game_t));
}

void destroy_game(game_t game) {

    for (int i = 0; i < NUM_OF_FRAMES; ++i) {
        game.frames[i].roll_1 = 0;
        game.frames[i].roll_2 = 0;
        game.frames[i].extra_roll = 0;
    }
}

int handle_strike(game_t *game, int frame_number) {
    int score = 0;
    int next_frame_first_roll              = game->frames[NEXT_FRAME(frame_number)].roll_1;
    int frame_after_next_first_roll        = game->frames[NEXT_FRAME(NEXT_FRAME(frame_number))].roll_1;
    int next_frame_second_roll             = game->frames[NEXT_FRAME(frame_number)].roll_2;

    int combined_consecutive_frames_roll_1 = next_frame_first_roll + frame_after_next_first_roll;
    int combined_rolls_of_next_frame       = next_frame_first_roll + next_frame_second_roll;

    if (STRIKE(game->frames[frame_number].roll_1)){
        if(   STRIKE(game->frames[NEXT_FRAME(frame_number)].roll_1) == false
           || (STRIKE(game->frames[NEXT_FRAME(frame_number)].roll_1) && NEXT_FRAME(frame_number) == LAST_FRAME))
        {
            score += 10 + combined_rolls_of_next_frame;
        }
        else{
            score += 10 + combined_consecutive_frames_roll_1;
        }
    }
    return score;
}

int handle_open_frame(game_t *game, int frame_number) {
    int score = 0;

    if (OPEN_FRAME(game->frames[frame_number].roll_1, game->frames[frame_number].roll_2)){
        score += game->frames[frame_number].roll_1 + game->frames[frame_number].roll_2;
    }
    return score;
}

int handle_tenth_frame(game_t *game) {
    int score = 0;
    if (STRIKE(game->frames[LAST_FRAME].roll_1) || SPARE(game->frames[LAST_FRAME].roll_1, game->frames[LAST_FRAME].roll_2)) {
        score += game->frames[LAST_FRAME].roll_1 + game->frames[LAST_FRAME].roll_2 + game->frames[LAST_FRAME].extra_roll;
    }
    return score;
}

int handle_spare(game_t *game, int frame_number) {
    int score = 0;
    if (SPARE(game->frames[frame_number].roll_1, game->frames[frame_number].roll_2)) {
        score += 10 + game->frames[NEXT_FRAME(frame_number)].roll_1;
    }
    return score;
}

static void print_rolls(game_t *game, int frame_number) {

    if (frame_number < 0 || frame_number >= NUM_OF_FRAMES) {
        return; // Invalid game or frame number
    }

    if(frame_number != LAST_FRAME) {
        printf(" ");
        if (STRIKE(game->frames[frame_number].roll_1)) {
            printf("%-11s","|X|-|");
        } else if (SPARE(game->frames[frame_number].roll_1, game->frames[frame_number].roll_2)) {
            printf("|%d|/|%-5s", game->frames[frame_number].roll_2, "");
        } else {
            printf(" |%d|%d|%-6s", game->frames[frame_number].roll_1, game->frames[frame_number].roll_2, "");
        }
    }
    if(frame_number == LAST_FRAME){
        if(   STRIKE(game->frames[frame_number].roll_1)
           && STRIKE(game->frames[frame_number].roll_2)
           && STRIKE(game->frames[frame_number].extra_roll))
        {
            printf(" |X|X|X|");
        }
        else if(   SPARE(game->frames[frame_number].roll_1, game->frames[frame_number].roll_2)
                && STRIKE(game->frames[frame_number].extra_roll))
        {
            printf(" |%d|/|X|", game->frames[frame_number].roll_2);
        }
        else if(   STRIKE(game->frames[frame_number].roll_1)
                && SPARE(game->frames[frame_number].roll_2, game->frames[frame_number].extra_roll))
        {
            printf(" |X|%d|/|",game->frames[frame_number].roll_2);
        }
        else if(   STRIKE(game->frames[frame_number].roll_1)
                && OPEN_FRAME(game->frames[frame_number].roll_2, game->frames[frame_number].extra_roll))
        {
            printf(" |X|%d|%d|", game->frames[frame_number].roll_2, game->frames[frame_number].extra_roll);
        }
        else if(   SPARE(game->frames[frame_number].roll_1, game->frames[frame_number].roll_2)
                && OPEN_FRAME(game->frames[frame_number].extra_roll, 0))
        {
            printf(" |%d|/|%d|", game->frames[frame_number].roll_2, game->frames[frame_number].extra_roll);
        }
        else{
            printf(" |%d|%d|-|", game->frames[frame_number].roll_1, game->frames[frame_number].roll_2);
        }
    }


}

static int frame_score[10];

static void print_score(int score, int frame_number) {

    printf("  ");
    for (int i = 0; i <= frame_number; ++i) {
        printf("%-12d", frame_score[i]);
    }
    printf("\n");

}

static void print_recoreded_rolls(game_t *game, int frame_number) {
    for(int i = 0; i <= frame_number; ++i) {
        print_rolls( game, i);
    }
    printf("\n");
}

static void print_frame_header(void) {
    for (int i = 0; i < NUM_OF_FRAMES; ++i) {
        printf("Frame: %d    ", i + 1);
    }
    printf("\n");
}

static void print_score_board(int frame_number, game_t *game, int score) {

    print_frame_header();
    print_recoreded_rolls(game, frame_number);
    print_score(score, frame_number);
}

int update_score(game_t *game, int frame_number)
{
    if (frame_number < 0 || frame_number >= NUM_OF_FRAMES) {
        return 0; // Invalid game or frame number
    }

    int score = 0;

    for (int i = 0; i <= frame_number ; ++i) {
        if (i == 9) {
            score += handle_tenth_frame(game);
            frame_score[i] = score;
        }
        if(i < 9) {
            score += handle_strike(game, i);
            score += handle_spare(game, i);
            frame_score[i] = score;
        }
        score += handle_open_frame(game, i);
        frame_score[i] = score;
    }

    return score;
}

static int (check_for_invalid_rolls)(int roll, game_t *game, int frame_number) {
    if (roll < 0 ) {
        return 0;
    }
    if (roll > 10) {
        printf("Invalid roll1\n");
        return 0;
    }
    if (frame_number != LAST_FRAME && (game->frames[frame_number].roll_1 + roll) > 10) {
        printf("Invalid roll2\n");
        return 0;
    }
    if (   frame_number == 9
        && (game->frames[frame_number].roll_1 + game->frames[frame_number].roll_2) != 10
        && (game->frames[frame_number].extra_roll > 0)) {
        printf("Invalid roll3\n");
        printf("roll_1: %d, roll_2: %d\n", game->frames[frame_number].roll_1, game->frames[frame_number].roll_2);
        printf("roll: %d\n", roll);
        return 0;
    }
    return roll;
}

void record_roll(game_t *game, int roll, int frame_number, int roll_number)
{
    if(roll_number == 0 && frame_number != LAST_FRAME){
        game->frames[frame_number].roll_1 = check_for_invalid_rolls(roll, game, frame_number);
        return;
    }
    if(roll_number == 1 && frame_number != LAST_FRAME){
        game->frames[frame_number].roll_2 = check_for_invalid_rolls(roll, game, frame_number);
        return;
    }
    if(frame_number == LAST_FRAME && roll_number == 0)
    {
        game->frames[frame_number].roll_1 = check_for_invalid_rolls(roll, game, frame_number);
        return;
    }
    if(frame_number == LAST_FRAME && roll_number == 1){
        game->frames[frame_number].roll_2 = check_for_invalid_rolls(roll, game, frame_number);
        return;
    }
    if(frame_number == LAST_FRAME && roll_number == 2){
        game->frames[frame_number].extra_roll = check_for_invalid_rolls(roll, game, frame_number);
        return;
    }
}

void run_game_loop(game_t *game, int rolls[NUM_OF_FRAMES][3])
{
    int score = 0;

    for (int i = 0; i < NUM_OF_FRAMES; ++i) {
        for (int j = 0; j < 3; ++j) {
            record_roll(game, rolls[i][j], i, j);
        }
        update_score(game, i);
        print_score_board(i, game, score);
    }
}