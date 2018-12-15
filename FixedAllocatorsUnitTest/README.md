# Final Exam Read me 

## How To Test it

The **FixedSizeAllocator** stuff is put in the **FixedAllocatorsUnitTest** project; Open the **Visual studio** solution file and set the  **FixedAllocatorsUnitTest**  as the startup project and run it in different configurations.



## Features

### Change the memory allocation between the *Normal Allocation* and the *Fixed Size Allocation*

* if you want to use the *Normal Allocator*, you need to comment the `#define USE_FIXED_ALLOCATORS ` in `FixedAllocatorsUnitTest\MemorySystem.h line:8`
* If you want to use the *Fixed Size Allocation*, you need to keep the macro.  

### Use the `_BitScanForward` to find the first set in bits

The Implement can be found in `FixedAllocatorsUnitTest\BitArray.cpp line:122.`

### *BitArray* uses a byte array(uint8_t * ) to handle the issue about platform change(32bit or 64 bit)



## Something about `FixedSizeAllocator`

In order to test it out, I just set the size of `FixedSizeAllocator` are 8, 16, 32, 64, 128, 256 and their block size is 100.



## Some Issue

Here is a issue about my project; I don't why that I cannot override the default `malloc` method and `free` with the `void * __cdecl malloc(size_t i_size)`and `void __cdecl free(void * i_ptr)`. So the only thing I can do is that I change the `malloc` and `free` to `myMalloc` and `myFree`, which can be found in `FixedAllocatorsUnitTest\FIxedAllocators.cpp.cpp line:9 and line: 28.`If you have some idea about this issue, please let me know :).



## Contact

If there is any question or issue, please slack **@Tezika** or email to tezikazhou@gmail.com, Thanks

