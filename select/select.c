#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/select.h>

int main(int argc, char *argv[])
{
	fd_set readfds, writefds;
	int ready, nfds, fd, numRead;
	struct timeval timeout;
	struct timeval *pto;
	char buf[10];

	if(argc < 2)
	{
		printf("Incorrect Number of Arguments\n");
		exit(0);
	}

	if(strcmp(argv[1], "-") == 0)
	{
		pto = NULL;
	}
	else
	{
		pto = &timeout;
		timeout.tv_sec = atoi(argv[1]);
		timeout.tv_usec = 0;
	}
	
	nfds = 0;

	//Initialize file descriptors
	FD_ZERO(&readfds);
	FD_ZERO(&writefds);

	for(int i = 2;i < argc; i += 2)
	{
		numRead = sscanf(argv[i], "%d", &fd);
		numRead += sscanf(argv[i + 1], "%s", buf);
		if(numRead != 2)
		{
			printf("File descriptors specified incorrectly\n");
		}
		
		if(fd > FD_SETSIZE)
		{
			printf("File Descriptor esxeeds given limit : %d", FD_SETSIZE);
		}

		if(nfds <= fd)
		{
			nfds = fd + 1;
		}

		if(strrchr(buf, 'r') != NULL)
		{
			printf("%d in read\n", fd);
			FD_SET(fd, &readfds);
			printf("%d\n",FD_ISSET(fd, &readfds)?1:0);
		}

		if(strrchr(buf, 'w') != NULL)
		{
			FD_SET(fd, &writefds);
		}
	}

	ready = select(nfds, &readfds, &writefds, NULL, pto);

	if(ready == -1)
	{
		printf("Error Occured\n");
	}
	else if(ready == 0)
	{
		printf("TimeOut occured\n");
	}
	printf("Value of ready : %d\n", ready);
	
	printf("fd : R : W\n");
	for(fd = 0;fd < nfds; fd++)
	{
		printf("%d : %s %s \n", fd, FD_ISSET(fd, &readfds) ? "Y" : "N", FD_ISSET(fd, &writefds) ? "Y" : "N");
	}

	if(pto != NULL)
	{
		printf("Timeout after select() : %ld.%03ld\n", (long) timeout.tv_sec, (long) timeout.tv_usec / 10000);
	}
	return 0;
}
