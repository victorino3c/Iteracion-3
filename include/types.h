/**
 * @brief It defines common types for the whole project
 *
 * @file types.h
 * @author Miguel Soto, Nicolas Victorino, Antonio Van-Oers, Ignacio Nunez
 * @version 2.0
 * @date 02-04-2022
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

#define WORD_SIZE 1000    /*!< Establish the length for some strings */
#define NO_ID -1          /*!< Establish a non-defined id and its value is -1*/
#define MAX_ARG 20        /*!< Establish a length of command input arguments */

#define FD_ID_SPACE 1  /*!< First digit of a space. */
#define FD_ID_PLAYER 2 /*!< First digit of a player. */
#define FD_ID_OBJ 3    /*!< First digit of an object. */
#define FD_ID_ENEMY 4  /*!< First digit of an enemy. */

/**
 * @brief Ids
 */
typedef long Id;

/**
 * @brief Booleans (TRUE or FALSE)
 */
typedef enum
{
  FALSE,
  TRUE
} BOOL;

/**
 * @brief Status (OK or ERROR)
 */
typedef enum
{
  ERROR = 0,
  OK = 1
} STATUS;

/**
 * @brief Link's and space's directions (N, S, E, W or ND (not-defined))
 */
typedef enum
{
  ND = -1, /* !< Short for Not Defined */
  N,       /* !< Short for North */
  S,       /* !< Short for South */
  E,       /* !< Short for East */
  W        /* !< Short for West */
} DIRECTION;

#endif
