#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int LOGGIN = 0;
static char *file_path = "../../extras/log.txt";

void log_write(char *text) {
	FILE *f = fopen(file_path, "a");

	time_t current_time;
	char* c_time_string;

	current_time = time(NULL);
	c_time_string = ctime(&current_time);

	fprintf(f, "%s: %s \n", c_time_string, text);

	fclose(f);
}
