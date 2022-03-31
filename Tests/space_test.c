/**
 * @brief It tests space module
 *
 * @file space_test.c
 * @author Profesores Pprog
 * @version 3.0
 * @date 09-03-2021
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../space.h"
#include "space_test.h"
#include "test.h"

#define MAX_TESTS 33

/**
 * @brief Main function for SPACE unit tests.
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
    printf("Running all test for module Space:\n");
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
  if (all || test == i) test1_space_create();
  i++;
  if (all || test == i) test2_space_create();
  i++;

  if (all || test == i) test1_space_destroy();
  i++;
  if (all || test == i) test2_space_destroy();
  i++;

  if (all || test == i) test1_space_set_name();
  i++;
  if (all || test == i) test2_space_set_name();
  i++;
  if (all || test == i) test3_space_set_name();
  i++;

  if (all || test == i) test1_space_set_north();
  i++;
  if (all || test == i) test2_space_set_north();
  i++;

  if (all || test == i) test1_space_set_south();
  i++;
  if (all || test == i) test2_space_set_south();
  i++;

  if (all || test == i) test1_space_set_east();
  i++;
  if (all || test == i) test2_space_set_east();
  i++;

  if (all || test == i) test1_space_set_west();
  i++;
  if (all || test == i) test2_space_set_west();
  i++;

  if (all || test == i) test2_space_set_west();
  i++;
  if (all || test == i) test2_space_set_west();
  i++;

  if (all || test == i) test1_space_add_object();
  i++;
  if (all || test == i) test2_space_add_object();
  i++;

  if (all || test == i) test1_space_del_object();
  i++;
  if (all || test == i) test2_space_del_object();
  i++;
  if (all || test == i) test3_space_del_object();
  i++;

  if (all || test == i) test1_space_get_object();
  i++;
  if (all || test == i) test2_space_get_object();
  i++;
  if (all || test == i) test3_space_get_object();
  i++;

  if (all || test == i) test1_space_get_north();
  i++;
  if (all || test == i) test2_space_get_north();
  i++;

  if (all || test == i) test1_space_get_south();
  i++;
  if (all || test == i) test2_space_get_south();
  i++;

  if (all || test == i) test1_space_get_east();
  i++;
  if (all || test == i) test2_space_get_east();
  i++;

  if (all || test == i) test1_space_get_west();
  i++;
  if (all || test == i) test2_space_get_west();
  i++;

  if (all || test == i) test1_space_get_id();
  i++;
  if (all || test == i) test2_space_get_id();
  i++;

  if (all || test == i) test2_space_get_id();
  i++;
  if (all || test == i) test2_space_get_id();
  i++;

  if (all || test == i) test1_space_set_gdesc();
  i++;
  if (all || test == i) test2_space_set_gdesc();
  i++;

  if (all || test == i) test1_space_get_gdesc();
  i++;
  if (all || test == i) test2_space_get_gdesc();
  i++;

  PRINT_PASSED_PERCENTAGE;

  return 1;
}

/*  space_create */
void test1_space_create()
{
  int result;
  Space *s;
  s = space_create(5);
  result = s != NULL;
  PRINT_TEST_RESULT(result);
  space_destroy(s);
}
void test2_space_create()
{
  Space *s;
  s = space_create(4);
  PRINT_TEST_RESULT(space_get_id(s) == 4);
  space_destroy(s);
}

/*  space_destroy*/
void test1_space_destroy()
{
  Space *s = NULL;
  s = space_create(1);
  PRINT_TEST_RESULT(space_destroy(s) == OK);
}
void test2_space_destroy()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_destroy(s) == ERROR);
}

/*  space_set_name*/
void test1_space_set_name()
{
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_name(s, "hola") == OK);
  space_destroy(s);
}
void test2_space_set_name()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_name(s, "hola") == ERROR);
}
void test3_space_set_name()
{
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_name(s, NULL) == ERROR);
  space_destroy(s);
}

/*  space_set_north*/
void test1_space_set_north()
{
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_north(s, 4) == OK);
  space_destroy(s);
}
void test2_space_set_north()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_north(s, 4) == ERROR);
}
void test3_space_set_north()
{
  Space *s = NULL;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_north(s, NO_ID) == ERROR);
}

/*  space_set_south*/
void test1_space_set_south()
{
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_south(s, 4) == OK);
  space_destroy(s);
}
void test2_space_set_south()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_south(s, 4) == ERROR);
}
void test3_space_set_south()
{
  Space *s = NULL;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_south(s, NO_ID) == ERROR);
}

/*  space_set_east*/
void test1_space_set_east()
{
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_east(s, 4) == OK);
  space_destroy(s);
}
void test2_space_set_east()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_east(s, 4) == ERROR);
}
void test3_space_set_east()
{
  Space *s = NULL;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_east(s, NO_ID) == ERROR);
}

/*  space_set_west*/
void test1_space_set_west()
{
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_west(s, 4) == OK);
  space_destroy(s);
}
void test2_space_set_west()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_west(s, 4) == ERROR);
}
void test3_space_set_west()
{
  Space *s = NULL;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_west(s, NO_ID) == ERROR);
}

/*  space_get_id*/
void test1_space_get_id()
{
  Space *s = NULL;
  s = space_create(5);
  PRINT_TEST_RESULT(space_get_id(s) == 5);
  space_destroy(s);
}
void test2_space_get_id()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_id(s) == NO_ID);
}

/*  space_add_object*/
void test1_space_add_object()
{
  Space *s;
  s = space_create(1);
  PRINT_TEST_RESULT(space_add_objectid(s, 31) == OK);
  space_destroy(s);
}
void test2_space_add_object()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_add_objectid(s, 31) == ERROR);
}
void test3_space_add_object()
{
  Space *s;
  s = space_create(1);
  PRINT_TEST_RESULT(space_add_objectid(s, NO_ID) == ERROR);
  space_destroy(s);
}

/*  space_del_object*/
void test1_space_del_object()
{
  Space *s;
  s = space_create(1);
  space_add_objectid(s, 31);
  PRINT_TEST_RESULT(space_del_objectid(s, 31) == OK);
  space_destroy(s);
}
void test2_space_del_object()
{
  Space *s = NULL;
  s = space_create(1);
  space_add_objectid(s, 31);
  PRINT_TEST_RESULT(space_del_objectid(s, 32) == ERROR);
  space_destroy(s);
}
void test3_space_del_object()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_del_objectid(s, 31) == ERROR);
}

/*  space_get_object*/
void test1_space_get_object()
{
  Space *s;
  s = space_create(1);
  PRINT_TEST_RESULT(space_has_object(s, 31) == FALSE);
  space_destroy(s);
}
void test2_space_get_object()
{
  Space *s;
  s = space_create(1);
  space_add_objectid(s, 31);
  PRINT_TEST_RESULT(space_has_object(s, 31) == TRUE);
  space_destroy(s);
}
void test3_space_get_object()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_has_object(s, 31) == FALSE);
}

/*  space_get_name*/
void test1_space_get_name()
{
  Space *s;
  s = space_create(1);
  space_set_name(s, "adios");
  PRINT_TEST_RESULT(strcmp(space_get_name(s), "adios") == 0);
  space_destroy(s);
}
void test2_space_get_name()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_name(s) == NULL);
}

/*  space_get_north*/
void test1_space_get_north()
{
  Space *s;
  s = space_create(5);
  space_set_north(s, 4);
  PRINT_TEST_RESULT(space_get_north(s) == 4);
  space_destroy(s);
}
void test2_space_get_north()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_north(s) == NO_ID);
}

/*  space_get_south*/
void test1_space_get_south()
{
  Space *s;
  s = space_create(5);
  space_set_south(s, 2);
  PRINT_TEST_RESULT(space_get_south(s) == 2);
  space_destroy(s);
}
void test2_space_get_south()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_south(s) == NO_ID);
}

/*  space_get_east*/
void test1_space_get_east()
{
  Space *s;
  s = space_create(5);
  space_set_east(s, 1);
  PRINT_TEST_RESULT(space_get_east(s) == 1);
  space_destroy(s);
}
void test2_space_get_east()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_east(s) == NO_ID);
}

/*  space_get_west*/
void test1_space_get_west()
{
  Space *s;
  s = space_create(5);
  space_set_west(s, 6);
  PRINT_TEST_RESULT(space_get_west(s) == 6);
  space_destroy(s);
}
void test2_space_get_west()
{
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_west(s) == NO_ID);
}

/*  space_set_gdesc*/
void test1_space_set_gdesc()
{
  Space *s = NULL;
  char *gdesc[TAM_GDESC_X] = {"123456789", "123456789", "123456789", "123456789", "123456789"};
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_gdesc(s, gdesc) == OK);
  space_destroy(s);
}
void test2_space_set_gdesc()
{
  Space *s = NULL;
  char *gdesc[TAM_GDESC_X] = {"123456789", "123456789", "123456789", "123456789", "123456789"};
  PRINT_TEST_RESULT(space_set_gdesc(s, gdesc) == ERROR);
}
void test3_space_set_gdesc()
{
  Space *s = NULL;
  char **gdesc = NULL;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_gdesc(s, gdesc) == ERROR);
  space_destroy(s);
}

/*  space_get_desc*/
void test1_space_get_gdesc()
{
  Space *s = NULL;
  int res = 0, i = 0;
  char *gdesc[TAM_GDESC_X] = {"123456789", "123456789", "123456789", "123456789", "123456789"};
  s = space_create(5);
  space_set_gdesc(s, gdesc);
  for (res = 0, i = 0; i < 5; i++)
  {
    res += strcmp(space_get_gdesc(s)[4], gdesc[i]);
  }
  
  PRINT_TEST_RESULT(res == 0);
  space_destroy(s);
}
void test2_space_get_gdesc()
{
  Space *s = NULL;  
  PRINT_TEST_RESULT(space_get_gdesc(s) == NULL);
}
