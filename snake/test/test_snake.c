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
    snake_elem_t *snake = snake_get_snake();

    float current_time = 0.0f;

    snake_update(current_time);

    snake_update(current_time + 0.21f);

    TEST_ASSERT_EQUAL_INT(6, snake[0].x_pos);
}

void test_snake_moving_complex(void)
{
    snake_elem_t *snake = snake_get_snake();

    snake_set_head_movement(MOVEMENT_DOWN);

    float current_time = 0.0f;

    snake_update(current_time);

    /* update 10 times - about 2 seconds passed virtually */
    for (int i = 0; i < 10; i++)
    {
        snake_update(current_time + i * (SNAKE_UPDATE_TIMEOUT_SEC + 0.01f));
    }

    TEST_ASSERT_EQUAL_INT(9, snake[0].y_pos);
}

void test_snake_food_eating(void)
{
    snake_food_init(1, 1);
    snake_elem_t *snake = snake_get_snake();
    /* initial snake position is x 0 y 0 food is 1 1 so we must go 1 to the right 1 down  virtually */

    float current_time = 0.0f;
    snake_set_head_movement(MOVEMENT_RIGHT);

    /* update of position happens every 0.2s */
    snake_update(current_time + 0.21f);

    snake_food_update(2, 2);

    snake_set_head_movement(MOVEMENT_DOWN);

    snake_update(current_time + 0.63f);
    snake_food_update(2, 2);

    /* Check if food x coordinate has changed */

    TEST_ASSERT_NOT_EQUAL(snake_food_get_x_pos(), 1);
}

void test_snake_len_increased_after_eaten_food(void)
{
    snake_food_init(1, 1);

    snake_elem_t *snake = snake_get_snake();
    /* initial snake position is x 0 y 0 food is 1 1 so we must go 1 to the right 1 down  virtually */

    float current_time = 0.0f;
    snake_set_head_movement(MOVEMENT_RIGHT);

    /* update of position happens every 0.2s */
    snake_update(current_time + 0.21f);

    snake_food_update(2, 2);

    snake_set_head_movement(MOVEMENT_DOWN);

    snake_update(current_time + 0.63f);
    snake_food_update(2, 2);

    /* Check if food x coordinate has changed */

    TEST_ASSERT_EQUAL(2, snake_get_len());
}

void test_snake_next_brick_coords_after_food_eating(void)
{
    snake_food_init(1, 1);
    snake_elem_t *snake = snake_get_snake();

    float current_time = 0.0f;
    snake_set_head_movement(MOVEMENT_RIGHT);
    snake_update(current_time + 0.21f);
    snake_food_update(2, 2);
    snake_set_head_movement(MOVEMENT_DOWN);
    snake_update(current_time + 0.42f);
    snake_food_update(2, 2);

    unsigned int coords[2];
    coords[0] = snake[1].x_pos;
    coords[1] = snake[1].y_pos;

    unsigned int coords_expected[2] = {1, 1};

    TEST_ASSERT_EQUAL_INT_ARRAY(coords_expected, coords, 2);
}

void test_snake_second_brick_coords_after_updated_movement(void)
{
    snake_food_init(1, 1);
    snake_elem_t *snake = snake_get_snake();

    /* Move snake to food position and eat it */
    float current_time = 0.0f;
    snake_set_head_movement(MOVEMENT_RIGHT);
    current_time += 0.21f;
    snake_update(current_time);
    snake_set_head_movement(MOVEMENT_DOWN);
    current_time += 0.21f;
    snake_update(current_time);
    snake_food_update(5, 5);
    current_time += 0.21f;
    snake_update(current_time);
    current_time += 0.21f;
    snake_update(current_time);
    current_time += 0.21f;
    snake_update(current_time);

    unsigned int coords_actual[2];
    unsigned int coords_expected[2] = {1, 3};

    coords_actual[0] = snake[1].x_pos;
    coords_actual[1] = snake[1].y_pos;

    TEST_ASSERT_EQUAL_INT_ARRAY(coords_expected, coords_actual, 2);
}