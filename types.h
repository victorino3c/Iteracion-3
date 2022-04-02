/**
 * @brief It defines common types for the whole project
 *
 * @file types.h
 * @author Miguel Soto, Nicolas Victorino, Antonio Van-Oers, Ignacio Nunez
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
#define FD_ID_SPACE 1  /* <! First digit of a space  */
#define FD_ID_PLAYER 2 /* <! First digit of a player  */
#define FD_ID_OBJ 3    /* <! First digit of an object*/
#define FD_ID_ENEMY 4  /* <! First digit of an enemy*/

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
  ND = -1, /* !< Short for Not Defined */
  N,       /* !< Short for North */
  S,       /* !< Short for South */
  E,       /* !< Short for East */
  W        /* !< Short for West */
} DIRECTION;

#endif
