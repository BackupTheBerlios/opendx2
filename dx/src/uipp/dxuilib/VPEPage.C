/*  Open Visualization Data Explorer Source File */


#include "VPEPage.h"
#include "EditorWindow.h"


VPEPage::VPEPage (const char* name, Widget parent, WorkSpaceInfo *info,
    EditorWindow* editor, WorkSpaceRoot* root) :
    EditorWorkSpace(name, parent, info, editor), WorkSpacePage(root)
{
}

boolean VPEPage::isA(Symbol classname)
{
    Symbol s = theSymbolManager->registerSymbol(ClassVPEPage);
    return (s == classname);
}

boolean VPEPage::isA(const char* classname)
{
    Symbol s = theSymbolManager->registerSymbol(classname);
    return this->isA(s);
}

void VPEPage::saveWorkSpaceParams(WorkSpace*)
{
    this->EditorWorkSpace::saveWorkSpaceParams(this->editor->getWorkSpace());
}
