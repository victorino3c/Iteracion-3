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
void game_loop_run(Game *game, Graphic_engine *gengine);
void game_loop_run_from_file(Game *game, Graphic_engine *gengine, char *f);
void game_loop_cleanup(Game *game, Graphic_engine *gengine);

/**
  * @brief Programa principal del game_loop
  * @author Profesores PPROG
  *
  * Comprueba si el valor de argc y argv son correctos para decidir si inciar el juego y activar el cleanup
  * @param argc un entero
  * @param argv una cadena de caracteres
  * @return 0 si se ejecuta el juego con exito y 1 si no se ha usado el game_data_file correcto
  */
int main(int argc, char *argv[])
{
  Game *game = game_alloc2();
  Graphic_engine *gengine;

  if (argc < 2)
  {
    fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
    return 1;
  } else if (argc > 2) { /*Loads game from a file*/

      if (!game_loop_init(game, &gengine, argv[1]))
      {
        game_loop_run_from_file(game, gengine, argv[2]);
        game_loop_cleanup(game, gengine);
      }

  } else if (argc == 2) { /*Loads game and waits for player interaction*/
 
      if (!game_loop_init(game, &gengine, argv[1]))
      {
        game_loop_run(game, gengine);
        game_loop_cleanup(game, gengine);
      }
  }

  return 0;
}

/**
  * @brief Inicializa el juego
  * @author Profesores PPROG
  *
  * Comprueba si el valor de argc y argv son correctos para decidir si inciar el juego y activar el cleanup
  * @param game es el puntero que apunta a la estructura tipo Game que contiene los datos de localización de objeto y jugador 
  * junto con los espacios del juego y el ultimo comando
  * @param gengine es un doble puntero para acceder al motor grafico
  * @param file_name es un puntero al nombre del fichero para acceder a el tras haber ejecutado el juego e imprimir cualquier error que se haya dado
  * @return 0 si se inicializa el juego con exito y 1 si no se ha producido un error
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
  * @brief Ejecuta el juego
  * @author Profesores PPROG
  *
  * Comprueba en bucle si no se ha introducido exit ni el juego se ha acabado para seguir ejecutando el juego
  * @param game es el puntero que apunta a la estructura tipo Game que contiene los datos de localización de objeto y jugador 
  * junto con los espacios del juego y el ultimo comando
  * @param gengine es un puntero que apunta al motor grafico
  */
void game_loop_run(Game *game, Graphic_engine *gengine)
{
  T_Command command = NO_CMD;
  char arg[MAX_ARG];
  int st = 5;

  while ((command != EXIT) && !game_is_over(game))
  {
    graphic_engine_paint_game(gengine, game, st);
    command = command_get_user_input(arg);
    st = game_update(game, command, arg);
  }
}

/**
  * @brief Executes the game from a file
  * @author Nicolas Victorino
  *
  * Reads a file in a loop and executes the commands that are on the file
  * @param game is a gamem type pointer that points to the structure that contains all the player and object location data along 
  * with the game spaces, the last command, the enemies and the links between said spaces
  * @param gengine es un puntero que apunta al motor grafico
  */
void game_loop_run_from_file(Game *game, Graphic_engine *gengine, char *file)
{
  T_Command command = NO_CMD;
  char arg[MAX_ARG], input[MAX_ARG];
  int st = 5;
  FILE *f;
  f = fopen(file, "r");

  while ((command != EXIT) && !game_is_over(game) && fgets(input, MAX_ARG, f) > 0)
  {
    graphic_engine_paint_game(gengine, game, st);
    command = command_get_file_input(input, arg);
    st = game_update(game, command, arg);
  }
  fclose(f);
}


/**
  * @brief Termina y limpia el juego
  * @author Profesores PPROG
  *
  * Tras terminar con la partida actual, destruye el juego y el motor grafico para limpiar estos procesos
  * @param game es el puntero que apunta a la estructura tipo Game que contiene los datos de localización de objeto y jugador 
  * junto con los espacios del juego y el ultimo comando
  * @param gengine es un puntero que apunta al motor grafico
  */
void game_loop_cleanup(Game *game, Graphic_engine *gengine)
{
  game_destroy(game);
  graphic_engine_destroy(gengine);
}
