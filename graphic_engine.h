/**
 * @brief It defines the textual graphic engine interface
 *
 * @file graphic_engine.h
 * @author Profesores PPROG
 * @version 2.0
 * @date 29-11-2021
 * @copyright GNU Public License
 */

#ifndef __GRAPHIC_ENGINE__
#define __GRAPHIC_ENGINE__

#include "game.h"

/**
 * @brief Motor grafico
 *
 * Esta estructura contiene todos los punteros a los recursos necesarios que gestiona
 * el motor grafico como el mapa, help o feedback
 */
typedef struct _Graphic_engine Graphic_engine;

/**
  * @brief Crea el motor grafico 
  * @author Profesores PPROG
  *
  * graphic_engine_create inicializa la pantalla de juego con las dimensiones adecuadas
  * y reserva memoria para una variable ge del tipo Graphic_engine (motor grafico) 
  * e inicializa en las posiciones iniciales el mapa, el menu de ayuda y los otros elementos de la variable.
  * @return ge si todo sale bien y NULL si hubo un error en la reserva de memoria
  */
Graphic_engine *graphic_engine_create();

/**
  * @brief Destruye los elementos de ge
  * @author Profesores PPROG
  *
  * graphic_engine_destroy, llamando a las funciones de screen_area_destroy, 
  * destruye mapa, banner, descript, help y feedback 
  * Ademas libera la memoria que se habia reservado para ge
  * @param ge el puntero que apunta al motor grafico, otorga acceso a modificar sus componentes
  */
void graphic_engine_destroy(Graphic_engine *ge);

/**
  * @brief Dibuja el juego 
  * @author Profesores PPROG
  *
  * El motor grafico dibuja en la inerfaz los componentes del juego para que se visualicen
  * en la posicion correcta en la pantalla
  * @param ge el puntero que apunta al motor grafico, otorga acceso a modificar sus componentes
  * @param game es el puntero que apunta a game, que contiene los datos de localización de objeto y jugador 
  * junto con los espacios del juego y el ultimo comando
  */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game, int st);

/**
  * @brief Escribe el comando introducido en la interfaz grafica
  * @author Profesores PPROG
  *
  * @param ge el puntero que apunta al motor grafico, otorga acceso a modificar sus componentes
  * @param str el puntero que apunta a la cadena de caracteres introducida por el usuario.
  */
void graphic_engine_write_command(Graphic_engine *ge, char *str);

#endif
