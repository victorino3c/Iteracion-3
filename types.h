/**
 * @brief It defines common types for the whole project
 *
 * @file types.h
 * @author Profesores PPROG
 * @version 2.0
 * @date 29-11-2021
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

#define WORD_SIZE 1000
#define NO_ID -1
#define MAX_ARG 20

// Establecer norma primer digito (fd = first digit) de los ids
#define FD_ID_SPACE 1       /* <! Primer digito id del space */
#define FD_ID_PLAYER 2      /* <! Primer digito id del player */
#define FD_ID_OBJ 3         /* <! Primer digito id del object */
#define FD_ID_ENEMY 4       /* <! Primer digito id del enemy */



typedef long Id;

typedef enum
{
  FALSE,
  TRUE
} BOOL;

typedef enum
{
  ERROR,
  OK
} STATUS;

typedef enum
{
  N,    /* !< Abreviatura para Norte */
  S,    /* !< Abreviatura para Sur */
  E,    /* !< Abreviatura para Este */
  W     /* !< Abreviatura para Oeste */
} DIRECTION;

#endif
