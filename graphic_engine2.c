/**
 * @brief It defines a textual graphic engine
 *
 * @file graphic_engine.c
 * @author Profesores PPROG
 * @version 2.0
 * @date 29-11-2021
 * @copyright GNU Public License
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "graphic_engine.h"
#include "libscreen.h"
#include "command.h"
#include "space.h"
#include "types.h"
#include "enemy.h"
#include "player.h"
#include "object.h"

#define ROWS 37
#define COLUMNS 96

/**
 * @brief Motor grafico
 *
 * Esta estructura contiene todos los punteros a los recursos necesarios que gestiona
 * el motor grafico como el mapa, help o feedback
 */
struct _Graphic_engine
{
  Area *map, *descript, *banner, *help, *feedback;   /*!< mapa de juego, descript, icono, menu de ayuda, y feedback para los comandos introducidos */
};

/**
  * graphic_engine_create inicializa la pantalla de juego con las dimensiones adecuadas
  */
Graphic_engine *graphic_engine_create()
{
  static Graphic_engine *ge = NULL;

  if (ge)
    return ge;

  screen_init(ROWS, COLUMNS);
  ge = (Graphic_engine *)malloc(sizeof(Graphic_engine));
  if (ge == NULL)
    return NULL;

  ge->map = screen_area_init(1, 1, 55, 23);
  ge->descript = screen_area_init(57, 1, 35, 23);
  ge->banner = screen_area_init(42, 26, 23, 1);
  ge->help = screen_area_init(1, 28, 90, 3);
  ge->feedback = screen_area_init(1, 32, 90, 3);

  return ge;
}

/**
  * graphic_engine_destroy, llamando a las funciones de screen_area_destroy, 
  * destruye mapa, banner, descript, help y feedback 
  * Ademas libera la memoria que se habia reservado para ge
  */
void graphic_engine_destroy(Graphic_engine *ge)
{
  if (!ge)
    return;

  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);

  screen_destroy();
  free(ge);
}

/**
  * El motor grafico dibuja en la inerfaz los componentes del juego para que se visualicen
  * en la posicion correcta en la pantalla
  */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game, int st)
{
  /*Declaracion de variables a utilizar*/
  Id id_act = NO_ID, id_up = NO_ID, id_down = NO_ID, id_left= NO_ID, id_right= NO_ID;
  Id obj_loc[MAX_OBJS] = {NO_ID}, player_loc = NO_ID, en_loc = NO_ID, obj_id[MAX_OBJS]= {NO_ID};
  Object *player_obj = NULL;
  int en_health = 0, player_health = 0;
  Space *space_act = NULL;
  char obj = '\0';
  char str[255];
  T_Command last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  int i;
  char **gdesc;


  /*Asignacion de los valores correspondientes a las variables*/
  player_loc = game_get_player_location(game, 21);
  id_act = player_loc;
  en_loc = enemy_get_location(game->enemy[MAX_PLAYERS-1]); 
  player_obj = player_get_object(game->player[MAX_PLAYERS-1]);
  player_health = player_get_health(game->player[MAX_PLAYERS-1]); 
  en_health = enemy_get_health(game->enemy[MAX_PLAYERS-1]);

  for(i=0;i<MAX_OBJS;i++)
  { 
    /* Control de errores */  
    if (game->object[i]==NULL)
    {
      break;
    }
    obj_id[i] = obj_get_id(game->object[i]);
    obj_loc[i] = obj_get_location(game->object[i]);
  }

  /* Paint the in the map area */
  screen_area_clear(ge->map);
  
  if (id_act != NO_ID)
  {
    space_act = game_get_space(game, id_act);
    id_up = space_get_north(space_act);
    id_down = space_get_south(space_act);
    id_left = space_get_west(space_act );
    id_right = space_get_east(space_act);

    /* ESPACIO ARRIBA */
    if (id_up != NO_ID)
    {
      for(i=0;i<MAX_OBJS;i++)
      { 
        /*Comprobar si el objeto se encuentra en el espacio*/
        if (space_has_object(game_get_space(game, id_up), obj_id[i]) == FALSE)
        {         
          obj = ' ';
        }
        else
        {
          obj = '*';
          break;
        }
      }

      
      sprintf(str, "  |               %2d|", (int)id_up);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |                  |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |        %c        |", obj);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |                 |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "        ^");
      screen_area_puts(ge->map, str);
    }

    /* ESPACIO ACTUAL */

    if (id_act != NO_ID)
    {
      
      for(i=0;i<MAX_OBJS;i++)
      {   
        /*Comprobar si el objeto se encuentra en el espacio*/           
        if (space_has_object(game_get_space(game, id_act), obj_id[i]) == FALSE)
        {         
          obj = ' ';
        }
        else
        {
          obj = '*';
          break;
        }
      }

      /*Si no hay espacios a derecha o izquierda*/
      if(id_left==NO_ID && id_right==NO_ID)  
      {
          sprintf(str, "  +-----------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "  |                 |");
        /*\\(\")/ CODIFICACION HORMIGA */
        if (id_act < 100)
        {
          sprintf(str, "  | gpp0^        %2d |", (int)id_act);
          screen_area_puts(ge->map, str);
        }
        else
        {
          sprintf(str, "  | gpp0^        %2d|", (int)id_act);
          screen_area_puts(ge->map, str);
        }
        
        sprintf(str, "  |                 |");
        screen_area_puts(ge->map, str);
        gdesc = space_get_gdesc(game_get_space(game, id_act));
        
        for (i = 0; i < TAM_GDESC_Y; i++)
        {
          sprintf(str, "  |    %s    |", gdesc[i]);
          screen_area_puts(ge->map, str);
        }
        
        sprintf(str, "  |                 |");
        screen_area_puts(ge->map, str);

        if (id_act < 100)
        {
          sprintf(str, "  | gpp0^        %2d |", (int)id_act);
          screen_area_puts(ge->map, str);
        }
        else
        {
          sprintf(str, "  | gpp0^        %2d|", (int)id_act);
          screen_area_puts(ge->map, str);
        }
        
        sprintf(str, "  |        %c        |", obj);
        screen_area_puts(ge->map, str);
        sprintf(str, "  |                 |");
        screen_area_puts(ge->map, str);
        sprintf(str, "  +-----------------+");
        screen_area_puts(ge->map, str);
      } 
      
      /*Si  hay espacios a derecha y no a izquierda*/
      if (id_right != NO_ID && id_left == NO_ID)
      {  
        sprintf(str, "  +-----------------+   ------------------|");
        screen_area_puts(ge->map, str);
        sprintf(str, "  |                 |                     |");
        /*\\(\")/ CODIFICACION HORMIGA */
        sprintf(str, "  | gpp0^                 %c      %2d   |", (int)id_act);
        screen_area_puts(ge->map, str);
        sprintf(str, "  |                 |");
        screen_area_puts(ge->map, str);
        /*gdesc = space_get_gdesc(game_get_space(game, id_act)); */
        /*
        for (i = 0; i < TAM_GDESC_Y; i++)
        {
          sprintf(str, "  |%s|", gdesc[i]);
          screen_area_puts(ge->map, str);
        }
        */
        sprintf(str, "  |                 |");
        screen_area_puts(ge->map, str);
        sprintf(str, "  |        %c       |", obj);
        screen_area_puts(ge->map, str);
        sprintf(str, "  |                 |");
        screen_area_puts(ge->map, str);
        sprintf(str, "  +-----------------+>>");
        screen_area_puts(ge->map, str);  
      }
      
      /*Si hay espacios a derecha e izquierda*/
      if (id_left != NO_ID && id_right != NO_ID)
      {
        sprintf(str, "  +-----------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "  |                 |");
        /*\\(\")/ CODIFICACION HORMIGA */
        sprintf(str, "  | gpp0^        %2d|", (int)id_act);
        screen_area_puts(ge->map, str);
        sprintf(str, "  |                 |");
        screen_area_puts(ge->map, str);
        /*gdesc = space_get_gdesc(game_get_space(game, id_act)); */
        /*
        for (i = 0; i < TAM_GDESC_Y; i++)
        {
          sprintf(str, "  |%s|", gdesc[i]);
          screen_area_puts(ge->map, str);
        }
        */
        sprintf(str, "  |                 |");
        screen_area_puts(ge->map, str);
        sprintf(str, "  |        %c       |", obj);
        screen_area_puts(ge->map, str);
        sprintf(str, "  |                 |");
        screen_area_puts(ge->map, str);
        sprintf(str, "  <<+---------------+>>");
        screen_area_puts(ge->map, str);
      }

      /*Si no hay espacios a derecha y si a izquierda*/
      if (id_right != NO_ID && id_left == NO_ID)
      {  
          sprintf(str, "  +-----------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "  |                 |");
        /*\\(\")/ CODIFICACION HORMIGA */
        sprintf(str, "  | gpp0^        %2d|", (int)id_act);
        screen_area_puts(ge->map, str);
        sprintf(str, "  |                 |");
        screen_area_puts(ge->map, str);
        /*gdesc = space_get_gdesc(game_get_space(game, id_act)); */
        /*
        for (i = 0; i < TAM_GDESC_Y; i++)
        {
          sprintf(str, "  |%s|", gdesc[i]);
          screen_area_puts(ge->map, str);
        }
        */
        sprintf(str, "  |                 |");
        screen_area_puts(ge->map, str);
        sprintf(str, "  |        %c       |", obj);
        screen_area_puts(ge->map, str);
        sprintf(str, "  |                 |");
        screen_area_puts(ge->map, str);
        sprintf(str, "<<+-----------------+");
        screen_area_puts(ge->map, str);  
      }
          
    }

    /* ESPACIO ABAJO*/
    if (id_down != NO_ID)
    {
      for(i=0;i<MAX_OBJS;i++)
      {   
        /*Comprobar si el objeto se encuentra en el espacio*/           
        if (space_has_object(game_get_space(game, id_down), obj_id[i]) == FALSE)
        {         
          obj = ' ';
        }
        else
        {
          obj = '*';
          break;
        }
      }
    
      sprintf(str, "        v");
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |                 |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |              %2d|", (int)id_down);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |        %c        |", obj);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |                 |");
      screen_area_puts(ge->map, str);
    }

  /* Para los espacios de derecha e izquierda */

    if (id_left != NO_ID)
    {
      for(i=0;i<MAX_OBJS;i++)
      {   
        /*Comprobar si el objeto se encuentra en el espacio*/           
        if (space_has_object(game_get_space(game, id_act), obj_id[i]) == FALSE)
        {         
          obj = ' ';
        }
        else
        {
          obj = '*';
          break;
        }
      }
      sprintf(str, "  |------------------");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |       %c      %2d ", obj, (int)id_left);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |                 ");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |-------------------");
      screen_area_puts(ge->map, str);
    }


    if (id_right != NO_ID)
    {
      for(i=0;i<MAX_OBJS;i++)
      {   
        /*Comprobar si el objeto se encuentra en el espacio*/           
        if (space_has_object(game_get_space(game, id_act), obj_id[i]) == FALSE)
        {         
          obj = ' ';
        }
        else
        {
          obj = '*';
          break;
        }
      }
      sprintf(str, "  ------------------|");
      screen_area_puts(ge->map, str);
      sprintf(str, "                    |");
      screen_area_puts(ge->map, str);
      sprintf(str, "       %c      %2d  |", obj, (int)id_right);
      screen_area_puts(ge->map, str);
      sprintf(str, "                    |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  ------------------|");
      screen_area_puts(ge->map, str);
    }
    
  }

  /* Paint in the description area */
  screen_area_clear(ge->descript);
  
  if ((player_loc != NO_ID) && (en_loc != NO_ID))
  {
    sprintf(str, "  Objects location:");
    screen_area_puts(ge->descript, str);
    
    for(i=0;i<MAX_OBJS;i++)
    { 
      if (game->object[i]==NULL)
      {
        break;                     
      }
     sprintf(str, "  %d:%d, ", (int)obj_id[i], (int)obj_loc[i]);
     screen_area_puts(ge->descript, str);
    }

    sprintf(str, "   ") ;
    screen_area_puts(ge->descript, str);
    sprintf(str, "  Player location:%d", (int)player_loc);
    screen_area_puts(ge->descript, str);
    sprintf(str, "  Player object:%d", (int)obj_get_id(player_obj));
    screen_area_puts(ge->descript, str);
    sprintf(str, "  Player health:%d", (int)player_health);
    screen_area_puts(ge->descript, str);

    
    sprintf(str, "   ") ;
    screen_area_puts(ge->descript, str);
    sprintf(str, "  Enemy location:%d", (int)en_loc);
    screen_area_puts(ge->descript, str);
    sprintf(str, "  Enemy health:%d", (int)en_health);
    screen_area_puts(ge->descript, str);
  }

  /* Paint in the banner area */
  screen_area_puts(ge->banner, " The game of the Goose "); 

  /* Paint in the help area */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, " w(UP), s(DOWN), a(LEFT), d(RIGHT), c(TAKE), v(DROP), q(ATTACK), e(EXIT)");
  screen_area_puts(ge->help, str);
  sprintf(str, " Player object will be -1 as long as it doesn't carry one");
  screen_area_puts(ge->help, str);

  /* Paint in the feedback area */
  last_cmd = game_get_last_command(game);
  sprintf(str, " %s (%s)", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
  screen_area_puts(ge->feedback, str);

  /* Dump to the terminal */
  screen_paint();
  printf("prompt:> ");
}
