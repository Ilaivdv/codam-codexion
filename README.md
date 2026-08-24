_This project has been created as part of the 42 curriculum by ivan-der_

# Codexion
A program about handling [Dijkstra's philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) with multithreading using [POSIX threads](https://en.wikipedia.org/wiki/Pthreads).
### -- The Problem --
One or more coders are working next to each other in a circle. In the center, there is a shared compiler.<br>
- There are **USB dongles** in between each coders left and right side. There are as many dongles as there are coders.
- The coders alternatively **compile**, **debug** and **refactor**.
- They are only allowed to execute one action at a time.
- Compilation requires a coder to be holding **2** dongles simultaneously.
- When a coder finishes compiling, they put both dongles back.
- Each time the dongles are freed, they go on cooldown before they can be used again.
- Coders are not allowed to communicate to one another.
- Every coder needs to compile regularly, otherwise they will burn out and the program ends.

# Instructions
Compile the program using:<br>
```bash
make
# or
make all

# to recompile all files
make re
```
This will create a file `codexion` as a runnable program.<br>
Required parameters are as follows:<br>

| Parameter                  | Description
|-|-
| number_of_coders           | The number of coders and dongles (max 512)
| time_to_burnout            | Time coder has to compile again after the last compilation
| time_to_compile            | Time a coder will be compiling for
| time_to_debug              | Time a coder will be debugging for
| time_to_refactor           | Time a coder will be refactoring for
| number_of_compiles_required| Each coder has to reach this amount of compiles for program to end
| dongle_cooldown            | Time a dongle will be unavailable for after being released
| scheduler                  | Scheduler to use for dongle queue (can only be either 'fifo' or 'edf')

Example:<br>
> [!NOTE]
> Results may vary per system
```bash
./codexion 10 250 20 20 20 5 5 edf
```

To clean excess files after compilation, run:<br>
```bash
make clean

# to also remove binary
make fclean
```

# Thread Error Handling
Threads introduce a bunch of new issues to a program, like deadlock and starvation. Here are some measures that were taken to prevent them.

## Blocking cases
[Deadlock](https://en.wikipedia.org/wiki/Deadlock_(computer_science)) was prevented by ensuring every mutex locked, would properly unlock with every function,<br>
regardless of exit status, this was also how logging coder status was handled.<br>
I avoided using pthreads `pthread_cond_t` as I wanted to implement a solution for signalling events and wait times myself,
therefore removing another possible deadlock.<br>
Preventing starvation (coder burnout), was done by running the program with one of 2 implemented schedulers:

- FIFO - first in, first out
- EDF - earliest deadline first

Of course, starvation is not always avoidable given certain parameters.<br>
Cooldown checking was handled by sleeping periodically and checking program status<br>
instead of using `usleep()` once for the entire cooldown time reducing time accuracy on incoming events.<br>
This is also how burnout is precisely detected and stops any action correctly.

## Thead synchronization
Pthreads `pthread_cond_t` was not used as I wanted to implement ways of signalling and waiting for events myself.<br>
This was done with `t_ctx` storing timestamps that were used to check for events and program processing status.<br>
When program processing status ever becomes false (usually due to coder burnout), all active coders and events exit and get freed properly.
For coder coordination, the dongles were used to hold queues in the form of a heap.<br>
Based on the chosen scheduler, the queue will prioritise coders accordingly and only allow a coder to start compilation when the dongle is not on cooldown.<br>

Lastly, preventing [race conditions](https://www.geeksforgeeks.org/operating-systems/race-condition-in-operating-systems/) was done by ensuring mutexes are always locked in a function where a shared variable can be changed.

# Resources
> [!NOTE]
> **No AI was used in the making of this project**

- [Unix Threads in C](https://youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&si=x5V11YgOhwpLyz5_)
- [Linux Tutorial: POSIX Threads](https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html#BASICS)
- [pthread(3)](https://man.netbsd.org/pthread.3)
