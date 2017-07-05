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