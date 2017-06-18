#ifndef generateCRC32Value_H
#define generateCRC32Value_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define POLY 0x82608EDB

int hashCRC(char *fileName);
int getBytes(FILE* fptr,unsigned int *bytePtr, unsigned long long *tempPtr);
int shiftXOR(FILE *fptr, unsigned int *bytePtr, unsigned long long *tempPtr);
int shiftXOR2(unsigned int *bytePtr,unsigned long long *tempPtr);
int calCRC32(unsigned long long *tempPtr);

#endif // generateCRC32Value_H
