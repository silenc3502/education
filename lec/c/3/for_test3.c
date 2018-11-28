#include <stdio.h>

int main(void)
{
	int i, j, cnt = 0;

	/* 이중 초기화
	   for 문의 초기화 파트에서
	   여러 변수를 동시에 초기화 할 수 있음 */

	// for(i = 0, j = 3; i != j; j--, i++)

	// 주석이 적용된 위의 코드는
	// i 와 j 에 대한 증감식도 동시에 적용함
	// 그러나 i 가 1 이 되고 j 는 2 가 되서
	// 조건이 만족할 수 없게 되어 무한 루프가 됨

	for(i = 0, j = 3; i != j; j--)
		printf("cnt = %d\n", cnt++);

	return 0;
}



