/** 
 * @brief Implementa la interfaz del enemigo.
 * 
 * @file enemy.h
 * @author Antonio Van-Oers
 * @version 1.2
 * @date 12-02-2021
 * @copyright GNU Public License
 */

#ifndef ENEMY_H
#define ENEMY_H

#include "types.h"

#define Enemy_Name_lenght 60
#define MAX_ENEMYS 10

typedef struct _Enemy Enemy;


/**
 * @brief Crea un enemigo nuevo.
 * @author Antonio Van-Oers 
 *
 * enemy_create reserva memoria para un nuevo enemy e inicializa sus campos.
 * @param id el numero de identificacion del nuevo enemigo a crear.
 * @return un nuevo enemigo (tipo enemy) inicializado, o NULL si hubo algun error.
 */
Enemy *enemy_create(Id id);

/**
 * @brief Destruye un enemigo.
 * @author Antonio Van-Oers 
 * 
 * enemy_destroy libera la memoria previamente reservada de un enemigo.
 * @param enemy un puntero a enemy que necesita ser destruido.
 * @return OK, si ha funcionado correctamente o ERROR, si hubo algun error.
 */
STATUS enemy_destroy(Enemy *enemy);

/**
 * @brief Obtiene el id de un enemigo.
 * @author Antonio Van-Oers
 * 
 * enemy_get_id devuelve el id de un enemigo(enemy).
 * @param enemy un puntero a enemy.
 * @return el id del enemigo, o NULL si hubo algun error.
 */
Id enemy_get_id(Enemy *enemy);

/**
 * @brief Comprueba si el id recibido es el de un enemy
 * @author Miguel Soto
 * 
 * @param id el id que se quiere comprobar
 * @return OK, si es correcto o ERROR si no es correcto o hubo algun error.
 */
STATUS enemy_test_id(Id id);

/**
 * @brief Obtiene el nombre de un enemigo.
 * @author Antonio Van-Oers
 * 
 * enemy_get_name devuelve el nombre de un enemigo (enemy).
 * @param enemy un puntero a enemy.
 * @return un string con el nombre del enemigo enemy, o NULL si hubo algun error.
 */
const char *enemy_get_name(Enemy *enemy);

/**
 * @brief Obtiene el nombre de un enemigo.
 * @author Antonio Van-Oers
 * 
 * enemy_get_location obtiene la localizacion de un enemigo (enemy).
 * @param enemy un puntero a enemy.
 * @return enemy->location, la id de la localizacion de un enemigo (enemy).
 */
Id enemy_get_location(Enemy *enemy);

/**
 * @brief Obtiene la salud de un enemigo.
 * @author Antonio Van-Oers
 * 
 * enemy_get_health obtiene la salud de un enemigo (enemy).
 * @param enemy un puntero a enemy.
 * @return enemy->health, obtiene la salud restante de un enemigo (enemy)
 * y -1 en caso de error.
 */
int enemy_get_health(Enemy *enemy);

/**
 * @brief Establece la salud de un enemigo.
 * @author Antonio Van-Oers
 * 
 * enemy_set_health establece la salud de un enemigo (enemy).
 * @param enemy un puntero a enemy.
 * @param health es un entero con la salud del enemigo
 * @return OK, si ha funcionado correctamente o ERROR, si hubo algun error.
 */
STATUS enemy_set_health(Enemy *enemy, int health);

/**
 * @brief Establece el nombre de un enemigo.
 * @author Antonio Van-Oers
 * 
 * enemy_set_location establece la localizacion de un enemigo (enemy).
 * @param enemy un puntero a enemy.
 * @param location es la identificacion del espacio en el que esta el enemigo.
 * @return OK, si ha funcionado correctamente o ERROR, si hubo algun error.
 */
STATUS enemy_set_location(Enemy *enemy, Id location);

/**
 * @brief Establece un nombre a un enemigo.
 * @author Antonio Van-Oers
 * 
 * obj_set_name establece el nombre (name) de un enemigo (enemy).
 * @param enemy un puntero a enemy.
 * @param name un string con el nombre que se va a establecer al enemigo.
 * @return OK, si ha funcionado correctamente o ERROR, si hubo algun error.
 */
STATUS enemy_set_name(Enemy *enemy, char *name);

/**
 * @brief Imprime la informacion de un enemigo.
 * @author Antonio Van-Oers
 * 
 * obj_print muestra el id y el nombre de un enemigo (enemy).
 * @param enemy un puntero a enemy.
 * @return OK, si ha funcionado correctamente o ERROR, si hubo algun error.
 */
STATUS enemy_print(Enemy *enemy);

#endif
