#include <stdio.h>

int count_upper(char *str)
{
	int i, cnt = 0;

	for(i = 0; str[i]; i++)
		if(str[i] > 64 && str[i] < 90)
			cnt++;

	return cnt;
}

int main(void)
{
	int cnt;
	char str[64] = "Damn it! Where is m Important Pointer ?";

	printf("대문자 개수 = %d\n", count_upper(str));

	return 0;
}
