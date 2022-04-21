#include "unity.h"

#include "snake.h"
#include "config.h"

void setUp(void)
{
    snake_init(0, 0);
    snake_food_init(0, 0);
}

void tearDown(void)
{
}

void test_snake_moving_simple(void)
{
    snake_init(5, 5);

    snake_set_head_movement(MOVEMENT_RIGHT);
    snake_elem_t *grid = snake_get_grid();

    float current_time = 0.0f;

    snake_update(current_time);

    snake_update(current_time + 0.21f);

    TEST_ASSERT_EQUAL_INT(6, grid[0].x_pos);
}

void test_snake_moving_complex(void)
{
    snake_elem_t *grid = snake_get_grid();

    snake_set_head_movement(MOVEMENT_DOWN);

    float current_time = 0.0f;

    snake_update(current_time);

    /* update 10 times - about 2 seconds passed virtually */
    for (int i = 0; i < 10; i++)
    {
        snake_update(current_time + i * (SNAKE_UPDATE_TIMEOUT_SEC + 0.01f));
    }

    TEST_ASSERT_EQUAL_INT(9, grid[0].y_pos);
}

void test_snake_food_eating(void)
{
    snake_food_init(1, 1);
    snake_elem_t *grid = snake_get_grid();
    /* initial snake position is x 0 y 0 food is 1 1 so we must go 1 to the right 1 down  virtually */

    float current_time = 0.0f;
    snake_set_head_movement(MOVEMENT_RIGHT);

    /* update of position happens every 0.2s */
    snake_update(current_time + 0.21f);

    snake_food_update();

    snake_set_head_movement(MOVEMENT_DOWN);

    snake_update(current_time + 0.63f);
    snake_food_update();

    /* Check if food x coordinate has changed */

    TEST_ASSERT_NOT_EQUAL(snake_food_get_x_pos(), 1);
}

void test_snake_len_increased_after_eaten_food(void)
{
    snake_food_init(1, 1);

    snake_elem_t *grid = snake_get_grid();
    /* initial snake position is x 0 y 0 food is 1 1 so we must go 1 to the right 1 down  virtually */

    float current_time = 0.0f;
    snake_set_head_movement(MOVEMENT_RIGHT);

    /* update of position happens every 0.2s */
    snake_update(current_time + 0.21f);

    snake_food_update();

    snake_set_head_movement(MOVEMENT_DOWN);

    snake_update(current_time + 0.63f);
    snake_food_update();

    /* Check if food x coordinate has changed */

    TEST_ASSERT_EQUAL(2, snake_get_len());
}
