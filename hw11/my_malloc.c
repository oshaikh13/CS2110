/*
 * CS 2110 Fall 2019
 * Author:
 */

/* we need this for uintptr_t */
#include <stdint.h>
/* we need this for memcpy/memset */
#include <string.h>
/* we need this to print out stuff*/
#include <stdio.h>
/* we need this for the metadata_t struct and my_malloc_err enum definitions */
#include "my_malloc.h"
/* include this for any boolean methods */
#include <stdbool.h>

/*Function Headers
 * Here is a place to put all of your function headers
 * Remember to declare them as static
 */
static void set_canary(metadata_t* block);
static void remove_from_addr_list(metadata_t* remove_block);
static metadata_t* split_block(metadata_t* block, size_t size);
static metadata_t* find_left(metadata_t* block);
static metadata_t* split_block(metadata_t* block, size_t size);
static void add_to_addr_list(metadata_t* add_block);
static void merge(metadata_t* left, metadata_t* right);
static bool check_canary(metadata_t* block, unsigned long canary);
static metadata_t* find_right(metadata_t* block);

/* Our freelist structure - our freelist is represented as a singly linked list
 * the freelist is sorted by address;
 */
metadata_t *address_list;

/* Set on every invocation of my_malloc()/my_free()/my_realloc()/
 * my_calloc() to indicate success or the type of failure. See
 * the definition of the my_malloc_err enum in my_malloc.h for details.
 * Similar to errno(3).
 */
enum my_malloc_err my_malloc_errno;

/* MALLOC
 * See PDF for documentation
 */
void *my_malloc(size_t size) {

  metadata_t *best_block = NULL;
  size_t best_size = 0;
  my_malloc_errno = NO_ERROR;

  if (size > SBRK_SIZE - TOTAL_METADATA_SIZE) {
    my_malloc_errno = SINGLE_REQUEST_TOO_LARGE;
    return NULL;
  }  
  
  if (size == 0) {
    return NULL;
  }

  metadata_t *curr = address_list;
  while (curr != NULL) {
    if (size == curr->size) {
      remove_from_addr_list(curr);
      set_canary(curr);
      return curr + 1;
    } else if (size + MIN_BLOCK_SIZE < curr->size && 
        (best_block == NULL || size + MIN_BLOCK_SIZE < best_size)) {
      best_block = curr;
      best_size = size + MIN_BLOCK_SIZE;
    }
    curr = curr->next;
  }

  if (best_block != NULL) {
    remove_from_addr_list(best_block);
    metadata_t *new_split = split_block(best_block, size);
    set_canary(new_split);
    add_to_addr_list(best_block);
    return new_split + 1;
  }

  metadata_t *sbrk_mem = my_sbrk(SBRK_SIZE);
  if (sbrk_mem == NULL) {
    my_malloc_errno = OUT_OF_MEMORY;
    return NULL;
  }

  metadata_t *left = find_left(sbrk_mem);
  sbrk_mem->size = SBRK_SIZE - TOTAL_METADATA_SIZE;
  if (left != NULL) {
    remove_from_addr_list(left);
    merge(left, sbrk_mem);
    sbrk_mem = left;
  }
  
  metadata_t *tmp_sbrk = sbrk_mem;
  if (sbrk_mem->size != size) {
    tmp_sbrk = split_block(sbrk_mem, size);
    add_to_addr_list(sbrk_mem);
  }

  set_canary(tmp_sbrk);
  return tmp_sbrk + 1;
  
}

/* REALLOC
 * See PDF for documentation
 */
void *my_realloc(void *ptr, size_t size) {

  if (ptr == NULL) {
    return my_malloc(size);
  }

  if (size == 0) {
    my_free(ptr);
    return NULL;
  }
  
  metadata_t* block = (metadata_t*) ptr - 1;
  unsigned long canary = ((uintptr_t)block ^ CANARY_MAGIC_NUMBER) + 1890;
  
  if (!check_canary(block, canary)) {
    my_malloc_errno = CANARY_CORRUPTED;
    return NULL;
  }

  void* curr = my_malloc(size);
  size_t curr_size = size;
  if (size > block->size) {
    curr_size = block->size;
  }
  
  memcpy(curr, ptr, curr_size);
  my_free(ptr);
  return curr;
  
}

/* CALLOC
 * See PDF for documentation
 */
void *my_calloc(size_t nmemb, size_t size) {
  size_t curr_size = size * nmemb;
  void* curr = my_malloc(curr_size);
  if (curr != NULL) {
    memset(curr, 0, curr_size);
  }
  return curr;
}

/* FREE
 * See PDF for documentation
 */
void my_free(void *ptr) {
  my_malloc_errno = NO_ERROR;

  if (ptr == NULL) {
    return;
  }

  metadata_t* block = (metadata_t*) ptr - 1;
  unsigned long canary = ((uintptr_t)block ^ CANARY_MAGIC_NUMBER) + 1890;

  if (!check_canary(block, canary)) {
    my_malloc_errno = CANARY_CORRUPTED;
    return;
  } 

  metadata_t *right = find_right(block);
  if (right != NULL) {
    remove_from_addr_list(right);
    merge(block, right);
  }
  
  metadata_t *left = find_left(block);
  if (left != NULL) {
    remove_from_addr_list(left);
    merge(left, block);
    block = left;
  }
  
  add_to_addr_list(block);
  
}

static bool check_canary(metadata_t* block, unsigned long canary) {
  bool end_canary_match = *(unsigned long*)((uint8_t*)block + sizeof(metadata_t) + block->size) == canary;
  bool block_match = block->canary == canary;
  return block_match && end_canary_match;
}

static void set_canary(metadata_t* block) {
  unsigned long canary = ((uintptr_t)block ^ CANARY_MAGIC_NUMBER) + 1890;
  block->canary = canary;
  *(unsigned long*)((uint8_t*)block + sizeof(metadata_t) + block->size) = canary;
}

static void remove_from_addr_list(metadata_t* remove_block) {
  metadata_t *curr = address_list;
  metadata_t **indirect = &address_list;
  while (curr != NULL) {
    if (curr == remove_block) {
      *indirect = curr->next;
      curr->next = NULL;
      break;
    }
    indirect = &(curr->next);
    curr = curr->next;
  }
}

static metadata_t* find_left(metadata_t* block) {
  metadata_t *curr = address_list;
  
  while (curr != NULL) {
    metadata_t* left = (metadata_t*)((uint8_t*)curr + curr->size + TOTAL_METADATA_SIZE);
    if (left == block) {
      return curr;
    }
    curr = curr->next;
  }
  return NULL;
}

static metadata_t* find_right(metadata_t* block) {
  metadata_t* right = (metadata_t*)((uint8_t*)block + block->size + TOTAL_METADATA_SIZE);
  metadata_t* curr = address_list;
  
  while (curr != NULL) {
    if (curr == right) {
      return curr;
    }
    
    curr = curr->next;
  }
  return NULL;
}

static void merge(metadata_t* left, metadata_t* right) {
  left->size += right->size + TOTAL_METADATA_SIZE;
}

static metadata_t* split_block(metadata_t* block, size_t size) {
  metadata_t* block_split = (metadata_t*)((uint8_t*)block + block->size - size);
  block_split->size = size;
  block->size -= size + TOTAL_METADATA_SIZE;
  return block_split;
}

static void add_to_addr_list(metadata_t* add_block) {
  metadata_t *curr = address_list;
  metadata_t **indirect = &address_list;
  while (curr != NULL) {
    if ((uintptr_t) add_block <= (uintptr_t) curr) {
      add_block->next = curr;
      *indirect = add_block;
      return;
    }
    indirect = &(curr->next);
    curr = curr->next;
  }
  *indirect = add_block;
  add_block->next = NULL;
}
