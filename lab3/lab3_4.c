#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> 
#include <sys/shm.h> 
#include <sys/stat.h>
#include <sys/mman.h> // for PROT_WRITE & PROT_READ

void main(int argc, char* argv[]) {
	const int SIZE = 4096;
	const char* name = "OS";
	int n = atoi(argv[1]);

	if(n <= 0) { // To check invalid input like negative and zero
		printf("Invalid Input!\n");
		return;
	}

	int shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666); //Shared Memory Object
	ftruncate(shm_fd, SIZE); //Assign size to shared memory object
	void* ptr = mmap(0, SIZE, PROT_WRITE | PROT_WRITE, MAP_SHARED, shm_fd, 0); //Create a mapping

	pid_t p = fork();

	if(p < 0){ // Check if child process is created
		printf("Creation of child unsuccessful!\n");
		return;
	}


	if(p){ // Parent Process : Wait for child to complete
		printf("Parent process starts...\n");
		wait(NULL);

		printf("Parent process resumes...\n\n");	
		while(strcmp((char*)ptr, "-1") > 0) {
			printf("%s ", (char*)ptr);
			ptr += sizeof(int);
		}
		printf("\n\n");
		printf("Parent Process Completes!\n");
		shm_unlink(name);
	}
	else{ // Collatz conjecture code for child process
		printf("Child process starts...\n");
		sprintf(ptr, "%d", n);
		ptr += sizeof(int);
		while(n != 1) {
			if(n%2)
				n = 3*n + 1;
			else
				n /= 2;
			sprintf(ptr, "%d", n);
			ptr += sizeof(int);
			
		}
		sprintf(ptr, "-1");
		printf("Writing to shared memory object completed!\n");
		printf("Child process completed!\n");
	}
}

/*
To run code :
	gcc lab3_4.c -lrt
	./a.out 35

Why "-lrt" ?
-l : Search the library named library when linking
*/


