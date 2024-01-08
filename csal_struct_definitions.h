#ifndef _CSAL_STRUCT_DEFINITIONS_H
#define _CSAL_STRUCT_DEFINITIONS_H

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"
#include "freertos/timers.h"

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

#define DEFAULT_THREAD_HANDLE {.handle=NULL, .buffer = StaticTask_t()}

typedef TimerHandle_t timer_cb_param_t;

/**
 * @typedef os_timer_cb_t
 *
 * @brief Callback function type for OS timer.
 *
 * This function type is used as a callback for OS timer events.
 *
 * @param data A pointer to user data passed to the timer callback function.
 */
typedef void (*os_timer_cb_t)(timer_cb_param_t *data);

typedef struct os_timer
{
    TimerHandle_t timer;
    int interval_ms;
    bool one_shot;
    os_timer_cb_t cb;
} os_timer_t;

#endif