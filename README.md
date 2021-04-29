# CS550 Assignment 02

This is the repo for my second project. This is going to be good

## Instructions for running

The kernel module and userspace program (driver.c) are located in the 
`parts_ef` directory. Once in the directory, enter `make` to compile 
the kernel module and compile the driver with `gcc -o driver driver.c`.

Once you are done compiling, install the kernel module using
`sudo insmod process_list.ko`. Once this is done, you can run the driver
using `sudo ./driver`. You **must** use `sudo` when running the `./driver`
executable.

Thanks! Have a nice day!
