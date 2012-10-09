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
//#define Nthreads 5
int *messages;
//char mesg[50][10];

void main()

{


	int Nthreads=5;
	messages = (int*) calloc(Nthreads, sizeof(int)) ;

     pthread_t *threadk = (pthread_t*) calloc(Nthreads, sizeof(pthread_t)) ;
     char *message1 = "Thread 1";

     char *message2 = "Thread 2";

     //int Nthreads = 50 ;
    int i=0;

     // for( int i=0; i<Nthreads;i++)
/*    while(i<Nthreads)
     {
    	 messages[i] =i ;
    	 i++ ;
     }
*/
    // int  iret1, iret2;
  //   int *iret  = (int*)  calloc(Nthreads, sizeof(int)) ;
    int iret[5] ;

     /*srand ( time(NULL) );

        generate secret number:
       iSecret = rand() % 10 + 1;
       */


     pthread_mutex_init(&pmutex, NULL) ;

   //   pmutex.__data = "text1" ;

    /* Create independent threads each of which will execute function */

     for ( i=0;i<Nthreads; i++)
     {
    	// message1= (char*) (&i) ;

    	//strcpy( message1,(char*) i);   //= itoa(i) ;
    	//  printf("%c", message1) ;
    	 iret[i] = pthread_create( threadk[i], NULL, print_message_function, (void*) message1);

     }
     /*
     iret1 = pthread_create( &thread1, NULL, print_message_function, (void*) message1);
     iret2 = pthread_create( &thread2, NULL, print_message_function, (void*) message2);
		*/

     /* Wait till threads are complete before main continues. Unless we  */

     /* wait we run the risk of executing an exit which will terminate   */

     /* the process and all threads before the threads have completed.   */

     //pthread_join( thread1, NULL);

     //pthread_join( thread2, NULL);

     for(i=0;i<Nthreads;i++)
     {
    	 pthread_join(threadk[i],NULL) ;
     }


     // printf("Thread 1 returns: %d\n",iret1);

     // printf("Thread 2 returns: %d\n",iret2);

     exit(0);




}



void *print_message_function( void *ptr )

{
	 printf("entering print message") ;
     int *message;

     message = (int *) ptr;

     int sleepcount =0 ;

     while(sleepcount<10){

     if (pthread_mutex_trylock(&pmutex))
     {
    	 pthread_mutex_lock(&pmutex) ;
    	// printf("%d", pmutex.__data) ;
    	// pmutex.__data =  atoi(message) ;
    	 printf('%d', message) ;
    	 sleep(0.005);
    	 pthread_mutex_unlock(&pmutex) ;
     }
     else
     {
    	 sleep(0.005) ;
    	 sleepcount++ ;
     }
     }

    // printf("%s \n", message);

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

