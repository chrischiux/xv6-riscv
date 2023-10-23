#include "kernel/types.h"
#include "user/user.h"

// int main(int argc, char *argv[]) {
    
//     int parent_pid, child_pid, p[2];
//     parent_pid = getpid();
//     child_pid = fork();
//     pipe(p);
//     printf("%d: starting pingpong\n", pid1);
//     // Terminate the process.
//     exit(0);
// }

int
main(int argc, char *argv[])
{
    int p[2];  // file descriptors for pipe
    char recv_buf[5];

    pipe(p);

    if (fork() == 0) {  // child
        read(p[0], recv_buf, 5);
        printf("Child: received %s\n", recv_buf);
        close(p[0]);

        write(p[1], "pong", 5);
        close(p[1]);

    } else {  // parent
        write(p[1], "ping", 5);
        close(p[1]);
        wait(0);

        read(p[0], recv_buf, 5);
        printf("Parent: received %s\n", recv_buf);
        close(p[0]);
    }
    exit(0);
}