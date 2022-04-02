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
#define N_CMD 12

typedef enum enum_CmdType {
  CMDS,
  CMDL} T_CmdType;

/** 
* @brief La enumeracion T_Command 
*
* Intitializes No_CMD to -1 and includes every possible interpretation for the input 
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
  ATTACK,
  MOVE,
  INSPECT,} T_Command;

/**
  * @brief Obtiene el input del usuario 
  * @author Profesores PPROG
  *
  * It scans the cmd searching for key words introduced by the user 
  * in order to interpret and clasify the info
  * 
  * @return cmd, a T_Command type variable that changes its value depending on the input
  */
T_Command command_get_user_input();

/**
  * @brief Obtiene el input del usuario 
  * @author Nicolas Victorino
  *
  * It scans the cmd searching for key words introduced by the file 
  * in order to interpret and clasify the info
  * 
  * @return cmd, a T_Command type variable that changes its value depending on the input
  */
T_Command command_get_file_input(char *command, char *arg);


#endif
