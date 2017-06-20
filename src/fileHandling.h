#ifndef fileHandling_H
#define fileHandling_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include <malloc.h>
#include "jansson.h"

#define TRUE 1
#define FALSE 0

int checkFile(const char *path);
int checkFolder(const char *path);
FILE *getFilePtr(const char *path);
DIR *getFolderPtr(const char *path);
bool checkFileFolder(const char *path);
int getFileSize(const char *path);
int listFileNumber(const char *path);
int listSubFolderNumber(const char *path);
char *traverseFolder(const char *path);
char *subFolder(const char *path);
char *checkLatestModifiedTime(const char *path);
int compareDateTime(char *dateTime, const char *path);
int fileDateTime(char *dateTime,char *path);
int convertEpoch(char *fileDateTime);

#endif // fileHandling_H
