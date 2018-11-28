#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int rand_init(void)
{
	srand(time(NULL));
	return rand() % 9 + 1;
}

void for_test(int num)
{
	int i;

	/* for(초기화; 조건문; 증감식)
	   Visual Studio(Windows) 에서 작업을 해왔다면
	   아주 안좋은 습관이 하나 있을 수 있다.
	   윈도우는 for(int i = 0; ~~~)
	   위와 같은 것을 허용하는 반면
	   리눅스나 표준 C 언어는
	   위와 같은 것을 허용하지 않음
	   C 언어는 철저한 설계하에
	   프로그래밍을 한다는 가정을 하기 때문에
	   변수 선언은 처음에 다 해둬야 함

	   또한 초기화 파트는 for 문 진입시
	   오직 딱 한 번만 실행함

	   조건문에 오는 조건이 만족하면
	   for 문 내부로 진입하게 되고
	   만족하지 않는다면 for 문을 빠져나감

	   증감식은 for 문 내부의 코드가
	   한 번 수행되면 이후에 증감식을 진행하게됨

	   아래를 예로 들어보자면
	   처음 for 문 진입시 i = 0 으로 초기화 하고
	   i < num 을 비교하게 됨
	   i = 0 이고 num 은 최소한 1 이므로 참임
	   조건이 참이므로 for 문 내부로 들어가서
	   printf() 코드를 수행하게 됨
	   내부 코드가 완료되었으므로 증감식을 진행함
	   즉 i = 0 이였는데 ++ 을 함으로써 i = 1 이 됨
	   num 이 2 라고 가정하고 조건을 비교하면
	   다시 한 번 조건이 참이므로
	   for 문 내부로 들어감
	   그리고 다시 printf() 를 수행하고
	   증감식을 수행하여 i = 2 가 됨
	   이제 더 이상 i < num 의 조건을
	   만족하지 않으므로 for 문을 빠져나감 */
	for(i = 0; i < num; i++)
	{
		printf("num = %d\n", i);
	}
}

int main(void)
{
	int num = rand_init();
	for_test(num);

	return 0;
}
