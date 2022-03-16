CC=gcc
CFLAGS=-Wall -ansi
DFLAGS=-g
PROGS=j_shell
OBJS=

all: $(OBJS) $(PROGS)

j_shell: main.c $(OBJS)
	$(CC) $(CFLAGS) $< -o $@ $(OBJS)

clean:
	rm -f $(PROGS) *.o ~*

clean_mac:
	rm -rf $(PROGS) *.o ~* *.dSYM