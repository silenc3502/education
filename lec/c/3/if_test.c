#include <stdio.h>
#include <stdbool.h>

#if 0

bool 은 stdbool.h 헤더 파일을 포함해야만 사용할 수 있다.
또한 논리 자체를 표현할 수 있어서 아래 보이듯이
false 나 true 를 return 할 수 있어서 꽤 유용하게 사용된다.
최근 C 문법에 추가된 녀석 중 하나임

#endif
bool is_it_even(int value)
{
	// 2 로 나눈 나머지가 1 이면 참 아니면 거짓
	// 즉 짝수면 true 가 반환되고 홀수면 false 가 반환됨
	if(value % 2)
	{
		return false;
	}

	return true;
}

int main(void)
{
	// 3 은 홀수 이므로 false 가 반환되어 else 로 가게됨
	if(is_it_even(3))
	{
		printf("이것은 짝수\n");
	}
	else
	{
		printf("이것은 홀수\n");
	}

	return 0;
}
