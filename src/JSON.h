#ifndef JSON_H
#define JSON_H

#include "jansson.h"

void traverseJson(json_t* jObject);
json_t *createJsonObject();
void writeJsonIntoFile();
int checkJSON();
void createJSON();
int delJSON();

#endif // JSON_H
