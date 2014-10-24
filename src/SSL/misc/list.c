#include "list.h"
#include "SSL_Logger.h"
#include <stdlib.h>

/**************************//**
 *
 * Creates a List an returns it
 * If it fails to create return -1
 *
 *************************/
List *list_create() {
	List *list = malloc(sizeof(List));	/* allocate memory */
	list->next = 0;						/* point to empty */

	return (list) ? list : (List *)0;	/* return list */
}


/**************************//**
 *
 * Adds a value to the list
 *
 * @param list - list to add to
 * @param data - data to add
 *
 *************************/
void list_set(List *list, void *data) {
	List *tmp = malloc(sizeof(List));					/* allocate memory */
	if (!tmp) {SSL_Log_Write("Failed to allocate memory for List! "); return;}

	tmp->data = data;									/* fill in the data */
	tmp->next = 0;

	List *curr = list;									/* loop until we hit the end of the list */
	while (curr->next != 0) {
		curr = curr->next;
	}
	curr->next = tmp;									/* else finally we can set the last next to point to the new element */
}


/**************************//**
 *
 * Gets a value from the List
 * returns -1 if key is not found
 *
 * @param list - List to search
 * @param data - data to look for
 *
 *************************/
void *list_get(List *list, int pos) {
	List *curr = list;						/* tmp pointer used to loop */
	int i = 0;
	while (i < pos && curr->next != 0) {	/* loop until we find the pos */
		curr = curr->next;
		i++;
	}

	return (i == pos) ? curr->data : (void *)-1;	/* return */
}


/**************************//**
 *
 * Removes a key from the List
 *
 *@param list - List with the key to remove
 *@param data - data to remove
 *
 *************************/
void list_remove(List *list, void *data) {
	List *pre;											/* Previous and next pointer to loop through the list */
	List *curr = list;

	while(curr->data != data && curr->next != 0) {			/* loop until the end or we find the data */
		pre = curr;
		curr = curr->next;
	}
	if (curr->data != data) {								/* if it does not equal the key we have reached the end */
		return;
	}

	pre->next = curr->next;									/* else adjust the pointers and return */
	free(curr);
}

/**************************//**
 *
 * Destroys the List
 *
 *@param list - List to destroy
 *
 *************************/
void list_destroy(List *list) {
	free(list);
}
