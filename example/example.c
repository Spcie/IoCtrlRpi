#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	FILE *fb0 = NULL;
	char Buf[256];

	printf("BUF:%s\n", Buf);

	fb0 = fopen("/dev/IoCtrl", "r+");

	if(fb0 == NULL)
	{
		printf("Open IoCtrl Error!\n");
		return -1;
	}

	fwrite(Buf,sizeof(Buf),1,fb0);

	return 0;
}