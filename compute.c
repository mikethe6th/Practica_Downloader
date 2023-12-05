#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "compute.h"

/* Number of hits */
unsigned int hits;

/* Mutex Semaphore */
pthread_mutex_t mutex;

/* Thread function */
void * thread_function(void * data) {

    /* The input variable contains the number of points that the thread must
     * calculate */
    int points = *((int *)data);    
    

    double x,y;
    struct drand48_data rand_buffer;
    srand48_r(time(NULL), &rand_buffer);

    /* The local variable that shall be used to store the number of points within
     * the circular section */
    unsigned int count = 0;

    /* TODO: Implement the loop that obtains the random points and counts how
     * many of those lay within the circumference of radius 1 */

    for (int i=0; i<points; i++){
        drand48_r(&rand_buffer, &x);
        drand48_r(&rand_buffer, &y);

        if((x*x + y*y) <= 1){
            count++;
        }
    }   

    /* TODO: Add the count to the global variable hits in mutual exclusion */
    pthread_mutex_lock(&mutex);
    hits = hits + count;
    printf("Hits: %d\n",hits);
    pthread_mutex_unlock(&mutex);
    return NULL;

}


void compute(int npoints, int nthreads) {

    /* TODO: Erase the following line: */
    /*printf("compute(%d, %d)\n", npoints, nthreads);*/
    pthread_t threads[nthreads];

    int nPass= npoints/nthreads;
    
    int np = npoints;
    
    pthread_mutex_init(&mutex, NULL);

    /* TODO: Launch the threads that will count the points */

    for(int i=0; i<nthreads; i++){

        printf("Total points: %d\n",np);
    /* TODO: Wait for all threads to finish */
    if(i == (nthreads-1)){
            printf("Creating thread: %d ... \n", i);    
            pthread_create(&(threads[i]), NULL, &thread_function ,  &np);
            pthread_join(threads[i], NULL);   
            
        }else{
            printf("Creating thread: %d ... \n", i);  
            pthread_create(&(threads[i]), NULL, &thread_function ,  &nPass);
            pthread_join(threads[i], NULL);   
                  
        }
        np = np -nPass;
    }
    
    /* TODO: print the ratio of points that meet the criteria */
    printf("Total hits: %d\n", hits);
    /* The following print string can be used to print the calculated value:
     * printf("%.8f\n", VALUE_OF_PI);
     * where VALUE_OF_PI is the floating-point value to be printed.
     */
    float VALUE_OF_PI=((float)hits/(float)npoints)  * 4;
    printf("PI's value: %.8f\n", VALUE_OF_PI);
}
