/*******************************************************************************************
 *
 *   raylib [core] example - Basic window
 *
 *   Welcome to raylib!
 *
 *   To test examples, just press F6 and execute raylib_compile_execute script
 *   Note that compiled executable is placed in the same folder as .c file
 *
 *   You can find all basic examples on C:\raylib\raylib\examples folder or
 *   raylib official webpage: www.raylib.com
 *
 *   Enjoy using raylib. :)
 *
 *   This example has been created using raylib 1.0 (www.raylib.com)
 *   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
 *
 *   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

/** How to build
 * Enter in terminal :
 * gcc src/main.c src/snake.c -o game.exe -O3 -Wall -std=c99 -Wno-missing-braces -I include/ -I src/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
 * Compiler : gcc (i686-posix-dwarf-rev0, Built by MinGW-W64 project) 8.1.0
 **/

#include <../include/raylib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "config.h"
#include "snake.h"

static void prv_snake_draw(void);
static void prv_snake_food_draw(void);
static void prv_grid_draw(void);

static char prv_current_time_text[100];

static void prv_snake_food_draw(void);

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    double current_time = GetTime();

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] example - basic window");

    snake_init(5, 5);
    snake_food_init(7, 7);
    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    srand(current_time);
    //--------------------------------------------------------------------------------------
    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        current_time = GetTime();
        // Update
        //----------------------------------------------------------------------------------

        KeyboardKey key_pressed = GetKeyPressed();
        switch (key_pressed)
        {
        case KEY_W:
            snake_set_head_movement(MOVEMENT_UP);
            break;
        case KEY_S:
            snake_set_head_movement(MOVEMENT_DOWN);
            break;
        case KEY_A:
            snake_set_head_movement(MOVEMENT_LEFT);
            break;
        case KEY_D:
            snake_set_head_movement(MOVEMENT_RIGHT);
            break;
        default:
            break;
        }

        if (snake_update(current_time))
        {
            snake_food_update();

            if (snake_food_get_status() == FOOD_GENERATE_NEW)
            {
                bool result = false;
                do
                {
                    uint32_t x_new_food_pos = rand() % (SCREEN_WIDTH_BLOCK_CNT - 1);
                    uint32_t y_new_food_pos = rand() % (SCREEN_HEIGHT_BLOCK_CNT - 1);

                    result = snake_food_create_new_food(x_new_food_pos, y_new_food_pos);
                } while (result == false);
            }
        }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        prv_grid_draw();

        prv_snake_draw();
        prv_snake_food_draw();

        sprintf(prv_current_time_text, " current time %lf", current_time);

        DrawText((const char *)&prv_current_time_text, 25, 25, 10, BLACK);
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

static void prv_snake_draw(void)
{
    snake_elem_t *snake_elem = snake_get_snake_coords();

    DrawRectangle(snake_elem[0].x_pos * BLOCK_SIZE, snake_elem[0].y_pos * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, MAROON);
    for (int i = 1; i < snake_get_len(); i++)
    {
        DrawRectangle(snake_elem[i].x_pos * BLOCK_SIZE, snake_elem[i].y_pos * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, PINK);
    }
}

static void prv_snake_food_draw(void)
{
    DrawRectangle(snake_food_get_x_pos() * BLOCK_SIZE, snake_food_get_y_pos() * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, RED);
}
