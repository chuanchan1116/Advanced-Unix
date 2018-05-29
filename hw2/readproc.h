#ifndef PROC_STAT
#define PROC_STAT

struct proc_stat {
    int pid;
    char *comm;
    char state;
    int ppid;
    int pgrp;
    int session;
    int tty_nr;
    int uid;
    int gid;
    char *cmdline;
};

struct proc_stat* read_proc();
void free_proc(struct proc_stat *p);
#endif
