/**
 * @brief It defines the space interface
 *
 * @file space.h
 * @author Profesores PPROG
 * @version 2.0
 * @date 29-11-2021
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "set.h"
#include "types.h"
#include "object.h"

typedef struct _Space Space;

#define MAX_SPACES 100
#define FIRST_SPACE 1

#define TAM_GDESC_Y 5
#define TAM_GDESC_X 9

/**
  * @brief It creates a new space
  * @author Profesores PPROG
  *
  * space_create allocates memory for a new space
  *  and initializes its members
  * @param id the identification number for the new space
  * @return a new space, initialized
  */
Space* space_create(Id id);

/**
  * @brief It destroys a space
  * @author Profesores PPROG
  *
  * space_destroy frees the previous memory allocation 
  *  for a space
  * @param space a pointer to the space that must be destroyed  
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS space_destroy(Space* space);

/**
  * @brief It gets the id of a space
  * @author Profesores PPROG
  * 
  * @param space a pointer to the space  
  * @return the id of space
  */
Id space_get_id(Space* space);

/**
 * @brief Comprueba si el id recibido es el de un espacio
 * @author Miguel Soto
 * 
 * @param id el id que se quiere comprobar
 * @return OK, si es correcto o ERROR si no es correcto o hubo algun error.
 */
STATUS space_test_id(Id id);

/**
  * @brief It sets the name of a space
  * @author Profesores PPROG
  * 
  * @param space a pointer to the space
  * @param name a string with the name to store
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS space_set_name(Space* space, char* name);

/**
  * @brief It gets the name of a space
  * @author Profesores PPROG
  * 
  * @param space a pointer to the space
  * @return  a string with the name of the space
  */
const char* space_get_name(Space* space);

/**
  * @brief It sets the id of the space located at the north
  * @author Profesores PPROG
  * 
  * @param space a pointer to the space
  * @param id the id number of the space located at the north
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS space_set_north(Space* space, Id id);
/**
  * @brief It gets the id of the space located at the north
  * @author Profesores PPROG
  *
  * @param space a pointer to the space
  * @return the id number of the space located at the north 
  */
Id space_get_north(Space* space);

/**
  * @brief It sets the id of the space located at the south
  * @author Profesores PPROG
  *
  * @param space a pointer to the space
  * @param id the id number of the space located at the south
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS space_set_south(Space* space, Id id);
/**
  * @brief It gets the id of the space located at the south
  * @author Profesores PPROG
  *
  * @param space a pointer to the space
  * @return the id number of the space located at the south 
  */
Id space_get_south(Space* space);

/**
  * @brief It sets the id of the space located at the east
  * @author Profesores PPROG
  *
  * @param space a pointer to the space
  * @param id the id number of the space located at the east
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS space_set_east(Space* space, Id id);
/**
  * @brief It gets the id of the space located at the east
  * @author Profesores PPROG
  *
  * @param space a pointer to the space
  * @return the id number of the space located at the east
  */
Id space_get_east(Space* space);

/**
  * @brief It sets the id of the space located at the west
  * @author Profesores PPROG
  *
  * @param space a pointer to the space
  * @param id the id number of the space located at the west
  * @return OK, if everything goes well or ERROR if there was some mistake 
  */
STATUS space_set_west(Space* space, Id id);
/**
  * @brief It gets the id of the space located at the west
  * @author Profesores PPROG
  *
  * @param space a pointer to the space
  * @return the id number of the space located at the west
  */
Id space_get_west(Space* space);

/**
 * @brief It add an object id in the space's set of objects
 * @author Miguel Soto
 * 
 * @param s a pointer to the space 
 * @param id from an object that wants to be added.
 * @return OK, if everything goes well or ERROR if there was some mistake 
 */
STATUS space_add_objectid(Space *s, Id id);

/**
 * @brief It deletes an object id in the space's set of objects
 * @author Miguel Soto
 * 
 * @param s a pointer to the space 
 * @param id from an object that wants to be added.
 * @return OK, if everything goes well or ERROR if there was some mistake 
 */
STATUS space_del_objectid(Space *s, Id id);

/**
  * @brief It gets a pointer to the set of objects in a space
  * @author Miguel Soto
  *
  * @param space a pointer to the space
  * @return a pointer to Set with all objects id that are in that space or NULL if there was an error
  */
Set *space_get_objects(Space* space);

/**
  * @brief It gets a pointer to the id array of a set of objects that are in that space
  * @author Miguel Soto
  *
  * @param space a pointer to the space
  * @return a pointer to Id with all objects id that are in that spacea or NULL if there was an error
  */
Id *space_get_objects_ids(Space* space);

/**
 * @brief It gets if there is an object with id id in a space s.
 * @author Miguel Soto
 * 
 * @param s a pointer to space
 * @param id of an object
 * @return TRUE if object is in space or FLASE if object is not in space. Returns FALSE if there has been an error.
 */
BOOL space_has_object(Space *s, Id id);

/**
 * @brief It alloc memory for the space_gdesc
 * @author Miguel Soto
 * 
 * @return double pointer to char to the newgdesc or NULL if there has been an error
 */
char **space_create_gdesc();

/**
 * @brief It frees memory for the space_gdesc
 * @author Miguel Soto
 * 
 * @param s pointer to space that gdesc must be destroy
 * @return OK, if everything goes well or ERROR if there was some mistake 
 */
STATUS space_destroy_gdesc(char **gdesc);

/**
 * @brief It sets the graphic description of a space
 * @author Miguel Soto
 * 
 * @param s a pointer to space
 * @param newgdesc a double char array with the graphical description
 * @return OK, if everything goes well or ERROR if there was some mistake 
 */
STATUS space_set_gdesc(Space *s, char **newgdesc);

/**
 * @brief It gets the graphic description from a space
 * @author Miguel Soto
 * 
 * @param s a pointer to space
 * @return a double char array with the graphical description, or NULL if there was some error.
 */
char **space_get_gdesc(Space *s);

/**
  * @brief It prints the space information
  * @author Profesores PPROG
  *
  * This fucntion shows the id and name of the space, the spaces that surrounds it and wheter it has an object or not.
  * @param space a pointer to the space
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
STATUS space_print(Space* space);

#endif
