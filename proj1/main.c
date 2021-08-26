#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	int opt;
	while ((opt = getopt(argc, argv, ":if:ht")) != -1){
		switch(opt){
		case 'h':
			printf("Help function\n");
			break;
		case 't':
			printf("Time in seconds: %s\n", optarg);
			break;
		case ':':
			printf("Option needs a value!");
			break;
		case '?':
			printf("Unknown option: %c\n", optopt);
			break;
		}
	}
	
	//optind is for the extra args which are not parsed in the first loop
	for(; optind < argc; optind++){
		printf("file arguments: %s\n", argv[optind]);
	}
	
	return 0;
}
