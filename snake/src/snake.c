

#include "snake.h"
#include "config.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SNAKE_HEAD_IDX (0U)
#define SNAKE_SPEED (1U) // 1 block size

typedef struct
{
    int x_pos;
    int y_pos;
    int is_eaten;
} snake_food_t;

static snake_elem_t prv_snake[SNAKE_MAX_LEN];
static snake_food_t prv_snake_food;
static movement_t prv_snake_head_movement = MOVEMENT_RIGHT;

static unsigned int prv_snake_len;
static float prv_snake_movement_update_time;

static void prv_snake_update_head(void);

void snake_init(unsigned int x_start_head_pos, unsigned int y_start_head_pos)
{
    prv_snake_len = 1;
    prv_snake[SNAKE_HEAD_IDX].x_pos = x_start_head_pos;
    prv_snake[SNAKE_HEAD_IDX].y_pos = y_start_head_pos;
    prv_snake_head_movement = MOVEMENT_RIGHT;
    prv_snake_movement_update_time = 0.0f;
}

void snake_update(float current_time)
{
    if (current_time - prv_snake_movement_update_time >= SNAKE_UPDATE_TIMEOUT_SEC)
    {
        for (int i = prv_snake_len - 1; i >= 1; i--)
        {

            prv_snake[i].x_pos = prv_snake[i - 1].x_pos;
            prv_snake[i].y_pos = prv_snake[i - 1].y_pos;
        }

        prv_snake_update_head();
        // printf("snake head %d %d len %d\r\n", prv_snake[SNAKE_HEAD_IDX].x_pos, prv_snake[SNAKE_HEAD_IDX].y_pos, prv_snake_len);

        if ((prv_snake[SNAKE_HEAD_IDX].x_pos == prv_snake_food.x_pos) && (prv_snake[SNAKE_HEAD_IDX].y_pos == prv_snake_food.y_pos))
        {
            prv_snake_food.is_eaten = true;
            // printf("snake food eaten \r\n");
        }

        prv_snake_movement_update_time = current_time;
    }
}

void snake_set_head_movement(movement_t movement)
{
    prv_snake_head_movement = movement;
}

void snake_food_init(unsigned int x_food_start_pos, unsigned int y_food_start_pos)
{
    prv_snake_food.is_eaten = false;
    prv_snake_food.x_pos = x_food_start_pos;
    prv_snake_food.y_pos = y_food_start_pos;
}

void snake_food_update(unsigned int x_food_new_pos, unsigned int y_food_new_pos)
{
    if (prv_snake_food.is_eaten)
    {
        prv_snake[prv_snake_len].x_pos = prv_snake_food.x_pos;
        prv_snake[prv_snake_len].y_pos = prv_snake_food.y_pos;

        prv_snake_food.x_pos = x_food_new_pos;
        prv_snake_food.y_pos = y_food_new_pos;

        prv_snake_len++;
        prv_snake_food.is_eaten = false;
    }
}

snake_elem_t *snake_get_snake_coords(void)
{
    return &prv_snake[0];
}

unsigned int snake_food_get_x_pos(void)
{
    return prv_snake_food.x_pos;
}

unsigned int snake_food_get_y_pos(void)
{
    return prv_snake_food.y_pos;
}

unsigned int snake_get_len(void)
{
    return prv_snake_len;
}

static void prv_snake_update_head(void)
{
    switch (prv_snake_head_movement)
    {
    case MOVEMENT_LEFT:
        prv_snake[SNAKE_HEAD_IDX].x_pos -= SNAKE_SPEED;
        break;

    case MOVEMENT_RIGHT:
        prv_snake[SNAKE_HEAD_IDX].x_pos += SNAKE_SPEED;
        break;

    case MOVEMENT_UP:
        prv_snake[SNAKE_HEAD_IDX].y_pos -= SNAKE_SPEED;
        break;

    case MOVEMENT_DOWN:
        prv_snake[SNAKE_HEAD_IDX].y_pos += SNAKE_SPEED;
        break;
    }
}