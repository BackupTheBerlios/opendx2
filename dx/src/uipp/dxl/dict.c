/*  Open Visualization Data Explorer Source File */

#include    <string.h>
#include	"../base/UIConfig.h"
#include	"../base/defines.h"
#include	"dict.h"
#if defined(MSDOS) || defined(sun4)
# include	<malloc.h>
#endif

#ifndef NULL
#define NULL 0
#endif

struct _dictitem_t {
        struct  _dictitem_t     *nexti;
        char			*key;
        void                    *def;
        void                    (*deleter)(void*);
};

#define HASH_SIZE 32

static int _dict_hash(const char *str)
{
    char c, *p = (char*)str;
    int key, i, sum = 0;

    for (i=0 ; (c = *p) && i<12 ; i++, p++)
        sum = sum + c;

    key = sum & (HASH_SIZE -1);

    return key;

}

static void DeleteDictItem(DictItem *di)
{
    if (di->deleter)
	(*di->deleter)(di->def);

    if (di->key)
	FREE(di->key);

    FREE(di);
}
static DictItem *NewDictItem(const char *key, const void *def, 
				void (*deleter)(void*))
{
    DictItem *di = (DictItem*)MALLOC(sizeof(DictItem));

    if (!di)
	return NULL;
    di->nexti = NULL;
    di->key = strdup(key);
    di->def = (void*)def;
    di->deleter = deleter;
    return di;
}

void DeleteDictionary(_Dictionary *d)
{
    int i ;
	
    for (i=0 ; i<d->size ; i++) {
	DictItem *di = d->harr[i];
	if (di) {
	    DictItem *next; 
	    do {
		next = di->nexti;
		DeleteDictItem(di);
	    } while (di == next);
	}
    }
    FREE(d->harr);
    FREE(d);
}
_Dictionary *NewDictionary()
{
 	int i;
	_Dictionary *dict;

  	dict = (_Dictionary*)MALLOC(sizeof(_Dictionary));
   	if (!dict)
	    return NULL;
	if (!(dict->harr = (DictItem**)MALLOC(HASH_SIZE*sizeof(DictItem*))))
	    return NULL;
	dict->num_in_dict = 0;
	dict->size = HASH_SIZE;
	for (i=0 ; i<HASH_SIZE; i++)
		dict->harr[i] = (DictItem*)NULL;

	return(dict);
}

DictDelete(dictionary,key)
_Dictionary	*dictionary;
const char 	*key;
{
	DictItem	*dlist,*next;
	int		found=0;
	int		bucket;
		
	bucket = _dict_hash(key); 
	if (dlist = dictionary->harr[bucket]) {
		found = !strcmp(dlist->key, key);
		if (found) {	/* First item on list */
			dictionary->harr[bucket] = dlist->nexti;
		}
		else {		/* Not first item on list */
			while (dlist->nexti && !found) {
				found = !strcmp(dlist->nexti->key,key);
				if (!found)
					dlist = dlist->nexti;
				else {
					if (next = dlist->nexti) {
						dlist->nexti = next->nexti;
					}
					else
						dlist->nexti=(DictItem*)0;
					dlist = next;
					dictionary->num_in_dict -= 1;
				}
			}
		}
		DeleteDictItem(dlist);
	}
#ifdef debug
	printf("delete: key = %d, found = %d\n",key,found);
#endif
	return(found);
}
	
DictInsert(dictionary,key,def, deleter)
_Dictionary	*dictionary;
const 		char *key;
void		*def;
void		(*deleter)(void*);
{
	DictItem	*dlist;
	int		bucket;
	
	dlist = NewDictItem(key,def,deleter);
	if (!dlist)
	    return NULL;
	bucket = _dict_hash(key);
	dlist->nexti = dictionary->harr[bucket];
	dictionary->harr[bucket] = dlist;
	dictionary->num_in_dict += 1;
	return 1;
}
	
void		*DictFind(dictionary,key)
_Dictionary	*dictionary;
const char 	*key;
{
	DictItem	*dlist;
	int		found=0;
		
	dlist = dictionary->harr[_dict_hash(key)];
	while (dlist && !found) {
		found = !strcmp(dlist->key,key);
		if (!found) 
			dlist = dlist->nexti;
		else
			return(dlist->def);
	}
	return(0);
}
