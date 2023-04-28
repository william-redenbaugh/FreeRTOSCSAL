#include "os_mutx.h"
#include "os_error.h"
#include "FreeRTOS.h"
#include "semphr.h"

int os_mut_init(os_mut_t *mut){
    if(mut == NULL)
        return OS_RET_INVALID_PARAM;

    mut->mut = xSemaphoreCreateBinary();

    if(mut->mut == NULL)
        return OS_RET_NO_MORE_RESOURCES;

    return OS_RET_OK;
}

int os_mut_entry(os_mut_t *mut, uint32_t timeout_ms){
    if(mut == NULL)
        return OS_RET_INVALID_PARAM;

    if(xSemaphoreTake(mut->mut, timeout_ms/portMAX_DELAY) == pdTRUE){
        return OS_RET_OK;
    }
    else{
        return OS_RET_TIMEOUT;
    }
}

int os_mut_count(os_mut_t *mut){
    if(mut == NULL)
        return OS_RET_INVALID_PARAM;

    return uxSemaphoreGetCount(mut->mut);
}

int os_mut_entry_wait_indefinite(os_mut_t *mut){
    if(mut == NULL)
        return OS_RET_INVALID_PARAM;

    if(xSemaphoreTake(mut->mut, portMAX_DELAY) == pdTRUE){
        return OS_RET_OK;
    }
    else{
        return OS_RET_MAX_RENTRANT;
    }
}

int os_mut_exit(os_mut_t *mut){
    if(mut == NULL){
        return OS_RET_INVALID_PARAM;
    }

    if(xSemaphoreGive(mut->mut) == pdTRUE){
        return OS_RET_OK;
    }
    else{
        return OS_RET_INT_ERR;
    }
}