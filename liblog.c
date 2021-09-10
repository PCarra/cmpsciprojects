#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


typedef struct data_struct {
	time_t time;
	char type[2];
	char msg[100];
} data_t;

typedef struct list_struct {
        data_t data;
        struct list_struct* next;
} list_t;

struct tm* get_time(){
        time_t tm;
        struct tm * tp = localtime(&tm);
        return tp;
}

//struct list_struct *head = (struct list_struct*)malloc(sizeof(struct list_struct));
struct list_struct *head = NULL;

char* get_time_str(time_t rawtime){
        struct tm * timeinfo;
        timeinfo = localtime(&rawtime);
        char* time_str = asctime(timeinfo);
        time_str[strlen(time_str) - 1] = '\0';
        return time_str;
}

//appends to its internal list structure a node containing a copy of data
int addmsg(char* type, char* msg){
        int nodesize;
       	nodesize = sizeof(struct list_struct) + strlen(msg) + strlen(type) + 1;
       	struct list_struct* newnode = (struct list_struct*)malloc(nodesize);
       	//calculate timestamp
       	time_t rawtime = time(&rawtime);
       	newnode->data.time = rawtime;
       	strcpy(newnode->data.type, type);
       	strcpy(newnode->data.msg, msg);
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
	fclose(fopen("messages.log", "w"));
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
	//printf("saving log");
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
	printf("%s", getlog());
        return 0;
}



//read messages from msg file and call addmsg to add messages to log list(struct_list)
void readFile(char inputfile[], int timeval){
	head = (struct list_struct*)malloc(sizeof(struct list_struct));
        FILE *file = fopen(inputfile, "r");
        //int delay = timeval*2;
	int delay = rand() % (2*timeval + 1 -0);
        if(file != NULL){
                char line[1000];
                while(fgets(line, sizeof line, file)!=NULL){
                        if(line[0]!='\n'){
                                sleep(delay);
                                char* type = strtok(line, ",");
                                char* str = strtok(NULL, ",");
                                char* msg = strtok(str, ",");
				if(strcmp(type, "I")==0 || strcmp(type, "W")==0 || strcmp(type, "E")==0 || strcmp(type, "F")==0){
                               		if(strcmp(type, "F")==0){
        	                       		addmsg(type, msg);
                                       		savelog("messages.log");
						exit(0);
                               		}
					addmsg(type, msg);
				}
				else{
					perror("Invalid message type given skipping messagen");
					exit(1);
				}
                        }
                }
                fclose(file);
        }
        else {
                perror("Error opening file for read operation");
        }
}
