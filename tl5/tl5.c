/**
 * CS 2110 - Fall 2019 - Timed Lab #5
 *
 * @author YOUR NAME HERE
 *
 * tl5.c: Complete the functions!
 */

// Do not add ANY additional includes!!!
#include "tl5.h"
#include "string.h"

///* You should NOT have any global variables. */

/** unzip
  *
  * Splits a list into two lists, with the first list containing all elements
  * with even index and the second list containing all elements with odd index.
  *
  * If listToUnzip is NULL return NULL. For any memory allocations
  * failures your code must not leak memory. This means that if any
  * memory allocation failures occur, before you return NULL, you must destroy
  * the list 
  *
  * @param listToUnzip A pointer to the struct list structure to make a copy of
  * @return The struct list structure created by splitting the old one, or NULL on
  *         failure (includes any of the parameters being null)
  */
List *unzip(List *listToUnzip)
{
  if (listToUnzip == NULL) {
    return NULL;
  }

  List *unzipped = (List*) malloc(sizeof(List));
  if (unzipped == NULL) {
    // destroy(listToUnzip);
    return NULL;
  }
  unzipped->head = NULL;


  unsigned long int listSize = 0;
  Node *tempCurr = listToUnzip->head;
  while (tempCurr != NULL) {
    listSize++;
    tempCurr = tempCurr->next;
  }


  Node **currUnzipped = &unzipped->head;
  Node **curr = &listToUnzip->head;

  for (unsigned long int currIndex = 0; currIndex < listSize; currIndex++) {
    if (currIndex % 2 != 0) {
      *currUnzipped = *curr;
      currUnzipped = &(*currUnzipped)->next;
      // cut out the current node

      *curr = (*curr)->next;
    }

    curr = &(*curr)->next;
  }
  
  // if (listSize % 2 != 0) {
  //   (*currUnzipped)->next = NULL;
  // }

  return unzipped;
}

                /*                    ATTENTION 
                  To locally test the destroy() and destroy_pokemon() methods run:

                            'make run-valgrind TEST=test_name'
                */


/** Destroy
  *
  * Destroys the entire struct list. This function removes every list node and pokemon
  * and finally removes the list itself.
  *
  * HINT: remember every malloc needs a respective free
  * 
  * @param listToEmpty a pointer to the struct list
  */
void destroy(List *listToDestroy)
{
  if (listToDestroy == NULL) {
    return;
  }

  Node *curr = listToDestroy->head;
  while (curr != NULL) {
    destroy_pokemon(curr->data);
    Node *tempCurr = curr;
    curr = curr->next;
    free(tempCurr);
  }
  free(listToDestroy);
}

/** Destroy Pokemon
  *
  * Destroys the pokemon. This function frees any necessary elements to free
  *
  * If pokemonToDestroy is NULL, just return.
  *
  * HINT: remember every malloc needs a respective free (and assume all pointer types were malloc'd)
  *
  * @param pokemonToDestroy a pointer to the struct pokemon
  */
void destroy_pokemon(Pokemon *pokemonToDestroy)
{
  if (pokemonToDestroy == NULL) return;
  Pokemon *b = (Pokemon *) pokemonToDestroy;
  free(b->name);
  free(b->type);
  free(b);
}
