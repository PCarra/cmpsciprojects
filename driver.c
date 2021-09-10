#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "liblog.h"

void print_usage(){
	printf("Use -t to specify a value for delay followed by an input file name.\n");
	printf("Use -g to print log to screen");
	printf("Use -c to clear the log");
}

int main(int argc, char *argv[]){
	char inputfile[20];
	int timeval;
	int opt;
	int clear_flag=0;
	int get_flag=0;


	while ((opt = getopt(argc, argv, ":t:hgc")) != -1){
		switch(opt){
		case 'h':
			//call help function
			print_usage();
			break;
		case 't':
			timeval = atoi(optarg);
			break;
		case 'g':
			get_flag=1;
			break;
		case 'c':
			clear_flag=1;
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
	if(argc>4){
		print_usage();
		exit(1);
	}
	else if(timeval && argc==4){
		strcpy(inputfile, argv[3]);
		readFile(inputfile, timeval);
	}
	else if(clear_flag){
		clearlog();
	}
	else if(get_flag){
		printf("%s", getlog());
	}
	else{
		print_usage();
		exit(1);
	}
	//printList(head);
	return 0;
}
