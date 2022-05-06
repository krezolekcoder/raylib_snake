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
    uint32_t x_pos;
    uint32_t y_pos;
} snake_elem_t;

/****************** SNAKE INTERFACE *************************************/

/**
 * @brief Initializes snake with starting head x,y coordinates . 
 * 
 * @param x_start_head_pos 
 * @param y_start_head_pos 
 */
void snake_init(uint32_t x_start_head_pos, uint32_t y_start_head_pos);

/**
 * @brief Defines which movement is possible for snake head based on internal lookup table of possible movements 
 * 
 * @param movement 
 * @return true assigning movement is possible
 * @return false this movement is not possible
 */
bool snake_set_head_movement(const movement_t movement);

/**
 * @brief Updates snake current possition according to time passed 
 * 
 * @param current_time current time in seconds 
 * @return true update of snake position went ok 
 * @return false update is not possible because of snake collision 
 */
bool snake_update(const float current_time);

/**
 * @brief 
 * 
 * @return uint32_t 
 */
uint32_t snake_get_len(void);


/**
 * @brief helper function, returns current time used in snake module
 * 
 * @return float 
 */
float snake_get_time(void);

/**
 * @brief Returns pointer to snake coords buffer 
 * 
 * @return snake_elem_t* 
 */
snake_elem_t *snake_get_snake_coords(void);

/******************* SNAKE FOOD INTERFACE *******************************/

bool snake_food_init(uint32_t x_food_start_pos, uint32_t y_food_start_pos);
void snake_food_update(void);
bool snake_food_create_new_food(uint32_t x_food_new_pos, uint32_t y_food_new_pos);
snake_food_status_t snake_food_get_status(void);
uint32_t snake_food_get_x_pos(void);
uint32_t snake_food_get_y_pos(void);

#endif // SNAKE_H
