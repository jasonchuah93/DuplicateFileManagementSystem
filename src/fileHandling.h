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
int compareDateTime(char *JSONDateTime, const char *path);
int getDateTime(char *dateTime,const char *path);

#endif // fileHandling_H
