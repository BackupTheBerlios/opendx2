/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>




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


