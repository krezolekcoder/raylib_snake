

#include "snake.h"
#include "config.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SNAKE_HEAD_IDX (0U)
#define SNAKE_SPEED (1U) // 1 block size
#define MOVEMENT_CNT (4U)

typedef struct
{
    int x_pos;
    int y_pos;
    snake_food_status_t food_status;
} snake_food_t;

static snake_elem_t prv_snake[SNAKE_MAX_LEN];
static snake_food_t prv_snake_food;
static movement_t prv_snake_head_movement = MOVEMENT_RIGHT;

/* Lookup table for prohibited movement f.ex if snake is moving in right direction, the left direction is not possible
 * LUT indexing according to movement_t enum */

static movement_t prv_snake_movement_not_possible_lookup[MOVEMENT_CNT] = {MOVEMENT_DOWN, MOVEMENT_UP, MOVEMENT_RIGHT, MOVEMENT_LEFT};

static uint32_t prv_snake_len;
static float prv_snake_movement_update_time;

static bool prv_check_if_snake_head_update_possible(void);
static void prv_snake_update_head(void);

void snake_init(uint32_t x_start_head_pos, uint32_t y_start_head_pos)
{
    prv_snake_len = 1;
    prv_snake[SNAKE_HEAD_IDX].x_pos = x_start_head_pos;
    prv_snake[SNAKE_HEAD_IDX].y_pos = y_start_head_pos;
    prv_snake_head_movement = MOVEMENT_RIGHT;
    prv_snake_movement_update_time = 0.0f;
}

bool snake_update(float current_time)
{
    bool result = false;

    if (current_time - prv_snake_movement_update_time >= SNAKE_UPDATE_TIMEOUT_SEC)
    {
        /* update coordinates of all snake */

        result = prv_check_if_snake_head_update_possible();

        if (result)
        {
            for (int i = prv_snake_len - 1; i >= 1; i--)
            {
                prv_snake[i].x_pos = prv_snake[i - 1].x_pos;
                prv_snake[i].y_pos = prv_snake[i - 1].y_pos;
            }

            prv_snake_update_head();

            /* check if food has been eaten, if so change food status */
            if ((prv_snake[SNAKE_HEAD_IDX].x_pos == prv_snake_food.x_pos) && (prv_snake[SNAKE_HEAD_IDX].y_pos == prv_snake_food.y_pos))
            {
                prv_snake_food.food_status = FOOD_EATEN;
            }
        }

        prv_snake_movement_update_time = current_time;
    }

    return result;
}

bool snake_set_head_movement(movement_t movement)
{
    bool result = true;
    if (prv_snake_head_movement == prv_snake_movement_not_possible_lookup[movement])
    {
        result = false;
    }
    else
    {
        prv_snake_head_movement = movement;
    }

    return result;
}

bool snake_food_init(uint32_t x_food_start_pos, uint32_t y_food_start_pos)
{
    prv_snake_food.food_status = FOOD_GENERATE_NEW;

    return snake_food_create_new_food(x_food_start_pos, y_food_start_pos);
}

void snake_food_update(void)
{

    switch (prv_snake_food.food_status)
    {
    case FOOD_NOT_EATEN:
        break;

    case FOOD_EATEN:
        prv_snake[prv_snake_len].x_pos = prv_snake_food.x_pos;
        prv_snake[prv_snake_len].y_pos = prv_snake_food.y_pos;
        prv_snake_len++;

        prv_snake_food.food_status = FOOD_GENERATE_NEW;
        break;

    case FOOD_GENERATE_NEW:

        break;
    default:
        break;
    }
}

bool snake_food_create_new_food(uint32_t x_food_new_pos, uint32_t y_food_new_pos)
{
    bool result = false;

    if (prv_snake_food.food_status != FOOD_GENERATE_NEW)
    {
        return result;
    }

    for (int i = 0; i < prv_snake_len; i++)
    {
        if (prv_snake[i].x_pos != x_food_new_pos || prv_snake[i].y_pos != y_food_new_pos)
        {
            result = true;
            prv_snake_food.x_pos = x_food_new_pos;
            prv_snake_food.y_pos = y_food_new_pos;
            prv_snake_food.food_status = FOOD_NOT_EATEN;
        }
        else
        {
            result = false;
            prv_snake_food.food_status = FOOD_GENERATE_NEW;
            break;
        }
    }

    return result;
}

snake_food_status_t snake_food_get_status(void)
{
    return prv_snake_food.food_status;
}

snake_elem_t *snake_get_snake_coords(void)
{
    return &prv_snake[0];
}

uint32_t snake_food_get_x_pos(void)
{
    return prv_snake_food.x_pos;
}

uint32_t snake_food_get_y_pos(void)
{
    return prv_snake_food.y_pos;
}

uint32_t snake_get_len(void)
{
    return prv_snake_len;
}

static bool prv_check_if_snake_head_update_possible(void)
{

    uint32_t x_pos = prv_snake[SNAKE_HEAD_IDX].x_pos;
    uint32_t y_pos = prv_snake[SNAKE_HEAD_IDX].y_pos;

    // TODO - code duplication, maybe implement some function which returns updated coords of snake
    switch (prv_snake_head_movement)
    {
    case MOVEMENT_LEFT:
        x_pos -= SNAKE_SPEED;
        break;

    case MOVEMENT_RIGHT:
        x_pos += SNAKE_SPEED;
        break;

    case MOVEMENT_UP:
        y_pos -= SNAKE_SPEED;
        break;

    case MOVEMENT_DOWN:
        y_pos += SNAKE_SPEED;
        break;
    default:
        break;
    }

    if (x_pos < 0 || y_pos < 0 || x_pos >= SCREEN_WIDTH_BLOCK_CNT || y_pos >= SCREEN_HEIGHT_BLOCK_CNT)
    {
        return false;
    }

    return true;
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
    default:
        break;
    }
}

float snake_get_time(void)
{
    return prv_snake_movement_update_time;
}