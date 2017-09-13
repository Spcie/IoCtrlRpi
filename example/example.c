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

	fb0 = fopen("/dev/msic_IoCtrl", "r+");

	if(fb0 == NULL)
	{
		printf("Open IoCtrl Error!\n");
		return -1;
	}

	printf("write!\n");
	fwrite(Buf,sizeof(Buf),1,fb0);
	fclose(fb0);
	printf("close IoCtrl!\n");
	return 0;
}
