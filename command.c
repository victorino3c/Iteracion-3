/** 
 * @brief It implements the command interpreter
 * 
 * escanea el cmd en busca de palabras clave que introduzca el usuario para interpretar y clasificar la info:
 * desconocida, si no introduce nada o cualquier otro caracter; exit, si introduce "e";
 * next, si introduce "n" y back si introduce "b";
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
[N_CMDT] = {{"", "No command"},    /*!< Al empezar, no hay comandos */
			{"", "Unknown"},             /*!< Si no recibe nada o algun caracter desconocido, se interpreta como desconocido */
			{"e", "Exit"},               /*!< Si recibe una e, se interpreta como Exit*/
			{"s", "Down"},               /*!< Si recibe una s, se interpreta como Down/Next */
      {"a", "Left"},               /*!< Si recibe una a, se interpreta como Left */
			{"w", "Up"},               /*!< Si recibe una w, se interpreta como Up/Back */
      {"d", "Right"},              /*!< Si recibe una d, se interpreta como Right */
      {"c", "Take"},               /*!< Si recibe una z, se interpreta como Take */
      {"v", "Drop"},               /*!< Si recibe una x, se interpreta como Drop */
      {"q", "Attack"}};            /*!< Si recibe una q, se interpreta como Attack */

/**Escanea el cmd en busca de caracteres clave que introduzca el usuario 
  * para interpretar y clasificar la informacion
  */
T_Command command_get_user_input(char *arg)
{
  T_Command cmd = NO_CMD; 
  char input[CMD_LENGHT] = "";
  int i = UNKNOWN - NO_CMD + 1;
  
  // Error control
  if (!arg)
  {
    return NO_CMD;
  }
  
  if (scanf("%s", input) > 0)
  {
    cmd = UNKNOWN;
    while (cmd == UNKNOWN && i < N_CMD)     /*!< Condicion para seguir leyendo el cmd*/
    {
      if (!strcasecmp(input, cmd_to_str[i][CMDS]) || !strcasecmp(input, cmd_to_str[i][CMDL]))
      {
        cmd = i + NO_CMD;                   /*!< Si detecta diferencias entre CMDS y CMDL con el input, modificar cmd */
        if (cmd == TAKE || cmd == DROP )
        {
          if (scanf("%s", arg) < 0)
          {
            fprintf(stdout, "Comando incorrecto. Los comandos TAKE DROP necesitan un argumento mas con la id.\n");
          }
        }
        
      }
      else                                  /*!< En caso contrario seguir avanzando en la lectura */
      {
        i++;                                 
      }
    }
  }
  
  return cmd;
}
