# EFI-Linker
It'll eventually easy you in creating an EFI image.

Lastly tested on clang. Made to work on GCC too (tested on 6.1.1).

You will need to include/compile "main.c" in your project in order to work. "main.h" is the header with the functions
you will want to use.

Uefi image created using this helper was tested on Asrock B75M-GL motherboard firmware.


The helper header is for now only required for "test1.c".

Test1 (test1.c) will accept a single command parameter naming a binary file will be used to create a simple EFI image with it's content as single executable section. 

Dependencies:

C standard libraries.
VLA, VM extensions.
__typeof__ extension (for test1).

You could use fasm to build the sections. For this purpose you would also need to find UEFI documentation and .inc files.
