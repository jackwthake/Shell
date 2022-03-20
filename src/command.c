#include "command.h"

#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "term.h"

void create_command(com_pair *pair, const char *name, command_func callback) {
    if (!pair || !name)
        return;
    
    pair->func = callback;
    pair->id_length = strnlen(name, MAX_BUF);
    pair->id = calloc(pair->id_length + 1, sizeof(char));
    if (!pair->id || !strncpy(pair->id, name, pair->id_length)) {
        return;
    }

    pair->id[pair->id_length] = '\0';
}

void destroy_command(com_pair *com) {
    if (com) {
        if (com->id) {
            free(com->id);
        }

        free(com);
    }
}