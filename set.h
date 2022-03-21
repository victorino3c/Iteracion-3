/** 
 * @brief Integra la funcionalidad necesaria para el manejo de conjuntos.
 * 
 * @file set.h
 * @author Miguel Soto
 * @version 2.0
 * @date 08-03-2022 
 * @copyright GNU Public License
 */

#ifndef SET_H
#define SET_H

#include <stdlib.h>
#include <stdio.h>
#include "types.h"

typedef struct _Set Set;

/**
 * @brief Reserva memoria para un nuevo set.
 * @author Miguel Soto
 * 
 * set_create reserva memoria para un nuevo set, e
 * inicializa sus miembros.
 *  
 * @return un puntero a Set inicializado o NULL si ha habido algun error.
 */
Set *set_create();

/**
 * @brief Libera memoria de un tipo de dato set.
 * @author Miguel Soto
 * 
 * set_destroy libera la memoria de un set y todos sus miembros.
 * 
 * @param set un puntero a Set que se quiere liberar.
 * @return OK si ha funcionado correctamente, o ERROR si ha habido algun error.
 */
STATUS set_destroy(Set *s);

/**
 * @brief Añade un id al set.
 * @author Miguel Soto
 * 
 * set_add amplia el numero de ids guardados en el set 
 * y guarda el nuevo id en la ultima posicion.
 * 
 * @param s un puntero a Set del que se quiere añadir a un id.
 * @param id el id que se quiere añadir al set
 * @return OK si ha funcionado correctamente, o ERROR si ha habido algun error.
 */
STATUS set_add(Set *s, Id id);

/**
 * @brief Elimina un id del set
 * @author Miguel Soto
 * 
 * set_del_id busca un id dentro del set y lo elimina.
 * 
 * @param s un puntero a Set del que se quiere eliminar un id.
 * @param id el id que se quiere añadir al set
 * @return OK si ha funcionado correctamente, o ERROR si ha habido algun error.
 */
STATUS set_del_id(Set *s, Id id);

/**
 * @brief Elimina un id del set por la posicion en la que se encuentra.
 * @author Miguel Soto
 * 
 * set_del_pos elimina un id dentro del set a traves de la posicion que tenga dentro del set.
 * 
 * @param s un puntero a Set del que se quiere eliminar un id.
 * @param pos la pos en el Set s del id que se quiere eliminar.
 * @return OK si ha funcionado correctamente, o ERROR si ha habido algun error. 
 */
STATUS set_del_pos(Set *s, int pos);

/**
 * @brief Devuelve el numero de ids en un set
 * @author Miguel Soto
 * 
 * @param s un puntero a Set del que se quiere obtener el numero de ids
 * @return int con el numero de ids en un set. En caso de error devuelve -1.
 */
int set_get_nids(Set *s);

/**
 * @brief Devuelve un array con todos los ids del set
 * @author Miguel Soto
 * 
 * @param s un puntero a Set del que se quiere obtener la lista de ids
 * @return un puntero a Id con todos los ids guardados en un set.
 */
Id *set_get_ids(Set *s);

/**
 * @brief Comprueba si un set esta bien definido
 * @author Miguel Soto
 * 
 * Comprueba:
 * - s no es NULL
 * - No haya id == NO_ID
 * - El numero de ids incluido es igual al guardado en la variable
 * - Numero de ids no sea negativo
 * 
 * @param s un puntero a Set que se quiere comprobar si esta bien definido.
 * @return OK si esta bien definido o ERROR si ha encontrado algun error.
 */
STATUS set_test(Set *s);

/**
 * @brief Imprime toda la informacion de un set
 * 
 * @param s puntero a Set que se quiere imprimir
 * @return int el numero de caracteres que imprime
 */
int set_print(Set *s);

#endif