//
//  practice_threading.c
//  philo
//
//  Created by Yuliia Demura on 12/8/21.
//  Copyright © 2021 Yuliia Demura. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int mails = 0;
pthread_mutex_t mutex;

void *writing_messages(void *message)
{
    printf("%s\n", (char *)message);
    sleep(3);
    printf("after sleeping\n");
    return (0);
}

void    practice_messages(void)
{
    pthread_t t1;
    pthread_t t2;
    
    char *message1 = "Test from thread1: here is johnny";
    char *message2 = "Test from thread2: I know nothing";
    if (pthread_create(&t1, NULL, &writing_messages, (void *)message1) != 0)
        printf("err");
    if (pthread_create(&t2, NULL, &writing_messages, (void *)message2) != 0)
        printf("err");
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
}

void    *test_incremention_mutex() //cannot add void here as receive error mess:hn
///	Incompatible function pointer types passing 'void *(*)(void)' to parameter of type 'void * _Nullable (* _Nonnull)(void * _Nullable)'
{
    int i = 0;
    while (i < 1000000)
    {
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
        i++;
    }
    
    return 0;
}

void    practic_mutex(void)
{
    pthread_t t1;
    pthread_t t2;
    pthread_mutex_init(&mutex, NULL);
    
    if (pthread_create(&t1, NULL, &test_incremention_mutex, NULL) != 0)
        printf("err");
    if (pthread_create(&t2, NULL, &test_incremention_mutex, NULL) != 0)
        printf("err");
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    printf("%i\n", (int)mails);
    pthread_mutex_destroy(&mutex); ///when initialize mutex - needs to destroy at the end
}

void    create_loop_threads() //practice mutex but in a form of while loop
{
    pthread_t th[4];
    int i = 0;
    pthread_mutex_init(&mutex, NULL);
    while (i < 4)
    {
        if (pthread_create(&th[i], NULL, &test_incremention_mutex, NULL) != 0)
            printf("err");
        printf("%s %i \n", "create", i);
        i++;
    }
    i = 0;
    while (i < 4)
    {
        if (pthread_join(th[i], NULL) != 0)
            printf("err");
        printf("%s %i \n", "join", i);
        i++;
    }
    printf("%i: %s\n", (int)mails, "end");
    pthread_mutex_destroy(&mutex);
}

void    *roll_dice()
/// in order to return something in pthread_join
/// I cannot return a piece of mem on stack that is allocated and deallocated in this function.
/// I need to allocate mem with malloc and put res in this mem, this way I can return it into next function (join)
{
    int value = (rand() % 6) + 1;
    int *result = malloc(sizeof(int) * 1);
    result = &value;
    //printf("%i ", value); //how do we get this value to main?
    return (void *)result;
}

void    getting_res_from_join()
{
    pthread_t th;
    pthread_mutex_t m_th;
    srand((unsigned int)time((long *)NULL));

    pthread_mutex_init(&m_th, NULL);
    if (pthread_create(&th, NULL, &roll_dice, NULL) != 0)
        printf("err");
    int *res;
    if (pthread_join(th, (void **)&res) != 0) ///    NULL, 2 parameter is ** pointer-pointer, it will set a value
        printf("err");
    free(res);
    pthread_mutex_destroy(&m_th);
}

int primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

void *print_prime_per_thread(void *arg)
{
    int index = *(int *)arg;
    printf("%d ", primes[index]);
    free(arg);
    return 0;
}

void    passing_arg_to_thread(void)
{
    pthread_t th[10];
    for (int i = 0; i < 10; i++)
    {
        int *a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&th[i], NULL, &print_prime_per_thread, a) != 0)
            printf("error_create");
    }
    for (int i = 0; i < 10; i++)
    {
        if (pthread_join(th[i], NULL) != 0)
            printf("error_join");
    }
}


void    practice_thread(void)
{
//    practice_messages();
//    practic_mutex();
//    create_loop_threads();
//    getting_res_from_join();
//    passing_arg_to_thread();
    
    printf("end!\n");
    
}



//pthread_join(thread, NULL-or-something);
////sec arg can contain the result of the thread if needed
////join is like wait for fork and pids but for threads
////can return mistake, need protection
