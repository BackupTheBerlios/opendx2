/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>



#include "RecordSeparator.h"
#include "../base/Strings.h"

boolean RecordSeparator::RecordSeparatorClassInitialized = FALSE;


RecordSeparator::RecordSeparator(char* name) : Base()
{
    //
    // Initialize member data.
    //

    this->name = DuplicateString(name); 
    this->type = DuplicateString("# of bytes");
    this->type = DuplicateString("");
    this->num  = DuplicateString("");
}

void RecordSeparator::setType(char *type)
{
    if(this->type)
        delete this->type;
    this->type = DuplicateString(type);
}
void RecordSeparator::setName(char *name)
{
    if(this->name)
        delete this->name;
    this->name = DuplicateString(name);
}
void RecordSeparator::setNum(char *num)
{
    if(this->num)
        delete this->num;
    this->num = DuplicateString(num);
}

RecordSeparator::~RecordSeparator()
{
    if(this->type)
	delete this->type;
    if(this->name)
	delete this->name;
    if(this->num)
	delete this->num;
}
