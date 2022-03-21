/** 
 * @brief Integra la funcionalidad necesaria para el manejo de conjuntos.
 * 
 * @file set.c
 * @author Miguel Soto
 * @version 2.0
 * @date 08-03-2022 
 * @copyright GNU Public License
 */

#include "set.h"

struct _Set
{
    Id *ids;            /* !< Array de ids dentro del set */
    int n_ids;          /* !< Longitud del array ids */
};

/**
 * Funciones privadas
 */
STATUS reorder_set_ids(Set *s, int pos);


/**
 * @brief Elimina el hueco que hay en el conjunto de Sets
 * y lo sustituye por el ultimo id. No hace realloc.
 * @author Miguel Soto
 * 
 * Elimina el hueco que hay en el conjunto de Sets
 * y lo sustituye por el ultimo id. No hace realloc.
 * Si se entrega un s vacio devuelve ERROR.
 * 
 * @param s un puntero a set del que se quiere ordenar los ids.
 * @param pos la posición de un NO_ID conocida.
 * @return OK si ha funcionado correctamente, o ERROR si ha habido algun error.
 */
STATUS reorder_set_ids(Set *s, int pos)
{
    int i;

    /*Error control*/
    if (!s || pos < 0 || pos >= s->n_ids || s->n_ids == 0)
    {
        return ERROR;
    }
    
    for (i = pos; i < s->n_ids; i++)
    {
        if (s->ids[i] == NO_ID)
        {      
            s->ids[i] = s->ids[s->n_ids-1];
        }
        
    }
    
    return OK;
}

/**
 * Funciones primitivas
 */


/**
 * Reserva memoria para un nuevo set e
 * inicializa sus miembros.
 */
Set *set_create()
{
    Set *new_set = NULL;    

    new_set = (Set *) malloc(sizeof(Set));
    if (!new_set)
    {
        return NULL;
    }
    
    // Reserva memoria para los ids
    new_set->ids = NULL;
    new_set->n_ids = 0;

    return new_set;
}

/**
 * Libera la memoria de un set y todos sus miembros.
 */
STATUS set_destroy(Set *s)
{
    /*Error control*/
    if (!s)
    {
        return ERROR;
    }
    
    if (s->ids)
    {
        free(s->ids);
    }
    
    free(s);
    s = NULL;
    
    return OK;
}

/**
 * Añade un id al set.
 */
STATUS set_add(Set *s, Id id)
{
    Id *aux = NULL;
    int newlength;

    /*Error control*/
    if (!s || id == NO_ID)
    {
        return ERROR;
    }
    
    /* Amplia el numero de ids guardado en el set*/
    newlength = s->n_ids + 1;
    aux = (Id *) realloc(s->ids, newlength * sizeof(Id));
    if (!aux)
    {
        return ERROR;
    }
    s->ids = aux;
    aux = NULL;

    s->ids[newlength-1] = id;
    s->n_ids++;

    return OK;
}

/**
 * Busca un id dentro del set y lo elimina.
 */
STATUS set_del_id(Set *s, Id id)
{
    int i, k;
    Id *aux = NULL;
    
    /*Error control*/
    if (!s || id == NO_ID || s->n_ids == 0)
    {
        return ERROR;
    }
    
    for (i = 0, k = 0; i < s->n_ids && k == 0; i++)
    {
        if (s->ids[i] == id)
        {
            s->ids[i] = NO_ID;
            reorder_set_ids(s, i);

            /*Error control*/
            aux = (Id *) realloc(s->ids, s->n_ids * sizeof(Id));
            if (!aux)
            {
                return ERROR;
            }
            s->n_ids--;

            s->ids = aux;
            aux = NULL;

            k = 1;
        }
    }

    if (k == 1)
    {
        return OK;
    }
    else
    {
        return ERROR;
    }
}

/**
 * Elimina el id del set que se encuentra en pos
 */
STATUS set_del_pos(Set *s, int pos)
{
    Id *aux = NULL;

    /*Error control*/
    if (!s || pos < 0 || pos >= s->n_ids || s->n_ids == 0)
    {
        printf("aa\n");
        return ERROR;
    }

    /*Error control*/
    if (s->ids[pos] == NO_ID)
    {
        printf("aaa\n");
        return ERROR;
    }
    
    s->ids[pos] = NO_ID;
    reorder_set_ids(s, pos);
    
    aux = (Id *) realloc(s->ids, s->n_ids * sizeof(Id));
    if (!aux)
    {
        return ERROR;
    }
    s->n_ids--;
    s->ids = aux;
    aux = NULL;

    return OK;
}

/**
 * Devuelve el numero de ids en un set
 */
int set_get_nids(Set *s)
{
    /*Error control*/
    if (!s)
    {
        return -1;
    }
    
    return s->n_ids;
}

/**
 * Devuelve un array con todos los ids del set
 */
Id *set_get_ids(Set *s)
{
    /*Error control*/
    if (!s)
    {
        return NULL;
    }
    
    return s->ids;
}

/**
 * Comprueba si un set esta bien definido
 */
STATUS set_test(Set *s)
{
    int i, size_s;

    /*Error control*/
    if (!s || s->n_ids < 0)
    {
        return ERROR;
    }
    
    /* Comprobar si s->n_ids coincide con el numero que hay*/
    if (s->n_ids > 0)
    {
        size_s = (int) sizeof(s->ids) / sizeof(Id);
        if (size_s != s->n_ids)
        {
            return ERROR;
        }
        
    }
    
    /* Comprobar no haya NO_ID*/
    for (i = 0; i < s->n_ids; i++)
    {
        if (s->ids[i] == NO_ID)
        {
            return ERROR;
        }
        
    }
    
    return OK;
}

/**
 * Imprime toda la informacion de un set
 */
int set_print(Set *s)
{
    int i, n;

    /*Error control*/
    for (i = 0, n = 0; i < s->n_ids; i++)
    {
        n += fprintf(stdout, "Id %d : %ld\n", i, s->ids[i]);
    }
    
    return n;
}