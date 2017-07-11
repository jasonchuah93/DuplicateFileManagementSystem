#ifndef JSON_H
#define JSON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include "fileHandling.h"
#include "generateCRC32Value.h"
#include "jansson.h"

int checkJSON(const char* path);
void createJSON(const char* JSONpath,const char* filePath,char *filePathPtr[],int fileCount);
int delJSON(char *file);

#endif // JSON_H
