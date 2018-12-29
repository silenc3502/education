#include <stdio.h>

#define __my_section		__attribute__((__section__("my_section")))

struct ro {
	char a;
	int b;
	char * c;
};

struct ro my_ro __my_section =
{
	.a = 'a',
	.b = 3,
	.c = NULL,
};


int main(int argc, char **argv) {
	printf("attribute section test\n");
	printf("a = %c, b =%d, c = %p\n", my_ro.a, my_ro.b, my_ro.c);

	return 0;
}
