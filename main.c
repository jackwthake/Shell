#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <printf.h>

#define abort(M, ...) printf(M, ##__VA_ARGS__); exit(-1);
#define UNUSED(x) (void)(x)

#define MAX_BUF 200
#define MAX_ARGS 20

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

extern char **environ;

int parse_line(char *buf, char **argv, int *argc) {
    int argv_ind = 0;    
    char *token = strtok(buf, " ");

    if (*buf == '\n')
        return 0;

    while (token) { /* tokenize arguments */
        if (argv_ind == MAX_ARGS - 1) {
            ++argv_ind;
            break;
        }

        size_t length = strnlen(token, MAX_BUF);

        /* copy into argv */
        argv[argv_ind] = calloc(length, sizeof(char)); /* TODO: fix this memory leak */
        memcpy(argv[argv_ind], token, length);
        argv[argv_ind][length] = '\0'; /* ensure null terminator */

        token = strtok(NULL, " "); /* get next token */
        ++argv_ind;
    }

    *argc = argv_ind;
    argv[argv_ind - 1][strnlen(argv[argv_ind - 1], MAX_BUF) - 1] = '\0'; /* remove new line */

    if (strncmp(argv[*argc - 1], "&", 1) == 0) /* check for background process */
        return 1;
    
    return 0;
}

void eval(char *cmd_buf) {
    char *argv[MAX_ARGS] = { 0 };
    pid_t pid;
    int argc, bg = parse_line(cmd_buf, argv, &argc);

    if (argv[0] == NULL || argc == 0) /* don't attempt to run empty line */
        return;

    if ((pid = fork()) == 0) { /* fork and then run in child process */
        if (execvp(argv[0], argv) < 0) {
            abort("%s: Command not found\n", argv[0]);
        }
    }

    if (!bg) { /* allow things to run in the background */
        int status;
        if (waitpid(pid, &status, 0) < 0) {
            abort("waitpid error\n");
        }

        printf("%s%d exited with code %d.%s\n", KRED, pid, status, KNRM);
    } else {
        printf("Background process %d: %s\n", pid, argv[0]);
    }
}

int main(int argc, char **argv) {
    char cmd_buf[MAX_BUF] = { 0 };

    for (;;) {
        char *wd = getcwd(NULL, 0);
        printf("[%s %s %s] $ ", KGRN, wd, KNRM);
        free(wd);

        /* get next input line */
        if ((fgets(cmd_buf, MAX_BUF, stdin) != cmd_buf) && feof(stdin)) {
            abort("Encountered error in STDIN\n");
        }

        /* check for exit, TODO: build in some commands in a cleaner way */
        if (strncmp(cmd_buf, "exit\n", 5) == 0) {
            break;
        }

        eval(cmd_buf);
    }

    return 0;
}