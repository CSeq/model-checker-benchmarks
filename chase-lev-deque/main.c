#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <threads.h>
#include <stdatomic.h>

#include "deque.h"

Deque *q;
int a;
int b;

static void task(void * param) {
	a=steal(q);
}

int user_main(int argc, char **argv)
{
	thrd_t t;
	q=create();
	thrd_create(&t, task, 0);
	push(q, 1);
	push(q, 2);
	do {
		b=take(q);
	}	while(b==EMPTY);
	thrd_join(t);
	if (a+b!=3)
		printf("a=%d b=%d\n",a,b);
	return 0;
}
