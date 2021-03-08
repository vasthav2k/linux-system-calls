#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <poll.h>

int main(int argc, char *argv[])
{
	int numPipes, i, ready, randPipe, numWrites;
	int (*pfds)[2];
	struct pollfd *pollFd;

	if(argc < 2)
	{
		perror("Invalid number of arguments");
		exit(1);
	}

	numPipes = atoi(argv[1]);

	pfds = calloc(numPipes, sizeof(int[2]));

	if(pfds == NULL)
	{
		perror("Calloc Allocation error\n");
		exit(1);
	}
	pollFd = (struct pollfd *)calloc(numPipes, sizeof(struct pollfd));
	
	if(pollFd == NULL)
	{
		perror("Calloc Poll FD Error\n");
		exit(1);
	}

	for(i = 0;i < numPipes; i++)
	{
		//printf("%d ",pfds[i][0]);
		if(pipe(pfds[i]) == -1)
		{
			perror("pipe\n");
		}
	}

	numWrites = (argc > 2) ? atoi(argv[2]) : 1;

	srandom((int) time(NULL));

	for(i = 0;i < numWrites; i++)
	{
		randPipe = random()%numPipes;
		printf("Writing to fd : %3d (read fd : %3d)\n", pfds[randPipe][1], pfds[randPipe][0]);

		if(write(pfds[randPipe][1], "a",1) == -1)
		{
			printf("Write to fd : %d\n", pfds[randPipe][1]);
		}
	}

	for(i = 0; i < numPipes; i++)
	{
		pollFd[i].fd = pfds[i][0];
		pollFd[i].events = POLLIN;
	}

	ready = poll(pollFd,numPipes, 10000);

	if(ready == -1)
		perror("Poll error\n");

	for(i = 0;i < numPipes; i++)
	{
		if(pollFd[i].revents & POLLIN)
		{
			printf("Readable : %d %3d\n", i, pollFd[i].fd);
		}
	}

	return 0;
}

	
