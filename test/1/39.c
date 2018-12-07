#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct __queue
{
	int data;
	int idx;
} queue;

typedef struct __queue_manager
{
	int cur_idx;
	int elem_num;
	int start_idx;
	queue *arr;
} qm;

typedef struct __free_arr
{
	int cur_idx;
	int elem_num;
	int *arr;
} fa;

void init_queue_manager(qm *m)
{
	queue *tmp = (queue *)malloc(sizeof(queue) * 128);
	memset(tmp, 0x0, sizeof(queue) * 128);

	(*m).arr = tmp;
	(*m).cur_idx = 0;
	(*m).elem_num = 0;
	(*m).start_idx = 0;
}

void init_free_arr(fa *f)
{
	int *tmp = (int *)malloc(sizeof(int) * 128);
	memset(tmp, 0x0, sizeof(int) * 128);

	(*f).arr = tmp;
	(*f).cur_idx = 0;
	(*f).elem_num = 0;
}

void enqueue(qm *m, int data)
{
	int idx = m->start_idx;

	while(m->arr[idx].data)
		idx = m->arr[idx].idx;

	m->arr[idx].data = data;
	m->elem_num++;
	m->arr[idx].idx = ++m->cur_idx;
}

void dequeue(qm *m, int data, fa *f)
{
	queue tmp;
	int idx = m->start_idx;

	while(m->arr[idx].data)
	{
		if(m->arr[idx].data == data)
		{
			f->arr[f->cur_idx++] = idx;
			f->elem_num++;
			m->elem_num--;

			memmove(&tmp, &m->arr[m->arr[idx].idx], sizeof(queue));

			m->arr[m->arr[idx].idx].data = 0;
			m->arr[m->arr[idx].idx].idx = 0;

			m->arr[idx].data = tmp.data;
			m->arr[idx].idx = tmp.idx;
			//m->arr[m->arr[idx].idx].data;
			return;
		}
		else
			idx = m->arr[idx].idx;
	}

	printf("당신이 지우고자 하는 데이터는 이미 지워졌거나 없습니다.\n");
}

void print_queue(qm m)
{
	int i, j;

	for(i = j = 0; j < m.elem_num; i++, j++)
	{
		if(m.arr[i].data == 0)
			j--;
		else
		{
			printf("data = %3d ", m.arr[i].data);
			printf("next = %3d\n", m.arr[m.arr[i].idx].data);
		}
	}
}

int main(void)
{
	int i;
	int data[14] = {20, 10, 30, 50, 70, 60, 40, 90, 80, 100};
	int del[4] = {50, 70, 10};

	qm manager = {0};
	fa free_arr = {0};

	init_queue_manager(&manager);
	init_free_arr(&free_arr);

	for(i = 0; data[i]; i++)
		enqueue(&manager, data[i]);

	print_queue(manager);

	for(i = 0; del[i]; i++)
		dequeue(&manager, del[i], &free_arr);

	printf("After Delete\n");
	print_queue(manager);

	return 0;
}
