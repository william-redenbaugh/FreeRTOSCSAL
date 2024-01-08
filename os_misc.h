#ifndef _OS_MISC_H
#define _OS_MISC_H
#include "Arduino.h"

// Macro: println(e)
// Description: Prints the given expression followed by a newline character.
#define println(...) Serial.println(__VA_ARGS__)

// Macro: print(e)
// Description: Prints the given expression.
#define print(...) Serial.printf(__VA_ARGS__)

// Macro: os_printf(e)
// Description: Prints the formatted output using the Serial.printf function.
#define os_printf(...) printf(__VA_ARGS__)

#endif