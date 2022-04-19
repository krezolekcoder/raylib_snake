#include "build/temp/_test_snake.c"
#include "src/config.h"
#include "src/snake.h"
#include "C:/Ruby26-x64/lib/ruby/gems/2.6.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"




void setUp(void)

{

}



void tearDown(void)

{

}



void test_snake_moving_simple(void)

{

    snake_init(5, 5);

    snake_food_init(7, 7);



    snake_set_head_movement(MOVEMENT_RIGHT);

    snake_elem_t *grid = snake_get_grid();



    float current_time = 0.0f;



    snake_update(current_time);



    snake_update(current_time + 0.21f);



    UnityAssertEqualNumber((UNITY_INT)((6)), (UNITY_INT)((grid[0].x_pos)), (

   ((void *)0)

   ), (UNITY_UINT)(28), UNITY_DISPLAY_STYLE_INT);

}



void test_snake_moving_complex(void)

{

    snake_init(0, 0);

    snake_elem_t *grid = snake_get_grid();



    snake_set_head_movement(MOVEMENT_DOWN);



    float current_time = 0.0f;



    snake_update(current_time);





    for (int i = 1; i < 11; i++)

    {

        snake_update(current_time + i * ((0.2f) + 0.01f));

    }



    UnityAssertEqualNumber((UNITY_INT)((9)), (UNITY_INT)((grid[0].y_pos)), (

   ((void *)0)

   ), (UNITY_UINT)(48), UNITY_DISPLAY_STYLE_INT);

}

void test_snake_food_eating(void)

{





    snake_init(0, 0);

    snake_food_init(1, 1);

    snake_elem_t *grid = snake_get_grid();





    float current_time = 0.0f;

    snake_set_head_movement(MOVEMENT_RIGHT);







    snake_update(current_time + 0.21f);



    snake_food_update();



    snake_set_head_movement(MOVEMENT_DOWN);



    snake_update(current_time + 0.63f);

    snake_food_update();







    do {if (((snake_food_get_x_pos()) != (1))) {} else {UnityFail( ((" Expected Not-Equal")), (UNITY_UINT)((UNITY_UINT)(75)));}} while(0);

}



void test_snake_len_increased_after_eaten_food(void)

{





    snake_init(0, 0);

    snake_food_init(1, 1);

    snake_elem_t *grid = snake_get_grid();





    float current_time = 0.0f;

    snake_set_head_movement(MOVEMENT_RIGHT);







    snake_update(current_time + 0.21f);



    snake_food_update();



    snake_set_head_movement(MOVEMENT_DOWN);



    snake_update(current_time + 0.63f);

    snake_food_update();







    UnityAssertEqualNumber((UNITY_INT)((2)), (UNITY_INT)((snake_get_len())), (

   ((void *)0)

   ), (UNITY_UINT)(103), UNITY_DISPLAY_STYLE_INT);

}
