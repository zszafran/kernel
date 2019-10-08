# Standard Library

This directory contains the standard library shared across both user-space programs and the kernel.

## User Space (libc)

The default target `//src/lib` compiles the library for usage in user-space which interacts with the kernal via system calls.

## Kernel Space (libk)

The target `//src/lib:libk` compiles the library for usage inside the kernel itself.

This rules provides the  `-D__is_libk` cppflag at compile-time to let library switch implementations accordingly.
