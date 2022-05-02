#include "unity.h"

#include "snake.h"
#include "config.h"
#include <stdbool.h>

#define ABS(x) ((x > 0) ? x : -x)

#define SNAKE_UPDATE_TIMEOUT (0.21f)

void setUp(void)
{
    snake_init(0, 0);
    snake_food_init(1, 1);
}

void tearDown(void)
{
}

/**
 * @brief Helper function for moving snake to defined place
 *
 * @param x_pos_start
 * @param y_pos_start
 * @param x_pos_dst
 * @param y_pos_dst
 */
static bool prv_move_snake_to_arbitrary_place(uint32_t x_pos_start, uint32_t y_pos_start, uint32_t x_pos_dst, uint32_t y_pos_dst);

void test_snake_moving(void)
{
    uint32_t expected[2] = {1, 5};
    uint32_t actual[2];
    snake_elem_t *snake = snake_get_snake_coords();

    prv_move_snake_to_arbitrary_place(snake[0].x_pos, snake[0].y_pos, 1, 1);

    prv_move_snake_to_arbitrary_place(snake[0].x_pos, snake[0].y_pos, 1, 5);

    actual[0] = snake[0].x_pos;
    actual[1] = snake[0].y_pos;

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, actual, 2);
}

/* test generating new food and increased len of snake after eating */
void test_snake_len_increased_after_eaten_food(void)
{
    snake_elem_t *snake = snake_get_snake_coords();
    /* initial snake position is x 0 y 0 food is 1 1 so we must go 1 to the right 1 down  virtually */

    for (int i = 0; i < 3; i++)
    {
        prv_move_snake_to_arbitrary_place(snake[0].x_pos, snake[0].y_pos, i + 1, i + 1);
        snake_food_update();
        snake_food_create_new_food(i + 2, i + 2);
    }

    /* Check if food x coordinate has changed */

    TEST_ASSERT_EQUAL(4, snake_get_len());
}

void test_snake_next_brick_coords_after_food_eating(void)
{
    snake_elem_t *snake = snake_get_snake_coords();

    prv_move_snake_to_arbitrary_place(snake[0].x_pos, snake[0].y_pos, 1, 1);
    snake_food_update();

    uint32_t coords[2];
    coords[0] = snake[1].x_pos;
    coords[1] = snake[1].y_pos;

    uint32_t coords_expected[2] = {1, 1};

    TEST_ASSERT_EQUAL_INT_ARRAY(coords_expected, coords, 2);
}

void test_snake_second_brick_coords_after_updated_movement(void)
{
    snake_elem_t *snake = snake_get_snake_coords();

    /* Move snake to food position and eat it */
    prv_move_snake_to_arbitrary_place(snake[0].x_pos, snake[0].y_pos, 1, 1);
    snake_food_update();
    prv_move_snake_to_arbitrary_place(snake[0].x_pos, snake[0].y_pos, 1, 3);

    uint32_t coords_actual[2];
    uint32_t coords_expected[2] = {1, 2};

    coords_actual[0] = snake[1].x_pos;
    coords_actual[1] = snake[1].y_pos;

    TEST_ASSERT_EQUAL_INT_ARRAY(coords_expected, coords_actual, 2);
}

/* snake eats three blocks and expands its len to 3 - make sure if third brick also is moving correctly */

void test_snake_tail_coords_with_increased_len(void)
{
    uint32_t elems_expected[6] = {7, 2, 6, 2, 5, 2};
    uint32_t elems_actual[6];
    snake_elem_t *snake = snake_get_snake_coords();

    for (int i = 0; i < 2; i++)
    {
        prv_move_snake_to_arbitrary_place(snake[0].x_pos, snake[0].y_pos, i + 1, i + 1); // move snake to food destination
        snake_food_update();
        snake_food_create_new_food(i + 2, i + 2); // create new food. Snake will eat it in new iteration
    }

    prv_move_snake_to_arbitrary_place(snake[0].x_pos, snake[0].y_pos, 7, 2);

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
    for (int i = 0; i < 2; i++)
    {
        prv_move_snake_to_arbitrary_place(snake[0].x_pos, snake[0].y_pos, i + 1, i + 1);
        snake_food_update();
        snake_food_create_new_food(i + 2, i + 2); // create new food. Snake will eat it in new iteration
    }
    TEST_ASSERT_EQUAL(false, snake_food_create_new_food(2, 2));
}

void test_result_if_new_position_dont_collide_with_snake(void)
{
    snake_elem_t *snake = snake_get_snake_coords();
    float current_time = 0.0f;
    prv_move_snake_to_arbitrary_place(snake[0].x_pos, snake[0].y_pos, 1, 1);
    snake_food_update();

    TEST_ASSERT_EQUAL(true, snake_food_create_new_food(2, 2));
}

void test_result_check_if_backwards_snake_head_movement_not_possible(void)
{
    snake_elem_t *snake = snake_get_snake_coords();
    prv_move_snake_to_arbitrary_place(snake[0].x_pos, snake[0].y_pos, 1, 1);

    TEST_ASSERT_EQUAL(false, snake_set_head_movement(MOVEMENT_UP));
}

void test_result_check_collision_with_wall_x_coord_less_than_min(void)
{
    snake_elem_t *snake = snake_get_snake_coords();
    float current_time = 0.0f;
    bool snake_update_result = true;

    // at initial time snake could not go backwards so we need to go down for 1 box and then turn left to induce wrong behaviour
    snake_set_head_movement(MOVEMENT_DOWN);
    current_time += SNAKE_UPDATE_TIMEOUT;

    snake_update_result = snake_update(current_time);
    snake_set_head_movement(MOVEMENT_LEFT);
    current_time += SNAKE_UPDATE_TIMEOUT;
    snake_update_result = snake_update(current_time);

    TEST_ASSERT_EQUAL(false, snake_update_result);
}

void test_result_check_collision_with_wall_x_coord_greather_than_max(void)
{
    snake_elem_t *snake = snake_get_snake_coords();
    float current_time = 0.0f;
    bool snake_update_result = true;

    snake_set_head_movement(MOVEMENT_UP);
    current_time += SNAKE_UPDATE_TIMEOUT;
    snake_update_result = snake_update(current_time);

    TEST_ASSERT_EQUAL(false, snake_update_result);
}

void test_result_check_collision_with_wall_y_coord_less_than_min(void)
{
    snake_elem_t *snake = snake_get_snake_coords();
    float current_time = 0.0f;
    bool snake_update_result = true;

    snake_set_head_movement(MOVEMENT_RIGHT);

    // we need to go right to the end of the blocks area
    for (int i = 0; i < SCREEN_WIDTH_BLOCK_CNT + 1; i++)
    {
        current_time += SNAKE_UPDATE_TIMEOUT;
        snake_update_result = snake_update(current_time);
    }

    TEST_ASSERT_EQUAL(false, snake_update_result);
}

void test_result_check_collision_with_wall_y_coord_greather_than_max(void)
{
    snake_elem_t *snake = snake_get_snake_coords();
    float current_time = 0.0f;
    bool snake_update_result = true;

    snake_set_head_movement(MOVEMENT_DOWN);

    // we need to go down to the end of the blocks area
    for (int i = 0; i < SCREEN_HEIGHT_BLOCK_CNT + 1; i++)
    {
        current_time += SNAKE_UPDATE_TIMEOUT;
        snake_update_result = snake_update(current_time);
    }

    TEST_ASSERT_EQUAL(false, snake_update_result);
}

void test_snake_x_coords_after_wall_collision_less_than_min(void)
{
    snake_elem_t *snake = snake_get_snake_coords();
    float current_time = 0.0f;
    bool snake_update_result = true;

    // at initial time snake could not go backwards so we need to go down for 1 box and then turn left to induce wrong behaviour
    snake_set_head_movement(MOVEMENT_DOWN);
    current_time += SNAKE_UPDATE_TIMEOUT;

    snake_update_result = snake_update(current_time);
    snake_set_head_movement(MOVEMENT_LEFT);
    current_time += SNAKE_UPDATE_TIMEOUT;
    snake_update_result = snake_update(current_time);

    TEST_ASSERT_EQUAL(0, snake[0].x_pos);
}

/** Increase the snake len to f.ex 3, hit the wall and check if snake coords are correct that is non of snake bricks should exceed the wall and dissapear */
void test_snake_x_coords_still_after_wall_colision_left(void)
{
    snake_elem_t *snake = snake_get_snake_coords();
    uint32_t elems_expected[6] = {0, 2, 1, 2, 2, 2};
    uint32_t elems_actual[6];

    float current_time;
    /** increase snake len to 3 */
    for (int i = 0; i < 2; i++)
    {
        prv_move_snake_to_arbitrary_place(snake[0].x_pos, snake[0].y_pos, i + 1, i + 1);
        snake_food_update();
        snake_food_create_new_food(i + 2, i + 2);
    }

    /** move snake to edge of the left wall */
    if (!snake_set_head_movement(MOVEMENT_LEFT))
    {
        printf("wrong head movement left!\r\n");
    }
    current_time = snake_get_time();
    for (int i = 0; i < 7; i++)
    {
        snake_update(current_time + i * SNAKE_UPDATE_TIMEOUT);
    }

    /** Let snake do some movement and check if coords of snake do not exceeded wall */

    elems_actual[0] = snake[0].x_pos;
    elems_actual[1] = snake[0].y_pos;
    elems_actual[2] = snake[1].x_pos;
    elems_actual[3] = snake[1].y_pos;
    elems_actual[4] = snake[2].x_pos;
    elems_actual[5] = snake[2].y_pos;

    TEST_ASSERT_EQUAL_INT_ARRAY(elems_expected, elems_actual, 6);
}

void test_snake_x_coords_still_after_wall_colision_right(void)
{
    uint32_t elems_expected[6] = {24, 2, 23, 2, 22, 2};
    uint32_t elems_actual[6];

    float current_time;

    snake_elem_t *snake = snake_get_snake_coords();
    /** increase snake len to 3 */
    for (int i = 0; i < 2; i++)
    {
        prv_move_snake_to_arbitrary_place(snake[0].x_pos, snake[0].y_pos, i + 1, i + 1);
        snake_food_update();
        snake_food_create_new_food(i + 2, i + 2);
    }

    /** move snake to right edge of the screen */

    if (!snake_set_head_movement(MOVEMENT_RIGHT))
    {
        printf("Wrong head movement right \r\n");
    }
    current_time = snake_get_time();

    /** Let snake do some movement */
    for (int i = 0; i < SCREEN_WIDTH_BLOCK_CNT; i++)
    {
        snake_update(current_time + i * SNAKE_UPDATE_TIMEOUT);
    }

    /** check if coords of snake do not exceeded wall */

    elems_actual[0] = snake[0].x_pos;
    elems_actual[1] = snake[0].y_pos;
    elems_actual[2] = snake[1].x_pos;
    elems_actual[3] = snake[1].y_pos;
    elems_actual[4] = snake[2].x_pos;
    elems_actual[5] = snake[2].y_pos;

    TEST_ASSERT_EQUAL_INT_ARRAY(elems_expected, elems_actual, 6);
}

void test_snake_y_coords_still_after_wall_collision_up(void)
{
    snake_elem_t *snake = snake_get_snake_coords();
    uint32_t elems_expected[6] = {3, 0, 3, 1, 3, 2};
    uint32_t elems_actual[6];

    float current_time;
    /** increase snake len to 3 */
    for (int i = 0; i < 2; i++)
    {
        prv_move_snake_to_arbitrary_place(snake[0].x_pos, snake[0].y_pos, i + 1, i + 1);
        snake_food_update();
        snake_food_create_new_food(i + 2, i + 2);
    }

    /** move snake to up edge of the screen  */

    if (!snake_set_head_movement(MOVEMENT_UP))
    {
        /** we have to turn snake around  */
        snake_set_head_movement(MOVEMENT_RIGHT);
        current_time = snake_get_time();
        snake_update(current_time + SNAKE_UPDATE_TIMEOUT);
        snake_set_head_movement(MOVEMENT_UP);
    }

    /** Let snake do some movement */
    for (int i = 0; i < 7; i++)
    {
        snake_update(current_time + i * SNAKE_UPDATE_TIMEOUT);
    }

    /** check if coords of snake do not exceeded wall */

    elems_actual[0] = snake[0].x_pos;
    elems_actual[1] = snake[0].y_pos;
    elems_actual[2] = snake[1].x_pos;
    elems_actual[3] = snake[1].y_pos;
    elems_actual[4] = snake[2].x_pos;
    elems_actual[5] = snake[2].y_pos;

    TEST_ASSERT_EQUAL_INT_ARRAY(elems_expected, elems_actual, 6);
}

void test_snake_y_coords_still_after_wall_collision_down(void)
{
    snake_elem_t *snake = snake_get_snake_coords();
    uint32_t elems_expected[6] = {2, 14, 2, 13, 2, 12};
    uint32_t elems_actual[6];

    float current_time;
    /** increase snake len to 3 */
    for (int i = 0; i < 2; i++)
    {
        prv_move_snake_to_arbitrary_place(snake[0].x_pos, snake[0].y_pos, i + 1, i + 1);
        snake_food_update();
        snake_food_create_new_food(i + 2, i + 2);
    }

    /** move snake to the down edge of the screen */

    if (!snake_set_head_movement(MOVEMENT_DOWN))
    {
        printf("wrong head movement down !\r\n");
    }
    current_time = snake_get_time();

    /** Let snake do some movement  */
    for (int i = 0; i < SCREEN_HEIGHT_BLOCK_CNT; i++)
    {
        snake_update(current_time + i * SNAKE_UPDATE_TIMEOUT);
    }

    /** check if coords of snake do not exceeded wall */

    elems_actual[0] = snake[0].x_pos;
    elems_actual[1] = snake[0].y_pos;
    elems_actual[2] = snake[1].x_pos;
    elems_actual[3] = snake[1].y_pos;
    elems_actual[4] = snake[2].x_pos;
    elems_actual[5] = snake[2].y_pos;

    printf("coords : ");
    for (int i = 0; i < 6; i++)
    {
        printf("%d ", elems_actual[i]);
    }

    TEST_ASSERT_EQUAL_INT_ARRAY(elems_expected, elems_actual, 6);
}
/************************************ HELPER FUNCTIONS IMPLEMENTATION ************************************************************/

static bool prv_move_snake_to_arbitrary_place(uint32_t x_pos_start, uint32_t y_pos_start, uint32_t x_pos_dst, uint32_t y_pos_dst)
{
    bool result = true;
    uint32_t x_distance = x_pos_dst - x_pos_start;
    uint32_t y_distance = y_pos_dst - y_pos_start;
    float current_time = snake_get_time();

    movement_t snake_movement;

    if (x_distance > 0)
    {
        snake_movement = MOVEMENT_RIGHT;
    }
    else if (x_distance < 0)
    {
        snake_movement = MOVEMENT_LEFT;
    }

    snake_movement = x_distance > 0 ? MOVEMENT_RIGHT : MOVEMENT_LEFT;

    if (x_distance != 0)
    {
        if (!snake_set_head_movement(snake_movement))
        {
            result = false;
        }

        for (int i = 0; i < ABS(x_distance); i++)
        {
            current_time += SNAKE_UPDATE_TIMEOUT;
            snake_update(current_time);
        }
    }

    snake_movement = y_distance > 0 ? MOVEMENT_DOWN : MOVEMENT_UP;

    if (y_distance != 0)
    {
        if (!snake_set_head_movement(snake_movement))
        {
            result = false;
        }

        for (int i = 0; i < ABS(y_distance); i++)
        {
            current_time += SNAKE_UPDATE_TIMEOUT;
            snake_update(current_time);
        }
    }

    return result;
}