//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/LocalAttributes.h,v 1.1 1999/03/24 15:17:43 gda Exp $
 */


#ifndef _LocalAttributes_h
#define _LocalAttributes_h


#include "defines.h"
#include "Base.h"


//
// Class name definition:
//
#define ClassLocalAttributes	"LocalAttributes"


//
// Describes local attributes for a component of a scalar 
// Currently, we only support a local delta value.
//
class LocalAttributes : public Base {
    friend InteractorNode;
    friend class ScalarNode;
    friend class ScalarInstance;
    friend class ScalarListInstance;


  private:

  protected:

    boolean integerTyped;	 
    boolean usingLocalDelta;	// Are we using the local delta value 
    double  currentValue; 
    double  delta; 

    void setValue(double val)   { this->currentValue = val; }

    void useLocalDelta(double delta) 
	    { this->usingLocalDelta = TRUE; this->setDelta(delta); }

    void setDelta(double delta) { this->delta = delta; }

    void clrLocalDelta() 	{ this->usingLocalDelta = FALSE; } 

  public:
    LocalAttributes(boolean isInteger) 
		{  
		    this->integerTyped = isInteger;
		    this->delta = 1.00; 
		    this->currentValue = 0.0;
		    this->usingLocalDelta = FALSE; 
		}
	
    ~LocalAttributes() { } 


    boolean isLocalDelta() { return usingLocalDelta; }

#define ROUND(x) \
        ( (double) ((x > 0.0) ? (int)(x + .5) : (int)(x - .5) ) )

    double getValue()
           { return (this->integerTyped ? 
                        ROUND(this->currentValue) : this->currentValue); }

    double getDelta() 
           { return (this->integerTyped ? 
                        ROUND(this->delta) : this->delta); }
#undef ROUND

    const char *getClassName() 
	{ return ClassLocalAttributes; }

};

#endif // _LocalAttributes_h

