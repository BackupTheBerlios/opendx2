/*  Open Visualization Data Explorer Source File */

#ifndef _NetCDF_CHOICE_H
#define _NetCDF_CHOICE_H

#include "ImportableChoice.h"
#include "SymbolManager.h"

#define ClassNetCDFChoice "NetCDFChoice"

class NetCDFChoice : public ImportableChoice {
    private:
	static boolean	ClassInitialized;

    protected:

	static String	DefaultResources[];

    public:

	NetCDFChoice (GARChooserWindow* gcw, Symbol sym) : ImportableChoice (
	    "netCDFData", FALSE, TRUE, TRUE, FALSE, gcw, sym) {};
	static NetCDFChoice* NetCDFChoice::Allocator(GARChooserWindow* gcw, Symbol sym)
	    { return new NetCDFChoice(gcw, sym); }
	~NetCDFChoice(){};

	virtual void		initialize();
	virtual const char*	getFormalName() { return "NetCDF format file"; }
	virtual const char*	getInformalName() { return "NetCDF"; }
	virtual const char*	getFileExtension() { return ".nc"; }
	virtual const char*	getImportType() { return "netCDF"; }

	const char *	getClassName() {
	    return ClassNetCDFChoice;
	}

};

#endif  // _NetCDF_CHOICE_H

