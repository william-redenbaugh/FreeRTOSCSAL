#include "global_includes.h"

#define SETBITS_DEBUGGING
#ifdef SETBITS_DEBUGGING
#define setbits_println(e...) \
    print(e);                 \
    print("\n")
#else
#define setbits_println(e...) void(e)
#endif
int os_setbits_init(os_setbits_t *mod)
{
    if (mod == NULL)
    {
        return OS_RET_NULL_PTR;
    }

    mod->event_group = xEventGroupCreate();

    if (mod->event_group == NULL)
    {
        setbits_println("No more resources for setbits module");
        return OS_RET_NO_MORE_RESOURCES;
    }

    return OS_RET_OK;
}

int os_setbits_deconstruct(os_setbits_t *mod){
    vEventGroupDelete(mod->event_group);

    return OS_RET_OK;
}

int os_setbits_signal(os_setbits_t *mod, int bit)
{
    if (mod == NULL)
    {
        return OS_RET_NULL_PTR;
    }
    int n = bit;
    xEventGroupSetBits(mod->event_group, n);

    return OS_RET_OK;
}

int os_clearbits(os_setbits_t *mod, int bit)
{
    if (mod == NULL)
    {
        setbits_println("Null pointer to setbits module");
        return OS_RET_NULL_PTR;
    }
    int n = bit;
    xEventGroupClearBits(mod->event_group, n);

    return OS_RET_OK;
}

int os_waitbits(os_setbits_t *mod, int bit, uint32_t timeout_ms)
{
    if (mod == NULL)
    {
        return OS_RET_NULL_PTR;
    }

    int n = bit;
    xEventGroupWaitBits(mod->event_group, n, pdFAIL, pdTRUE, timeout_ms / portTICK_PERIOD_MS);
    return OS_RET_OK;
}

int os_waitbits_indefinite(os_setbits_t *mod, int bit)
{
    if (mod == NULL)
    {
        return OS_RET_NULL_PTR;
    }
    int n = bit;
    xEventGroupWaitBits(mod->event_group, n, pdFALSE, pdFALSE, portMAX_DELAY);
    return OS_RET_OK;
}