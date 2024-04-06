Philosopher Simulation Project

## Overview

This project simulates the Dining Philosophers problem, demonstrating solutions to synchronization issues in concurrent programming. Philosophers perform actions like eating, thinking, and sleeping while sharing resources (forks).

## Simulation Flow:

Philosophers (threads) are created and each follows a routine where they think, try to pick up forks, eat, and then sleep.
Access to forks is synchronized using mutexes to prevent race conditions and ensure mutual exclusion.
The program monitors the state of each philosopher to determine if they have died or if the simulation can end based on the philosophers' meal counts.

This simulation offers a practical exploration of concurrency, thread synchronization, and the challenges of managing shared resources in a multi-threaded environment.
