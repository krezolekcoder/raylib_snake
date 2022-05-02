#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>
#include <stdint.h>

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

/****************** SNAKE INTERFACE *************************************/

void snake_init(uint32_t x_start_head_pos, uint32_t y_start_head_pos);
bool snake_set_head_movement(const movement_t movement);
bool snake_update(const float current_time);
uint32_t snake_get_len(void);
snake_elem_t *snake_get_snake_coords(void);
float snake_get_time(void);

/******************* SNAKE FOOD INTERFACE *******************************/
bool snake_food_init(uint32_t x_food_start_pos, uint32_t y_food_start_pos);
void snake_food_update(void);
bool snake_food_create_new_food(uint32_t x_food_new_pos, uint32_t y_food_new_pos);
snake_food_status_t snake_food_get_status(void);
uint32_t snake_food_get_x_pos(void);
uint32_t snake_food_get_y_pos(void);

#endif // SNAKE_H
