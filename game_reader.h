/** 
 * @brief It defines the game's space loading
 * 
 * @file game_reader.h
 * @author Miguel Soto
 * @version 1.1
 * @date 12-02-2022
 * @copyright GNU Public License
 */

#ifndef GAME_READER
#define GAME_READER

#include "command.h"
#include "space.h"
#include "types.h"
#include "game.h"

typedef enum
{
  IS_SPACE = FD_ID_SPACE,
  IS_PLAYER = FD_ID_PLAYER,
  IS_OBJECT = FD_ID_OBJ,
  IS_ENEMY = FD_ID_ENEMY
} GAME_IS_ELEMENT;

/**
  * @brief Crea e inicializa una partida desde el fichero
  * @author Profesores PPROG
  *
  * game_create_from_file inicializa los campos necesarios del juego leidos desde el filename.dat
  * @param game es el puntero que apunta a game
  * @param filename es el puntero que apunta al nombre del fichero 
  * @return OK, si todo va bien o ERROR si ha habido algun fallo
  */
STATUS game_create_from_file(Game *game, char *filename);

#endif