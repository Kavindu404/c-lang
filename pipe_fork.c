#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void main(){

    int fds[2];
    char buf[512];
    int n,pid;

    pipe(fds);
    pid=fork();

    if(pid>0){//Parent Process
        close(fds[0]);
        write(fds[1], "hello", 5);
        printf("The producer\n");
    }else{//Child Process
        close(fds[1]);
        n=read(fds[0], buf, sizeof(buf));
        printf("The Consumer: %s\n",buf);
        exit(0);
    }
}

/*
fds is an integer array.
pipe is a system call. This will create a pipe where fds[0] knows one end and fds[1] knows the other
Pipe is a Bidirectional one. Initially the direction is not set. But there are some
restrictions. We cant enter or leave from both sides at the same time
Initially there is only one copy of fds. But after fork(), there will be two copies.
In parent process, there will be fds with 2 elements and so as in the child process.
fds[0] in both child and parent points to the same end and same with the fds[1].
fork() will only duplicate the process. Not the pipe. 

In parent's class;
It closes fds[0] link, which means fds[0] is no longer pointed to one end of the pipe.

In child's class;
It closes fds[1].

So now parent only knows one side of the pipe and the child knows only the other side.

Parent writes in "hello" to one side of the pipe that it knows. First it inserts h, then e and so on. It is known as a stream. Which is an ordered set of characters.

Child is reading from the other side of the pipe.

This is how the pipe helps to communicate between processes.

Call for the pipe function should be done before fork() so the assignment of fds[0]&1 will be synchronize in both processes. 

PIPE IS VOLATILE

fd- file descriptor

*/
