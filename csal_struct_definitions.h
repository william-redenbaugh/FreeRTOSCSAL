#ifndef _CSAL_STRUCT_DEFINITIONS_H
#define _CSAL_STRUCT_DEFINITIONS_H

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"

typedef struct os_mut_t
{
    SemaphoreHandle_t mut;
} os_mut_t;

typedef struct os_sem_t
{
    SemaphoreHandle_t sem;
} os_sem_t;

typedef struct os_setbits_t
{
    EventGroupHandle_t event_group;
} os_setbits_t;

typedef struct os_thread_id_s
{
    TaskHandle_t handle;
    StaticTask_t buffer;
} os_thread_id_s;
#endif