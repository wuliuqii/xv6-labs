#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void filter(int fd);

void filter(int fd) {
    int prime;
    int p[2];
    pipe(p);

    if (read(fd, &prime, sizeof(int)) != sizeof(prime)) {
        exit(1);
    }
    printf("prime %d\n", prime);

    if (fork() == 0) {
        close(p[1]);
        filter(p[0]);
    } else {
        int n;
        int eof;

        close(p[0]);
        do {
            eof = read(fd, &n, sizeof(int));
            if (n % prime != 0)
                write(p[1], &n, sizeof(int));
        } while (eof);
        close(p[1]);
    }

    wait(0);
    exit(0);
}

int main(int argc, char *argv[]) {
    int p[2];
    pipe(p);

    if (fork() == 0) {
        close(p[1]);
        filter(p[0]);
    } else {
        close(p[0]);
        for (int i = 2; i < 36; i++) {
            write(p[1], &i, sizeof(int));
        }
        close(p[1]);
    }

    wait(0);
    exit(0);
}