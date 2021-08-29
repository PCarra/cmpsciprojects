#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "listlib.h"

typedef structlist_struct {
	data_t item;
	struct list_struct *next;
} list_t;

int logmsgs(char *msgfile);

//appends to its internal list structure a node containing a copy of data
int addmsg(const char type, const char *msg){
	list_t *newnode;
	int nodesize;

	nodesize = sizeof(list_t) + strlen(*msg) + 1;
	if ((newnode = (list_t *) (malloc(nodesize))) == NULL)
		return -1;
	//calculate timestamp
	newnode->item.time = *msg.time;
	newnode->item.type = *msg.type;
	newnode->item.string = (char *)newnode + sizof(list_t);
	strcpy(newnode->item.string, *msg.string);
	newnode->next = NULL;
	if (headptr == NULL)
		headptr = newnode;
	else
		tailptr->next = newnode;
        return 0;
}

//releases all the storage that has been allocated for the logged messages and empties the list of logged messages
void clearlog(){
}

//allocates enough space for a string containing the entire log, copies the log into this string, and returns a pointer to the stringg
char *getlog(){
        return NULL;
}

//saves the logged messsages to a disk file
int savelog(char *filename){
        return 0;
}

//read messages from msg file and call addmsg to add messages to log list(struct_list)
int logmsgs(char *msgfile){
	return 0;
}

int main(int argc, char *argv[]){
	char *filename = 'logfile.txt';
	int timeval;
	char msgfile;
	//declare a linked list
	int opt;
	while ((opt = getopt(argc, argv, ":if:ht")) != -1){
		switch(opt){
		case 'h':
			printf("Help function\n");
			//call help function
			break;
		case 't':
			printf("Time in seconds: %s\n", optarg);
			if(optarg != NULL)
				timeval = optarg;
				msgfile = argv[0];
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
	
	/*
	//optind is for the extra args which are not parsed in the first loop
	for(; optind < argc; optind++){
		//file arguments are where the messages to be logged are stored
		printf("file arguments: %s\n", argv[optind]);
		//save msg files to a list of strings
	}
	*/

	if(timeval && msgfile!=NULL)
		//call function to read msgfile and store msgs into linked list
	
	return 0;
}
