#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<pthread.h>
#include<sys/msg.h>
#include<sys/types.h>

#define File "output.txt"


int main()
{
	FILE *fp;
	fp=fopen(File,"r");
	char line[256];
	while(fgets(line ,sizeof(line),fp) != NULL)
	{
		printf("%s",line);
	}
	fclose(fp);
	

}
