/**
 * @file set_test.c
 * @author Miguel Soto
 * @brief It tests the set module
 * @version 0.1
 * @date 2022-02-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "set.h"

void free_all(Set **s);

int main()
{
    Id lista_ids[] = {11, 12, 13, 14, 15, 16, 17};
    Set *set = NULL;
    Id *ids_set = NULL;
    int i = 0, nids = 0;

    /**
     * TEST: CREATE SET
     */
    fprintf(stdout, "\n>>> TEST: Creando set\n");
    set = set_create();

    if (!set)
    {
        fprintf(stderr, "ERROR creando set\n");
        free_all(&set);
        return 1;
    }
    fprintf(stdout, "Set creado\n");


    /**
     * TEST: Adding elements to Set
     */
    fprintf(stdout, "\n>>> TEST: Añadir elementos a Set\n");
    
    /*  Adding Id 0 to set*/
    i = 0;
    fprintf(stdout, "Añadiendo id %d\n", i);
    if (set_add(set, lista_ids[i]) == ERROR)
    {
        fprintf(stderr, "ERROR añadiendo id 0\n");
        free_all(&set);

        return 1;
    }

    /*  Adding Id 1 to set*/
    i++;
    fprintf(stdout, "Añadiendo id %d\n", i);
    if (set_add(set, lista_ids[i]) == ERROR)
    {
        fprintf(stderr, "ERROR añadiendo id 1\n");
        free_all(&set);

        return 1;
    }
    
    /*  Print set*/
    set_print(set);

    /**
     * TEST: Getting elements from set
     */
    fprintf(stdout, "\n>>> TEST: Recibir elementos del Set\n");
    
    fprintf(stdout, "Recibiendo array ids\n");
    ids_set = set_get_ids(set);
    if (ids_set == ERROR)
    {
        fprintf(stderr, "ERROR set_get_ids\n");
        free_all(&set);
        return 1;
    }
    
    fprintf(stdout, "Recibiendo nids\n");
    nids = set_get_nids(set);
    fprintf(stdout, "nids = %d\n", nids);

    /**
     * TEST: Delete Ids
     */
    fprintf(stdout, "\n>>> TEST: Eliminando elementos de Set\n");

    /*  Delete Id 1*/
    i = 1;
    fprintf(stdout, "Eliminando id %d\n", i);
    if (set_del_id(set, lista_ids[i]) == ERROR)
    {
        fprintf(stderr, "ERROR eliminando id %d\n", i);
        free_all(&set);

        return 1;
    }

    /*  Print set*/
    set_print(set);

    /*  Delete Id 0 by pos*/
    i = 0;
    fprintf(stdout, "Eliminando id %d\n", i);
    if (set_del_pos(set, i) == ERROR)
    {
        fprintf(stderr, "ERROR eliminando id %d\n", i);
        free_all(&set);

        return 1;
    }

    /*  Print set*/
    set_print(set);


    /**
     * TEST: Free Set
     */
    fprintf(stdout, "\n>>> TEST: Liberar Set\n");

    /*  Destroy set*/
    free_all(&set);
    fprintf(stdout, "Set liberado correctamente\n");


    fprintf(stdout, "\n********\nTODO OK\n********\n");
    return 0;
}

void free_all(Set **s)
{
    if (*s)
    {
        set_destroy(*s);
        (*s) = NULL;
    }
}