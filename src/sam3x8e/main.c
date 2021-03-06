// Main starting point for SAM3x8e boards.
//
// Copyright (C) 2016,2017  Kevin O'Connor <kevin@koconnor.net>
//
// This file may be distributed under the terms of the GNU GPLv3 license.

#include "board/misc.h" // alloc_maxsize
#include "command.h" // DECL_CONSTANT
#include "sam3x8e.h" // WDT
#include "sched.h" // sched_main

DECL_CONSTANT(MCU, "sam3x8e");


/****************************************************************
 * watchdog handler
 ****************************************************************/

void
watchdog_reset(void)
{
    WDT->WDT_CR = 0xA5000001;
}
DECL_TASK(watchdog_reset);

void
watchdog_init(void)
{
    uint32_t timeout = 32768 / 2;  // 500ms timeout
    WDT->WDT_MR = WDT_MR_WDRSTEN | WDT_MR_WDV(timeout) | WDT_MR_WDD(timeout);
}
DECL_INIT(watchdog_init);


/****************************************************************
 * misc functions
 ****************************************************************/

void
command_reset(uint32_t *args)
{
    NVIC_SystemReset();
}
DECL_COMMAND_FLAGS(command_reset, HF_IN_SHUTDOWN, "reset");

void * __visible
_sbrk(int nbytes)
{
    extern char _end;
    static void *heap_ptr = (void *)&_end;
    void *pos = heap_ptr;
    heap_ptr = pos + nbytes;
    return pos;
}

// Main entry point
int
main(void)
{
    SystemInit();
    sched_main();
    return 0;
}
