#include "threads_init.h"
#include "os_thread.h"

void threads_list_init(void)
{
    for (int n = 0; n < NUM_THREADS; n++)
    {
        if(THREAD_LIST[n].task_init_fun!= NULL)
            THREAD_LIST[n].task_init_fun(NULL);
    }

    // Launch each task!
    for (int n = 0; n < NUM_THREADS; n++)
    {
        if(THREAD_LIST[n].task_fun != NULL){
            os_add_thread((thread_func_t)THREAD_LIST[n].task_fun, THREAD_LIST[n].param, THREAD_LIST[n].stack_size, THREAD_LIST[n].stack);
        }
    }
}