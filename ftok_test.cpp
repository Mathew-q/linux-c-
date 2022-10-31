#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/sem.h>


int main_ftok()
{
	key_t semkey;
	if ((semkey = ftok("./test", 123)) < 0) 
	{
		printf("ftok failed\n");
		exit(EXIT_FAILURE);
	}

	printf("ftok ok,semkey = %d\n",semkey);
	return 0;

}

int main_ftok_key()
{

	char filename[50];
	struct stat buf;

	int ret;
	
	strcpy(filename, "./test");
	ret = stat(filename, &buf);
	if (ret) 
	{
		printf("stat error\n");
		return -1;
	
	}

	printf(" %x ,  %x  , %x")

}