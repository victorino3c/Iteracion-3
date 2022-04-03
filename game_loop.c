/**
 * @brief It defines the game loop
 *
 * @file game_loop.c
 * @author Miguel Soto, Nicolas Victorino, Antonio Van-Oers and Ignacio Nunez
 * @version 2.0
 * @date 03-04-2022
 * @copyright GNU Public License
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "graphic_engine.h"
#include "game.h"
#include "command.h"
#include "game_reader.h"

int game_loop_init(Game *game, Graphic_engine **gengine, char *file_name);
void game_loop_run(Game *game, Graphic_engine *gengine, char *flog_name, char *fcmd_name);
void game_loop_cleanup(Game *game, Graphic_engine *gengine);
void print_syntaxinfo(char *argv[]);

/**
 * @brief Programa principal del game_loop
 * @author Miguel Soto Y Nicolas Victorino
 *
 * Comprueba si el valor de argc y argv son correctos para decidir si inciar el juego y activar el cleanup
 * @param argc un entero
 * @param argv una cadena de caracteres
 * @return 0 si se ejecuta el juego con exito y 1 si no se ha usado el game_data_file correcto
 */
int main(int argc, char *argv[])
{
  Game *game = NULL;
  Graphic_engine *gengine;
  /* Used to able to save commands in log */
  char *wlog_name = NULL, *cmdf_name = NULL;
  int i; /* Used in loops */

  /* Alloc game's struct in memory */
  game = game_alloc2();
  if (!game)
  {
    fprintf(stderr, "ERROR allocating game's memory\n");
    return 1;
  }

  /* Check arguments in execution command */
  if (argc < 2) /* Incorrect syntax */
  {
    print_syntaxinfo(argv);
    return 1;
  }
  else if (argc == 2)
  {
    /*Loads game and waits for player interaction*/
    if (!game_loop_init(game, &gengine, argv[1]))
    {
      game_loop_run(game, gengine, NULL, NULL);
      game_loop_cleanup(game, gengine);
    }
  }
  else if (argc > 2)
  {
    /*Loads game from a file*/
    wlog_name = NULL;
    cmdf_name = NULL;
    if (argc == 3)
    {
      fprintf(stderr, "\nWrong syntax. Argument %s unidentified.\n", argv[2]);
      print_syntaxinfo(argv);
      return 1;
    }
    
    for (i = 2; i < (argc - 1); i++)
    {
      printf("argv[%d] = %s\n", i, argv[i]);
      if (strcmp(argv[i], "-l\0") == 0)
      {
        i++;
        wlog_name = argv[(i)];
      }
      else if (strcmp(argv[i], "<\0") == 0)
      {
        i++;
        cmdf_name = argv[i];
      }
      else
      {
        fprintf(stderr, "\nWrong syntax. Argument %s unidentified.\n", argv[i]);
        print_syntaxinfo(argv);
        return 1;
      }
    }

    if (!game_loop_init(game, &gengine, argv[1]))
    {
      game_loop_run(game, gengine, wlog_name, cmdf_name);
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
 * @author Miguel Soto and Nicolas Victorino
 *
 * Comprueba en bucle si no se ha introducido exit ni el juego se ha acabado para seguir ejecutando el juego
 * @param game es el puntero que apunta a la estructura tipo Game que contiene los datos de localización de objeto y jugador
 * junto con los espacios del juego y el ultimo comando
 * @param gengine es un puntero que apunta al motor grafico
 */
void game_loop_run(Game *game, Graphic_engine *gengine, char *flog_name, char *fcmd_name)
{
  T_Command command = NO_CMD;
  char arg[MAX_ARG], input[MAX_ARG];
  int st = 5, wlog = 0, rcmd = 0;
  FILE *flog = NULL, *fcmd = NULL;
  T_Command last_cmd;
  extern char *cmd_to_str[N_CMD][N_CMDT];

  if (flog_name)
  {
    wlog = 1;
    flog = fopen(flog_name, "w");
    if (!flog)
    {
      fprintf(stderr, "There was an error opening log_file.\n");
      return;
    }
  }
  if (fcmd_name)
  {
    rcmd = 1;
    fcmd = fopen(fcmd_name, "r");
    if (!fcmd)
    {
      fprintf(stderr, "There was an error opening cmd_file.\n");
      return;
    }
  }

  for (; (command != EXIT) && !game_is_over(game);)
  {
    graphic_engine_paint_game(gengine, game, st);

    if (rcmd == 1)
    {
      if (fgets(input, MAX_ARG, fcmd))
      {
        command = command_get_file_input(input, arg);
      }
      else
      {
        // Si hay error al inicio de ejecutarse es aqui
        command = EXIT;
      }
    }
    else
    {
      command = command_get_user_input(arg);
    }

    st = game_update(game, command, arg);

    if (wlog == 1)
    {
      last_cmd = game_get_last_command(game);
      if (st == 0)
      {
        fprintf(flog, " %s (%s) %s: ERROR\n", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS], arg);
      }
      else if (st == 1)
      {
        fprintf(flog, " %s (%s) %s: OK\n", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS], arg);
      }
      else
      {
        fprintf(flog, " %s (%s)\n", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
      }
    }
  }

  fprintf(stdout, "\n");

  if (flog)
  {
    fclose(flog);
    flog = NULL;
  }
  if (fcmd)
  {
    fclose(fcmd);
    fcmd = NULL;
  }

  return;
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

/**
 * @brief Prints syntax info when running programme.
 * @author Miguel Soto
 *
 * @param argv Arguments from the command used to execute programme.
 */
void print_syntaxinfo(char *argv[])
{
  fprintf(stderr, "\nUse: %s <game_data_file>.\n", argv[0]);
  fprintf(stderr, "If you want to save inserted commands use the flag \"-l\" with the file name\n");
  fprintf(stderr, "Also, if you want to execute commands from a file use \"<\" with the file name\n \n");
  fprintf(stderr, "\tGlobal syntax: %s <game_data_file> [-l <log_file>] [< <command_file>]\n", argv[0]);
  fprintf(stderr, "\tArguments between [ ] are optional.\n \n");
}
