#include <stdio.h>

int mult1(int n1, int n2, int n3, int n4)
{
	return n1 + n2 + n3 + n4;
}

int mult2(int *num, int len)
{
	int i, tmp = 0;
	for(i = 0; i < len; i++)
		tmp += num[i];
	return tmp;
}

int main(void)
{
	int n1 = 1, n2 = 2, n3 = 3, n4 = 4;
	int arr[4] = {1, 2, 3, 4};

	printf("res = %d\n", mult1(n1, n2, n3, n4));
	printf("res = %d\n",
		mult2(arr, sizeof(arr)/sizeof(int)));

	return 0;
}
