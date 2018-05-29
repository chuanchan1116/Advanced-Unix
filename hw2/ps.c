#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "readproc.h"
#include "devname.h"
#include "ps.h"

void ps(struct ps_opt o) {
    struct proc_stat *proc_info;
    struct proc_list list = { malloc(sizeof(struct proc_stat *) * 8), 0, 8 };
    int uid = geteuid();

    printf("  pid   uid   gid  ppid  pgid   sid      tty St (img) cmd\n");
    while(proc_info = read_proc()) {
        if(o.aflag || proc_info->uid == uid) {
            if(o.xflag || proc_info->tty_nr) {
                insert_proc(&list, proc_info);
            }
        }
    }


    switch(o.sort_mode) {
        case '\0':
        case 'p':
            sort_proc(&list, sort_pid);
            break;
        case 'q':
            sort_proc(&list, sort_ppid);
            break;
        case 'r':
            sort_proc(&list, sort_pgid);
            break;
        case 's':
            sort_proc(&list, sort_sid);
            break;
    }

    for(int i = 0; i < list.used; i++) {
        if(list.array[i]) {
            char tty[8];
            get_tty(tty, 8, list.array[i]->tty_nr);
            printf("%5d %5d %5d %5d %5d %5d %8s %2c %s", list.array[i]->pid,
                    list.array[i]->uid, list.array[i]->gid, list.array[i]->ppid, 
                    list.array[i]->pgrp, list.array[i]->session, tty, list.array[i]->state,
                    list.array[i]->comm);
            if(list.array[i]->cmdline){
                printf(" %s", list.array[i]->cmdline);
            }
            printf("\n");
            if(o.tflag) print_child(list.array[i]->pid, 0, &list);
            free_proc(list.array[i]);
            list.array[i] = NULL;
        }
    }

    free(list.array);
    list.array = NULL;
}

void insert_proc(struct proc_list *l, struct proc_stat *p) {
    if(l->used == l->size) {
        l->size *= 2;
        l->array = realloc(l->array, sizeof(struct proc_stat *) * l->size);
    }
    l->array[l->used++] = p;
};

void sort_proc(struct proc_list *l, int (*compare)(const void *, const void *)) {
    qsort(l->array, l->used, sizeof(struct proc_stat *), compare);
}

int sort_pid(const void *a, const void *b) {
    return (*(struct proc_stat **)a)->pid - (*(struct proc_stat **)b)->pid;
}

int sort_ppid(const void *a, const void *b) {
    return (*(struct proc_stat **)a)->ppid - (*(struct proc_stat **)b)->ppid;
}

int sort_pgid(const void *a, const void *b) {
    return (*(struct proc_stat **)a)->pgrp - (*(struct proc_stat **)b)->pgrp;
}

int sort_sid(const void *a, const void *b) {
    return (*(struct proc_stat **)a)->session - (*(struct proc_stat **)b)->session;
}

void print_child(int ppid, int depth, struct proc_list *l) {
    for(int i = 0; i < l->used; i++) {
        if(l->array[i] && l->array[i]->ppid == ppid) {
            char tty[8];
            get_tty(tty, 8, l->array[i]->tty_nr);
            printf("%5d %5d %5d %5d %5d %5d %8s %2c ", l->array[i]->pid,
                    l->array[i]->uid, l->array[i]->gid, l->array[i]->ppid, 
                    l->array[i]->pgrp, l->array[i]->session, tty, l->array[i]->state);

            for(int j = 0; j < depth; j++) printf("  | ");

            printf("  |-%s", l->array[i]->comm);
            if(l->array[i]->cmdline) {
                printf(" %s", l->array[i]->cmdline);
            }
            printf("\n");
            print_child(l->array[i]->pid, depth + 1, l);
            free_proc(l->array[i]);
            l->array[i] = NULL;
        }
    }
}
