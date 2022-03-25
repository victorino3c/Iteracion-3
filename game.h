/** 
 * @brief It defines the game interface
 * 
 * @file game.h
 * @author Profesores PPROG
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
 * @brief Juego o partida
 *
 * Esta estructura contiene todos los datos necesarios para un juego o partida
 */
typedef struct _Game Game;

char *game_get_description(Game *game);

/**
 * @brief Reserva memoria para Player y Object del Game
 * @author Miguel Soto
 * 
 * @param game 
 * @return STATUS 
 */
STATUS game_alloc(Game *game);
/**
  * @brief Crea el juego
  * @author Profesores PPROG
  *
  * game_create inicializa todas las variables necesarias para el juego a valores vacios
  * 
  * @param game es el puntero que apunta a game, que contiene los datos de localización de objeto y jugador 
  * junto con los espacios del juego y el ultimo comando
  * @return OK si todo va bien
  */
STATUS game_create(Game *game);

/**
  * @brief Comprueba si ha habido una actualizacion en el estado de la partida
  * @author Profesores PPROG
  *
  * game_update utiliza la variable cmd del interprete de comandos para determinar que funcion debe llamar
  * en cada caso
  * @param game es el puntero que apunta a game, que contiene los datos de localización de objeto y jugador 
  * junto con los espacios del juego y el ultimo comando
  * @param cmd la variable tipo T_Command del interprete de comandos, varia segun el comando introducido por el usuario
  * @return 0 if ERROR, 1 if OK, and 5 if OK but dont print condition
  */
int game_update(Game *game, T_Command cmd, char *arg);

/**
  * @brief Destruye la partida
  * @author Profesores PPROG
  *
  * game_destroy destruye todos los espacios de la partida llamando a space_destroy para cada uno de ellos
  * @param game es el puntero que apunta a game, que contiene los datos de localización de objeto y jugador 
  * junto con los espacios del juego y el ultimo comando
  * @return OK si se destruye con exito
  */
STATUS game_destroy(Game *game);

/**
  * @brief Termina la partida
  * @author Profesores PPROG
  *
  * Devuelve FALSE cuando se llama a la funcion, significando que la partida ha terminado
  * 
  * @param game es el puntero que apunta a game, que contiene los datos de localización de objeto y jugador 
  * junto con los espacios del juego y el ultimo comando 
  * @return FALSE 
  */
BOOL game_is_over(Game *game);

/**
  * @brief Imprime la informacion de la partida
  * @author Profesores PPROG
  *
  * game_print_data imprime en la interfaz los datos acerca de la posicion actual del jugador y objeto
  * @param game es el puntero que apunta a game, que contiene los datos de localización de objeto y jugador 
  * junto con los espacios del juego y el ultimo comando 
  */
void game_print_data(Game *game);

/**
  * @brief Comprueba si existe un espacio
  * @author Profesores PPROG
  *
  * Comprueba uno a uno los espacios del juego para ver si son nulos o coinciden con la id
  * @param game es el puntero que apunta a game, que contiene los datos de localización de objeto y jugador 
  * junto con los espacios del juego y el ultimo comando  
  * @param id es el numero de identificacion del espacio
  * @return un puntero al espacio que coincide con el id, o NULL en caso de error o de que no exista.
  */
Space *game_get_space(Game *game, Id id);

/**
 * @brief Obtiene un objeto a traves de su id
 * @author Miguel Soto
 * 
 * Comprueba uno a uno los objetos del juego para ver si coinciden con la id
 * @param game es puntero un puntero a game
 * @param id el id del objeto que se quiere obtener
 * @return un puntero al objeto que coincide con el id, o NULL en caso de error o de que no exista.
 */
Object *game_get_object(Game *game, Id id);

/**
 * @brief Obtiene un player a traves de su id
 * @author Miguel Soto
 * 
 * Comprueba uno a uno los players del juego para ver si coinciden con la id
 * @param game es puntero un puntero a game
 * @param id el id del player que se quiere obtener
 * @return un puntero al player que coincide con el id, o NULL en caso de error o de que no exista.
 */
Player *game_get_player(Game *game, Id id);

/**
 * @brief Obtiene un enemy a traves de su id
 * @author Miguel Soto
 * 
 * Comprueba uno a uno los enemies del juego para ver si coinciden con la id
 * @param game es puntero un puntero a game
 * @param id el id del objeto que se quiere obtener
 * @return un puntero al enemy que coincide con el id, o NULL en caso de error o de que no exista.
 */
Enemy *game_get_enemy(Game *game, Id id);

/**
 * @brief Obtiene un link a traves de su id
 * @author Miguel Soto
 * 
 * Comprueba uno a uno los links del juego para ver si coinciden con la id
 * @param game es puntero un puntero a game
 * @param id el id del objeto que se quiere obtener
 * @return un puntero al link que coincide con el id, o NULL en caso de error o de que no exista.
 */
Link *game_get_link(Game *game, Id id);

/**
  * @brief Obtiene la posicion de un player personaje 
  * @author Miguel Soto
  *
  * Obtiene la posicion del player
  * @param game es el puntero que apunta a game
  * @param player_id es la id del player del que se quiere consultar su posicion.
  * @return la id del espacio donde se encuentra el jugador en ese momento
  */
Id game_get_player_location(Game *game, Id player_id);

/**
  * @brief Obtiene la localizacion del enemigo
  * @author Antonio Van-Oers Luis
  *
  * Obtiene la posicion del enemigo
  * @param game es el puntero que apunta a game
  * @param enemy_id es la id del enemy del que se quiere consultar su posicion.
  * @return la id del espacio donde se encuentra el enemy en ese momento
  */
Id game_get_enemy_location(Game *game, Id enemy_id);

/**
  * @brief Obtiene la localizacion del objeto
  * @author Miguel Soto
  *
  * Obtiene la posicion del objeto cuando se llama a la funcion
  * @param game es el puntero que apunta a game
  * @param obj_id es la id del objeto del que se quiere consultar su posicion.
  * @return la id del espacio donde se encuentra el objeto en ese momento
  */
Id game_get_object_location(Game *game, Id obj_id);

/**
  * @brief Obtiene el ultimo comando introducido
  * @author Profesores PPROG
  *
  * Dentro de la estructura Game, accede a la variable last_cmd para obtener el ultimo comando introducido por el usuario en la partida
  * @param game es el puntero que apunta a game, que contiene los datos de localización de objeto y jugador 
  * junto con los espacios del juego y el ultimo comando 
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


#endif
