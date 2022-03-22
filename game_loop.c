/**
 * @brief It defines the game loop
 *
 * @file game_loop.c
 * @author Profesores PPROG
 * @version 2.0
 * @date 30-11-2020
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include "graphic_engine.h"
#include "game.h"
#include "command.h"
#include "game_reader.h"


int game_loop_init(Game *game, Graphic_engine **gengine, char *file_name);
void game_loop_run(Game game, Graphic_engine *gengine);
void game_loop_cleanup(Game game, Graphic_engine *gengine);

/**
  * @brief Main game_loop program
  * @author Profesores PPROG
  *
  * Checks whether argc and argv values are the expected in order 
  * to initialize the game and/or the cleanup
  * @param argc an integer
  * @param argv a string
  * @return 0 if the game is succesfully initialized and 1 
  * if game_data_file was not the expected one
  */
int main(int argc, char *argv[])
{
  Game game;
  Graphic_engine *gengine;

  if (argc < 2)
  {
    fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
    return 1;
  }
 
  if (!game_loop_init(&game, &gengine, argv[1]))
  {
    game_loop_run(game, gengine);
    game_loop_cleanup(game, gengine);
  }

  return 0;
}

/**
  * @brief Initializes the game and all its members 
  * @author Profesores PPROG
  *
  * @param game pointer to game that contains every needed member 
  * for the main execution of the programme.
  * @param gengine double pointer to access the graphic engine
  * @param file_name pointer to the file's name from which the game 
  * is created
  * @return 0 if the game is succesfully initialized and 1 if anything 
  * goes wrong
  */
int game_loop_init(Game *game, Graphic_engine **gengine, char *file_name)
{  
  if (game_create_from_file(game, file_name) == ERROR)
  {
    fprintf(stderr, "Error while initializing game.\n");
    return 1;
  }

  if ((*gengine = graphic_engine_create()) == NULL)
  {
    fprintf(stderr, "Error while initializing graphic engine.\n");
    game_destroy(game);
    return 1;
  }

  return 0;
}

/**
  * @brief Keeps the game running
  * @author Profesores PPROG
  *
  * Loop that is constantly checking whether the exit 
  * command is introduced or game_is_over is TRUE so 
  * that the game keeps running or not 
  * @param game pointer to game that contains every needed member 
  * for the main execution of the programme.
  * @param gengine pointer to the graphic engine
  */
void game_loop_run(Game game, Graphic_engine *gengine)
{
  T_Command command = NO_CMD;
  char arg[MAX_ARG];
  int st = 5;

  while ((command != EXIT) && !game_is_over(&game))
  {
    graphic_engine_paint_game(gengine, &game, st);
    command = command_get_user_input(arg);
    st = game_update(&game, command, arg);
  }
}


/**
  * @brief Ends and destroys all of the game's components 
  * @author Profesores PPROG
  *
  * After ending the current game, it destroys its components
  * by calling the suitable functions which also will free all
  * allocated memory.
  * @param game pointer to game that contains every needed member 
  * for the main execution of the programme.
  * @param gengine pointer to the graphic engine
  */
void game_loop_cleanup(Game game, Graphic_engine *gengine)
{
  game_destroy(&game);
  graphic_engine_destroy(gengine);
}
