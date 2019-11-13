/**
 * CS 2110 - Fall 2019 - Timed Lab 5
 *
 * Do not modify this file!
 *
 * struct tl5.h
 */

#ifndef tl5_H
#define tl5_H

#include <stdlib.h>

// This is just to remove compiler warnings associated with unused variables.
// Delete calls to this as you implement functions.
#define UNUSED_PARAMETER(x) (void)(x)

/**************************
 ** Datatype definitions **
 **************************/

/*
 * The following structs define the list and pokemon nodes for use in tl5.c. DO NOT MODIFY THESE STRUCT DEFINITIONS
 */

typedef struct pokemon
{
    char* name;
    char* type;
    int level;
} Pokemon;

typedef struct node
{
    struct node *next;
    struct pokemon *data;
} Node;


typedef struct list
{
    // Head pointer either points to a node with data or if the struct list is
    // empty NULL
    struct node *head;
} List;

/***************************************************
** Prototypes for struct list library functions.  **
**                                                **
** For more details on their functionality,       **
** check tl5.c.                                   **
***************************************************/

/* Copy List */
List *unzip(List *listToSplit);

/* Destroy List */
void destroy(List *listToDestroy);

/* Destroy Pokemon */
void destroy_pokemon(Pokemon *pokemonToDestroy);
#endif
