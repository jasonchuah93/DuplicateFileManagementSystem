#ifndef JSON_H
#define JSON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include "jansson.h"

int checkJSON(const char* path);
int createJSON(const char* path);

#endif // JSON_H
