#ifndef LIBTURTLE_H
#define LIBTURTLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include "bitman.h"

#define att(type) __attribute__((type))

#define DEFAULT_COLOR "black" /* Turtle's pen default color */

/* turtle's flags */
enum _turtleStateT {
    STATE_PENDOWN   = 1 <<  1, /*  */
    STATE_PENERASER = 1 <<  2, /* ERASER - if true, erase. Don't draw */
    STATE_ENDOFINS  = 1 <<  3, /* END OF INStructions - if true, no more instructions beyond */
};
typedef enum _turtleStateT turtleStateT;

struct _turtleT {
    unsigned int x, y;
    char* color;
    turtleStateT state;
    unsigned short int angle;
};
typedef struct _turtleT *turtleT;

/* pointer to function used to handle instruction */
typedef int (*inshandler) (turtleT turtle, unsigned int argc, const char** argv);

struct _ins { 
    const char *strrep;    /* string representation of command */
    inshandler handler;    /* pointer to function specific to the cmd entered */
};
typedef struct _ins ins;

void freeTurtle(turtleT turtle);
turtleT initTurtle(const char* color,
                   unsigned int startx,
                   unsigned int starty,
                   unsigned short int startangle);
const char* changeColor(turtleT turtle, const char* newcolor);
int changeAngle(turtleT turtle, short int newangle);
char** tokenate(const char* string, const char* separators, unsigned int *ntokens);
int executeLine(turtleT turtle, const char **tokenatedline, unsigned int ntokens);

#endif
