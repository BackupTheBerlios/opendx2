/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>





#include "defines.h"
#include "Arc.h"
#include "ArcStandIn.h"
#include "Node.h"
#include "StandIn.h"



Arc::Arc(Node *fromNode, int fp, Node *toNode, int tp)
{
        this->arcStandIn = NULL;

        this->from = fromNode;
        this->fromParameter = fp;
        this->to = toNode;
        this->toParameter = tp;
        this->from->addOutputArc(this,fp);
        this->to->addInputArc(this,tp);
}

Arc::~Arc()
{
     Node*      sourceNode;
     Node*      destNode;
     StandIn*   srcStandIn;
     StandIn*   destStandIn;
     int        sourceIndex, destIndex;

     sourceNode = this->getSourceNode(sourceIndex);
     destNode   = this->getDestinationNode(destIndex);

     // 
     // remove the arc from the approiate lists.
     //
     this->to->deleteArc(this);

     //
     // If a standIn exists update the UI.
     //
     if (this->arcStandIn != NULL) {
         delete this->arcStandIn;
         srcStandIn = sourceNode->getStandIn();
	 if (srcStandIn)
             srcStandIn->drawTab(sourceIndex, True);
         destStandIn = destNode->getStandIn();
	 if (destStandIn)
             destStandIn->drawTab(destIndex, False);
     }

    
}


