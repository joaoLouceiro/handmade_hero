Starting with a very interesting resource: [The Intel 64 and IA-32 Architectures Software Developer Manuals](https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html). Cool resource.

He speaks about the **RDTSC (Read Time-Stamp Counter)** instruction, a processor-level instruction which helps us measure how long a piece of code took to execute, in CPU cycles.

Then, he goes over Window's [QueryPerformanceCounter()](https://learn.microsoft.com/en-us/windows/win32/api/profileapi/nf-profileapi-queryperformancecounter) and [QueryPerformanceFrequency()](https://learn.microsoft.com/en-us/windows/win32/api/profileapi/nf-profileapi-queryperformancefrequency) - in Linux's case, [SDL_GetPerformanceCounter()](https://wiki.libsdl.org/SDL2/SDL_GetPerformanceCounter) and [SDL_GetPerformanceFrequency()](https://wiki.libsdl.org/SDL2/SDL_GetPerformanceFrequency), which give us the time a piece of code takes to execute.

While RDTSC gives us a measure of how much work the CPU has done, we can't rely on it to tell us how long it took, due to variations in CPUs, to upcycling or downcycling, etc.

Let's start by printing out something that allows us to know how many frames per second we are actually outputting. We do that by calling QueryPerformanceCounter() right as our loop starts.

We review the concept of a union, which is a data structure in C and C++ that allows us to map various things to the same memory.

We eventually get to count how many frames per second (or how many milliseconds per frame) our program is outputting, and Casey rambles a bit about Dimensional Analysis, which sounds cool.

Right by the end, Casey goes over **intrinsics** and **SIMD**. 

**Intrinsics** are instructions that the compiler can execute directly in the CPU, or straight up assembly, in a sense. The compiler can simply issue the assembly instruction directly, without having to move stuff around.

**SIMD** (Single Instruction, Multiple Data) is, bluntly, a mechanism through which we can jam a bunch of data onto the same register and do a set computation on it.
