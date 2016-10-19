#include "ita3e.h"

// Implements an Array Stack
struct ArrayStack {
	int elements[MAX_ARRAY_SIZE];
	int top;
	int count;
};

// Implements an Linked Stack
struct LinkedStack {
	struct NodeType * Top;
	int count;
};

// Stack Methods/Operations
void ArrayStackInit	  (struct ArrayStack *);
void DisplayArrayStack(struct ArrayStack *);
int  isArrayStackFull (struct ArrayStack *);
int  isArrayStackEmpty(struct ArrayStack *);
int  ArrayPush				(struct ArrayStack *, int);
int  ArrayPop					(struct ArrayStack *, int *);

void LinkedStackInit	  (struct ArrayStack *);
void DisplayLinkedStack (struct ArrayStack *);
int  isLinkedStackFull  (struct ArrayStack *);
int  isLinkedStackEmpty (struct ArrayStack *);
int  LinkedPush					(struct ArrayStack *, int);
int  LinkedPop					(struct ArrayStack *, int *);



