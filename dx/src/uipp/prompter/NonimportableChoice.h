/*  Open Visualization Data Explorer Source File */

#ifndef _NON_IMP_CHOICE_H
#define _NON_IMP_CHOICE_H

#include "TypeChoice.h"

#define ClassNonimportableChoice "NonimportableChoice"

class ButtonInterface;
class NonimportableChoice;

class NonimportableChoice : public TypeChoice {
    private:

    protected:

	static String	DefaultResources[];

	virtual void	setAttachments(ButtonInterface**, int, Widget);

	NonimportableChoice (
	    const char*		name,
	    boolean		browsable,
	    boolean		testable,
	    boolean		visualizable,
	    boolean		prompterable,
	    GARChooserWindow*	gcw,
	    Symbol		sym
	) : TypeChoice (name, browsable, testable, visualizable, prompterable, gcw, sym)
	{}

    public:

	~NonimportableChoice(){}

	virtual int		getMinWidth() 
	    { return (VERTICAL_LAYOUT?440:675) ;}

	const char *	getClassName() {
	    return ClassNonimportableChoice;
	}

};

#endif  // _NON_IMP_CHOICE_H
