# Watchdog
The Watchdog is a a multi-threaded C program designed and purposed towards protecteing your application in critical sections of code from freezing, crashing 
and generally not responding for a set amount of time, by restarting your application with the same environment variables it started out with.

#### intended for Linux distros only

This program utilizes a [custom module for internal use scheduling ](./lib/scheduler/).

You are provided with a [makefile](./Makefile) for you to compile the Watchdog application (watchdog_proc.out) with,
along with a shared library (both ``DEBUG`` and ``RELEASE`` options) and an [API header](./include/watchdog.h) for you to include in your code.

# Compilation and Usage
* Compile the libraries and application using either ``make release`` ' or ``make debug``.

* the [API header](./include/watchdog.h) contains two operations:
```c
/*******************************************************************************
StartWD
Description: Start a new WatchDog Process, linked to a running process.
Parameters:
	- argc and argv[] parameters of the linked running process.
Return value:
	- the PID of the new WatchDog process.
********************************************************************************/
int StartWD(char *argv[]);


/******************************************************************************
StopWD
Description: Terminates a specified WatchDog Process.
Parameters:
	- the PID of the new WatchDog process.
Return value:
	- None.
********************************************************************************/
void StopWD(void);
```
### `StartWD` and `StopWD` functions that you can call on both ends of your code that you wish to encase in Watchdog activity.
