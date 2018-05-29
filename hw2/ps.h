#include "readproc.h"

struct ps_opt {
    short aflag;
    short xflag;
    short tflag;
    char sort_mode;
};

struct proc_list {
    struct proc_stat **array;
    int used;
    int size;
};

void ps(struct ps_opt o);

void insert_proc(struct proc_list *l, struct proc_stat *p);
void sort_proc(struct proc_list *l, int (*compare)(const void *, const void *));

int sort_pid(const void *a, const void *b);
int sort_ppid(const void *a, const void *b);
int sort_pgid(const void *a, const void *b);
int sort_sid(const void *a, const void *b);

void print_child(int ppid, int depth, struct proc_list *l);
