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


int checkFile(const char* path);
int checkFolder(const char* path);
FILE *getFile(const char* path);
bool checkFileFolder(const char* path);
int getFileSize(const char*path);
char *checkLatestModifiedTime(const char* path);
char *getFileName(char* path);
int listFileNumber(const char* path);
int listSubFolderNumber(const char* path);
char *listAllFilesPrototype(const char* path);
char *traverseFolder(const char* path);

#endif // fileHandling_H
