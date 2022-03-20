#if !defined(__COMMAND_H__)
#define __COMMAND_H__

typedef int (*command_func)(int argc, char **argv);

/* pair of command and it's identifier */
typedef struct com_pair {
    command_func func;
    unsigned id_length;
    char *id;
} com_pair;

/* node in command hash table */
typedef struct com_hash_node {
    com_pair pair;
    struct com_hash_node *next;
} com_hash_node;

/* hash table of intrinsic commands such as cd */
typedef struct com_hash_table {
    com_hash_node **table;
    unsigned length;
} com_hash_table;


/* com pair functions */
void create_command(com_pair *, const char *, command_func callback);
void destroy_command(com_pair *);

/* hash node functions */
void create_node(com_pair *, com_hash_node *);
void execute_node(com_hash_node *);
void destroy_node(com_hash_node *);

/* hash table functions */
void initialise_table(com_hash_table *);
int search_and_execute(com_hash_table *);
void destroy_table(com_hash_table *);

#endif