using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;

namespace WinDX.UI
{
    public delegate void DeferrableActionFunction(Network staticData, Node requestData);

    public class DeferrableAction
    {
        private bool required;
        private int deferrals;
        private DeferrableActionFunction actionFunction;
        private Network staticData;

        protected void setActionRequired() { required = true; }

        public DeferrableAction(DeferrableActionFunction daf)
        {
            required = false;
            deferrals = 0;
            actionFunction = daf;
            staticData = null;
        }
        public DeferrableAction(DeferrableActionFunction daf, Network data)
        {
            required = false;
            deferrals = 0;
            actionFunction = daf;
            staticData = data;
        }

        /// <summary>
        /// Request that the action be taken.  If it is currently deferred, then
        /// the action won't be taken.
        /// </summary>
        /// <param name="requestData"></param>
        public void requestAction(Node requestData)
        {
            if (isActionDeferred())
                setActionRequired();
            else
                actionFunction(staticData, requestData);
        }

        /// <summary>
        /// Defer the action, assuming that the caller uses isActionDeferred()
        /// and setActionRequired() when attempting the action. 
        /// This meant to be called in pairs with undeferAction().
        /// </summary>
        public void deferAction() { deferrals++; }

        /// <summary>
        /// Undefer the action, which results in the action being performed if
        /// it was requested prior to the undeferral.   If the action is called,
        /// then the requestData parameter passed to the action function is NULL.
        /// This meant to be called in pairs with deferAction().
        /// </summary>
        public void undeferAction()
        {
            Debug.Assert(deferrals > 0);
            if ((--deferrals == 0) && required)
            {
                required = false;
                actionFunction(staticData, null);
            }
        }

        /// <summary>
        /// See if the action is currently deferred.
        /// </summary>
        /// <returns></returns>
        public bool isActionDeferred() { return deferrals != 0; }
    }
}
