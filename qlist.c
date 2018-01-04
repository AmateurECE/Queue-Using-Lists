/******************************************************************************
 * NAME:	    qlist.c
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    Source code for the implementation of a Queue, using a
 *		    linked list. Follows the function prototypes in qlist.h.
 *		    Also contains test code, which is compiled by 'make debug'.
 *
 * CREATED:	    05/09/2017
 *
 * LAST EDITED:	    01/04/2018
 ***/

/******************************************************************************
 * INCLUDES
 ***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef CONFIG_DEBUG_QLIST
#include <time.h>
#include <assert.h>
#endif /* CONFIG_DEBUG_QLIST */

#include "qlist.h"

/******************************************************************************
 * LOCAL PROTOTYPES
 ***/

#ifdef CONFIG_DEBUG_QLIST
static inline void error_exit(char *);
#endif /* CONFIG_DEBUG_QLIST */

/******************************************************************************
 * API FUNCTIONS
 ***/

/******************************************************************************
 * FUNCTION:	    queue_init
 *
 * DESCRIPTION:	    Initializes a Queue pointer.
 *
 * ARGUMENTS:	    queue: (Queue *) -- the queue to be initialized.
 *		    destroy: (void (*)(void *)) -- pointer to a user defined
 *			     function meant to free the data held in the queue.
 *
 * RETURN:	    void.
 *
 * NOTES:	    O(1)
 ***/
void queue_init(Queue * queue, void (*destroy)(void *))
{
  queue->head = NULL;
  queue->tail = NULL;
  queue->size = 0;
  queue->destroy = destroy;
}

/******************************************************************************
 * FUNCTION:	    queue_enqueue
 *
 * DESCRIPTION:	    Enqueues the data held in 'data.'
 *
 * ARGUMENTS:	    queue: (Queue *) -- the queue to be operated on.
 *		    data: (void *) -- the data to be enqueued.
 *
 * RETURN:	    int -- 0 on success, -1 otherwise.
 *
 * NOTES:	    O(1)
 ***/
int queue_enqueue(Queue * queue, void * data)
{
  QElmt * new;

  if (data == NULL || (new = (QElmt *)malloc(sizeof(QElmt))) == NULL)
    return -1;

  new->data = data;

  if (queue_isempty(queue)) {
    /* Handle queueing when the queue is empty. */
    queue->head = new;
    queue->tail = new;
    new->next = NULL;

  } else {
    /* Handle queueing when it's not. */
    queue->tail->next = new;
    new->next = NULL;
    queue->tail = new;

  }

  queue->size++;
  return 0;
}

/******************************************************************************
 * FUNCTION:	    queue_dequeue
 *
 * DESCRIPTION:	    Dequeues from the queue, and places the data in 'data.'
 *
 * ARGUMENTS:	    queue: (Queue *) -- the queue to be operated on.
 *		    data: (void *) -- once removed, the data is placed here.
 *
 * RETURN:	    int -- 0 on success, -1 otherwise.
 *
 * NOTES:	    O(1)
 ***/
int queue_dequeue(Queue * queue, void ** data)
{
  if (data == NULL || queue_isempty(queue))
    return -1;

  QElmt * old = queue->head;
  *data = old->data;
  queue->head = old->next;

  if (queue->head == NULL)
    queue->tail = NULL;
  else if (queue->head->next == NULL)
    queue->tail = queue->head;

  queue->size--;
  free(old);
  return 0;
}

/******************************************************************************
 * FUNCTION:	    queue_dest
 *
 * DESCRIPTION:	    Removes all data in the queue, and sets all bytes of memory
 *		    in the Queue structure to be 0.
 *
 * ARGUMENTS:	    queue: (Queue *) -- the queue to be operated on.
 *
 * RETURN:	    void.
 *
 * NOTES:	    O(n)
 ***/
void queue_dest(Queue * queue)
{
  void * data;

  while (!queue_isempty(queue)) {

    queue_dequeue(queue, (void **)&data);

   if (data != NULL && queue->destroy != NULL)
      queue->destroy(data);

  }

  memset(queue, 0, sizeof(Queue));
}

/******************************************************************************
 * MAIN
 ***/

#ifdef CONFIG_DEBUG_QLIST
int main(int argc, char * arv[])
{
  /* CASES TO TEST FOR:
      * Normal dequeueing and enqueueing of data. Check order.
      * Check that attempting to dequeue from an empty queue returns -1.
   */
  int * pNum = NULL;
  Queue * q;

  if ((q = (Queue *)malloc(sizeof(Queue))) == NULL)
    error_exit("Could not allocate memory for Queue!");

  queue_init(q, free);

  srand((unsigned)time(NULL));

  /* Populate the queue with integers. */
  printf("==== Inserting ====\n");
  for (int i = 0; i < 10; i++) {
    pNum = (int *)malloc(sizeof(int));
    *pNum = rand() % 10;

    if (queue_enqueue(q, (void *)pNum) != 0)
      error_exit("There was an error when enqueueing!");
    else
      printf("int %d @ %p\n", *pNum, pNum);
  }

  /* Remove all the integers currently in the queue. */
  printf("==== Removing =====\n");
  for (int i = 0; i < 10; i++) {

    if (queue_dequeue(q, (void **)&pNum) != 0)
      error_exit("There was an error when dequeueing!");
    else
      printf("int %d @ %p\n", *pNum, pNum);
    free(pNum);
  }

  assert(queue_dequeue(q, (void **)&pNum) == -1);

  queue_dest(q);
  free(q);
}
#endif /* CONFIG_DEBUG_QLIST */

/******************************************************************************
 * LOCAL FUNCTIONS
 ***/

#ifdef CONFIG_DEBUG_QLIST
static inline void error_exit(char * msg)
{
  fprintf(stderr, "%s\n", msg);
  exit(1);
}
#endif /* CONFIG_DEBUG_QLIST */

/*****************************************************************************/
