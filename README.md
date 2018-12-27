memcrash by neonious GmbH

Written 2018-12-27,
tested with current ESP-IDF (commit 1023ff73fb2edea8e5abb413997e2a2ce4998771),
compiled under Mac OS X.

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
