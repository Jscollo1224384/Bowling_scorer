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

void record_roll(game_t *game, int roll, int frame_number) {
    if (game == NULL || frame_number < 0 || frame_number >= NUM_OF_FRAMES) {
        return; // Invalid game or frame number
    }
    if (   frame_number == 9
        && (game->frames[frame_number]->roll_1 +
            game->frames[frame_number]->roll_2) == 10)
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