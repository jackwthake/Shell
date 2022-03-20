#if !defined(__TERM_H__)
#define __TERM_H__

#if !defined(abort)
    #define abort(M, ...) printf(M, ##__VA_ARGS__); exit(-1);
#endif

#if !defined(UNUSED)
    #define UNUSED(x) (void)(x)
#endif

#define MAX_BUF 200
#define MAX_ARGS 20

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\033[0m"

extern char **environ;

#endif