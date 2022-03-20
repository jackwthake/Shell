CC=gcc
CFLAGS=-Wall -ansi
DFLAGS=
ifeq ($(debug),1)
DFLAGS=-ggdb
endif

PROGS=j_shell
OBJS=command.o

all: $(OBJS) $(PROGS)

j_shell: src/main.c $(OBJS)
	$(CC) $(CFLAGS) $(DFLAGS) $< -o $@ $(OBJS)

command.o: src/command.c
	$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@

clean:
	rm -f $(PROGS) *.o ~*

clean_mac:
	rm -rf $(PROGS) *.o ~* *.dSYM