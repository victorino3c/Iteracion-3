/** 
 * @brief Implementa el modulo del objeto.
 * 
 * @file object.c
 * @author Miguel Soto, Antonio Van-Oers, Ignacio Nuñez and Nicolas Victorino
 * @version 1.3 
 * @date 12-02-2021
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "object.h"

/**
 * @brief Object
 *
 * This structure contains all relevant info
 * and members regarding an object
 */
typedef struct _Object
{
  Id id;
  char name[OBJ_NAME_LEN];
  Id location;
} Object;

/** obj_create allocates memory for a new 
 * object and initializes all its members
 */
Object *obj_create(Id id)
{
  Object *new_obj = NULL;

  /* Error contol  */
  if (id == NO_ID)
  {
    return NULL;
  }

  new_obj = (Object *) malloc(sizeof(Object));
  if (new_obj == NULL)
  {
    return NULL;
  }
  
  /* Initializing all of object's members */
  new_obj->id = id;
  new_obj->name[0] = '\0';
  return new_obj;
}

/** obj_destroy frees the previously allocated 
 * memory for an object
 */
STATUS obj_destroy(Object *obj)
{
	/* Error contol  */
  if (!obj)
  {
    return ERROR;
  }
  
  free(obj);
  obj = NULL;
  return OK;
}

/**
 * Tests whether the designated id is from an object or not
 */
STATUS obj_test_id(Id id)
{
  int first_digit, digits;

  /* Error contol  */
  if (id < 0)
  {
    return ERROR;
  }

  /* It figures out how many digits - 1 are there */
  digits = (int)log10(id); 

  /* Gets the first digit */
  first_digit = (int)(id / pow(10, digits));
  
  if (first_digit == FD_ID_OBJ)
  {
    return OK;
  }
  else
  {
    return ERROR;
  }
}

/** obj_get_id gets an object's id
 */
Id obj_get_id(Object *obj)
{
	/* Error contol  */
  if (!obj)
  {
    return NO_ID;
  }
  
  return obj->id;
}

/** obj_get_name gets the name (name) from an object (obj).
 */
const char *obj_get_name(Object *obj)
{
	/* Error contol  */
  if (!obj)
  {
    return NULL;
  }
  
  return obj->name;
}

/** obj_set_name sets the name (name) of an object (obj).
 */
STATUS obj_set_name(Object *obj, char *name)
{
	/* Error contol  */
  if (!obj || !name)
  {
    return ERROR;
  }
  
	/* Error contol  */
  if (!strcpy(obj->name, name))
  {
    return ERROR;
  }
  
  return OK;
}

/** obj_get_location Gets an object's position
 */
Id obj_get_location(Object *obj)
{
  /* Error contol  */
  if (!obj)
  {
    return ERROR;
  }
  
  return obj->location;
}

/** obj_set_location sets an object's position
 */
STATUS obj_set_location(Object *obj, Id id)
{
  /* Error contol  */
  if (!obj)
  {
    return ERROR;
  }
  
  obj->location = id;
  return OK;
}

/** obj_print prints an object's name and id
 */
STATUS obj_print(Object *obj)
{
  /* Error contol  */
  if (!obj)
  {
    return ERROR;
  }
  
  fprintf(stdout, "--> Object (Id: %ld; Name: %s)\n", obj->id, obj->name);

  return OK;
}
