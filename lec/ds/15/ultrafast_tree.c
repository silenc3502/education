#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct __tree
{
	int data;
	int left_idx;
	int right_idx;
} tree;

typedef struct __tree_manager
{
	int cur_idx;
	int elem_num;
	int start_idx;
	tree *arr;
} tm;

typedef struct __free_arr
{
	int cur_idx;
	int elem_num;
	int *arr;
} fa;

void init_tree_manager(tm *m)
{
	tree *tmp = (tree *)malloc(sizeof(tree) * 128);
	memset(tmp, 0x0, sizeof(tree) * 128);

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

void tree_ins(tm *m, int data)
{
	int idx = m->start_idx;

	while(m->arr[idx].data)
	{
		if(m->arr[idx].data > data)
			idx = m->arr[idx].left_idx;
		else if(m->arr[idx].data < data)
			idx = m->arr[idx].right_idx;
	}

	m->arr[idx].data = data;
	m->elem_num++;
	m->arr[idx].left_idx = ++m->cur_idx;
	m->arr[idx].right_idx = ++m->cur_idx;
}

int get_chg_node(tm *m, int idx, int ir_idx)
{
	int tmp;

	if(!m->arr[m->arr[ir_idx].right_idx].data)
	{
		//m->arr[ir_idx].left_idx = 0;

		tmp = m->arr[idx].data;
		m->arr[idx].data = m->arr[m->arr[ir_idx].left_idx].data;

		return tmp;
	}
	else if(!m->arr[m->arr[ir_idx].left_idx].data)
	{
		tmp = m->arr[idx].data;
		m->arr[idx].data = m->arr[m->arr[ir_idx].right_idx].data;

		return tmp;
	}
}

int find_max(tm *m, int idx)
{
	int max_idx = idx;

	while(m->arr[max_idx].data)
	{
		if(m->arr[m->arr[max_idx].right_idx].data)
			max_idx = m->arr[max_idx].right_idx;
		else
			return get_chg_node(m, idx, max_idx);
	}
}

int proc_node(tm *m, int idx)
{
	int tmp_idx;

	if(!m->arr[m->arr[idx].right_idx].data)
		return m->arr[m->arr[idx].left_idx].data;
	else if(!m->arr[m->arr[idx].left_idx].data)
		return m->arr[m->arr[idx].right_idx].data;
}

void tree_del(tm *m, int data, fa *f)
{
	int max, tmp;
	int idx = m->start_idx;

	while(m->arr[idx].data)
	{
		if(m->arr[idx].data > data)
			idx = m->arr[idx].left_idx;
		else if(m->arr[idx].data < data)
			idx = m->arr[idx].right_idx;
		else
		{
			f->arr[f->cur_idx++] = idx;
			f->elem_num++;
			m->elem_num--;

			if(m->arr[m->arr[idx].left_idx].data && m->arr[m->arr[idx].right_idx].data)
			{
				max = find_max(m, m->arr[idx].left_idx);
				m->arr[idx].data = max;
				return;
			}
			else
			{
				tmp = proc_node(m, idx);
				m->arr[idx].data = tmp;
				return;
			}
		}
	}

	printf("당신이 지우고자 하는 데이터는 이미 지워졌거나 없습니다.\n");
}

void print_tree(tm m)
{
	int i, j;

	for(i = j = 0; j < m.elem_num; i++, j++)
	{
		if(m.arr[i].data == 0)
			j--;
		else
		{
			printf("data = %3d ", m.arr[i].data);
			printf("left = %3d ", m.arr[m.arr[i].left_idx].data);
			printf("right = %3d\n", m.arr[m.arr[i].right_idx].data);
		}
	}
}

int main(void)
{
	int i;
	int data[14] = {20, 10, 30, 50, 70, 60, 40, 90, 80, 100};
	int del[4] = {50, 70, 10};

	tm manager = {0};
	fa free_arr = {0};

	init_tree_manager(&manager);
	init_free_arr(&free_arr);

	for(i = 0; data[i]; i++)
		tree_ins(&manager, data[i]);

	print_tree(manager);

	for(i = 0; del[i]; i++)
		tree_del(&manager, del[i], &free_arr);

	printf("After Delete\n");
	print_tree(manager);

	return 0;
}
