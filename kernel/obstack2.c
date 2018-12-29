#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <obstack.h>

#define obstack_chunk_alloc malloc
#define obstack_chunk_free free

typedef struct node
{
    int val;
    struct node * next;
} node_t;


void obstack_test(int n)
{
	int i;
	struct obstack obst;

	obstack_init(&obst);

	// n - 1 에 해당하는 메모리 할당
	char *str = obstack_alloc(&obst, n * sizeof(str[0]));

	// 노드 n 개에 대한 배열 할당
	node_t **nodes = obstack_alloc(&obst, n * sizeof(nodes[0]));

	// obstack 의 현재 위치 마킹
	void *mark = obstack_base(&obst);

	// 노드 할당
	for(i = 0; i < n; i++)
		nodes[i] = obstack_alloc(&obst, sizeof(nodes[0]));

	// 마킹 해제
	obstack_free(&obst, mark);

	// 정리
	obstack_free(&obst, NULL);
}

void set_char(char c)
{
	struct obstack stack;

	obstack_init(&stack);

	// growing object 가 있을 경우 강종
	assert(obstack_object_size(&stack) == 0);

	// growing object 추가
	obstack_1grow(&stack, c);

	if(obstack_object_size(&stack) == 0)
		return;

	printf("char data = %s\n", (char *)obstack_finish(&stack));

	obstack_free(&stack, NULL);
}

void set_int(int num)
{
	struct obstack stack;

	obstack_init(&stack);

	assert(obstack_object_size(&stack) == 0);

	obstack_int_grow(&stack, num);

	if(obstack_object_size(&stack) == 0)
		return;

	printf("int data = %d\n", *((int *)obstack_finish(&stack)));

	obstack_free(&stack, NULL);
}

void set_pnt(char *str)
{
	char *test;
	char **string;
	struct obstack stack;

	obstack_init(&stack);

	assert(obstack_object_size(&stack) == 0);

	obstack_ptr_grow(&stack, str);

	if(obstack_object_size(&stack) == 0)
		return;

	string = (char **)obstack_finish(&stack);
	printf("pointer = %s\n", string[0]);

	test = (char *)obstack_finish(&stack);
	printf("test = %s\n", test);

	obstack_free(&stack, NULL);
}

int main(void)
{
	obstack_test(7);

	set_char('C');
	set_int(3);
	set_pnt("pointer");

	return 0;
}
