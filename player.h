/** 
 * @brief Implementa la interfaz del jugador.
 * 
 * @file player.h
 * @author Antonio Van-Oers
 * @version 1.2
 * @date 12-02-2021
 * @copyright GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"
#include "object.h"

#define Player_Name_lenght 60
#define MAX_PLAYERS 1

typedef struct _Player Player;


/**
 * @brief Crea un jugador nuevo.
 * @author Antonio Van-Oers 
 *
 * player_create reserva memoria para un nuevo Player e inicializa sus campos.
 * @param id el numero de identificacion del nuevo jugador a crear.
 * @return un nuevo jugador (tipo Player) inicializado, o NULL si hubo algun error.
 */
Player *player_create(Id id);

/**
 * @brief Destruye un jugador.
 * @author Antonio Van-Oers 
 * 
 * player_destroy libera la memoria previamente reservada de un jugador.
 * @param player un puntero a Player que necesita ser destruido.
 * @return OK, si ha funcionado correctamente o ERROR, si hubo algun error.
 */
STATUS player_destroy(Player *player);

/**
 * @brief Obtiene el id de un jugador.
 * @author Antonio Van-Oers
 * 
 * player_get_id devuelve el id de un jugador(player).
 * @param player un puntero a Player.
 * @return el id del jugador, o NULL si hubo algun error.
 */
Id player_get_id(Player *player);

/**
 * @brief Comprueba si el id recibido es el de un player
 * @author Miguel Soto
 * 
 * @param id el id que se quiere comprobar
 * @return OK, si es correcto o ERROR si no es correcto o hubo algun error.
 */
STATUS player_test_id(Id id);

/**
 * @brief Obtiene el nombre de un jugador.
 * @author Antonio Van-Oers
 * 
 * player_get_name devuelve el nombre de un jugador (player).
 * @param player un puntero a Player.
 * @return un string con el nombre del jugador player, o NULL si hubo algun error.
 */
const char *player_get_name(Player *player);

/**
 * @brief Obtiene el nombre de un jugador.
 * @author Antonio Van-Oers
 * 
 * player_get_location obtiene la localizacion de un jugador (player).
 * @param player un puntero a Player.
 * @param location es la identificacion del espacio en el que esta el jugador.
 * @return player->location, la id de la localizacion de un jugador (player).
 */
Id player_get_location(Player *player);

/**
 * @brief Obtiene el nombre de un objeto.
 * @author Antonio Van-Oers
 * 
 * player_get_object obtiene la id de un object perteneciente al jugador.
 * @param player un puntero a Player.
 * @return player->object, la id de la localizacion de un objeto o NULL si hay un error.
 */
Object *player_get_object(Player *player);

/**
 * @brief Obtiene la salud de un jugador.
 * @author Antonio Van-Oers
 * 
 * player_get_health obtiene la salud de un jugador (player).
 * @param player un puntero a player.
 * @return player->health, obtiene la salud restante de un jugador (player)
 * y -1 en caso de error.
 */
int player_get_health(Player *player);

/**
 * @brief Establece la salud de un jugador.
 * @author Antonio Van-Oers
 * 
 * player_set_health establece la salud de un jugador (player).
 * @param player un puntero a player.
 * @return player->health, establece la salud restante de un jugador (player)
 * y -1 en caso de error.
 */
STATUS player_set_health(Player *player, int health);

/**
 * @brief Establece el objeto de un jugador.
 * @author Antonio Van-Oers
 * 
 * player_set_object establece un objeto introducido como perteneciente al jugador
 * @param player un puntero a Player.
 * @param object es la identificacion del objeto del jugador.
 * @return OK, si ha funcionado correctamente o ERROR, si hubo algun error.
 */
STATUS player_set_object(Player *player, Object *object);
/**
 * @brief Establece el nombre de un jugador.
 * @author Antonio Van-Oers
 * 
 * player_set_location establece la localizacion de un jugador (player).
 * @param player un puntero a Player.
 * @param location es la identificacion del espacio en el que esta el jugador.
 * @return OK, si ha funcionado correctamente o ERROR, si hubo algun error.
 */
STATUS player_set_location(Player *player, Id location);

/**
 * @brief Establece un nombre a un jugador.
 * @author Antonio Van-Oers
 * 
 * obj_set_name establece el nombre (name) de un jugador (player).
 * @param player un puntero a Player.
 * @param name un string con el nombre que se va a establecer al jugador.
 * @return OK, si ha funcionado correctamente o ERROR, si hubo algun error.
 */
STATUS player_set_name(Player *player, char *name);

/**
 * @brief Imprime la informacion de un jugador.
 * @author Antonio Van-Oers
 * 
 * obj_print muestra el id y el nombre de un jugador (player).
 * @param player un puntero a Player.
 * @return OK, si ha funcionado correctamente o ERROR, si hubo algun error.
 */
STATUS player_print(Player *player);

#endif

