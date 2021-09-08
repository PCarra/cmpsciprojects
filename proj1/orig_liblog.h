#include <time.h>

typedef struct data_struct {
	time_t time;
	char type[20];
	char msg[100];
} data_t;

int addmsg(const char type[], const char msg[]);
void clearlog();
char *getlog();
int savelog(char *filename);
