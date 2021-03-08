#include <stdio.h>
#include <string.h>
#include <sys/select.h>

int main()
{
	int fd;
	char buf[11];
	int ret, sret;

	//Set fd as input stream
	fd = 0;

	fd_set readfds;
	struct timeval timeout;

	while(1)
	{
		//Initializes readfds
		FD_ZERO(&readfds);
		//Add fd to readfds using set		
		FD_SET(fd, &readfds);

		//Set Timeout
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;

		sret = select(8, &readfds, NULL, NULL, &timeout);

		if(sret == 0)
		{
			printf("sret : %d\ntimeout\n", sret);
		}
		else
		{
			printf("sret : %d\n", sret);
			memset((void *)buf, 0, 11);
			ret = read(fd, buf, 10);
			printf("ret : %d\n", ret);

			if(ret != -1)
			{
				buf[10] = '\0';
				printf("Value in Buffer : %s\n", buf);
			}
		}
	}

	return 0;
}
