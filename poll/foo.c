#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <poll.h>

int main()
{
	int fd = 0;
	char buf[11];
	int ret, pret;

	struct pollfd fds[1];
	int timeout;

	while(1)
	{
		fds[0].fd = fd;
		fds[0].events = 0;
		fds[0].events |= POLLIN;

		timeout = 5000;

		pret = poll(fds, 1, timeout);

		if(pret == 0)
		{
			printf("ret : %d\n", ret);
			printf("timeout\n");
		}
		else
		{



			memset((void * )buf, 0, 11);
			ret = read(fd, (void *)buf, 10);
			printf("ret : %d\n", ret);


			if(ret != -1)
			{
				buf[ret - 1] = '\0';
				printf("buf : %s\n", buf);
			}
		}	
	}

	return 0;
}

