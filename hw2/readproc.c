#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include "readproc.h"

struct proc_stat* read_proc() {
    static DIR *d = NULL;
    if(!d) d = opendir("/proc/");

    struct dirent *dent;
    while(dent = readdir(d)) {
        if(dent->d_name[0] > '0' && dent->d_name[0] <= '9') {
            break;
        }
    }


    if(!dent || !dent->d_name) return 0;

    struct proc_stat *ret = malloc(sizeof(struct proc_stat));

    char path[64];
    sprintf(path, "/proc/%s/stat", dent->d_name);

    struct stat file_stat;
    stat(path, &file_stat);
    ret->uid = file_stat.st_uid;
    ret->gid = file_stat.st_gid;

    FILE *f = fopen(path, "r");
    fscanf(f, "%d %ms %c %d %d %d %d", &(ret->pid), &(ret->comm), &(ret->state), &(ret->ppid), &(ret->pgrp), &(ret->session), &(ret->tty_nr));
    fclose(f);

    sprintf(path, "/proc/%s/cmdline", dent->d_name);
    f = fopen(path, "r");
    fscanf(f, "%ms", &(ret->cmdline));
    fclose(f);

    return ret;
}

void free_proc(struct proc_stat *p) {
    if(p->comm) free(p->comm);
    if(p->cmdline) free(p->cmdline);
    free(p);
}
