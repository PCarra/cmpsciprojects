#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "liblog.h"

void print_usage(){
	printf("Usage: Use -f to specify a filename, use -t to specify a value for delay");
}

int main(int argc, char *argv[]){
	char inputfile[20];
	int timeval;
	int opt;

	while ((opt = getopt(argc, argv, ":f:t:h")) != -1){
		switch(opt){
		case 'h':
			//call help function
			print_usage();
			break;
		case 't':
			timeval = atoi(optarg);
			break;
		case 'f':
			strcpy(inputfile, optarg);
			break;
		case ':':
			printf("Option needs a value!");
			print_usage();
			//call help message
			break;
		case '?':
			perror("Unkown option try again");
			//printf("Unknown option: %c\n", optopt);
			print_usage();
			//call help message
			break;
		}
	}

	readFile(inputfile, timeval);
	printf("%s", getlog());
	clearlog();
	//printList(head);
	return 0;
}
