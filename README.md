C++ Memory Allocation List Simulator
====================================

Description
-----------

CLI memory allocaiton list simulator, written in C++ and implemented using a doubly linked list.


Implementation
--------------

A circular doubly linked list has been constructed to provide the base for the simulator.  The [worst fit algorithm](http://goo.gl/qwgLD) is used to allocate the memory blocks.

Released blocks are coalesced if possible.


Usage
-----

Allocate and release memory blocks and see the effect of doing so by printing the list map.


Contributors
------------

[David Sauntson](http://www.davidsauntson.com)