/** 
 * @brief It implements the space module
 * 
 * @file space.c
 * @author Profesores PPROG
 * @version 2.0 
 * @date 29-11-2021 
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "space.h"


/**
 * @brief Space
 *
 * This struct stores all the information of a space.
 */
struct _Space {
  Id id;                                    /*!< Id number of the space, it must be unique */
  char name[WORD_SIZE + 1];                 /*!< Name of the space */
  char description[WORD_SIZE];              /*!< Description of the space*/
  Id north;                                 /*!< Id of the space at the north */
  Id south;                                 /*!< Id of the space at the south */
  Id east;                                  /*!< Id of the space at the east */
  Id west;                                  /*!< Id of the space at the west */
  Set *objects;                             /*!< Conjunto de ids de los objetos que se encuentran en el espacio */
  char **gdesc;                             /*!< Array de 5 strings de 9 caracteres */
};

/** space_create allocates memory for a new space
  *  and initializes its members
  */
Space* space_create(Id id) {
  Space *newSpace = NULL;

  /* Error control */
  if (id == NO_ID)
    return NULL;

  newSpace = (Space *) malloc(sizeof (Space));
  if (newSpace == NULL) {
    return NULL;
  }

  /* Initialization of an empty space*/
  newSpace->id = id;
  newSpace->name[0] = '\0';
  newSpace->north = NO_ID;
  newSpace->south = NO_ID;
  newSpace->east = NO_ID;
  newSpace->west = NO_ID;
  newSpace->objects = set_create();
  newSpace->gdesc = NULL;

  return newSpace;
}

/** space_destroy frees the previous memory allocation 
  *  for a space
  */
STATUS space_destroy(Space* space) 
{
  // Error control
  if (!space) {
    return ERROR;
  }

  if (space->objects)
  {
    set_destroy(space->objects);
    space->objects = NULL;
  }

  
  if (space->gdesc)
  {
    if (space_destroy_gdesc(space->gdesc) == ERROR)
    {
      /*printf("ERROR liberando memoria gdesc\n");*/
    }
  }
  
 
  free(space);
  space = NULL;
  return OK;
}

/** It gets the id of a space
  */
Id space_get_id(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->id;
}

/**
 * Comprueba si el id recibido es el de un espacio
 */
STATUS space_test_id(Id id)
{
  int first_digit, digits;

  // Control de errores
  if (id < 0)
  {
    return ERROR;
  }

  // Calcular numbero total de digitos - 1
  digits = (int)log10(id); 

  // Obtener primer digito
  first_digit = (int)(id / pow(10, digits));
  
  if (first_digit == FD_ID_SPACE)
  {
    return OK;
  }
  else
  {
    return ERROR;
  }
}

/** It sets the name of a space
  */
STATUS space_set_name(Space* space, char* name) {
  if (!space || !name) {
    return ERROR;
  }

  if (!strcpy(space->name, name)) {
    return ERROR;
  }
  return OK;
}
/** It gets the name of a space
  */
const char * space_get_name(Space* space) {
  if (!space) {
    return NULL;
  }
  return space->name;
}

/** space_get_description returns the description of a space.
 */
const char *space_get_description(Space *space)
{
	/*CONTROL ERRORS*/
  if (!space)
  {
    return NULL;
  }
  
  return space->description;
}

/** space_set_description set a new description for an space.
 */
STATUS space_set_description(Space *space, char *description)
{
	/* CONTROL ERROR */
  if (!space || !description)
  {
    return ERROR;
  }
  
  if (!strcpy(space->description, description))
  {
    /*CONTROL ERROR*/
    return ERROR;
  }
  
  return OK;

}

/** It sets the id of the space located at the north
  */
STATUS space_set_north(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->north = id;
  return OK;
}
/** It gets the id of the space located at the north
  */
Id space_get_north(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->north;
}

/** It sets the id of the space located at the south
  */
STATUS space_set_south(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->south = id;
  return OK;
}
/** It gets the id of the space located at the south
  */
Id space_get_south(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->south;
}

/** It sets the id of the space located at the east
  */
STATUS space_set_east(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->east = id;
  return OK;
}
/** It gets the id of the space located at the east
  */
Id space_get_east(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->east;
}

/** It sets the id of the space located at the west
  */
STATUS space_set_west(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->west = id;
  return OK;
}
/** It gets the id of the space located at the west
  */
Id space_get_west(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->west;
}

/**
 * It add an object id in the space's set of objects
 */
STATUS space_add_objectid(Space *s, Id id)
{
  // Error control
  if (!s || !id)
  {
    return ERROR;
  }
  
  if (!set_add(s->objects, id))
  {
    return ERROR;
  }

  return OK;
}

/**
 * It deletes an object id in the space's set of objects
 */
STATUS space_del_objectid(Space *s, Id id)
{
  // Error control
  if (!s || !id)
  {
    return ERROR;
  }
  
  if (!set_del_id(s->objects, id))
  {
    return ERROR;
  }
  
  return OK;
}

/** 
 * It gets a pointer to the set of objects in a space
 */
Set *space_get_objects(Space *space)
{
  // Error control
  if (!space) {
    return NULL;
  }
  return space->objects;
}

/**
 * It gets a pointer to the id array of a set of objects that are in that space
 */
Id *space_get_objects_ids(Space *s)
{
  // Error control
  if (!s)
  {
    return NULL;
  }
  
  return set_get_ids(space_get_objects(s));
}

/**
 * It sets the graphic description of a spaces.
 */
BOOL space_has_object(Space *s, Id id)
{
  Id *ids = NULL;
  BOOL b = FALSE;
  int i;

  // Error control
  if (!s)
  {
    return FALSE;
  }
  
  ids = set_get_ids(s->objects);
  if (ids == NULL)
  {
    return FALSE;
  }
  
  for (i = 0; (i < set_get_nids(s->objects)) && (b == FALSE); i++)
  {
    if (*(ids+i) == id)
    {
      b = TRUE;
    }
  }
  
  return b;
}

char **space_create_gdesc()
{
  char **newgdesc = NULL;
  int i, j;

  newgdesc = (char **) malloc((TAM_GDESC_Y+1) * sizeof(char *));
  if (!newgdesc)
  {
    return NULL;
  }
  for (i = 0; i < (TAM_GDESC_Y+1); i++)
  {
    newgdesc[i] = NULL;
    newgdesc[i] = (char *) malloc((TAM_GDESC_X+2) * sizeof(char));
    if (!newgdesc[i])
    {
      return NULL;
    }
    
    for (j = 0; j < (TAM_GDESC_X+2); j++)
    {
      newgdesc[i][j] = '\0';
    }
    
  }

  return newgdesc;
}


STATUS space_destroy_gdesc(char **gdesc)
{
  int i;

  // Error control
  if (!gdesc)
  {
    return ERROR;
  }
  
  if (gdesc)
  {
    for (i = TAM_GDESC_Y; i >= 0; i--)
    {
      if (gdesc[i])
      {
        free(gdesc[i]);
        gdesc[i] = NULL;
      }
    }

    free(gdesc);
    gdesc = NULL;
  }

  return OK;
}


/**
 * It gets the graphic description from a space.
 */
STATUS space_set_gdesc(Space *s, char **newgdesc)
{
  // Error control
  if (!s || !newgdesc)
  {
    return ERROR;
  }

  s->gdesc = newgdesc;

  return OK;
}

char **space_get_gdesc(Space *s)
{
  // Error control
  if (!s)
  {
    return NULL;
  }

  return s->gdesc;
}

/** It prints the space information
  */
STATUS space_print(Space* space) {
  Id idaux = NO_ID;
  int nobj, i, j;

  /* Error Control */
  if (!space) {
    return ERROR;
  }

  /* 1. Print the id and the name of the space */
  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);
 
  /* 2. For each direction, print its link */ 
  idaux = space_get_north(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> North link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No north link.\n");
  }
  idaux = space_get_south(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> South link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No south link.\n");
  }
  idaux = space_get_east(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> East link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No east link.\n");
  }
  idaux = space_get_west(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> West link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No west link.\n");
  }

  /* 3. Print if there is an object in the space or not */
  nobj = set_get_nids(space_get_objects(space));
  if (nobj > 0) {
    fprintf(stdout, "---> %d objects in the space.\n", nobj);
  } else {
    fprintf(stdout, "---> No object in the space.\n");
  }

  // 4. Print gdesc
  printf("=> Gdesc:\n");
  for (i = 0; i < TAM_GDESC_Y && space->gdesc[i]; i++)
  {
    for (j = 0; j < TAM_GDESC_X && space->gdesc[i][j]; j++)
    {
      printf("%c", space->gdesc[i][j]);
    }
    printf("\n");
    if (j != TAM_GDESC_X)
    {
      printf("ERROR IMPRIMIENDO space->gdesc[%d][%d] = NULL\n", i, j);
    }
  }
  
  return OK;
}
