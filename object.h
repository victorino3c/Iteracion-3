/** 
 * @brief Implements the object's interface
 * 
 * @file object.h
 * @author Miguel Soto
 * @version 1.3 
 * @date 12-02-2021
 * @copyright GNU Public License
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"

#define OBJ_NAME_LEN 40
#define MAX_OBJS 10

typedef struct _Object Object;


/**
 * @brief Crea un objeto nuevo.
 * @author Miguel Soto
 *
 * obj_create allocates memory for a new object and initializes all its members
 * @param id is the target object's id
 * @return a new object (type Object) initialized, or NULL if anything goes wrong.
 */
Object *obj_create(Id id);

/**
 * @brief Destruye un objeto.
 * @author Miguel Soto
 * 
 * obj_destroy frees the previously allocated memory for an object
 * @param obj is a pointer to the target object.
 * @return Ok if it succesfully completed the task or ERROR, if anything goes wrong.
 */
STATUS obj_destroy(Object *obj);

/**
 * @brief Tests whether the designated id is from an object or not
 * @author Miguel Soto
 * 
 * @param id is the target object's id
 * @return Ok if it succesfully completed the task or ERROR, if anything goes wrong.
 */
STATUS obj_test_id(Id id);

/**
 * @brief  Gets an object's id
 * @author Miguel Soto
 * 
 * @param obj is a pointer to the target object.
 * @return object's id, or NULL if anything goes wrong.
 */
Id obj_get_id(Object *obj);

/**
 * @brief Gets an object's name 
 * @author Miguel Soto
 *
 * @param obj is a pointer to the target object.
 * @return a string with the object's name, or NULL if anything goes wrong.
 */
const char *obj_get_name(Object *obj);

/**
 * @brief Sets an object's name
 * @author Miguel Soto
 * 
 * @param obj is a pointer to the target object.
 * @param name a string containing the new object's name
 * @return Ok if it succesfully completed the task or ERROR, if anything goes wrong.
 */
STATUS obj_set_name(Object *obj, char *name);

/**
 * @brief Gets an object's position
 * @author Miguel Soto
 * 
 * @param obj is a pointer to the target object.
 * @return space's id where the object is located.
 */
Id obj_get_location(Object *obj);

/**
 * @brief Sets an object's position
 * @author Miguel Soto
 * 
 * @param obj is a pointer to the target object.
 * @param id is the target object's id
 * @return Ok if it succesfully completed the task or ERROR, if anything goes wrong. 
 */
STATUS obj_set_location(Object *obj, Id id);

/**
 * @brief Prints the info regarding an object 
 * @author Miguel Soto
 * 
 * obj_print prints an object's name and id
 * @param obj is a pointer to the target object.
 * @return Ok if it succesfully completed the task or ERROR, if anything goes wrong.
 */
STATUS obj_print(Object *obj);

#endif
