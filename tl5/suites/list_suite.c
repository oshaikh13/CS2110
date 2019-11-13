// Timed Lab 5 Tests, Spring 2019
// Structure by Austin, actual work by Jim and Sanjay (RIP), lots of change by Maddie (why do I do this)
//
// Warning: much the structure of this file is shamelessly copypasted from
// https://libcheck.github.io/check/doc/check_html/check_3.html

#include <stdio.h>
#include <check.h>
#include <stdlib.h>
#include <string.h>
#include "test_utils.h"
static struct list *l;

// The number of mallocs in user code until the next one fails, or -1 for
// successful mallocs
int mallocs_until_fail = -1;

static void reset_mallocs_until_fail(void) {
    mallocs_until_fail = -1;
}

static struct list *_create_list_empty(void) {
    struct list* emptyList = _create_list();
    return emptyList;
}

static struct list *_create_length_1_list(void) {
    struct list *shortList = _create_list();
    _push_front(shortList, _create_pokemon("Pichu", "Water", 5));
    return shortList;
}

static struct list *_create_length_2_list(void) {
    struct list *shortList = _create_list();
    _push_front(shortList, _create_pokemon("Pichu", "Water", 5));
    _push_front(shortList, _create_pokemon("Pikachu", "Electric", 12));
    return shortList;
}

static struct list *_create_even_longer_even_list(void) {
    struct list *longerList = _create_list();
    _push_front(longerList, _create_pokemon("Pikachu", "Electric", 12));
    _push_front(longerList, _create_pokemon("Evee", "Electric", 12));
    _push_front(longerList, _create_pokemon("Mawile", "Electric", 12));
    _push_front(longerList, _create_pokemon("Pikachu", "Electric", 14));
    _push_front(longerList, _create_pokemon("Pikachu", "Electric", 15));
    _push_front(longerList, _create_pokemon("Pikachu", "Electric", 18));
    return longerList;
}

static struct list *_create_even_longer_odd_list(void) {
    struct list *longerList = _create_list();
    _push_front(longerList, _create_pokemon("Pikachu", "Electric", 12));
    _push_front(longerList, _create_pokemon("Charizard", "Electric", 12));
    _push_front(longerList, _create_pokemon("Bulbasaur", "Electric", 12));
    _push_front(longerList, _create_pokemon("Pikachu", "Electric", 12));
    _push_front(longerList, _create_pokemon("Pikachu", "Electric", 14));
    _push_front(longerList, _create_pokemon("Pikachu", "Electric", 16));
    _push_front(longerList, _create_pokemon("Pikachu", "Electric", 13));
    return longerList;
}

void teardown_bar_list(void) {
    if (l != NULL) {
        _free_list_nodes_and_data(l);
        l = NULL;
    }
}

/******************************************************************************/
/*************************** unzip() tests ***************************/
/******************************************************************************/
START_TEST(test_list_unzip_basic_odd_easy) {
    struct list *l1 = _create_length_1_list();
    struct list *l2 = unzip(l1);

    ck_assert(l1);
    ck_assert_msg(l2, "unzip didn't return a new list D:!");
    
    Node *current_l1 = l1->head;
    Node *current_l2 = l2->head;
    
    //checks to make sure l2 isn't null
    ck_assert_msg(!current_l2, "The returned list was not empty (non-null head) when it should have been");
    ck_assert_msg(current_l1, "The original list became empty (null head) when it shouldn't have been");

    _free_list_nodes_and_data(l1);
    _free_list_nodes_and_data(l2);
}
END_TEST

START_TEST(test_list_unzip_basic_odd_hard) {
    struct list *l1 = _create_length_1_list();
    Node *n = l1->head;
    Node current_node = *n;
    struct list *l2 = unzip(l1);

    ck_assert(l1);
    ck_assert_msg(l2, "unzip didn't return a new list D:!");

    Node *current_l1 = l1->head;
    Node *current_l2 = l2->head;

    ck_assert_msg(!current_l2, "The returned list was not empty (non-null head) when it should have been");
    ck_assert_ptr_eq(current_l1, n);
    ck_assert_ptr_eq(current_node.next, current_l1->next);
    ck_assert_int_eq(current_node.data->level, current_l1->data->level);
    ck_assert_str_eq(current_node.data->type, current_l1->data->type);
    
    _free_list_nodes_and_data(l1);
    _free_list_nodes_and_data(l2);
}
END_TEST

START_TEST(test_list_unzip_basic_even_easy) {
    struct list *l1 = _create_length_2_list();
    struct list *l2 = unzip(l1);

    ck_assert(l1);
    ck_assert_msg(l2, "unzip didn't return a new list D:!");

    Node *current_l1 = l1->head;
    Node *current_l2 = l2->head;

    //checks to make sure l2 isn't null
    ck_assert_msg(current_l2, "The returned list was empty (null head) when it shouldn't have been");
    ck_assert_msg(current_l1, "The original list became empty (null head) when it shouldn't have been");

    _free_list_nodes_and_data(l1);
    _free_list_nodes_and_data(l2);
}
END_TEST

START_TEST(test_list_unzip_basic_even_hard) {
    struct list *l1 = _create_length_2_list();
    Node *n = l1->head;
    Node *n2 = l1->head->next;
    Node current_node = *n;
    Node current_node_2 = *n2;
    struct list *l2 = unzip(l1);

    ck_assert(l1);
    ck_assert_msg(l2, "unzip didn't return a new list D:!");

    Node *current_l1 = l1->head;
    Node *current_l2 = l2->head;

    ck_assert_ptr_eq(current_l1, n);
    ck_assert_ptr_eq(current_node.next, current_l2);
    ck_assert_int_eq(current_node.data->level, current_l1->data->level);
    ck_assert_str_eq(current_node.data->type, current_l1->data->type);

    ck_assert_ptr_eq(current_l2, n2);
    ck_assert_ptr_eq(current_node_2.next, current_l1->next);
    ck_assert_int_eq(current_node_2.data->level, current_l2->data->level);
    ck_assert_str_eq(current_node_2.data->type, current_l2->data->type);

    _free_list_nodes_and_data(l1);
    _free_list_nodes_and_data(l2);
}
END_TEST

START_TEST(test_list_unzip_long_even) {
    struct list *l1 = _create_even_longer_even_list();
    Node *n1 = l1->head;
    Node *n2 = n1->next;
    Node *n3 = n2->next;
    Node *n4 = n3->next;
    Node *n5 = n4->next;
    Node *n6 = n5->next;
    struct list *l2 = unzip(l1);

    ck_assert_msg(l2, "unzip didn't return a new list D:!");

    Node *l1_n1 = l1->head;
    Node *l1_n2 = l1->head->next;
    Node *l1_n3 = l1->head->next->next;
    Node *l2_n1 = l2->head;
    Node *l2_n2 = l2->head->next;
    Node *l2_n3 = l2->head->next->next;

    ck_assert_ptr_eq(n1, l1_n1);
    ck_assert_ptr_eq(n2, l2_n1);
    ck_assert_ptr_eq(n3, l1_n2);
    ck_assert_ptr_eq(n4, l2_n2);
    ck_assert_ptr_eq(n5, l1_n3);
    ck_assert_ptr_eq(n6, l2_n3);

    _free_list_nodes_and_data(l1);
    _free_list_nodes_and_data(l2);

}
END_TEST

START_TEST(test_list_unzip_long_odd) {
    struct list *l1 = _create_even_longer_odd_list();
    Node *n1 = l1->head;
    Node *n2 = n1->next;
    Node *n3 = n2->next;
    Node *n4 = n3->next;
    Node *n5 = n4->next;
    Node *n6 = n5->next;
    Node *n7 = n6->next;
    struct list *l2 = unzip(l1);

    ck_assert_msg(l2, "unzip didn't return a new list D:!");

    Node *l1_n1 = l1->head;
    Node *l1_n2 = l1->head->next;
    Node *l1_n3 = l1->head->next->next;
    Node *l1_n4 = l1->head->next->next->next;
    Node *l2_n1 = l2->head;
    Node *l2_n2 = l2->head->next;
    Node *l2_n3 = l2->head->next->next;

    ck_assert_ptr_eq(n1, l1_n1);
    ck_assert_ptr_eq(n2, l2_n1);
    ck_assert_ptr_eq(n3, l1_n2);
    ck_assert_ptr_eq(n4, l2_n2);
    ck_assert_ptr_eq(n5, l1_n3);
    ck_assert_ptr_eq(n6, l2_n3);
    ck_assert_ptr_eq(n7, l1_n4);

    _free_list_nodes_and_data(l1);
    _free_list_nodes_and_data(l2);

}
END_TEST

START_TEST(test_list_unzip_malloc_failure) {
    struct list *l1 = _create_length_1_list();

    mallocs_until_fail = 0;
    struct list *l2 = unzip(l1);

    if (l2) {
        ck_abort_msg("Error in handling error cases for malloc!");
    }
    _free_list_nodes_and_data(l1);
}
END_TEST

START_TEST(test_list_unzip_malloc_failure_hard) {
    struct list *l1 = _create_length_2_list();

    mallocs_until_fail = 10;
    struct list *l2 = unzip(l1);

    if (mallocs_until_fail != 9) {
        ck_abort_msg("Called malloc an incorrect number of instances!");
    }

    _free_list_nodes_and_data(l1);
    _free_list_nodes_and_data(l2);
}
END_TEST

START_TEST(test_list_unzip_empty_list) {
    struct list *l1 = _create_list_empty();
    struct list *l2 = unzip(l1);

    ck_assert_msg(l2, "unzip didn't return a new list D:!");
    ck_assert(!l2 -> head);
    free(l1);
    free(l2);
}
END_TEST

START_TEST(test_list_unzip_null_list) {
    struct list *l1 = unzip(NULL);
    ck_assert_msg(!l1, "List returned was not NULL");
}
END_TEST

/******************************************************************************/
/***************************** destroy() tests ********************************/
/******************************************************************************/
START_TEST(test_list_destroy_NULL_list) {
    // Success if there is no error
    destroy(NULL);
}
END_TEST

START_TEST(test_list_destroy_empty) {
    struct list *l = _create_list();
    destroy(l);
}
END_TEST

START_TEST(test_list_destroy_length_1) {
    struct list *l = _create_length_1_list();
    destroy(l);
}
END_TEST

START_TEST(test_list_destroy_longer_list) {
    struct list *l = _create_even_longer_odd_list();
    destroy(l);
}
END_TEST

/******************************************************************************/
/************************ destroy_pokemon() tests *****************************/
/******************************************************************************/
START_TEST(test_list_destroy_pokemon_NULL_node) {
        // Success if there is no error
        destroy_pokemon(NULL);
}
END_TEST

START_TEST(test_list_destroy_pokemon_NULL_name) {
    struct pokemon *poke = _create_pokemon(NULL, "Water", 4);
    destroy_pokemon(poke);
}
END_TEST

START_TEST(test_list_destroy_pokemon_normal_node) {
    struct pokemon *poke = _create_pokemon("Squirtle", "Fire", 6);
    destroy_pokemon(poke);
}
END_TEST

Suite *list_suite(void) {
    Suite *s = suite_create("struct list");

    // create_list() tests
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_unzip_basic_odd_easy);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_unzip_basic_odd_hard);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_unzip_basic_even_easy);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_unzip_basic_even_hard);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_unzip_long_odd);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_unzip_long_even);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_unzip_malloc_failure);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_unzip_malloc_failure_hard);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_unzip_null_list);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_unzip_empty_list);

    // destroy() tests
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_destroy_NULL_list);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_destroy_empty);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_destroy_length_1);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_destroy_longer_list);

    // destroy_pokemon() tests
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_destroy_pokemon_NULL_node);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_destroy_pokemon_NULL_name);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_destroy_pokemon_normal_node);


    return s;
}