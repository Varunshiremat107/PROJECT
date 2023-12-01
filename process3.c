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
#define MAX_TEXT 1024
FILE *fp;

struct enviro
{
	int noise;
	int air;
	char weather[10];
};
struct trf
{
	char cam1[10];
	char cam2[10];
	char cam3[10];
};

 struct  scity{
 struct enviro e1;
 struct trf t1;
 int  waste;
};

struct mq
{
	char b1[7][100];
	
};
struct mq data;



void* trafficfunc()
{
		
	
	int shmid;
	struct scity *sm;
	shmid = shmget((key_t)1234,1024,0666);
	fp=fopen("output.txt","a");
	sm =(struct scity *)shmat(shmid, NULL, 0);
	if(strcmp(sm->t1.cam1,"low")==0)
	{
		fprintf(fp,"Route 1 is clear ur good to go\n");

		
	}
	else 
	{
		
		
		fprintf(fp,"Route 1 is high in traffic better avoid\n");
		
	}
	if(strcmp(sm->t1.cam2,"low")==0)
        {
               
		fprintf(fp,"Route 2 is clear ur good to go\n");
        }
        else
        {
                
		fprintf(fp,"Route 2 is high in traffic better avoid\n");
		
        }
        
	if(strcmp(sm->t1.cam3,"low")==0)
        {
                
		fprintf(fp,"Route 3 is clear ur good to go\n");
		
		
        }
        else
        {
                
		fprintf(fp,"Route 1 is high in traffic better avoid\n");
		
        }
        fclose(fp);


	return NULL;
}

void* wastefunc()
{

	
	int shmid;
	struct scity *sm;
	shmid = shmget((key_t)1234,1024,0666);
	fp=fopen("output.txt","a");
	sm =(struct scity *)shmat(shmid, NULL, 0);
	int waste=sm->waste;
	char buff[40];
	sprintf(buff,"the amount of waste is %d\n",waste);
	fprintf(fp,"%s\n",buff);
	fclose(fp);
	return NULL;
	
}
void* envfunc()
{
		
	
	int shmid;
	struct scity *sm;
	shmid = shmget((key_t)1234,1024,0666);
	sm =(struct scity *)shmat(shmid, NULL, 0);
	fp=fopen("output.txt","a");
	if(sm->e1.noise >=0 && sm->e1.noise <=50)
	{
		
		fprintf(fp,"Noise is in the low range \n");
		
		
	}
	else if(sm->e1.noise >=50 && sm->e1.noise<=100)
	{
		
		fprintf(fp,"Noise id the medium range \n");
		
	}
	else 
	{
		
		fprintf(fp,"TOO noisy outside be aware\n");
		
	}
	if(sm->e1.air >=0 && sm->e1.air<=200)
	{
		
		fprintf(fp,"Air quality is good u can go \n");
		
		
	}
	else if(sm->e1.air >=200 && sm->e1.air<=350)
	{
		
		fprintf(fp,"Air quality is quite bad better wear a mask \n");
		
	}
	else
	{
		
		fprintf(fp,"Air quality is too bad be alert\n");
		
	}
	if(strcmp(sm->e1.weather,"rainy")==0)
	{
		
		fprintf(fp,"Its Rainy outside take ur umbrella\n");
		
		
	}
	else if(strcmp(sm->e1.weather,"cloudy")==0)
        {
                
               fprintf(fp,"Its cloudy outside wait for sometime  \n");
		
        }
	else 
		
        {
                
                fprintf(fp,"Its clear  outside u can go out \n");
		
        }
        fclose(fp);
	return NULL;

}
		




int main()
{
  struct scity *sm;
  int shmid;
  pthread_t t1,t2,t3;
  
  
  shmid = shmget((key_t)1234,1024,0666);
  printf("key of the shared memory is : %d\n",shmid); 
  sm =(struct scity *)shmat(shmid, NULL, 0);
  //printf("camera 1 %s\n",sm->t1.cam1);
  //printf("camera 2%s\n",sm->t1.cam2);
  //printf("camera 2 %s\n",sm->t1.cam3);
  //printf("waste %d\n",sm->waste );
  //printf("noise %d\n",sm->e1.noise);
  //printf("air %d\n",sm->e1.air);
  //printf("weather %s\n",sm->e1.weather);


  pthread_create (&t1,NULL,trafficfunc,NULL);
  pthread_join(t1,NULL);
  pthread_create (&t2,NULL,wastefunc,NULL);
  pthread_join(t2,NULL);
  pthread_create (&t3,NULL,envfunc,NULL);
  pthread_join(t3,NULL);
  
  
  
  }
  
