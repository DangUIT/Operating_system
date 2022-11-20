#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
void *thread1(void *arg)
{
	printf("Hello world\n");
	pthread_exit(NULL);
}
int main(){
	int ic;	
	size_t s1;
	pthread_attr_t attr;
	pthread_t tid;
/* 
-Cu phap khoi tao ham: 
     int pthread_attr_setstacksize(pthread_attr_t *attr, size_t stacksize);
 Trong do: + attr la bien tham chieu kieu pthread_attrt_t	
 	   + stacksize la kich thuoc muon tao kieu size_t
-Ham tra ve 0 neu thanh cong, nguoc lai tra ve -1
-Muc dich su dung: Tao kich thuoc cho doi tuong thuoc tinh luong 
*/
	ic = pthread_attr_init(&attr);
	if(ic==-1){
		printf("Error in pthread_attr_init");
		exit(1);
	}
	s1 = 1000;
	ic = pthread_attr_setstacksize(&attr, s1);
	if(ic==-1){
		printf("Error in pthread_attr_setstacksize");
		exit(2);
	}
	ic = pthread_create(&tid,&attr,thread1,NULL);
	if(ic==-1){
		printf("Error in pthread_create");
		exit(2);
	}
	pthread_join(tid, NULL);
	pthread_attr_destroy(&attr);
	exit(0);
	return 0;
}
