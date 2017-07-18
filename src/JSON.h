#ifndef JSON_H
#define JSON_H

#include "jansson.h"

typedef struct FileInfo FileInfo;
struct FileInfo{
	const char *fileName;
	unsigned long long int fileSize;
	unsigned long int fileCRC32Value; 
};

FileInfo *createInfo();
void getFileInfoFrmJson(json_t *fileArray,FileInfo *fptr,int counter);
json_t *getJsonArrayFrmFolderObj(json_t *folderObject);
json_t *createJsonObjectFrmFolder(const char *folderPath);
void writeJsonIntoFile();
int checkJSON();
void createJSON();
int delJSON();

#endif // JSON_H
