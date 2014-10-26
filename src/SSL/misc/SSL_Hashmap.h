/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Hashmap.h
   @author  P. Batty
   @brief   Implements a simple hashmap structure

   This module implements a simple hashmap structure, a structure containing a
   key, data and a next element pointer.
*/
/*--------------------------------------------------------------------------*/

#ifndef HASHMAP_H_
#define HASHMAP_H_


/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief    SSL_Hashmap

  This object contains a unique key, data tied to the key and a next pointer
  to the next element in the map.

\----------------------------------------------------------------------------*/
typedef struct _SSL_Hashmap_ {
	void *key;					/**< unique key */
	void *value;				/**< value tied to the key */
	struct _SSL_Hashmap_ *next; /**< next element in the SSL_Hashmap */
} SSL_Hashmap;


/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief    Creates a new SSL_Hashmap object.
  @return Pointer to a SSL_Hashmap object on successful creation otherwise 0.

  Creates a new SSL_Hashmap object with allocated memory destroy with
  SSL_Hashmap_Destroy.

  If it cannot create the object it will return 0.

\-----------------------------------------------------------------------------*/
SSL_Hashmap *SSL_Hashmap_Create();


/*!--------------------------------------------------------------------------
  @brief    Adds a element to the SSL_Hashmap
  @param    map		  The SSL_Hashmap to add the data to
  @param    key		  The key to add the data to
  @param    value		  The value to tie to the key
  @return   void

  Adds the data passed in to the key inside the SSL_Hashmap

\-----------------------------------------------------------------------------*/
void SSL_Hashmap_Add(SSL_Hashmap *map, void *key, void *value);


/*!--------------------------------------------------------------------------
  @brief    Gets a element in the list
  @param    map		  The SSL_Hashmap to get the data from
  @param    key		  The key to search for
  @return   the value stored at that location else -1

  Returns the value at the given location. NOTE: DOES NOTE CAST TO A TYPE.

\-----------------------------------------------------------------------------*/
void *SSL_Hashmap_Get(SSL_Hashmap *map, void *key);


/*!--------------------------------------------------------------------------
  @brief    Removes a element in the list
  @param    map		  The SSL_Hashmap to remove the data from
  @param    key		  The key to search for
  @return   void

  remove the value in the SSL_Hashmap.

\-----------------------------------------------------------------------------*/
void SSL_Hashmap_Remove(SSL_Hashmap *map, void *key);


/*!--------------------------------------------------------------------------
  @brief    Destroys the SSL_Hashmap
  @param    map		  The SSL_Hashmap to destroy
  @return   void

  Destroys the SSL_Hashmap.

\-----------------------------------------------------------------------------*/
void SSL_Hashmap_Destroy(SSL_Hashmap *map);

#endif /* HASHMAP_H_ */
