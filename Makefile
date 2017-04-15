CC=gcc
CFLAGS=--std=c99
DFLAGS=-pg -Wall -DITA3E_DEBUG
FLAGS=$(CFLAGS) $(DFLAGS)
# -gdwarf-3
INCLUDES=-I include
LIBS=-lm
MAIN=prog
SRCS=src/ita3e.c \
		 src/ita3e_queue.c \
		 src/ita3e_queue_test.c \
		 src/ita3e_stack.c \
		 src/ita3e_stack_test.c \
		 src/ita3e_indexedseq.c \
		 src/ita3e_indexedseq_test.c \
		 src/ita3e_sort.c \
		 src/ita3e_sort_test.c \
		 src/ita3e_list.c \
		 src/ita3e_list_test.c \
		 src/ita3e_btree.c \
		 src/main.c
OBJS=$(SRCS:.c=.o)

$(MAIN): $(OBJS)
		 $(CC) $(FLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LIBS)

.c.o:
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
			rm -rf src/*.o
			rm prog
