#include <stdio.h>
#include <unistd.h>
#include "ps.h"

int main(int argc, char* argv[]) {
    int opt;
    short aflag = 0;
    short xflag = 0;
    short tflag = 0;
    short invalid = 0;
    char sort_mode = '\0';

    while((opt = getopt(argc, argv, "axpqrst")) != -1) {
        switch(opt) {
            case 'a':
                aflag = 1;
                break;
            case 'x':
                xflag = 1;
                break;
            case 'p':
            case 'q':
            case 'r':
            case 's':
                if(sort_mode) invalid = 1;
                sort_mode = opt;
                break;
            case 't':
                tflag = 1;
                break;
            case '?':
                invalid = 1;
                break;
        }
    }
    if(invalid) {
        printf("Usage: %s [-a] [-x] [-p | -q | -r | -s] [-t]\n", argv[0]);
    } else {
        struct ps_opt o = { aflag, xflag, tflag, sort_mode };
        ps(o);
    }
    return 0;
}
