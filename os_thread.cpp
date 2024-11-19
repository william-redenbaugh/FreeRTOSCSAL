#include "os_thread.h"

#include "project_defs.h"

#ifdef PICO_MODULE
#include "FreeRTOS.h"
#include "task.h"
#else
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#endif


os_thread_id_t os_add_thread(thread_func_t p, void *arg, int stack_size, void *stack)
{
    os_thread_id_t id;

    if (stack == NULL)
    {
        xTaskCreate(p,
                    "",
                    stack_size,
                    arg,
                    32,
                    &id.handle);
    }

    return id;
}

os_thread_id_t os_suspend_thread(os_thread_id_t target_thread_id)
{
    vTaskSuspend(target_thread_id.handle);

    return target_thread_id;
}

os_thread_id_t os_resume_thread(os_thread_id_t target_thread_id)
{
    vTaskResume(target_thread_id.handle);

    return target_thread_id;
}

os_thread_id_t os_kill_thread(os_thread_id_t target_thread_id)
{
    vTaskDelete(target_thread_id.handle);

    return target_thread_id;
}

bool os_cmp_id(os_thread_id_t thread_one_id, os_thread_id_t thread_two_id){
    return thread_one_id.handle == thread_two_id.handle;
}

os_thread_id_t os_current_id(void)
{
    os_thread_id_t id;
    id.handle = xTaskGetCurrentTaskHandle();

    return id;
}

void os_kill_self_thread(void)
{
    vTaskDelete(NULL);
}