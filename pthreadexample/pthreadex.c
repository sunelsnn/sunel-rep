/*
 * pthreadex.c
 *
 *  Created on: Sep 7, 2012
 *      Author: root
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>
// #include <iostream.h>
// #include <conio.h>
void *print_message_function( void *ptr );

pthread_mutex_t pmutex ;
int Nthreads = 50 ;
int messages[Nthreads] ;
char mesg[][];

void main()

{

     pthread_t thread[10] ;
     char *message1 = "Thread 1";

     char *message2 = "Thread 2";



     //int Nthreads = 50 ;

     for (int i=0; i< Nthreads ;i++)
     {
    	 messages[i] =i ;
     }

    // int  iret1, iret2;
     int iret[Nthreads] ;

     /*srand ( time(NULL) );

        generate secret number:
       iSecret = rand() % 10 + 1;
       */


     pthread_mutex_init(&pmutex, NULL) ;

   //   pmutex.__data = "text1" ;

    /* Create independent threads each of which will execute function */

     for (int i=0 ;i<Nthreads ; i++)
     {
    	 strcpy(message1, itoa(i)) ;
iret[i] = pthread_create( &thread1[i], NULL, print_message_function, (void*) message1);
     }
     /*
     iret1 = pthread_create( &thread1, NULL, print_message_function, (void*) message1);
     iret2 = pthread_create( &thread2, NULL, print_message_function, (void*) message2);
		*/

     /* Wait till threads are complete before main continues. Unless we  */

     /* wait we run the risk of executing an exit which will terminate   */

     /* the process and all threads before the threads have completed.   */

     pthread_join( thread1, NULL);

     pthread_join( thread2, NULL);


     printf("Thread 1 returns: %d\n",iret1);

     printf("Thread 2 returns: %d\n",iret2);

     exit(0);

}



void *print_message_function( void *ptr )

{

     char *message;

     message = (char *) ptr;

     int sleepcount =0 ;

     while(sleepcount<10){

     if (pthread_mutex_trylock(&pmutex))
     {
    	 pthread_mutex_lock(&pmutex) ;
    	 printf("%d", pmutex.__data) ;
    	 pmutex.__data =  atoi(message) ;
    	 pthread_mutex_unlock(&pmutex) ;
     }
     else
     {
    	 sleep(1) ;
    	 sleepcount++ ;
     }
     }

     printf("%s \n", message);

}

/*
 * #define _GNU_SOURCE
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
int
main(int argc, char *argv[])
{
    cpu_set_t *cpusetp;
    size_t size;
    int num_cpus, cpu;
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <num-cpus>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    num_cpus = atoi(argv[1]);
    cpusetp = CPU_ALLOC(num_cpus);
    if (cpusetp == NULL) {
        perror("CPU_ALLOC");
        exit(EXIT_FAILURE);
    }
    size = CPU_ALLOC_SIZE(num_cpus);
    CPU_ZERO_S(size, cpusetp);
    for (cpu = 0; cpu < num_cpus; cpu += 2)
        CPU_SET_S(cpu, size, cpusetp);
    printf("CPU_COUNT() of set:    %d\n", CPU_COUNT_S(size, cpusetp));
    CPU_FREE(cpusetp);
    exit(EXIT_SUCCESS);
}
*/
 */
