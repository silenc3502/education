/* 자료구조 학습의 의의:
   SW 개발자에게 있어서 머리속 생각을
   프로그램 코드로 바꾸는 것이 무엇보다 중요하다.
   이것이 불가능하다면 단순한 코더가 되고
   이것이 가능해진다면 비로소 그 때 SW 개발자가 될 수 있다.

   자료구조를 학습하는 이유는 머리속에서
   생각한 내용을 코드로 변환하는 훈련을 하는
   일련의 절차라고 보면 된다.

   익숙해지면 이후에는
   생각한 대부분의 모든 것들을 프로그램 코드로 바꿀 수 있다. */
#include <stdio.h>
#include <stdlib.h>

typedef struct __stack
{
	int data;
	struct __stack *link;
} stack;

stack *get_stack_node(void)
{
	stack *tmp = (stack *)malloc(sizeof(stack));
	tmp->link = NULL;

	return tmp;
}

void push(stack **top, int data)
{
	stack *tmp = *top;
	*top = get_stack_node();
	(*top)->data = data;
	(*top)->link = tmp;
}

void print_stack(stack *top)
{
	stack *tmp = top;

	while(tmp)
	{
		printf("tmp->data = %d\n", tmp->data);
		tmp = tmp->link;
	}
}

int pop(stack **top)
{
	int num;
	stack *tmp = *top;

	if(!tmp)
	{
		printf("Stack 이 텅비어 있다.\n");
		return 0;
	}

	num = (*top)->data;
	*top = (*top)->link;

	free(tmp);

	return num;
}

int main(void)
{
	int i;
	stack *top = NULL;

	for(i = 1; i <= 4; i++)
		push(&top, i * 10);

	print_stack(top);

	for(i = 0; i < 5; i++)
		printf("pop data = %d\n", pop(&top));

	return 0;
}




