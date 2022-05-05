/** How to build
 * Enter in terminal :
 * gcc src/main.c src/pong.c  -o pong.exe -O3 -Wall -std=c99 -Wno-missing-braces -I include/ -I src/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
 * Compiler : gcc (i686-posix-dwarf-rev0, Built by MinGW-W64 project) 8.1.0
 **/

#include <../include/raylib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "config.h"

static void prv_grid_draw(void);

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    double current_time = GetTime();

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] example - basic window");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    double input_process_time = GetTime();
    //--------------------------------------------------------------------------------------
    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        prv_grid_draw();

        ClearBackground(RAYWHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

static void prv_grid_draw(void)
{
    for (int i = 0; i < SCREEN_WIDTH_BLOCK_CNT; i++)
    {
        for (int j = 0; j < SCREEN_HEIGHT_BLOCK_CNT; j++)
        {
            DrawRectangleLines(BLOCK_SIZE * i, BLOCK_SIZE * j, BLOCK_SIZE, BLOCK_SIZE, GRAY);
        }
    }
}