/**
* @brief It implements enemy module in the ant game
*
* @file inventory.c
* @author Ignacio Nunnez
* @version 1.3
* @date 19/03/2022
* @copyright GNU Public License
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory.h"

/**
 * @brief Inventory
 *
 * This struct stores all the 
 * inventory's information
 */
struct _Inventory {
  Set* objects;
};

/** inventory_create allocates memory for a new inventory
  *  and initializes its members
  */
Inventory* inventory_create() {
  Inventory *newInventory = NULL;

  newInventory = (Inventory *) malloc(sizeof (Inventory));
  if (newInventory == NULL) {
    return NULL;
  }

  /* Initialization of an empty inventory*/
  newInventory->objects = set_create();

  return newInventory;
}

/** inventory_destroy frees the previous memory allocation 
  *  for an inventory
  */
STATUS inventory_destroy(Inventory* inventory) {
  
  /* Error control */
  if (!inventory) {
    return ERROR;
  }

	set_destroy(inventory->objects);
	free(inventory);

  return OK;
}

/** It gets the set of objects
 *  of an inventory
  */
Set *inventory_get_objects(Inventory* inventory) {
  
  /* Error control */
  if (!inventory) {
    return NULL;
  }

  return inventory->objects;
}

/** It sets the objects of an enemy
  */
STATUS inventory_set_objects(Inventory* inventory, Set* set) {

	/*ERROR CONTROL*/
	if(!inventory || !set){
		return ERROR;
	}

	inventory->objects = set;
	return OK;
}

/* It adds an object to the inventory if possible
	*/
STATUS inventory_add_object(Inventory* inventory, Id object) {

	/*CONTROL ERROR*/
	if(!inventory || !object){
		return ERROR;
	}

	if(set_get_n_is(inventory->objects) == MAX_INV_OBJ){
		return ERROR;
	}

	set_add(inventory->objects, object);

	return OK;
	
}

/* It removes an object of the inventory
	*/
STATUS inventory_remove_object(Inventory* inventory, Id object) {

	/*CONTROL ERROR*/
	if(!inventory || !object){
		return ERROR;
	}

	if(set_del_id(inventory->objects, object) == OK){
		return OK;
	}

	return ERROR;
	
}

/** It prints the enemy information
  */
STATUS inventory_print(Inventory* inventory) {

  /* Error Control */
  if (!inventory) {
    return ERROR;
  }

  /* 1. Prints the Set of the inventory*/
	fprintf(stdout, "Set of objects:\n");
  set_print(inventory->objects);

  return OK;
}