///////////////////////////////////////////////////////////////////////
//                        DX  SOURCEFILE                             //
//                                                                   //
///////////////////////////////////////////////////////////////////////

INCLUDE  objectClass.X

SUBCLASS Private OF Object
IMPLEMENTS Delete

struct private {
    struct object object;		/* object preamble */
    Pointer data;			/* pointer to user's data */
    Error (*delete)(Pointer);		/* deletion routine */
};

static Private _NewPrivate(Pointer data, Error (*delete)(Pointer),
		        struct private_class *class);
