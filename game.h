/** 
 * @brief It defines the game interface
 * 
 * @file game.h
 * @author Antonio Van-Oers, Miguel Soto, Nicolas Victorino, Ignacio Nunez
 * @version 2.1
 * @date 12-02-2021 
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "command.h"
#include "space.h"
#include "link.h"
#include "types.h"
#include "player.h"
#include "object.h"
#include "enemy.h"
#include "inventory.h"

#define MAX_LINKS 200

/**
 * @brief Game's structucture
 *
 * Has all members necessary to create, start and play a game
 */
typedef struct _Game Game;

/**
  * @brief returns description' pointer
  * @author Antonio Van-Oers, Miguel Soto, Nicolas Victorino, Ignacio Nunez
  * 
  * @param game a pointer to game
  * @return description pointer (can be NULL)
  */
char *game_get_description(Game *game);

/**
 * @brief Allocs memory for some of game's members
 * @author Miguel Soto
 * 
 * @param game a pointer to game
 * @return OK if everything goes well or ERROR if there was any mistake
 */
STATUS game_alloc(Game *game);

/**
  * @brief initializes all necessary members to empty values
  * @author Antonio Van-Oers, Miguel Soto, Nicolas Victorino, Ignacio Nunez
  * 
  * @param game a pointer to game
  * @return OK if everything goes well or ERROR if there was any mistake
  */
STATUS game_create(Game *game);

/**
  * @brief Checks if there was any update on the game cmd, whenever the user types something
  * @author Antonio Van-Oers, Miguel Soto, Nicolas Victorino, Ignacio Nunez
  *
  * game_update updates cmd whenever something is typed in, this is where 
  * every known case gets interpreted as the various actions on the game, 
  * any other input would be considered unknown
  * 
  * @param game a pointer to game, que contiene los datos de localización de objeto y jugador 
  * junto con los espacios del juego y el ultimo comando
  * @param cmd la variable tipo T_Command del interprete de comandos, varia segun el comando introducido por el usuario
  * @return 0 if ERROR, 1 if OK, and 5 if OK but dont print condition
  */
int game_update(Game *game, T_Command cmd, char *arg);

/**
  * @brief frees/destroys the game
  * @author Antonio Van-Oers, Miguel Soto, Nicolas Victorino, Ignacio Nunez
  *
  * game_destroy frees/destroys all of game's spaces  
  * calling space_destroy for each one of them
  * @param game a pointer to game
  * @return OK if everything goes well or ERROR if there was any mistake
  */
STATUS game_destroy(Game *game);

/**
  * @brief Ends the game
  * @author Antonio Van-Oers, Miguel Soto, Nicolas Victorino, Ignacio Nunez
  *
  * False is the output when called, meaning game has ended
  * 
  * @param game a pointer to game
  * @return FALSE 
  */
BOOL game_is_over(Game *game);

/**
  * @brief  Prints all game related relevant data
  * @author Antonio Van-Oers, Miguel Soto, Nicolas Victorino, Ignacio Nunez
  *
  * @param game a pointer to game
  */
void game_print_data(Game *game);

/**
  * @brief Gets a space via target id
  * @author Antonio Van-Oers, Miguel Soto, Nicolas Victorino, Ignacio Nunez
  *
  * Checks wheter a space is on the game by comparing target id with each game's spaces' id
  * @param game a pointer to game  
  * @param id target space's id
  * @return a pointer to the space which has that id, or NULL if something went wrong
  * or the space doesn't belong to the game
  */
Space *game_get_space(Game *game, Id id);

/**
 * @brief Gets an object via target id
 * @author Miguel Soto
 * 
 * Checks wheter an object is on the game by comparing target id with each game's objects' id
 * @param game a pointer to game
 * @param id target objec's id
 * @return a pointer to the object which has that id, or NULL if something went wrong
 * or the object doesn't belong to the game
 */
Object *game_get_object(Game *game, Id id);

/**
 * @brief Gets a player via target id
 * @author Miguel Soto
 * 
 * Checks wheter a player is on the game by comparing target id with each game's players' id
 * @param game a pointer to game
 * @param id target player's id
 * @return a pointer to the player which has that id, or NULL if something went wrong
 * or the player doesn't belong to the game
 */
Player *game_get_player(Game *game, Id id);

/**
 * @brief Gets an enemy via target id
 * @author Miguel Soto
 * 
 * Checks wheter an enemy is on the game by comparing target id with each game's enemies' id
 * @param game a pointer to game
 * @param id target enemy's id
 * @return a pointer to the enemy which has that id, or NULL if something went wrong
 * or the enemy doesn't belong to the game
 */
Enemy *game_get_enemy(Game *game, Id id);

/**
 * @brief Gets an enemy via target id
 * @author Miguel Soto
 * 
 * Checks wheter a link is on the game by comparing target id with each game's links' id
 * @param game a pointer to game
 * @param id target link's id
 * @return a pointer to the link which has that id, or NULL if something went wrong
 * or the link doesn't belong to the game
 */
Link *game_get_link(Game *game, Id id);

/**
  * @brief Gets a player's location via target id
  * @author Miguel Soto
  *
  * @param game a pointer to game
  * @param player_id targe player's id
  * @return player's location's id or NO_ID if something went wrong
  */
Id game_get_player_location(Game *game, Id player_id);

/**
  * @brief Gets an enemy's location via target id
  * @author Antonio Van-Oers Luis
  *
  * @param game a pointer to game
  * @param enemy_id target enemy's id
  * @return enemy's location's id or NO_ID if something went wrong
  */
Id game_get_enemy_location(Game *game, Id enemy_id);

/**
  * @brief Gets an objects's location via target id
  * @author Miguel Soto
  *
  * @param game a pointer to game
  * @param obj_id target object's id
  * @return object's location's id or NO_ID if something went wrong
  */
Id game_get_object_location(Game *game, Id obj_id);

/**
  * @brief Gets the last command input 
  * @author Antonio Van-Oers, Miguel Soto, Nicolas Victorino, Ignacio Nunez
  *
  * @param game a pointer to game
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
T_Command game_get_last_command(Game *game);

/**
 * @brief Function that gets the enemy id based on the position it is located in the enemy array located in the game structure
 * @author Nicolas Victorino
 * 
 * @param game  pointer to game @param num number of the enemy position in the array 
 * @return The id of the enemy, or in case it doesn't have one, NO_ID
 */
Id game_get_enemy_id(Game *game, int num);

/**
 * @brief Function that gets the player id 
 * @author Nicolas Victorino
 * 
 * @param game  pointer to game  
 * @return The id of the player, or in case it doesn't have one, NO_ID
 */
Id game_get_player_id(Game* game);

/**
 * @brief Function that gets the object id based on the position it is located in the object array located in the game structure
 * @author Nicolas Victorino
 * 
 * @param game  pointer to game @param num number of the object position in the array 
 * @return The id of the enemy, or in case it doesn't have one, NO_ID
 */
Id game_get_object_id(Game *game, int num);

/**
 * @brief Function that saves memory for the game in game_loop
 * @author Nicolas Victorino
 * 
 * @return A pointer to the game
 */
Game* game_alloc2();

/**
 * @brief It get if link is open or close giving an space and a specific direction
 * @author Miguel Soto
 * 
 * @param game pointer to game
 * @param act_spaceid id from space (normaly it would be actual player location)
 * @param dir link's direction
 * @return OPEN if link is open or CLOSE if link is close. In case of error, returns CLOSE 
 */
LINK_STATUS game_get_connection_status(Game *game, Id act_spaceid, DIRECTION dir);

/**
 * @brief It get id from the space destination of a link
 * @author Miguel Soto
 * 
 * @param game pointer to game
 * @param act_spaceid id from space (normaly it would be actual player location)
 * @param dir link's direction
 * @return Id from the space destination of a link
 */
Id game_get_connection(Game *game, Id act_spaceid, DIRECTION dir);


#endif
