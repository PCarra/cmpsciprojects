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
			//call help message
			break;
		case '?':
			printf("Unknown option: %c\n", optopt);
			//call help message
			break;
		}
	}

	if(inputfile[0]=='\0'){
		strcpy(inputfile, "messages.txt");
	}

	readFile(inputfile, timeval);
	printf("%s", getlog());
	clearlog();
	//printList(head);
	return 0;
}
