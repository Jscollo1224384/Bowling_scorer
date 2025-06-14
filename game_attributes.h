//
// Created by Joseph-Scollo on 5/9/25.
//

#ifndef BOWLING_SCORER_GAME_ATTRIBUTES_H
#define BOWLING_SCORER_GAME_ATTRIBUTES_H

#include <stdbool.h>

#define NUM_OF_FRAMES 10
#define LAST_FRAME   (NUM_OF_FRAMES - 1)
#define STRIKE(x)    ((x) == 10)
#define SPARE(x, y) (((x) + (y) == 10) && ((x) != 10))
#define OPEN_FRAME(x, y) ((x) + (y) < 10)
#define NEXT_FRAME(x) ((x) + 1)

typedef struct {
    int  roll_1;
    int  roll_2;
    int  extra_roll;
} frame_t;

typedef struct {
    frame_t frames[NUM_OF_FRAMES];
} game_t;


game_t create_game(void);
void destroy_game(game_t game);
void record_roll(game_t *game, int roll, int frame_number, int roll_number);
int record_frames(game_t game, int rolls[10][3]);
int handle_strike(game_t game, int frame_number);
int handle_spare(game_t game, int frame_number);
int handle_open_frame(game_t game, int frame_number);
int handle_tenth_frame(game_t game);
int update_score(game_t game, int frame_number, int debug);
#endif //BOWLING_SCORER_GAME_ATTRIBUTES_H
