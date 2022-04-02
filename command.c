/** 
 * @brief It implements the command interpreter
 * 
 * It scans the cmd searching for key words introduced by the user in order to interpret and clasify the commands
 * as unknown, exit, up, down, left, right attack, take, drop or move depending on what string is typed.
 * 
 * @file command.c
 * @author Profesores PPROG
 * @version 2.0 
 * @date 29-11-2021 
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "command.h"

#define CMD_LENGHT 30

char *cmd_to_str[N_CMD]
[N_CMDT] = {{"", "No command"},    /*!< At the beginning, there is no commands */
      {"", "Unknown"},             /*!< If an empty or unknown string is received, it is interpreted as Unknown */
      {"e", "Exit"},               /*!< If an e is received, it is interpreted as Exit */
      {"s", "Down"},               /*!< If a s is received, it is interpreted as Down/Next */
      {"a", "Left"},               /*!< If an a is received, it is interpreted as Left */
      {"w", "Up"},                 /*!<  If a w is received, it is interpreted as Up/Back */
      {"d", "Right"},              /*!< If a d is received, it is interpreted as Right */
      {"c", "Take"},               /*!<  If a c is received, it is interpreted as Take */
      {"v", "Drop"},               /*!<  If a v is received, it is interpreted as Drop */
      {"q", "Attack"},             /*!<  If a s is received, it is interpreted as Attack */
      {"m", "Move"},               /*!<  If a m is received, it is interpreted as move */
      {"i", "Inspect"},            /*!<  If an i is received, it is interpreted as inspect */
      };           
/**It scans the cmd searching for key words introduced by the user 
  *in order to interpret and clasify the info
  */
T_Command command_get_user_input(char *arg)
{
  T_Command cmd = NO_CMD; 
  char input[CMD_LENGHT] = "";
  int i = UNKNOWN - NO_CMD + 1;
  
  /* Error control*/
  if (!arg)
  {
    return NO_CMD;
  }
  
  if (scanf("%s", input) > 0)
  {
    cmd = UNKNOWN;
    while (cmd == UNKNOWN && i < N_CMD)     /*!< Condition to continue reading */
    {
      if (!strcasecmp(input, cmd_to_str[i][CMDS]) || !strcasecmp(input, cmd_to_str[i][CMDL]))
      {
        cmd = i + NO_CMD;                   /*!< If any differences are detected between CMDS, CMDL and the input, cmd is modified */
        if (cmd == TAKE || cmd == DROP || cmd == MOVE || cmd == INSPECT)
        {
          if (scanf("%s", arg) < 0)
          {
            fprintf(stdout, "Comando incorrecto. Los comandos TAKE DROP INSPECT MOVE necesitan un argumento mas como el nombre del objeto .\n");
          }
        }
        
      }
      else                                  /*!< In any other case, continue reading >! */
      {
        i++;                                 
      }
    }
  }
  
  return cmd;
}

T_Command command_get_file_input(char *command, char *arg) //Funciona bien, pero necesita un espacio al final del segundo argumento en el file desde el que se carga
{
  T_Command cmd = NO_CMD; 
  char input[CMD_LENGHT] = "";
  int i = UNKNOWN - NO_CMD + 1, j = 0, z = 0;
  
  /* Error control*/
  if (!arg)
  {
    return NO_CMD;
  }
  
  if (command != NULL)
  {
    cmd = UNKNOWN;
    for (j = 0; command[j] != ' '; j++) { /*Reads first part of command*/
      input[j] = command[j];
    }
    input[j] = '\0';
    while (cmd == UNKNOWN && i < N_CMD)     /*!< Condition to continue reading */
    {
      if (!strcasecmp(input, cmd_to_str[i][CMDS]) || !strcasecmp(input, cmd_to_str[i][CMDL]))
      {
        cmd = i + NO_CMD;                   /*!< If any differences are detected between CMDS, CMDL and the input, cmd is modified */
        if (cmd == TAKE || cmd == DROP || cmd == MOVE || cmd == INSPECT)
        {
          for (j++, z = 0; command[j] != ' '; j++, z++) { /*Reads the second argument of command and saves it in arg*/ //Funciona si hay un espacio al final del argumento
            arg[z] = command[j];
          } 
          arg[z] = '\0';
          if (arg == NULL)
          {
            fprintf(stdout, "Comando incorrecto. Los comandos TAKE DROP INSPECT MOVE necesitan un argumento mas como el nombre del objeto .\n");
          }
        }
        
      }
      else                                  /*!< In any other case, continue reading >! */
      {
        i++;                                 
      }
    }
  }
  
  return cmd;
