#include "build/temp/_test_snake.c"
#include "src/config.h"
#include "src/snake.h"
#include "C:/Ruby26-x64/lib/ruby/gems/2.6.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"














void setUp(void)

{

    snake_init(0, 0);

    snake_food_init(1, 1);

}



void tearDown(void)

{

}

static 

      _Bool 

           prv_move_snake_to_arbitrary_place(uint32_t x_pos_start, uint32_t y_pos_start, uint32_t x_pos_dst, uint32_t y_pos_dst);



void test_snake_moving(void)

{

    uint32_t expected[2] = {1, 5};

    uint32_t actual[2];

    snake_elem_t *snake = snake_get_snake_coords();



    prv_move_snake_to_arbitrary_place(snake[0].x_pos, snake[0].y_pos, 1, 1);



    prv_move_snake_to_arbitrary_place(snake[0].x_pos, snake[0].y_pos, 1, 5);



    actual[0] = snake[0].x_pos;

    actual[1] = snake[0].y_pos;



    UnityAssertEqualIntArray(( const void*)((expected)), ( const void*)((actual)), (UNITY_UINT32)((2)), (

   ((void *)0)

   ), (UNITY_UINT)(44), UNITY_DISPLAY_STYLE_INT, UNITY_ARRAY_TO_ARRAY);

}





void test_snake_len_increased_after_eaten_food(void)

{

    snake_elem_t *snake = snake_get_snake_coords();





    for (int i = 0; i < 3; i++)

    {

        prv_move_snake_to_arbitrary_place(snake[0].x_pos, snake[0].y_pos, i + 1, i + 1);

        snake_food_update();

        snake_food_create_new_food(i + 2, i + 2);

    }







    UnityAssertEqualNumber((UNITY_INT)((4)), (UNITY_INT)((snake_get_len())), (

   ((void *)0)

   ), (UNITY_UINT)(62), UNITY_DISPLAY_STYLE_INT);

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



    UnityAssertEqualIntArray(( const void*)((coords_expected)), ( const void*)((coords)), (UNITY_UINT32)((2)), (

   ((void *)0)

   ), (UNITY_UINT)(78), UNITY_DISPLAY_STYLE_INT, UNITY_ARRAY_TO_ARRAY);

}



void test_snake_second_brick_coords_after_updated_movement(void)

{

    snake_elem_t *snake = snake_get_snake_coords();





    prv_move_snake_to_arbitrary_place(snake[0].x_pos, snake[0].y_pos, 1, 1);

    snake_food_update();

    prv_move_snake_to_arbitrary_place(snake[0].x_pos, snake[0].y_pos, 1, 3);



    uint32_t coords_actual[2];

    uint32_t coords_expected[2] = {1, 2};



    coords_actual[0] = snake[1].x_pos;

    coords_actual[1] = snake[1].y_pos;



    UnityAssertEqualIntArray(( const void*)((coords_expected)), ( const void*)((coords_actual)), (UNITY_UINT32)((2)), (

   ((void *)0)

   ), (UNITY_UINT)(96), UNITY_DISPLAY_STYLE_INT, UNITY_ARRAY_TO_ARRAY);

}







void test_snake_tail_coords_with_increased_len(void)

{

    uint32_t elems_expected[6] = {7, 2, 6, 2, 5, 2};

    uint32_t elems_actual[6];

    snake_elem_t *snake = snake_get_snake_coords();



    for (int i = 0; i < 2; i++)

    {

        prv_move_snake_to_arbitrary_place(snake[0].x_pos, snake[0].y_pos, i + 1, i + 1);

        snake_food_update();

        snake_food_create_new_food(i + 2, i + 2);

    }



    prv_move_snake_to_arbitrary_place(snake[0].x_pos, snake[0].y_pos, 7, 2);



    elems_actual[0] = snake[0].x_pos;

    elems_actual[1] = snake[0].y_pos;

    elems_actual[2] = snake[1].x_pos;

    elems_actual[3] = snake[1].y_pos;

    elems_actual[4] = snake[2].x_pos;

    elems_actual[5] = snake[2].y_pos;



    UnityAssertEqualIntArray(( const void*)((elems_expected)), ( const void*)((elems_actual)), (UNITY_UINT32)((6)), (

   ((void *)0)

   ), (UNITY_UINT)(123), UNITY_DISPLAY_STYLE_INT, UNITY_ARRAY_TO_ARRAY);

}



void test_result_if_new_position_of_food_collide_with_snake(void)

{

    snake_elem_t *snake = snake_get_snake_coords();

    float current_time = 0.0f;

    for (int i = 0; i < 2; i++)

    {

        prv_move_snake_to_arbitrary_place(snake[0].x_pos, snake[0].y_pos, i + 1, i + 1);

        snake_food_update();

        snake_food_create_new_food(i + 2, i + 2);

    }

    UnityAssertEqualNumber((UNITY_INT)((

   0

   )), (UNITY_INT)((snake_food_create_new_food(2, 2))), (

   ((void *)0)

   ), (UNITY_UINT)(136), UNITY_DISPLAY_STYLE_INT);

}



void test_result_if_new_position_dont_collide_with_snake(void)

{

    snake_elem_t *snake = snake_get_snake_coords();

    float current_time = 0.0f;

    prv_move_snake_to_arbitrary_place(snake[0].x_pos, snake[0].y_pos, 1, 1);

    snake_food_update();



    UnityAssertEqualNumber((UNITY_INT)((

   1

   )), (UNITY_INT)((snake_food_create_new_food(2, 2))), (

   ((void *)0)

   ), (UNITY_UINT)(146), UNITY_DISPLAY_STYLE_INT);

}



void test_result_check_if_backwards_snake_head_movement_not_possible(void)

{

    snake_elem_t *snake = snake_get_snake_coords();

    prv_move_snake_to_arbitrary_place(snake[0].x_pos, snake[0].y_pos, 1, 1);



    UnityAssertEqualNumber((UNITY_INT)((

   0

   )), (UNITY_INT)((snake_set_head_movement(MOVEMENT_UP))), (

   ((void *)0)

   ), (UNITY_UINT)(154), UNITY_DISPLAY_STYLE_INT);

}



void test_result_check_collision_with_wall_x_coord_less_than_min(void)

{

    snake_elem_t *snake = snake_get_snake_coords();

    float current_time = 0.0f;

    

   _Bool 

        snake_update_result = 

                              1

                                  ;





    snake_set_head_movement(MOVEMENT_DOWN);

    current_time += ((0.1f) + 0.1f);



    snake_update_result = snake_update(current_time);

    snake_set_head_movement(MOVEMENT_LEFT);

    current_time += ((0.1f) + 0.1f);

    snake_update_result = snake_update(current_time);



    UnityAssertEqualNumber((UNITY_INT)((

   0

   )), (UNITY_INT)((snake_update_result)), (

   ((void *)0)

   ), (UNITY_UINT)(172), UNITY_DISPLAY_STYLE_INT);

}



void test_result_check_collision_with_wall_x_coord_greather_than_max(void)

{

    snake_elem_t *snake = snake_get_snake_coords();

    float current_time = 0.0f;

    

   _Bool 

        snake_update_result = 

                              1

                                  ;



    snake_set_head_movement(MOVEMENT_UP);

    current_time += ((0.1f) + 0.1f);

    snake_update_result = snake_update(current_time);



    UnityAssertEqualNumber((UNITY_INT)((

   0

   )), (UNITY_INT)((snake_update_result)), (

   ((void *)0)

   ), (UNITY_UINT)(185), UNITY_DISPLAY_STYLE_INT);

}



void test_result_check_collision_with_wall_y_coord_less_than_min(void)

{

    snake_elem_t *snake = snake_get_snake_coords();

    float current_time = 0.0f;

    

   _Bool 

        snake_update_result = 

                              1

                                  ;



    snake_set_head_movement(MOVEMENT_RIGHT);





    for (int i = 0; i < (25U) + 1; i++)

    {

        current_time += ((0.1f) + 0.1f);

        snake_update_result = snake_update(current_time);

    }



    UnityAssertEqualNumber((UNITY_INT)((

   0

   )), (UNITY_INT)((snake_update_result)), (

   ((void *)0)

   ), (UNITY_UINT)(203), UNITY_DISPLAY_STYLE_INT);

}



void test_result_check_collision_with_wall_y_coord_greather_than_max(void)

{

    snake_elem_t *snake = snake_get_snake_coords();

    float current_time = 0.0f;

    

   _Bool 

        snake_update_result = 

                              1

                                  ;



    snake_set_head_movement(MOVEMENT_DOWN);





    for (int i = 0; i < (15U) + 1; i++)

    {

        current_time += ((0.1f) + 0.1f);

        snake_update_result = snake_update(current_time);

    }



    UnityAssertEqualNumber((UNITY_INT)((

   0

   )), (UNITY_INT)((snake_update_result)), (

   ((void *)0)

   ), (UNITY_UINT)(221), UNITY_DISPLAY_STYLE_INT);

}



void test_snake_x_coords_after_wall_collision_less_than_min(void)

{

    snake_elem_t *snake = snake_get_snake_coords();

    float current_time = 0.0f;

    

   _Bool 

        snake_update_result = 

                              1

                                  ;





    snake_set_head_movement(MOVEMENT_DOWN);

    current_time += ((0.1f) + 0.1f);



    snake_update_result = snake_update(current_time);

    snake_set_head_movement(MOVEMENT_LEFT);

    current_time += ((0.1f) + 0.1f);

    snake_update_result = snake_update(current_time);



    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((snake[0].x_pos)), (

   ((void *)0)

   ), (UNITY_UINT)(239), UNITY_DISPLAY_STYLE_INT);

}





void test_snake_x_coords_still_after_wall_colision_left(void)

{

    snake_elem_t *snake = snake_get_snake_coords();

    uint32_t elems_expected[6] = {0, 2, 1, 2, 2, 2};

    uint32_t elems_actual[6];



    float current_time;



    for (int i = 0; i < 2; i++)

    {

        prv_move_snake_to_arbitrary_place(snake[0].x_pos, snake[0].y_pos, i + 1, i + 1);

        snake_food_update();

        snake_food_create_new_food(i + 2, i + 2);

    }





    if (!snake_set_head_movement(MOVEMENT_LEFT))

    {

        printf("wrong head movement left!\r\n");

    }

    current_time = snake_get_time();

    for (int i = 0; i < 7; i++)

    {

        snake_update(current_time + i * ((0.1f) + 0.1f));

    }







    elems_actual[0] = snake[0].x_pos;

    elems_actual[1] = snake[0].y_pos;

    elems_actual[2] = snake[1].x_pos;

    elems_actual[3] = snake[1].y_pos;

    elems_actual[4] = snake[2].x_pos;

    elems_actual[5] = snake[2].y_pos;



    UnityAssertEqualIntArray(( const void*)((elems_expected)), ( const void*)((elems_actual)), (UNITY_UINT32)((6)), (

   ((void *)0)

   ), (UNITY_UINT)(278), UNITY_DISPLAY_STYLE_INT, UNITY_ARRAY_TO_ARRAY);

}



void test_snake_x_coords_still_after_wall_colision_right(void)

{

    uint32_t elems_expected[6] = {24, 2, 23, 2, 22, 2};

    uint32_t elems_actual[6];



    float current_time;



    snake_elem_t *snake = snake_get_snake_coords();



    for (int i = 0; i < 2; i++)

    {

        prv_move_snake_to_arbitrary_place(snake[0].x_pos, snake[0].y_pos, i + 1, i + 1);

        snake_food_update();

        snake_food_create_new_food(i + 2, i + 2);

    }







    if (!snake_set_head_movement(MOVEMENT_RIGHT))

    {

        printf("Wrong head movement right \r\n");

    }

    current_time = snake_get_time();





    for (int i = 0; i < (25U); i++)

    {

        snake_update(current_time + i * ((0.1f) + 0.1f));

    }







    elems_actual[0] = snake[0].x_pos;

    elems_actual[1] = snake[0].y_pos;

    elems_actual[2] = snake[1].x_pos;

    elems_actual[3] = snake[1].y_pos;

    elems_actual[4] = snake[2].x_pos;

    elems_actual[5] = snake[2].y_pos;



    UnityAssertEqualIntArray(( const void*)((elems_expected)), ( const void*)((elems_actual)), (UNITY_UINT32)((6)), (

   ((void *)0)

   ), (UNITY_UINT)(320), UNITY_DISPLAY_STYLE_INT, UNITY_ARRAY_TO_ARRAY);

}



void test_snake_y_coords_still_after_wall_collision_up(void)

{

    snake_elem_t *snake = snake_get_snake_coords();

    uint32_t elems_expected[6] = {3, 0, 3, 1, 3, 2};

    uint32_t elems_actual[6];



    float current_time;



    for (int i = 0; i < 2; i++)

    {

        prv_move_snake_to_arbitrary_place(snake[0].x_pos, snake[0].y_pos, i + 1, i + 1);

        snake_food_update();

        snake_food_create_new_food(i + 2, i + 2);

    }







    if (!snake_set_head_movement(MOVEMENT_UP))

    {



        snake_set_head_movement(MOVEMENT_RIGHT);

        current_time = snake_get_time();

        snake_update(current_time + ((0.1f) + 0.1f));

        snake_set_head_movement(MOVEMENT_UP);

    }





    for (int i = 0; i < 7; i++)

    {

        snake_update(current_time + i * ((0.1f) + 0.1f));

    }







    elems_actual[0] = snake[0].x_pos;

    elems_actual[1] = snake[0].y_pos;

    elems_actual[2] = snake[1].x_pos;

    elems_actual[3] = snake[1].y_pos;

    elems_actual[4] = snake[2].x_pos;

    elems_actual[5] = snake[2].y_pos;



    UnityAssertEqualIntArray(( const void*)((elems_expected)), ( const void*)((elems_actual)), (UNITY_UINT32)((6)), (

   ((void *)0)

   ), (UNITY_UINT)(364), UNITY_DISPLAY_STYLE_INT, UNITY_ARRAY_TO_ARRAY);

}



void test_snake_y_coords_still_after_wall_collision_down(void)

{

    snake_elem_t *snake = snake_get_snake_coords();

    uint32_t elems_expected[6] = {2, 14, 2, 13, 2, 12};

    uint32_t elems_actual[6];



    float current_time;



    for (int i = 0; i < 2; i++)

    {

        prv_move_snake_to_arbitrary_place(snake[0].x_pos, snake[0].y_pos, i + 1, i + 1);

        snake_food_update();

        snake_food_create_new_food(i + 2, i + 2);

    }







    if (!snake_set_head_movement(MOVEMENT_DOWN))

    {

        printf("wrong head movement down !\r\n");

    }

    current_time = snake_get_time();





    for (int i = 0; i < (15U); i++)

    {

        snake_update(current_time + i * ((0.1f) + 0.1f));

    }







    elems_actual[0] = snake[0].x_pos;

    elems_actual[1] = snake[0].y_pos;

    elems_actual[2] = snake[1].x_pos;

    elems_actual[3] = snake[1].y_pos;

    elems_actual[4] = snake[2].x_pos;

    elems_actual[5] = snake[2].y_pos;



    UnityAssertEqualIntArray(( const void*)((elems_expected)), ( const void*)((elems_actual)), (UNITY_UINT32)((6)), (

   ((void *)0)

   ), (UNITY_UINT)(405), UNITY_DISPLAY_STYLE_INT, UNITY_ARRAY_TO_ARRAY);

}





void test_snake_selfcollision_normal_movement(void)

{

    snake_elem_t *snake = snake_get_snake_coords();

    uint32_t elems_expected[6] = {2, 14, 2, 13, 2, 12};

    uint32_t elems_actual[6];

    

   _Bool 

        result = 

                 1

                     ;



    float current_time;



    for (int i = 0; i < 4; i++)

    {

        result = prv_move_snake_to_arbitrary_place(snake[0].x_pos, snake[0].y_pos, i + 1, i + 1);

        snake_food_update();

        snake_food_create_new_food(i + 2, i + 2);

        if (!result)

        {

            break;

        }

    }



    UnityAssertEqualNumber((UNITY_INT)((

   1

   )), (UNITY_INT)((result)), (

   ((void *)0)

   ), (UNITY_UINT)(429), UNITY_DISPLAY_STYLE_INT);

}



void test_snake_selfcollision_detection(void)

{

    snake_elem_t *snake = snake_get_snake_coords();

    uint32_t elems_expected[6] = {2, 14, 2, 13, 2, 12};

    uint32_t elems_actual[6];

    

   _Bool 

        result = 

                 0

                      ;



    float current_time;



    for (int i = 0; i < 9; i++)

    {

        prv_move_snake_to_arbitrary_place(snake[0].x_pos, snake[0].y_pos, i + 1, i + 1);

        snake_food_update();

        snake_food_create_new_food(i + 2, i + 2);

    }

    current_time = snake_get_time();





    snake_set_head_movement(MOVEMENT_DOWN);

    current_time += 0.21f;

    snake_update(current_time);



    snake_set_head_movement(MOVEMENT_LEFT);

    current_time += 0.21f;

    snake_update(current_time);



    snake_set_head_movement(MOVEMENT_UP);





    for (int i = 0; i < 5; i++)

    {

        current_time += 0.21f;

        result = snake_update(current_time);

    }







    UnityAssertEqualNumber((UNITY_INT)((

   0

   )), (UNITY_INT)((result)), (

   ((void *)0)

   ), (UNITY_UINT)(469), UNITY_DISPLAY_STYLE_INT);

}







static 

      _Bool 

           prv_move_snake_to_arbitrary_place(uint32_t x_pos_start, uint32_t y_pos_start, uint32_t x_pos_dst, uint32_t y_pos_dst)

{

    

   _Bool 

        result = 

                 1

                     ;

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

            result = 

                    0

                         ;

        }



        for (int i = 0; i < ((x_distance > 0) ? x_distance : -x_distance); i++)

        {

            current_time += ((0.1f) + 0.1f);

            result &= snake_update(current_time);

        }

    }



    snake_movement = y_distance > 0 ? MOVEMENT_DOWN : MOVEMENT_UP;



    if (y_distance != 0)

    {

        if (!snake_set_head_movement(snake_movement))

        {

            result = 

                    0

                         ;

        }



        for (int i = 0; i < ((y_distance > 0) ? y_distance : -y_distance); i++)

        {

            current_time += ((0.1f) + 0.1f);

            result &= snake_update(current_time);

        }

    }



    return result;

}
