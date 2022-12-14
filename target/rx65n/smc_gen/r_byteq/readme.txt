
r_byteq
=======

Overview
--------------------------------------------------------------------------------
The r_byteq module is a collection of circular buffer routines for byte data.
The application passes a buffer to be used as a circular buffer to the Open() 
function which assigns a queue control block to it to handle indexing. The 
Open() function returns a handle which is then used as a queue/buffer id for all 
other API functions. These functions include routines for adding and removing 
data from a queue, inspecting the amount of data in a queue, and the ability to 
flush a queue.

The queue control blocks can be allocated at compile time or dynamically at run
time. A configuration option for this exists in "r_config\r_byteq_config.h".


Features
--------
* Statically or dynamically allocated queue control blocks.
* Number of queues limited only by the amount of RAM available on the mcu.

File Structure
--------------
r_byteq
|   readme.txt
|   r_byteq_if.h
|
+---doc
|    +---en
|    |      r01an1683ej{VERSION_NUMBER}-rx-apl.pdf
|    |
|    +---ja
|           r01an1683jj{VERSION_NUMBER}-rx-apl.pdf
|
+---src
        r_byteq.c
        r_byteq_private.h
   
r_config
    r_byteq_config.h

