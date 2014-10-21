#include "ini_reader.h"
#include "../misc/hashmap.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

char *trim_whitespace(char *str);

Ini_Reader *ini_create() {
	Ini_Reader *ini = malloc(sizeof(Ini_Reader));
	if (!ini) return (Ini_Reader *) -1;
	ini->catogories = hashmap_create();
	ini_add_catorgory(ini, "default");
	return ini;
}

void ini_read_file(Ini_Reader *ini, char *file) {

	  FILE *f = fopen(file, "r");
	  if (!f) return;

	  char curr_cat[256] = "default";
	  char *line = ";";

	  char buf[256];
	  while (fgets (buf, sizeof(buf), f) != NULL) {
		  line = buf;
		 // line = trim_whitespace(line);
			  if (line[0] == '[') {
				  line++;
				  line[strlen(line)-1] = 0;
				  strcpy(curr_cat, line);
				  ini_add_catorgory(ini, line);
			  } else if (strchr(line, '=') != 0) {
				 char *key = strtok(line,"=");
				 char *val = strtok(NULL,"=");
				 ini_add_value(ini, curr_cat, key, val);
			  }
	  }
	  fclose(f);
}

void ini_add_catorgory(Ini_Reader *ini, char *catorgory) {
	hashmap_set(ini->catogories, catorgory, hashmap_create());
}

void ini_add_value(Ini_Reader *ini, char *catorgory, void *key, void *value) {
	Hashmap *values = hashmap_get(ini->catogories, catorgory);
	if (values == (void *)-1) return;
	hashmap_set(values, key, value);
}

void *ini_get_value(Ini_Reader *ini, char *catorgory, void *key) {
	Hashmap *curr = ini->catogories;
	while (curr->next) {
		printf(" Key: %s \n", (char *)curr->key);
		Hashmap *val =  curr->value;
		while (val->next) {
			printf(" Val: %s %s \n", (char *)val->key, (char *)val->value);
			val = val->next;
		}
		curr = curr->next;
	}
	printf("\n");

	Hashmap *values = hashmap_get(ini->catogories, catorgory);
	if (values == (void *)-1) return (void*)-1;
	return hashmap_get(values, key);
}

char *trim_whitespace(char *str) {
  char *end;

  while(isspace(*str)) str++;

  if(*str == 0)
    return str;

  end = str + strlen(str) - 1;
  while(end > str && isspace(*end)) end--;

  *(end+1) = 0;

  return str;
}
