CC=gcc
CFLAGS=-g -Wall --std=c99
INCLUDES=-I.
LIBS=-lm
MAIN=prog
SRCS=ita3e.c \
		 ita3e_sort.c \
		 ita3e_Queue.c \
		 ita3e_Stack.c \
		 main.c
OBJS=$(SRCS:.c=.o)

$(MAIN): $(OBJS)
		 $(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
			rm -rf *.o
			rm prog
