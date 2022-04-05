/**
 * @brief It tests game module
 *
 * @file game_test.c
 * @author Ignacio Nunnez
 * @version 3.0
 * @date 04-04-2022
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../game.h"
#include "game_test.h"
#include "test.h"

#define MAX_TESTS 33

/**
 * @brief Main function for inventory unit tests.
 *
 * You may execute ALL or a SINGLE test
 *   1.- No parameter -> ALL test are executed
 *   2.- A number means a particular test (the one identified by that number)
 *       is executed
 *
 */
int main(int argc, char **argv)
{

  int test = 0;
  int all = 1, i;

  if (argc < 2)
  {
    printf("Running all test for game inventory:\n");
  }
  else
  {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 && test > MAX_TESTS)
    {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }

  i = 1;
  if (all || test == i) test1_game_alloc2();
  i++;

  if (all || test == i) test1_game_destroy();
  i++;
  if (all || test == i) test2_game_destroy();
  i++;

  if (all || test == i) test1_game_create();
  i++;
  if (all || test == i) test2_game_create();
  i++;

  if (all || test == i) test1_game_update();
  i++;
  if (all || test == i) test2_game_update();
  i++;

  if (all || test == i) test1_game_is_over();
  i++;
  if (all || test == i) test2_game_is_over();
  i++;

  if (all || test == i) test1_game_get_space();
  i++;
  if (all || test == i) test2_game_get_space();
  i++;

  if (all || test == i) test1_game_get_object();
  i++;
  if (all || test == i) test2_game_get_object();
  i++;

  if (all || test == i) test1_game_get_player();
  i++;
  if (all || test == i) test2_game_get_player();
  i++;

  if (all || test == i) test1_game_get_enemy();
  i++;
  if (all || test == i) test2_game_get_enemy();
  i++;
  
  if (all || test == i) test1_game_get_player_location();
  i++;
  if (all || test == i) test2_game_get_player_location();
  i++;

  if (all || test == i) test1_game_get_enemy_location();
  i++;
  if (all || test == i) test2_game_get_enemy_location();
  i++;

  if (all || test == i) test1_game_get_object_location();
  i++;
  if (all || test == i) test2_game_get_object_location();
  i++; 

  if (all || test == i) test1_game_get_last_command();
  i++;
  if (all || test == i) test2_game_get_last_command();
  i++;  

  if (all || test == i) test1_game_get_enemy_id();
  i++;
  if (all || test == i) test2_game_get_enemy_id();
  i++;  

  if (all || test == i) test1_game_get_player_id();
  i++;
  if (all || test == i) test2_game_get_player_id();
  i++;

  if (all || test == i) test1_game_get_object_id();
  i++;
  if (all || test == i) test2_game_get_object_id();
  i++;

  /*if (all || test == i) test1_game_get_connection_status();
  i++;
  if (all || test == i) test2_game_get_connection_status();
  i++;
  
  if (all || test == i) test1_game_get_connection();
  i++;
  if (all || test == i) test2_game_get_connection();
  i++;*/

  if (all || test == i) test1_game_get_description();
  i++;

  PRINT_PASSED_PERCENTAGE;

  return 1;
}

void test1_game_alloc2(){
    Game *g = NULL;
    g = game_alloc2();
    PRINT_TEST_RESULT(g != NULL);
    game_destroy(g);
}

void test1_game_destroy(){
    Game *g = NULL;
    g = game_alloc2();
    PRINT_TEST_RESULT(game_destroy(g) == OK);
}

void test2_game_destroy(){
    Game *g = NULL;
    PRINT_TEST_RESULT(game_destroy(g) == ERROR);
}

void test1_game_create(){
    Game *g = NULL;
    g = game_alloc2();
    PRINT_TEST_RESULT(game_create(g) == OK);
    game_destroy(g);
}

void test2_game_create(){
    Game *g = NULL;
    PRINT_TEST_RESULT(game_create(g) == ERROR);
}

void test1_game_update(){
    Game *g = NULL;
    char *arg = NULL;
    g = game_alloc2();
    PRINT_TEST_RESULT(game_update(g, EXIT, arg) > 0);
    game_destroy(g);
}

void test2_game_update(){
    Game *g = NULL;
    char *arg = NULL;
    PRINT_TEST_RESULT(game_update(g, EXIT, arg) == 0);
}

void test1_game_is_over(){
    Game *g = NULL;
    g = game_alloc2();
    player_set_health(game_get_player(g, 0), 0);
    PRINT_TEST_RESULT(game_is_over(g) == TRUE);
    game_destroy(g);
}

void test2_game_is_over(){
    Game *g = NULL;
    g = game_alloc2();
    player_set_health(game_get_player(g, 0), 10);
    PRINT_TEST_RESULT(game_is_over(g) == TRUE);
    game_destroy(g);
}

void test1_game_get_space(){
    Game *g = NULL;
    Space *s = NULL;
    s = space_create(11);
    g = game_alloc2();
    game_create(g);
    game_add_space(g, s);
    PRINT_TEST_RESULT(game_get_space(g, 11) != NULL);
    game_destroy(g);
}

void test2_game_get_space(){
    Game *g = NULL;
    Space *s = NULL;
    s = space_create(11);
    g = game_alloc2();
    game_create(g);
    game_add_space(g, s);
    PRINT_TEST_RESULT(game_get_space(g, 12) == NULL);
    game_destroy(g);
}

void test1_game_get_object(){
    Game *g = NULL;
    Object *o = NULL;
    o = obj_create(31);
    g = game_alloc2();
    game_create(g);
    game_add_object(g, o);
    PRINT_TEST_RESULT(game_get_object(g, 31) != NULL);
    game_destroy(g);
}

void test2_game_get_object(){
    Game *g = NULL;
    Object *o = NULL;
    o = obj_create(31);
    g = game_alloc2();
    game_create(g);
    game_add_object(g, o);
    PRINT_TEST_RESULT(game_get_object(g, 32) == NULL);
    game_destroy(g);
}

void test1_game_get_player(){
    Game *g = NULL;
    Player *p = NULL;
    p = player_create(21);
    g = game_alloc2();
    game_create(g);
    game_add_player(g, p);
    PRINT_TEST_RESULT(game_get_player(g, 21) != NULL);
    game_destroy(g);
}

void test2_game_get_player(){
    Game *g = NULL;
    Player *p = NULL;
    p = player_create(21);
    g = game_alloc2();
    game_create(g);
    game_add_player(g, p);
    PRINT_TEST_RESULT(game_get_player(g, 22) == NULL);
    game_destroy(g);
}

void test1_game_get_enemy(){
    Game *g = NULL;
    Enemy *e = NULL;
    e = enemy_create(41);
    g = game_alloc2();
    game_create(g);
    game_add_enemy(g, e);
    PRINT_TEST_RESULT(game_get_enemy(g, 41) != NULL);
    game_destroy(g);
}

void test2_game_get_enemy(){
    Game *g = NULL;
    Enemy *e = NULL;
    e = enemy_create(41);
    g = game_alloc2();
    game_create(g);
    game_add_enemy(g, e);
    PRINT_TEST_RESULT(game_get_enemy(g, 42) == NULL);
    game_destroy(g);
}

void test1_game_get_player_location(){
    Game *g = NULL;
    Player *p = NULL;
    p = player_create(21);
    player_set_location(p, 100);
    g = game_alloc2();
    game_create(g);
    game_add_player(g, p);
    PRINT_TEST_RESULT(game_get_player_location(g, 21) == 100);
    game_destroy(g);
}

void test2_game_get_player_location(){
    Game *g = NULL;
    g = game_alloc2();
    game_create(g);
    PRINT_TEST_RESULT(game_get_player_location(g, 21) == NO_ID);
    game_destroy(g);
}

void test1_game_get_enemy_location(){
    Game *g = NULL;
    Enemy *e = NULL;
    e = enemy_create(41);
    enemy_set_location(e, 100);
    g = game_alloc2();
    game_create(g);
    game_add_enemy(g, e);
    PRINT_TEST_RESULT(game_get_enemy_location(g, 41) == 100);
    game_destroy(g);
}

void test2_game_get_enemy_location(){
    Game *g = NULL;
    g = game_alloc2();
    game_create(g);
    PRINT_TEST_RESULT(game_get_enemy_location(g, 41) == NO_ID);
    game_destroy(g);
}

void test1_game_get_object_location(){
    Game *g = NULL;
    Object *o = NULL;
    o = obj_create(31);
    obj_set_location(o, 100);
    g = game_alloc2();
    game_create(g);
    game_add_object(g, o);
    PRINT_TEST_RESULT(game_get_object_location(g, 31) == 100);
    game_destroy(g);
}

void test2_game_get_object_location(){
    Game *g = NULL;
    g = game_alloc2();
    game_create(g);
    PRINT_TEST_RESULT(game_get_object_location(g, NO_ID) == NO_ID);
    game_destroy(g);
}

void test1_game_get_last_command(){
    Game *g = NULL;
    char *arg = NULL;
    g = game_alloc2();
    game_create(g);
    game_update(g, EXIT, arg);
    PRINT_TEST_RESULT(game_get_last_command(g) == EXIT);
    game_destroy(g);
}

void test2_game_get_last_command(){
    Game *g = NULL;
    char *arg = NULL;
    g = game_alloc2();
    game_create(g);
    game_update(g, EXIT, arg);
    PRINT_TEST_RESULT(game_get_last_command(g) != MOVE);
    game_destroy(g);
}

void test1_game_get_enemy_id(){
    Game *g = NULL;
    Enemy *e = NULL;
    e = enemy_create(41);
    g = game_alloc2();
    game_create(g);
    game_add_enemy(g, e);
    PRINT_TEST_RESULT(game_get_enemy_id(g, 0) == 41);
    game_destroy(g);
}

void test2_game_get_enemy_id(){
    Game *g = NULL;
    g = game_alloc2();
    game_create(g);
    PRINT_TEST_RESULT(game_get_enemy_id(g, 0) == NO_ID);
    game_destroy(g);
}

void test1_game_get_player_id(){
    Game *g = NULL;
    Player *p = NULL;
    p = player_create(21);
    g = game_alloc2();
    game_create(g);
    game_add_player(g, p);
    PRINT_TEST_RESULT(game_get_player_id(g) == 21);
    game_destroy(g);
}

void test2_game_get_player_id(){
    Game *g = NULL;
    g = game_alloc2();
    game_create(g);
    PRINT_TEST_RESULT(game_get_player_id(g) == NO_ID);
    game_destroy(g);
}

void test1_game_get_object_id(){
    Game *g = NULL;
    Object *o = NULL;
    o = obj_create(31);
    g = game_alloc2();
    game_create(g);
    game_add_object(g, o);
    PRINT_TEST_RESULT(game_get_object_id(g, 0) == 31);
    game_destroy(g);
}

void test2_game_get_object_id(){
    Game *g = NULL;
    g = game_alloc2();
    game_create(g);
    PRINT_TEST_RESULT(game_get_object_id(g, 0) == NO_ID);
    game_destroy(g);
}

void test1_game_get_connection_status(){
    Game *g = NULL;
    Space *s1;
    Link *l;
    g = game_alloc2();
    game_create(g);
    l = link_create(40);
    link_set_start(l, 11);
    link_set_destination(l, 12);
    link_set_direction(l, W);
    s1 = space_create(11);
    space_set_link(s1, 40, W);
    link_set_status(l, OPEN);
    game_add_space(g, s1);
    PRINT_TEST_RESULT(game_get_connection_status(g, 11, W) == OPEN);
    game_destroy(g);
}

void test2_game_get_connection_status(){
    Game *g = NULL;
    Space *s1, *s2;
    Link *l;
    g = game_alloc2();
    game_create(g);
    l = link_create(40);
    link_set_start(l, 11);
    link_set_destination(l, 12);
    link_set_direction(l, W);
    s1 = space_create(11);
    s2 = space_create(12);
    space_set_link(s1, 40, W);
    PRINT_TEST_RESULT(game_get_connection_status(g, 11, S) == CLOSE);
    game_destroy(g);
}

void test1_game_get_connection(){
    Game *g = NULL;
    Space *s1;
    Link *l;
    g = game_alloc2();
    game_create(g);
    l = link_create(40);
    link_set_start(l, 11);
    link_set_destination(l, 12);
    link_set_direction(l, W);
    s1 = space_create(11);
    space_set_link(s1, 40, W);
    PRINT_TEST_RESULT(game_get_connection(g, 11, W) == 12);
    game_destroy(g);
}

void test2_game_get_connection(){
    Game *g = NULL;
    Space *s1;
    Link *l;
    g = game_alloc2();
    game_create(g);
    l = link_create(40);
    link_set_start(l, 11);
    link_set_destination(l, 12);
    link_set_direction(l, W);
    s1 = space_create(11);
    space_set_link(s1, 40, W);
    PRINT_TEST_RESULT(game_get_connection(g, 11, N) == NO_ID);
    game_destroy(g);
}

void test1_game_get_description(){
    Game *g = NULL;
    g =  game_alloc2();
    game_create(g);
    PRINT_TEST_RESULT(game_get_description(g) != NULL);
    game_destroy(g);
}