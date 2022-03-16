CC=gcc
CFLAGS=-Wall -ansi
DFLAGS=
ifeq ($(debug),1)
DFLAGS=-ggdb
endif

PROGS=j_shell
OBJS=

all: $(OBJS) $(PROGS)

j_shell: main.c $(OBJS)
	$(CC) $(CFLAGS) $(DFLAGS) $< -o $@ $(OBJS)

clean:
	rm -f $(PROGS) *.o ~*

clean_mac:
	rm -rf $(PROGS) *.o ~* *.dSYM