#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM                     100
#define PAGENUM         6

typedef struct __mem_man
{
	int used_flag;
	int usage;
	int idx;
	struct __mem_man *link;
} mem_man;

void init_arr(int *arr)
{
	int i;

	for (i = 0; i < NUM; i++)
		arr[i] = rand() % 131072 + 1;
}

int find_opt_idx(int req_mem)
{
	int i, tmp, cnt = 0;
	tmp = req_mem >> 12;

	for (i = 0; i < PAGENUM; i++)
	{
		if (!tmp)
			break;
		tmp >>= 1;
		cnt++;
	}

	return cnt;
}

mem_man *get_mm_node(void)
{
	mem_man *tmp;

	tmp = (mem_man *)malloc(sizeof(mem_man));
	tmp->link = NULL;
	tmp->used_flag = 1;

	return tmp;
}

void link_test(mem_man **mm, int *arr)
{
	int i, idx;
	mem_man **tmp = NULL;

	for (i = 0; i < NUM; i++)
	{
		idx = find_opt_idx(arr[i]);
		tmp = mm + idx;

redo:
		if (!*tmp)
		{
			(*tmp) = get_mm_node();
			(*tmp)->idx = i;
			(*tmp)->usage = arr[i];
			//(*tmp)->usage = (1 << (12 + idx)) - arr[i];
		}
		else
		{
			tmp = &(*tmp)->link;
			goto redo;
		}
	}
}

void mem_man_info(mem_man *mm[PAGENUM])
{
	int i, total_dissipation = 0;
	mem_man *tmp;

	for (i = 0; i < PAGENUM; i++)
	{
		tmp = mm[i];
		printf("It's for page[%2d] = %6d\n", i, 1 << (12 + i));
		while (tmp)
		{
			total_dissipation += ((1 << (12 + i)) - tmp->usage);
			printf("idx = %2d, used_flag = %s,\
					usage = %6d, link = %s\n",
					tmp->idx, tmp->used_flag ? "Yes" : "No",
					tmp->usage, tmp->link ? "Yes" : "No");

			tmp = tmp->link;
		}
	}

	printf("Total Dissipation = %d\n", total_dissipation);
}

int main(void)
{
	int arr[NUM] = { 0 };
	mem_man *mm[PAGENUM] = { 0 };

	srand(time(NULL));

	init_arr(arr);
	link_test(&mm, arr);
	mem_man_info(mm);

	return 0;
}
