#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

int main(void)
{
	pid_t child1, child2;

	printf("Parent is running\n");

	signal(SIGCHLD, SIG_IGN);


	child1 = fork();
	if (child1 == -1) {
		printf("Fail to fork child1\n");
		exit(1);
	} else if (child1 == 0) {
		printf("Child1 enter sleep\n");
		sleep(30);
		printf("Child1 wakes up and exit\n");
		exit(0);
	}

	printf("Fork child1 successfully\n");
	child2 = fork();
	if (child2 == -1) {
		printf("Fail to fork child2\n");
		waitpid(child1, NULL, 0);
		exit(1);
	} else if (child2 == 0) {
		printf("Child2 exit now\n");
		exit(0);
	}

	printf("Fork child2 successfully, and wait any child\n");
	pid_t ret = waitpid(-1, NULL, 0);
	if (ret == -1) {
		printf("waitpid return -1, errno(%d): %s\n", errno, strerror(errno));
	}

	printf("Parent exit\n");
	
	return 0;
}
