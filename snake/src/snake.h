#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>

typedef enum
{
    MOVEMENT_UP = 0,
    MOVEMENT_DOWN = 1,
    MOVEMENT_LEFT = 2,
    MOVEMENT_RIGHT = 3,
} movement_t;

typedef enum
{
    FOOD_NOT_EATEN,
    FOOD_GENERATE_NEW,
    FOOD_EATEN,
} snake_food_status_t;

typedef struct
{
    int x_pos;
    int y_pos;
    movement_t movement_dir;
} snake_elem_t;

void snake_init(unsigned int x_start_head_pos, unsigned int y_start_head_pos);
bool snake_set_head_movement(const movement_t movement);
void snake_update(const float current_time);

unsigned int snake_get_len(void);
snake_elem_t *snake_get_snake_coords(void);

bool snake_food_init(unsigned int x_food_start_pos, unsigned int y_food_start_pos);

void snake_food_update(void);
bool snake_food_create_new_food(unsigned int x_food_new_pos, unsigned int y_food_new_pos);
snake_food_status_t snake_food_get_status(void);
unsigned int snake_food_get_x_pos(void);
unsigned int snake_food_get_y_pos(void);

#endif // SNAKE_H
