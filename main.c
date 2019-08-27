#include "libturtle.h"

int main(int argc, const char** argv){
    unsigned int ntokens = 0;
    char **tokenated = NULL;
    char* source = NULL;
    char* line = NULL;
    size_t read = 0;
    FILE* fp = NULL;
    size_t len = 0;


    /* TODO: Needs a bit more robust method */
    /* Handle main input arguments */
    if (argc > 1){
        source = strdup(argv[1]);
        if (!source)
            return 0;
        fp = fopen(source, "r");
        if (!fp) {
            perror(NULL);
            free(source);
            return 0;
        }
    }
    else
        /* If no filepath supplied, use stdin */
        fp = stdin;


    turtleT turtle = initTurtle("default", 0, 0, 0);
    if (!turtle)
        return 1;

    /* TODO: We should handle getline errors in a better way conforming to man */
    /* TODO: Add support for piped stdin when no target file is specified */
    while (IS_FLAG_FALSE(turtle->state, STATE_ENDOFINS) && ((read = getline(&line, &len, fp)) != -1)){
        
        char **tokenated = tokenate(line, " \r\t", &ntokens);
        if(executeLine(turtle, (const char**) tokenated, ntokens) == 2)
            fprintf(stderr, "Unsupported instruction\n");

        /* free the tokenated arrays */
        /* TODO: Create a better way of handling string arrays - less frequent frees while working with them */
        for (unsigned int i = 0; i<ntokens; i++) {
            if (tokenated[i])      
                free(tokenated[i]);
        }
        free(tokenated);
    }


    freeTurtle(turtle);
    free(tokenated);
    free(source);
    free(line);

    return 0;
}
