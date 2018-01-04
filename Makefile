###############################################################################
# NAME:		    Makefile
#
# AUTHOR:	    Ethan D. Twardy
#
# DESCRIPTION:	    Makefile for the executable C code contained in qlist.c
#
# CREATED:	    06/07/2017
#
# LAST EDITED:	    01/04/2018
###

P = qlist
OBJECTS = qlist.c
CFLAGS = -Wall -O3
LDLIBS=
CC=gcc

$(P):
	$(CC) $(CFLAGS) -o $(P) $(OBJECTS) $(LDLIBS)

.PHONY: debug clean

CFLAGS_DEBUG = -g -O0 -Wall -D CONFIG_DEBUG_QLIST

debug:
	$(CC) $(CFLAGS_DEBUG) -o $(P) $(OBJECTS) $(LDLIBS)

clean:
	rm -rf *.c~
	rm -rf *.h~
	rm -rf makefile~

###############################################################################
