#ifndef LIST_H_
#define LIST_H_

/* List struct */
typedef struct _List {
	void *data;				/* data in the element */
	struct _List *next;		/* next element */
} List;


/* function prototypes */
List *list_create();
void list_set(List *list, void *data);
void *list_get(List *list, int pos);
void list_remove(List *list, void *data);
void list_destroy(List *list);

#endif /* LIST_H_ */
