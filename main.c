#include <stdio.h>
#include <string.h>
#include "test_cases.h"
#include "Unity-2.6.1/src/unity.h"
#include "game_attributes.h"

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "debug") == 0) {
        printf("Debug mode enabled.\n");
        run_tests();
    } else {
        printf("Running in normal mode.\n");
    }
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
    game_t *game = create_game();
    record_frames(game, rolls_game);

    return 0;
}
