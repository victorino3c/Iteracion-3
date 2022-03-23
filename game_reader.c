/** 
 * @brief Se encarga de la carga de espacios
 * 
 * @file game_reader.c
 * @author Miguel Soto
 * @version 1.1
 * @date 12-02-2022
 * @copyright GNU Public License
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "game_reader.h"

STATUS game_add_space(Game *game, Space *space);
STATUS game_add_object(Game *game, Object *obj);
STATUS game_add_player(Game *game, Player *p);
STATUS game_add_enemy(Game *game, Enemy *e);
Id game_get_space_id_at(Game *game, int position);
STATUS game_set_player_location(Game *game, Id player_id, Id space_id);
STATUS game_set_object_location(Game *game, Id obj_id, Id space_id);
STATUS game_set_enemy_location(Game *game, Id enemy_id, Id space_id);

/**
  Funciones privadas
*/
STATUS game_load_spaces(Game *game, char *filename);
STATUS game_load_objs(Game *game, char *filename);
STATUS game_load_players(Game *game, char *filename);
STATUS game_load_enemy(Game *game, char *filename);

GAME_IS_ELEMENT id_type(Id id);

/**
  Game_reader implementacion
*/

/** game_create_from_file inicializa la localizacion 
  * del jugador y el objeto a 0, situandolos en el primer espacio
  */
STATUS game_create_from_file(Game *game, char *filename)
{

  if (game_create(game) == ERROR)
  {
    return ERROR;
  }
  
  if (game_load_spaces(game, filename) == ERROR)
  {
    return ERROR;
  }

  if (game_load_objs(game, filename) == ERROR)
  {
    return ERROR;
  }

  if (game_load_players(game, filename) == ERROR)
  {
    return ERROR;
  } 

  if (game_load_enemy(game, filename) == ERROR)
  {
    return ERROR;
  } 

  /* The player and the object are located in the first space */

  return OK;
}

/**
  * @brief Loads the spaces of the game
  * @author Profesores PPROG
  *
  * @param game pointer to the game
  * @param filename pointer to the file from where spaces are being loaded
  * @return OK if everything goes right ERROR if something goes wrong
  */
STATUS game_load_spaces(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL, *aux;
  char **gdesc = NULL;
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
  Space *space = NULL;
  STATUS status = OK;
  int i, j;

  if (!filename)
  {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL)
  {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#s:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      north = atol(toks);
      toks = strtok(NULL, "|");
      east = atol(toks);
      toks = strtok(NULL, "|");
      south = atol(toks);
      toks = strtok(NULL, "|");
      west = atol(toks);

      gdesc = space_create_gdesc();
      if (gdesc == NULL)
      {
        return ERROR;
      }
      
      for (i = 0; i < TAM_GDESC_Y; i++)
      {
        aux = strtok(NULL, "|");
        for (j = 0; j < strlen(aux) && j < TAM_GDESC_X; j++)
        {
          gdesc[i][j] = aux[j];
        }
      }
      
      

#ifdef DEBUG
      //printf("Leido: %ld|%s|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west);
#endif
      space = space_create(id);
      if (space != NULL)
      {
        space_set_name(space, name);
        space_set_north(space, north);
        space_set_east(space, east);
        space_set_south(space, south);
        space_set_west(space, west);
        space_set_gdesc(space, gdesc);
        game_add_space(game, space);
      }
    }
  }

  if (ferror(file))
  {
    status = ERROR;
  }

  fclose(file);

  return status;
}

/**
  * @brief Carga los objetos del juego
  * @author Miguel Soto
  *
  * game_load_objs carga la info de los objetos creados
  * @param game es el puntero que apunta a game
  * @param filename es el puntero que apunta al nombre del fichero 
  * @return OK si todo va bien y ERROR si ha habido algun fallo de carga
  */
STATUS game_load_objs(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, pos = NO_ID;
  Object *obj = NULL;
  STATUS status = OK;

  if (!filename)
  {
    return ERROR;
  }
   
  file = fopen(filename, "r");
  if (file == NULL)
  {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#o:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      pos = atol(toks);

#ifdef DEBUG
      //printf("Leido: %ld|%s|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west);
#endif
      obj = obj_create(id);
      if (obj != NULL)
      {
        obj_set_name(obj, name);
        obj_set_location(obj, pos);
        if (space_add_objectid(game_get_space(game, pos), id) == ERROR)
        {
          return ERROR;
        }
        game_add_object(game, obj);
      }
    }
  }

  if (ferror(file))
  {
    status = ERROR;
  }

  fclose(file);

  return status;
}

/**
  * @brief Loads the player into the game
  * @author Nicolas Victorino
  *
  * @param game pointer to game
  * @param filename pointer to the file from where it is going to load the player
  * @return OK if everything is right ERROR if something went wrong
  */
STATUS game_load_players(Game *game, char *filename) 
{
 FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, object = NO_ID, location = NO_ID;;
  Player *player = NULL;
  STATUS status = OK;

  /*Error control*/
  if (!filename)
  {
    return ERROR;
  }

  /*Error control*/
  file = fopen(filename, "r");
  if (file == NULL)
  {
    return ERROR;
  }

  
  /*
  * While the loop reads information in the current line from the file: "hormiguero.dat", it divides that line in smaller tokens.
  * Each token has a piece of information, in the following order:
  * ID of the player, name, Id of the object that the player has (NO_ID if it has no object), and location.
  */
  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#p:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      object = atol(toks);
      toks = strtok(NULL, "|");
      location = atol(toks);

  /*If debug is being used, it will print all the information from the current player that is being loaded*/
#ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%ld\n", id, name, objet, location);
#endif

  /*Defines a private variable called "player" and saves a pointer to player with the given id in it*/
      player = player_create(id);

  /*Error control, and in case everything is fine, it saves the information gotten in the prior loop in the newly created player*/
      if (player != NULL)
      {
        player_set_name(player, name);
        player_set_object(player, game_get_object(game, object));
        player_set_location(player, location);
        player_set_health(player, 3); //Añadir MAX_HEALTH_PLAYER
        game_add_player(game, player); 
      } 
    }
  }

  /*Error control, if it has given an error at any moment while using the file, ferror while make the if condition be true.
   This will change the private status variable declared at the beggining of the function from OK to ERROR. */
  if (ferror(file))
  {
    status = ERROR;
  }

  fclose(file);

  return status;
}

/**
  * @brief Loads the enemy into the game
  * @author Nicolas Victorino
  *
  * @param game pointer to game
  * @param filename pointer to the file from where it is going to load the enemy
  * @return OK if everything is right ERROR if something went wrong
  */
STATUS game_load_enemy(Game *game, char *filename) 
{
 FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, location = NO_ID;;
  Enemy *enemy = NULL;
  STATUS status = OK;

  /*Error control*/
  if (!filename)
  {
    return ERROR;
  }

  /*Error control*/
  file = fopen(filename, "r");
  if (file == NULL)
  {
    return ERROR;
  }

  
  /*
  * While the loop reads information in the current line from the file: "hormiguero.dat", it divides that line in smaller tokens.
  * Each token has a piece of information, in the following order:
  * ID of the enemy, name, and location.
  */
  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#e:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      location = atol(toks);

  /*If debug is being used, it will print all the information from the current enemy that is being loaded*/
#ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%ld\n", id, name, objet, location);
#endif

  /*Defines a private variable called "enemy" and saves a pointer to player with the given id in it*/
      enemy = enemy_create(id);

  /*Error control, and in case everything is fine, it saves the information gotten in the prior loop in the newly created enemy*/
      if (enemy != NULL)
      {
        enemy_set_name(enemy, name);
        enemy_set_location(enemy, location);
        enemy_set_health(enemy, 3); //Añadir MAX_HEALTH_ENEMY
        game_add_enemy(game, enemy); 
      } 
    }
  }

  /*Error control, if it has given an error at any moment while using the file, ferror while make the if condition be true.
   This will change the private status variable declared at the beggining of the function from OK to ERROR. */
  if (ferror(file))
  {
    status = ERROR;
  }

  fclose(file);

  return status;
}


/**
 * @brief Indica de que elemento del juego es el id
 * @author Miguel Soto
 * 
 * @param id que se quiere clasificar
 * @return elemento del juego del que es el id
 */
GAME_IS_ELEMENT id_type(Id id)
{
  int first_digit, digits;

  if (id < 0)
  {
    return '\0';
  }

  digits = (int)log10(id); 

  first_digit = (int)(id / pow(10, digits));
  
  if (first_digit == FD_ID_SPACE)
  {
    return IS_SPACE;
  }
  else if (first_digit == FD_ID_PLAYER)
  {
    return IS_PLAYER;
  }
  else if (first_digit == FD_ID_OBJ)
  {
    return IS_OBJECT;
  }
  else if (first_digit == FD_ID_ENEMY)
  {
    return IS_ENEMY;
  }
  else
  {
    return '\0';
  }
}
