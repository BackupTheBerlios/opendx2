//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/GroupStyle.C,v 1.1 1999/03/24 15:17:40 gda Exp $
 */

#include "Network.h"
#include "PageGroupManager.h"
#include "ProcessGroupManager.h"
#include "AnnotationGroupManager.h"

Dictionary* BuildTheGroupManagerDictionary(Network* net)
{
GroupManager *gmgr;
Dictionary* groupManagers = new Dictionary;

    boolean isMacro = net->isMacro();
    if ((!isMacro) || (ProcessGroupManager::SupportsMacros())) {
	gmgr = new ProcessGroupManager(net);
	groupManagers->addDefinition (gmgr->getManagerName(), gmgr);
    }

    if ((!isMacro) || (PageGroupManager::SupportsMacros())) {
	gmgr = new PageGroupManager(net);
	groupManagers->addDefinition (gmgr->getManagerName(), gmgr);
    }

    if ((!isMacro) || (AnnotationGroupManager::SupportsMacros())) {
	gmgr = new AnnotationGroupManager(net);
	groupManagers->addDefinition (gmgr->getManagerName(), gmgr);
    }
    return groupManagers;
}
