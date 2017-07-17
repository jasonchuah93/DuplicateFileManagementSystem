#ifndef fileHandling_H
#define fileHandling_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define MaxFile 10000

char *createJSONFilePath(const char *folderPath);
int checkFile(const char *path);
int checkFolder(const char *path);
FILE *getFilePtr(const char *path);
DIR *getFolderPtr(const char *path);
int getFileSize(const char *path);
int listFileNumber(const char *path);
int listSubFolderNumber(const char *path);
int traverseFolder(char *folderPath);
char *subFolder(const char *path);
int compareDateTime(char *dateTime,const char *path);
int getFileDateTime(char *dateTime,const char *path);
int convertEpoch(char *fileDateTime);

#endif // fileHandling_H
