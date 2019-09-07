#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
    pid_t p = fork();
    if (p != 0){
    	sleep(10);
        //system("ps -eo pid,ppid,stat,cmd");
    }
    else {
        exit(0);
    }

    return 0;
}