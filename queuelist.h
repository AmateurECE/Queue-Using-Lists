/*
 * NAME: queue-list.h -- implementation of a queue using lists, as opposed to arrays.
 * AUTHOR: Ethan D. Twardy
 * CREATED: 05/09/17
 * LAST EDITED: 05/10/17
 */

/* ************ NOTE ************ */
/* Due to conflicts between func- */
/* tion signatures for the public */
/* interfaces for this structure  */
/* and the queue using arrays,    */
/* the two header files cannot    */
/* be used in the same .c file.   */
/* ****************************** */

#ifndef __ET_QUEUELIST__
#define __ET_QUEUELIST__

#include <string.h>

/************* TYPE DEFINITIONS *************/
/********************************************/

typedef struct _QElmt_ {

  void * data;
  struct _QElmt_ * next;

} QElmt;

typedef struct _Queue_ {

  QElmt * head;
  QElmt * tail;

  int size;
  void (*destroy)(void *);

} Queue;

/************* MACRO DEFINITIONS ************/
/********************************************/

#define queue_peek(queue) ((queue)->head)
#define queue_size(queue) ((queue)->size)
#define queue_isempty(queue) ((queue)->size == 0 ? 1 : 0)

/************* PUBLIC INTERFACE *************/
/********************************************/

// FUNCTION: queue_init O(1) -- initializes the queue in queue.
// PARAMETERS: queue: (Queue *) -- the queue to be initialized.
//             destroy: void (*)(void *) -- user defined function
//                      to free all memory allocated with data in a QElmt.
// RETURN: void.
void queue_init(Queue * queue, void (*destroy)(void *))
{
  queue->head = NULL;
  queue->tail = NULL;
  queue->size = 0;
  queue->destroy = destroy;
}

// FUNCTION: queue_enqueue O(1) -- enqueues the key data to the end of the list.
// PARAMETERS: queue: (Queue *) -- the queue to be operated on.
//             data: (const void *) -- the data to be enqueued.
// RETURN: int -- 0 on success, -1 on failure.
int queue_enqueue(Queue * queue, void * data)
{
  QElmt * new;

  if (data == NULL || (new = (QElmt *)malloc(sizeof(QElmt))) == NULL)
    return -1;

  new->data = data;

  if (queue_isempty(queue)) {
    // Handle queueing when the queue is empty.
    queue->head = new;
    queue->tail = new;
    new->next = NULL;

  } else {
    // Handle queueing when it's not.
    queue->tail->next = new;
    new->next = NULL;
    queue->tail = new;

  }

  queue->size++;
  return 0;
}

// FUNCTION: queue_dequeue O(1) -- dequeues the next key and places it in *data.
// PARAMETERS: queue: (Queue *) -- the queue to be operated on.
//             data: (void **) -- location to place the key after dequeueing.
// RETURN: int -- 0 on success, -1 on failure.
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

// FUNCTION: queue_dest O(n) -- removes all nodes from the queue and sets
//           all bytes of the Queue struct to 0. If queue->destroy is set to NULL,
//           does not free the memory associated with the data.
// PARAMETERS: queue: (Queue *) -- the queue to be destroyed.
// RETURN: void.
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

#endif // __ET_QUEUELIST__
