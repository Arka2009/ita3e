CC=gcc
CFLAGS=-g -Wall --std=c99
INCLUDES=-I include
LIBS=-lm
MAIN=prog
SRCS=src/ita3e.c \
		 src/ita3e_sort.c \
		 src/ita3e_queue.c \
		 src/ita3e_queue_test.c \
		 src/ita3e_stack.c \
		 src/ita3e_stack_test.c \
		 src/ita3e_indexedseq.c \
		 src/ita3e_indexedseq_test.c \
		 src/main.c
OBJS=$(SRCS:.c=.o)

$(MAIN): $(OBJS)
		 $(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
			rm -rf src/*.o
			rm prog
