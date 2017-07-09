#include "fileHandling.h"

#define MaxFile 10000
struct stat attr;
struct dirent *dir;
struct tm t;
static char* lastFile[MaxFile] = {0};
static int lastFileCount;

/*************************************************************
*   Scan the folder, traverse all content inside
*
*	Input: 	path		the path of the folder we want to scan  
*			
*	Output: size		size of the file 
*			
*	Destroy: none
**************************************************************/
int traverseFolder(char *folderPath){
	DIR *d = getFolderPtr(folderPath);
	int countFileNumber = 0,fileLen = 0, latestFileNumber = 0;
	char *subFolderPath = NULL, *jsonFileName = "/jsonInfo.json";
	char *jsonPath = (char*)malloc(1+strlen(folderPath)+strlen(jsonFileName));
	unsigned long int latestEpochSec = 0, currentEpochSec = 0;
	char dateTime[100] = {0}, filePath[200] = {0}, latestFilePath[200] = {0};
	while((dir = readdir(d))!= NULL){
		if(dir->d_type == DT_REG){
			if(memcmp(dir->d_name,"jsonInfo.json",13) == 0){
				goto here;
			}else{
				fileLen = strlen(dir->d_name)+1;
				lastFile[countFileNumber] = malloc(fileLen);
				strcpy(lastFile[countFileNumber],dir->d_name);
				countFileNumber++;
			}
			here:
			sprintf(filePath,"%s/%s",folderPath,dir->d_name);
			fileDateTime(dateTime,filePath);
			latestEpochSec = convertEpoch(dateTime);
			if(latestEpochSec > currentEpochSec){
				strcpy(latestFilePath,dir->d_name);
				currentEpochSec = latestEpochSec;
			}
		}else if(dir->d_type == DT_DIR && strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0){
			subFolderPath = subFolder(folderPath);
			traverseFolder(subFolderPath);
		}
	}
	if(strcmp(latestFilePath,"jsonInfo.json") == 0){
		printf("JSON File is latest at %s.\n",folderPath);
	}else{
		strcpy(jsonPath,folderPath);
		strcat(jsonPath,jsonFileName);
		lastFileCount = countFileNumber;
		if(lastFileCount > 0){
			createJSON(jsonPath,folderPath,lastFile,lastFileCount);
		}
	}
	latestFileNumber = countFileNumber;
	closedir(d);
	return latestFileNumber;
}

/*************************************************************
* 	Check if the parameter is any type of file 
*
*	Input: 	path		the path of the file we want to check  
*			
*	Output: 1			indicate is file
*			0			indicate is not a file
*	
*	Destroy: none
**************************************************************/
int checkFile(const char *path) {
    FILE *f = fopen(path,"r");
	if(f!=NULL)
		return 1;
	else
		return 0;
}

/*************************************************************
* 	Get file pointer  
*
*	Input: 	path		the path of the file we want to check  
*			
*	Output: f					pointer of the file
*			Throw error			indicate is not a file
*	
*	Destroy: none
**************************************************************/
FILE *getFilePtr(const char *path){
	int c = 0;
	c = checkFile(path);
	if(c == 1){
		FILE *f = fopen(path,"r");
		return f;
	}
}

/*************************************************************
* Check if the parameter is folder
*
*	Input: 	path		the path of the folder we want to check  
*			
*	Output: 1			indicate is folder
*			0			indicate is not a folder
*	
*	Destroy: none
**************************************************************/
int checkFolder(const char *path) {
    DIR *d = opendir(path);
	if(d!=NULL)
		return 1;
	else 
		return 0;
}

/*************************************************************
* 	Get folder pointer  
*
*	Input: 	path		the path of the file we want to check  
*			
*	Output: d					pointer of the folder
*			Throw error			indicate is not a folder
*	
*	Destroy: none
**************************************************************/
DIR *getFolderPtr(const char *path){
	int c = 0;
	c = checkFolder(path);
	if(c == 1){
		DIR *d = opendir(path);
		return d;
	}else if(c == 0){
		
	}
}

/*************************************************************
* Check the size of a given file
*
*	Input: 	path		the path of the file we want to check  
*			
*	Output: size		size of the file 
*			
*	Destroy: none
**************************************************************/
int getFileSize(const char *path){
	int size = 0;
	FILE *f = getFilePtr(path);
	fseek(f,0,SEEK_END);    
	size = ftell(f);   
    return size;
}

/*************************************************************
* Check the total number of file in folder 
*
*	Input: 	path		the path of the file we want to check  
*			
*	Output: count		number of file inside a folder 
*			
*	Destroy: none
**************************************************************/
int listFileNumber(const char *path){
	int count = 0;
	DIR *folder = getFolderPtr(path);
	while((dir=readdir(folder))!=NULL){
		if(dir->d_type == DT_REG){
			count++;
		}
	}
	return count;
}

/*************************************************************
* Check the total number of sub folders in folder 
*
*	Input: 	path		the path of the file we want to check  
*			
*	Output: count		number of sub folders inside a folder 
*			
*	Destroy: none
**************************************************************/
int listSubFolderNumber(const char *path){
	int count = 0;
	DIR *folder = getFolderPtr(path);
	while((dir=readdir(folder))!=NULL){
		if(dir->d_type == DT_DIR && strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0){
			count++;
		}
	}
	return count;
}

/****************************************************************************
*   This function add subfolder path name into existing folder path name
*
*	Input: 	path		the path of the folder
*			
*	Output: newPath		the path of subFolder 
*			
*	Destroy: none
****************************************************************************/
char *subFolder(const char *path){
	static char newPath[500];
	strcpy(newPath,path);//Copy the path to a new path 
	strcat(newPath,"/");//Add / right after the path name
	strcat(newPath,dir->d_name);//Add the sub folder path name right after the main folder path name		
	return newPath;
}

/*************************************************************
* Compare the last modified date & time between 2 files 
*
*	Input:   dateTime       the file date time for compare 	 
*			 path			the path of the file to compare

*	Output:  1				if dateTime is latest than path 
*			 0 				if path is latest than dateTime
 
*	Destroy: none
**************************************************************/
int compareDateTime(char *dateTime,const char *path){
	unsigned long int epoch1 = 0;
	unsigned long int epoch2 = 0;
	char dateTimePath[20] ={0};
	fileDateTime(dateTimePath,path);
	epoch1 = convertEpoch(dateTime);
	epoch2 = convertEpoch(dateTimePath);
	if(epoch1 > epoch2)
		return 1;
	else if(epoch1 < epoch2)
		return -1;
	else if(epoch1 == epoch2)
		return 0;
}

/*************************************************************
* Check the last modified date & time of the file 
*
*	Input: 	 dateTime       Initially is NULL
*			 path			the path of the file we want to check  

*	Output:  dateTimes		date and time of the file 
*			
*	Destroy: none
**************************************************************/
int fileDateTime(char *dateTime,const char *path){
	char times[50]={0};
	time_t t = time(NULL);
	stat(path, &attr);
	strftime(times,20,"%Y/%m/%d %H:%M:%S",localtime(&(attr.st_mtime)));
	strcpy(dateTime,times);
}

/*************************************************************
* Convert date and time of given file to epoch format
*
*	Input: 	 dateTime       Initially is NULL
*
*	Output:  epochSecs		date and time of the file in epoch format
*			
*	Destroy: none
**************************************************************/
int convertEpoch(char *fileDateTime){
	unsigned long int epochSecs = 0;
	time_t epoch = 0;
	char year[5] = {0},month[5] = {0},day[5] = {0};
	char hr[5] = {0},min[5] = {0},sec[5] = {0};
	int yearVal = 0,monthVal = 0,dayVal = 0;
	int hrVal = 0,minVal = 0,secVal = 0;
	strncpy(year,fileDateTime,4);strncpy(month,fileDateTime+5,2);strncpy(day,fileDateTime+8,2);
	strncpy(hr,fileDateTime+11,2);strncpy(min,fileDateTime+14,2);strncpy(sec,fileDateTime+17,2);
	yearVal = atoi(year);monthVal = atoi(month);dayVal = atoi(day);
	hrVal = atoi(hr);minVal = atoi(min);secVal = atoi(sec);
	t.tm_year  = yearVal-1900;
	t.tm_mon   = monthVal-1;           
    t.tm_mday  = dayVal;
    t.tm_hour  = hrVal;
    t.tm_min   = minVal;
    t.tm_sec   = secVal;
    t.tm_isdst = -1; 
	epoch = mktime(&t);
	epochSecs = (unsigned long int)epoch;
	return epochSecs;
}