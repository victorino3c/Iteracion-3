/** 
 * @brief Implementa la interfaz del objeto.
 * 
 * @file object.h
 * @author Miguel Soto
 * @version 1.3 
 * @date 12-02-2021
 * @copyright GNU Public License
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"

#define OBJ_NAME_LEN 40
#define MAX_OBJS 10

typedef struct _Object Object;


/**
 * @brief Crea un objeto nuevo.
 * @author Miguel Soto
 *
 * obj_create reserva memoria para un nuevo Object e inicializa sus miembros.
 * @param id el numero de identificacion del nuevo objeto a crear.
 * @return un nuevo objeto (tipo Object) inicializado, o NULL si hubo algun error.
 */
Object *obj_create(Id id);

/**
 * @brief Destruye un objeto.
 * @author Miguel Soto
 * 
 * obj_destroy libera la memoria previamente reservada de un objeto.
 * @param obj un puntero a Object que necesita ser destruido.
 * @return OK, si ha funcionado correctamente o ERROR, si hubo algun error.
 */
STATUS obj_destroy(Object *obj);

/**
 * @brief Comprueba si el id recibido es el de un objeto
 * @author Miguel Soto
 * 
 * @param id el id que se quiere comprobar
 * @return OK, si es correcto o ERROR si no es correcto o hubo algun error.
 */
STATUS obj_test_id(Id id);

/**
 * @brief Obtiene el id de un objeto.
 * @author Miguel Soto
 * 
 * obj_get_id devuelve el id de un Object (obj).
 * @param obj un puntero a Object.
 * @return el id del objeto, o NULL si hubo algun error.
 */
Id obj_get_id(Object *obj);

/**
 * @brief Obtiene el nombre de un objeto.
 * @author Miguel Soto
 * 
 * obj_get_name devuelve el nombre de un Object (obj).
 * @param obj un puntero a Object.
 * @return un string con el nombre del objeto obj, o NULL si hubo algun error.
 */
const char *obj_get_name(Object *obj);

/**
 * @brief Establece un nombre a un objeto.
 * @author Miguel Soto
 * 
 * obj_set_name establece el nombre (name) de un Object (obj).
 * @param obj un puntero a Object.
 * @param name un string con el nombre que se va a establecer al objeto.
 * @return OK, si ha funcionado correctamente o ERROR, si hubo algun error.
 */
STATUS obj_set_name(Object *obj, char *name);

/**
 * @brief Obtiene la posicion de un objeto
 * @author Miguel Soto
 * 
 * obj_get_location devuelve la posicion de un Object (obj)
 * @param obj un puntero a Object.
 * @return el id del espacio donde se encuentra el objeto
 */
Id obj_get_location(Object *obj);

/**
 * @brief Establece la posicion de un objeto
 * @author Miguel Soto
 * 
 * obj_set_location establece la posicion (location) de un Object (obj)
 * @param obj un puntero a Object.
 * @param id del espacio donde se va encontrar el objeto
 * @return OK, si ha funcionado correctamente o ERROR, si hubo algun error. 
 */
STATUS obj_set_location(Object *obj, Id id);

/**
 * @brief Imprime la informacion de un objeto.
 * @author Miguel Soto
 * 
 * obj_print muestra el id y el nombre de un Object (obj).
 * @param obj un puntero a Object.
 * @return OK, si ha funcionado correctamente o ERROR, si hubo algun error.
 */
STATUS obj_print(Object *obj);

#endif