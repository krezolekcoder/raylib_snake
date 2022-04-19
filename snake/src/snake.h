#ifndef SNAKE_H
#define SNAKE_H

typedef enum
{
    MOVEMENT_UP = 0,
    MOVEMENT_DOWN = 1,
    MOVEMENT_LEFT = 2,
    MOVEMENT_RIGHT = 3,
} movement_t;

typedef struct
{
    int x_pos;
    int y_pos;
    movement_t movement_dir;
} snake_elem_t;

void snake_init(unsigned int x_start_head_pos, unsigned int y_start_head_pos);
void snake_set_head_movement(const movement_t movement);
void snake_update(const float current_time);

unsigned int snake_get_len(void);
snake_elem_t *snake_get_grid(void);

void snake_food_init(unsigned int x_food_start_pos, unsigned int y_food_start_pos);
void snake_food_update(void);
unsigned int snake_food_get_x_pos(void);
unsigned int snake_food_get_y_pos(void);

#endif // SNAKE_H
