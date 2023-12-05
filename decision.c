#include"headerfile.h"
#include"structure.h"
// structure for message queue
struct mq
{
	char b1[7][100];
};
struct mq data;
// function for error handling
void error_handler (char *message )
{
	perror(message);
	exit(1);
}
//function for comparision of traffic sensed datas
void* TrafficComparision()
{
	int msqid;
	int shmid;
	struct scity *sm;
	msqid=msgget((key_t)17834,0666 |IPC_CREAT);
	if(msqid==-1)
	{
		error_handler("message queue creation is unsuccesful");
	}
	shmid = shmget((key_t)1234,1024,0666);
	if(shmid ==-1)
	{
		error_handler("Acessing of shared memory failed ");
	}
	sm =(struct scity *)shmat(shmid, NULL, 0);
	if(sm->t1.cam1<=50)
	{
		strcpy(data.b1[0],"ROUTE SENSED IN CAMERA 1 IS CLEAR IN TRAFFIC YOU ARE GOOD TO GO IN THIS ROUTE");
		msgsnd(msqid, &data, sizeof(data.b1), 0);
	}
	else
	{
		strcpy(data.b1[0],"ROUTE SENSED IN CAMERA 1 IS HIGH IN TRAFFIC BETTER AVOID  THIS ROUTE ");
		msgsnd(msqid, &data, sizeof(data.b1), 0);
	}
	if(sm->t1.cam2<=50)
	{
		strcpy(data.b1[1],"ROUTE SENSED IN CAMERA 2 IS CLEAR IN TRAFFIC YOU ARE GOOD TO GO IN THIS ROUTE  ");
		msgsnd(msqid, &data, sizeof(data.b1),0);
	}
	else
	{
		strcpy(data.b1[1],"ROUTE SENSED IN CAMERA 2 IS HIGH IN TRAFFIC BETTER AVOID THIS ROUTE ");
		msgsnd(msqid, &data, sizeof(data.b1), 0);
	}
	if(sm->t1.cam3<=50)
	{
		strcpy(data.b1[2],"ROUTE SENSED IN CAMERA 3 IS CLEAR IN TRAFFIC YOU ARE GOOD TO GO IN THIS ROUTE  ");
		msgsnd(msqid, &data, sizeof(data.b1), 0);
	}
	else
	{
		strcpy(data.b1[2],"ROUTE SENSED IN CAMERA 3 IS HIGH IN TRAFFIC BETTER AVOID THIS ROUTE ");
		msgsnd(msqid, &data, sizeof(data.b1), 0);
	}
	return NULL;
}
//function for waste sended data to make decision
void* WasteComparision()
{
	int msqid;
	int shmid;
	struct scity *sm;
	msqid=msgget((key_t)17834,0666 | IPC_CREAT);
	if(msqid==-1)
	{
		error_handler("message queue accesing is unsuccesful");
	}
	shmid = shmget((key_t)1234,1024,0666);
	if(shmid ==-1)
	{
		error_handler("Acessing of shared memory failed ");
	}
	sm =(struct scity *)shmat(shmid,NULL,0);
	//int waste=sm->waste;
	char buff[40];
	sprintf(buff,"THE AMOUNT OF WASTE SENSED  :  %d K.G\n",sm->waste);
	strcpy(data.b1[3],buff);
	msgsnd(msqid, &data, sizeof(data.b1),0);
	return NULL;
}
// function for comparision of envirionmenr sensed data
void* EnvComparision()
{
	int msqid;
	int shmid;
	struct scity *sm;
	msqid=msgget((key_t)17834,0666 | IPC_CREAT);
	if(msqid==-1)
	{
		error_handler("message queue accesing is unsuccesful");
	}
	shmid = shmget((key_t)1234,1024,0666);
	sm =(struct scity *)shmat(shmid, NULL, 0);
	if(shmid ==-1)
	{
		error_handler("Acessing of shared memory failed ");
	}
	if(sm->e1.noise >=20 && sm->e1.noise <=60)
	{
		strcpy(data.b1[4],"NOISE SENSED IS IN LOW RANGE ");
		msgsnd(msqid, &data, sizeof(data.b1), 0);
	}
	else if(sm->e1.noise >=60 && sm->e1.noise<=80)
	{
		strcpy(data.b1[4],"NOISE SENSED IS IN MEDIUM RANGE ");
		msgsnd(msqid, &data, sizeof(data.b1), 0);
	}
	
	else
	{
		strcpy(data.b1[4],"NOISE SENSED FROM THE SENSOR IS TOO HIGH BE AWARE ");
		msgsnd(msqid, &data, sizeof(data.b1), 0);
	}
	
	if(sm->e1.air >=0 && sm->e1.air<=100)
	{
		strcpy(data.b1[5],"AIR QUALITY SENSED IS GOOD  ");
		msgsnd(msqid, &data, sizeof(data.b1), 0);
	}
	else if(sm->e1.air >=100 && sm->e1.air<=2000)
	{
		strcpy(data.b1[5],"AIR QUALITY SENSED IS QUITE BAD BETTER WEAR A MASK ");
		msgsnd(msqid, &data, sizeof(data.b1), 0);
	}
	else
	{
		strcpy(data.b1[5],"AIR QUALITY SENSED IS TOO BAD BETTER DO NOT GO OUT ");
		msgsnd(msqid, &data, sizeof(data.b1), 0);
	}
	if(strcmp(sm->e1.weather,"Rainy")==0)
	{
		strcpy(data.b1[6],"WEATHER SENSED IS RAINY BEWARE OF GOING OUT ");
		msgsnd(msqid, &data, sizeof(data.b1), 0);
	}
	else if(strcmp(sm->e1.weather,"Cloudy")==0)
	{
		strcpy(data.b1[6],"WEATHER SENSED IS CLOUDY BETTER TAKE UMBRELLA BEFORE GOING OUT  ");
		msgsnd(msqid, &data, sizeof(data.b1), 0);
	}
	else
	{
		strcpy(data.b1[6],"THE SKY IS CLEAR ENJOY YOUR DAY ");
		msgsnd(msqid, &data, sizeof(data.b1), 0);
	}
	return NULL;
}
int main()
{
	struct scity *sm;
	int shmid;
	pthread_t t1,t2,t3;
	shmid = shmget((key_t)1234,1024,0666);
	printf("KEY OF THE SHARED MEMORY : : %d\n",shmid); 
	sm =(struct scity *)shmat(shmid, NULL, 0);
	int msgid=msgget((key_t)17834,0666 | IPC_CREAT);// creation of msgqueeu
	pthread_create (&t1,NULL,TrafficComparision,0);	// thread creation
	pthread_join(t1,NULL);	// waiting for thread t1 to complete 
	pthread_create (&t2,NULL,WasteComparision,0);// thread creation
	pthread_join(t2,NULL);// waiting for the thread t2 to complete
	pthread_create (&t3,NULL,EnvComparision,0);// thread creation
	pthread_join(t3,NULL);
	printf("DECISION BASED ON THE RECEIVED SENSOR IS COMPLETED \n");
	sleep(5);
	execl("./p5","p5",NULL,NULL);
}
