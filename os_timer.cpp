#include "global_includes.h"

int os_timer_init(os_timer_t *timer, os_timer_cb_t cb, int interval_ms)
{
    if (timer == NULL)
    {
        return OS_RET_INVALID_PARAM;
    }

    timer->timer = xTimerCreate("",
                                interval_ms / portTICK_PERIOD_MS,
                                pdTRUE,
                                0,
                                (TimerCallbackFunction_t)cb);

    timer->cb = cb;
    timer->interval_ms = interval_ms;
    timer->one_shot = false;

    return OS_RET_OK;
}

int os_timer_start_oneshot(os_timer_t *timer)
{
    if (timer == NULL)
    {
        return OS_RET_NULL_PTR;
    }
    if (timer->timer == NULL)
    {
        return OS_RET_NOT_INITIALIZED;
    }

    if (timer->timer == NULL)
    {
        return OS_RET_NOT_INITIALIZED;
    }
    xTimerStart(timer->timer, timer->interval_ms / portTICK_PERIOD_MS);
    return OS_RET_OK;
}

int os_timer_start_recurring(os_timer_t *timer)
{
    if (timer == NULL)
    {
        return OS_RET_NULL_PTR;
    }
    if (timer->timer == NULL)
    {
        return OS_RET_NOT_INITIALIZED;
    }

    xTimerStart(timer->timer, timer->interval_ms / portTICK_PERIOD_MS);

    return OS_RET_OK;
}

int os_timer_interval_change(os_timer_t *timer, int interval_ms)
{
    if (timer == NULL)
    {
        return OS_RET_NULL_PTR;
    }
    if (timer->timer == NULL)
    {
        return OS_RET_NOT_INITIALIZED;
    }
    timer->interval_ms = interval_ms;
    xTimerChangePeriod(timer->timer, interval_ms / portTICK_PERIOD_MS, interval_ms / portTICK_PERIOD_MS);
    return OS_RET_OK;
}

int os_timer_stop(os_timer_t *timer)
{
    if (timer == NULL)
    {
        return OS_RET_NULL_PTR;
    }
    if (timer->timer == NULL)
    {
        return OS_RET_NOT_INITIALIZED;
    }

    xTimerStop(timer->timer, 0);
    return OS_RET_OK;
}

int os_timer_deinit(os_timer_t *timer)
{
    if (timer == NULL)
    {
        return OS_RET_NULL_PTR;
    }
    if (timer->timer == NULL)
    {
        return OS_RET_NOT_INITIALIZED;
    }

    xTimerDelete(timer->timer, 0);
    timer->timer = NULL;
    return OS_RET_OK;
}