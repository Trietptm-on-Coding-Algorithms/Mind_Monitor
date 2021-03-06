#include <sys/types.h>      // pid_t
#include <pthread.h>        // pthread_create()
#include <stdio.h>          // fprintf()
#include <stdlib.h>         // exit(), free()
#include <string.h>         // strcpy()
#include "gimme_mem.h"      // gimme_mem_malloc()
#include "mimo_wrappers.h"  // setup_mimo(), teardown_mimo()

#define BUF_SIZE 64
#define START_STRING "ORIGINAL THREAD"
#define NEW_STRING "NEW THREAD"


void double_free(char *buf)
{
    // PRINT
    printf("%s", buf);
    free(buf);
}


/*
 *  Purpose - Encapsulate all the work the new thread will do
 */
void *execute_thread(void);


int main(void)
{
    /***********************************************************/
    /* 13. Multi-Thread Double Free                            */
    /***********************************************************/
    // SETUP
    setup_mimo();

    // LOCAL VARIABLES
    pthread_t thread_id = 0;

    // SPAWN THREAD
    printf("%s: Creating new thread\n", START_STRING); 
    if(!pthread_create(&thread_id, NULL, (void *)execute_thread, NULL))
    {
        printf("%s: New thread successfully created\n", START_STRING);
    }
    else
    {
        fprintf(stderr, "%s: Failed to create new thread\n", START_STRING);
    }

    // JOIN THREAD
    if(!pthread_join(thread_id, NULL))
    {
        printf("%s: Successfully joined with the new thread\n", START_STRING);
    }
    else
    {
        fprintf(stderr, "%s: Failed to join with the new thread\n", START_STRING);
    }

    // DONE
    teardown_mimo();
    exit(EXIT_SUCCESS);
}


void *execute_thread(void)
{
    // SETUP
    setup_mimo();

    // LOCAL VARIABLES
    char *bufDbleFree = (char *)gimme_mem_malloc((BUF_SIZE * sizeof(char)) + 1);

    // COPY
    strcpy(bufDbleFree, NEW_STRING": Hello World!\n");

    // PRINT
    double_free(bufDbleFree);

    // CLEAN UP
    // free(bufDbleFree);

    // DONE
    teardown_mimo();
    return NULL;
}
