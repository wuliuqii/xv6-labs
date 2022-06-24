#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    int p[2];
    char msg;
    pipe(p);

    if (fork() == 0) {
        read(p[0], &msg, 1);
        printf("child received: %c\n", msg);
        printf("%d: received ping\n", getpid());
        close(p[0]);
        write(p[1], "b", 1);
        close(p[1]);
    } else {
        write(p[1], "a", 1);
        close(p[1]);

        wait(0);

        read(p[0], &msg, 1);
        printf("parent received: %c\n", msg);
        printf("%d: received pong\n", getpid());
        close(p[0]);
    }

    exit(0);
}