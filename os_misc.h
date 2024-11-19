#ifndef _OS_MISC_H
#define _OS_MISC_H

#include "project_defs.h"

#ifdef PICO_MODULE

#include <cstdio>

#define println(...) printf(__VA_ARGS__); printf("\n")

// Macro: print(e)
// Description: Prints the given expression.
#define print(...) os_printf(__VA_ARGS__)

// Macro: os_printf(e)
// Description: Prints the formatted output using the os_printf function.
#define os_printf(...) printf(__VA_ARGS__)

#ifndef OS_ASSERT
#define OS_ASSERT(val) \
    if(val) {   \
    while(true){\
                \
    }           \
    }           \

#endif
#else 
#include "Arduino.h"
// Macro: println(e)
// Description: Prints the given expression followed by a newline character.
#define println(...) Serial.println(__VA_ARGS__)

// Macro: print(e)
// Description: Prints the given expression.
#define print(...) os_printf(__VA_ARGS__)

// Macro: os_printf(e)
// Description: Prints the formatted output using the os_printf function.
#define os_printf(...) printf(__VA_ARGS__)
#endif
#endif