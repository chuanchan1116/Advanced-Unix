#ifndef  __LIBMINIC_H__
#define __LIBMINIC_H__

#define _SIGSET_NWORDS (1024 / (8 * sizeof (unsigned long int)))
#define NULL 0

#define SIGHUP 1
#define SIGINT 2
#define SIGQUIT 3
#define SIGILL 4
#define SIGTRAP 5
#define SIGABRT 6
#define SIGIOT 6
#define SIGBUS 7
#define SIGFPE 8
#define SIGKILL 9
#define SIGUSR1 10
#define SIGSEGV 11
#define SIGUSR2 12
#define SIGPIPE 13
#define SIGALRM 14
#define SIGTERM 15
#define SIGSTKFLT 16
#define SIGCHLD 17
#define SIGCONT 18
#define SIGSTOP 19
#define SIGTSTP 20
#define SIGTTIN 21
#define SIGTTOU 22
#define SIGURG 23
#define SIGXCPU 24
#define SIGXFSZ 25
#define SIGVTALRM 26
#define SIGPROF 27
#define SIGWINCH 28
#define SIGIO 29
#define SIGPOLL SIGIO
#define SIGPWR 30
#define SIGSYS 31
#define SIGUNUSED 31

const SIG_BLOCK = 0;
const SIG_UNBLOCK = 1;
const SIG_SETMASK = 2;

typedef struct {
    unsigned long int __val[_SIGSET_NWORDS];
} sigset_t; /* size: 128 */
typedef long long size_t;
typedef struct jmp_buf_s {
    long long reg[8];
    sigset_t mask;
} jmp_buf[1];

struct timespec {
    long tv_sec;
    long tv_nsec;
};

struct sigaction {
    void (*sa_handler)(int); /* size: 8 */
    unsigned long sa_flags;
    void (*sa_restorer)(void);
    sigset_t sa_mask;        /* mask last for extensibility */
};

#define SA_NOCLDSTOP    0x00000001u
#define SA_NOCLDWAIT    0x00000002u
#define SA_SIGINFO    0x00000004u
#define SA_ONSTACK    0x08000000u
#define SA_RESTART    0x10000000u
#define SA_NODEFER    0x40000000u
#define SA_RESETHAND    0x80000000u

#define SA_NOMASK    SA_NODEFER
#define SA_ONESHOT    SA_RESETHAND

#define SA_RESTORER    0x04000000

int read(unsigned int fd, char *buf, size_t count);
int sys_read(unsigned int fd, char *buf, size_t count);
int write(unsigned int fd, char *buf, size_t count);
int sys_write(unsigned int fd, char *buf, size_t count);
void pause();
void sys_pause();
long sleep(long s);
long nanosleep(struct timespec *rqtp, struct timespec *rmtp);
long sys_nanosleep(struct timespec *rqtp, struct timespec *rmtp);
void alarm(unsigned int seconds);
void sys_alarm(unsigned int seconds);
void exit(int error_code);
void sys_exit(int error_code);
int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
int setjmp(jmp_buf env);
void longjmp(jmp_buf env, int value);
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);

#endif
