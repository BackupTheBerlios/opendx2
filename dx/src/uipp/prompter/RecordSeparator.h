/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>



#ifndef _RecordSeparator_h
#define _RecordSeparator_h

#include <Xm/Xm.h>
#include "../base/defines.h"
#include "../base/Base.h"

//
// Class name definition:
//
#define ClassRecordSeparator	"RecordSeparator"


//
// RecordSeparator class definition:
//				
class RecordSeparator : public Base
{

  private:
    //
    // Private class data:
    //
    static boolean RecordSeparatorClassInitialized;

    char	*type;
    char	*name;
    char	*num;

  protected:


  public:

    //
    // Constructor:
    //
    RecordSeparator(char *);

    //
    // Destructor:
    //
    ~RecordSeparator();

    //
    // set/get the record separator info 
    //
    void setType		(char *);
    void setName		(char *);
    void setNum		        (char *);

    char *getName() 		{ return this->name; }
    char *getType()		{ return this->type; };
    char *getNum()	        { return this->num;};

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassRecordSeparator;
    }
};


#endif // _RecordSeparator_h

