/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>



#define NO_TEXT_SYMBOL "<NULL>"
#include "CommentStyleUser.h"
#include "LabelDecorator.h"

LabelDecorator* CommentStyleUser::ParsingDecorator = NUL(LabelDecorator*);

const char* CommentStyleUser::getPrintableText()
{
    //
    // It seems right to ASSERT here, but there was a situation in which the
    // ui was so hosed, that it crashed and came here from 
    // DXApplication::emergencySave and found ParsingDecorator==NULL.  The result
    // was a loop in which a large number of net files was produced in /tmp.
    //ASSERT(CommentStyleUser::ParsingDecorator);
    if (CommentStyleUser::ParsingDecorator == NUL(LabelDecorator*)) return NUL(char*);
    return CommentStyleUser::ParsingDecorator->getLabelValue();
}

void CommentStyleUser::setPrintableText(const char *value)
{
    //
    // It seems right to ASSERT here, but there was a situation in which the
    // ui was so hosed, that it crashed and came here from 
    // DXApplication::emergencySave and found ParsingDecorator==NULL.  The result
    // was a loop in which a large number of net files was produced in /tmp.
    //ASSERT(CommentStyleUser::ParsingDecorator);
    if (CommentStyleUser::ParsingDecorator == NUL(LabelDecorator*)) return ;
    CommentStyleUser::ParsingDecorator->setLabel(value);
}

