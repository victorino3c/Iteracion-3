
/** 
 * @brief Implements the player's interface
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
 * This structure contains all relevant info 
 * and members of a player
 */


typedef struct _Player
{
  Id id;
  char name[Player_Name_lenght];
  Inventory *inventory;
  Id location;
  int health;
} Player;

/** player_create allocates memory for a new player
 * and initializes all its members
 */
Player *player_create(Id id)
{
  Player *new_player = NULL;

  /*Error control */
  if (id == NO_ID)
  {
      return NULL;
  }

  new_player = (Player *) malloc(sizeof(Player));
	/*Error control */
  if (new_player == NULL)
  {
    return NULL;
  }
  
  /* Initializing all of player's members*/
  new_player->id = id;
  new_player->health = 3;
  new_player->name[0] = '\0';
  new_player->location = NO_ID;
  new_player->inventory = inventory_create();

  return new_player;
}

/** player_destroy frees all previously allocated
 * memory for a player
 */
STATUS player_destroy(Player *player)
{
	/*Error control */
  if (!player)
  {
    return ERROR;
  }
  
  if (player->inventory != NULL) {
    inventory_destroy(player->inventory);
    player->inventory = NULL;
  }
	
  free(player);
  player = NULL;
  return OK;
}

/** player_get_id gets a player's id
 */
Id player_get_id(Player *player)
{
	/*Error control */
  if (!player)
  {
    return NO_ID;
  }
  
  return player->id;
}

/**
 * Tests whether an id is from a player or not
 */
STATUS player_test_id(Id id)
{
  int first_digit, digits;

  /*Error control */
  if (id < 0)
  {
    return ERROR;
  }

  /* Figuring out how many digits - 1 are there 
  and which one is the first */
  digits = (int)log10(id); 

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

/** player_get_name gets a player's name
 */
const char *player_get_name(Player *player)
{
	/*Error control */
  if (!player)
  {
    return NULL;
  }
  
  return player->name;
}

/** player_get_location gets a player's location
 */
Id player_get_location(Player *player)
{
	/*Error control */
  if (!player)
  {
    return NO_ID;
  }
  
  return player->location;
}

/** player_get_health gets a player's health.
 */
int player_get_health(Player *player)
{
	/*Error control */
  if (!player)
  {
    return -1;
  }
  
  return player->health;
}

/** player_set_health sets a player's health
 */
STATUS player_set_health(Player *player, int health)
{ 
	/*Error control */
  if (!player)
  {
    return ERROR; 
  }
  
  player->health = health;
  return OK;
}



/** player_set_name sets a player's location
 */
STATUS player_set_location(Player *player, Id location)
{
	/*Error control */
  if (!player)
  {
    return ERROR;
  }

  player->location = location;
  
  return OK;
}



/** player_set_object assigns an object to a player
 */
STATUS player_add_object(Player *player, Object *object)
{
	/*Error control */
  if (!player|| !object)
  {
    return ERROR;
  }
  
  inventory_add_object(player->inventory, obj_get_id(object));
  return OK;
}

/** Removes an object from a player's inventory
 */
STATUS player_del_object(Player *player, Id id_obj){
  /*Error control */
  if (!player || id_obj==NO_ID)
  {
    return ERROR;
  }
  
  inventory_remove_object(player->inventory, id_obj);
  return OK;
}

/** Gets a player's inventory 
 */
Inventory *player_get_inventory(Player *player)
{
	/*Error control */
  if (!player)
  {
    return NULL;
  }
  
  return player->inventory;
}



/** player_set_name sets the player's new name
 */
STATUS player_set_name(Player *player, char *name)
{
	/*Error control */
  if (!player || !name)
  {
    return ERROR;
  }
  
	/*Error control */
  if (!strcpy(player->name, name))
  {
    return ERROR;
  }
  
  return OK;
}

/** player_print prints all player related info in a string
 */
STATUS player_print(Player *player)
{
 /*Error control */
  if (!player)
  {
      return ERROR;
  }
  
  fprintf(stdout, "--> Player (Id: %ld; Name: %s)\n", player->id, player->name);

  return OK;
}

STATUS player_set_max_inventory(Player* player, int num) 
{

  if (!player)
  {
    return ERROR;
  }

  inventory_set_maxObjs(player->inventory, num);
  return OK;
}


