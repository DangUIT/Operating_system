#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
int main(){
	int ic;	
	size_t size;
	pthread_attr_t attr;
/* 
-Cu phap khoi tao ham: 
     int pthread_attr_getstacksize(pthread_attr_t *attr, size_t *stacksize);
 Trong do: + attr la bien tham chieu kieu pthread_attrt_t	
 	   + stacksize la bien tham chieu chua kich thuoc cua attr
-Ham tra ve 0 neu thanh cong, nguoc lai tra ve -1
-Muc dich su dung: Lay kich thuoc cua doi tuong thuoc tinh luong
*/
	ic = pthread_attr_init(&attr);
	if(ic==-1){
		printf("Error in pthread_attr_init");
		exit(1);
	}
	ic = pthread_attr_getstacksize(&attr, &size);
	if(ic==-1){
		printf("Error in pthread_attr_getstacksize");
		exit(2);
	}
	printf("The stack size is %d.\n",(int) size);
	pthread_attr_destroy(&attr);
	exit(0);
	return 0;
}
