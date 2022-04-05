/**
 * @brief It defines a textual graphic engine
 *
 * @file graphic_engine.c
 * @author Miguel Soto, Antonio Van-Oers, Nicolas Victorino and Ignacio Nunez
 * @version 3.0
 * @date 04-04-2022
 * @copyright GNU Public License
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../include/graphic_engine.h"
#include "../include/libscreen.h"
#include "../include/command.h"
#include "../include/space.h"
#include "../include/types.h"
#include "../include/enemy.h"
#include "../include/player.h"
#include "../include/object.h"
#include "../include/inventory.h"
#include "../include/set.h"


#define ROWS 37       /*!< Establish screen size in y dimension */
#define COLUMNS 120   /*!< Establish screen size in x dimension */

/**
 * @brief Graphic engine
 *
 * This struct contains all pointer to the different areas shown in graphics
 */
struct _Graphic_engine
{
  Area *map;      /*!< graphic engine area of the game map */
  Area *descript; /*!< graphic engine area of the description */
  Area *banner;   /*!< graphic engine area of the banner */
  Area *help;     /*!< graphic engine area of help */
  Area *feedback;   /*!< graphic engine area of feedback */
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

  ge->map = screen_area_init(1, 1, 80, 23);
  ge->descript = screen_area_init(82, 1, 35, 23);
  ge->banner = screen_area_init(53, 27, 14, 1);
  ge->help = screen_area_init(1, 28, 115, 3);
  ge->feedback = screen_area_init(1, 32, 115, 3);

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
  Id obj_loc[MAX_OBJS] = {NO_ID}, player_loc = NO_ID, en_loc[MAX_ENEMYS] = {NO_ID}, obj_id[MAX_OBJS]= {NO_ID};
  Inventory *player_inventory = NULL;
  int en_health[MAX_ENEMYS] = {0}, player_health = 0;
  Space *space_act = NULL;
  char obj = '\0';
  char str[255];
  T_Command last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  int i;
  char **gdesc = NULL, **gdesc_right = NULL, **gdesc_left = NULL;
  char *description;
  char *obj_name[MAX_OBJS];
  char link_up = '\0', link_down = '\0';

  /*Asignacion de los valores correspondientes a las variables*/
  player_loc = game_get_player_location(game, 21);
  id_act = player_loc;
  player_inventory = player_get_inventory(game_get_player(game, game_get_player_id(game)));
  player_health = player_get_health(game_get_player(game, game_get_player_id(game)));
  description = game_get_description(game);

  for(i=0;i<MAX_ENEMYS;i++)
  { 
    /* Control de errores */  
    if (game_get_enemy(game, game_get_enemy_id(game, i))==NULL)
    {
      break;
    }
    en_health[i] = enemy_get_health(game_get_enemy(game, game_get_enemy_id(game, i)));
    en_loc[i] = game_get_enemy_location(game, game_get_enemy_id(game, i));
  }

  for(i=0;i<MAX_OBJS;i++)
  { 
    /* Control de errores */  
    if (game_get_object(game, game_get_object_id(game, i))==NULL)
    {
      break;
    }
    obj_id[i] = game_get_object_id(game, i);
    obj_loc[i] = obj_get_location(game_get_object(game, game_get_object_id(game, i)));
    obj_name[i] = (char *) obj_get_name(game_get_object(game, game_get_object_id(game, i)));
  }

  /* Paint the in the map area */
  screen_area_clear(ge->map);
  
  if (id_act != NO_ID)
  {
    space_act = game_get_space(game, id_act);
    id_up = space_get_id_dest_by_link(game_get_link(game, space_get_link(space_act, N)));
    id_down = space_get_id_dest_by_link(game_get_link(game, space_get_link(space_act, S)));
    id_left = space_get_id_dest_by_link(game_get_link(game, space_get_link(space_act, W)));
    id_right = space_get_id_dest_by_link(game_get_link(game, space_get_link(space_act, E)));

    space_print(space_act);

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

      if (id_up < 100)
      {
        sprintf(str, "  | gpp0^        %2d |", (int)id_act);
      }
      else
      {
        sprintf(str, "  | gpp0^        %2d|", (int)id_act);
      }
      screen_area_puts(ge->map, str);

      sprintf(str, "  |                  |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |        %c         |", obj);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |                 |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------------+");
      screen_area_puts(ge->map, str);
      
      if (game_get_connection_status(game, id_act, N) == OPEN)
      {
        link_up = '^';
      }
      else
      {
        link_up = ' ';
      }
      if (game_get_connection_status(game, id_up, S) == OPEN)
      {
        link_down = 'v';
      }
      else
      {
        link_down = ' ';
      }
      sprintf(str, "      %c  %c", link_up, link_down);
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
        screen_area_puts(ge->map, str);
        /*\\(\")/ CODIFICACION HORMIGA */
        if (id_act < 100)
        {
          sprintf(str, "  | gpp0^        %2d |", (int)id_act);
        }
        else
        {
          sprintf(str, "  | gpp0^        %2d|", (int)id_act);
        }
        screen_area_puts(ge->map, str);

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
        sprintf(str, "  +-----------------+    ------------------|");
        screen_area_puts(ge->map, str);
        sprintf(str, "  |                  |   |                 |");
        screen_area_puts(ge->map, str);
        /*\\(\")/ CODIFICACION HORMIGA */
        sprintf(str, "  | gpp0^         %2ld|   |              %2ld|", id_act, id_right);
        screen_area_puts(ge->map, str);
        sprintf(str, "  |       %c          |   |                 |", obj);
        screen_area_puts(ge->map, str);
        gdesc = space_get_gdesc(game_get_space(game, id_act)); 
        gdesc_right = space_get_gdesc(game_get_space(game, id_right)); 
        
        for (i = 0; i < TAM_GDESC_Y; i++)
        {
          if (i != 3) {
            sprintf(str, "  |     %s    |   |    %s    |", gdesc[i], gdesc_right[i]);
            screen_area_puts(ge->map, str);
          } else {
            sprintf(str, "  |     %s    | > |    %s    |", gdesc[i], gdesc_right[i]);
            screen_area_puts(ge->map, str);
          }
        }
        
        sprintf(str, "  |                  |   |                 |");
        screen_area_puts(ge->map, str);
        sprintf(str, "  |                  |   |                 |");
        screen_area_puts(ge->map, str);
        sprintf(str, "  |                  |   |                 |");
        screen_area_puts(ge->map, str);
        sprintf(str, "  +-----------------+>>  ------------------|");
        screen_area_puts(ge->map, str);  
      }
      
      /*Si hay espacios a derecha e izquierda*/
      if (id_left != NO_ID && id_right != NO_ID)
      {
        for (i = 0; i < 4; i++) 
        {
        sprintf(str, " ");
        screen_area_puts(ge->map, str);
        }
        
        sprintf(str, "  |-----------------    +-----------------+   ------------------|");
        screen_area_puts(ge->map, str);
        sprintf(str, "  |                 |   |                 |   |                 |");
        screen_area_puts(ge->map, str);
        /*\\(\")/ CODIFICACION HORMIGA */
        sprintf(str, "  |              %2ld|   | gpp0^        %2ld|   |              %2ld|",id_left, id_act, id_right);
        screen_area_puts(ge->map, str);
        sprintf(str, "  |                 |   |         %c       |   |                 |", obj);
        screen_area_puts(ge->map, str);
        gdesc = space_get_gdesc(game_get_space(game, id_act)); 
        gdesc_right = space_get_gdesc(game_get_space(game, id_right)); 
        gdesc_left = space_get_gdesc(game_get_space(game, id_left)); 
        
        for (i = 0; i < TAM_GDESC_Y; i++)
        {
          if (i != 3) {
            sprintf(str, "  |    %s    |   |    %s    |   |    %s    |", gdesc_left[i], gdesc[i], gdesc_right[i]);
            screen_area_puts(ge->map, str);
          } else {
            sprintf(str, "  |    %s    | < |    %s    | > |    %s    |", gdesc_left[i], gdesc[i], gdesc_right[i]);
            screen_area_puts(ge->map, str);
          }
        }
        
        sprintf(str, "  |                 |   |                 |   |                 |");
        screen_area_puts(ge->map, str);
        sprintf(str, "  |                 |   |                 |   |                 |");
        screen_area_puts(ge->map, str);
        sprintf(str, "  |                 |   |                 |   |                 |");
        screen_area_puts(ge->map, str);
        sprintf(str, "  |                 |   |                 |   |                 |");
        screen_area_puts(ge->map, str);  
        sprintf(str, "  |-----------------    +-----------------+   ------------------|");
        screen_area_puts(ge->map, str);
      }

      /*Si no hay espacios a derecha y si a izquierda*/
      if (id_right == NO_ID && id_left != NO_ID && id_act==14)
      {  
        for (i = 0; i < 4; i++) 
        {
        sprintf(str, " ");
        screen_area_puts(ge->map, str);
        }

        sprintf(str, "  |------------------   +-----------------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "  |                 |   |                 |");
        screen_area_puts(ge->map, str);
        /*\\(\")/ CODIFICACION HORMIGA */
        sprintf(str, "  |              %2ld|   |  gpp0^       %2ld |", id_left, id_act);
        screen_area_puts(ge->map, str);
        sprintf(str, "  |                 |   |        %c        |", obj);
        screen_area_puts(ge->map, str);
        gdesc = space_get_gdesc(game_get_space(game, id_act)); 
        gdesc_left = space_get_gdesc(game_get_space(game, id_left)); 
        
        for (i = 0; i < TAM_GDESC_Y; i++)
        {
          if (i != 3) {
            sprintf(str, "  |     %s   |   |     %s   |", gdesc_left[i], gdesc[i]);
            screen_area_puts(ge->map, str);
          }else {
            sprintf(str, "  |     %s   | > |     %s   |", gdesc_left[i], gdesc[i]);
            screen_area_puts(ge->map, str);
          }
        }
        
        sprintf(str, "  |                 |   |                 |");
        screen_area_puts(ge->map, str);
        sprintf(str, "  |                 |   |                 |");
        screen_area_puts(ge->map, str);
        sprintf(str, "  |                 |   |                 |");
        screen_area_puts(ge->map, str);
        sprintf(str, "  |-----------------    <<+---------------+");
        screen_area_puts(ge->map, str);  
      }
          
    }

    /* ESPACIO ABAJO*/
    if (id_down != NO_ID && id_act != 14)
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

      sprintf(str, "           v");
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
    
  }

      /* ESPACIO ABAJO EN ESPACIO 14*/
    if (id_down != NO_ID && id_act == 14)
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

      sprintf(str, "                                  v");
      screen_area_puts(ge->map, str);
      sprintf(str, "                        +-----------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                        |                 |");
      screen_area_puts(ge->map, str);
      sprintf(str, "                        |              %2d |", (int)id_down);
      screen_area_puts(ge->map, str);
      sprintf(str, "                        |        %c        |", obj);
      screen_area_puts(ge->map, str);
      sprintf(str, "                        |                 |");
      screen_area_puts(ge->map, str);
    }

  /* Paint in the description area */
  screen_area_clear(ge->descript);
  
  if ((player_loc != NO_ID) && (en_loc[0] != NO_ID))
  {
    sprintf(str, "  Objects location:");
    screen_area_puts(ge->descript, str);
    
    for(i=0;i<MAX_OBJS;i++)
    { 
      if (game_get_object(game, game_get_object_id(game, i))==NULL)
      {
        break;                     
      }
     sprintf(str, "  %s:%d, ", obj_name[i], (int)obj_loc[i]);
     screen_area_puts(ge->descript, str);
    }

    sprintf(str, "   ") ;
    screen_area_puts(ge->descript, str);
    sprintf(str, "  Player location:%d", (int)player_loc);
    screen_area_puts(ge->descript, str);
    if(player_inventory==NULL)
    {
      sprintf(str, "  Player object: No object" );
      screen_area_puts(ge->descript, str);
    }
    else
    {
      sprintf(str, "  Player objects:"); 
      screen_area_puts(ge->descript, str);

      for (i = 0; i < set_get_nids(inventory_get_objects(player_get_inventory(game_get_player(game, 21)))); i++)
      {
        sprintf(str, "    %s", obj_get_name(game_get_object(game, set_get_ids_by_number(inventory_get_objects(player_get_inventory(game_get_player(game, 21))),i)))); 
        screen_area_puts(ge->descript, str);
      }
    }
    
    sprintf(str, "  Player health:%d", (int)player_health);
    screen_area_puts(ge->descript, str);

    
    sprintf(str, "   ") ;
    screen_area_puts(ge->descript, str);
    sprintf(str, "  Enemy location:%d", (int)en_loc[0]);
    screen_area_puts(ge->descript, str);
    sprintf(str, "  Enemy health:%d", (int)en_health[0]);
    screen_area_puts(ge->descript, str);

    sprintf(str, "   ");
    screen_area_puts(ge->descript, str);
    sprintf(str, "  Descriptions:");
    screen_area_puts(ge->descript, str);
    if(description){
      sprintf(str, "  %s", description);
      screen_area_puts(ge->descript, str);
    }
  }

  /* Paint in the banner area */
  screen_area_puts(ge->banner, " The Ant-Game "); 

  /* Paint in the help area */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, " w(UP), s(DOWN), a(LEFT), d(RIGHT), c(TAKE), v(DROP), q(ATTACK), i(INSPECT), m(MOVE), e(EXIT)");
  screen_area_puts(ge->help, str);
  /*
  sprintf(str, " Player object will be -1 as long as it doesn't carry one");
  screen_area_puts(ge->help, str);
  */

  /* Paint in the feedback area */
  last_cmd = game_get_last_command(game);
  if (st == 0)
  {
    sprintf(str, " %s (%s): ERROR", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
  }
  else if (st == 1)
  {
    sprintf(str, " %s (%s): OK", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
  }
  else
  {
    sprintf(str, " %s (%s)", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
  }
  
  screen_area_puts(ge->feedback, str);

  /* Dump to the terminal */
  screen_paint();
  printf("prompt:> ");
}
