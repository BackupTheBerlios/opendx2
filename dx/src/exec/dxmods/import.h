/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>



/* 
 * input parameter list which each function must accept:
 *
 *  the parms are:
 *    pointer to the filename
 *    null terminated string list of fields to import
 *    pointer to the format string
 *    optionally, start, end and deltas for series objects
 */

struct parmlist {
    char *filename;
    char **fieldlist;
    char *format;
    int *startframe;
    int *endframe;
    int *deltaframe;
};


/* data-format file search returns */
typedef enum
{
    IMPORT_STAT_FOUND,
    IMPORT_STAT_NOT_FOUND,
    IMPORT_STAT_ERROR
} ImportStatReturn;

/* 
 * table of entry points for each format.
 *
 *  for each type of file to be imported, three things must be supplied:
 *   a function to determine if this is a valid file of this type
 *   a function to actually import the data and return it
 *   a list of format strings which indicate this type of file
 * 
 *  if the autotype function is null, the extension must be given for import
 *   to process this type of file.
 *
 */
struct import_table {
    ImportStatReturn (*autotype)(struct parmlist *);
    Object (*readin)(struct parmlist *);
    char *formatlist[10];
};

/* the actual table */
extern struct import_table _dxdImportTable[];


/*
 * useful utility routines for dealing with binary data and machines
 * with conflicting byte orders.
 */

/* these use the (destination, source, ... ) parm order */
#define SWAB(x,y,z)  _dxfByteSwap((void *)x, (void*)y, (int)(z)/2, TYPE_SHORT)
#define SWAW(x,y,z)  _dxfByteSwap((void *)x, (void*)y, (int)(z)/4, TYPE_INT)
#define SWAD(x,y,z)  _dxfByteSwap((void *)x, (void*)y, (int)(z)/8, TYPE_DOUBLE)

/* Byte order */
typedef enum {
    BO_UNKNOWN = 1,
    BO_MSB = 2,
    BO_LSB = 3
} ByteOrder;

extern Error     _dxfByteSwap(void *, void*, int, Type);
extern ByteOrder _dxfLocalByteOrder(void);

#define LOCAL_BYTEORDER   _dxfLocalByteOrder()
