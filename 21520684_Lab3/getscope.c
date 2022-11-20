#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
int main(){
	int ic;	
	int s;
	pthread_attr_t attr;
/* 
-Cu phap khoi tao ham: 
     int pthread_attr_getscope(pthread_attr_t *attr, int *scope);
 Trong do: + attr la bien tham chieu kieu pthread_attrt_t	
 	   + scope la bien tham chieu kieu int
-Ham tra ve 0 neu thanh cong, nguoc lai tra ve -1
-Muc dich su dung: Truy xuat pham vi cua luong attr
*/
	ic = pthread_attr_init(&attr);
	if(ic==-1){
		printf("Error in pthread_attr_init");
		exit(1);
	}
	ic = pthread_attr_getscope(&attr, &s);
	if(ic==-1){
		printf("Error in pthread_attr_getstacksize");
		exit(2);
	}
	printf("The scope is %d.\n",(int) s);
	pthread_attr_destroy(&attr);
	exit(0);
	return 0;
}
