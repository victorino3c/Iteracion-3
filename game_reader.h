/** 
 * @brief It defines the game's members loading
 * 
 * @file game_reader.h
 * @author Miguel Soto, Nicolas Victorino, Ignacio Nunez, Antonio Van-Oers
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
  * @brief Creates and initializes a game from a file
  * @author Profesores PPROG
  *
  * game_create_from_file initializes all of game's members from the filename.dat
  * @param game pointer to game
  * @param filename pointer to the file's name 
  * @return OK, if everything goes well or ERROR if something didn't
  */
STATUS game_create_from_file(Game *game, char *filename);

#endif
