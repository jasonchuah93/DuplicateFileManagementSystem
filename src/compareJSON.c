#include "compareJSON.h"

int compareFileSize(Node **sizeFromRBT,Node *sizeToCompare){
	unsigned long long int rootSize = getFileSize(*sizeFromRBT);
	unsigned long long int targetSize = getFileSize(sizeToCompare);
	if(rootSize > targetSize){
		return 1;
	}else if(rootSize < targetSize){
		return -1;
	}else if(rootSize == targetSize){ 
		compareFileCRC(sizeFromRBT,sizeToCompare);
	}
}

int compareFileCRC(Node **crcFromRBT,Node *crcToCompare){
	unsigned long int rootCrc = getFileCrc(*crcFromRBT);
	unsigned long int targetCrc = getFileCrc(crcToCompare);
	
	if(rootCrc > targetCrc){
		return 1;
	}else if(rootCrc < targetCrc){
		return -1;
	}else if(rootCrc == targetCrc){ 
		return 0;
	}
}

int compareFileByte(Error *nodeFromRBT,Node *nodeToCompare){
	int i = 0,int1 = 0, int2 = 0;
	char temp[100] = {0}, temp2[100] = {0};
	const char *rootLocation = getFilePathLocationFrmErr(nodeFromRBT);
	const char *targetLocation = getFilePathLocationFrmNode(nodeToCompare);
	FILE *fptr1 = fopen(rootLocation,"r");
	FILE *fptr2 = fopen(targetLocation,"r");
	int1 = getc(fptr1);
	int2 = getc(fptr2);
	while ((int1 != EOF) && (int2 != EOF) && (int1 == int2)) {
         int1 = getc(fptr1);
         int2 = getc(fptr2);
	}
	if(int1 == int2)
		return 0;
	else
		return -1;
}