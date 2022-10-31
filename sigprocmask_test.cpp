#include<sys/wait.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>


void handler(int sig)
{

	printf("Deal SIgINT");

}

int main(void)
{
	sigset_t newmask;
	sigset_t oldmask;
	sigset_t pendmask;


	struct sigaction act;
	act.sa_handler = handler;

	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	sigaction(SIGINT, &act, 0);

	sigemptyset(&newmask);
	sigaddset(&newmask,,SIGINT);
	sigprocmask(SIG_BLOCK, &newmask,&oldmask);
	sleep(5);

	sigpending(&pendmask);


	if(sigismember(&pendmask.SIGINT))
		printf("SIGINT pending\n");

	sigprocmask(SIG_SETMASk, &oldmask, NULL);

	printf(" signal unblocked");
	sleep(5); 
	return 0;


}

