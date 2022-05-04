/** How to build
 * Enter in terminal :
 * gcc src/main.c src/snake.c src/ring_buffer.c -o game.exe -O3 -Wall -std=c99 -Wno-missing-braces -I include/ -I src/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
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
#include "ring_buffer.h"

static void prv_snake_draw(void);
static void prv_snake_food_draw(void);
static void prv_grid_draw(void);

static char prv_current_time_text[100];

static void prv_snake_food_draw(void);

static uint8_t inputs_buff[100];
static ring_buffer_t input_ring_buf;

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

    ring_buffer_init(&input_ring_buf, inputs_buff, sizeof(inputs_buff) / sizeof(uint8_t));

    printf("head %d tail %d capacity %d \r\n", input_ring_buf.head_idx, input_ring_buf.tail_idx, input_ring_buf.buff_capacity);

    double input_process_time = GetTime();
    //--------------------------------------------------------------------------------------
    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        current_time = GetTime();
        // Update
        //----------------------------------------------------------------------------------

        KeyboardKey key_pressed = GetKeyPressed();

        if (key_pressed != 0)
        {
            ring_buffer_write(&input_ring_buf, (uint8_t)key_pressed);
        }

        if (current_time - input_process_time >= 0.25f)
        {
            if (ring_buffer_get_elems_cnt(&input_ring_buf) != 0)
            {
                uint8_t key;

                if (ring_buffer_read(&input_ring_buf, &key))
                {
                    printf("key read %d", key);
                    switch (key)
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
                }
            }

            input_process_time = current_time;
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
