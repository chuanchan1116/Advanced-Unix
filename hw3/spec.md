# Homework #3

###### Advanced Programming in the UNIX Environment

### Due: May 30, 2018

## Extend Mini Lib C to Handle Signals

In this homework, you have to extend the mini C library introduced in the class to support signal relevant system calls. You have to implement (at least) the following C library functions in Assembly using the syntax supported by yasm (x86_64) assembler.

1. [v] write: write data to a specific file descriptor
2. [v]  setjmp: prepare for long jump by saving the current CPU state. In addition, preserve the signal mask of the current process.
3. [v] longjmp: perform the long jump by restoring a saved CPU state. In addition, restore the preserved signal mask.
4. [?] sigaction: setup the handler of a signal.
5. [v] sigprocmask: can be used to block/unblock signals, and get/set the current signal mask.
6. [] alarm: setup a timer for the current process.
7. [v] pause: suspend the execution of the current process until a signal is delivered.
8. [v] sleep: suspend the execution of the current process for a given period.
9. [v] exit: terminate the current process.

The API interface is equivalent to what we have in the standard C library. However, because we are attempting to replace the standard C library, your program can only be linked against the library implemented in this homework. We will use the following commands to assemble, compile, link, and test your codes.

```bash
$ yasm -f elf64 libminic.asm -o libminic.o
$ ld -shared -o libminic.so libminic.o
$ gcc -c -g -Wall -fno-stack-protector test1.c
$ gcc -nostdlib -o test1 test1.o start.o libminic.o
$ gcc -nostdlib -o test1s test1.o start.o libminic.so
```

Where `libminic.asm` is the assembly implmentation of this homework and `test1.c` is the testing code prepared by the TAs. The `start.o` file is the program start routine we have introduced in the class. Please notice that there is a *-nostdlib parameter* passed to the compiler, which means that you will not be able to work with any standard C library functions, but only the functions you have implemented in the `libminic.asm file`. In addition to your library source code, you will also have to provide a corresponding `libminic.h` file. The testing codes will include this file and use the function prototypes and data types defined in the header file.

To ensure that your library can handle signals properly, the setjmp function must save the signal mask of the current process in your customized jmp_buf data structure. The saved signal mask must be restored by the longjmp function.

## Homework Submission

Please pack your files into a single ZIP archive and submit your homework via the E3 system. Please also provide a Makefile (used for compiling and linking your codes) and a README file (indicating what features you have implemented).

## Sample Test Cases

We will implement some simple test programs and link them against your mini C library. Here are three simple test cases: test0.c, test1.c, and test2.c.

The commands to assemble, compile, and link test1.c, as well as the corresponding runtime output are pasted below.

```bash
$ make test1
yasm -f elf64 libminic.asm -o libminic.o
gcc -c -g -Wall -fno-stack-protector test1.c
yasm -f elf64 start.asm -o start.o
gcc -nostdlib -o test1 test1.o start.o libminic.o
rm start.o test1.o
$ ./test1
This is function a().
This is function b().
This is function c().
This is function d().
This is function e().
This is function f().
This is function g().
This is function h().
This is function i().
This is function j().
$
```

The commands to assemble, compile, and link test2.c, as well as the corresponding runtime output are pasted below.

```bash
$ make test2
yasm -f elf64 libminic.asm -o libminic.o
gcc -c -g -Wall -fno-stack-protector test2.c
yasm -f elf64 start.asm -o start.o
gcc -nostdlib -o test2 test2.o start.o libminic.o
rm start.o test2.o
$ ./test2
^CSIGINT received.
^CSIGINT received.
^CSIGINT received.
^\Quit (core dumped)
$
```

## Hints

This might be a relatively difficult homework, so we have several hints for this homework. Reading these hints carefully may reduce your efforts to implement this homework.

1. x86\_64 system call table: It should be easy for you to find one on Internet. Here is the one we demonstrated in the course ([x86\_64 syscall table](http://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/)).

2. If you need precise prototypes for system calls, you may refer to an online Linux cross reference (LXR) site. For example, this page shows the official prototypes form the linux kernel ([include/linux/syscalls.h](https://elixir.bootlin.com/linux/v4.16.8/source/include/linux/syscalls.h#L603)).

3. You will have to define all the required data structures and constants by yourself. If you do not know how to define a data structure, try to find them from the Linux kernel source codes.

4. With LXR, you may also check how a system call is implemented, especially when an error code is returned from a system call. For example, here is the implementation for [sys\_rt\_sigaction](https://elixir.bootlin.com/linux/v4.16.8/source/kernel/signal.c#L3711) system call in the kernel. By reading the codes, you would know that passing an incorrect sigset\_t size would lead to a negative EINVAL error code.

5. For implementing setjmp with the preserved process signal mask, the recommended data structure for x86_64 is given below:

  ```c
  typedef struct jmp_buf_s {
  	  long long reg[8];
	  sigset_t mask;
  } jmp_buf[1];
  ```
  The minimal eight 64-bit values you have to preserve in the *reg* array are: RBX, RSP, RBP, R12, R13, R14, R15, and the return address (to the caller of setjmp). The current process signal mask can be preserved in the *mask* field.

6. To ensure that a signal handler can be properly called without *crashing* a process, you have to do the following additional setup in your implemented sigaction function as follows (illustrated in C language):

  ```c
  long sigaction(int how, const struct sigaction *nact, struct sigaction *oact) {
      ...
      nact->sa_flags |= SA_RESTORER;
      nact->sa_restorer = /* your customized restore routine, e.g., __myrt */;
      ret = sys_rt_sigaction(how, nact, oact, sizeof(sigset_t));
      ...
  }
  ```

  The implementation of the *__myrt* function is simply making a system call to *sigreturn*.

7. Please notice that the sigaction data structure used in the C library may be *different* from that used in the kernel.

8. The assembly instructions we used in this homework are pretty simple. All the required instructions have been introduced in the class. Here we enumerate the possible required assembly instructions for this homework.

  ```
  add     call    cmp     inc     jmp
  jnz     lea     mov     or      pop
  push    ret     sub     syscall xor
  ```
