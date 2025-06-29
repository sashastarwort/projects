#include <pthread.h>
#include <stdio.h>
#include <math.h>

float f1r;
float f2r;
float f3r;
pthread_barrier_t br1;

struct values
{
    float a;
    float b;
    short n;
    float h;
};

void* fn1(void* arg)
{
    float x;
    struct values thread_arg = *((struct values*)arg);
    for (short i = 0; i <= thread_arg.n; i++)
    {
        x = thread_arg.a + thread_arg.h * i;
        f1r = sin(x) * sin(x) * cos(x);
        pthread_barrier_wait(&br1);
        pthread_barrier_wait(&br1);
    }
    return NULL;
}

void* fn2(void* arg)
{
    float x;
    struct values thread_arg = *((struct values*)arg);
    for (short i = 0; i <= thread_arg.n; i++)
    {
        x = thread_arg.a + thread_arg.h * i;
        f2r = cos(x) * cos(x) * (1 + sin(x));
        pthread_barrier_wait(&br1);
        pthread_barrier_wait(&br1);
    }
    return NULL;
}

void* fn3(void* arg)
{
    float x;
    struct values thread_arg = *((struct values*)arg);
    for (short i = 0; i <= thread_arg.n; i++)
    {
        x = thread_arg.a + thread_arg.h * i;
        f3r = cos(x) * (1 + sin(x) * sin(x));
        pthread_barrier_wait(&br1);
        pthread_barrier_wait(&br1);
    }
    return NULL;
}

int main()
{
    float a = -2 * M_PI;
    float b = 0;
    short n = 10;
    float h = (2 * M_PI) / 10;

    pthread_t f1, f2, f3;

    struct values data;
    data.a = a;
    data.b = b;
    data.n = n;
    data.h = h;

    printf("\tx\t|  sin^2+cos  | cos^2*(1+sin) | cos*(1+sin^2) |\n");
    printf("----------------|-------------|---------------|---------------|\n");

    pthread_barrier_init(&br1, NULL, 4);

    pthread_create(&f1, NULL, fn1, &data);
    pthread_create(&f2, NULL, fn2, &data);
    pthread_create(&f3, NULL, fn3, &data);

    for(int i = 0; i <= n; i++)
    {
        float x = a + i * h;
        printf(" %8.5f\t|", x);
        pthread_barrier_wait(&br1);
        printf(" %8.5f    |", f1r);
        printf(" %8.5f      |", f2r);
        printf(" %8.5f      |\n", f3r);
        pthread_barrier_wait(&br1);
    }
    printf("----------------|-------------|---------------|---------------|\n");

    pthread_join(f1, NULL);
    pthread_join(f2, NULL);
    pthread_join(f3, NULL);

    pthread_barrier_destroy(&br1);
    return 0;
}


