#include <stdio.h>
#include <stdlib.h>
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

int main(void)
{
	obstack_test(7);

	return 0;
}
