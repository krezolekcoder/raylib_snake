#include "unity.h"

#include "snake.h"
#include "config.h"
#include <stdbool.h>

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
    snake_elem_t *snake = snake_get_snake_coords();

    float current_time = 0.0f;

    snake_update(current_time);

    snake_update(current_time + 0.21f);

    TEST_ASSERT_EQUAL_INT(6, snake[0].x_pos);
}

void test_snake_moving_complex(void)
{
    snake_elem_t *snake = snake_get_snake_coords();

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
    snake_elem_t *snake = snake_get_snake_coords();
    /* initial snake position is x 0 y 0 food is 1 1 so we must go 1 to the right 1 down  virtually */

    float current_time = 0.0f;
    snake_set_head_movement(MOVEMENT_RIGHT);

    /* update of position happens every 0.2s */
    snake_update(current_time + 0.21f);

    snake_food_update();

    snake_set_head_movement(MOVEMENT_DOWN);

    snake_update(current_time + 0.63f);
    snake_food_update();
    snake_food_create_new_food(2, 2);

    /* Check if food x coordinate has changed */

    TEST_ASSERT_NOT_EQUAL(snake_food_get_x_pos(), 1);
}

void test_snake_len_increased_after_eaten_food(void)
{
    snake_food_init(1, 1);

    snake_elem_t *snake = snake_get_snake_coords();
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

void test_snake_next_brick_coords_after_food_eating(void)
{
    snake_food_init(1, 1);
    snake_elem_t *snake = snake_get_snake_coords();

    float current_time = 0.0f;
    snake_set_head_movement(MOVEMENT_RIGHT);
    snake_update(current_time + 0.21f);
    snake_food_update();
    snake_set_head_movement(MOVEMENT_DOWN);
    snake_update(current_time + 0.42f);
    snake_food_update();

    unsigned int coords[2];
    coords[0] = snake[1].x_pos;
    coords[1] = snake[1].y_pos;

    unsigned int coords_expected[2] = {1, 1};

    TEST_ASSERT_EQUAL_INT_ARRAY(coords_expected, coords, 2);
}

void test_snake_second_brick_coords_after_updated_movement(void)
{
    snake_food_init(1, 1);
    snake_elem_t *snake = snake_get_snake_coords();

    /* Move snake to food position and eat it */
    float current_time = 0.0f;
    snake_set_head_movement(MOVEMENT_RIGHT);
    current_time += 0.21f;
    snake_update(current_time);
    snake_set_head_movement(MOVEMENT_DOWN);
    current_time += 0.21f;
    snake_update(current_time);
    snake_food_update();
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

void test_snake_increased_len_after_eating_more_food(void)
{
    snake_food_init(1, 1);
    snake_elem_t *snake = snake_get_snake_coords();

    float current_time = 0.0f;
    snake_set_head_movement(MOVEMENT_RIGHT);
    current_time += 0.21f;
    snake_update(current_time);
    snake_set_head_movement(MOVEMENT_DOWN);
    current_time += 0.21f;
    snake_update(current_time);
    snake_food_update();
    snake_food_create_new_food(2, 2);
    current_time += 0.21f;
    snake_update(current_time);
    snake_set_head_movement(MOVEMENT_RIGHT);
    current_time += 0.21f;
    snake_update(current_time);
    snake_food_update();

    TEST_ASSERT_EQUAL_INT(3, snake_get_len());
}

/* snake eats three blocks and expands its len to 3 - make sure if third brick also is moving correctly */

void test_snake_tail_coords_with_increased_len(void)
{
    snake_food_init(1, 1);
    snake_elem_t *snake = snake_get_snake_coords();

    unsigned int elems_expected[6];
    unsigned int elems_actual[6];

    float current_time = 0.0f;

    snake_set_head_movement(MOVEMENT_RIGHT);
    current_time += 0.21f;
    snake_update(current_time);

    snake_set_head_movement(MOVEMENT_DOWN);
    current_time += 0.21f;
    snake_update(current_time);
    snake_food_update();
    snake_food_create_new_food(2, 2);

    current_time += 0.21f;
    snake_update(current_time);

    snake_set_head_movement(MOVEMENT_RIGHT);
    current_time += 0.21f;
    snake_update(current_time);
    snake_food_update();
    snake_food_create_new_food(3, 3);

    // move snake in right direction
    for (int i = 0; i < 5; i++)
    {
        current_time += 0.21f;
        snake_update(current_time);
    }

    elems_expected[0] = 7;
    elems_expected[1] = 2;
    elems_expected[2] = 6;
    elems_expected[3] = 2;
    elems_expected[4] = 5;
    elems_expected[5] = 2;

    elems_actual[0] = snake[0].x_pos;
    elems_actual[1] = snake[0].y_pos;
    elems_actual[2] = snake[1].x_pos;
    elems_actual[3] = snake[1].y_pos;
    elems_actual[4] = snake[2].x_pos;
    elems_actual[5] = snake[2].y_pos;

    TEST_ASSERT_EQUAL_INT_ARRAY(elems_expected, elems_actual, 6);
}

void test_result_if_new_position_of_food_collide_with_snake(void)
{
    snake_elem_t *snake = snake_get_snake_coords();
    float current_time = 0.0f;
    snake_food_init(1, 1);

    bool food_update_result = true;

    snake_set_head_movement(MOVEMENT_RIGHT);
    current_time += 0.21f;
    snake_update(current_time);
    snake_set_head_movement(MOVEMENT_DOWN);
    current_time += 0.21f;
    snake_update(current_time);
    snake_food_update();
    snake_food_create_new_food(2, 2);
    current_time += 0.21f;
    snake_update(current_time);
    snake_set_head_movement(MOVEMENT_RIGHT);
    current_time += 0.21f;
    snake_food_update();
    food_update_result = snake_food_create_new_food(2, 2);

    TEST_ASSERT_EQUAL(false, food_update_result);
}

void test_result_if_new_position_dont_collide_with_snake(void)
{
    snake_elem_t *snake = snake_get_snake_coords();
    float current_time = 0.0f;
    snake_food_init(1, 1);

    bool food_update_result = true;

    snake_set_head_movement(MOVEMENT_RIGHT);
    current_time += 0.21f;
    snake_update(current_time);
    snake_set_head_movement(MOVEMENT_DOWN);
    current_time += 0.21f;
    snake_update(current_time);
    snake_food_update();
    food_update_result = snake_food_create_new_food(2, 2);

    TEST_ASSERT_EQUAL(true, food_update_result);
}

void test_result_check_if_backwards_snake_head_movement_not_possible(void)
{
    snake_elem_t *snake = snake_get_snake_coords();
    float current_time = 0.0f;

    snake_food_init(1, 1);

    snake_set_head_movement(MOVEMENT_RIGHT);
    current_time += 0.21f;
    snake_update(current_time);
    snake_set_head_movement(MOVEMENT_DOWN);
    current_time += 0.21f;
    snake_update(current_time);
    snake_food_update();
    snake_food_create_new_food(2, 2);

    bool result = snake_set_head_movement(MOVEMENT_UP);

    TEST_ASSERT_EQUAL(false, result);
}
