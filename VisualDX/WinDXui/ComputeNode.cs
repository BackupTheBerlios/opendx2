using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Text.RegularExpressions;

namespace WinDX.UI
{
    class ComputeNode : Node
    {
        protected bool exposedExpression;
        protected String expression;
        protected List<String> nameList = new List<string>();

        protected String resolveExpression() { throw new Exception("Not Yet Implemented"); }

        protected override bool netPrintAuxComment(StreamWriter s)
        {
            throw new Exception("Not Yet Implemented");
            return base.netPrintAuxComment(s);
        }

        protected override bool addRepeats(bool input)
        {
            if (input)
            {
                int i = InputCount + 1;
                char name = 'a';
                name = (char)(name + i - 2);
                
                setName(name.ToString(), i - 1, false);
            }
            return base.addRepeats(input);
        }

        protected override bool removeRepeats(bool input)
        {
            if (input)
            {
                int i = InputCount;
                if (i - 2 <= nameList.Count)
                    nameList.RemoveAt(i - 2);
            }
            return base.removeRepeats(input);
        }

        public ComputeNode(NodeDefinition nd, Network net, int instnc)
            :base(nd, net, instnc)
        {
            expression = "";
            exposedExpression = false;
        }

        public override bool initialize()
        {
            char name = 'a';
            for (int i = 2; i <= InputCount; i++)
            {
                setName(name.ToString(), i - 1, false);
                name++;
            }
            return true;
        }

        public void setExpression(String expr, bool send)
        {
            expression = expr;
            exposedExpression = false;

            String input = resolveExpression();
            setInputValue(1, input, DXTypeVals.StringType, send);
        }
        
        public String getExpression() { return expression; }

        public void setName(String name, int i, bool send)
        {
            if (i - 1 > nameList.Count)
                nameList.Add(name);
            else
                nameList[i - 1] = name;

            String input = resolveExpression();
            setInputValue(1, input, DXTypeVals.StringType, send);
        }

        public String getName(int i)
        {
            if (i - 1 > nameList.Count) return null;
            return nameList[i - 1];
        }

        protected override bool netParseAuxComment(string comment, string filename, int lineno)
        {
            // Compute comments are of the form
            // expression: value = a*0.1
            // name[2]: value = a
            if (comment.StartsWith(" expression:"))
            {
                setExpression(comment.Substring(comment.IndexOf('=') + 2), false);
                return true;
            }
            else if (comment.StartsWith(" name["))
            {
                Regex regex = new Regex(@" name\[(\d+)\]: value = (.+)");
                Match m = regex.Match(comment);
                if (m.Success)
                {
                    int i = Int32.Parse(m.Groups[1].Value);
                    setName(m.Groups[2].Value, i, false);
                }
                else
                {
                    ErrorDialog ed = new ErrorDialog();
                    ed.post("Erroneous 'name' comment file {0}, line {1}", filename, lineno);
                }
                return true;
            }
            else
                return base.netParseAuxComment(comment, filename, lineno);
        }

        public override string getExtraPSText()
        {
            return getExpression();
        }

        public override bool isA(Symbol classname)
        {
            Symbol s = SymbolManager.theSymbolManager.registerSymbol("ComputeNode");
            if (s == classname)
                return true;
            else
                return base.isA(classname);
        }
    }
}
