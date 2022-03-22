/**
 * @file link.h
 * @author Miguel Soto, Antonio Van-Oers, Nicolas VIctorino and Nacho
 * @brief It defines the link functions between spaces
 * @version 0.1
 * @date 2022-03-17
 * 
 * @copyright Copyright (c) 2022
 */

#include "types.h"

#define LINK_NAME_LEN 40

typedef enum
{
    CLOSE = 0,
    OPEN = 1
} LINK_STATUS;

typedef struct _Link Link;

/**
 * @brief It allocs memory for a new link struct and initialize its members.
 * @author Miguel Soto
 * 
 * link_create allocs memory for a new link struct and initialize its members:
 * - direction = ND
 * - status = CLOSE
 * 
 * @param id The id of the new link.
 * @return a pointer to link, or NULL if there was some error.
 */
Link *link_create(Id id);

/**
 * @brief It frees the memory of a link's struct.
 * @author Miguel Soto
 * 
 * @param link a pointer to link that must be destroy
 * @return OK, if everything goes well or ERROR if there was some mistake.
 */
STATUS link_destroy(Link * link);

/**
 * @brief It gets link's id.
 * @author Miguel Soto
 * 
 * @param link a pointer to link.
 * @return link's id or NO_ID if there was some error.
 */
Id link_get_id(Link *link);

/**
 * @brief It sets a name to a link.
 * @author Miguel Soto
 * 
 * @param link a pointer to link.
 * @param name string with link's new name.
 * @return OK, if everything goes well or ERROR if there was some mistake.
 */
STATUS link_set_name(Link *link, char *name);

/**
 * @brief It gets link's name.
 * @author Miguel Soto
 * 
 * @param link a pointer to link.
 * @return string with link's name or NULL if there was some error.
 */
char *link_get_name(Link *link);

/**
 * @brief 
 * @author
 * 
 * @param link 
 * @param id_space_dest 
 * @return STATUS 
 */
STATUS link_set_destination(Link *link, Id id_space_dest);

/**
 * @brief 
 * @author
 * 
 * @param link 
 * @return Id 
 */
Id link_get_destination(Link *link);

/**
 * @brief 
 * @author
 * 
 * @param link 
 * @param dir 
 * @return STATUS 
 */
STATUS link_set_direction(Link *link, DIRECTION dir);

/**
 * @brief 
 * @author
 * 
 * @param link 
 * @return DIRECTION 
 */
DIRECTION link_get_direction(Link *link);

/**
 * @brief 
 * @author
 * 
 * @param link 
 * @param st 
 * @return STATUS 
 */
STATUS link_set_status(Link *link, LINK_STATUS st);

/**
 * @brief 
 * @author
 * 
 * @param link 
 * @return LINK_STATUS 
 */
LINK_STATUS link_get_status(Link *link);

/**
 * @brief It prints link and its elements for debugging porpuses.
 * @author MIguel Soto
 * 
 * @param link a ponter to link struct
 * @return the number of characters written or -1 in caseof error.
 */
int link_proint(Link *link);