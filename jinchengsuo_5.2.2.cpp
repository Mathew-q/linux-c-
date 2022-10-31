#include <stdio.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

static char* started_pid  filename default = "/var/run/test.pid";


static bool check_pid(char* pid_file) {

	struct stat stb;
	FILE* pid_file;


	if (stat(pid file, &stb) == 0) 
	{
		pidfile = fopen(pid file, "r");

		if (pidfile)
		{
			char buf[64];
			pid_t pid = 0;
			memset(buf, 0, sizeof(buf));

			if (fread(buf, 1, sizeof(buf), pidfile))
			{
				buf[sizeof(buf) - 1] = '\0';
				pid = atoi(buf);
			}
			fclose(pidfile);

			if (pid && kill(pid, 0) == 0)
			{
				return 1;

			}
		
		}
		printf("remving pidfile '%s',process not running", pid_file);
		unlink(pid_file);



	}

	return 0;


}
int main()
{
	FILE* fd = fopen(stater pid file default, "w");

	if (fd) {
		fprintf(fd, "%u\n", getpid());
		fclose(fd);
	}
	if(check pid(stater pid file default))
	{
		printf("test is already running (%s exists)",stater pid file default);
	}
	else
		printf("test is NOT running (%s not exists)", stater pid file default);

	unlink(stater pid file default);
	return 0;

}


