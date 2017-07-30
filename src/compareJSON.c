#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "fileHandling.h"
#include "generateCRC32Value.h"
#include "LinkedList.h"
#include "compareJSON.h"

int compareList(Node **sizeFromRBT, Node *sizeToCompare){
	unsigned long long int rootSize = getSizefromList(*sizeFromRBT);
	unsigned long long int targetSize = getSizefromList(sizeToCompare);
	if(rootSize > targetSize)
		return 1;
	else if(rootSize < targetSize)
		return -1;
}

/******************************************************************
* 	Compare the size of 2 input parameters
*
*	Input: 	sizeFromRBT		the size of node from RBT   
*			sizeToCompare	the size of node to compareFileByte
*
*	Output:  1			indicate the sizeFromRBT is larger than
*						sizeToCompare
*
*			-1`			indicate the sizeFromRBT is smaller than
*						sizeToCompare
*	If both size are the same, call function to compare their CRC32
*	value instead
*	Destroy: none
*******************************************************************/
int compareFileSize(Node **sizeFromRBT,Node *sizeToCompare){
	unsigned long long int rootSize = getSize(*sizeFromRBT);
	unsigned long long int targetSize = getSize(sizeToCompare);
	if(rootSize > targetSize){
		return 1;
	}else if(rootSize < targetSize){
		return -1;
	}else if(rootSize == targetSize){ 
		compareFileCRC(sizeFromRBT,sizeToCompare);
	}
}

/******************************************************************
* 	Compare the crc value of 2 input parameters
*
*	Input: 	crcFromRBT		the crc of node from RBT   
*			crcToCompare	the crc of node to compareFileByte
*
*	Output:  1			indicate the crcFromRBT is larger than
*						sizeToCompare
*
*			-1`			indicate the crcFromRBT is smaller than
*						sizeToCompare
*	If both crc are the same, call function to compare the 2 files 
*	byte by byte
*	Destroy: none
*******************************************************************/
int compareFileCRC(Node **crcFromRBT,Node *crcToCompare){
	unsigned long int rootCrc = getCRC(*crcFromRBT);
	unsigned long int targetCrc = getCRC(crcToCompare);
	
	if(rootCrc > targetCrc){
		return 1;
	}else if(rootCrc < targetCrc){
		return -1;
	}else if(rootCrc == targetCrc){ 
		return 0;
	}
}

/******************************************************************
* 	Compare the byte of 2 input parameters
*
*	Input: 	nodeFromRBT		the node from RBT   
*			nodeToCompare	the node to compareFileByte
*
*	Output:  0			indicate the bytes of 2 files are the same
*
*			-1`			indicate the bytes of 2 files are different
*
*	Destroy: none
*******************************************************************/
int compareFileByte(char *rootFile,char *fileToCompare){
	int int1 = 0, int2 = 0;
	char temp[100] = {0}, temp2[100] = {0};
	FILE *fptr1 = fopen(rootFile,"r");
	FILE *fptr2 = fopen(fileToCompare,"r");
	int1 = getc(fptr1);
	int2 = getc(fptr2);
	while ((int1 != EOF) && (int2 != EOF) && (int1 == int2)) {
         int1 = getc(fptr1);
         int2 = getc(fptr2);
	}
	if(int1 == int2){
		return 0;
	}else if(int1 != int2){
		return -1;
	}
}
