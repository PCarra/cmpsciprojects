#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


int addmsg(char* type,char* msg);
void clearlog();
char *getlog();
int savelog(char *filename);
char* get_time_str(time_t rawtime);

void readFile(char inputfile[], int timeval);
