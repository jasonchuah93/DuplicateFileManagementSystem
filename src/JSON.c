#include "JSON.h"

int checkJSON(const char* path){
	//FILE *JSONF = fopen(path,"r");
	int cmp = 0;
	const char ext = '.';
	char *jsonExt;
	jsonExt = strrchr(path,ext);
	cmp = strcmp(jsonExt,".json");
	if(cmp == 0)
		return 1;
	else
		return 0;
	
}

int createJSON(const char* path){
	FILE *f = fopen(path,"w");
}

