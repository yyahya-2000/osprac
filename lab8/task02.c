#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int a = 0;  // The variable a is global static for the entire program,
// so it will be shared by both threads of execution.

/**
  Below follows the text of the function
  that will be associated with the 2nd thread.

  Parameter dummy is used only for type compatibility.
  For the same reason, the function returns void *.
**/
void *mythread(void *dummy)
{
    pthread_t mythid;
    //
    // Note that mythid variable is a dynamic local variable of mythread () function,
    // that is, it is pushed on the stack and, therefore, is not shared by the threads.
    //
    mythid = pthread_self();

    a = a+1;
    printf("Thread %u, Calculation result = %d\n", mythid, a);
    return NULL;
}

/**
  The main() function is also an associated function of the main thread.
**/
int main()
{
    pthread_t thid_1,thid_2, mythid;
    int       res_1,res_2;
    //
    // Try to create a new thread of execution associated with the mythread () function.
    // Pass it NULL as a parameter. If it succeeds,
    // the identifier of the new thread is written into the thid_1 variable.
    // If an error occurs, stop working.
    //
    res_1 = pthread_create (&thid_1, (pthread_attr_t *)NULL, mythread, NULL);

    if (res_1 != 0) {
        printf ("Error on thread create, return value = %d\n", res_1);
        exit(-1);
    }

    printf("Thread created, thid_1 = %u\n", thid_1);

    /* creat the second thread*/
    res_2 = pthread_create (&thid_2, (pthread_attr_t *)NULL, mythread, NULL);

    if (res_2 != 0) {
        printf ("Error on thread create, return value = %d\n", res_1);
        exit(-1);
    }

    printf("Thread created, thid_2 = %u\n", thid_2);

    mythid = pthread_self();

    a = a+1;

    printf("Thread %u, Calculation result = %d\n", mythid, a);
    //
    // Wait for the spawned threads to terminate, not caring what value it return.
    // If these functions are not called, the main() function may end before
    // the spawned threads are executed, which will automatically cause it to terminate,
    // distorting the results.
    //
    pthread_join(thid_1, (void **)NULL);
    pthread_join(thid_2, (void **)NULL);

    return 0;
}
