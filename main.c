#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <printf.h>

#define abort(M, ...) printf(M, ##__VA_ARGS__); exit(-1);
#define UNUSED(x) (void)(x)

#define MAX_BUF 200
#define MAX_ARGS 20

int parse_line(char *buf, char **argv, int *argc) {
    int argv_ind = 0;    
    char *token = strtok(buf, " ");

    while (token) {
        size_t length = strnlen(token, MAX_BUF);

        argv[argv_ind] = calloc(length, sizeof(char));
        memcpy(argv[argv_ind], token, length);
        argv[argv_ind][length] = '\0';

        token = strtok(NULL, " ");
        ++argv_ind;
    }

    *argc = argv_ind;
    if (strncmp(argv[*argc - 1], "&", 1) == 0)
        return 1;
    
    return 0;
}

void eval(char *cmd_buf) {
    char *argv[MAX_ARGS];
    pid_t pid;
    int argc, bg = parse_line(cmd_buf, argv, &argc);

    UNUSED(pid);
    printf("%d\n", bg);
}

int main(int argc, char **argv) {
    char cmd_buf[MAX_BUF] = { 0 };

    for (;;) {
        printf("> "); /* TODO Add to prompt */
        if ((fgets(cmd_buf, MAX_BUF, stdin) != cmd_buf) && feof(stdin)) {
            abort("Encountered error in STDIN\n");
        }

        if (strncmp(cmd_buf, "exit\n", 5) == 0) {
            break;
        }

        eval(cmd_buf);
    }

    return 0;
}