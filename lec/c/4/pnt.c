#include <stdio.h>

int main(void)
{
	int *p = NULL;
	int num = 3;
	p = &num;

	// tab size adjustment(탭 크기 조정) =>>> 명령 모드에서 :set ts=4
	printf("num = %d\n", num);
	printf("*p = %d\n", *p);

	return 0;
}
