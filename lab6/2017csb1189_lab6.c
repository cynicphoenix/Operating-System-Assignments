#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void main(int argc, char *argv[]) {
    if(argc < 2){ 
        printf("Invalid Input!\n");
        return;
    }
    
    long long int virtualAddress = atoi(argv[1]); // Input virtual address
    if(virtualAddress < 0) {
        printf("Virtual Address must pe positive!\n");
        return;
    }
    
    long long int pageNumber, offset; // Page number & offset
    pageNumber = virtualAddress/((int)pow(2,12));
    offset = virtualAddress - pageNumber * (int)pow(2,12);
    printf("The address %lld contains:\n", virtualAddress);
    printf("page number = %lld\n", pageNumber);
    printf("offset = %lld\n", offset); 
}