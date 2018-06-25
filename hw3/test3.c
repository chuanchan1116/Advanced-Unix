#include "libminic.h"

static int  mylen(const char *s) { int len = 0; while(*s++) len++; return len; }
static void myzero(void *m, int size) { char *ptr = (char *) m; while(size-- > 0) *ptr++ = '\0'; }
static char hh(unsigned char c) { c >>= 4;   return (c >= 0 && c <= 9) ? ('0'+c) : ('a'+c-10); }
static char hl(unsigned char c) { c &= 0x0f; return (c >= 0 && c <= 9) ? ('0'+c) : ('a'+c-10); }

static int canjump = 0;
static jmp_buf jb;

static void pr_mask(const char *m) {
    sigset_t s;
    int i;
    unsigned char *rptr = (unsigned char*) &s;
    myzero(&s, sizeof(s));
    write(1, m, mylen(m));
    if(sigprocmask(0, NULL, &s) >= 0) {
        char output[128], *wptr = output;
        *wptr++ = ' ';
        for(i = 0; i < 4; i++, rptr++) {
            *wptr++ = hh(*rptr);
            *wptr++ = hl(*rptr);
        }
        *wptr++ = '\n';
        *wptr++ = '\0';
        write(1, output, mylen(output));
    } else {
        write(1, "\n", 1);
    }
}

static void sigusr1(int s) {
    pr_mask("sigusr1:");
    if(canjump) {
        canjump = 0;
        longjmp(jb, 1);
    }
}

int main() {
    struct sigaction act;
    myzero(&act, sizeof(act));
    act.sa_handler = sigusr1;
    sigaction(SIGUSR1, &act, NULL);
    pr_mask("before setjmp:");
    if(setjmp(jb) != 0) {
        pr_mask("after longjmp:");
        exit(0);
    }
    canjump = 1;
    pause();
    return 0;
}
