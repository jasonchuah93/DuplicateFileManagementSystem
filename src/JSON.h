#ifndef JSON_H
#define JSON_H

#include "jansson.h"

typedef struct FileInfo FileInfo;
struct FileInfo{
	char *name;
	unsigned long long int fileSize;
	unsigned long int fileCRC32Value; 
	unsigned long int fileEpochSec;
};

void getFileInfoFrmJson(json_t *fileArray,FileInfo *fptr,int counter);
json_t *getJsonArrayFrmFolderObj(json_t *folderObject);
json_t *createJsonObjectFrmFolder(const char *folderPath);
void writeJsonIntoFile();
int checkJSON();
void createJSON();
int delJSON();

#endif // JSON_H
