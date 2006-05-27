using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using WinDX.Scanning;
using System.Text.RegularExpressions;
using System.IO;
using NUnit.Framework;
using System.Drawing;

namespace WinDX.UI
{
    class Utils
    {
        const Int32 UnspecifiedPosition = 32767;
        const Int32 UnspecifiedDimension = 32767;

        /// <summary>
        ///     ParseGeometryComment actually performs the Window placement and
        ///     Window sizing for shell windows such as the ImageWindow and
        ///     Control Panels. The network saves the placement as a normalized
        ///     vector of where and what size it was on the authors screen
        ///     and then tries to replicate that to fit the screen of others. 
        /// </summary>
        /// <param name="line"></param>
        /// <param name="file"></param>
        /// <param name="lineno"></param>
        /// <param name="xpos"></param>
        /// <param name="ypos"></param>
        /// <param name="xsize"></param>
        /// <param name="ysize"></param>
        /// <param name="tag"></param>
        /// <returns></returns>
        public static bool ParseGeometryComment(String line, String file, int lineno, ref int xpos,
            ref int ypos, ref int xsize, ref int ysize, String tag)
        {
            Scanner scanner = new Scanner();
            MatchCollection matches = null;
            float norm_xsize, norm_ysize, norm_xpos, norm_ypos;
            Screen[] screens = Screen.AllScreens;
            int screen = -1;
            int width = 0, height = 0, x = 0, y = 0;

            if (tag == null)
                tag = "window";

            String scanline;
            scanline = String.Format(
                @"{0}: position = \({{Single}}\, {{Single}}\)\, size = {{Single}}x{{Single}}, screen = {{Int32}}",
                tag);

            scanline = scanner.CreateRegexPattern(scanline);
            //scanner.Scan(line, scanline, targets);
            Regex reggie = new Regex(scanline);

            matches = reggie.Matches(line);
            if (matches.Count == 0)
            {
                scanline = String.Format(
                @"{0}: position = \({{Single}}\, {{Single}}\)\, size = {{Single}}x{{Single}}",
                tag);
                scanline = scanner.CreateRegexPattern(scanline);
                reggie = new Regex(scanline);
                matches = reggie.Matches(line);
            }

            if (matches.Count == 0)
            {
                WarningDialog wd = new WarningDialog();
                wd.post("Bad comment found in file {0} line {1}", file, lineno);
                return false;
            }

            string sVal = matches[0].Groups[1].Captures[0].Value;
            norm_xpos = float.Parse(sVal);
            sVal = matches[0].Groups[2].Captures[0].Value;
            norm_ypos = float.Parse(sVal);
            sVal = matches[0].Groups[3].Captures[0].Value;
            norm_xsize = float.Parse(sVal);
            sVal = matches[0].Groups[4].Captures[0].Value;
            norm_ysize = float.Parse(sVal);
            if (matches[0].Groups.Count == 6)
            {
                sVal = matches[0].Groups[5].Captures[0].Value;
                screen = Int32.Parse(sVal);
            }

            if (norm_xsize >= 3 || norm_ysize >= 3)
            {
                xpos = UnspecifiedPosition;
                ypos = UnspecifiedPosition;
                xsize = UnspecifiedDimension;
                ysize = UnspecifiedDimension;
                return true;
            }

            if (screen != -1 && screen < screens.Length)
            {
                width = screens[screen].Bounds.Width;
                height = screens[screen].Bounds.Height;
                x = screens[screen].Bounds.X;
                y = screens[screen].Bounds.Y;
            }
            else
            {
                Screen ps = Screen.PrimaryScreen;
                width = ps.Bounds.Width;
                height = ps.Bounds.Height;
                x = ps.Bounds.X;
                y = ps.Bounds.Y;
            }

            xpos = (Int32)Math.Round(width * norm_xpos + x);
            ypos = (Int32)Math.Round(height * norm_ypos + y);
            xsize = (Int32)Math.Round(width * norm_xsize);
            ysize = (Int32)Math.Round(height * norm_ysize);

            return true;
        }

        public static bool PrintGeometryComment(StreamWriter f, int xpos, int ypos,
            int xsize, int ysize, String tag, String indent)
        {
            float norm_xsize = 0, norm_ysize = 0, norm_xpos = 0, norm_ypos = 0;
            int screen = -1;
            int x = 0, y = 0, width = 0, height = 0;
            Screen[] screens = Screen.AllScreens;

            if (tag == null)
                tag = "window";

            if (indent == null)
                indent = "";

            int i = 0;
            while (i < screens.Length)
            {
                if (xpos > screens[i].Bounds.X &&
                    xpos < screens[i].Bounds.X + screens[i].Bounds.Width &&
                    ypos > screens[i].Bounds.Y &&
                    ypos < screens[i].Bounds.Y + screens[i].Bounds.Height)
                {
                    screen = i;
                    width = screens[i].Bounds.Width;
                    height = screens[i].Bounds.Height;
                    x = screens[i].Bounds.X;
                    y = screens[i].Bounds.Y;
                }
            }

            norm_xsize = (float)(xsize / width);
            norm_ysize = (float)(ysize / height);
            norm_xpos = (float)(xpos - x) / width;
            norm_ypos = (float)(ypos - y) / height;

            if (screen != -1)
            {
                f.WriteLine("{0}// {1}: position = ({2},{3}), size = {4}x{5}, screen = {6}",
                    indent, tag, norm_xpos.ToString("#.0000"), norm_ypos.ToString("#.0000"),
                    norm_xsize.ToString("#.0000"), norm_ysize.ToString("#.0000"), screen);
            }
            else
            {
                f.WriteLine("{0}// {1}: position = ({2},{3}), size = {4}x{5}",
                    indent, tag, norm_xpos.ToString("#.0000"), norm_ypos.ToString("#.0000"),
                    norm_xsize.ToString("#.0000"), norm_ysize.ToString("#.0000"));
            }
            return true;

        }

        /// <summary>
        /// Will tokenize a string.
        /// </summary>
        /// <param name="s"></param>
        /// <param name="separators">The charactors to split over.</param>
        /// <param name="quotes">The characters used for grouping (not split within)</param>
        /// <returns>A list of the tokenized strings. Separators are eaten, quotes are returned. </returns>
        public static List<String> StringTokenizer(String s, String separators, String[] quotes)
        {
            String seps;
            String qts;

            if (s == null)
                return null;
            if (separators == null)
                seps = " ";
            else
                seps = separators;

            if (quotes == null)
                qts = "\"";
            else
            {
                qts = quotes[0];
                for (int i = 1; i < quotes.Length; i++)
                {
                    qts += quotes[i];
                }
            }

            List<String> ret = new List<string>();

            char[] fullString = s.ToCharArray();
            bool inQuoted = false;
            String str = "";
            Stack<String> quoteStack = new Stack<string>();

            for (int i = 0; i < fullString.Length; i++)
            {
                String ch = String.Format("{0}", fullString[i]);

                #region Check if separator
                if (separators.Contains(ch))
                {
                    if (inQuoted)
                        str += ch;
                    else
                    {
                        if (str.Length > 0)
                        {
                            ret.Add(str);
                            str = "";
                        }
                    }

                }
                #endregion 
                #region Check if a Quote
                else if (qts.Contains(ch))
                {
                    if (inQuoted)
                    {
                        // Now see if we're closing, opening, or ignoring
                        for (int j = 0; j < quotes.Length; j++)
                        {
                            if (quotes[j].Contains(ch))
                            {
                                // Found the quote, check to see if its a binary or singular.
                                if (quotes[j].Length == 1)
                                {
                                    // Singular, now see if its equal to the top of the quoteStack.
                                    if (quoteStack.Count > 0 && quoteStack.Peek() == ch)
                                    {
                                        // Pop off the stack and close current token
                                        quoteStack.Pop();
                                        if (quoteStack.Count == 0)
                                        {
                                            str += ch;
                                            ret.Add(str);
                                            str = "";
                                            inQuoted = false;
                                        }
                                        else
                                        {
                                            str += ch;
                                        }
                                    }
                                    else
                                    {
                                        quoteStack.Push(ch);
                                        inQuoted = true;
                                        str += ch;
                                    }
                                }
                                else
                                {
                                    // Binary quote, check to see if they match up.
                                    if (quoteStack.Count > 0 && quotes[j].Contains(quoteStack.Peek()))
                                    {
                                        // check to see if its the match or should be
                                        // pushed up. 
                                        int loc = quotes[j].IndexOf(ch);
                                        if (loc == 0)
                                        {
                                            quoteStack.Push(ch);
                                            str += ch;
                                        }
                                        else
                                        {
                                            // Closing quote
                                            quoteStack.Pop();
                                            if (quoteStack.Count == 0)
                                            {
                                                str += ch;
                                                ret.Add(str);
                                                str = "";
                                                inQuoted = false;
                                            }
                                            else
                                            {
                                                str += ch;
                                            }
                                        }

                                    }
                                    else
                                    {
                                        quoteStack.Push(ch);
                                        inQuoted = true;
                                        str += ch;
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        quoteStack.Push(ch);
                        str += ch;
                        inQuoted = true;
                    }
                }
                #endregion 
                else
                {
                    str += ch;
                }
            }

            if (str.Length > 0)
                ret.Add(str);

            return ret;
        }


        /// <summary>
        /// Find the first string in s that is delimited by the 'start'
        /// and 'end' characters.
        /// </summary>
        /// <param name="s">String to parse</param>
        /// <param name="start">start character</param>
        /// <param name="end">end character</param>
        /// <param name="nestChars">if given as a string of nesting
        /// characters then if the end delimiter is found within the 
        /// nesting characters then don't accept it as the terminating
        /// delimiter. Useful for finding '"{a} {b}"' within
        /// '{"{a} {b}"}'.</param>
        /// <returns>null if none found otherwise a string that contains
        /// the begin and end characters.</returns>
        public static String FindDelimitedString(String s, char start, char end, String nestChars)
        {
            if (s == null)
                return null;
            int si = s.IndexOf(start);
            if (si < 0)
                return null;

            String sub1 = s.Substring(si + 1);

            if (sub1.IndexOf(end) < 0)
                return null;

            if (nestChars == null)
                return (sub1.Substring(0, sub1.IndexOf(end)));

            // Now need to find nested pairs of nestChars.
            char[] castr = sub1.ToCharArray();

            char nestChar = '\0';
            int lastInd = -1;

            for (int i = 0; i < castr.Length; i++)
            {
                char nc = castr[i];
                int tt = nestChars.IndexOf(nc);
                if (tt >= 0)
                {
                    // A nesting character.
                    if (nestChar == '\0')
                        nestChar = castr[i];
                    else if (nestChar == castr[i])
                        nestChar = '\0';
                }
                else
                {
                    if (nestChar == '\0' && castr[i] == end)
                    {
                        lastInd = i;
                        break;
                    }
                }
            }

            if (lastInd == -1)
                return null;

            return (sub1.Substring(0, lastInd));

        }

        public static Color ColorFromPoundString(String str)
        {
            if (str.Length != 7)
                return Color.Black;
            String red = str.Substring(1, 2);
            String green = str.Substring(3, 2);
            String blue = str.Substring(5, 2);

            int redi = Int32.Parse(red, System.Globalization.NumberStyles.HexNumber);
            int greeni = Int32.Parse(green, System.Globalization.NumberStyles.HexNumber);
            int bluei = Int32.Parse(blue, System.Globalization.NumberStyles.HexNumber);

            Color c = Color.FromArgb(redi, greeni, bluei);
            return c;
        }

        /// <summary>
        /// Take a string and insert newlines to make it multiple line.
        /// </summary>
        /// <param name="str">String to add newlines to</param>
        /// <param name="avLength">The length preferred</param>
        /// <param name="maxLength">The maximum length if no space found to break near preferred</param>
        /// <returns></returns>
        public static String WordWrap(String str, int avLength) { return WordWrap(str, avLength, avLength + 3); }
        public static String WordWrap(String str, int avLength, int maxLength)
        {
            String newStr = "";
            String subStr = "";
            bool done = false;
            int buf = maxLength - avLength;

            String sub;
            int startingAt = 0;

            while (!done)
            {                
                if (startingAt > str.Length)
                    done = true;

                subStr = str.Substring(startingAt);
                subStr.TrimStart();
                if (subStr.Length > avLength + buf)
                {
                    sub = subStr.Substring(avLength - buf, 2 * buf);
                    int ci = sub.IndexOf(' ');
                    if (ci == -1)
                    {
                        newStr += subStr.Substring(0, avLength + buf) + Environment.NewLine;
                        startingAt += avLength + buf;
                    }
                    else
                    {
                        newStr += subStr.Substring(0, avLength - buf + ci) + Environment.NewLine;
                        startingAt += avLength - buf + ci;
                    }
                }
                else
                {
                    newStr += str.Substring(startingAt);
                    done = true;
                }

            }


            return newStr;
        }
    }
}
