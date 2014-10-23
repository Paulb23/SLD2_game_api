#include "ini_reader.h"
#include "../misc/hashmap.h"
#include "../misc/logger.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

/* function prototyping */
static char *trim_whitespace(char *str);


/**************************//**
 *
 * Creates and returns a new Ini reader
 * return -1 on fail
 *
 *************************/
Ini_Reader *ini_create() {
	Ini_Reader *ini = malloc(sizeof(Ini_Reader));										/* Allocate memory */
	if (!ini) {log_write("Failed to create ini reader! "); return (Ini_Reader *) -1;}	/* if Allocation fails return */

	ini->categories = hashmap_create();				/* create the categories hashmap */
	ini_add_catorgory(ini, "default");				/* add a default category */
	return ini;										/* return */
}


/**************************//**
 *
 * Reads a ini file
 *
 * @param ini - the ini to sore into
 * @param file - the file read from
 *
 *************************/
void ini_read_file(Ini_Reader *ini, char *file) {

	  FILE *f = fopen(file, "r");								/* open the file */
	  if (!f) {log_write("Failed to open ini file! "); return;}	/* return if failed */

	  char curr_cat[256] = "default";				/* default category */
	  char *line = ";";								/* default line */

	  char buf[256];								/* buffer to read the line into */
	  while (fgets (buf, sizeof(buf), f) != NULL) {	/* Loop through the file */
		  line = buf;								/* convert to pointer for easy manipulation*/
		  line = trim_whitespace(line);				/* trim the line */
			  if (line[0] == '[') {					/* if it is a category definition*/
				  line++;							/* remove the braces surrounding it*/
				  line[strlen(line)-1] = 0;
				  strcpy(curr_cat, line);			/* update the current category */
				  ini_add_catorgory(ini, line);		/* add the category */
			  } else if (strchr(line, '=') != 0) {	/* else if it is a key + value */
				 char *key = strtok(line,"=");		/* split the line into key + value*/
				 char *val = strtok(NULL,"=");		/* add them the category */
				 ini_add_value(ini, curr_cat, key, val);
			  }
	  }
	  fclose(f);									/* close the file */
}


/**************************//**
 *
 * Adds a category to the reader
 *
 * @param ini - ini to add the category to
 * @param category - name of the category
 *
 *************************/
void ini_add_catorgory(Ini_Reader *ini, char *catorgory) {
	hashmap_set(ini->categories, catorgory, hashmap_create());
}


/**************************//**
 *
 * Adds a value to the reader
 *
 * @param ini - ini to add the category to
 * @param category - name of the category
 * @param key - name of the key
 * @param value - value to store at the key
 *
 *************************/
void ini_add_value(Ini_Reader *ini, char *catorgory, void *key, void *value) {
	Hashmap *values = hashmap_get(ini->categories, catorgory);
	if (values == (void *)-1) { log_write("Failed to find catorgory reader! "); return;}
	hashmap_set(values, key, value);
}


/**************************//**
 *
 * Gets and returns a value
 * returns -1 on fail
 *
 * @param ini - ini to add the category to
 * @param category - name of the category
 * @param key - name of the key
 *
 *************************/
void *ini_get_value(Ini_Reader *ini, char *catorgory, void *key) {
	Hashmap *values = hashmap_get(ini->categories, catorgory);
	if (values == (void *)-1) {log_write("Failed to find catorgory reader! "); return (void*)-1;}
	return hashmap_get(values, key);
}


/**************************//**
 *
 * Trims whitespace from a string
 *
 * @param str - string to trim
 *
 *************************/
static char *trim_whitespace(char *str) {
  char *end;

  while(isspace(*str)) str++;

  if(*str == 0)
    return str;

  end = str + strlen(str) - 1;
  while(end > str && isspace(*end)) end--;

  *(end+1) = 0;

  return str;
}
