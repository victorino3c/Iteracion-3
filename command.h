/**
 * @brief It implements the command interpreter interface
 *
 * @file command.h
 * @author Profesores PPROG
 * @version 2.0
 * @date 29-11-2021
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "types.h"

#define N_CMDT 2
#define N_CMD 10

typedef enum enum_CmdType {
  CMDS,
  CMDL} T_CmdType;

/** 
* @brief La enumeracion T_Command 
*
* Establece un valor inicial para NO_CMD y las posibles interpretaciones de lo que introduce el usuario
*/
typedef enum enum_Command {
  NO_CMD = -1,
  UNKNOWN,
  EXIT,
  DOWN,
  LEFT,
  UP,
  RIGHT,
  TAKE,
  DROP,
  ATTACK} T_Command;

/**
  * @brief Obtiene el input del usuario 
  * @author Profesores PPROG
  *
  * Escanea el cmd en busca de caracteres clave que introduzca el usuario para interpretar y clasificar la info
  * 
  * @return cmd, una variable tipo T_Command que varia segun lo introducido por el usuario
  */
T_Command command_get_user_input();

#endif
