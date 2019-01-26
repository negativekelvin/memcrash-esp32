/*
memcrash by neonious GmbH

Demonstrates PSRAM on ESP32 still has issues which results into crashes.
Works directly with PSRAM, because of this malloc on PSRAM is not enabled.

There only seems to be two workarounds:

- Use only the first 2 MB of 4 MB of PSRAM (big penalty)

- End every function which stores to PSRAM with a memw instruction
  (slow). nops do not help.

How to compile and try out yourself (runs on any ESP32-WROVER module):

- clone git
- cd memcrash-esp32
- git submodule update --init --recursive
- make menuconfig  <-- change path to flasher here
- make flash monitor

Written 2018-12-27,
tested with current ESP-IDF (commit 1023ff73fb2edea8e5abb413997e2a2ce4998771)
Updated on 2019-01-26

********************************************************************************

Our advertisment block:

- please take a look at www.lowjs.org for Node.JS on ESP32:
  scalable, feature rich programming of microcontrollers done easily

- please take a look at www.neonious.com for a great microcontroller board
  with Ethernet and Wifi
  wifi an integrated IDE + debugger on board
  and more!

- please take a look at our blog www.neonious-basics.com for interesting news
  and blog posts which educate you about electronics

********************************************************************************
*/

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include <stdio.h>

void crash_set_both(int *mem1, int *mem2, int val)
{
    *mem1 = val;
    *mem2 = val;

#if 0
    // This works, but is slow!
    asm("memw");
#endif
}

void app_main(void)
{
    int tries = 0, waitTicks = 1000;
    int startTicks = xTaskGetTickCount();

    while(1)
    {
        int ticks = xTaskGetTickCount();
        int tim = ticks - startTicks;
        if(tim >= waitTicks)
        {
            waitTicks += 1000;
            printf("At tick: %d  tries per ms: %.2lf\n", tim, tries / (double)tim);
        }

        // pos1 must be in upper 2 MB of RAM
        int pos1 = 2 * 1024 * 1024 + ((rand() % (2 * 1024 * 1024 - sizeof(void *))) & ~3);
        // pos1 must be in lower 2 MB of RAM
        int pos2 = (rand() % (2 * 1024 * 1024 - sizeof(void *))) & ~3;

        int *mem1 = (int *)(0x3F800000 + pos1);
        int *mem2 = (int *)(0x3F800000 + pos2);
        int val = rand();

        if(pos1 == pos2)
            continue;

        // write
        crash_set_both(mem1, mem2, val);
        // read
        if(*mem2 != val)
            printf("Try %d did not work, addresses in SPI RAM (base=0): %08x %08x!\n", tries, pos1, pos2);

        tries++;
    }
}
