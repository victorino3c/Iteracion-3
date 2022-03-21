/** 
 * @brief Implementa el modulo del objeto.
 * 
 * @file player.c
 * @author Antonio Van-Oers
 * @version 1.3 
 * @date 12-02-2021
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "player.h"

/**
 * @brief Player
 *
 * Esta estructura almacena la informacion de un ojugador
 */


typedef struct _Player
{
  Id id;
  char name[Player_Name_lenght];
  Object *object;
  Id location;
  int health;
} Player;

/** player_create reserva memoria para un nuevo jugador e inicializa sus miembros.
 */
Player *player_create(Id id)
{
  Player *new_player = NULL;

  /* Control de errores */
  if (id == NO_ID)
  {
      return NULL;
  }

  new_player = (Player *) malloc(sizeof(Player));
	/* Control de errores */
  if (new_player == NULL)
  {
    return NULL;
  }
  
  /* Inicializacion del nuevo jugador*/
  new_player->id = id;
  new_player->health = 3;
  new_player->name[0] = '\0';
  new_player->location = NO_ID;
  new_player->object = NULL;

  return new_player;
}

/** player_destroy libera la memoria previamente reservada de un jugador.
 */
STATUS player_destroy(Player *player)
{
	/* Control de errores */
  if (!player)
  {
    return ERROR;
  }
  
  free(player);
  player = NULL;
  return OK;
}

/** player_get_id devuelve el id de un jugador (player).
 */
Id player_get_id(Player *player)
{
	/* Control de errores */
  if (!player)
  {
    return NO_ID;
  }
  
  return player->id;
}

/**
 * Comprueba si el id recibido es el de un player
 */
STATUS player_test_id(Id id)
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

/** player_get_name obtiene el nombre (name) de un jugador (player).
 */
const char *player_get_name(Player *player)
{
	/* Control de errores */
  if (!player)
  {
    return NULL;
  }
  
  return player->name;
}

/** player_get_location obtiene la posicion (location) de un jugador (player).
 */
Id player_get_location(Player *player)
{
	/* Control de errores */
  if (!player)
  {
    return NO_ID;
  }
  
  return player->location;
}

/** player_get_health obtiene la salud de un jugador (player).
 */
int player_get_health(Player *player)
{
	/* Control de errores */
  if (!player)
  {
    return -1;
  }
  
  return player->health;
}

/** player_set_health establece la salud de un jugador (player).
 */
STATUS player_set_health(Player *player, int health)
{ 
	/* Control de errores */
  if (!player)
  {
    return ERROR; 
  }
  
  player->health = health;
  return OK;
}



/** player_set_name establece la posicion (location) de un jugador (player).
 */
STATUS player_set_location(Player *player, Id location)
{
	/* Control de errores */
  if (!player)
  {
    return ERROR;
  }

  player->location = location;
  
  return OK;
}



/** player_get_name establece el objeto del player.
 */
STATUS player_set_object(Player *player, Object *object)
{
	/* Control de errores */
  if (!player)
  {
    return ERROR;
  }
  
  player->object = object;
  return OK;
}

Object *player_get_object(Player *player)
{
	/* Control de errores */
  if (!player)
  {
    return NULL;
  }
  
  return player->object;
}



/** player_set_name establece el nombre (name) de un jugador (player).
 */
STATUS player_set_name(Player *player, char *name)
{
	/* Control de errores */
  if (!player || !name)
  {
    return ERROR;
  }
  
	/* Control de errores */
  if (!strcpy(player->name, name))
  {
    return ERROR;
  }
  
  return OK;
}

/** player_print muestra por pantalla el id y el nombre de un jugador(player).
 */
STATUS player_print(Player *player)
{
 /* Control de errores */
  if (!player)
  {
      return ERROR;
  }
  
  fprintf(stdout, "--> Player (Id: %ld; Name: %s)\n", player->id, player->name);

  return OK;
}


