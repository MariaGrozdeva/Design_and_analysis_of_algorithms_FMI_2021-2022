## Intrinsics
Intrinsics are assembly-coded functions that allow you to use C++ function calls and variables in place of assembly instructions.
Intrinsics are expanded inline eliminating function call overhead. Providing the same benefit as using inline assembly, intrinsics improve code readability,
assist instruction scheduling, and help reduce debugging.

[**Full list of *Intel intrinsics***](https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html)

In the solution, I use [**Advanced Vector Extensions (AVX)**](https://en.wikipedia.org/wiki/Advanced_Vector_Extensions).

Here you can see the results of the comparisons I've done between ordinary Binary search and AVX Binary search.  
There are seven different tests with much various data executed repeatedly.  

![alt_text]()
