#include <time.h>
#include <stdio.h>
#include <stdlib.h>

/* void 타입 = 아무것도 받지 않음 */
int rand_init(void)
{
	srand(time(NULL));
	return rand() % 3 + 1;
}

void switch_test(int num)
{
	switch(num)
	{
		case 1:
			printf("1 Detected\n");
			/* break 는 강제로 여기서 멈추란 뜻
			   좀 더 구체적으로 switch 문을 빠져나감 */
			break;
		case 2:
			printf("2 Detected\n");
			break;
		default:
			printf("Wrong Number\n");
			break;
	}
}

int main(void)
{
	int num = rand_init();
	printf("num = %d\n", num);
	switch_test(num);

	return 0;
}






