//////////////////////////////////////////////////////////////////////////////
// Field.h -							   	    //
//                                                                          //
// Definition for the Field class.				  	    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/prompter/Field.h,v 1.1 1999/04/05 13:33:43 gda Exp $
 */

#ifndef _Field_h
#define _Field_h

#include <Xm/Xm.h>
#include "../base/defines.h"
#include "../base/Base.h"

//
// Class name definition:
//
#define ClassField	"Field"


//
// Field class definition:
//				
class Field : public Base
{

  private:
    //
    // Private class data:
    //
    static boolean FieldClassInitialized;

    char	*type;
    char	*name;
    char	*structure;
    char 	*layout_skip;
    char 	*layout_width;
    char	*block_skip;
    char	*block_element;
    char	*block_width;
    char	*dependency;

  protected:


  public:

    //
    // Constructor:
    //
    Field(char *);

    //
    // Destructor:
    //
    ~Field();

    //
    // set/get the field name
    //
    void setName		(char *);
    void setType		(char *);
    void setStructure		(char *);
    void setLayoutSkip		(char *);
    void setLayoutWidth		(char *);
    void setBlockSkip		(char *);
    void setBlockElement	(char *);
    void setBlockWidth		(char *);
    void setDependency		(char *);

    //
    // set/get the field type
    //
    char *getName() 		{ return this->name; }
    char *getType()		{ return this->type; };
    char *getStructure()	{ return this->structure;};
    char *getLayoutSkip()	{ return this->layout_skip; };
    char *getLayoutWidth()	{ return this->layout_width; };
    char *getBlockSkip()	{ return this->block_skip; };
    char *getBlockElement()	{ return this->block_element; };
    char *getBlockWidth()	{ return this->block_width; };
    char *getDependency()	{ return this->dependency; };

    //
    // set/get the field structure
    //

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassField;
    }
};


#endif // _Field_h

