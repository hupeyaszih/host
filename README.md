# HOST (Hupeyaszih OS Technology)
OS project with immutable and content based memory management.

> [!WARNING]
>I'm not going to develop this project anymore, because I tested this memory design and it indicated bad results: In the best-case scenario, the RAM usage decreased 98.83%; in the worst-case scenario, the RAM usage increased 200%. I tested in other ways too, but the results are the same. So, the project is finished.

## Table of Contents
- [Philosophy and Memory Model](#philosophy-and-memory-model)
- [Trade-Offs (simply)](#trade-offs-simply)
- [Status](#status)
- [Roadmap](#roadmap)
- [Memory Map](#memory-map)
- [Not Planned Ideas](#not-planned-ideas)
- [Building and Running](#building-and-running)
- [Useful Make Targets](#useful-make-targets)

## Philosophy and Memory Model
Why do we spend so much memory? For what?
HOST provides an immutable-memory, it enables us to make a hashtable-based memory management system. It means two different variables that have the same value and live in the RAM shares the same address, since the values are immutable, if we want to change the value of one of the variables, HOST will give us another address, and the variable whose the value we changed now lives in different address.
It may seem like a bad situation, and yes it is but it depends where you look from.
### Trade-Offs (simply):

(+) RAM usage will dramatically decrease. OS will use less ram for the same results.

(-) It'll create hashtable looking overhead. It means it has a potential to damage OS's and other softwares', that run on the OS, speed.

(-) Imagine that you built a software in C (or another language) which is targeting my OS. The software mustn't do following thing; 
```c
int main(void) {
    int *p1 = malloc(sizeof(int));
    *p1 = 10;

    int *p2 = p1;
    *p2 = 20;

    int res = *p1;
    return res;
}
```
Did you notice that? Okay, one question: What is the program's exit code? If you said "20", you are completely wrong! But why? Let me explain: OS allocated an int in heap which is so normal, then you changed the value of where p1 points to ten, then you declared one more pointer (p2) which points to the address where p1 points to.
This is also normal too. But the thing happens when you tried to change value of where p1 points: If you remember, the rule was "memory is immutable", so the OS gives our beautiful p2 another address, and now p2 points to the address which has the value of "20", which is 20, but p1 still points to old memory address which is 10.
So, the answer to the first question is "10". The program would definitely finished with exit code "10".

(+) But still, advantage of less RAM usage is the main target of the project.

The WORST thing is that most of software written would have to be rewritten to work properly in my OS (I may develop a compatibility layer once I implement most of the features I want to implement).

NOTE: Virtual memory management is still available via the memory manager design (I didn't design it yet but I've some ideas which are allows the OS to do virtual memory management.)

## Status
- [x] bootloader (with long mode)
- [x] jumping to the kernel
- [x] VGA driver
- [x] Memory Map
- [x] IDT (Interrupt Descriptor Table), NOTE: done, but needs reconsideration.

## Roadmap
- [ ] Memory Manager (PMM and VMM)
- [ ] Other stuffs

## Memory Map
```
0x7c00     -> boot_stage1.asm
0x7e00     -> boot_stage2.asm
0x500      -> memory map (first 4 byte is how much page read)
0x00008200 -> kernel_entry
```

## Not Planned Ideas
SNN's are really good in my opinion, they don't need so much power, they are adaptive when compared with LLMs, and they have a lot of other benefits. And I'm curious about AI supported OS designs. I've a plan for this thing but I'm not certainly sure what to do right now,
yes I've some plans but I'll keep those ideas myself because even I've a plan for this thing, I am not entirely sure what to do right now. That is why this idea is under the "Not Planned Ideas" subtitle.

## Building and Running
### Dependencies:
Make sure you have installed following tools on your system:
- **Build Tools**:  `make`, `nasm`, `gcc`, `ld`
- **Emulator**: `qemu-system-x86_64`
- **Documentation**: `doxygen` (optional)

```bash
#Clone the repository
git clone https://github.com/hupeyaszih/host.git
cd host

#Build/Generate the kernel image
make
#Or specify the architecture explicitly
make ARCH=x86_64

#Launch the kernel in QEMU
make run
```
**NOTE:** Currently only supports `ARCH=x86_64`

### Running on real hardware
**HOST can run directly on real bare-metal hardware.**

Steps:
1. Ensure that you built host.bin (using the `make build` command).
2. Write host.bin into the USB etc. via `dd` (linux) or you can use `Rufus` (Windows):
```bash
#Example using dd on Linux (WARNING: double-check the target is your USB to avoid data loss!)
sudo dd if=./build/host.bin of=/dev/<Your USB> bs=512 conv=notrunc status=progress oflag=sync
```
3. Plug the USB into the target machine.
4. Access your motherboard's BIOS settings and ensure:
    - Secure boot is disabled
    - Legacy Boot / CSM (Compability Support Mode) is enabled.
5. Boot from the USB and there it is. HOST is booted!


### Useful Make Targets
`make clean` - removes `build/` directory

`make docs`  - Generates HTML documentation using doxygen into `doxy/`
