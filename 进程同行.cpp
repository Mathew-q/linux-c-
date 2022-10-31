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



	childpid = fork(); //�����ӽ���

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
		if (0 == (waitpid(childpid, &status, WNOHANG)))//�ж��ӽ����Ƿ��Ѿ��˳�
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
���֪��������fork����һ���µ��ӽ��̵�ʱ���ӽ��̾������µ��������ڣ����������Լ��ĵ�ַ�ռ��ڶ������С����е�ʱ������ϣ��֪��ĳһ���Լ��������ӽ��̺�ʱ������
�Ӷ����㸸������һЩ��������ͬ���ģ�����ptraceȥattachһ�������ͺ�
�Ǹ���attach�Ľ���ĳ��������˵���������Ǹ�attach�����̵��ӽ��̣���������£���ʱ�����֪�������ԵĽ��̺�ʱֹͣ���С�
������������£�������ʹ��Linux�е�waitpid()������������������waitpid�����Ķ��壺

����ڵ���waitpid()����ʱ����ָ���ȴ����ӽ����Ѿ�ֹͣ���л�����ˣ���waitpid()���������أ���������ӽ��̻�û��ֹͣ���л�����������waitpid()�����ĸ�������ᱻ��������ͣ���С�
�������������µ��ò����ĺ��壺


����	˵��
WNOHANG	���pidָ�����ӽ���û�н�������waitpid()������������0����������������������ϵȴ�����������ˣ��򷵻ظ��ӽ��̵Ľ��̺š�
WUNTRACED	����ӽ��̽�����ͣ״̬�������Ϸ��ء�


��Щ���������á�|���������������ʹ�á�
���waitpid()����ִ�гɹ����򷵻��ӽ��̵Ľ��̺ţ�����д��������򷵻�-1�����ҽ�ʧ�ܵ�ԭ������errno�����С�
ʧ�ܵ�ԭ����Ҫ�У�û���ӽ��̣�errno����ΪECHILD�������ñ�ĳ���ź��жϣ�errno����ΪEINTR����ѡ�������Ч��errno����ΪEINVAL��
�������������waitpid������waitpid(-1, status, 0)�����ʱwaitpid()��������ȫ�˻�����wait()������


*/