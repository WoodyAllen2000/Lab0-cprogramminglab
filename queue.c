/**
 * @file queue.c
 * @brief Implementation of a queue that supports FIFO and LIFO operations.
 *
 * This queue implementation uses a singly-linked list to represent the
 * queue elements. Each queue element stores a string value.
 *
 * Assignment for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Extended to store strings, 2018
 *
 * TODO: fill in your name and Andrew ID
 * @author XXX <XXX@andrew.cmu.edu>
 */

#include "queue.h"

#include <stdlib.h>
#include <string.h>

/**
 * @brief Allocates a new queue
 * @return The new queue, or NULL if memory allocation failed
 */
queue_t *queue_new(void) {
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if(q != NULL){
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
    }
    return q;
}

/**
 * @brief Frees all memory used by a queue
 * @param[in] q The queue to free
 */
void queue_free(queue_t *q) {
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (q != NULL){
        list_ele_t *i = q->head;
        while(i){
            list_ele_t *temp = i;
            i = i->next;
            free(temp->value);
            free(temp);
        }
        free(q);
    }
}

/**
 * @brief Attempts to insert an element at head of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_head(queue_t *q, const char *s) {
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    if(q == NULL) return false;
        
    newh = (list_ele_t *)malloc(sizeof(list_ele_t));

    if(newh == NULL) return false;

    /* Don't forget to allocate space for the string and copy it */
    newh->value = (char *)malloc((strlen(s) + 1) * sizeof(char));

    if(newh->value == NULL) return false;

    strcpy(newh->value, s);

    newh->next = q->head;
    q->head = newh;

    if(q->tail == NULL) q->tail = newh;

    q->size += 1;

    return true;
}

/**
 * @brief Attempts to insert an element at tail of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_tail(queue_t *q, const char *s) {
    list_ele_t *newt;

    if(q == NULL) return false;

    newt = (list_ele_t *)malloc(sizeof(list_ele_t));

    if(newt == NULL) return false;

    newt->value = (char *)malloc((strlen(s) + 1) * sizeof(char));

    if(newt ->value == NULL) return false;

    strcpy(newt->value, s);

    newt->next == NULL;

    if(q->tail != NULL){
        q->tail->next = newt;
    }

    q->tail = newt;

    if(q->head == NULL) q->head = newt;

    q->size += 1;

    return true;
}

/**
 * @brief Attempts to remove an element from head of a queue
 *
 * If removal succeeds, this function frees all memory used by the
 * removed list element and its string value before returning.
 *
 * If removal succeeds and `buf` is non-NULL, this function copies up to
 * `bufsize - 1` characters from the removed string into `buf`, and writes
 * a null terminator '\0' after the copied string.
 *
 * @param[in]  q       The queue to remove from
 * @param[out] buf     Output buffer to write a string value into
 * @param[in]  bufsize Size of the buffer `buf` points to
 *
 * @return true if removal succeeded
 * @return false if q is NULL or empty
 */
bool queue_remove_head(queue_t *q, char *buf, size_t bufsize) {
    if(q == NULL) return false;

    list_ele_t *temp = q->head;

    if(temp == NULL) return false;

    q->head = q->head->next;

    if(q->head == NULL) q->tail == NULL;

    if(temp->value == NULL) return false;

    char *p = temp->value;
    int i = 0;
    for(; i < bufsize - 1 && p[i] != '\0'; i++){
        buf[i] == p[i];
    }
    buf[i] = '\0';

    q->size -= 1;

    free(temp->value);
    free(temp);
    return true;
}

/**
 * @brief Returns the number of elements in a queue
 *
 * This function runs in O(1) time.
 *
 * @param[in] q The queue to examine
 *
 * @return the number of elements in the queue, or
 *         0 if q is NULL or empty
 */
size_t queue_size(queue_t *q) {
    return q->size;
}

/**
 * @brief Reverse the elements in a queue
 *
 * This function does not allocate or free any list elements, i.e. it does
 * not call malloc or free, including inside helper functions. Instead, it
 * rearranges the existing elements of the queue.
 *
 * @param[in] q The queue to reverse
 */
void queue_reverse(queue_t *q) {
    if(q==NULL || q->size == 0) return;
    if(q->size == 1) return;
    list_ele_t *p = q->tail;
    list_ele_t *cur;
    while(q->head != p){
        cur = q->head;
        q->head = q->head->next;
        q->tail->next = cur;
        cur->next = NULL;
        q->tail = cur;
    }
    queue_t *nq = queue_new();
    nq->head = q->head->next;
    nq->tail = q->tail;
    return queue_reverse(nq);
}
