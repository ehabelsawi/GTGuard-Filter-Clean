# Support library

We need all kind of little helpers for ensure ABI compatibility, accessing existing structures at given addresses or 
even hooking into existing functions. This library has it all. 

## ABI checking

To check the layout (offset of members) in any class, simply add the following structure to your class declaration.
This is a compile-time check. If the offsets are wrong, your code will not compile.


\include abitest.example.h
