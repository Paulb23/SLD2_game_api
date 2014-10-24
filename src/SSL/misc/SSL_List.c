/*-------------------------------------------------------------------------*/
/**
   @file    SSL_List.c
   @author  P. Batty
   @brief   Implements a list collection object.

   This module implements a simple list object, a structure containing a
   and data, and a next pointer.
*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "SSL_List.h"
#include "SSL_Logger.h"

#include <stdlib.h>

/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief    Creates a new SSL_List object.
  @return Pointer to a SSL_List object on successful creation otherwise 0.

  Creates a new SSL_List object with allocated memory destroy with
  SSL_List_Destroy.

  If it cannot create the object it will return 0.

\-----------------------------------------------------------------------------*/
SSL_List *SSL_List_Create() {

	/* allocate memory */
	SSL_List *list = malloc(sizeof(SSL_List));

	/* point to empty */
	list->next = 0;

	/* return list */
	return (list) ? list : (SSL_List *)0;
}


/*!--------------------------------------------------------------------------
  @brief    Adds a element to the list
  @param    list		  The list to add the data to
  @param    data		  The data to add
  @return   void

  Adds the data passed in to the end of the list

\-----------------------------------------------------------------------------*/
void SSL_List_Add(SSL_List *list, void *data) {

	/* allocate memory */
	SSL_List *tmp = malloc(sizeof(SSL_List));

	/* if allocation failed return */
	if (!tmp) {
		SSL_Log_Write("Failed to allocate memory for List! ");
		return;
	}

	/* else fill in the data */
	tmp->data = data;
	tmp->next = 0;

	/* loop until we hit the end of the list */
	SSL_List *curr = list;
	while (curr->next != 0) {
		curr = curr->next;
	}

	/* finally we can set the last next to point to the new element */
	curr->next = tmp;
}


/*!--------------------------------------------------------------------------
  @brief    Adds a element to the list
  @param    list		  The list to get the data from
  @param    pos		  Position in the list to get the data
  @return   the data stored at that location else -1

  Returns the data at the given location. NOTE: DOES NOTE CAST TO A TYPE.

\-----------------------------------------------------------------------------*/
void *SSL_List_Get(SSL_List *list, int pos) {

	/* tmp pointer used to loop */
	SSL_List *curr = list;

	/* loop until we find the pos */
	int i = 0;
	while (i < pos && curr->next != 0) {
		curr = curr->next;
		i++;
	}

	/* return */

	return (i == pos) ? curr->data : (void *)-1;
}


/*!--------------------------------------------------------------------------
  @brief    Removes a element to the list
  @param    list		  The list to get the data from
  @param    data		  The data to remove
  @return   void

  Removes the data from the list.

\-----------------------------------------------------------------------------*/
void SSL_List_Remove(SSL_List *list, void *data) {

	/* Previous and next pointer to loop through the list */
	SSL_List *pre;
	SSL_List *curr = list;

	/* loop until the end or we find the data */
	while(curr->data != data && curr->next != 0) {
		pre = curr;
		curr = curr->next;
	}

	/* if it does not equal the key we have reached the end */
	if (curr->data != data) {
		return;
	}

	/* else adjust the pointers and return */
	pre->next = curr->next;
	free(curr);
}

/*!--------------------------------------------------------------------------
  @brief    Destroys the list
  @return   void

  Destroys the list.

\-----------------------------------------------------------------------------*/
void SSL_List_Destroy(SSL_List *list) {

	/* free the memory */
	free(list);
}
