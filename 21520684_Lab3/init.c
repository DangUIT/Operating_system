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
	pthread_attr_t attr;
	pthread_t tid;
/* 
-Cu phap khoi tao ham: 
	int pthread_attr_init(pthread_attr_t *attr);
 Trong do: attr la bien tham chieu kieu pthread_attrt_t	
-Ham tra ve 0 neu thanh cong, nguoc lai tra ve -1
-Muc dich su dung: Tao mot doi tuong thuoc tinh luong, co the truyen vao pthread_create
*/
	ic = pthread_attr_init(&attr);
	if(ic==-1){
		printf("Error in pthread_attr_init");
		exit(1);
	}
	ic = pthread_create(&tid,&attr,thread1,NULL);
	if(ic==-1){
		printf("Error in pthread_create");
		exit(2);
	}
	pthread_join(tid, NULL);
	exit(0);
	return 0;
}
