#include"generateCRC32Value.h"


unsigned long long poly;
unsigned long long msb;

/*************************************************************
* 	Hash CRC32 checksum value of a given file
* 	Return 0 value if the given input is empty file/not a file
*
*	Input: 	fileName	Path of the file we want to hash  
*			
*	Output: crcValue	File's crc32 value
*			
*	Destroy: none
**************************************************************/
int hashCRC(const char *fileName){
    int crcValue=0,i=0;
	unsigned long long rem=0;
	unsigned int c;
	msb=0x80000000;
    msb=msb<<32;
    FILE *fptr = fopen(fileName,"r");
	poly=POLY;
	poly=poly<<32;
	
	c=fgetc(fptr);

	for(i=0;i<4;++i){
		if(c!=EOF){
			c=c<<24;
			rem=rem|c;
			c=fgetc(fptr);
		}
		rem=rem<<8;
	}
	crcValue = getBytes(fptr,&c,&rem);
    fclose(fptr);
	return crcValue;
}

/*************************************************************
* 	Calculate the bytes of the given file
*
*	Input: 	fptr		Pointer to the path of the file 
*			bytePtr		Pointer to the file
			tempPtr 	Temporary pointer to store byte pointer
			
*	Output: byte of the file
*			
*	Destroy: none
**************************************************************/
int getBytes(FILE* fptr,unsigned int *bytePtr, unsigned long long *tempPtr){
	if(*bytePtr!=EOF){
		*bytePtr=*bytePtr<<24;
        *tempPtr=*tempPtr|*bytePtr;
        *bytePtr=fgetc(fptr);
		shiftXOR(fptr,bytePtr,tempPtr);	
	}
	else{
		shiftXOR2(bytePtr,tempPtr);
		calCRC32(tempPtr);
	}
}

/*************************************************************
* 	XOR the bytes of the given file
*
*	Input: 	fptr		Pointer to the path of the file 
*			bytePtr		Pointer to the file
			tempPtr 	Temporary pointer to store byte pointer
			
*	Output: XOR value of file's bytes
*			
*	Destroy: none
**************************************************************/
int shiftXOR(FILE *fptr, unsigned int *bytePtr, unsigned long long *tempPtr){
	int count=8;
	while(count>0){
		if(*tempPtr&msb)
		*tempPtr=*tempPtr^poly;
		*tempPtr=*tempPtr<<1;
		count--;
	}
	getBytes(fptr,bytePtr,tempPtr);
}

/*************************************************************
* 	XOR the bytes of the given file
*
*	Input: 	fptr		Pointer to the path of the file 
*			bytePtr		Pointer to the file
			tempPtr 	Temporary pointer to store byte pointer
			
*	Output: XOR value of file's bytes
*			
*	Destroy: none
**************************************************************/
int shiftXOR2(unsigned int *bytePtr,unsigned long long *tempPtr){
	int count=32;
    while(count>0){
		if(*tempPtr&msb)
        *tempPtr=*tempPtr^poly;
		*tempPtr=*tempPtr<<1;
		count--;	
	}
}

/*************************************************************
* 	Get CRC32 checksum value of a given file through pointer
* 	Return 0 value if the given input is empty file/not a file
*
*	Input: 	tempPtr		Pointer of the file we want to hash  
*			
*	Output: crc			File's crc32 value
*			
*	Destroy: none
**************************************************************/
int calCRC32(unsigned long long *tempPtr){
	int crc=*tempPtr>>32;
	//printf("\nCRC32 : %08X\n\n",crc);
	return crc;
}
