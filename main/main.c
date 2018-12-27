/*
memcrash by neonious GmbH

Written 2018-12-27,
tested with current ESP-IDF (commit 1023ff73fb2edea8e5abb413997e2a2ce4998771)

Demonstrates PSRAM on ESP32 still has issues which results into crashes.
Works directly with PSRAM, because of this malloc on PSRAM is not enabled.

The assignment in crash_set_both_broken does not work reliably, while
the assignment in crash_set_both_working does.

Runs on any ESP32-WROVER module

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

struct chunk
{
    struct chunk *entry;
};

void crash_set_both_broken(struct chunk *parent1, struct chunk *parent2, struct chunk *child)
{
    parent1->entry = parent2->entry = child;
}

void crash_set_both_working(struct chunk *parent1, struct chunk *parent2, struct chunk *child)
{
    parent1->entry = child;
    parent2->entry = child;
}

void app_main(void)
{
    int tries = 0, waitTicks = 10000;
    int startTicks = xTaskGetTickCount();

    while(1)
    {
        int ticks = xTaskGetTickCount();
        int tim = ticks - startTicks;
        if(tim >= waitTicks)
        {
            waitTicks += 10000;
            printf("At tick: %d  tries per ms: %.2lf\n", tim, tries / (double)tim);
        }

        // Find 3 random points in memory
        int pos1 = (rand() % (4 * 1024 * 1024 - sizeof(struct chunk))) & ~7;
        int pos2 = (rand() % (4 * 1024 * 1024 - sizeof(struct chunk))) & ~7;
        int pos3 = (rand() % (4 * 1024 * 1024 - sizeof(struct chunk))) & ~7;
        if(pos1 == pos2 || pos2 == pos3 || pos1 == pos3)
            continue;

        struct chunk *parent1 = (struct chunk *)(0x3F800000 + pos1);
        struct chunk *parent2 = (struct chunk *)(0x3F800000 + pos2);
        struct chunk *child = (struct chunk *)(0x3F800000 + pos3);

#if 1   // THIS DOES NOT WORK ALL THE TIME
        crash_set_both_broken(parent1, parent2, child);
#else   // THIS ALWAYS WORKS
        crash_set_both_working(parent1, parent2, child);
#endif

        if(parent1->entry != child || parent2->entry != child)
            printf("Try %d did not work, addresses in SPI RAM (base=0): parents: %08x %08x child: %08x!\n", tries, pos1, pos2, pos3);

        tries++;
    }
}