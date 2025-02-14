#ifndef _OS_THREAD_H
#define _OS_THREAD_H

#include "project_defs.h"

#ifdef PLATFORM_ESP32
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#else
#include "FreeRTOS.h"
#include "task.h"
#endif


#include "csal_struct_definitions.h"
#include "stdint.h"
#include "stdbool.h"

/*!
 * @brief  Thread id value
 * @note
 */
typedef os_thread_id_s os_thread_id_t;

/*!
 * @brief Redeclaration of thread function
 * @note Holds pointer to begining of thread function subroutine. Holds register space for void pointer
 */
typedef void (*thread_func_t)(void *);

/*!
 * @brief Adds a thread to Will-OS Kernel
 * @note Paralelism at it's finest!
 * @param will_os_thread_func_t thread(pointer to thread function call begining of program counter)
 * @param void *arg(pointer arguement to parameters for thread)
 * @param void *stack(pointer to begining of thread stack)
 * @param int stack_size(size of the allocated threadstack)
 * @returns none
 */
os_thread_id_t os_add_thread(thread_func_t p, void *arg, int stack_size, void *stack);

/*!
 * @brief Sets the state of a thread to suspended.
 * @brief If thread doesn't exist, then
 * @param Which thread are we trying to get our state for
 * @returns will_thread_state_t
 */
os_thread_id_t os_suspend_thread(os_thread_id_t target_thread_id);

/*!
 * @brief Sets the state of a thread to resumed.
 * @brief If thread doesn't exist or hasn't been run before, then
 * @param Which thread are we trying to get our state for
 * @returns will_thread_state_t
 */
os_thread_id_t os_resume_thread(os_thread_id_t target_thread_id);

/*!
 * @brief Sets the state of a thread to dead
 * @brief If thread doesn't exist, then
 * @param Which thread are we trying to get our state for
 * @returns will_thread_state_t
 */
os_thread_id_t os_kill_thread(os_thread_id_t target_thread_id);

/*!
 * @returns The current thread's ID.
 */
os_thread_id_t os_current_id(void);

/**
 * @brief True if two task IDs are equal.
 * @note can't check directly because of platform dependant structures
*/
bool os_cmp_id(os_thread_id_t thread_one_id, os_thread_id_t thread_two_id);

/*!
 * @brief Kills and closes out current thread
 */
void os_kill_self_thread(void);

/*!
 * @brief Sleeps the thread through a hypervisor call.
 * @note Sleeps the thread for the alloted time, and wakes up once the thread is ready
 * @param int milliseconds since last system tick
 * @returns none
 */
#define os_thread_sleep_ms(millisecond) vTaskDelay(millisecond / portTICK_PERIOD_MS)

/*!
 * @brief Sleeps the thread through a hypervisor call.
 * @note Sleeps the thread for the alloted time, and wakes up once the thread is ready
 * @param int seconds since last system tick
 * @returns none
 */
#define os_thread_sleep_s(s) os_thread_sleep_ms(s * 1000)

/*!
 *   @brief allows our program to "yield" out of current subroutine
 *   @note Call's hypervisor command to look into something else.
 */
#define _os_yield() portYIELD()

#ifndef get_current_time_millis
#define get_current_time_millis() (xTaskGetTickCount() * (1/configTICK_RATE_HZ) * 1000)
#endif

#endif