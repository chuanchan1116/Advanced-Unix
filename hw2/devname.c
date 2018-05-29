#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include "devname.h"

void get_tty(char *c, int len, dev_t tty_nr) {
    static struct tty_map list = { NULL, 0, 0 };

    if(!list.size) {
        list.array = malloc(sizeof(struct tty_node *) * 8);
        list.size = 8;
        char path[64] = "/dev/";
        find_tty(&list, path);
    }

    for(int i = 0; i < list.used; i++) {
        if(tty_nr == list.array[i]->tty_nr) {
            strncpy(c, list.array[i]->name, len);
            return;
        } else {
            strcpy(c, "?");
        }
    }
}

void find_tty(struct tty_map *l, char *path) {
    DIR *d = opendir(path);
    struct dirent *dent;
    chdir(path);
    while(dent = readdir(d)) {
        struct stat file_state;
        lstat(dent->d_name, &file_state);
        if((file_state.st_mode & S_IFMT) == S_IFCHR) {
            struct tty_node *n = malloc(sizeof(struct tty_node));
            n->tty_nr = file_state.st_rdev;
            snprintf(n->name, 7, "%s%s", path+5, dent->d_name);
            insert_map(l, n);
        } else if(S_ISDIR(file_state.st_mode)) {
            if(strcmp(".", dent->d_name) == 0 || strcmp("..", dent->d_name) == 0)
                continue;

            char npath[64];
            snprintf(npath, 63, "%s%s/", path, dent->d_name);
            find_tty(l, npath);
            chdir(path);
        }
    }
}

void insert_map(struct tty_map *l, struct tty_node *p) {
    if(l->used == l->size) {
        l->size *= 2;
        l->array = realloc(l->array, sizeof(struct tty_node *) * l->size);
    }
    l->array[l->used++] = p;
}

