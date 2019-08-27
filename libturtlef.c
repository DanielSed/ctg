#include "libturtle.h"

static int insFWD(turtleT turtle, unsigned int argc, const char** argv);
static int insEND(turtleT turtle, unsigned int argc, const char** argv);

/* defines supported turtle commands */
ins insset[] = {
    {.strrep = "FWD",
     .handler = insFWD,
    },
    {.strrep = "END",
     .handler = insEND,
    },

    /* last strrep must always be NULL - used to indicate end of array */
    {.strrep = NULL}
};

/* Instruction set of turtle */

static int
insFWD(att(unused) turtleT turtle,
       unsigned int argc,
       att(unused) const char** argv){
    printf("%s, argc: %d\n", __FUNCTION__, argc);
    return 0;
}

static int
insEND(turtleT turtle,
       att(unused) unsigned int argc,
       att(unused) const char** argv){
    FLAG_SET_TRUE(turtle->state, STATE_ENDOFINS);
    
    return 0;
}

/* initTurtle
 * @color: string representation of color specified in the svg toolkit
 * @startx: starting turtle x position on svg canvas
 * @starty: starting turtle y position on svg canvas
 * @startangle: starting turtle angle on svg canvas
 * - Returns allocated turtle object with pen up, otherwise returns NULL
*/
turtleT
initTurtle(const char* color,
           unsigned int startx,
           unsigned int starty,
           unsigned short int startangle){

    turtleT turtle = malloc(sizeof(*turtle));
    if (!turtle)
        return NULL;

    /*turtle pen color assignement */
    turtle->color = NULL;
    if (!strcmp(color, "default")) 
        changeColor(turtle, DEFAULT_COLOR);
    else
        changeColor(turtle, color);
    if (!turtle->color)
        return NULL;

    /* turtle canvas position/orientation assignement */
    turtle->x = startx;
    turtle->y = starty;
    turtle->angle = changeAngle(turtle, startangle);

    /* turtle pen state assignement */
    FLAG_SET_FALSE(turtle->state, STATE_PENDOWN);
    FLAG_SET_FALSE(turtle->state, STATE_PENERASER);
    FLAG_SET_FALSE(turtle->state, STATE_ENDOFINS);

    return turtle;
}

/* used to free the memory allocated for turtle */
void
freeTurtle(turtleT turtle){
    if (turtle){
        free(turtle->color);
        free(turtle);
    }
}

const char*
changeColor(turtleT turtle, const char* newcolor){
    if (!turtle | !newcolor | !strlen(newcolor))
        return NULL;

    turtle->color = realloc(turtle->color, strlen(newcolor) + 1);
    if (!turtle->color)
        return NULL;

    strcpy(turtle->color, newcolor);
    
    return (const char*) turtle->color;
}

int
changeAngle(turtleT turtle, short int newangle){
    if (!turtle)
        return 1;

    turtle->angle = abs(newangle) % 360;

    return 0;
}

/*  tokenate()
 *  Transform string buffer from to 2D array of individual tokens terminated
 *  with NULL as last tokens value..
 *
 *  On sucessfull separation returns pointer to first token, otherwise NULL
 */
char**
tokenate(const char* string, const char* separators, unsigned int *ntokens){
    if (!string)
        return NULL;

    /* duplicate string so we dont discard const qualifier when tokenizing */
    char *strcopy = strdup(string);
    if (!strcopy) {
        return NULL;
    }

    char** tokenated = NULL;
    char* nexttoken = strtok(strcopy, separators);
    *ntokens = 0;

    /* while there are tokens left */
    while (nexttoken) {
        /* allocate memory for one more token */
        tokenated = realloc(tokenated, sizeof(*tokenated) * ++(*ntokens));
        if (!tokenated)
            goto cleanup;

        /* duplicate the token */
        tokenated[*ntokens-1] = strdup(nexttoken);
        if (!tokenated[*ntokens-1])
            goto cleanup;
        nexttoken = strtok(NULL, separators);
    }
    
    /* adding ending NULL ptr to mark end of tokens */
    tokenated = realloc(tokenated, sizeof(*tokenated) * (*ntokens + 1));
    if (!tokenated)
        goto cleanup;
    tokenated[*ntokens] = NULL;

    /* free the helper string copy */
    free(strcopy);
    strcopy = NULL;

    return tokenated;

 cleanup:
    for (unsigned int i=0; i<=*ntokens; i++){
        if (tokenated[i]) {
            free(tokenated[i]);
            tokenated[i] = NULL;
        }
    }
    
    if (tokenated) {
        free(tokenated);
        tokenated = NULL;
    }

    if (strcopy) {
        free(strcopy);
        strcopy = NULL;
    }
    return NULL;
}

/* getHandlerFromStrrep()
 * @potins - String representation in which to find potential instruction
 * - If @potins is present in insset, returns first occurence in insset,
 *   otherwise return NULL
 */
static ins*
getHandlerFromStrrep(const char* potins){ 
    ins* insiterator = insset;
    while (insiterator->strrep) {
        if (!strncmp(potins, insiterator->strrep, strlen(insiterator->strrep)))
            return insiterator;
        insiterator++;
    }
    
    return NULL;
}

/* executeLine()
 * @turtle - Turtle that is to execute the instruction from @tokenatedline
 * @tokenatedline - Array of strings containing the instruction and arguments
 * @ntokens - Number of tokens in @tokenatedline
 * - On succesfull execution returns the return value of handler corresponding
 *   to instruction found in @tokenatedline. If no supported instruction found
 *   then returns 2. On unsuccesfull execution returns non-zero value.
 */
int
executeLine(turtleT turtle, const char **tokenatedline, unsigned int ntokens){
    ins* insptr = NULL;

    if (ntokens<1 || !tokenatedline || !*tokenatedline ) 
        return 1;

    /* unknown/unsupported instruction */
    if (!(insptr = getHandlerFromStrrep(*tokenatedline)))
        return 2;

    return insptr->handler(turtle, ntokens, tokenatedline);
}
