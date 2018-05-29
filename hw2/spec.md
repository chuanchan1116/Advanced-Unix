# Homework #2

Advanced Programming in the UNIX Environment

## Due: May 16, 2018

## Process Finder

In this homework, we are going to implement a simple process finder in C/C++ language. The objective is prettry simple, you have to enumerate all the processes in the system, just like the ps command. The mandatory requirement for this homework is as follows:

1. You have to list all the processes, and and display the following info for each process: pid, uid, gid, ppid, pgid, sid, tty, status, and (image) command line.
2. By default, your tool listed only the processes belong to the current user and have an associated terminal.
3. A -a option can be used to list processes from all the users.
4. A -x option can be used to list processes without an associated terminal
5. We have several sort options, -p, -q, -r, and -s, which sort the listed processes by pid (default), ppid, pgid, and sid, respectively.
6. For an associated tty, you have to convert its major/minor number back to its name.
7. For the program output format, please refer to the ``running example" section below.
8. An optional feature is to have a -t option, which lists processes in a tree-relationship, just like pstree.

In additon to the required features, the score of your program will also be graded based on the compiled (and stripped) binary size. The smaller the size, the higher the socre.

## Hints

You may retrieve the requirement information from the following different sources:

1. The stats for each process in the system is available at /proc/[pid]/stat, please read [proc(5)](http://man7.org/linux/man-pages/man5/proc.5.html).
2. The command line for each process is available at /proc/[pid]/cmdline, please also read [proc(5)](http://man7.org/linux/man-pages/man5/proc.5.html)
3. The mapping between a major/number of a terminal device can be done by scanning all the devices in /dev and create the mapping by yourself.

## Homework Submission

Please pack your files into a single ZIP archive and submit your homework via the E3 system. Please also provide a Makefile (used for compiling and linking your codes) and a README file (for additional notes).

## A Running Example

You have to follow the output format of the running example.

```
  pid   uid   gid  ppid  pgid   sid      tty St (img) cmd
    1     0     0     0     1     1        -  S (systemd) /sbin/init splash
    2     0     0     0     0     0        -  S (kthreadd)
    3     0     0     2     0     0        -  S (ksoftirqd/0)
    5     0     0     2     0     0        -  S (kworker/0:0H)
    7     0     0     2     0     0        -  S (rcu_sched)
...
  402  1000  1000     1   402   402        -  S (tmux) tmux 
  418  1000  1000   402   418   418   pts/13  S (bash) -bash 
 1000     0     0     1  1000  1000   pts/13  S (ModemManager) /usr/sbin/ModemManager 
 7541  1000  1000     1  7541  7541   pts/13  S (systemd) /lib/systemd/systemd --user 
 7795  1000  1000  7541  7541  7541   pts/13  S ((sd-pam)) (sd-pam)          
10286  1000  1000 10257 10257 10257   pts/13  S (sshd) sshd: chuang@pts/2 
10287  1000  1000 10286 10287 10287    pts/2  S (bash) -bash 
10299  1000  1000 10287 10299 10287    pts/2  S (tmux) tmux at 
14021  1000  1000 28846 14021 28846    pts/4  R (psf) ./psf -ax 
26372  1000  1000 26343 26343 26343    pts/4  S (sshd) sshd: chuang@pts/1 
26373  1000  1000 26372 26373 26373    pts/1  S (bash) -bash 
28846  1000  1000   402 28846 28846    pts/4  S (bash) -bash

```
