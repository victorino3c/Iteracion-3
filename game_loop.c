/**
 * @brief It defines the game loop to run the ant game
 *
 * @file game_loop.c
 * @author Profesores PPROG
 * Modified by Nicolas Victorino
 * @version 2.2
 * @date 11-03-2022
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include "graphic_engine.h"
#include "game.h"
#include "command.h"
#include "game_reader.h"

int game_loop_init(Game *game, Graphic_engine **gengine, char *file_name);
void game_loop_run(Game game, Graphic_engine *gengine, STATUS cmd_st);
void game_loop_cleanup(Game game, Graphic_engine *gengine);

int main(int argc, char *argv[])
{
  Game game;
  Graphic_engine *gengine;
  STATUS cmd_st = OK;

  if (argc < 2)
  {
    fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
    return 1;
  }
 
  if (!game_loop_init(&game, &gengine, argv[1]))
  {
    game_loop_run(game, gengine, cmd_st);
    game_loop_cleanup(game, gengine);
  }

  return 0;
}

int game_loop_init(Game *game, Graphic_engine **gengine, char *file_name)
{
  if (game_create_from_file(game, file_name) == ERROR)
  {
    fprintf(stderr, "Error while initializing game.\n");
    return 1;
  }

  game_set_cmd_st(game, OK);

  if ((*gengine = graphic_engine_create()) == NULL)
  {
    fprintf(stderr, "Error while initializing graphic engine.\n");
    game_destroy(game);
    return 1;
  }

  return 0;
}

void game_loop_run(Game game, Graphic_engine *gengine, STATUS cmd_st)
{
  char arg[10];
  T_Command command = NO_CMD;

  while ((command != EXIT) && !game_is_over(&game))
  {
    graphic_engine_paint_game(gengine, &game);
    command = command_get_user_input(&arg[0]);
    cmd_st = game_update(&game, command, arg);

    game_set_cmd_st(&game, cmd_st);
  }
}

void game_loop_cleanup(Game game, Graphic_engine *gengine)
{
  game_destroy(&game);
  graphic_engine_destroy(gengine);
}
