#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main (int argc, char *argv[])
{
    int n;
    if (argc != 2) {
        fprintf(2, "Please input correct format:\nsleep n\n");
        exit(-1);
    }
    n = atoi(argv[1]);
    sleep(n);
    exit(0);    
}
