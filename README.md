# HOST (Hupeyaszih OS Technology)

## Philosophy
Why do we spend so much memory? For what?
HOST provides an immutable-memory, it enables us to make a hashtable-based memory management system. It means two different variables that have the same value and live in the RAM shares the same address, since the values are immutable, if we want to change the value of one of the variables, HOST will give us another address, and the variable whose the value we changed now lives in different address.
It may seem like a bad situation, and yes it is but it depends where you look from.
Trade-Offs (simply):

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

NOTE: Virtual memory management is still available via our memory manager design (I didn't design it yet but I've some ideas which are allows the OS to do virtual memory management.)

## Not Planned Ideas
SNN's are really good in my opinion, they don't need so much power, they are adaptive when compared with LLMs, and they have a lot of other benefits. And I'm curious about AI supported OS designs. I've a plan for this thing but I'm not certainly sure what to do right now,
yes I've some plans but I'll keep those ideas myself because even I've a plan for this thing, I am not entirely sure what to do right now. That is why this idea is under the "Not Planned Ideas" subtitle.
