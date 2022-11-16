#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

//Read characters from the pipe & echo them to stdout.

void read_from_pipe(int file){

    FILE *stream;
    int c;
    stream=fdopen(file,"r");
    while((c=fgetc(stream)) != EOF){
        putchar(c);
        fclose(stream);
    }
}

//Write some random text to the pipe

void write_to_pipe(int file){
    
    FILE *stream;
    stream=fdopen(file,"w");
    fprintf(stream, "hello world!!\n");
    fprintf(stream, "The End!!\n");
    fclose(stream);
}

int main(){

    pid_t pid;//for a fork() return it is a pid_t. Think as an integer
    int mypipe[2];

    //Create the Pipe
    if(pipe(mypipe)){
        fprintf(stderr, "Pipe failed!!!!!\n");
        return EXIT_FAILURE;
    }

    //Create the child process
    pid=fork();
    if(pid == (pid_t)0){//casting 0(int) to pid_t
        //This is the child process
        //Close one end first
        close(mypipe[1]);
        read_from_pipe(mypipe[0]);
        return EXIT_SUCCESS;
    }
    else if(pid < (pid_t)0){//Error checking section. fork() returns a negative pid_t if there was an error.
        //The fork failed
        fprintf(stderr, "Fork Failed!!\n");
        return EXIT_FAILURE;
    }else{
        //This is the parent process
        //Close the other end first
        close(mypipe[0]);
        write_to_pipe(mypipe[1]);
        return EXIT_SUCCESS;
    }
}
