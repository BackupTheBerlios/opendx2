///////////////////////////////////////////////////////////////////////
//                        DX  SOURCEFILE                             //
//                                                                   //
///////////////////////////////////////////////////////////////////////


/*
\section{String class}
*/

INCLUDE  objectClass.X

SUBCLASS String OF Object
IMPLEMENTS Delete Copy

#define IMBEDDED 12			/* strings shorter than this are */
					/* imbedded in object header */
    					/* if struct object changes, this */
    					/* must be changed to match */
struct string {
    struct object object;		/* object preamble */
    char *string;			/* pointer to the string itself */
    char shortstr[IMBEDDED];		/* short strings are stored here */
};

