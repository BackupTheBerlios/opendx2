//////////////////////////////////////////////////////////////////////////////
//                           DX  SOURCEFILE                                 //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/CommentStyleUser.h,v 1.1 1999/03/24 15:17:38 gda Exp $
  */


#ifndef _CommentStyleUser_h
#define _CommentStyleUser_h

#include "CommentStyle.h"

#define ClassCommentStyleUser "CommentStyleUser"

class CommentStyleUser: public CommentStyle {
  private:

    static LabelDecorator* ParsingDecorator;

  protected:

    virtual const char* getPrintableText();
    virtual void        setPrintableText(const char*);

  public:

    CommentStyleUser(){};
    ~CommentStyleUser(){};

    virtual boolean parseComment 
	(LabelDecorator* ldec, const char* comment, const char* file, int l) {
	CommentStyleUser::ParsingDecorator = ldec;
	return this->CommentStyle::parseComment(comment, file, l);
    }

    virtual boolean printComment (LabelDecorator* ldec, FILE* f) {
	CommentStyleUser::ParsingDecorator = ldec;
	return this->CommentStyle::printComment(f);
    }

    virtual const char* getKeyword() { return "user"; }

    const char* getClassName() { return ClassCommentStyleUser; }
};

#endif  // _CommentStyleUser_h

