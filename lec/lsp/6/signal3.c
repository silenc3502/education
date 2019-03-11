#include <signal.h>
#include <unistd.h>

int main(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGABRT, SIG_IGN);
	signal(SIGSTOP, SIG_IGN);
	signal(SIGKILL, SIG_IGN);

	for(;;)
		pause();

	return 0;
}
