/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

#ifndef	__EX_DICTIONARY_H
#define	__EX_DICTIONARY_H

#include <dx/dx.h>

#include "exobject.h"

typedef struct _EXDictionary		*EXDictionary;

extern EXDictionary	_dxf_ExDictionaryCreate(int size, int local, int locking);
extern EXDictionary	_dxf_ExDictionaryCreateSorted(int size, int local, int locking);
extern Error		_dxf_ExDictionaryDestroy(EXDictionary d);
extern int  		_dxf_ExDictionaryCompact(EXDictionary d);
extern Error		_dxf_ExDictionaryDelete(EXDictionary d, Pointer key);
extern Error		_dxf_ExDictionaryInsert(EXDictionary d, char *key, EXObj obj);
extern int		_dxf_ExDictionaryPurge(EXDictionary d);
extern EXObj		_dxf_ExDictionarySearch(EXDictionary d, char *key);
extern Error		_dxf_ExDictionaryBeginIterate(EXDictionary d);
extern EXObj		_dxf_ExDictionaryIterate(EXDictionary d, char **key);
extern Error		_dxf_ExDictionaryEndIterate(EXDictionary d);
extern int              _dxf_ExDictionaryIterateMany(EXDictionary d, char **key, EXObj *obj, int n);
extern int		_dxf_ExIsDictionarySorted(EXDictionary d);
extern Error 		_dxf_ExDictionaryBeginIterateSorted(EXDictionary d, int reverse);
extern EXObj 		_dxf_ExDictionaryIterateSorted(EXDictionary d, char **key);
extern int              _dxf_ExDictionaryIterateSortedMany(EXDictionary d, char **key, EXObj *obj, int n);

#endif /* __EX_DICTIONARY_H */
