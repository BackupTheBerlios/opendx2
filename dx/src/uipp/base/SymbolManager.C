//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/SymbolManager.C,v 1.1 1999/03/24 15:17:24 gda Exp $
 */


#include "SymbolManager.h"


SymbolManager* theSymbolManager = new SymbolManager;


Symbol SymbolManager::registerSymbol(const char* symbolString)
{
    Symbol symbol;

    symbol = 0;
    if (NOT this->StringTable::addString(symbolString, symbol))
    {
	symbol = this->StringTable::findString(symbolString);
    }

    return symbol;
}


