memcrash by neonious GmbH

Demonstrates PSRAM on ESP32 still has issues which results into crashes.
Works with any ESP32-WROVER based board, even one's with the current revision 1.

Note: low.js/neonious one is stable due to workaround.

There only seems to be two workarounds:

- Switch to unicore mode. The problem exists because each half of the 4 MB of PSRAM
  is handled by one core in dualcore mode and the problem only happens if the current
  thread is running on the other code.
  (This is the workaround we are using on low.js. JavaScript is non-multithreaded anyways,
  so not a big penalty for us)

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

