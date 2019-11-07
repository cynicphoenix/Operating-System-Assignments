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

#define PAGES 256
#define PAGE_SIZE 256
#define MEMORY_SIZE PAGES * PAGE_SIZE
#define TLB_SIZE 16
#define MEM_FILE "BACKING_STORE.bin"

int pagetable[PAGES]; // Fixed length page table
int TLB[TLB_SIZE][3]; // TLB contains <key, value, lastaccess time> tuples

void main(int argc, char* argv[]) {
    if(argc < 2) { // Invalid Input
        printf("Invalid Input!\n");
        return;
    }

    char *input_file = argv[1];
    char *output_file = "output.txt";
    char *file_name = MEM_FILE;

    // Initially Page Table is empty
    for(int i = 0; i < PAGES; i++)
        pagetable[i] = -1;
    
    // Initially TLB is also empty
    for(int i = 0; i < TLB_SIZE; i++)
        TLB[i][0] = -1;
    
    int addresses = 0; // Stotes total addresses translated
    int pageFault = 0; // Stores total page fault
    int hitCount = 0; // Stores hit count in TLB
    int counter = 0; // Tells current time used for replacement policy

    int ptr_fd = open(file_name, O_RDONLY); // Shared memory object for reading from DISC in case of page fault
    signed char *ptr = mmap(0, MEMORY_SIZE, PROT_READ, MAP_PRIVATE, ptr_fd, 0); // Create a mapping
    
    // File reading & writing
    FILE *inputFilePointer = fopen(input_file, "r");
    FILE *outputFilePointer = fopen(output_file, "w");

    signed char MEMORY[MEMORY_SIZE]; // Memory File
    char virtual_memory_address_buffer[10];
    unsigned char freePage = 0;

    // In case input file does not exist
    if( inputFilePointer == NULL) {
        printf("Such file do not exist!\n");
        return;
    }

    // Read from file and virtual memory management
    while(fgets(virtual_memory_address_buffer, 10, inputFilePointer) != NULL) {
        int virtual_memory_address = atoi(virtual_memory_address_buffer);
        int offset = virtual_memory_address & 255;
        int page_number = (virtual_memory_address >> 8) & 255;
        int frame_number;

        int TLB_hit = 0; // Flag variable
        for(int i = 0; i < TLB_SIZE; i++) {
            if(page_number == TLB[i][0]) {
                TLB_hit = 1;
                hitCount++;
                frame_number = TLB[i][1];
                TLB[i][2] = counter;
                break;
            }
        }

        if(TLB_hit == 0) {           
            frame_number = pagetable[page_number];

            // Update TLB
            int index = -1; // Which TLB to replace
            for(int i = 0; i < TLB_SIZE; i++) { // Incase TLB is empty
                if(TLB[i][0] == -1) {
                    index = i;
                    break;
                }
            }
            if(index == -1) { // Incase TLB is not empty
                int min = 9999;
                for(int i = 0; i < TLB_SIZE; i++) {
                    if(min > TLB[i][2]) {
                        min = TLB[i][2];
                        index = i;
                    }
                }
            }
            if(frame_number != -1) {
                TLB[index][0] = page_number;
                TLB[index][1] = frame_number;
                TLB[index][2] = counter;
            }

            // Update Page in case of page fault
            if(frame_number == -1) {
                pageFault++;
                frame_number = freePage;
                freePage++;
                memcpy(MEMORY + frame_number * PAGE_SIZE, ptr + page_number * PAGE_SIZE, PAGE_SIZE);
                pagetable[page_number] = frame_number;

                // Update TLB also
                TLB[index][0] = page_number;
                TLB[index][1] = frame_number;
                TLB[index][2] = counter;
            }
        }

        int physical_address = (frame_number << 8) | offset;
        signed char value = MEMORY[frame_number * PAGE_SIZE + offset];
        fprintf(outputFilePointer, "Virtual address : %d Physical address : %d Value: %d\n", virtual_memory_address, physical_address, value);

        counter++; // Clock increment
        addresses++; // Total address increment
    }

    printf("Total Address References : %d\n", addresses);
    printf("Page Faults              : %d\n", pageFault);
    printf("Page Fault Rate          : %.2f \n", ((float)pageFault/(float)addresses)*100.0);
    printf("Hit Count                : %d\n", hitCount);
    printf("Hit Count Rate           : %.2f\n", ((float)hitCount/(float)addresses)*100.0);    
    return;
}