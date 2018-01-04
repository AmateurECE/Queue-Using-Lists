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

typedef struct _qelmt_ {

  void * data;
  struct _qelmt_ * next;

} qelmt;

typedef struct {

  qelmt * head;
  qelmt * tail;

  int size;
  void (*destroy)(void *);

} qlist;

/******************************************************************************
 * MACRO DEFINITIONS
 ***/

#define qlist_peek(queue) ((queue)->head)
#define qlist_size(queue) ((queue)->size)
#define qlist_isempty(queue) ((queue)->size == 0 ? 1 : 0)

/******************************************************************************
 * API FUNCTION PROTOTYPES
 ***/

extern qlist * qlist_create(void (*)(void *));
extern int qlist_enqueue(qlist *, void *);
extern int qlist_dequeue(qlist *, void **);
extern void qlist_destroy(qlist **);

#endif /* __ET_QLIST_H__ */

/*****************************************************************************/
