#include "logger.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int LOGGIN = 1;
static char *file_path = "../extras/log.txt";

/**************************
 *
 *  Write to the log
 *
 *  @param text - text to write
 *
 *************************/
void log_write(char *text) {
	if (LOGGIN) {
		FILE *f = fopen(file_path, "ab");

		if (f == NULL) {
			printf("Hmmm");
			return;
		}

		time_t current_time;
		char* c_time_string;

		current_time = time(NULL);
		c_time_string = ctime(&current_time);

		fprintf(f, "%s: %s \r\n", c_time_string, text);

		fclose(f);
	}
}
