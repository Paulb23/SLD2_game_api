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
  @brief    Creates a new SSL_Hashmap object.
  @return Pointer to a SSL_Hashmap object on successful creation otherwise 0.

  Creates a new SSL_Hashmap object with allocated memory destroy with
  SSL_Hashmap_Destroy.

  If it cannot create the object it will return 0.

\-----------------------------------------------------------------------------*/
SSL_Hashmap *SSL_Hashmap_Create() {

	/* allocate memory */
	SSL_Hashmap *map = malloc(sizeof(SSL_Hashmap));

	/* Check we allocated memory */
	if (!map) {
		SSL_Log_Write("Failed to allocate memory for new Hashmap!");
		free(map);
		return 0;
	}

	/* point to empty */
	map->key = NULL;
	map->value = NULL;
	map->next = 0;

	/* return hashmap */
	return map;
}


/*!--------------------------------------------------------------------------
  @brief    Adds a element to the SSL_Hashmap
  @param    map		  The SSL_Hashmap to add the data to
  @param    key		  The key to add the data to
  @param    value		  The value to tie to the key
  @return   void

  Adds the data passed in to the key inside the SSL_Hashmap

\-----------------------------------------------------------------------------*/
void SSL_Hashmap_Add(SSL_Hashmap *map, void *key, void *value) {

	/* if the first element is empty */
	/* fill in the values and return */
	if (map->key == NULL) {
		map->key = key;
		map->value = value;
		return;
	}

	/* allocate memory */
	SSL_Hashmap *tmp = malloc(sizeof(SSL_Hashmap));

	/* return if failed allocation */
	if (!tmp) {
		SSL_Log_Write("Failed to allocate memory for new hashmap element! ");
		free(tmp);
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
  @brief    Gets a element in the hashmap
  @param    map		  The SSL_Hashmap to get the data from
  @param    key		  The key to search for
  @return   the value stored at that location else -1

  Returns the value at the given location. NOTE: DOES NOTE CAST TO A TYPE.

\-----------------------------------------------------------------------------*/
void *SSL_Hashmap_Get(SSL_Hashmap *map, void *key) {

	/* if it is in the first element */
	if (map->key == key) {
		return map->value;
	}

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
  @brief    Gets a string element in the hashmap
  @param    map		  The SSL_Hashmap to get the data from
  @param    key		  The key to search for
  @return   the value stored at that location else -1

  Returns the data at the given location. as a string.

\-----------------------------------------------------------------------------*/
char *SSL_Hashmap_Get_String(SSL_Hashmap *map,  void *key) {
	return (char *)SSL_Hashmap_Get(map, key);
}

/*!--------------------------------------------------------------------------
  @brief    Gets a int element in the hashmap
  @param    map		  The SSL_Hashmap to get the data from
  @param    key		  The key to search for
  @return   the value stored at that location else -1

  Returns the data at the given location. as a int.

\-----------------------------------------------------------------------------*/
int SSL_Hashmap_Get_Int(SSL_Hashmap *map,  void *key) {
	return atoi(SSL_Hashmap_Get(map, key));
}

/*!--------------------------------------------------------------------------
  @brief    Gets a float element in the hashmap
  @param    map		  The SSL_Hashmap to get the data from
  @param    key		  The key to search for
  @return   the value stored at that location else -1

  Returns the data at the given location. as a float.

\-----------------------------------------------------------------------------*/
float SSL_Hashmap_Get_Float(SSL_Hashmap *map,  void *key) {
	return atof(SSL_Hashmap_Get(map, key));
}


/*!--------------------------------------------------------------------------
  @brief    Gets the size of the hashmap.
  @param    list		  The hashmap to get the size of.
  @return   the size of the hashmap.

  Returns the size or amount of elements in the hashmap.

\-----------------------------------------------------------------------------*/
int SSL_Hashmap_Size(SSL_Hashmap *map) {
	int size = 0;

	/* loop until we reach the end */
	SSL_Hashmap *curr = map;
	while (curr->next != 0) {
		size++;
		curr = curr->next;
	}

	/* return the size */
	return size;
}


/*!--------------------------------------------------------------------------
  @brief    Removes a element in the hashmap
  @param    map		  The SSL_Hashmap to remove the data from
  @param    key		  The key to search for
  @return   void

  remove the value in the SSL_Hashmap.

\-----------------------------------------------------------------------------*/
void SSL_Hashmap_Remove(SSL_Hashmap *map, void *key) {

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
  @brief    Destroys the SSL_Hashmap
  @param    map		  The SSL_Hashmap to destroy
  @return   void

  Destroys the SSL_Hashmap.

\-----------------------------------------------------------------------------*/
void SSL_Hashmap_Destroy(SSL_Hashmap *map) {

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
