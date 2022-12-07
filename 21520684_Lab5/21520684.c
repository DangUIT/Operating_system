#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

int x1 = 1, x2 = 2, x3 = 3, x4 = 4, x5 = 5, x6 = 6;
int w, v, y, z, ans;
sem_t sem[8];
void *thread_a(void *);
void *thread_b(void *);
void *thread_c(void *);
void *thread_d(void *);
void *thread_e(void *);
void *thread_f(void *);
void *thread_g(void *);

int main()
{
	pthread_t id[7];
	for (int i = 0; i < 8; i++)
	{
		sem_init(&sem[i], 0, 0);
	}
	pthread_create(&id[0], NULL, &thread_a, NULL);
	pthread_create(&id[1], NULL, &thread_b, NULL);
	pthread_create(&id[2], NULL, &thread_c, NULL);
	pthread_create(&id[3], NULL, &thread_d, NULL);
	pthread_create(&id[4], NULL, &thread_e, NULL);
	pthread_create(&id[5], NULL, &thread_f, NULL);
	pthread_create(&id[6], NULL, &thread_g, NULL);
	pthread_exit(NULL);
	for (int i = 0; i < 8; i++)
	{
		sem_destroy(&sem[i]);
	}
	return 0;
}

void *thread_a(void *arg)
{
	w = x1 * x2;
	printf("(a) w = %d\n", w);
	sem_post(&sem[0]);
	sem_post(&sem[1]);
	pthread_exit(NULL);
}
void *thread_b(void *arg)
{
	v = x3 * x4;
	printf("(b) v = %d\n", v);
	sem_post(&sem[2]);
	sem_post(&sem[3]);
	pthread_exit(NULL);
}
void *thread_c(void *arg)
{
	sem_wait(&sem[2]);
	y = v * x5;
	printf("(c) y = %d\n", y);
	sem_post(&sem[4]);
	pthread_exit(NULL);
}
void *thread_d(void *arg)
{
	sem_wait(&sem[3]);
	z = v * x6;
	printf("(d) z = %d\n", z);
	sem_post(&sem[5]);
	pthread_exit(NULL);
}
void *thread_e(void *arg)
{
	sem_wait(&sem[0]);
	sem_wait(&sem[4]);
	y = w * y;
	printf("(e) y = %d\n", y);
	sem_post(&sem[6]);
	pthread_exit(NULL);
}

void *thread_f(void *arg)
{
	sem_wait(&sem[1]);
	sem_wait(&sem[5]);
	z = w * z;
	printf("(f) z = %d\n", z);
	sem_post(&sem[7]);
	pthread_exit(NULL);
}

void *thread_g(void *arg)
{
	sem_wait(&sem[6]);
	sem_wait(&sem[7]);
	ans = y + z;
	printf("(g) ans = %d\n", ans);
	pthread_exit(NULL);
}
