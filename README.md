# RickRoll LKM

Let's take rickrolling to the next level...

## So... what is RickRoll LKM?

A fun little project of mine that I developed in my free time.
It is a LKM (Loadable Kernel Module) for x86-64 linux systems that opens a specific video that is predefined in the LKM (rickroll in this case) when user tries to play a video file.
It does this by hooking into openat() linux system call.

I got this idea from an old youtube conference (like DEFCON, BlackHat, can't remember exactly which) video (I couldn't find the link to the video, I will update this README.md if I found it again) and rebuilt it using [xcellerator's](https://github.com/xcellerator) ftrace helper library (for hooking into syscalls) so it works on newer kernels.

## Disclaimer

Before you procede any further I need you to inform you that this was developed merely for educational purposes.
Do not install this on a real device, please test this LKM only on virtual machines.
I developed & tested this LKM only on a Linux Mint 22.2 virtual machine.

I'M NOT RESPONSIBLE FOR ANY DAMAGES

## How to compile and install

First you have to change one line in the rickroll.c:

```
#define RICKROLL_PATH "<path to your video>"
```

Replace this line with a video filepath of your choice

Eg :-
```
#define RICKROLL_PATH "/home/n0b0dy/Downloads/Rickroll {HD + No ads}.mp4"   
```


Then compile it using the Makefile

```console
$ make
```


and install it (on a virtual machine)

```console
$ sudo insmod ./rickroll.ko
```


## How to remove it

```console
$ sudo rmmod rickroll.ko
```
