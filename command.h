/**
 * @brief It implements the command interpreter interface
 *
 * @file command.h
 * @author Profesores PPROG
 * Modified by Ignacio Nunnez && Nicolas Victorino
 * @version 3.0
 * @date 11-03-2022
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

#define N_CMDT 2
#define N_CMD 10

typedef enum enum_CmdType {
  CMDS, // Abbrevation of the command 'e'
  CMDL // Name of the command 'EXIT'
  } T_CmdType;

typedef enum enum_Command {
  NO_CMD = -1,
  UNKNOWN, // No command detected
  EXIT, // Leaving the game
  NEXT, // Move next room
  BACK, // Move room at the back
  RIGHT, // Move room at the right
  LEFT, // Move room at the left
  TAKE, // Take an object
  DROP, // Drop an object
  ATTACK //Attack an enemy
  } T_Command;

/**
  * @brief Scans input of the User
  * @author Profesores PPROG
  *
  * @return 'cmd' with the command scaned
  */
T_Command command_get_user_input(char *arg);

#endif
