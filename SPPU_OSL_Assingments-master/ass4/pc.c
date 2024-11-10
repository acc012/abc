#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

sem_t e,f,s;
int data[5] ,in = 0,out = 0;

void *producer(void *arg){
    sem_wait(&e);
    sem_wait(&s);
    data[in] = rand();
    printf("Producer generated  %d\n",data[in]);
    in = (in + 1) % 5;
    sem_post(&s);
    sem_post(&f);
    sleep(1);


}

void *consumer(void *args){
   int value;

   do{
    sem_wait(&f);
    sem_wait(&s);

    value = data[out];

    printf("Consumer read : %d\n",value);

    out = (out + 1)%5;

    sem_post(&s);
    sem_post(&e);
    sleep(1);
   }while(value != 5);
}

void main(){
    pthread_t p[8],c;
    int i,j;
    sem_init(&f,0,0);
    sem_init(&e,0,5);
    sem_init(&s,0,1);

    pthread_create(&c,NULL,consumer,NULL);

    for(i = 0;i<8;i++){
        pthread_create(&p[i],NULL,producer,NULL);
    }
    pthread_join(c,NULL);

    for(i = 0;i<8;i++){
        pthread_join(p[i],NULL);
    }
    sem_destroy(&e);
    sem_destroy(&f);
    sem_destroy(&s);
    

    sleep(2);
}