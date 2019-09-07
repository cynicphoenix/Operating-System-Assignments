#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include<sys/wait.h>
#include <stdlib.h>

void main(int argc, char* argv[]) {
	int n = atoi(argv[1]);
	if(n <= 0) { // To check invalid input like negative and zero
		printf("Invalid Input!\n");
		return;
	}

	pid_t p = fork();

	if(p < 0){ // Check if child process is created
		printf("Creation of child unsuccessful!\n");
		return;
	}

	if(p){ // Parent Process : Wait for child to complete
		printf("Parent process starts...\n");
		wait(NULL);
		printf("Parent Process Completes!\n");
	}
	else{ // Collatz conjecture code for child process
		printf("Child process starts...\n\n");
		printf("%d ", n);
		while(n != 1) {
			if(n%2)
				n = 3*n + 1;
			else
				n /= 2;

			printf("%d ", n);
		}
		printf("\n\n");
		printf("Child process completed\n");
	}
}