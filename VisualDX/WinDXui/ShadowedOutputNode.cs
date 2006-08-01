// Completed 7/27/2006

using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;

namespace WinDX.UI
{
    public abstract class ShadowedOutputNode : DrivenNode
    {
        public ShadowedOutputNode(NodeDefinition nd, Network net, int instc)
            : base(nd, net, instc)
        {
        }

        /// <summary>
        /// Define the mapping of inputs that shadow outputs.
        /// By default, all data driven interactors, have a single output that is
        /// shadowed by the third input.
        /// </summary>
        /// <param name="output_index"></param>
        /// <returns>Returns an input index (greater than 1) or 0 if there is no shadowing
        /// input for the given output index.</returns>
        protected virtual int getShadowingInput(int output_index)
        {
            int input_index; 

            switch (output_index)
            {
                case 1: input_index = 3; break;
                default: input_index = 0; break;
            }
            return input_index;
        }

        /// <summary>
        /// A node that has its first parameter set or its last parameter unset
        /// must mark the network dirty so that is resent with/without the module
        /// in the network.  
        /// </summary>
        /// <param name="input"></param>
        /// <param name="index"></param>
        /// <param name="status"></param>
        protected override void ioParameterStatusChanged(bool input, int index, 
            NodeParameterStatusChange status)
        {
            if (input && isInputViewable(index))
            {
                int icnt = InputCount;
                int connections, settabs, i;
                bool became_non_dd = false;

                if ((status & NodeParameterStatusChange.ParameterValueChanged) > 0 &&
                    (status != NodeParameterStatusChange.PatemeterSetValueChanged))
                {
                    for (connections = 0, settabs = 0, i = 1; connections == 0 && settabs < 2 && i <= icnt;
                        i++)
                    {
                        if (isInputViewable(i))
                        {
                            if (isInputConnected(i))
                                connections++;
                            else if (!isInputDefaulting(i))
                                settabs++;
                        }
                    }
                    if (connections != 0 && (settabs < 2))
                    {
                        // Either a parameter was just given a set value or just 
                        // set to the default value.  If just set to the default value 
                        // and the number of set tabs is now 0 then the user just made 
                        // the last tab up so mark the network dirty.  If just given a 
                        // set value and it is the only (first) parameter with a set 
                        // value then mark the network dirty.
                        if (settabs == 0 && 
                            status == NodeParameterStatusChange.ParameterSetValueToDefaulting)
                        {
                            //Tool went from data-driven to non-data-driven.
                            became_non_dd = true;
                        }
                        else if (settabs == 1 && !isInputDefaulting(index))
                        {
                            // Tool went from non-data-driven to data-driven
                            getNetwork().setDirty();
                        }
                    }
                }
                if (became_non_dd)
                {
                    getNetwork().setDirty();
                }
            }
            base.ioParameterStatusChanged(input, index, status);
        }

        /// <summary>
        /// Update any inputs that are being updated by the server (i.e. the
        /// module that is doing the data-driven operations).
        /// We update the values internally, and send the shadowing input
        /// value back to the executive with an Executive() call.
        /// We use the Executive call instead of a direct assignment, because if
        /// we are currently in execute-on-change  mode, the assignment would cause
        /// extra executions.  
        /// The Executive() call (a dictionary update) avoids that.
        /// </summary>
        /// <param name="output_index"></param>
        /// <param name="val"></param>
        /// <param name="t"></param>
        /// <returns></returns>
        protected DXTypeVals setShadowedOutputSentFromServer(int output_index, String val,
            DXTypeVals t)
        {
            // Set the values internally
            // Set the output quietly instead of just setting it and not sending it
            // for the following scenario with out the quietly:
            //
            //   1) Interactor->Echo,	Execute echos 0	 
            //		(references GLOBAL main_Interactor_1_out_1)
            //   2) Set Interactor:min value to 5, Execute echos 5
            //		(references LOCAL  main_Interactor_1_out_1)
            //   3) Tab up Interactor:min, Execute echos 0
            //		(references GLOBAL main_Interactor_1_out_1)
            //
            // So, setting the output quietly makes sure that the global value
            // is up to date.

            int input_index = getShadowingInput(output_index);
            DXTypeVals type = setOutputValueQuietly(output_index, val, t);
            if (type != DXTypeVals.UndefinedType)
            {
                clearOutputDirty(output_index);
                setInputValueQuietly(input_index, val, type);
            }
            return type;
        }

        /// <summary>
        /// Set the output value of ShadowedOutputNode.  This is the same as for
        /// the super class methodd, except that it updates the shadowing inputs 
        /// </summary>
        /// <param name="index"></param>
        /// <param name="value"></param>
        /// <param name="t"></param>
        /// <param name="send"></param>
        /// <returns></returns>
        public override DXTypeVals setOutputValue(int index, String value, DXTypeVals t, bool send)
        {
            DXTypeVals type;

            Debug.Assert(value != null);

            // Defer visual notification in case, we do more then one set*Value().
            deferVisualNotification();

            // When data-driven, outputs that have shadowing inputs are not sent and
            // instead their shadows are sent..
            int shadow_input = getShadowingInput(index);
            if (shadow_input > 0)
            {
                type = base.setOutputValue(index, value, t, false);
                if (type != DXTypeVals.UndefinedType)
                {
                    value = getOutputValueString(index);
                    setInputValue(shadow_input, value, type, false);
                    if (send)
                        sendValues(false);
                }
            }
            else
            {
                type = base.setOutputValue(index, value, t, send);
            }

            undeferVisualNotification();
            return type;
        }
    }
}
