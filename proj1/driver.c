#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "liblog.h"

char* get_time_str(time_t rawtime);

typedef struct list_struct {
	data_t data;
	struct list_struct* next;
} list_t;

struct list_struct *head = NULL;

struct tm* get_time(){
	time_t tm;
	struct tm * tp = localtime(&tm);
	return tp;
}

char* get_time_str(time_t rawtime){
	struct tm * timeinfo;
	timeinfo = localtime(&rawtime);
	char* time_str = asctime(timeinfo);
	time_str[strlen(time_str) - 1] = '\0';
	return time_str;
}
	
//appends to its internal list structure a node containing a copy of data
int addmsg(const char type[], const char msg[]){
	int nodesize;
	nodesize = sizeof(struct list_struct) + strlen(msg) + strlen(type) + 1;
	struct list_struct* newnode = (struct list_struct*)malloc(nodesize);
	//calculate timestamp
	time_t rawtime = time(&rawtime);
	newnode->data.time = rawtime;
	strcpy(newnode->data.type, type);
	strcpy(newnode->data.msg, msg);
	//newnode->next = head;
	//head = newnode;
	if(head->data.msg[0] == '\0'){
		head = newnode;
	}
	else {
		struct list_struct* curr = head;
		while(curr->next!=NULL){
			curr = curr->next;
		}
		curr->next = newnode;
	}
        return 0;
}


//releases all the storage that has been allocated for the logged messages and empties the list of logged messages
void clearlog(){
	struct list_struct* current = head;
	struct list_struct* next;
	while(current!=NULL){
		next = current->next;
		free(current);
		current = next;
	}
	head = NULL;

}

//allocates enough space for a string containing the entire log, copies the log into this string, and returns a pointer to the string
char *getlog(){
	FILE *fp = fopen("messages.log", "rb");
	fseek(fp, 0, SEEK_END);
	long fsize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char *string = malloc(fsize + 1);
	fread(string, 1, fsize, fp);
	fclose(fp);
	string[fsize]=0;
        return string;
}

//saves the logged messsages to a disk file
int savelog(char *filename){
	FILE *fp;
	fp = fopen(filename, "w");
	struct list_struct *n = NULL;
	n = (struct list_struct*)malloc(sizeof(struct list_struct));
	n = head;
	while (n!=NULL){
		//use fprintf and format each part of the linked list to a file
		fprintf(fp, "%s: %s: %s", get_time_str(n->data.time), n->data.type, n->data.msg);
		n = n->next;
	}
	fclose(fp);
        return 0;
}

void printList(struct list_struct *n){
      	char time_string[9];
	while (n!=NULL){
		printf("%s: %s: %s ", get_time_str(n->data.time), n->data.type, n->data.msg);
		n = n->next;
	}
}

//read messages from msg file and call addmsg to add messages to log list(struct_list)
void readFile(char inputfile[], int timeval){
	FILE *file = fopen(inputfile, "r");
        int delay = timeval*2;
	if(file != NULL){
		char line[1000];
		while(fgets(line, sizeof line, file)!=NULL){
			if(line[0]!='\n'){
				sleep(delay);
				//MODIFY THIS TO WORK WITH CSV FILE INSTEAD OF STDIN
				//USE THE ADDMSG FUNCTION TO ADD MSG TO A LINKED LIST
				//fprintf(stdout, "%s", line);
				char* type = strtok(line, ",");
				char* str = strtok(NULL, ",");
				char* msg = strtok(str, ",");
				addmsg(type, msg);
				if(msg[0] == 'F'){
					savelog("messages.log");
				}
			}
		}
		fclose(file);
	}
	else {
		perror(inputfile);
	}
}

void print_usage(){
	printf("Usage: Use -f to specify a filename, use -t to specify a value for delay");
}

int main(int argc, char *argv[]){
	char inputfile[20];
	int timeval;
	int opt;
	head = (struct list_struct*)malloc(sizeof(struct list_struct));

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

	if(!inputfile){
		strcpy(inputfile, "messages.txt");
	}

	readFile(inputfile, timeval);
	printf("%s", getlog());
	clearlog();
	//printList(head);
	return 0;
}
