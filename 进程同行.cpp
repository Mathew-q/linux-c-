#include<sys/wait.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

int main(void)
{
	pid_t childpid;
	int status;
	int retval;



	childpid = fork(); //创建子进程

	if (-1 == childpid)
	{
		perror("fork()");
		exit(EXIT_FAILURE);
	}
	else if (0 == childpid)
	{
		puts("In child process");
		sleep(100);
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (0 == (waitpid(childpid, &status, WNOHANG)))//判断子进程是否已经退出
		{
			retval = kill(childpid, SIGKILL);
			
			if(retval)
			{
				puts("kill failed");
				perror("kill");
				waitpid(childpid, &status, 0);
			}
			else
			{
				printf("%d killed\n", childpid);
			}
		}

	}

	exit(EXIT_SUCCESS);


}

/*
waitpid();
大家知道，当用fork启动一个新的子进程的时候，子进程就有了新的生命周期，并将在其自己的地址空间内独立运行。但有的时候，我们希望知道某一个自己创建的子进程何时结束，
从而方便父进程做一些处理动作。同样的，在用ptrace去attach一个进程滞后，
那个被attach的进程某种意义上说可以算作那个attach它进程的子进程，这种情况下，有时候就想知道被调试的进程何时停止运行。
以上两种情况下，都可以使用Linux中的waitpid()函数做到。先来看看waitpid函数的定义：

如果在调用waitpid()函数时，当指定等待的子进程已经停止运行或结束了，则waitpid()会立即返回；但是如果子进程还没有停止运行或结束，则调用waitpid()函数的父进程则会被阻塞，暂停运行。
下面来解释以下调用参数的含义：


参数	说明
WNOHANG	如果pid指定的子进程没有结束，则waitpid()函数立即返回0，而不是阻塞在这个函数上等待；如果结束了，则返回该子进程的进程号。
WUNTRACED	如果子进程进入暂停状态，则马上返回。


这些参数可以用“|”运算符连接起来使用。
如果waitpid()函数执行成功，则返回子进程的进程号；如果有错误发生，则返回-1，并且将失败的原因存放在errno变量中。
失败的原因主要有：没有子进程（errno设置为ECHILD），调用被某个信号中断（errno设置为EINTR）或选项参数无效（errno设置为EINVAL）
如果像这样调用waitpid函数：waitpid(-1, status, 0)，这此时waitpid()函数就完全退化成了wait()函数。


*/