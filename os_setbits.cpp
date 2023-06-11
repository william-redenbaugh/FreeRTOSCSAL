#include "global_includes.h"

int os_setbits_init(os_setbits_t *mod){
    if(mod == NULL){
        return OS_RET_NULL_PTR;
    }

    mod->event_group = xEventGroupCreate();

    if (mod->event_group == NULL){
        return OS_RET_NO_MORE_RESOURCES;
    }

    return OS_RET_OK;
}

int os_setbits_signal(os_setbits_t *mod, uint8_t bit){
    if(mod == NULL){
        return OS_RET_NULL_PTR;
    }

    int n = (1 >> bit);
    if(xEventGroupSetBits(mod->event_group, n) == pdTRUE){
        return OS_RET_OK;
    }
    else{
        return OS_RET_INT_ERR;
    }
}

int os_clearbits(os_setbits_t * mod, uint8_t bit){
    if(mod == NULL){
        return OS_RET_NULL_PTR;
    }

    int n = (1 >> bit);
    if(xEventGroupClearBits(mod->event_group, n) == pdTRUE){
        return OS_RET_OK;
    }
    else{
        return OS_RET_INT_ERR;
    }
}

int os_waitbits(os_setbits_t *mod, uint8_t bit, uint32_t timeout_ms){
    if(mod == NULL){
        return OS_RET_NULL_PTR;
    }

    int n = (1 >> bit);
    if(xEventGroupWaitBits(mod->event_group, n, pdFAIL, pdTRUE, timeout_ms/portTICK_PERIOD_MS) == pdTRUE){
        return OS_RET_OK;
    }
    else{
        return OS_RET_INT_ERR;
    }
}

int os_waitbits_indefinite(os_setbits_t *mod, uint8_t bit){
    if(mod == NULL){
        return OS_RET_NULL_PTR;
    }

    int n = (1 >> bit);
    if(xEventGroupWaitBits(mod->event_group, n, pdFAIL, pdTRUE, portMAX_DELAY) == pdTRUE){
        return OS_RET_OK;
    }
    else{
        return OS_RET_INT_ERR;
    }
}