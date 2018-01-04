/******************************************************************************
 * NAME:	    qlist.h
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    Header file containing the typedefs and macros for the
 *		    implementation of a Queue using Lists in qlist.c.
 *
 * CREATED:	    05/09/2017
 *
 * LAST EDITED:	    01/04/2018
 ***/

#ifndef __ET_QLIST_H__
#define __ET_QLIST_H__

/******************************************************************************
 * TYPE DEFINITIONS
 ***/

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

/******************************************************************************
 * MACRO DEFINITIONS
 ***/

#define queue_peek(queue) ((queue)->head)
#define queue_size(queue) ((queue)->size)
#define queue_isempty(queue) ((queue)->size == 0 ? 1 : 0)

/******************************************************************************
 * API FUNCTION PROTOTYPES
 ***/

extern Queue * queue_create(void (*)(void *));
extern int queue_enqueue(Queue *, void *);
extern int queue_dequeue(Queue *, void **);
extern void queue_destroy(Queue **);

#endif /* __ET_QLIST_H__ */

/*****************************************************************************/
