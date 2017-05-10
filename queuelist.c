/*
 * NAME: queuelist.c -- the test file for the queue implementation in queuelist.h
 * AUTHOR: Ethan D. Twardy
 * CREATED: 05/09/17
 * LAST EDITED: 05/10/17
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "queuelist.h"

static inline void error_exit(char * msg)
{
  fprintf(stderr, "%s\n", msg);
  exit(1);
}

int main(int argc, char * arv[])
{
  // CASES TO TEST FOR:
  //    * Normal dequeueing and enqueueing of data. Check order.
  //    * Check that attempting to dequeue from an empty queue returns -1.

  int * pNum = NULL;
  Queue * q;

  if ((q = (Queue *)malloc(sizeof(Queue))) == NULL)
    error_exit("Could not allocate memory for Queue!");

  queue_init(q, free);

  srand((unsigned)time(NULL));

  // Populate the queue with integers.
  printf("==== Inserting ====\n");
  for (int i = 0; i < 10; i++) {
    pNum = (int *)malloc(sizeof(int));
    *pNum = rand() % 10;

    if (queue_enqueue(q, (void *)pNum) != 0)
      error_exit("There was an error when enqueueing!");
    else
      printf("int %d @ %p\n", *pNum, pNum);
  }

  // Remove all the integers currently in the queue.
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
