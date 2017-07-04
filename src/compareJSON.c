#include "compareJSON.h"

int compareFileSize(Node **sizeFromRBT,Node *sizeToCompare){
	unsigned long long int rootSize = (*sizeFromRBT)->fileSize;
	unsigned long long int targetSize = sizeToCompare->fileSize;
	if(rootSize > targetSize){
		return 1;
	}else if(rootSize < targetSize){
		return -1;
	}else if(rootSize == targetSize){ 
		compareFileCRC(sizeFromRBT,sizeToCompare);
	}
}

int compareFileCRC(Node **sizeFromRBT,Node *sizeToCompare){
	unsigned long long int rootCrc = (*sizeFromRBT)->crc32Value;
	unsigned long long int targetCrc = sizeToCompare->crc32Value;
	
	if(rootCrc > targetCrc){
		return 1;
	}else if(rootCrc < targetCrc){
		return -1;
	}else if(rootCrc == targetCrc){ 
		return 0;
	}
}