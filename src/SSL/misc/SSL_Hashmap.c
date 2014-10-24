/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Hashmap.c
   @author  P. Batty
   @brief   Implements a simple hashmap structure

   This module implements a simple hashmap structure, a structure containing a
   key, data and a next element pointer.
*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "SSL_Hashmap.h"
#include "SSL_Logger.h"

#include <stdlib.h>


/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
|  @brief    Creates a new SSL_Hashmap object.
|  @return Pointer to a SSL_Hashmap object on successful creation otherwise 0.
|
|  Creates a new SSL_Hashmap object with allocated memory destroy with
|  SSL_Hashmap_Destroy.
|
|  If it cannot create the object it will return 0.
|
\-----------------------------------------------------------------------------*/
SSL_Hashmap *SSL_Hashmap_Create() {

	/* allocate memory */
	SSL_Hashmap *map = malloc(sizeof(SSL_Hashmap));

	/* point to empty */
	map->next = 0;

	/* return hashmap */
	return (map) ? map : (SSL_Hashmap *)0;
}


/*!--------------------------------------------------------------------------
|  @brief    Adds a element to the SSL_Hashmap
|  @param    map		  The SSL_Hashmap to add the data to
|  @param    key		  The key to add the data to
|  @param    value		  The value to tie to the key
|  @return   void
|
|  Adds the data passed in to the key inside the SSL_Hashmap
|
\-----------------------------------------------------------------------------*/
void SSL_Hashmap_Add(SSL_Hashmap *map, void *key, void *value) {

	/* allocate memory */
	SSL_Hashmap *tmp = malloc(sizeof(SSL_Hashmap));

	/* return if failed allocation */
	if (!tmp) {
		SSL_Log_Write("Failed to allocate memory for hashmap! ");
		return;
	}

	/* fill in the data */
	tmp->key = key;
	tmp->value = value;
	tmp->next = 0;

	/* loop until we hit the end of the map */
	/* or we find the key already exists    */
	SSL_Hashmap *curr = map;
	while (curr->next != 0) {
		if (curr->key == key) {
			curr->value = value;
			return;
		}
		curr = curr->next;
	}

	/* check the last element isn't the key */
	if (curr->key == key) {
		curr->value = value;
		return;
	}

	/* finally we can set the last next to point to the new element */
	curr->next = tmp;
}


/*!--------------------------------------------------------------------------
|  @brief    Gets a element in the list
|  @param    map		  The SSL_Hashmap to get the data from
|  @param    key		  The key to search for
|  @return   the value stored at that location else -1
|
|  Returns the value at the given location. NOTE: DOES NOTE CAST TO A TYPE.
|
\-----------------------------------------------------------------------------*/
void *SSL_Hashmap_Get(SSL_Hashmap *map, void *key) {

	/* tmp pointer used to loop */
	SSL_Hashmap *curr = map;

	/* loop until we find the key */
	while (curr->key != key && curr->next != 0) {
		curr = curr->next;
	}

	/* return */
	return (curr->key == key) ? curr->value : (void *)-1;
}


/*!--------------------------------------------------------------------------
|  @brief    Removes a element in the list
|  @param    map		  The SSL_Hashmap to remove the data from
|  @param    key		  The key to search for
|  @return   void
|
|  remove the value in the SSL_Hashmap.
|
\-----------------------------------------------------------------------------*/
void hashmap_remove(SSL_Hashmap *map, void *key) {

	/* Previous and next pointer to loop through the map */
	SSL_Hashmap *pre;
	SSL_Hashmap *curr = map;

	/* loop until the end or we find the key */
	while(curr->key != key && curr->next != 0) {
		pre = curr;
		curr = curr->next;
	}

	/* if it does not equal the key we have reached the end */
	if (curr->key != key) {
		return;
	}

	/* else adjust the pointers and return */
	pre->next = curr->next;
	free(curr);
}


/*!--------------------------------------------------------------------------
|  @brief    Destroys the SSL_Hashmap
|  @param    map		  The SSL_Hashmap to destroy
|  @return   void
|
|  Destroys the SSL_Hashmap.
|
\-----------------------------------------------------------------------------*/
void hashmap_destroy(SSL_Hashmap *map) {

	/* Previous and next pointer to loop through the map */
	SSL_Hashmap *pre;
	SSL_Hashmap *curr = map;

	/* loop through and free everything */
	while(curr->next != 0) {
		free(pre);
		pre = curr;
		curr = curr->next;
	}

	free(pre);
	free(curr);
}
