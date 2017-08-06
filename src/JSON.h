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
json_t *updateJson(const char *folderPath, const char *jsonFile);
void getFileInfoFrmJson(json_t *fileArray,FileInfo *fptr,int counter);
json_t *getJsonArrayFrmFolderObj(json_t *folderObject);
json_t *createJsonObjectFrmFolder(const char *folderPath);
int checkJsonFile(const char *folder, const char *jsonFile);
int checkFileLaterThanJson(const char *folder,char *jsonFile);
void writeJsonIntoFile(const char *jsonFile,json_t *jsonObject);
int checkJSON(const char* path);
int delJSON(const char *JSONfile);

#endif // JSON_H
