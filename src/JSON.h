#ifndef JSON_H
#define JSON_H

#include "jansson.h"
#include "fileInfo.h"

json_t *updateJsonFolderObject(const char *folderName, const char *jsonFile);
int checkFilesLatestThanJson(const char *folderName,char *jsonFile);
void writeJsonObjectIntoFile(const char *jsonFile,json_t *jsonObject);
void getFileInfoFromJsonObject(json_t *fileArray,FileInfo *fptr,int counter);
json_t *createJsonFolderObject(const char *folderPath);
json_t *goIntoJsonArrayFrmFolderObj(json_t *folderObject);
int checkJsonFileExistInFolder(const char *folder, const char *jsonFile);
int checkJsonTypeFile(const char *jsonFilePath);

#endif // JSON_H
