/** 
 * @brief It implements the game interface and all the associated calls
 * for each command
 * 
 * @file game.c
 * @author Profesores PPROG
 * @version 2.1
 * @date 12-02-2021 
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game.h"

typedef struct _Game
{
  Player *player[MAX_PLAYERS];      /*!< Pointer to player's array */
  Object *object[MAX_OBJS];         /*!< Pointer to object's array */
  Enemy *enemy[MAX_ENEMYS];         /*!< Pointer to enemy's array */
  Space *spaces[MAX_SPACES];        /*!< Pointer to space's array */
  Link *links[MAX_LINKS];           /*!< Pointer to link's array */
  char *description;                /*!< Description that should be shown*/
  T_Command last_cmd;               /*!< Ultimo comando introducido por el usuario */
}Game; 

/**
   Private functions
*/
STATUS game_add_space(Game *game, Space *space);
STATUS game_add_object(Game *game, Object *obj);
STATUS game_add_player(Game *game, Player *p);
STATUS game_add_enemy(Game *game, Enemy *e);
STATUS game_add_link(Game *game, Link *l);
Id game_get_space_id_at(Game *game, int position);
STATUS game_set_player_location(Game *game, Id player_id, Id space_id);
STATUS game_set_object_location(Game *game, Id obj_id, Id space_id);
STATUS game_set_enemy_location(Game *game, Id enemy_id, Id space_id);

int game_command_unknown(Game *game, char *arg);
STATUS game_command_exit(Game *game, char *arg);
STATUS game_command_down(Game *game, char *arg);
STATUS game_command_up(Game *game, char *arg);
STATUS game_command_take(Game *game, char *arg);
STATUS game_command_drop(Game *game, char *arg);
STATUS game_command_attack(Game *game, char *arg);
STATUS game_command_left(Game *game, char *arg);
STATUS game_command_right(Game *game, char *arg);
STATUS game_command_move(Game *game, char *arg);
STATUS game_command_inspect(Game *game, char *arg);


/**
  Game interface implementation
*/


STATUS game_alloc(Game *game)
{

  if (!game)
  {
    fprintf(stderr, "Error saving memory for game (game_alloc)");
    return ERROR;
  }
  Id id_player = 21, id_enemy = 41;
  int i;

  for (i = 0; i < MAX_PLAYERS; i++)
  {
    game->player[i] = player_create(id_player);
    if (!game->player[i])
    {
      return ERROR;
    }  
  }

  for (i = 0; i < MAX_ENEMYS; i++)
  {
    game->enemy[i] = enemy_create(id_enemy);
    if (!game->enemy[i])
    {
      return ERROR;
    }
  }

  game->description = " ";
  return OK;
}


/** game_create inicializa todas las variables necesarias para 
  * el juego a valores vacios
  */
STATUS game_create(Game *game)
{
  /* Control de errores*/
  if (game == NULL)
  {
    return ERROR;
  }
  
  
  int i;

  for (i = 0; i < MAX_SPACES; i++)
  {
    game->spaces[i] = NULL;
  }

  for (i = 0; i < MAX_OBJS; i++)
  {
    game->object[i] = NULL;
  }

  for (i = 0; i < MAX_PLAYERS; i++)
  {
    game->player[i] = NULL;
  }

  for (i = 0; i < MAX_ENEMYS; i++)
  {
    game->enemy[i] = NULL;
  }

  for (i = 0; i < MAX_LINKS; i++)
  {
    game->links[i] = NULL;
  }
  
  game->last_cmd = NO_CMD;

  return OK;
}

/** game_destroy destruye todos los espacios de la partida 
  * llamando a space_destroy para cada uno de ellos
  */
STATUS game_destroy(Game *game)
{
  /* Control de errores */
  if(game == NULL)
  {
    return ERROR;
  }

  int i = 0;
  
  for (i = 0; i < MAX_OBJS && game->object[i] != NULL; i++)
  {
    obj_destroy(game->object[i]);
    game->object[i] = NULL;
  }
  
  for (i = 0; i < MAX_PLAYERS && game->player[i] != NULL; i++)
  {
    player_destroy(game->player[i]);
    game->player[i] = NULL;
  }

  for (i = 0; i < MAX_ENEMYS && game->enemy[i] != NULL; i++)
  {
    enemy_destroy(game->enemy[i]);
    game->enemy[i] = NULL;
  }
      
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    space_destroy(game->spaces[i]);
    game->spaces[i] = NULL;
  }

  for (i = 0; i < MAX_LINKS; i++)
  {
    link_destroy(game->links[i]);
    game->links[i] = NULL;
  }
  
  free(game);
  game = NULL;

  return OK;
}

/**
  * @brief Agrega los espacios del juego
  * @author Profesores PPROG
  *
  * game_add_space agrega uno a uno los espacios al juego
  * @param game es el puntero que apunta a la estructura tipo Game
  * @param space es el puntero que apunta a la estructura tipo espacio para anadir
  * @return OK si todo ha ido bien y ERROR si ha habido algun problema
  */
STATUS game_add_space(Game *game, Space *space)
{
  /* Control de errores */
  if (game == NULL)
  {
    return ERROR;
  }
  int i = 0;

  /* Control de errores */
  if (space == NULL)
  {
    return ERROR;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {}

  /* Control de errores */
  if (i >= MAX_SPACES)
  {
    return ERROR;
  }

  game->spaces[i] = space;

  return OK;
}

/**
 * @brief Agrega los objetos del juego
 * @author Miguel Soto
 * 
 * game_add_obj agrega uno a uno los objetos al juego
 * @param game es el puntero a Game del que se quiere incluir un objeto
 * @param obj es el puntero a Object que se quiere incluir en el juego
 * @return OK si todo ha ido bien y ERROR si ha habido algun problema
 */
STATUS game_add_object(Game *game, Object *obj)
{
  if (!game || !obj)
  {
    return ERROR;
  }

  int i;

  for (i = 0; i < MAX_OBJS && game->object[i] != NULL; i++) {}

  if (i >= MAX_OBJS)
  {
    return ERROR;
  }

  game->object[i] = obj;

  return OK;
}

/**
 * @brief Agrega jugadores al juego
 * @author Miguel Soto
 * 
 * game_add_obj agrega uno a uno los objetos al juego
 * @param game es el puntero a Game del que se quiere incluir un objeto
 * @param obj es el puntero a Object que se quiere incluir en el juego
 * @return OK si todo ha ido bien y ERROR si ha habido algun problema
 */
STATUS game_add_player(Game *game, Player *p)
{
  if (!game || !p)
  {
    return ERROR;
  }
  
  int i;
  for (i = 0; i < MAX_PLAYERS && game->player[i] != NULL; i++) {}

  if (i >= MAX_PLAYERS)
  {
    return ERROR;
  }
  
  game->player[i] = p;

  return OK;
}

/**
 * @brief Agrega los objetos del juego
 * @author Miguel Soto
 * 
 * game_add_obj agrega uno a uno los objetos al juego
 * @param game es el puntero a Game del que se quiere incluir un objeto
 * @param obj es el puntero a Object que se quiere incluir en el juego
 * @return OK si todo ha ido bien y ERROR si ha habido algun problema
 */
STATUS game_add_enemy(Game *game, Enemy *e)
{
  if (!game || !e)
  {
    return ERROR;
  }
  
  int i;
  for (i = 0; i < MAX_ENEMYS && game->enemy[i] != NULL; i++) {}

  if (i >= MAX_ENEMYS)
  {
    return ERROR;
  }
  
  game->enemy[i] = e;

  return OK;
}

/**
 * @brief Agrega los objetos del juego
 * @author Miguel Soto
 * 
 * game_add_obj agrega uno a uno los objetos al juego
 * @param game es el puntero a Game del que se quiere incluir un objeto
 * @param obj es el puntero a Object que se quiere incluir en el juego
 * @return OK si todo ha ido bien y ERROR si ha habido algun problema
 */
STATUS game_add_link(Game *game, Link *l)
{
  if (!game || !l)
  {
    return ERROR;
  }
  
  int i;
  for (i = 0; i < MAX_LINKS && game->links[i] != NULL; i++) {}

  if (i >= MAX_LINKS)
  {
    return ERROR;
  }
  
  game->links[i] = l;

  return OK;
}

/**
  * @brief Comprueba si los espacios están o no fuera del rango establecido
  * @author Profesores PPROG
  *
  * game_get_space_id_at Comprueba si un espacio esta o no fuera del juego y devuelve No_ID 
  * para establecer que se encuentra fuera de limites o su id si este esta en el juego
  * @param game es el puntero que apunta a la estructura tipo Game, que contiene los datos de localización de objeto y jugador 
  * junto con los espacios del juego y el ultimo comando 
  * @param position es el entero que indica la posicion del espacio a comprobar
  * @return space_get_id(game->spaces[position]) Llamada a la funcion para obtener la id del espacio si este se encuentra en el juego
  * y NO_ID si el espacio se encentra fuera del rango 
  */
Id game_get_space_id_at(Game *game, int position)
{
  /* Control de errores */
  if (position < 0 || position >= MAX_SPACES)
  {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}

/** Comprueba uno a uno los espacios del juego para 
  * ver si son nulos o coinciden con la id
  */
Space *game_get_space(Game *game, Id id)
{
  int i;

  if (!game || id == NO_ID)
  {
    return NULL;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    if (id == space_get_id(game->spaces[i]))
    {
      return game->spaces[i];
    }
  }

  return NULL;
}

/**
 * Comprueba uno a uno los objetos del juego para ver si coinciden con la id
 */
Object *game_get_object(Game *game, Id id)
{
  int i;

  if (!game || id == NO_ID)
  {
    return NULL;
  }
  
  for (i = 0; i < MAX_OBJS && game->object[i] != NULL; i++)
  {
    if (id == obj_get_id(game->object[i]))
    {
      return game->object[i];
    }
  }

  return NULL;
}

/**
 * Finds an object with the same name
 */
Object *game_get_object_byName(Game *game, char* name)
{
  int i;

  if (!game || name == NULL)
  {
    return NULL;
  }
  
  for (i = 0; i < MAX_OBJS && game->object[i] != NULL; i++)
  {
    if (strcmp(name, obj_get_name(game->object[i])) == 0)
    {
      return game->object[i];
    }
  }

  return NULL;
}

/**
 * Comprueba uno a uno los players del juego para ver si coinciden con la id
 */
Player *game_get_player(Game *game, Id id)
{
  int i;

  if (!game || id == NO_ID)
  {
    return NULL;
  }
  
  for (i = 0; i < MAX_PLAYERS && game->player[i] != NULL; i++)
  {
    if (id == player_get_id(game->player[i]))
    {
      return game->player[i];
    }
  }

  return NULL;
}

/**
 * Comprueba uno a uno los enemies del juego para ver si coinciden con la id
 */
Enemy *game_get_enemy(Game *game, Id id)
{
  int i;

  if (!game || id == NO_ID)
  {
    return NULL;
  }
  
  for (i = 0; i < MAX_ENEMYS && game->enemy[i] != NULL; i++)
  {
    if (id == enemy_get_id(game->enemy[i]))
    {
      return game->enemy[i];
    }
  }
  
  return NULL;
}

/**
 * returns description that is on screen
 */
char *game_get_description(Game *game)
{
  if (!game)
  {
    return NULL;
  }
  
  return game->description;
}

/**
 * Comprueba uno a uno los enemies del juego para ver si coinciden con la id
 */
Link *game_get_link(Game *game, Id id)
{
  int i;

  if (!game || id == NO_ID)
  {
    return NULL;
  }
  
  for (i = 0; i < MAX_LINKS && game->links[i] != NULL; i++)
  {
    if (id == link_get_id(game->links[i]))
    {
      return game->links[i];
    }
  }
  
  return NULL;
}

/**
  * @brief Establece la id como la posicion del jugador
  * @author Miguel Soto
  *
  * game_set_player_location establece la id como la posicion del jugador
  * @param game es el puntero que apunta a game, que contiene los datos de localización de objeto y jugador 
  * junto con los espacios del juego y el ultimo comando 
  * @param id es el numero de identificacion del espacio en el que se establecera el jugador
  * @return OK si a la posicion del jugador se le asigna la id con exito y ERROR si la id no esta definida
  */
STATUS game_set_player_location(Game *game, Id player_id, Id space_id)
{
  /* Control de errores */
  if (!game || player_id == NO_ID || space_id == NO_ID)
  {
    return ERROR;
  }

  Player *p = NULL;
  p = game_get_player(game, player_id);
  if (!p)
  {
    return ERROR;
  }
  
  if(player_set_location(p, space_id)==ERROR)
  {
    return ERROR;
  }

  return OK;
}

/**
  * @brief Establece la id como la posicion del objeto
  * @author Miguel Soto
  *
  * game_set_object_location establece la id como la posicion del objeto
  * @param game es el puntero que apunta a game, que contiene los datos de localización de objeto y jugador 
  * junto con los espacios del juego y el ultimo comando 
  * @param id es el numero de identificacion del espacio en el que se establecera el objeto
  * @return OK si a la posicion del objeto se le asigna la id con exito y ERROR si la id no esta definida
  */
STATUS game_set_object_location(Game *game, Id obj_id, Id space_id)
{
  /* Control de errores */
  if (!game || obj_id == NO_ID)
  {
    return ERROR;
  }

  Object *o = NULL;

  o = game_get_object(game, obj_id);
  if (!o)
  {
    return ERROR;
  }

  if(obj_set_location(o, space_id)==ERROR)
  {
    return ERROR;
  }

  return OK;
}

/**
  * @brief Establece la id como la posicion del enemigo
  * @author Antonio Van-Oers
  *
  * game_set_enemy_location establece la id como la posicion del enemigo
  * @param game es el puntero que apunta a game, que contiene los datos de localización de objeto y jugador 
  * junto con los espacios del juego y el ultimo comando 
  * @param id es el numero de identificacion del espacio en el que se establecera el enemigo
  * @return OK si a la posicion del enemigo se le asigna la id con exito y ERROR si la id no esta definida
  */
STATUS game_set_enemy_location(Game *game, Id enemy_id, Id space_id)
{
  /* Control de errores */
  if (!game || enemy_id == NO_ID || space_id == NO_ID)
  {
    return ERROR;
  }

  Enemy *e = NULL;
  e = game_get_enemy(game, enemy_id);
  if (!e)
  {
    return ERROR;
  }
  
  return enemy_set_location(game->enemy[MAX_PLAYERS-1], space_id);
}


/** Obtiene la posicion del player
  */
Id game_get_player_location(Game *game, Id player_id)
{
  /* Control de errores */
  if (!game || player_id == NO_ID)
  {
    return NO_ID;
  }

  Player *p = NULL;
  p = game_get_player(game, player_id);
  if (!p)
  {
    return NO_ID;
  }
  
  return player_get_location(p);
}

/** Obtiene la posicion del enemigo
  */
Id game_get_enemy_location(Game *game, Id enemy_id)
{
  /* Control de errores */
  if (!game || enemy_id == NO_ID)
  {
    return NO_ID;
  }

  Enemy *e = NULL;
  e = game_get_enemy(game, enemy_id);
  if (!e)
  {
    return NO_ID;
  }

  return enemy_get_location(e);
}

/** Obtiene la posicion del objeto
  */
Id game_get_object_location(Game *game, Id obj_id)
{
  /* Control de errores */
  if (!game || obj_id == NO_ID)
  {
    return NO_ID;
  }

  Object *o = NULL;
  o = game_get_object(game, obj_id);
  if (!o)
  {
    return ERROR;
  }

  return obj_get_location(o);
}

/** game_update utiliza la variable cmd del interprete de comandos para determinar que funcion debe llamar
  * en cada caso
  */
int game_update(Game *game, T_Command cmd, char *arg)
{
  int st = 0;
  game->last_cmd = cmd;

  switch (cmd)
  {
  case UNKNOWN:
    st = game_command_unknown(game, arg);
    break;

  case EXIT:
    st = (int) game_command_exit(game, arg);
    break;

  case DOWN:
    st = (int) game_command_down(game, arg);
    break;

  case RIGHT:
    st = (int) game_command_right(game, arg);
    break;

  case LEFT:
    st = (int) game_command_left(game, arg);
    break;

  case UP:
    st = (int) game_command_up(game, arg);
    break;

  case TAKE:
    st = (int) game_command_take(game, arg);
    break;
  
  case DROP:
    st = (int) game_command_drop(game, arg);
    break;

  case ATTACK:
    st = (int) game_command_attack(game, arg);
    break;
  
  case MOVE:
    st = (int) game_command_move(game, arg);
    break;
  case INSPECT:
    st = (int) game_command_inspect(game, arg);

  default:
    break;
  }

  return st;
}

/** Dentro de game, accede a la variable last_cmd para obtener el ultimo 
  * comando introducido por el usuario en la partida
  */
T_Command game_get_last_command(Game *game)
{
  return game->last_cmd;
}

/** 
  * game_print_data imprime en la interfaz los datos acerca de la posicion actual del jugador y objeto
  */
void game_print_data(Game *game)
{
  int i = 0;

  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    space_print(game->spaces[i]);
  }

  printf("=> Objects:\n");
  for (i = 0; i < MAX_OBJS && game->object[i] != NULL; i++)
  {
    obj_print(game->object[i]);
  }
  
  printf("=> Players:\n");
  for (i = 0; i < MAX_PLAYERS && game->player[i] != NULL; i++)
  {
    player_print(game->player[i]);
  }
  
  printf("=> Enemies:\n");
  for (i = 0; i < MAX_ENEMYS && game->enemy[i] != NULL; i++)
  {
    enemy_print(game->enemy[i]);
  }
}

/** Devuelve FALSE cuando se llama a la funcion, 
 * significando que la partida ha terminado
 */
BOOL game_is_over(Game *game)
{
  if (player_get_health(game->player[MAX_PLAYERS-1]) <= 0)
  {
    return TRUE;
  }
  
  return FALSE;
}

/**
   Calls implementation for each action 
*/
int game_command_unknown(Game *game, char *arg)
{
  return 5;
}

STATUS game_command_exit(Game *game, char *arg)
{
  return OK;
}

STATUS game_command_take(Game *game, char *arg)
{
  Id player_location = player_get_location(game->player[MAX_PLAYERS-1]);
  Id id_obj_taken = NO_ID, obj_loc = NO_ID;
  Object *obj_taken;

  obj_taken = game_get_object_byName(game, arg);
  id_obj_taken = obj_get_id(obj_taken);
  

   /* Control de errores */
  if (space_has_object(game_get_space(game, player_location), id_obj_taken))
  {
    obj_loc = game_get_object_location(game, id_obj_taken);
    
    /* Control de errores */
    if (player_location != obj_loc)
    {
      return ERROR;
    }

    Space *s = game_get_space(game, player_location);
    /* Control de errores */
    if (s == NULL)
    {
      return ERROR;
    }

    Object *o = game_get_object(game, id_obj_taken);
    /* Control de errores */
    if (o == NULL)
    {
      return ERROR;
    }

    if (game_set_object_location(game, obj_get_id(o), NO_ID) == ERROR)
    {
      printf("Igual es la 786 o por ahi, %d", (int)obj_get_id(o));
      return ERROR;
    }
        
    if (player_add_object(game->player[MAX_PLAYERS-1], o) == ERROR)
    {
      return ERROR;
    }
    if (space_del_objectid(s, id_obj_taken) == ERROR)
    {
      return ERROR;
    }
    return OK;
  }

  return ERROR;
} 

STATUS game_command_drop(Game *game, char *arg)
{

  Id player_location = player_get_location(game->player[MAX_PLAYERS-1]);
  Id obj_id = NO_ID;
  Object *obj;

  obj = game_get_object_byName(game, arg);
  obj_id = obj_get_id(obj);

  if (obj_id != obj_get_id(obj) || inventory_has_id(player_get_inventory(game->player[MAX_PLAYERS-1]), obj_id)==FALSE)
  {
    return ERROR;
  }
   
  /* Control de errores */
  if (player_get_inventory(game->player[MAX_PLAYERS-1]) == NULL)
  {
    return ERROR;
  }

  Space *s = game_get_space(game, player_location);
  /* Control de errores */
  if (s == NULL)
  {
    return ERROR;
  }
  
  Object *o = game_get_object(game, obj_id);
  /* Control de errores */
  if (o == NULL)
  {
    return ERROR;
  }

  if (space_add_objectid(s, obj_get_id(o)) == ERROR)
  {
    return ERROR;
  }
  if (game_set_object_location(game, obj_get_id(o), space_get_id(s)) == ERROR)
  {
    return ERROR;
  }
  if (player_del_object(game->player[MAX_PLAYERS-1], obj_id) == ERROR)
  {
    return ERROR;
  }

  return OK;
}

/** Cuando el ultimo comando se ha interpretado como next
 * desplaza al jugador hacia el sur, actualizando su posicion
 */
STATUS game_command_down(Game *game, char *arg)
{
  Id player_location = player_get_location(game->player[MAX_PLAYERS-1]);
  Id player_id = player_get_id(game->player[MAX_PLAYERS-1]);
  int i = 0;
  Id current_id = NO_ID;
  
  if (player_id == NO_ID)
  {
    return ERROR;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == player_location) 
    {
      current_id = space_get_south(game->spaces[i]);
      if (current_id != NO_ID)
      {
        game_set_player_location(game,player_id, current_id);
        return OK;
      }
    }
  }
  return ERROR;
}

/** Cuando el ultimo comando se ha interpretado como back
 * desplaza al jugador hacia el norte, actualizando su posicion
 */
STATUS game_command_up(Game *game, char *arg)
{
  Id player_location = player_get_location(game->player[MAX_PLAYERS-1]);
  Id player_id = player_get_id(game->player[MAX_PLAYERS-1]);
  int i = 0;
  Id current_id = NO_ID;
  
  if (player_id == NO_ID)
  {
    return ERROR;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == player_location) 
    {
      current_id = space_get_north(game->spaces[i]);
      if (current_id != NO_ID)
      {
        game_set_player_location(game,player_id, current_id);
        return OK;
      }
    }
  }
  return ERROR;
}

STATUS game_command_attack(Game *game, char *arg)
{
  srand (time(NULL)); 
  int rand_num;
  rand_num = rand() % 10; 
  
  Id player_loc = player_get_location(game->player[MAX_PLAYERS-1]);
  Id enemy_loc= enemy_get_location(game->enemy[MAX_PLAYERS-1]);
  
  if(enemy_get_health(game->enemy[MAX_PLAYERS-1])==0)
  {
    return ERROR;
  }

  if (player_loc == NO_ID || enemy_loc == NO_ID)
  {
    return ERROR;
  }
 

  /*En caso de que no se encuentren en el mismo espacio, el comando no hace nada */
  if(player_loc != enemy_loc)
  {
    return ERROR;
  }
  /*El jugador gana si en rand_num es > 5, en caso contrario, pierde una vida ya que el enemigo ha ganado*/
  if (rand_num > 5)
  {
    enemy_set_health(game->enemy[MAX_PLAYERS-1], (enemy_get_health(game->enemy[MAX_PLAYERS-1])-1)); 
  }
  else 
  {
    player_set_health(game->player[MAX_PLAYERS-1], (player_get_health(game->player[MAX_PLAYERS-1])-1)); 
    if (player_get_health(game->player[MAX_PLAYERS-1])== 0 )
    {
      game_is_over(game);
    }
  }

  return OK;
}

/** Cuando el ultimo comando se ha interpretado como left
 * desplaza al jugador hacia el Oeste, actualizando su posicion
 */
STATUS game_command_left(Game *game, char *arg)        
{
  Id player_location = player_get_location(game->player[MAX_PLAYERS-1]);
  Id player_id = player_get_id(game->player[MAX_PLAYERS-1]);
  int i = 0;
  Id current_id = NO_ID;
  
  if (player_id == NO_ID)
  {
    return ERROR;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == player_location) 
    {
      current_id = space_get_west(game->spaces[i]);
      if (current_id != NO_ID)
      {
        game_set_player_location(game,player_id, current_id);
        return OK;
      }
    }
  }
  return ERROR;
}

/** Cuando el ultimo comando se ha interpretado como right
 * desplaza al jugador hacia el Este, actualizando su posicion
 */
STATUS game_command_right(Game *game, char *arg)
{
  Id player_location = player_get_location(game->player[MAX_PLAYERS-1]);
  Id player_id = player_get_id(game->player[MAX_PLAYERS-1]);
  int i = 0;
  Id current_id = NO_ID;
  
  if (player_id == NO_ID)
  {
    return ERROR;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == player_location) 
    {
      current_id = space_get_east(game->spaces[i]);
      if (current_id != NO_ID)
      {
        game_set_player_location(game,player_id, current_id);
        return OK;
      }
    }
  }
  return ERROR;
}

/*Function that gets the enemy id based on the position it is located in the enemy array located in the game structure */
Id game_get_enemy_id(Game *game, int num) 
{

  if ( !game || num < 0 || num > MAX_ENEMYS - 1) 
  {
    return NO_ID;
  }

  return (Id)enemy_get_id(game->enemy[num]);
}

Id game_get_player_id(Game* game) 
{
  
  if (!game)
  {
    return NO_ID;
  }

  return (Id)player_get_id(game->player[MAX_PLAYERS-1]);
}

/*Function that gets the object id based on the position it is located in the object array located in the game structure */
Id game_get_object_id(Game *game, int num) 
{

  if ( !game || num < 0 || num > MAX_ENEMYS - 1) 
  {
    return NO_ID;
  }

  return (Id)obj_get_id(game->object[num]);
}

Game* game_alloc2() 
{

  Game* game = NULL;

  game = (Game*)malloc(sizeof(Game));
  if (!game)
  {
    fprintf(stderr, "Error saving memory for game(game_create)");
    return ERROR;
  }

  return game;
}

/** Forma alternativa para moverse, segun sea move n,s,e,w
 * a norte, sur, este y oeste
 */
STATUS game_command_move(Game *game, char *arg)        
{
  Id player_location = player_get_location(game->player[MAX_PLAYERS-1]);
  Id player_id = player_get_id(game->player[MAX_PLAYERS-1]);
  int i = 0;
  Id current_id = NO_ID;
  char c[10];
  char west[10]={'w','\0'};
  char north[10]={'n','\0'};
  char south[10]={'s','\0'};
  char east[10]={'e','\0'};

  strcpy(c, arg);
  c[1]='\0';

  if (player_id == NO_ID)
  {
    return ERROR;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == player_location) 
    {
      /*Move west*/
      
      if(strcmp(c, west)==0){
      current_id = space_get_west(game->spaces[i]);
      }

      /*Move north*/
      
     if(strcmp(c, north)==0){
      current_id = space_get_north(game->spaces[i]);
      }

      /*Move south*/
     
      if(strcmp(c, south)==0){
      current_id = space_get_south(game->spaces[i]);
      }

      /*Move east*/
      
      if(strcmp(c, east)==0){
      current_id = space_get_east(game->spaces[i]);
      }

      if (current_id != NO_ID)
      {
        game_set_player_location(game,player_id, current_id);
        return OK;
      }
    }
  }
  
  return ERROR;
}

/*Changes the description of game to the one user wanted
*/
STATUS game_command_inspect(Game *game, char *arg){

  /*SPACE CASE*/
  if(strcmp(arg, "space")==0 || strcmp(arg, "s")==0){
    game->description = (char*) space_get_description(game_get_space(game, player_get_location(game->player[MAX_PLAYERS-1])));
    return OK;
  }

  /*OBJECT CASE*/
  else{
    if(arg == NULL){
      game->description = " ";
      return ERROR;
    }
    Object* obj = game_get_object_byName(game, arg);
    if(obj==NULL){
      game->description = " ";
      return ERROR;
    }
    if(player_has_object(game->player[0], obj_get_id(obj)) == FALSE && player_get_location(game->player[0]) != obj_get_location(obj)){
      return ERROR;
    }
    game->description = (char*) obj_get_description(obj);
    return OK;
  }
  return ERROR;
}
