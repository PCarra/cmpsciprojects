#include <time.h>

typedef struct data_struct {
	time_t time;
	char type;
	char *msg;
} data_t;

int addmsg(const char type, const char *msg);
void clearlog();
char *getlog();
int savelog(char *filename);

int addmsg(const char type, const char *msg){
	return 0;
}

void clearlog(){
}

char *getlog(){
	return NULL;
}

int savelog(char *filename){
	return 0;
}
