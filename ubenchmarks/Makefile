ROOT 	   = ${PWD}
EXECUTABLE = ${ROOT}/test
LIBS	   = -lpthread -lm
INCLUDES   = -I .
CC		   = gcc
CFLAGS	   = -O3

.PHONY: all
all:	test

# Isolated Kernel Analyses
SRCS = \
	  ${ROOT}/common_utils.c					\
	  ${ROOT}/cache_ubench.c					\
	  ${ROOT}/main.c						

OBJS=$(SRCS:.c=.o)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) $(DFLAGS) -c $< -o $@

test: $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(DFLAGS) $(OBJS) -o $(EXECUTABLE) $(LIBS)
	
clean:
	rm -rf $(OBJS)
	rm -rf $(EXECUTABLE)
