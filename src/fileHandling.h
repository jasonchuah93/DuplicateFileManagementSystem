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

#define TRUE 1
#define FALSE 0

bool checkFile(const char* path);
bool checkFolder(const char* path);
bool checkFileFolder(const char* path);
int checkFileSize(const char*path);
int checkFileLatestTime(const char* path);

#endif // fileHandling_H
