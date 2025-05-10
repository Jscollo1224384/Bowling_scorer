//
// Created by Joseph-Scollo on 5/9/25.
//

#ifndef BOWLING_SCORER_GAME_ATTRIBUTES_H
#define BOWLING_SCORER_GAME_ATTRIBUTES_H
#define NUM_OF_FRAMES 10
typedef struct {
    int roll_1;
    int roll_2;
    int extra_roll;
} frame_t;

typedef struct {
    frame_t *frames[NUM_OF_FRAMES];
} game_t;

game_t *create_game(void);
void destroy_game(game_t *game);
#endif //BOWLING_SCORER_GAME_ATTRIBUTES_H
