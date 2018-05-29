#include <unistd.h>

struct tty_node {
    dev_t tty_nr;
    char name[8];
};

struct tty_map {
    struct tty_node **array;
    int used;
    int size;
};

void get_tty(char *c, int len, dev_t tty_nr);
void find_tty(struct tty_map *l, char *path);

void insert_map(struct tty_map *l, struct tty_node *p);
