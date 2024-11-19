#include "project_defs.h"

#ifdef PICO_MODULE
#include "FreeRTOS.h"
#include "semphr.h"
#else
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#endif

#include "global_includes.h"

int os_sem_init(os_sem_t *sem, int count)
{
    if (sem == NULL)
    {
        return OS_RET_NULL_PTR;
    }
    sem->sem = xSemaphoreCreateCounting(count, 0);
    return OS_RET_OK;
}

int os_sem_entry(os_sem_t *sem, uint32_t timeout_ms)
{
    if (sem == NULL)
    {
        return OS_RET_NULL_PTR;
    }

    if (xSemaphoreTake(sem->sem, timeout_ms / portTICK_PERIOD_MS) == pdTRUE)
    {
        return OS_RET_OK;
    }
    else
    {
        return OS_RET_MAX_RENTRANT;
    }
}

int os_sem_entry_wait_indefinite(os_sem_t *sem)
{
    if (sem == NULL)
    {
        return OS_RET_NULL_PTR;
    }

    if (xSemaphoreTake(sem->sem, portMAX_DELAY) == pdTRUE)
    {
        return OS_RET_OK;
    }
    else
    {
        return OS_RET_MAX_RENTRANT;
    }

    return OS_RET_OK;
}

int os_sem_entry_try(os_sem_t *sem)
{
    if (sem == NULL)
    {
        return OS_RET_NULL_PTR;
    }
    if (xSemaphoreTake(sem->sem, 0) == pdTRUE)
    {
        return OS_RET_OK;
    }
    else
    {
        return OS_RET_MAX_RENTRANT;
    }
}

int os_sem_count(os_sem_t *sem)
{
    if (sem == NULL)
    {
        return OS_RET_NULL_PTR;
    }
    return uxSemaphoreGetCount(sem->sem);
}

int os_sem_give(os_sem_t *sem)
{
    if (sem == NULL)
    {
        return OS_RET_NULL_PTR;
    }

    if (xSemaphoreGive(sem->sem) == pdTRUE)
    {
        return OS_RET_OK;
    }
    else
    {
        return OS_RET_MAX_RENTRANT;
    }
}