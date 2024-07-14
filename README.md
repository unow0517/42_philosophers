# 42_philosophers

# Must Know
* **A Thread** : A basic unit of CPU Utilization. IF a process has multiple threads of cnotrol, it can perform more than one task at a time (Multi-threaded process).

  It shares its code, data, other os resources(open files and signals) with other threads belonging to the same process.

* **A Core** : A worker. OS is like a boss. OS tell CPU what to do. Threads are like sequences of commands given to the cores, like conveyer belts of products. 4 Core CPU = CPU has 4 workers which can work on conveyer belt(threads)

  4 Physical cores x 2Threads/Core = 8 Logical Cores. A Core cannot work on multiple threads at a time.

A Core with multiple threads is more efficient than a core with a thread. When there is downtime working on a thread (due to resource error for example), the core can switch to another thread and work on it.
* **Parallel Operations** : Core to Core, all operate at the same time, **Concurrent Operations** : Core to Thread, operate by switching.

* **Data Races** : occur when multiple tasks or threads access a shared resource without sufficient protections, leading to undefined or unpredictable behavior.

* **Mutex** : MUTual EXclusion, a lock to prevent data races to happen.

# Key Point
* **pthread** : to run a function in a seperate thread.
* **pthread_create** : to start a new thread in calling process.
* **pthread_join** : to join the execution to the main thread. Allows the calling thread to wait for the ending of the target thread.
* **Dot Operator (.) in Struct** : The dot operator is used to access members of a structure directly. When you have a structure variable, you use the dot operator to access its members.
* **Arrow Operator (->) in Struct** : The arrow operator is used to access members of a structure through a pointer. When you have a pointer to a structure, you use the arrow operator to access its members.

### References
[Introduction to Threads](https://www.youtube.com/watch?v=ldJ8WGZVXZk) : Comparing single thread vs multiple thread with C code.

[CPU Cores VS Threads Explained](https://www.youtube.com/watch?v=hwTYDQ0zZOw) : CPU, Thread explanation for dummies like me.

https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2
