#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<signal.h>
int loop_forever=1;

void *printThread(void * messenge){
	printf("Welcome to IT007, I am 21520684!\n");
	pthread_exit(NULL);
}
void *openThread(void * open){
	system("gedit abcd.txt");	
	pthread_exit(NULL);
}	
void on_sigint(){
	loop_forever=0;
	printf("\nYou are pressed CTRL+C! Goodbye!");
	printf("\n");
}
int main()
{	loop_forever=1;
	pthread_t idthread[1];
	pthread_create(&idthread[0],NULL,&printThread,NULL);
	pthread_create(&idthread[1],NULL,&openThread,NULL);
	pthread_join(idthread[0],NULL);
	pthread_join(idthread[1],NULL);
	signal(SIGINT,on_sigint);
	while(loop_forever){};
//	pthread_exit(NULL);
	exit(0);
	return 0;
}
