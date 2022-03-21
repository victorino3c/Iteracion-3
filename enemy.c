/** 
 * @brief Implements the enemy interface
 * 
 * @file enemy.c
 * @author Antonio Van-Oers
 * @version 1.3 
 * @date 12-02-2021
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "enemy.h"

/**
 * @brief Enemy
 *
 * This structure stores all info that each enemy has
 */
typedef struct _Enemy
{
  Id id;
  char name[Enemy_Name_lenght];
  Id location;
  int health;
} Enemy;

/**enemy_create allocates memory for a new enemy and initializes all its members .
 */
Enemy *enemy_create(Id id)
{
  Enemy *new_enemy = NULL;

  /* Control de errores */
  if (id == NO_ID)
  {
      return NULL;
  }

  new_enemy = (Enemy *) malloc(sizeof(Enemy));
	/* Control de errores */
  if (new_enemy == NULL)
  {
    return NULL;
  }
  
  /* Enemy's members initialization*/
  new_enemy->id = id;
  new_enemy->health = 3;
  new_enemy->name[0] = '\0';
  new_enemy->location = NO_ID;

  return new_enemy;
}

/** enemy_destroy frees the previous memory allocation for an enemy
 */
STATUS enemy_destroy(Enemy *enemy)
{
	/* Control de errores */
  if (!enemy)
  {
    return ERROR;
  }
  
  free(enemy);
  enemy = NULL;
  return OK;
}

/**  It gets an enemy's id
 */
Id enemy_get_id(Enemy *enemy)
{
	/* Control de errores */
  if (!enemy)
  {
    return NO_ID;
  }
  
  return enemy->id;
}

/**
 * Tests whether the id is from an enemy or not
 */
STATUS enemy_test_id(Id id)
{
  int first_digit, digits;

  /* Control de errores */
  if (id < 0)
  {
    return ERROR;
  }

  /* Calcular numbero total de digitos - 1 */
  digits = (int)log10(id); 

  /* Obtener primer digito */
  first_digit = (int)(id / pow(10, digits));
  
  if (first_digit == FD_ID_PLAYER)
  {
    return OK;
  }
  else
  {
    return ERROR;
  }
}

/** enemy_get_name obtiene el nombre (name) de un enemigo (enemy).
 */
const char *enemy_get_name(Enemy *enemy)
{
	/* Control de errores */
  if (!enemy)
  {
    return NULL;
  }
  
  return enemy->name;
}

/** enemy_get_location obtiene la posicion (location) de un enemigo (enemy).
 */
Id enemy_get_location(Enemy *enemy)
{
	/* Control de errores */
  if (!enemy)
  {
    return NO_ID;
  }
  
  return enemy->location;
}

/**
 * enemy_get_health obtiene la salud de un enemigo (enemy).
 */
int enemy_get_health(Enemy *enemy)
{
  if (!enemy)
  {
    return -1;                  
  }
  
  return enemy->health;
}


/**
 * enemy_set_health establece la salud de un enemigo (enemy).
 */
STATUS enemy_set_health(Enemy *enemy, int health)
{
	/* Control de errores */
  if (!enemy)
  {
    return ERROR;
  } 
  
  enemy->health = health;
  return OK;
}
 

/** enemy_set_name establece la posicion (location) de un enemigo (enemy).
 */
STATUS enemy_set_location(Enemy *enemy, Id location)
{
	/* Control de errores */
  if (!enemy)
  {
    return ERROR;
  }
  
  enemy->location = location;
  return OK;
}


/** enemy_set_name establece el nombre (name) de un enemigo (enemy).
 */
STATUS enemy_set_name(Enemy *enemy, char *name)
{
	/* Control de errores */
  if (!enemy || !name)
  {
    return ERROR;
  }
  
	/* Control de errores */
  if (!strcpy(enemy->name, name))
  {
    return ERROR;
  }
  
  return OK;
}


/** enemy_print muestra por pantalla el id y el nombre de un enemigo(enemy).
 */
STATUS enemy_print(Enemy *enemy)
{
 /* Control de errores */
  if (!enemy)
  {
      return ERROR;
  }
  
  fprintf(stdout, "--> enemy (Id: %ld; Name: %s)\n", enemy->id, enemy->name);

  return OK;
}
