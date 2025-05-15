//
// Created by Joseph-Scollo on 5/9/25.
//

#include <stdlib.h>
#include <printf.h>
#include "game_attributes.h"

game_t *create_game(void) {
    game_t *game = malloc(sizeof(game_t));
    if (game == NULL) {
        return NULL; // Memory allocation failed
    }

    for (int i = 0; i < NUM_OF_FRAMES; i++) {
        game->frames[i] = malloc(sizeof(frame_t));
        if (game->frames[i] == NULL) {
            destroy_game(game);
            return NULL; // Memory allocation failed
        }
        game->frames[i]->roll_1 = 0;
        game->frames[i]->roll_2 = 0;
        game->frames[i]->extra_roll = 0;
    }

    return game;
}

void destroy_game(game_t *game) {
    if (game == NULL) {
        return;
    }

    for (int i = 0; i < NUM_OF_FRAMES; i++) {
        free(game->frames[i]);
    }
    free(game);
}

static int handle_strike(game_t *game, int frame_number) {
    int score = 0;
    if(game->frames[frame_number]->roll_1 == 10){
        if(frame_number == 8){
            score += 10 + game->frames[frame_number + 1]->roll_1 + game->frames[frame_number + 1]->roll_2;
            return score;
        }
        if(game->frames[frame_number + 1]->roll_1 != 10){
            score += 10 + game->frames[frame_number + 1]->roll_1 + game->frames[frame_number + 1]->roll_2;
        }
        else{
            score += 10 + game->frames[frame_number + 1]->roll_1 + game->frames[frame_number + 2]->roll_1;
        }
    }
    return score;
}

static int handle_open_frame(game_t *game, int frame_number) {
    int score = 0;

    if (game->frames[frame_number]->roll_1 + game->frames[frame_number]->roll_2 < 10) {
        score += game->frames[frame_number]->roll_1 + game->frames[frame_number]->roll_2;
    }
    return score;
}

static int handle_tenth_frame(game_t *game) {
    int score = 0;
    int last_frame = 9;
    if (game->frames[last_frame]->roll_1 == 10 || game->frames[last_frame]->roll_1 + game->frames[last_frame]->roll_2 == 10) {
        score += 10 + game->frames[last_frame]->roll_1 + game->frames[last_frame]->roll_2 + game->frames[last_frame]->extra_roll;
    }
    return score;
}

static int handle_spare(game_t *game, int frame_number) {
    int score = 0;
    if (game->frames[frame_number]->roll_1 + game->frames[frame_number]->roll_2 == 10 && game->frames[frame_number]->roll_1 != 10) {
        score += 10 + game->frames[frame_number + 1]->roll_1;
    }
    return score;
}

void update_score(game_t *game, int frame_number)
{
    if (game == NULL || frame_number < 0 || frame_number >= NUM_OF_FRAMES) {
        return; // Invalid game or frame number
    }

    int score = 0;
    for (int i = 0; i <= frame_number; i++) {

       if (i == 9) {
           score += handle_tenth_frame(game);
       }
       if(i < 9) {
           score += handle_strike(game, i);
           score += handle_spare(game, i);
       }
       score += handle_open_frame(game, i);
        printf("Score for frame %d: %d\n", i + 1, score);

    }


}


static int (check_for_invalid_rolls)(int roll, game_t *game, int frame_number) {
    if (roll < 0 ) {
        return 0;
    }
    if (roll > 10) {
        printf("Invalid roll1\n");
        return 10;
    }
    if (frame_number != 9 && (game->frames[frame_number]->roll_1 + roll) > 10) {
        printf("Invalid roll2\n");
        return 10 - game->frames[frame_number]->roll_1;
    }
    if (frame_number == 9 && (game->frames[frame_number]->roll_1 + roll) > 10) {
        printf("Invalid roll3\n");
        printf("roll_1: %d, roll_2: %d\n", game->frames[frame_number]->roll_1, game->frames[frame_number]->roll_2);
        printf("roll: %d\n", roll);
        return 10;
    }
    return roll;
}

void record_roll(game_t *game, int roll, int frame_number, int roll_number) {
   // printf("in record_roll    Roll is %d:\n", roll);
    if(roll_number == 0){
        game->frames[frame_number]->roll_1 = check_for_invalid_rolls(roll, game, frame_number);
        return;
    }
    if(roll_number == 1){
        game->frames[frame_number]->roll_2 = check_for_invalid_rolls(roll, game, frame_number);
        return;
    }
    if(  frame_number == 9
       && roll_number == 2
       && game->frames[frame_number]->roll_1 + game->frames[frame_number]->roll_2 == 10)
    {
        game->frames[frame_number]->extra_roll = roll;
        return;
    }
    if(game->frames[frame_number]->roll_1 == -1) {
        game->frames[frame_number]->roll_1 = roll;
        return;
    }
    game->frames[frame_number]->roll_2 = roll;


}