/**
 * CS 2110 - Fall 2019 - Homework #9
 *
 * @author YOUR NAME HERE
 *
 * list.c: Complete the functions!
 */

/**
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!-IMPORTANT-!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * For any function that must use malloc, if malloc returns NULL, the function
 * itself should return NULL if needs to return something (or return 0 if
 * the function returns a int).
 */

// Do not add ANY additional includes!!!
#include "list.h"

/* You should NOT have any global variables. */

/* The create_node function is static because this is the only file that should
   have knowledge about the nodes backing the linked List. */
static inline Node *create_node(Pokemon *data);
void swap(Node **a, Node **b);

/** create_node
  *
  * Helper function that creates a Node by allocating memory for it on the heap.
  * Be sure to set its next pointer to NULL.
  *
  * If malloc returns NULL, you should return NULL to indicate failure.
  *
  * @param data a void pointer to data the user wants to store in List
  * @return a Node
  */
static Node* create_node(Pokemon *data)
{
  Node* node = (Node*) malloc(sizeof(Node));
  if (node == NULL) return NULL;
  node->next = NULL;
  node->data = data;
  return node;
}

/** create_list
  *
  * Creates a struct linked_list by allocating memory for it on the heap.
  * Be sure to initialize size to zero and head and tail to NULL.
  *
  * If malloc returns NULL, you should return NULL to indicate failure.
  *
  * @return a pointer to a new struct list or NULL on failure
  */
LinkedList *create_list(void)
{
  LinkedList* list = (LinkedList*) malloc(sizeof(LinkedList));
  if (list == NULL) return NULL;
  list->head = NULL;
  list->size = 0;
  return list;
}

/** push_front
  *
  * Adds the element at the front of the struct linked_list.
  *
  * @param listToPrependTo a pointer to the struct linked_list structure.
  * @param data the data to add to the struct linked_list.
  * @return 0 if the struct linked_list is NULL, 1 if successful.
  */
int push_front(LinkedList *listToPrependTo, Pokemon *data)
{
  return add_at_index(listToPrependTo, data, 0);
}

/** push_back
  *
  * Adds the element to the back of the LinkedList.
  *
  * @param listToAppendTo a pointer to the LinkedList structure.
  * @param data the data to add to the LinkedList.
  * @return 0 if the LinkedList is NULL, 1 if successful.
  */
int push_back(LinkedList *listToAppendTo, Pokemon *data)
{
  return listToAppendTo == NULL ? 0 : add_at_index(listToAppendTo, data, listToAppendTo->size);
}

/** add_at_index
  *
  * Add the element at the specified index in the LinkedList. This index must lie in
  * the inclusive range [0,size].
  * For example, if you have no elements in the LinkedList,
  * you should be able to add to index 0 but no further.
  * If you have two elements in the LinkedList,
  * you should be able to add to index 2 but no further.
  *
  * @param listToAddTo a pointer to the LinkedList structure
  * @param index 0-based, starting from the head in the inclusive range
  *              [0,size]
  * @param data the data to add to the LinkedList
  * @return 0 if the index is out of bounds or the LinkedList is NULL
  *         (do not add the data in this case)
  *         otherwise return 1
  */
int add_at_index(LinkedList *listToAddTo, Pokemon *data, int index)
{
  if (listToAddTo == NULL || index < 0 || index > listToAddTo->size) { 
    return 0;
  }
  
  Node* node = create_node(data);

  // also modified from linus torvalds ted talk
  Node **indirect = &listToAddTo->head;
  for (int i = 0; i < index; i++) {
    indirect = &(*indirect)->next;
  }

  Node *temp = *indirect;
  *indirect = node;
  node->next = temp;

  listToAddTo->size++;
  return 1;
}

/** get
  *
  * Gets the data at the specified index in the LinkedList
  *
  * @param listToGetDataFrom a pointer to the LinkedList structure
  * @param index 0-based, starting from the head.
  * @param dataOut A pointer to a pointer used to return the data from the
  *        specified index in the LinkedList or NULL on failure.
  * @return 0 if dataOut is NULL or index is out of range of the LinkedList or
  *         the LinkedList is NULL, 1 otherwise
  */
int get(LinkedList *listToGetDataFrom, int index, Pokemon **dataOut)
{
  if (listToGetDataFrom == NULL || dataOut == NULL || index < 0 || index >= listToGetDataFrom->size) {
    return 0;
  }

  Node* curr = listToGetDataFrom->head;
  for (int i = 0; i < index; i++) {
    curr = curr->next;
  }

  *dataOut = curr->data;
  return 1;
}

/** contains
  *
  * Traverses the LinkedList, trying to see if the LinkedList contains some
  * data. We will consider a node to contain the same data if the pokemon at that
  * node has the same name as the pokemon passed in.
  *
  * The "data" parameter may not necessarily point to the same address as the
  * equal data you are returning from this function, it's just data which the
  * comparator (pokemon_eq_name in this case) says is equal.
  *
  * If there are multiple pieces of data in the LinkedList which are equal to
  * the "data" parameter, return the one at the lowest index.
  *
  * Use pokemon_eq_name to compare pokemon structs. Be sure to take a look at that
  * function before you use it! Also be sure not to use pokemon_eq.
  *
  * @param listToSearch a pointer to the LinkedList structure
  * @param data The data, to see if it exists in the LinkedList
  * @param dataOut A pointer to a pointer used to return the data contained in
  *                the LinkedList or NULL on failure
  * @return int    0 if dataOut is NULL, the list is NULL, or the list
  *                does not contain data, else 1
  */
int contains(LinkedList *listToSearch, Pokemon *data, Pokemon **dataOut)
{
  if (listToSearch == NULL || data == NULL || dataOut == NULL) { 
    return 0;
  }

  Node* curr = listToSearch->head;
  while (curr != NULL) {
    if (pokemon_eq_name(data, curr->data) == 0) {
      *dataOut = curr->data;
      return 1;
    }
    curr = curr->next;
  }
  *dataOut = NULL;

  return 0;
}

/** pop_front
  *
  * Removes the List_node at the front of the LinkedList, and returns its data to the user
  *
  * @param listToPopFrom a pointer to the LinkedList.
  * @param dataOut A pointer to a pointer used to return the data in the first
  *                List_node or NULL on failure
  * @return 0 if dataOut is NULL or the LinkedList is NULL or empty, else 1
  */
int pop_front(LinkedList *listToPopFrom, Pokemon **dataOut)
{
  return remove_at_index(listToPopFrom, dataOut, 0);
}

/** pop_back
  *
  * Removes the ListNode at the back of the LinkedList, and returns its data to the user
  *
  * @param listToPopFrom a pointer to the LinkedList.
  * @param dataOut A pointer to a pointer used to return the data in the last
  *                ListNode or NULL on failure
  * @return 0 if dataOut is NULL or the LinkedList is NULL or empty, else 1
  */
int pop_back(LinkedList *listToPopFrom, Pokemon **dataOut)
{
  return listToPopFrom == NULL ? 0 : remove_at_index(listToPopFrom, dataOut, listToPopFrom->size - 1);
}


/** remove_at_index
  *
  * Remove the element at the specified index in the LinkedList.
  *
  * @param listToAddTo a pointer to the LinkedList structure
  * @param index 0-based, starting from the head in the inclusive range
  *              [0,size]
  * @param data the data to add to the LinkedList
  * @return 0 if the index is out of bounds, the LinkedList is NULL or
  *         the dataOut is NULL
  *         otherwise return 1
  */
int remove_at_index(LinkedList * listToRemoveFrom, Pokemon ** dataOut, int index) 
{
  if (listToRemoveFrom == NULL || dataOut == NULL || index < 0 || index >= listToRemoveFrom->size) {
    return 0;
  } 
  
  // linus torvalds ted talk.
  Node **indirect = &listToRemoveFrom->head;
  for (int i = 0; i < index; i++) {
    indirect = &(*indirect)->next;
  }

  *dataOut = (*indirect)->data;
  Node *removed = *indirect;
  *indirect = (*indirect)->next;
  free(removed);
  listToRemoveFrom->size--;

  return 1;
}

/** empty_list
  *
  * Empties the LinkedList. After this is called, the LinkedList should be
  * empty. This does not free the LinkedList struct itself, just all nodes and
  * data within. Make sure to check that listToEmpty is not NULL before
  * using it.
  *
  * Call pokemon_free to free a pokemon struct.
  *
  * @param listToEmpty a pointer to the LinkedList structure
  */
void empty_list(LinkedList *listToEmpty)
{
  if (listToEmpty != NULL) {
    Node* curr = listToEmpty->head;
    while (curr != NULL) {
      listToEmpty->head = curr->next;
      pokemon_free(curr->data);
      free(curr);
      curr = listToEmpty->head;
    }
    listToEmpty->size = 0;
  }
}

/** swap_pokemon
  *
  *
  * Swaps two nodes in the LinkedList. After this is called, the nodes containing the 
  * this Pokemon data should be swapped. Make sure you swap the nodes themselves
  * and NOT just the data! 
  * Consider all cases! (nodes being side by side, one of the nodes being the head, etc.)
  *
  *     LinkedList *A: A1 -> A2 -> A3 -> A4 -> A5 -> NULL
  *     swap_pokemon(A, A2, A4);
  *     LinkedList *A: A1 -> A4 -> A3 -> A2 -> A5 -> NULL
  *
  * @param poke1 first node to swap
  * @param poke2 second node to swap
  * @return 0 if Pokemon not in list or are NULL or if list is NULL, 1 on successful swap
  */

void swap(Node** a, Node** b) 
{ 
  Node* t;
  t = *a;
  *a = *b;
  *b = t;
}

int swap_pokemon(LinkedList *list, Node *poke1, Node *poke2)
{
  if (list == NULL || poke1 == NULL || poke2 == NULL) return 0;

  Node *prevPoke1 = NULL, *currPoke1 = list->head; 
  while (currPoke1 && pokemon_eq_name(currPoke1->data, poke1->data)) { 
    prevPoke1 = currPoke1; 
    currPoke1 = currPoke1->next; 
  } 

  Node *prevPoke2 = NULL, *currPoke2 = list->head; 
  while (currPoke2 && pokemon_eq_name(currPoke2->data, poke2->data)) { 
    prevPoke2 = currPoke2; 
    currPoke2 = currPoke2->next; 
  } 

  if (currPoke1 == NULL || currPoke2 == NULL) return 0; 

  if (prevPoke1 != NULL) prevPoke1->next = currPoke2; 
  else list->head = currPoke2;   

  if (prevPoke2 != NULL) prevPoke2->next = currPoke1; 
  else list->head = currPoke1; 

  Node *temp = currPoke2->next; 
  currPoke2->next = currPoke1->next; 
  currPoke1->next  = temp; 

  return 1;
 
}

/** zip
  *
  *
  * Zips two Lists together. After this is called, the first list should
  * have the elements from both lists and the second list should be empty. 
  * Do not free the second list. Both Lists might be empty. If either list
  * is NULL, just return.
  *
  *     LinkedList *A: A1 -> A2 -> A3 -> A4 -> A5 -> NULL
  *
  *     LinkedList *B: B1 -> B2 -> B3 -> NULL
  *
  *     zip(A, B): A1 -> B1 -> A2 -> B2 -> A3 -> B3 -> A4 -> A5 -> NULL
  *
  * @param team1 first LinkedList to zip together
  * @param team2 second LinkedList to zip together
  */
void zip(LinkedList *team1, LinkedList *team2)
{
  if (team1 == NULL || team2 == NULL) return;

  int i = 0;
  Node* temp = team2->head;
  while (temp != NULL) {
    int newSize = 2 * i + 1;
    if (newSize > team1->size) {
      newSize = team1->size;
    }
    add_at_index(team1, temp->data, newSize);
    Node* prev = temp;
    temp = temp->next;
    free(prev);
    i++;
  }
  team2->head = NULL;
  team2->size = 0;
}
