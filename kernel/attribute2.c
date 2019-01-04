#include <stdio.h>

#define __my_ss					__attribute__((__section__(".my_ss")))
#define  INFO_NAME(counter)  INFO_CAT(INFO_, counter)
#define  INFO_CAT(a, b)      INFO_DUMMY() a ## b
#define  INFO_DUMMY()

struct mystruct
{
    char name[255];
    int (*on_init) (int num1);
    int (*on_do_something) (int num1);
};

struct manager
{
	struct mystruct arr[3];
	int finish[0];
};

struct mystruct *__start_info;
struct mystruct *__stop_info;

static int _print_number(int x)
{
    printf("%d\n", x);
}

__my_ss static struct manager man = {
	.arr = {
   		{
        	.name = "mary",
        	.on_init = _print_number,
        	.on_do_something = _print_number
    	},
		{
        	.name = "joe",
        	.on_do_something = _print_number
    	},
		{ 
       		.name = "bob",
        	.on_do_something = _print_number
    	}
	}
};

#if 0
__my_ss static const struct mystruct INFO[] = {
    {
        .name = "mary",
        .on_init = _print_number,
        .on_do_something = _print_number
    },
	{
        .name = "joe",
        .on_do_something = _print_number
    },
	{ 
        .name = "bob",
        .on_do_something = _print_number
    }
	int finish[0]
};
#endif

//int mem __my_ss = 3;

int main(void)
{
	__start_info = man.arr;
	__stop_info = (struct mystruct *)man.finish;
	struct mystruct *iter = __start_info;

    for ( ; iter < __stop_info; ++iter)
    {
        printf("element name: %s\n", iter->name);
        if (iter->on_init != NULL)
        {
            iter->on_init(1);
        }
        if (iter->on_do_something != NULL)
        {
            iter->on_do_something(2);
        }
    }

	//printf("mem = %d\n", mem);

	return 0;
}
