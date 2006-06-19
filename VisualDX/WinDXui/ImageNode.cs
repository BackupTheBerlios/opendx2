using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Text.RegularExpressions;
using WinDX.Scanning;

namespace WinDX.UI
{
    class ImageNode : DisplayNode
    {
        private class ParamConst
        {
            public const int IMAGETAG = 1;
            public const int OBJECT = 2;
            public const int WHERE = 3;
            public const int USEVECTOR = 4;
            public const int TO = 5;
            public const int FROM = 6;
            public const int WIDTH = 7;
            public const int RESOLUTION = 8;
            public const int ASPECT = 9;
            public const int UP = 10;
            public const int VIEWANGLE = 11;
            public const int PROJECTION = 12;
            public const int OPTIONS = 13;
            public const int BUTTON_STATE = 14;
            public const int BUTTON_UP_APPROX = 15;
            public const int BUTTON_DOWN_APPROX = 16;
            public const int BUTTON_UP_DENSITY = 17;
            public const int BUTTON_DOWN_DENSITY = 18;
            public const int RENDER_MODE = 19;
            public const int DEFAULT_CAMERA = 20;
            public const int RESET_CAMERA = 21;
            public const int BACKGROUND = 22;
            public const int THROTTLE = 23;
            public const int RECENABLE = 24;
            public const int RECFILE = 25;
            public const int RECFORMAT = 26;
            public const int RECRESOLUTION = 27;
            public const int RECASPECT = 28;
            public const int AAENABLE = 29;
            public const int AALABELS = 30;
            public const int AATICKS = 31;
            public const int AACORNERS = 32;
            public const int AAFRAME = 33;
            public const int AAADJUST = 34;
            public const int AACURSOR = 35;
            public const int AAGRID = 36;
            public const int AACOLORS = 37;
            public const int AAANNOTATION = 38;
            public const int AALABELSCALE = 39;
            public const int AAFONT = 40;
            public const int INTERACTIONMODE = 41;
            public const int IMAGENAME = 42;

            //
            // new AutoAxes parameters
            //
            public const int AA_XTICK_LOCS = 43;
            public const int AA_YTICK_LOCS = 44;
            public const int AA_ZTICK_LOCS = 45;
            public const int AA_XTICK_LABELS = 46;
            public const int AA_YTICK_LABELS = 47;
            public const int AA_ZTICK_LABELS = 48;

            //
            // On behalf of Java Explorer
            //
            public const int JAVA_OPTIONS = 49;

            public static int[] translateInputs = {
                0,
                USEVECTOR,
                OBJECT,
                WHERE,
                TO,
                FROM,
                WIDTH,
                RESOLUTION,
                ASPECT,
                UP,
                OPTIONS,
                AAENABLE,
                AALABELS,
                AATICKS,
                AACORNERS,
                AAFRAME,
                AAADJUST,
                AACURSOR,
                RECENABLE,
                RECFILE,
                THROTTLE,
                RECFORMAT,
                PROJECTION,
                VIEWANGLE,
                BUTTON_STATE,
                BUTTON_UP_APPROX,
                BUTTON_DOWN_APPROX,
                BUTTON_UP_DENSITY,
                BUTTON_DOWN_DENSITY,
                RENDER_MODE,
                BACKGROUND,
                AAGRID,
                AACOLORS,
                AAANNOTATION,
                AALABELSCALE,
                AAFONT
            };
        }

        private bool printCommonComments(StreamWriter sw, String indent)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected bool parseCommonComments(String comment, String file, int lineno)
        {
            Regex regex = new Regex(@" interaction mode = (.*)");
            Match m = regex.Match(comment);
            if (m.Success)
            {
                setInteractionMode(m.Groups[1].Value);

                // Now since this is the last comment, ask the ImageWindow 
                // to refresh its state from our new cfg state. 
                if (image != null)
                    image.updateFromNewCfgState();
                return true;
            }
            else if (comment.StartsWith(" internal caching:"))
            {
                regex = new Regex(@" internal caching: (\d+)");
                m = regex.Match(comment);
                if (m.Success)
                {
                    int cacheval = Int32.Parse(m.Groups[1].Value);
                    switch (cacheval)
                    {
                        case 0:
                            InternalCacheability = Cacheability.InternalsNotCached;
                            break;
                        case 1:
                            InternalCacheability = Cacheability.InternalsFullyCached;
                            break;
                        case 2:
                            InternalCacheability = Cacheability.InternalsCacheOnce;
                            break;
                        default:
                            return false;
                            break;
                    }
                    return true;
                }
            }
            return false;
        }

        // The mode that was saved in the .net/.cfg file (when not data-driven). 
        private DirectInteractionMode saveInteractionMode;

        // cache value for the nodes internal to the image macro.
        private Cacheability internalCache;

        // FIXME!: this should really be being done through ImageWindow via
        // ImageNode::reflectStateChange().  ImageNode has no business setting
        // senstivities of another object.  That is ImageWindow's decision.
        //
        private void updateWindowSensitivities()
        { }

        private Node getWebOptionsNode()
        {
            throw new Exception("Not Yet Implemented");
        }

        private static bool SendString(Object callbackData, PacketIF.PacketIFCallback callback, 
            StreamWriter sw, String str, bool viasocket)
        {
            if (!viasocket)
            {
                sw.Write(str);
                if (callback != null)
                    callback(callbackData, str);
            }
            else
            {
                DXApplication.theDXApplication.getPacketIF().sendBytes(str);
            }
            return true;
        }
        private static void FormatMacro(StreamWriter sw, PacketIF.PacketIFCallback callback, 
            Object callbackData, String[] s, bool viasocket)
        {
            foreach (String str in s)
            {
                SendString(callbackData, callback, sw, str, viasocket);
            }
        }

        #region Macros Generated By Code -- need to be replaced if the Macros are rebuilt
        protected static String[] GifMacroTxt = new String[] { 
            "macro ImageExport(",
            " object",
            ",base_name",
            ",originalCamera",
            ",format",
            ") -> (",
            " file_written",
            ") {",
            "ImageExport_Inp51_o1 = format;",
            "ImageExport_Inq56_o1[cache: 2] = ",
            "Inquire(",
            "ImageExport_Inp51_o1,",
            "\"is null\",",
            "NULL",
            ") [instance: 56, cache: 1];",
            "ImageExport_Inq11_o1[cache: 2] = ",
            "Inquire(",
            "ImageExport_Inp51_o1,",
            "\"string match\",",
            "\"gif\"",
            ") [instance: 11, cache: 1];",
            "ImageExport_Inq54_o1[cache: 2] = ",
            "Inquire(",
            "ImageExport_Inp51_o1,",
            "\"string match\",",
            "\"jpg\"",
            ") [instance: 54, cache: 1];",
            "ImageExport_Inq55_o1[cache: 2] = ",
            "Inquire(",
            "ImageExport_Inp51_o1,",
            "\"string match\",",
            "\"png\"",
            ") [instance: 55, cache: 1];",
            "ImageExport_Compute_79_o1 = ",
            "Compute(",
            "\"($0==1)?1:($1==1)?1:($2==1)?2:($3==1)?3:4\",",
            "ImageExport_Inq56_o1,",
            "ImageExport_Inq11_o1,",
            "ImageExport_Inq54_o1,",
            "ImageExport_Inq55_o1",
            ") [instance: 79, cache: 1];",
            "ImageExport_Inp6_o1 = base_name;",
            "ImageExport_Switch_35_o1[cache: 2] = ",
            "Switch(",
            "ImageExport_Compute_79_o1,",
            "{\"gif\"},",
            "{\"jpg\"},",
            "{\"png\"},",
            "ImageExport_Inp51_o1",
            ") [instance: 35, cache: 1];",
            "ImageExport_Format_7_o1[cache: 2] = ",
            "Format(",
            "\"%s.%s\",",
            "ImageExport_Inp6_o1,",
            "ImageExport_Switch_35_o1",
            ") [instance: 7, cache: 1];",
            "ImageExport_Inp5_o1 = object;",
            "ImageExport_Inp22_o1 = originalCamera;",
            "ImageExport_Inq8_o1[cache: 2] = ",
            "Inquire(",
            "ImageExport_Inp5_o1,",
            "\"is image + 1\",",
            "NULL",
            ") [instance: 8, cache: 1];",
            "file_written = ImageExport_Format_7_o1;",
            "ImageExport_Render_1_o1[cache: 2] = ",
            "Render(",
            "ImageExport_Inp5_o1,",
            "ImageExport_Inp22_o1,",
            "\"DXByte\"",
            ") [instance: 1, cache: 1];",
            "ImageExport_Switch_9_o1[cache: 2] = ",
            "Switch(",
            "ImageExport_Inq8_o1,",
            "ImageExport_Render_1_o1,",
            "ImageExport_Inp5_o1",
            ") [instance: 9, cache: 1];",
            "WriteImage(",
            "ImageExport_Switch_9_o1,",
            "ImageExport_Format_7_o1,",
            "\"ImageMagick supported format\",",
            "NULL",
            ") [instance: 1, cache: 1];",
            "}"
        };
        protected static String[] VrmlMacroTxt = new String[] {
            "macro VRMLExport(",
            " object",
            ",base_name",
            ") -> (",
            " file_written",
            ") {",
            "VRMLExport_Inp7_o1 = object;",
            "VRMLExport_Inp8_o1 = base_name;",
            "Export(",
            "VRMLExport_Inp7_o1,",
            "VRMLExport_Inp8_o1,",
            "\"vrml\"",
            ") [instance: 1, cache: 1];",
            "VRMLExport_Format_8_o1[cache: 2] = ",
            "Format(",
            "\"%s.wrl\",",
            "VRMLExport_Inp8_o1,",
            "NULL",
            ") [instance: 8, cache: 1];",
            "file_written = VRMLExport_Format_8_o1;",
            "}"
        };
        protected static String[] ImageMacroTxt = new String[] {
            "macro Image(",
            " id",
            ",object",
            ",where",
            ",useVector",
            ",to",
            ",from",
            ",width",
            ",resolution",
            ",aspect",
            ",up",
            ",viewAngle",
            ",perspective",
            ",options",
            ",buttonState",
            ",buttonUpApprox",
            ",buttonDownApprox",
            ",buttonUpDensity",
            ",buttonDownDensity",
            ",renderMode",
            ",defaultCamera",
            ",reset",
            ",backgroundColor",
            ",throttle",
            ",recEnable",
            ",recFile",
            ",recFormat",
            ",recResolution",
            ",recAspect",
            ",AAenable",
            ",AAlabels",
            ",AAticks",
            ",AAcorners",
            ",AAframe",
            ",AAadjust",
            ",AAcursor",
            ",AAgrid",
            ",AAcolors",
            ",AAannotation",
            ",AAlabelscale",
            ",AAfont",
            ",interactionMode",
            ",title",
            ",aaxTickLocs",
            ",AAyTickLocs",
            ",aazTickLocs",
            ",aaxTickLabels",
            ",aayTickLabels",
            ",aazTickLabels",
            ",webOptions",
            ") -> (",
            " object",
            ",camera",
            ",Where",
            ") {",
            "IInp2_o1 = object;",
            "objectx = IInp2_o1;",
            "IRcv14_o1[cache: 0] = objectx;",
            "IInp21_o1 = reset;",
            "IInq44_o1[cache: 2] = ",
            "Inquire(",
            "IInp21_o1,",
            "\"is null + 1\",",
            "NULL",
            ") [instance: 44, cache: 1];",
            "ISwitch_33_o1[cache: 2] = ",
            "Switch(",
            "IInq44_o1,",
            "IInp21_o1,",
            "0",
            ") [instance: 33, cache: 1];",
            "resetx = ISwitch_33_o1;",
            "IRcv5_o1[cache: 0] = resetx;",
            "IInq2_o1[cache: 2] = ",
            "Inquire(",
            "IRcv5_o1,",
            "\"is null + 1\",",
            "NULL",
            ") [instance: 2, cache: 1];",
            "ISwitch_3_o1[cache: 2] = ",
            "Switch(",
            "IInq2_o1,",
            "IRcv5_o1,",
            "0",
            ") [instance: 3, cache: 1];",
            "IInp4_o1 = useVector;",
            "useVectorx = IInp4_o1;",
            "IRcv4_o1[cache: 0] = useVectorx;",
            "ICompute_6_o1[cache: 2] = ",
            "Compute(",
            "\"($0 != 0 || $1 == 0) ? 1 : 2\",",
            "ISwitch_3_o1,",
            "IRcv4_o1",
            ") [instance: 6, cache: 1];",
            "IInp20_o1 = defaultCamera;",
            "defaultCamerax = IInp20_o1;",
            "IRcv2_o1[cache: 0] = defaultCamerax;",
            "IInq1_o1[cache: 2] = ",
            "Inquire(",
            "IRcv2_o1,",
            "\"is null + 1\",",
            "NULL",
            ") [instance: 1, cache: 1];",
            "IInp22_o1 = backgroundColor;",
            "bkgndColor = IInp22_o1;",
            "IRcv3_o1[cache: 0] = bkgndColor;",
            "IUpdateCamera_1_o1[cache: 2] = ",
            "UpdateCamera(",
            "IRcv2_o1,",
            "NULL,",
            "NULL,",
            "NULL,",
            "NULL,",
            "NULL,",
            "NULL,",
            "NULL,",
            "NULL,",
            "IRcv3_o1",
            ") [instance: 1, cache: 1];",
            "IRcv119_o1[cache: 0] = objectx;",
            "IInp8_o1 = resolution;",
            "resolutionx = IInp8_o1;",
            "IRcv9_o1[cache: 0] = resolutionx;",
            "IInp9_o1 = aspect;",
            "aspectx = IInp9_o1;",
            "IRcv10_o1[cache: 0] = aspectx;",
            "IInp12_o1 = perspective;",
            "perspectivex = IInp12_o1;",
            "IRcv12_o1[cache: 0] = perspectivex;",
            "IInp11_o1 = viewAngle;",
            "angle = IInp11_o1;",
            "IRcv13_o1[cache: 0] = angle;",
            "IAutoCamera_1_o1[cache: 2] = ",
            "AutoCamera(",
            "IRcv119_o1,",
            "\"front\",",
            "IRcv119_o1,",
            "IRcv9_o1,",
            "IRcv10_o1,",
            "[0 1 0 ],",
            "IRcv12_o1,",
            "IRcv13_o1,",
            "IRcv3_o1",
            ") [instance: 1, cache: 1];",
            "ISwitch_1_o1[cache: 2] = ",
            "Switch(",
            "IInq1_o1,",
            "IUpdateCamera_1_o1,",
            "IAutoCamera_1_o1",
            ") [instance: 1, cache: 1];",
            "IInp5_o1 = to;",
            "tox = IInp5_o1;",
            "IRcv6_o1[cache: 0] = tox;",
            "IInp6_o1 = from;",
            "fromx = IInp6_o1;",
            "IRcv7_o1[cache: 0] = fromx;",
            "IInp7_o1 = width;",
            "widthx = IInp7_o1;",
            "IRcv8_o1[cache: 0] = widthx;",
            "IInp10_o1 = up;",
            "upx = IInp10_o1;",
            "IRcv11_o1[cache: 0] = upx;",
            "ICamera_1_o1[cache: 2] = ",
            "Camera(",
            "IRcv6_o1,",
            "IRcv7_o1,",
            "IRcv8_o1,",
            "IRcv9_o1,",
            "IRcv10_o1,",
            "IRcv11_o1,",
            "IRcv12_o1,",
            "IRcv13_o1,",
            "IRcv3_o1",
            ") [instance: 1, cache: 1];",
            "ISwitch_2_o1[cache: 2] = ",
            "Switch(",
            "ICompute_6_o1,",
            "ISwitch_1_o1,",
            "ICamera_1_o1",
            ") [instance: 2, cache: 1];",
            "camera_xcvr = ISwitch_2_o1;",
            "IRcv15_o1[cache: 0] = camera_xcvr;",
            "IInp30_o1 = AAlabels;",
            "aalabels = IInp30_o1;",
            "IRcv16_o1[cache: 0] = aalabels;",
            "IInp31_o1 = AAticks;",
            "aaticks = IInp31_o1;",
            "IRcv17_o1[cache: 0] = aaticks;",
            "IInp32_o1 = AAcorners;",
            "aacorners = IInp32_o1;",
            "IRcv22_o1[cache: 0] = aacorners;",
            "IInp33_o1 = AAframe;",
            "aaframe = IInp33_o1;",
            "IRcv21_o1[cache: 0] = aaframe;",
            "IInp34_o1 = AAadjust;",
            "aaadjust = IInp34_o1;",
            "IRcv20_o1[cache: 0] = aaadjust;",
            "IInp35_o1 = AAcursor;",
            "aacursor = IInp35_o1;",
            "IRcv19_o1[cache: 0] = aacursor;",
            "IInp36_o1 = AAgrid;",
            "aagrid = IInp36_o1;",
            "IRcv18_o1[cache: 0] = aagrid;",
            "IInp37_o1 = AAcolors;",
            "aacolors = IInp37_o1;",
            "IRcv26_o1[cache: 0] = aacolors;",
            "IInp38_o1 = AAannotation;",
            "annotation = IInp38_o1;",
            "IRcv25_o1[cache: 0] = annotation;",
            "IInp39_o1 = AAlabelscale;",
            "aalabelscale = IInp39_o1;",
            "IRcv24_o1[cache: 0] = aalabelscale;",
            "IInp40_o1 = AAfont;",
            "aafont = IInp40_o1;",
            "IRcv23_o1[cache: 0] = aafont;",
            "IInp43_o1 = aaxTickLocs;",
            "AAxTickLocs = IInp43_o1;",
            "IRcv27_o1[cache: 0] = AAxTickLocs;",
            "IInp44_o1 = AAyTickLocs;",
            "aayTickLocs = IInp44_o1;",
            "IRcv29_o1[cache: 0] = aayTickLocs;",
            "IInp45_o1 = aazTickLocs;",
            "AAzTickLocs = IInp45_o1;",
            "IRcv28_o1[cache: 0] = AAzTickLocs;",
            "IInp46_o1 = aaxTickLabels;",
            "AAxTickLabels = IInp46_o1;",
            "IRcv30_o1[cache: 0] = AAxTickLabels;",
            "IInp47_o1 = aayTickLabels;",
            "AAyTickLabels = IInp47_o1;",
            "IRcv32_o1[cache: 0] = AAyTickLabels;",
            "IInp48_o1 = aazTickLabels;",
            "AAzTickLabels = IInp48_o1;",
            "IRcv31_o1[cache: 0] = AAzTickLabels;",
            "IAutoAxes_2_o1[cache: 2] = ",
            "AutoAxes(",
            "IRcv14_o1,",
            "IRcv15_o1,",
            "IRcv16_o1,",
            "IRcv17_o1,",
            "IRcv22_o1,",
            "IRcv21_o1,",
            "IRcv20_o1,",
            "IRcv19_o1,",
            "IRcv18_o1,",
            "IRcv26_o1,",
            "IRcv25_o1,",
            "IRcv24_o1,",
            "IRcv23_o1,",
            "IRcv27_o1,",
            "IRcv29_o1,",
            "IRcv28_o1,",
            "IRcv30_o1,",
            "IRcv32_o1,",
            "IRcv31_o1",
            ") [instance: 2, cache: 1];",
            "ICollectNamed_1_o1[cache: 2] = ",
            "CollectNamed(",
            "0,",
            "\"javaId\",",
            "[0,0],",
            "\"counters\",",
            "\"gif\",",
            "\"format\",",
            "0,",
            "\"orbit\",",
            "0,",
            "\"imgId\",",
            "0,",
            "\"enabled\",",
            "\"image\",",
            "\"file\",",
            "{10.0},",
            "\"orbitDelta\",",
            "0,",
            "\"cacheCount\",",
            "\"untitled\",",
            "\"groupName\"",
            ") [instance: 1, cache: 1];",
            "IInp29_o1 = AAenable;",
            "IInq24_o1[cache: 2] = ",
            "Inquire(",
            "IInp29_o1,",
            "\"is null +1\",",
            "NULL",
            ") [instance: 24, cache: 1];",
            "ISwitch_25_o1[cache: 2] = ",
            "Switch(",
            "IInq24_o1,",
            "IInp29_o1,",
            "0",
            ") [instance: 25, cache: 1];",
            "aaenable = ISwitch_25_o1;",
            "IRcv33_o1[cache: 0] = aaenable;",
            "ICompute_1_o1[cache: 2] = ",
            "Compute(",
            "\"$0 + 1\",",
            "IRcv33_o1",
            ") [instance: 1, cache: 1];",
            "IInp19_o1 = renderMode;",
            "IInq30_o1[cache: 2] = ",
            "Inquire(",
            "IInp19_o1,",
            "\"is null + 1\",",
            "NULL",
            ") [instance: 30, cache: 1];",
            "ISwitch_31_o1[cache: 2] = ",
            "Switch(",
            "IInq30_o1,",
            "IInp19_o1,",
            "0",
            ") [instance: 31, cache: 1];",
            "renderModex = ISwitch_31_o1;",
            "IRcv162_o1[cache: 0] = renderModex;",
            "ICompute_2_o1[cache: 2] = ",
            "Compute(",
            "\"$0 + 1\",",
            "IRcv162_o1",
            ") [instance: 2, cache: 1];",
            "IInp24_o1 = recEnable;",
            "IInq8_o1[cache: 2] = ",
            "Inquire(",
            "IInp24_o1,",
            "\"is null + 1\",",
            "NULL",
            ") [instance: 8, cache: 1];",
            "ISwitch_15_o1[cache: 2] = ",
            "Switch(",
            "IInq8_o1,",
            "IInp24_o1,",
            "0",
            ") [instance: 15, cache: 1];",
            "recEnablex = ISwitch_15_o1;",
            "IRcv123_o1[cache: 0] = recEnablex;",
            "IInp27_o1 = recResolution;",
            "recRes = IInp27_o1;",
            "IRcv168_o1[cache: 0] = recRes;",
            "IInq4_o1[cache: 2] = ",
            "Inquire(",
            "IRcv168_o1,",
            "\"is null + 1\",",
            "NULL",
            ") [instance: 4, cache: 1];",
            "IRcv171_o1[cache: 0] = camera_xcvr;",
            "IInq7_o1[cache: 2] = ",
            "Inquire(",
            "IRcv171_o1,",
            "\"camera resolution\",",
            "NULL",
            ") [instance: 7, cache: 1];",
            "ISwitch_12_o1[cache: 2] = ",
            "Switch(",
            "IInq4_o1,",
            "IRcv168_o1,",
            "IInq7_o1",
            ") [instance: 12, cache: 1];",
            "IInp28_o1 = recAspect;",
            "recAsp = IInp28_o1;",
            "IRcv169_o1[cache: 0] = recAsp;",
            "IInq5_o1[cache: 2] = ",
            "Inquire(",
            "IRcv169_o1,",
            "\"is null + 1\",",
            "NULL",
            ") [instance: 5, cache: 1];",
            "IInq6_o1[cache: 2] = ",
            "Inquire(",
            "IRcv171_o1,",
            "\"camera aspect\",",
            "NULL",
            ") [instance: 6, cache: 1];",
            "ISwitch_13_o1[cache: 2] = ",
            "Switch(",
            "IInq5_o1,",
            "IRcv169_o1,",
            "IInq6_o1",
            ") [instance: 13, cache: 1];",
            "ICompute_3_o1[cache: 2] = ",
            "Compute(",
            "\"$0 == 0 ? 1 : (($1 == $2) && ($3 == $4)) ? 2 : 4\",",
            "IRcv123_o1,",
            "ISwitch_12_o1,",
            "IInq7_o1,",
            "ISwitch_13_o1,",
            "IInq6_o1",
            ") [instance: 3, cache: 1];",
            "IInp50_o1 = webOptions;",
            "IInq23_o1[cache: 2] = ",
            "Inquire(",
            "IInp50_o1,",
            "\"is null + 1\",",
            "NULL",
            ") [instance: 23, cache: 1];",
            "ISwitch_24_o1[cache: 2] = ",
            "Switch(",
            "IInq23_o1,",
            "IInp50_o1,",
            "ICollectNamed_1_o1",
            ") [instance: 24, cache: 1];",
            "ISelect_7_o1[cache: 2] = ",
            "Select(",
            "ISwitch_24_o1,",
            "\"enabled\",",
            "NULL",
            ") [instance: 7, cache: 1];",
            "java_enabled = ISelect_7_o1;",
            "IRcv129_o1[cache: 0] = java_enabled;",
            "IInq10_o1[cache: 2] = ",
            "Inquire(",
            "IRcv129_o1,",
            "\"is null + 1\",",
            "NULL",
            ") [instance: 10, cache: 1];",
            "ISwitch_17_o1[cache: 0] = ",
            "Switch(",
            "IInq10_o1,",
            "IRcv129_o1,",
            "0",
            ") [instance: 17, cache: 1];",
            "ICompute_7_o1[cache: 2] = ",
            "Compute(",
            "\"$0+1\",",
            "ISwitch_17_o1",
            ") [instance: 7, cache: 1];",
            "IRcv215_o1[cache: 0] = camera_xcvr;",
            "IInq31_o1[cache: 2] = ",
            "Inquire(",
            "IRcv215_o1,",
            "\"camera to\",",
            "NULL",
            ") [instance: 31, cache: 1];",
            "IInq32_o1[cache: 2] = ",
            "Inquire(",
            "IRcv215_o1,",
            "\"camera from\",",
            "NULL",
            ") [instance: 32, cache: 1];",
            "ICompute_27_o1[cache: 2] = ",
            "Compute(",
            "\"$1-$0\",",
            "IInq31_o1,",
            "IInq32_o1",
            ") [instance: 27, cache: 1];",
            "ICompute_28_o1[cache: 2] = ",
            "Compute(",
            "\"mag($0)\",",
            "ICompute_27_o1",
            ") [instance: 28, cache: 1];",
            "ICompute_29_o1[cache: 2] = ",
            "Compute(",
            "\"$1/$0\",",
            "ICompute_28_o1,",
            "ICompute_27_o1",
            ") [instance: 29, cache: 1];",
            "IRcv216_o1[cache: 0] = camera_xcvr;",
            "IInq33_o1[cache: 2] = ",
            "Inquire(",
            "IRcv216_o1,",
            "\"camera up\",",
            "NULL",
            ") [instance: 33, cache: 1];",
            "ICompute_30_o1[cache: 2] = ",
            "Compute(",
            "\"v = $1 cross $0; v/mag(v)\",",
            "ICompute_29_o1,",
            "IInq33_o1",
            ") [instance: 30, cache: 1];",
            "ICompute_31_o1[cache: 2] = ",
            "Compute(",
            "\"v = $0 cross $1; norm(v)\",",
            "ICompute_29_o1,",
            "ICompute_30_o1",
            ") [instance: 31, cache: 1];",
            "cfrom = IInq32_o1;",
            "IRcv67_o1[cache: 0] = cfrom;",
            "IConstruct_3_o1[cache: 0] = ",
            "Construct(",
            "{[-1 1 0]},",
            "{[0 -1 0] [1 0 0] [0 0 1]},",
            "[3 3 1],",
            "NULL",
            ") [instance: 3, cache: 1];",
            "IExtract_9_o1[cache: 2] = ",
            "Extract(",
            "IConstruct_3_o1,",
            "\"positions\"",
            ") [instance: 9, cache: 1];",
            "IRoute_14_o1[cache: 0],",
            "IRoute_14_o2[cache: 0] = ",
            "Route(",
            "ISelect_7_o1,",
            "ISwitch_24_o1",
            ") [instance: 14, cache: 1];",
            "ISelect_11_o1[cache: 2] = ",
            "Select(",
            "IRoute_14_o1,",
            "\"orbit\",",
            "NULL",
            ") [instance: 11, cache: 1];",
            "java_orbit = ISelect_11_o1;",
            "IRcv232_o1[cache: 0] = java_orbit;",
            "IRoute_9_o1[cache: 2],",
            "IRoute_9_o2[cache: 2] = ",
            "Route(",
            "IRcv232_o1,",
            "0",
            ") [instance: 9, cache: 1];",
            "IForEachN_1_o1[cache: 2],",
            "IForEachN_1_o2[cache: 2] = ",
            "ForEachN(",
            "IRoute_9_o1,",
            "8,",
            "1",
            ") [instance: 1, cache: 1];",
            "orbitLoop = IForEachN_1_o1;",
            "IRcv58_o1[cache: 0] = orbitLoop;",
            "ISelect_6_o1[cache: 2] = ",
            "Select(",
            "IExtract_9_o1,",
            "IRcv58_o1,",
            "NULL",
            ") [instance: 6, cache: 1];",
            "ISelect_13_o1[cache: 2] = ",
            "Select(",
            "IRoute_14_o1,",
            "\"orbitDelta\",",
            "NULL",
            ") [instance: 13, cache: 1];",
            "orbit_delta = ISelect_13_o1;",
            "IRcv63_o1[cache: 0] = orbit_delta;",
            "ICompute_33_o1[cache: 2] = ",
            "Compute(",
            "\"$0*sin($1*3.14159265/180.0)\",",
            "ICompute_28_o1,",
            "IRcv63_o1",
            ") [instance: 33, cache: 1];",
            "ICompute_32_o1[cache: 2] = ",
            "Compute(",
            "\"$0-$4*($1.x*$2+$1.y*$3)\",",
            "IRcv67_o1,",
            "ISelect_6_o1,",
            "ICompute_30_o1,",
            "ICompute_31_o1,",
            "ICompute_33_o1",
            ") [instance: 32, cache: 1];",
            "ISelect_9_o1[cache: 0] = ",
            "Select(",
            "IRoute_14_o1,",
            "\"counters\",",
            "NULL",
            ") [instance: 9, cache: 1];",
            "java_counters = ISelect_9_o1;",
            "IRcv158_o1[cache: 0] = java_counters;",
            "ICompute_56_o1[cache: 2] = ",
            "Compute(",
            "\"$0.x\",",
            "IRcv158_o1",
            ") [instance: 56, cache: 1];",
            "ICompute_57_o1[cache: 2] = ",
            "Compute(",
            "\"$0.y\",",
            "IRcv158_o1",
            ") [instance: 57, cache: 1];",
            "ISelect_5_o1[cache: 2] = ",
            "Select(",
            "IRoute_14_o1,",
            "\"format\",",
            "NULL",
            ") [instance: 5, cache: 1];",
            "java_format = ISelect_5_o1;",
            "IRcv131_o1[cache: 0] = java_format;",
            "IInq22_o1[cache: 2] = ",
            "Inquire(",
            "IRcv131_o1,",
            "\"string match\",",
            "\"wrl\"",
            ") [instance: 22, cache: 1];",
            "IInq11_o1[cache: 2] = ",
            "Inquire(",
            "IRcv131_o1,",
            "\"string match\",",
            "\"gif\"",
            ") [instance: 11, cache: 1];",
            "IInq54_o1[cache: 2] = ",
            "Inquire(",
            "IRcv131_o1,",
            "\"string match\",",
            "\"jpg\"",
            ") [instance: 54, cache: 1];",
            "IInq55_o1[cache: 2] = ",
            "Inquire(",
            "IRcv131_o1,",
            "\"string match\",",
            "\"png\"",
            ") [instance: 55, cache: 1];",
            "ICompute_78_o1 = ",
            "Compute(",
            "\"$0+$1+$2\",",
            "IInq11_o1,",
            "IInq54_o1,",
            "IInq55_o1",
            ") [instance: 78, cache: 1];",
            "IInq53_o1[cache: 2] = ",
            "Inquire(",
            "IRcv131_o1,",
            "\"string match\",",
            "\"dx\"",
            ") [instance: 53, cache: 1];",
            "ICompute_58_o1[cache: 0] = ",
            "Compute(",
            "\"($0==$1) && ($1==$2)\",",
            "IInq22_o1,",
            "ICompute_78_o1,",
            "IInq53_o1",
            ") [instance: 58, cache: 1];",
            "IRcv204_o1[cache: 0] = java_orbit;",
            "IRcv128_o1[cache: 0] = objectx;",
            "aaobj = IAutoAxes_2_o1;",
            "IRcv127_o1[cache: 0] = aaobj;",
            "ISwitch_4_o1[cache: 2] = ",
            "Switch(",
            "ICompute_1_o1,",
            "IRcv128_o1,",
            "IRcv127_o1",
            ") [instance: 4, cache: 1];",
            "IInq3_o1[cache: 2] = ",
            "Inquire(",
            "ISwitch_4_o1,",
            "\"object tag\",",
            "NULL",
            ") [instance: 3, cache: 1];",
            "whichCamera = ICompute_6_o1;",
            "IRcv40_o1[cache: 0] = whichCamera;",
            "IInp14_o1 = buttonState;",
            "IInq28_o1[cache: 2] = ",
            "Inquire(",
            "IInp14_o1,",
            "\"is null + 1\",",
            "NULL",
            ") [instance: 28, cache: 1];",
            "ISwitch_29_o1[cache: 2] = ",
            "Switch(",
            "IInq28_o1,",
            "IInp14_o1,",
            "1",
            ") [instance: 29, cache: 1];",
            "buttonStatex = ISwitch_29_o1;",
            "IRcv161_o1[cache: 0] = buttonStatex;",
            "IInp15_o1 = buttonUpApprox;",
            "IInq25_o1[cache: 2] = ",
            "Inquire(",
            "IInp15_o1,",
            "\"is null + 1\",",
            "NULL",
            ") [instance: 25, cache: 1];",
            "ISwitch_26_o1[cache: 2] = ",
            "Switch(",
            "IInq25_o1,",
            "IInp15_o1,",
            "\"none\"",
            ") [instance: 26, cache: 1];",
            "buttonUpApproxx = ISwitch_26_o1;",
            "IRcv163_o1[cache: 0] = buttonUpApproxx;",
            "IInp16_o1 = buttonDownApprox;",
            "IInq26_o1[cache: 2] = ",
            "Inquire(",
            "IInp16_o1,",
            "\"is null + 1\",",
            "NULL",
            ") [instance: 26, cache: 1];",
            "ISwitch_27_o1[cache: 2] = ",
            "Switch(",
            "IInq26_o1,",
            "IInp16_o1,",
            "\"none\"",
            ") [instance: 27, cache: 1];",
            "buttonDownApproxx = ISwitch_27_o1;",
            "IRcv164_o1[cache: 0] = buttonDownApproxx;",
            "ISwitch_10_o1[cache: 2] = ",
            "Switch(",
            "IRcv161_o1,",
            "IRcv163_o1,",
            "IRcv164_o1",
            ") [instance: 10, cache: 1];",
            "IFormat_14_o1[cache: 2] = ",
            "Format(",
            "\"%s,%s\",",
            "IRcv164_o1,",
            "IRcv163_o1",
            ") [instance: 14, cache: 1];",
            "ISwitch_8_o1[cache: 2] = ",
            "Switch(",
            "ICompute_2_o1,",
            "ISwitch_10_o1,",
            "IFormat_14_o1",
            ") [instance: 8, cache: 1];",
            "IRcv194_o1[cache: 0] = buttonStatex;",
            "IInp17_o1 = buttonUpDensity;",
            "IInq27_o1[cache: 2] = ",
            "Inquire(",
            "IInp17_o1,",
            "\"is null + 1\",",
            "NULL",
            ") [instance: 27, cache: 1];",
            "ISwitch_28_o1[cache: 2] = ",
            "Switch(",
            "IInq27_o1,",
            "IInp17_o1,",
            "1",
            ") [instance: 28, cache: 1];",
            "buttonUpDensityx = ISwitch_28_o1;",
            "IRcv165_o1[cache: 0] = buttonUpDensityx;",
            "IInp18_o1 = buttonDownDensity;",
            "IInq29_o1[cache: 2] = ",
            "Inquire(",
            "IInp18_o1,",
            "\"is null + 1\",",
            "NULL",
            ") [instance: 29, cache: 1];",
            "ISwitch_30_o1[cache: 2] = ",
            "Switch(",
            "IInq29_o1,",
            "IInp18_o1,",
            "1",
            ") [instance: 30, cache: 1];",
            "buttonDownDensityx = ISwitch_30_o1;",
            "IRcv166_o1[cache: 0] = buttonDownDensityx;",
            "ISwitch_11_o1[cache: 2] = ",
            "Switch(",
            "IRcv194_o1,",
            "IRcv165_o1,",
            "IRcv166_o1",
            ") [instance: 11, cache: 1];",
            "IFormat_2_o1[cache: 2] = ",
            "Format(",
            "\"%d,%d\",",
            "IRcv166_o1,",
            "IRcv165_o1",
            ") [instance: 2, cache: 1];",
            "ISwitch_7_o1[cache: 2] = ",
            "Switch(",
            "ICompute_2_o1,",
            "ISwitch_11_o1,",
            "IFormat_2_o1",
            ") [instance: 7, cache: 1];",
            "ISwitch_5_o1[cache: 2] = ",
            "Switch(",
            "ICompute_2_o1,",
            "{\"software\"},",
            "{\"hardware\"}",
            ") [instance: 5, cache: 1];",
            "IOptions_1_o1[cache: 2] = ",
            "Options(",
            "ISwitch_4_o1,",
            "\"send boxes\",",
            "0,",
            "\"cache\",",
            "1,",
            "\"object tag\",",
            "IInq3_o1,",
            "\"ddcamera\",",
            "IRcv40_o1,",
            "\"rendering approximation\",",
            "ISwitch_8_o1,",
            "\"render every\",",
            "ISwitch_7_o1,",
            "\"button state\",",
            "IRcv194_o1,",
            "\"rendering mode\",",
            "ISwitch_5_o1",
            ") [instance: 1, cache: 1];",
            "annotated_object = IOptions_1_o1;",
            "IRcv125_o1[cache: 0] = annotated_object;",
            "IInq37_o1[cache: 2] = ",
            "Inquire(",
            "IRcv125_o1,",
            "\"object tag\",",
            "NULL",
            ") [instance: 37, cache: 1];",
            "IGetGlobal_4_o1[cache: 2],",
            "IGetGlobal_4_o2[cache: 2] = ",
            "GetGlobal(",
            "0,",
            "NULL,",
            "NULL",
            ") [instance: 4, cache: 1];",
            "ICompute_65_o1[cache: 2] = ",
            "Compute(",
            "\"($0!=$1) ? 1: 2\",",
            "IInq37_o1,",
            "IGetGlobal_4_o1",
            ") [instance: 65, cache: 1];",
            "same_object = ICompute_65_o1;",
            "IRcv222_o1[cache: 0] = same_object;",
            "IRcv250_o1[cache: 0] = java_orbit;",
            "ICompute_72_o1[cache: 2] = ",
            "Compute(",
            "\"$0+1\",",
            "IRcv250_o1",
            ") [instance: 72, cache: 1];",
            "IRcv220_o1[cache: 0] = camera_xcvr;",
            "IRcv217_o1[cache: 0] = camera_xcvr;",
            "NewFrom = ICompute_32_o1;",
            "IRcv57_o1[cache: 0] = NewFrom;",
            "IRcv60_o1[cache: 0] = orbitNewRes;",
            "IUpdateCamera_3_o1[cache: 2] = ",
            "UpdateCamera(",
            "IRcv217_o1,",
            "NULL,",
            "IRcv57_o1,",
            "NULL,",
            "IRcv60_o1,",
            "NULL,",
            "NULL,",
            "NULL,",
            "NULL,",
            "NULL",
            ") [instance: 3, cache: 1];",
            "orbit_cam = IUpdateCamera_3_o1;",
            "IRcv251_o1[cache: 0] = orbit_cam;",
            "ISwitch_32_o1[cache: 0] = ",
            "Switch(",
            "ICompute_72_o1,",
            "IRcv220_o1,",
            "IRcv251_o1",
            ") [instance: 32, cache: 1];",
            "camera_iuse = ISwitch_32_o1;",
            "IRcv249_o1[cache: 0] = camera_iuse;",
            "IInq35_o1[cache: 2] = ",
            "Inquire(",
            "IRcv249_o1,",
            "\"object tag\",",
            "NULL",
            ") [instance: 35, cache: 1];",
            "IGetGlobal_2_o1[cache: 2],",
            "IGetGlobal_2_o2[cache: 2] = ",
            "GetGlobal(",
            "0,",
            "NULL,",
            "NULL",
            ") [instance: 2, cache: 1];",
            "ICompute_62_o1[cache: 2] = ",
            "Compute(",
            "\"($0 != $1) ? 1:2\",",
            "IInq35_o1,",
            "IGetGlobal_2_o1",
            ") [instance: 62, cache: 1];",
            "ICompute_63_o1[cache: 2] = ",
            "Compute(",
            "\"(($0==1)||($1==1))?1:2\",",
            "IRcv222_o1,",
            "ICompute_62_o1",
            ") [instance: 63, cache: 1];",
            "same_image = ICompute_63_o1;",
            "IRcv230_o1[cache: 0] = same_image;",
            "IRcv233_o1[cache: 0] = java_orbit;",
            "IGetGlobal_3_o1[cache: 2],",
            "IGetGlobal_3_o2[cache: 2] = ",
            "GetGlobal(",
            "0,",
            "NULL,",
            "NULL",
            ") [instance: 3, cache: 1];",
            "ICompute_64_o1[cache: 2] = ",
            "Compute(",
            "\"($0 != $1) ? 1 : 2\",",
            "IRcv233_o1,",
            "IGetGlobal_3_o1",
            ") [instance: 64, cache: 1];",
            "same_orbit = ICompute_64_o1;",
            "IRcv243_o1[cache: 0] = same_orbit;",
            "ISelect_12_o1[cache: 2] = ",
            "Select(",
            "IRoute_14_o1,",
            "\"imgId\",",
            "NULL",
            ") [instance: 12, cache: 1];",
            "img_id = ISelect_12_o1;",
            "IRcv234_o1[cache: 0] = img_id;",
            "IGetGlobal_5_o1[cache: 2],",
            "IGetGlobal_5_o2[cache: 2] = ",
            "GetGlobal(",
            "-1,",
            "NULL,",
            "NULL",
            ") [instance: 5, cache: 1];",
            "ICompute_66_o1[cache: 2] = ",
            "Compute(",
            "\"($0 != $1) ? 1 : 2\",",
            "IRcv234_o1,",
            "IGetGlobal_5_o1",
            ") [instance: 66, cache: 1];",
            "same_id = ICompute_66_o1;",
            "IRcv242_o1[cache: 0] = same_id;",
            "IRcv235_o1[cache: 0] = java_format;",
            "IGetGlobal_6_o1[cache: 2],",
            "IGetGlobal_6_o2[cache: 2] = ",
            "GetGlobal(",
            "\"\",",
            "NULL,",
            "NULL",
            ") [instance: 6, cache: 1];",
            "ICompute_67_o1[cache: 2] = ",
            "Compute(",
            "\"strcmp($0,$1) ? 1 : 2\",",
            "IRcv235_o1,",
            "IGetGlobal_6_o1",
            ") [instance: 67, cache: 1];",
            "same_format = ICompute_67_o1;",
            "IRcv241_o1[cache: 0] = same_format;",
            "IRcv236_o1[cache: 0] = orbit_delta;",
            "IGetGlobal_7_o1[cache: 2],",
            "IGetGlobal_7_o2[cache: 2] = ",
            "GetGlobal(",
            "0,",
            "NULL,",
            "NULL",
            ") [instance: 7, cache: 1];",
            "ICompute_70_o1[cache: 2] = ",
            "Compute(",
            "\"($0 != $1) ? 1 : 2\",",
            "IRcv236_o1,",
            "IGetGlobal_7_o1",
            ") [instance: 70, cache: 1];",
            "same_delta = ICompute_70_o1;",
            "IRcv240_o1[cache: 0] = same_delta;",
            "IInp41_o1 = interactionMode;",
            "IInq50_o1[cache: 2] = ",
            "Inquire(",
            "IInp41_o1,",
            "\"is null + 1\",",
            "NULL",
            ") [instance: 50, cache: 1];",
            "ISwitch_34_o1[cache: 2] = ",
            "Switch(",
            "IInq50_o1,",
            "IInp41_o1,",
            "\"none\"",
            ") [instance: 34, cache: 1];",
            "imodex = ISwitch_34_o1;",
            "IRcv282_o1[cache: 0] = imodex;",
            "IGetGlobal_11_o1[cache: 2],",
            "IGetGlobal_11_o2[cache: 2] = ",
            "GetGlobal(",
            "\"\",",
            "NULL,",
            "NULL",
            ") [instance: 11, cache: 1];",
            "ICompute_76_o1[cache: 2] = ",
            "Compute(",
            "\"strcmp($0,$1) ? 1 : 2\",",
            "IRcv282_o1,",
            "IGetGlobal_11_o1",
            ") [instance: 76, cache: 1];",
            "same_mode = ICompute_76_o1;",
            "IRcv283_o1[cache: 0] = same_mode;",
            "ICompute_69_o1[cache: 2] = ",
            "Compute(",
            "\"(($0==1)||($1==1)||($2==1)||($3==1)||($4==1))? 1: 2\",",
            "IRcv243_o1,",
            "IRcv242_o1,",
            "IRcv241_o1,",
            "IRcv240_o1,",
            "IRcv283_o1",
            ") [instance: 69, cache: 1];",
            "same_options = ICompute_69_o1;",
            "IRcv226_o1[cache: 0] = same_options;",
            "ICompute_59_o1[cache: 2] = ",
            "Compute(",
            "\"(($1==1)||($2==1) ? (($0==1)?2:1) : 0)\",",
            "IRcv204_o1,",
            "IRcv230_o1,",
            "IRcv226_o1",
            ") [instance: 59, cache: 1];",
            "IRcv246_o1[cache: 0] = same_image;",
            "IRcv247_o1[cache: 0] = same_options;",
            "ICompute_71_o1[cache: 2] = ",
            "Compute(",
            "\"(($0==1)||($1==1)) ?1:0\",",
            "IRcv246_o1,",
            "IRcv247_o1",
            ") [instance: 71, cache: 1];",
            "ISelect_15_o1[cache: 2] = ",
            "Select(",
            "IRoute_14_o1,",
            "\"groupName\",",
            "NULL",
            ") [instance: 15, cache: 1];",
            "groupName = ISelect_15_o1;",
            "IRcv267_o1[cache: 0] = groupName;",
            "IGetGlobal_8_o1[cache: 2],",
            "IGetGlobal_8_o2[cache: 2] = ",
            "GetGlobal(",
            "\"untitled\",",
            "NULL,",
            "NULL",
            ") [instance: 8, cache: 1];",
            "ICompute_73_o1[cache: 2] = ",
            "Compute(",
            "\"strcmp($0,$1) != 0?1:2\",",
            "IRcv267_o1,",
            "IGetGlobal_8_o1",
            ") [instance: 73, cache: 1];",
            "ISelect_14_o1[cache: 2] = ",
            "Select(",
            "IRoute_14_o1,",
            "\"cacheCount\",",
            "NULL",
            ") [instance: 14, cache: 1];",
            "cache_count = ISelect_14_o1;",
            "IRcv268_o1[cache: 0] = cache_count;",
            "IGetGlobal_9_o1[cache: 2],",
            "IGetGlobal_9_o2[cache: 2] = ",
            "GetGlobal(",
            "0,",
            "NULL,",
            "NULL",
            ") [instance: 9, cache: 1];",
            "ICompute_74_o1[cache: 2] = ",
            "Compute(",
            "\"($0 != $1) ? 1 : 2\",",
            "IRcv268_o1,",
            "IGetGlobal_9_o1",
            ") [instance: 74, cache: 1];",
            "IRcv284_o1[cache: 0] = same_image;",
            "IRcv285_o1[cache: 0] = same_options;",
            "ICompute_77_o1[cache: 2] = ",
            "Compute(",
            "\"(($0==1)||($1==1)) ?1:0\",",
            "IRcv284_o1,",
            "IRcv285_o1",
            ") [instance: 77, cache: 1];",
            "IRcv290_o1[cache: 0] = objectx;",
            "IRoute_15_o1[cache: 2],",
            "IRoute_15_o2[cache: 2] = ",
            "Route(",
            "IInq53_o1,",
            "IRcv290_o1",
            ") [instance: 15, cache: 1];",
            "IRoute_16_o1[cache: 2],",
            "IRoute_16_o2[cache: 2] = ",
            "Route(",
            "ICompute_77_o1,",
            "IRoute_15_o1",
            ") [instance: 16, cache: 1];",
            "DXExporter = IRoute_16_o1;",
            "IRcv288_o1[cache: 0] = DXExporter;",
            "ISelect_8_o1[cache: 2] = ",
            "Select(",
            "IRoute_14_o1,",
            "\"file\",",
            "NULL",
            ") [instance: 8, cache: 1];",
            "java_file = ISelect_8_o1;",
            "IRcv133_o1[cache: 0] = java_file;",
            "IInq21_o1[cache: 2] = ",
            "Inquire(",
            "IRcv158_o1,",
            "\"is null+1\",",
            "NULL",
            ") [instance: 21, cache: 1];",
            "ISwitch_22_o1[cache: 2] = ",
            "Switch(",
            "IInq21_o1,",
            "ICompute_56_o1,",
            "0",
            ") [instance: 22, cache: 1];",
            "seq_number = ISwitch_22_o1;",
            "IRcv134_o1[cache: 0] = seq_number;",
            "ISwitch_23_o1[cache: 2] = ",
            "Switch(",
            "IInq21_o1,",
            "ICompute_57_o1,",
            "0",
            ") [instance: 23, cache: 1];",
            "loop_number = ISwitch_23_o1;",
            "IRcv98_o1[cache: 0] = loop_number;",
            "IFormat_1_o1[cache: 2] = ",
            "Format(",
            "\"%s.%d.%d\",",
            "IRcv133_o1,",
            "IRcv134_o1,",
            "IRcv98_o1",
            ") [instance: 1, cache: 1];",
            "base_name = IFormat_1_o1;",
            "IRcv289_o1[cache: 0] = base_name;",
            "IDXExport_1_o1[cache: 2] = ",
            "DXExport(",
            "IRcv288_o1,",
            "IRcv289_o1",
            ") [instance: 1, cache: 1];",
            "record_code = ICompute_3_o1;",
            "IRcv172_o1[cache: 0] = record_code;",
            "IRoute_1_o1[cache: 2],",
            "IRoute_1_o2[cache: 2] = ",
            "Route(",
            "ICompute_7_o1,",
            "IRcv125_o1",
            ") [instance: 1, cache: 1];",
            "IRoute_6_o1[cache: 2],",
            "IRoute_6_o2[cache: 2],",
            "IRoute_6_o3[cache: 2],",
            "IRoute_6_o4[cache: 2] = ",
            "Route(",
            "IRcv172_o1,",
            "IRoute_1_o1",
            ") [instance: 6, cache: 1];",
            "IRcv50_o1[cache: 0] = camera_xcvr;",
            "IInp3_o1 = where;",
            "wherex = IInp3_o1;",
            "IRcv51_o1[cache: 0] = wherex;",
            "IInp23_o1 = throttle;",
            "throttlex = IInp23_o1;",
            "IRcv52_o1[cache: 0] = throttlex;",
            "IDisplay_1_o1[cache: 2] = ",
            "Display(",
            "IRoute_6_o1,",
            "IRcv50_o1,",
            "IRcv51_o1,",
            "IRcv52_o1,",
            "NULL,",
            "NULL,",
            "NULL,",
            "NULL",
            ") [instance: 1, cache: 1];",
            "IRender_1_o1[cache: 2] = ",
            "Render(",
            "IRoute_6_o2,",
            "IRcv50_o1,",
            "NULL",
            ") [instance: 1, cache: 1];",
            "IRcv173_o1[cache: 0] = throttlex;",
            "IDisplay_2_o1[cache: 2] = ",
            "Display(",
            "IRender_1_o1,",
            "NULL,",
            "IRcv51_o1,",
            "IRcv173_o1,",
            "NULL,",
            "NULL,",
            "NULL,",
            "NULL",
            ") [instance: 2, cache: 1];",
            "IRcv177_o1[cache: 0] = camera_xcvr;",
            "IRcv178_o1[cache: 0] = wherex;",
            "IRcv179_o1[cache: 0] = throttlex;",
            "IDisplay_3_o1[cache: 2] = ",
            "Display(",
            "IRoute_6_o3,",
            "IRcv177_o1,",
            "IRcv178_o1,",
            "IRcv179_o1,",
            "NULL,",
            "NULL,",
            "NULL,",
            "NULL",
            ") [instance: 3, cache: 1];",
            "IRcv180_o1[cache: 0] = camera_xcvr;",
            "IRcv181_o1[cache: 0] = wherex;",
            "IRcv182_o1[cache: 0] = throttlex;",
            "IDisplay_4_o1[cache: 2] = ",
            "Display(",
            "IRoute_6_o4,",
            "IRcv180_o1,",
            "IRcv181_o1,",
            "IRcv182_o1,",
            "NULL,",
            "NULL,",
            "NULL,",
            "NULL",
            ") [instance: 4, cache: 1];",
            "IInp1_o1 = id;",
            "idx = IInp1_o1;",
            "IRcv147_o1[cache: 0] = idx;",
            "IRcv258_o1[cache: 0] = img_id;",
            "IRcv259_o1[cache: 0] = resetx;",
            "IRcv255_o1[cache: 0] = camera_xcvr;",
            "java_exporter = IRoute_1_o2;",
            "IRcv130_o1[cache: 0] = java_exporter;",
            "IRoute_2_o1[cache: 2],",
            "IRoute_2_o2[cache: 2] = ",
            "Route(",
            "ICompute_78_o1,",
            "IRcv130_o1",
            ") [instance: 2, cache: 1];",
            "IRoute_8_o1[cache: 2],",
            "IRoute_8_o2[cache: 2] = ",
            "Route(",
            "ICompute_59_o1,",
            "IRoute_2_o1",
            ") [instance: 8, cache: 1];",
            "gifexporter = IRoute_8_o1;",
            "IRcv146_o1[cache: 0] = gifexporter;",
            "IRcv139_o1[cache: 0] = base_name;",
            "IRcv138_o1[cache: 0] = camera_xcvr;",
            "IRcv292_o1[cache: 0] = java_format;",
            "IImageExport_1_o1 = ",
            "ImageExport(",
            "IRcv146_o1,",
            "IRcv139_o1,",
            "IRcv138_o1,",
            "IRcv292_o1",
            ") [instance: 1, cache: 1];",
            "gif_data_drive = IImageExport_1_o1;",
            "IRcv266_o1[cache: 0] = gif_data_drive;",
            "IInq45_o1[cache: 2] = ",
            "Inquire(",
            "IRcv255_o1,",
            "\"camera perspective + 1\",",
            "IRcv266_o1",
            ") [instance: 45, cache: 1];",
            "IRoute_11_o1[cache: 0],",
            "IRoute_11_o2[cache: 0] = ",
            "Route(",
            "IInq45_o1,",
            "IRcv255_o1",
            ") [instance: 11, cache: 1];",
            "ocam = IRoute_11_o1;",
            "IRcv260_o1[cache: 0] = ocam;",
            "IInq40_o1[cache: 2] = ",
            "Inquire(",
            "IRcv260_o1,",
            "\"camera width\",",
            "NULL",
            ") [instance: 40, cache: 1];",
            "IInq51_o1[cache: 2] = ",
            "Inquire(",
            "IRcv260_o1,",
            "\"camera to\",",
            "NULL",
            ") [instance: 51, cache: 1];",
            "IInq42_o1[cache: 2] = ",
            "Inquire(",
            "IRcv260_o1,",
            "\"camera from\",",
            "NULL",
            ") [instance: 42, cache: 1];",
            "IInq43_o1[cache: 2] = ",
            "Inquire(",
            "IRcv260_o1,",
            "\"camera up\",",
            "NULL",
            ") [instance: 43, cache: 1];",
            "IRcv278_o1[cache: 0] = imodex;",
            "IRcv257_o1[cache: 0] = gif_data_drive;",
            "IFormat_20_o1[cache: 2] = ",
            "Format(",
            "\"imgId=%d; reset=%d; width=%.4f; to=%.4f; from=%.4f; up=%.4f; orbit=0; mode=%s; show=%s;\",",
            "IRcv258_o1,",
            "IRcv259_o1,",
            "IInq40_o1,",
            "IInq51_o1,",
            "IInq42_o1,",
            "IInq43_o1,",
            "IRcv278_o1,",
            "IRcv257_o1",
            ") [instance: 20, cache: 1];",
            "Echo(",
            "IRcv147_o1,",
            "IFormat_20_o1",
            ") [instance: 1, cache: 1];",
            "IRoute_4_o1[cache: 2],",
            "IRoute_4_o2[cache: 2] = ",
            "Route(",
            "ICompute_58_o1,",
            "NULL",
            ") [instance: 4, cache: 1];",
            "IFormat_13_o1[cache: 2] = ",
            "Format(",
            "\"Unrecognized Format: %s\",",
            "IRcv131_o1,",
            "IRoute_4_o1",
            ") [instance: 13, cache: 1];",
            "IFormat_26_o1[cache: 2] = ",
            "Format(",
            "\"format inquiries: %d %d %d\",",
            "IInq22_o1,",
            "ICompute_78_o1,",
            "IInq53_o1",
            ") [instance: 26, cache: 1];",
            "Echo(",
            "IFormat_13_o1,",
            "IFormat_26_o1",
            ") [instance: 3, cache: 1];",
            "IRcv205_o1[cache: 0] = idx;",
            "IRcv206_o1[cache: 0] = img_id;",
            "orbitexporter = IRoute_8_o2;",
            "IRcv213_o1[cache: 0] = orbitexporter;",
            "IRender_3_o1[cache: 2] = ",
            "Render(",
            "IRcv213_o1,",
            "IUpdateCamera_3_o1,",
            "NULL",
            ") [instance: 3, cache: 1];",
            "orbitedImage = IRender_3_o1;",
            "IRcv211_o1[cache: 0] = orbitedImage;",
            "IRcv275_o1[cache: 0] = java_file;",
            "IRcv276_o1[cache: 0] = seq_number;",
            "IFormat_24_o1[cache: 2] = ",
            "Format(",
            "\"%s.%d.%d\",",
            "IRcv275_o1,",
            "IRcv276_o1,",
            "IForEachN_1_o1",
            ") [instance: 24, cache: 1];",
            "IRcv209_o1[cache: 0] = camera_xcvr;",
            "IImageExport_2_o1 = ",
            "ImageExport(",
            "IRcv211_o1,",
            "IFormat_24_o1,",
            "IRcv209_o1,",
            "NULL",
            ") [instance: 2, cache: 1];",
            "IFormat_17_o1[cache: 2] = ",
            "Format(",
            "\"imgId=%d; orbit=1; show=%s;\",",
            "IRcv206_o1,",
            "IImageExport_2_o1",
            ") [instance: 17, cache: 1];",
            "Echo(",
            "IRcv205_o1,",
            "IFormat_17_o1",
            ") [instance: 5, cache: 1];",
            "IRcv244_o1[cache: 0] = idx;",
            "IRcv245_o1[cache: 0] = img_id;",
            "IRoute_3_o1[cache: 2],",
            "IRoute_3_o2[cache: 2] = ",
            "Route(",
            "IInq22_o1,",
            "IRcv130_o1",
            ") [instance: 3, cache: 1];",
            "IRoute_10_o1[cache: 2],",
            "IRoute_10_o2[cache: 2] = ",
            "Route(",
            "ICompute_71_o1,",
            "IRoute_3_o1",
            ") [instance: 10, cache: 1];",
            "wrlexporter = IRoute_10_o1;",
            "IRcv157_o1[cache: 0] = wrlexporter;",
            "IRcv153_o1[cache: 0] = base_name;",
            "IVRMLExport_1_o1[cache: 2] = ",
            "VRMLExport(",
            "IRcv157_o1,",
            "IRcv153_o1",
            ") [instance: 1, cache: 1];",
            "IFormat_19_o1[cache: 2] = ",
            "Format(",
            "\"imgId=%d; orbit=0; show=%s;\",",
            "IRcv245_o1,",
            "IVRMLExport_1_o1",
            ") [instance: 19, cache: 1];",
            "Echo(",
            "IRcv244_o1,",
            "IFormat_19_o1",
            ") [instance: 6, cache: 1];",
            "IRcv261_o1[cache: 0] = idx;",
            "IRcv262_o1[cache: 0] = img_id;",
            "IRcv263_o1[cache: 0] = resetx;",
            "pcam = IRoute_11_o2;",
            "IRcv264_o1[cache: 0] = pcam;",
            "IInq46_o1[cache: 2] = ",
            "Inquire(",
            "IRcv264_o1,",
            "\"camera angle\",",
            "NULL",
            ") [instance: 46, cache: 1];",
            "IInq52_o1[cache: 2] = ",
            "Inquire(",
            "IRcv264_o1,",
            "\"camera to\",",
            "NULL",
            ") [instance: 52, cache: 1];",
            "IInq48_o1[cache: 2] = ",
            "Inquire(",
            "IRcv264_o1,",
            "\"camera from\",",
            "NULL",
            ") [instance: 48, cache: 1];",
            "IInq49_o1[cache: 2] = ",
            "Inquire(",
            "IRcv264_o1,",
            "\"camera up\",",
            "NULL",
            ") [instance: 49, cache: 1];",
            "IRcv279_o1[cache: 0] = imodex;",
            "IRcv265_o1[cache: 0] = gif_data_drive;",
            "IFormat_21_o1[cache: 2] = ",
            "Format(",
            "\"imgId=%d; reset=%d; angle=%.4f; to=%.4f; from=%.4f; up=%.4f; orbit=0; mode=%s; show=%s;\",",
            "IRcv262_o1,",
            "IRcv263_o1,",
            "IInq46_o1,",
            "IInq52_o1,",
            "IInq48_o1,",
            "IInq49_o1,",
            "IRcv279_o1,",
            "IRcv265_o1",
            ") [instance: 21, cache: 1];",
            "Echo(",
            "IRcv261_o1,",
            "IFormat_21_o1",
            ") [instance: 7, cache: 1];",
            "IRcv273_o1[cache: 0] = idx;",
            "same_group = ICompute_73_o1;",
            "IRcv269_o1[cache: 0] = same_group;",
            "IRcv270_o1[cache: 0] = groupName;",
            "IRoute_12_o1[cache: 0],",
            "IRoute_12_o2[cache: 0] = ",
            "Route(",
            "IRcv269_o1,",
            "IRcv270_o1",
            ") [instance: 12, cache: 1];",
            "IFormat_22_o1[cache: 2] = ",
            "Format(",
            "\"group=%s\",",
            "IRoute_12_o1",
            ") [instance: 22, cache: 1];",
            "Echo(",
            "IRcv273_o1,",
            "IFormat_22_o1",
            ") [instance: 10, cache: 1];",
            "IRcv274_o1[cache: 0] = idx;",
            "same_cache = ICompute_74_o1;",
            "IRcv271_o1[cache: 0] = same_cache;",
            "IRcv272_o1[cache: 0] = cache_count;",
            "IRoute_13_o1[cache: 0],",
            "IRoute_13_o2[cache: 0] = ",
            "Route(",
            "IRcv271_o1,",
            "IRcv272_o1",
            ") [instance: 13, cache: 1];",
            "IFormat_23_o1[cache: 2] = ",
            "Format(",
            "\"cache=%d\",",
            "IRoute_13_o1",
            ") [instance: 23, cache: 1];",
            "Echo(",
            "IRcv274_o1,",
            "IFormat_23_o1",
            ") [instance: 11, cache: 1];",
            "IRcv286_o1[cache: 0] = idx;",
            "IRcv287_o1[cache: 0] = img_id;",
            "IFormat_25_o1[cache: 2] = ",
            "Format(",
            "\"imgId=%d; orbit=0; show=%s;\",",
            "IRcv287_o1,",
            "IDXExport_1_o1",
            ") [instance: 25, cache: 1];",
            "Echo(",
            "IRcv286_o1,",
            "IFormat_25_o1",
            ") [instance: 12, cache: 1];",
            "IRcv70_o1[cache: 0] = idx;",
            "IRcv99_o1[cache: 0] = bkgndColor;",
            "IRcv110_o1[cache: 0] = throttlex;",
            "IRcv195_o1[cache: 0] = recEnablex;",
            "IInp25_o1 = recFile;",
            "recFilex = IInp25_o1;",
            "IRcv196_o1[cache: 0] = recFilex;",
            "IInp26_o1 = recFormat;",
            "recFormatx = IInp26_o1;",
            "IRcv197_o1[cache: 0] = recFormatx;",
            "IRcv198_o1[cache: 0] = recRes;",
            "IRcv199_o1[cache: 0] = recAsp;",
            "IRcv91_o1[cache: 0] = aaenable;",
            "IRcv72_o1[cache: 0] = aalabels;",
            "IRcv73_o1[cache: 0] = aaticks;",
            "IRcv78_o1[cache: 0] = aacorners;",
            "IRcv77_o1[cache: 0] = aaframe;",
            "IRcv76_o1[cache: 0] = aaadjust;",
            "IRcv75_o1[cache: 0] = aacursor;",
            "IRcv74_o1[cache: 0] = aagrid;",
            "IRcv82_o1[cache: 0] = aacolors;",
            "IRcv81_o1[cache: 0] = annotation;",
            "IRcv80_o1[cache: 0] = aalabelscale;",
            "IRcv116_o1[cache: 0] = aafont;",
            "IRcv83_o1[cache: 0] = AAxTickLocs;",
            "IRcv85_o1[cache: 0] = aayTickLocs;",
            "IRcv84_o1[cache: 0] = AAzTickLocs;",
            "IRcv86_o1[cache: 0] = AAxTickLabels;",
            "IRcv88_o1[cache: 0] = AAyTickLabels;",
            "IRcv87_o1[cache: 0] = AAzTickLabels;",
            "IRcv118_o1[cache: 0] = imodex;",
            "IInp42_o1 = title;",
            "titlex = IInp42_o1;",
            "IRcv117_o1[cache: 0] = titlex;",
            "IRcv93_o1[cache: 0] = renderModex;",
            "IRcv96_o1[cache: 0] = buttonUpApproxx;",
            "IRcv97_o1[cache: 0] = buttonDownApproxx;",
            "IRcv94_o1[cache: 0] = buttonUpDensityx;",
            "IRcv95_o1[cache: 0] = buttonDownDensityx;",
            "ImageMessage(",
            "IRcv70_o1,",
            "IRcv99_o1,",
            "IRcv110_o1,",
            "IRcv195_o1,",
            "IRcv196_o1,",
            "IRcv197_o1,",
            "IRcv198_o1,",
            "IRcv199_o1,",
            "IRcv91_o1,",
            "IRcv72_o1,",
            "IRcv73_o1,",
            "IRcv78_o1,",
            "IRcv77_o1,",
            "IRcv76_o1,",
            "IRcv75_o1,",
            "IRcv74_o1,",
            "IRcv82_o1,",
            "IRcv81_o1,",
            "IRcv80_o1,",
            "IRcv116_o1,",
            "IRcv83_o1,",
            "IRcv85_o1,",
            "IRcv84_o1,",
            "IRcv86_o1,",
            "IRcv88_o1,",
            "IRcv87_o1,",
            "IRcv118_o1,",
            "IRcv117_o1,",
            "IRcv93_o1,",
            "IRcv96_o1,",
            "IRcv97_o1,",
            "IRcv94_o1,",
            "IRcv95_o1",
            ") [instance: 1, cache: 1];",
            "IInp13_o1 = options;",
            "camera = ISwitch_2_o1;",
            "object = IRcv125_o1;",
            "Where = IRcv51_o1;",
            "IReadImageWindow_1_o1[cache: 2] = ",
            "ReadImageWindow(",
            "IDisplay_3_o1",
            ") [instance: 1, cache: 1];",
            "IRcv175_o1[cache: 0] = recFormatx;",
            "IRcv176_o1[cache: 0] = recFilex;",
            "IRcv183_o1[cache: 0] = recFilex;",
            "IRcv184_o1[cache: 0] = recFormatx;",
            "IRcv186_o1[cache: 0] = camera_xcvr;",
            "IRcv187_o1[cache: 0] = recRes;",
            "IRcv188_o1[cache: 0] = recAsp;",
            "IUpdateCamera_2_o1[cache: 2] = ",
            "UpdateCamera(",
            "IRcv186_o1,",
            "NULL,",
            "NULL,",
            "NULL,",
            "IRcv187_o1,",
            "IRcv188_o1,",
            "NULL,",
            "NULL,",
            "NULL,",
            "NULL",
            ") [instance: 2, cache: 1];",
            "record_camera = IUpdateCamera_2_o1;",
            "IRcv185_o1[cache: 0] = record_camera;",
            "IRcv190_o1[cache: 0] = annotated_object;",
            "IScaleScreen_2_o1[cache: 2],",
            "IScaleScreen_2_o2[cache: 2] = ",
            "ScaleScreen(",
            "IRcv190_o1,",
            "NULL,",
            "IRcv187_o1,",
            "IRcv186_o1",
            ") [instance: 2, cache: 1];",
            "record_object = IScaleScreen_2_o1;",
            "IRcv191_o1[cache: 0] = record_object;",
            "IRcv193_o1[cache: 0] = record_code;",
            "IRender_2_o1[cache: 2] = ",
            "Render(",
            "IRcv191_o1,",
            "IRcv185_o1,",
            "NULL",
            ") [instance: 2, cache: 1];",
            "IRoute_7_o1[cache: 2],",
            "IRoute_7_o2[cache: 2],",
            "IRoute_7_o3[cache: 2],",
            "IRoute_7_o4[cache: 2] = ",
            "Route(",
            "IRcv193_o1,",
            "IRender_2_o1",
            ") [instance: 7, cache: 1];",
            "ISelect_10_o1[cache: 0] = ",
            "Select(",
            "IRoute_14_o1,",
            "\"javaid\",",
            "NULL",
            ") [instance: 10, cache: 1];",
            "SetGlobal(",
            "IInq35_o1,",
            "IGetGlobal_2_o2,",
            "NULL",
            ") [instance: 2, cache: 1];",
            "SetGlobal(",
            "IRcv233_o1,",
            "IGetGlobal_3_o2,",
            "NULL",
            ") [instance: 3, cache: 1];",
            "SetGlobal(",
            "IInq37_o1,",
            "IGetGlobal_4_o2,",
            "NULL",
            ") [instance: 4, cache: 1];",
            "SetGlobal(",
            "IRcv234_o1,",
            "IGetGlobal_5_o2,",
            "NULL",
            ") [instance: 5, cache: 1];",
            "SetGlobal(",
            "IRcv235_o1,",
            "IGetGlobal_6_o2,",
            "NULL",
            ") [instance: 6, cache: 1];",
            "SetGlobal(",
            "IRcv236_o1,",
            "IGetGlobal_7_o2,",
            "NULL",
            ") [instance: 7, cache: 1];",
            "SetGlobal(",
            "IRcv267_o1,",
            "IGetGlobal_8_o2,",
            "NULL",
            ") [instance: 8, cache: 1];",
            "SetGlobal(",
            "IRcv268_o1,",
            "IGetGlobal_9_o2,",
            "NULL",
            ") [instance: 9, cache: 1];",
            "SetGlobal(",
            "IRcv282_o1,",
            "IGetGlobal_11_o2,",
            "NULL",
            ") [instance: 11, cache: 1];",
            "options = IInp13_o1;",
            "java_id = ISelect_10_o1;",
            "WriteImage(",
            "IRender_1_o1,",
            "IRcv176_o1,",
            "IRcv175_o1,",
            "NULL",
            ") [instance: 2, cache: 1];",
            "WriteImage(",
            "IReadImageWindow_1_o1,",
            "IRcv176_o1,",
            "IRcv175_o1,",
            "NULL",
            ") [instance: 3, cache: 1];",
            "WriteImage(",
            "IRoute_7_o4,",
            "IRcv183_o1,",
            "IRcv184_o1,",
            "NULL",
            ") [instance: 4, cache: 1];"
        };
        protected static String[] DXMacroTxt = new String[] {
            "macro DXExport(",
            " object",
            ",base_name",
            ") -> (",
            " file_written",
            ") {",
            "DXExport_Inp7_o1 = object;",
            "DXExport_Inp8_o1 = base_name;",
            "Export(",
            "DXExport_Inp7_o1,",
            "DXExport_Inp8_o1,",
            "\"dx text follows\"",
            ") [instance: 1, cache: 1];",
            "DXExport_Format_8_o1[cache: 2] = ",
            "Format(",
            "\"%s.dx\",",
            "DXExport_Inp8_o1,",
            "NULL",
            ") [instance: 8, cache: 1];",
            "file_written = DXExport_Format_8_o1;",
            "}"
        };

        #endregion

        // The height which isn't stored in the parameter list.
        protected int height;

        // A boolean which says whether we're translating old values
        // into new ones.
        protected bool translating;

        // Fields and members to control the image macro.  When a parameter
        // that affects the image macro changes, macroDirty should be set
        // indicating that when ready, the system should update the macro.
        protected bool macroDirty;
        protected virtual bool sendMacro(DXPacketIF pif)
        {
            Object cbdata = null;
            PacketIF.PacketIFCallback cb = pif.getEchoCallback(ref cbdata);
            StreamWriter sw = pif.getStreamWriter();
            bool viasocket = true;

            if (getNetwork().isJavified())
            {
                pif.sendMacroStart();
                FormatMacro(sw, cb, cbdata, ImageNode.GifMacroTxt, viasocket);
                pif.sendMacroEnd();

                pif.sendMacroStart();
                FormatMacro(sw, cb, cbdata, ImageNode.VrmlMacroTxt, viasocket);
                pif.sendMacroEnd();

                pif.sendMacroStart();
                FormatMacro(sw, cb, cbdata, ImageNode.DXMacroTxt, viasocket);
                pif.sendMacroEnd();
            }

            pif.sendMacroStart();
            bool sts = printMacro(pif.getStreamWriter(), cb, cbdata, true);
            pif.sendMacroEnd();

            return sts;
        }
        protected bool printMacro(StreamWriter sw, PacketIF.PacketIFCallback pif,
            Object callbackData, bool viasocket)
        {
            Cacheability cacheability = InternalCacheability;
            int cacheflag = (cacheability == Cacheability.InternalsNotCached) ? 0 :
                (cacheability == Cacheability.InternalsFullyCached) ? 1 : 2;

            // If the network is intended for use under DXServer use the
            // new image macro.  Using the old image macro is a cheap way
            // of avoiding bugs in the new image macro.  A better way
            // to handle this is to make sure the new one doesn't have any
            // bugs in it.  Problem is the new is so big that it will
            // probably be a performance hit.

            if (getNetwork().isJavified())
            {
                FormatMacro(sw, pif, callbackData, ImageNode.ImageMacroTxt, viasocket);
            }
            else
            {
                String str = "macro Image(\n" +
                    "        id,\n" +
                    "        object,\n" +
                    "        where,\n" +
                    "        useVector,\n" +
                    "        to,\n" +
                    "        from,\n" +
                    "        width,\n" +
                    "        resolution,\n" +
                    "        aspect,\n" +
                    "        up,\n" +
                    "        viewAngle,\n" +
                    "        perspective,\n" +
                    "        options,\n" +
                    "        buttonState = 1,\n" +
                    "        buttonUpApprox = \"none\",\n" +
                    "        buttonDownApprox = \"none\",\n" +
                    "        buttonUpDensity = 1,\n" +
                    "        buttonDownDensity = 1,\n" +
                    "        renderMode = 0,\n";
                SendString(callbackData, pif, sw, str, viasocket);
                str = "        defaultCamera,\n" +
                    "        reset,\n" +
                    "        backgroundColor,\n" +
                    "        throttle,\n" +
                    "        RECenable = 0,\n" +
                    "        RECfile,\n" +
                    "        RECformat,\n" +
                    "        RECresolution,\n" +
                    "        RECaspect,\n" +
                    "        AAenable = 0,\n" +
                    "        AAlabels,\n" +
                    "        AAticks,\n" +
                    "        AAcorners,\n" +
                    "        AAframe,\n" +
                    "        AAadjust,\n" +
                    "        AAcursor,\n" +
                    "        AAgrid,\n" +
                    "        AAcolors,\n" +
                    "        AAannotation,\n" +
                    "        AAlabelscale,\n";
                SendString(callbackData, pif, sw, str, viasocket);
                str = "        AAfont,\n" +
                    "        interactionMode,\n" +
                    "        title,\n" +
                    "        AAxTickLocs,\n" +
                    "        AAyTickLocs,\n" +
                    "        AAzTickLocs,\n" +
                    "        AAxTickLabels,\n" +
                    "        AAyTickLabels,\n" +
                    "        AAzTickLabels,\n" +
                    "        webOptions) -> (\n" +
                    "        object,\n" +
                    "        camera,\n" +
                    "        where)\n{\n";
                SendString(callbackData, pif, sw, str, viasocket);

                // Begin macro body.
                str = "    ImageMessage(\n" + 
                    "        id,\n" + 
                    "        backgroundColor,\n" + 
                    "        throttle,\n" + 
                    "        RECenable,\n" + 
                    "        RECfile,\n" + 
                    "        RECformat,\n" + 
                    "        RECresolution,\n" + 
                    "        RECaspect,\n" + 
                    "        AAenable,\n" + 
                    "        AAlabels,\n" + 
                    "        AAticks,\n" + 
                    "        AAcorners,\n" + 
                    "        AAframe,\n" + 
                    "        AAadjust,\n" + 
                    "        AAcursor,\n" + 
                    "        AAgrid,\n" + 
                    "        AAcolors,\n" + 
                    "        AAannotation,\n" + 
                    "        AAlabelscale,\n";
                SendString(callbackData, pif, sw, str, viasocket);

                str = "        AAfont,\n" + 
                    "        AAxTickLocs,\n" + 
                    "        AAyTickLocs,\n" + 
                    "        AAzTickLocs,\n" + 
                    "        AAxTickLabels,\n" + 
                    "        AAyTickLabels,\n" + 
                    "        AAzTickLabels,\n" + 
                    "        interactionMode,\n" + 
                    "        title,\n" + 
                    "        renderMode,\n" + 
                    "        buttonUpApprox,\n" + 
                    "        buttonDownApprox,\n" + 
                    "        buttonUpDensity,\n" + 
                    String.Format("        buttonDownDensity) [instance: 1, cache: {0}];\n", cacheflag);
                SendString(callbackData, pif, sw, str, viasocket);

                // Generate a call to Camera or AutoCamera module.
                str = "    autoCamera =\n" + 
	                "        AutoCamera(\n" + 
	                "            object,\n" + 
	                "            \"front\",\n" + 
	                "            object,\n" + 
	                "            resolution,\n" + 
	                "            aspect,\n" + 
	                "            [0,1,0],\n" + 
	                "            perspective,\n" + 
	                "            viewAngle,\n" + 
	                String.Format("            backgroundColor) [instance: 1, cache: {0}];\n", cacheflag);
                SendString(callbackData, pif, sw, str, viasocket);

                str = "    realCamera =\n" + 
	                "        Camera(\n" + 
	                "            to,\n" + 
	                "            from,\n" + 
	                "            width,\n" + 
	                "            resolution,\n" + 
	                "            aspect,\n" + 
	                "            up,\n" + 
	                "            perspective,\n" + 
	                "            viewAngle,\n" + 
	                String.Format("            backgroundColor) [instance: 1, cache: {0}];\n", cacheflag);
                SendString(callbackData, pif, sw, str, viasocket);

                str = "    coloredDefaultCamera = \n" + 
	                "	 UpdateCamera(defaultCamera,\n" + 
	                String.Format("            background=backgroundColor) [instance: 1, cache: {0}];\n", cacheflag) +
                    "    nullDefaultCamera =\n" + 
	                "        Inquire(defaultCamera,\n" + 
	                String.Format("            \"is null + 1\") [instance: 1, cache: {0}];\n", cacheflag);
                SendString(callbackData, pif, sw, str, viasocket);

                str = "    resetCamera =\n" + 
	                "        Switch(\n" + 
	                "            nullDefaultCamera,\n" + 
	                "            coloredDefaultCamera,\n" + 
	                String.Format("            autoCamera) [instance: 1, cache: {0}];\n", cacheflag) +
	                "    resetNull = \n" + 
	                "        Inquire(\n" + 
	                "            reset,\n" + 
	                String.Format("            \"is null + 1\") [instance: 2, cache: {0}];\n", cacheflag);
                SendString(callbackData, pif, sw, str, viasocket);

                str = "    reset =\n" + 
	                "        Switch(\n" + 
	                "            resetNull,\n" + 
	                "            reset,\n" + 
	                String.Format("            0) [instance: 2, cache: {0}];\n", cacheflag) +
	                "    whichCamera =\n" + 
	                "        Compute(\n" + 
	                "            \"($0 != 0 || $1 == 0) ? 1 : 2\",\n" + 
	                "            reset,\n" + 
	                String.Format("            useVector) [instance: 1, cache: {0}];\n", cacheflag) +
                    "    camera = Switch(\n" + 
	                "            whichCamera,\n" + 
	                "            resetCamera,\n" + 
	                String.Format("            realCamera) [instance: 3, cache: {0}];\n", cacheflag);
                SendString(callbackData, pif, sw, str, viasocket);

	            /*
	             * Generate a call to AutoAxes module.
	             */
	
                str = "    AAobject =\n" + 
	                "        AutoAxes(\n" + 
	                "            object,\n" + 
	                "            camera,\n" + 
	                "            AAlabels,\n" + 
	                "            AAticks,\n" + 
	                "            AAcorners,\n" + 
	                "            AAframe,\n" + 
	                "            AAadjust,\n" + 
	                "            AAcursor,\n" + 
	                "            AAgrid,\n" + 
	                "            AAcolors,\n" + 
	                "            AAannotation,\n" + 
	                "            AAlabelscale,\n" + 
	                "            AAfont,\n" + 
	                "            AAxTickLocs,\n" + 
	                "            AAyTickLocs,\n" + 
	                "            AAzTickLocs,\n" + 
	                "            AAxTickLabels,\n" + 
	                "            AAyTickLabels,\n";
                SendString(callbackData, pif, sw, str, viasocket);

                str = String.Format("            AAzTickLabels) [instance: 1, cache: {0}];\n", cacheflag)+
                    "    switchAAenable = Compute(\"$0+1\",\n" + 
                    String.Format("	     AAenable) [instance: 2, cache: {0}];\n", cacheflag) +
	                "    object = Switch(\n" + 
	                "	     switchAAenable,\n" + 
	                "	     object,\n" + 
	                String.Format("	     AAobject) [instance:4, cache: {0}];\n", cacheflag);
                SendString(callbackData, pif, sw, str, viasocket);

	            /*
	             * Generate a call to the Approximation Switch module.
	             */
	            str = "    SWapproximation_options =\n" + 
	                "        Switch(\n" +  
	                "            buttonState,\n" + 
	                "            buttonUpApprox,\n" + 
	                String.Format("            buttonDownApprox) [instance: 5, cache: {0}];\n", cacheflag);
                SendString(callbackData, pif, sw, str, viasocket);

	            /*
	             * Generate a call to the Density Switch module.
	             */
	            str = "    SWdensity_options =\n" + 
	                "        Switch(\n" +  
	                "            buttonState,\n" + 
	                "            buttonUpDensity,\n" + 
	                String.Format("            buttonDownDensity) [instance: 6, cache: {0}];\n", cacheflag);
                SendString(callbackData, pif, sw, str, viasocket);

	           /*
	            * Generate a call to the Approximation Format module.
                */
                str = "    HWapproximation_options =\n" + 
	                "        Format(\n" +  
	                "            \"%s,%s\",\n" + 
	                "            buttonDownApprox,\n" + 
	                String.Format("            buttonUpApprox) [instance: 1, cache: {0}];\n", cacheflag);
                SendString(callbackData, pif, sw, str, viasocket);

                /*
                 * Generate a call to the Density Format module.
                 */
                str = "    HWdensity_options =\n" + 
	                "        Format(\n" +  
	                "            \"%d,%d\",\n" + 
	                "            buttonDownDensity,\n" + 
	                String.Format("            buttonUpDensity) [instance: 2, cache: {0}];\n", cacheflag) +
	                "    switchRenderMode = Compute(\n" + 
	                "	     \"$0+1\",\n" + 
	                String.Format("	     renderMode) [instance: 3, cache: {0}];\n", cacheflag) +
	                "    approximation_options = Switch(\n" + 
	                "	     switchRenderMode,\n" + 
	                "            SWapproximation_options,\n" + 
	                "	     HWapproximation_options)" + 
	                String.Format(" [instance: 7, cache: {0}];\n", cacheflag);
                SendString(callbackData, pif, sw, str, viasocket);

                str = "    density_options = Switch(\n" + 
	                "	     switchRenderMode,\n" + 
	                "            SWdensity_options,\n" + 
	                String.Format("            HWdensity_options) [instance: 8, cache: {0}];\n", cacheflag) +
	                "    renderModeString = Switch(\n" + 
	                "            switchRenderMode,\n" + 
	                "            \"software\",\n" + 
	                String.Format("            \"hardware\")[instance: 9, cache: {0}];\n", cacheflag) +
	                "    object_tag = Inquire(\n" + 
	                "            object,\n" +
	                String.Format("            \"object tag\")[instance: 3, cache: {0}];\n", cacheflag);
                SendString(callbackData, pif, sw, str, viasocket);

                /*
                 * Generate a call to Options module.
                 */
                str = "    annoted_object =\n" + 
                    "        Options(\n" +  
                    "            object,\n" + 
                    "            \"send boxes\",\n" + 
                    "            0,\n" + 
                    "            \"cache\",\n" + 
                    String.Format("            {0},\n", (cacheflag == (int)Cacheability.InternalsFullyCached ? 1 : 0))+
                    "            \"object tag\",\n" + 
                    "            object_tag,\n" + 
                    "            \"ddcamera\",\n" + 
                    "            whichCamera,\n" + 
                    "            \"rendering approximation\",\n" + 
                    "            approximation_options,\n" + 
                    "            \"render every\",\n" + 
                    "            density_options,\n" + 
                    "            \"button state\",\n" + 
                    "            buttonState,\n" + 
                    "            \"rendering mode\",\n" + 
                    String.Format("            renderModeString) [instance: 1, cache: {0}];\n", cacheflag);
                SendString(callbackData, pif, sw, str, viasocket);

                str = "    RECresNull =\n" + 
                    "        Inquire(\n" + 
                    "            RECresolution,\n" + 
                    String.Format("            \"is null + 1\") [instance: 4, cache: {0}];\n", cacheflag) +
                    "    ImageResolution =\n" + 
                    "        Inquire(\n" + 
                    "            camera,\n" + 
                    String.Format("            \"camera resolution\") [instance: 5, cache: {0}];\n", cacheflag)+
                    "    RECresolution =\n" + 
                    "        Switch(\n" + 
                    "            RECresNull,\n" + 
                    "            RECresolution,\n";
                SendString(callbackData, pif, sw, str, viasocket);

                str = String.Format("            ImageResolution) [instance: 10, cache: {0}];\n", cacheflag) +
	                "    RECaspectNull =\n" + 
	                "        Inquire(\n" + 
	                "            RECaspect,\n" + 
	                String.Format("            \"is null + 1\") [instance: 6, cache: {0}];\n", cacheflag) +
	                "    ImageAspect =\n" + 
	                "        Inquire(\n" + 
	                "            camera,\n" + 
	                String.Format("            \"camera aspect\") [instance: 7, cache: {0}];\n", cacheflag) +
	                "    RECaspect =\n" + 
	                "        Switch(\n" + 
	                "            RECaspectNull,\n" + 
	                "            RECaspect,\n" + 
	                String.Format("            ImageAspect) [instance: 11, cache: {0}];\n", cacheflag);
                SendString(callbackData, pif, sw, str, viasocket);

                str = "    switchRECenable = Compute(\n" + 
	                "          \"$0 == 0 ? 1 : (($2 == $3) && ($4 == $5)) ? ($1 == 1 ? 2 : 3) : 4\",\n" +  
	                "            RECenable,\n" + 
	                "            switchRenderMode,\n" + 
	                "            RECresolution,\n" + 
	                "            ImageResolution,\n" + 
	                "            RECaspect,\n" + 
	                String.Format("	     ImageAspect) [instance: 4, cache: {0}];\n", cacheflag) +
	                "    NoRECobject, RECNoRerenderObject, RECNoRerHW, RECRerenderObject = " +
			        "Route(switchRECenable, annoted_object);\n";
                SendString(callbackData, pif, sw, str, viasocket);

	            /*
	             * If no recording is specified, just use Display
	             */
                str = "    Display(\n" + 
	                "        NoRECobject,\n" + 
	                "        camera,\n" + 
	                "        where,\n" + 
	                String.Format("        throttle) [instance: 1, cache: {0}];\n", cacheflag);
                SendString(callbackData, pif, sw, str, viasocket);

	            /*
	             * If recording is used, but no rerendering is required,
	             * use Render followed by DIsplay and Write Image
	             */
                str = "    image =\n" + 
	                "        Render(\n" + 
	                "            RECNoRerenderObject,\n" + 
	                String.Format("            camera) [instance: 1, cache: {0}];\n", cacheflag) +
	                "    Display(\n" + 
	                "        image,\n" + 
	                "        NULL,\n" + 
	                "        where,\n" + 
	                String.Format("        throttle) [instance: 2, cache: {0}];\n", cacheflag) +
	                "    WriteImage(\n" + 
	                "        image,\n" + 
	                "        RECfile,\n" + 
	                String.Format("        RECformat) [instance: 1, cache: {0}];\n", cacheflag);
                SendString(callbackData, pif, sw, str, viasocket);

	            /*
	             * If recording is used in a hardware window, but no rerendering is required,
	             * use Display and ReadImageWindow.
	             */
                str = "    rec_where = Display(\n" + 
	                "        RECNoRerHW,\n" + 
	                "        camera,\n" + 
	                "        where,\n" + 
	                String.Format("        throttle) [instance: 1, cache: {0}];\n", 0/*cacheflag*/)  +
	                "    rec_image = ReadImageWindow(\n" + 
	                String.Format("        rec_where) [instance: 1, cache: {0}];\n", cacheflag) + 
	                "    WriteImage(\n" + 
	                "        rec_image,\n" + 
	                "        RECfile,\n" + 
	                String.Format("        RECformat) [instance: 1, cache: {0}];\n", cacheflag);
                SendString(callbackData, pif, sw, str, viasocket);

	            /*
	             * If recording, and rerendering *is* required, use Display 
	             * for the image window and Render and WriteImage along with
	             * the updated camera for the saved image
	             */
                str = "    RECupdateCamera =\n" + 
	                "	UpdateCamera(\n" + 
	                "	    camera,\n" + 
	                "	    resolution=RECresolution,\n" + 
	                String.Format("	    aspect=RECaspect) [instance: 2, cache: {0}];\n", cacheflag) +
	                "    Display(\n" + 
	                "        RECRerenderObject,\n" + 
	                "        camera,\n" + 
	                "        where,\n" + 
	                String.Format("        throttle) [instance: 1, cache: {0}];\n", cacheflag);
                SendString(callbackData, pif, sw, str, viasocket);

                str = "    RECRerenderObject =\n" +
                    "	ScaleScreen(\n" +
                    "	    RECRerenderObject,\n" +
                    "	    NULL,\n" +
                    "	    RECresolution,\n" +
                    String.Format("	    camera) [instance: 1, cache: {0}];\n", cacheflag) +
                    "    image =\n" +
                    "        Render(\n" +
                    "            RECRerenderObject,\n" +
                    String.Format("            RECupdateCamera) [instance: 2, cache: {0}];\n", cacheflag) +
                    "    WriteImage(\n" +
                    "        image,\n" +
                    "        RECfile,\n" +
                    String.Format("        RECformat) [instance: 2, cache: {0}];\n", cacheflag) +
                //
                // End macro body.
                //
	                "}\n";
                SendString(callbackData, pif, sw, str, viasocket);
            }
            return true;
        }

        // Fields for handling and storing parts of the image messages
        // sent from the executive.
        protected override void handleImageMessage(int id, string line)
        {
            Scanner scanner = new Scanner();
            String r = @"\d+:\s+IMAGE:\s+##\d+ (\d+)x(\d+) (.*)={Double} aspect={Double} " +
                @"from=\({Double},{Double},{Double}\) to=\({Double},{Double},{Double}\) " +
                @"up=\({Double},{Double},{Double}\) " +
                @"box=\({Double},{Double},{Double}\)\({Double},{Double},{Double}\)\({Double},{Double},{Double}\)\({Double},{Double},{Double}\) " +
                @"aamat=\({Double},{Double},{Double}\)\({Double},{Double},{Double}\)\({Double},{Double},{Double}\)\({Double},{Double},{Double}\)\s+" +
                @"ddcamera=(\d+) button=(\d+)";
            r = scanner.CreateRegexPattern(r);

            Regex regex = new Regex(r);
            Match m = regex.Match(line);
            if (m.Success)
            {
                int x = int.Parse(m.Groups[1].Value);
                int y = int.Parse(m.Groups[2].Value);
                String s = m.Groups[3].Value;
                double w = double.Parse(m.Groups[4].Value);
                double a = double.Parse(m.Groups[5].Value);
                double[] from = { double.Parse(m.Groups[6].Value), double.Parse(m.Groups[7].Value), double.Parse(m.Groups[8].Value) };
                double[] to = { double.Parse(m.Groups[9].Value), double.Parse(m.Groups[10].Value), double.Parse(m.Groups[11].Value) };
                double[] up = { double.Parse(m.Groups[12].Value), double.Parse(m.Groups[13].Value), double.Parse(m.Groups[14].Value) };
                double[,] box = { 
                { double.Parse(m.Groups[15].Value), double.Parse(m.Groups[16].Value), double.Parse(m.Groups[17].Value) }, 
                { double.Parse(m.Groups[18].Value), double.Parse(m.Groups[19].Value), double.Parse(m.Groups[20].Value) }, 
                { double.Parse(m.Groups[21].Value), double.Parse(m.Groups[22].Value), double.Parse(m.Groups[23].Value) },
                { double.Parse(m.Groups[24].Value), double.Parse(m.Groups[25].Value), double.Parse(m.Groups[26].Value) } };
                double[,] aamat = { 
                { double.Parse(m.Groups[27].Value), double.Parse(m.Groups[28].Value), double.Parse(m.Groups[29].Value) }, 
                { double.Parse(m.Groups[30].Value), double.Parse(m.Groups[31].Value), double.Parse(m.Groups[32].Value) },
                { double.Parse(m.Groups[33].Value), double.Parse(m.Groups[34].Value), double.Parse(m.Groups[35].Value) }, 
                { double.Parse(m.Groups[36].Value), double.Parse(m.Groups[37].Value), double.Parse(m.Groups[38].Value) } };
                int ddcamera = int.Parse(m.Groups[39].Value);
                int button = int.Parse(m.Groups[40].Value);

                bool persp;
                double viewAngle;

                if (s == "width")
                    persp = false;
                else
                    persp = true;

                double xdiff = from[0] - to[0];
                double ydiff = from[1] - to[1];
                double zdiff = from[2] - to[2];
                double dist = Math.Sqrt(xdiff * xdiff + ydiff * ydiff + zdiff * zdiff);

                if (persp)
                {
                    viewAngle = Math.Atan(w / 2) * 360 / Math.PI;
                    w = dist * w;
                }
                else
                {
                    viewAngle = Math.Atan((w / 2) / dist) * 360 / Math.PI;
                }

                DirectInteractionMode imode = image.getInteractionMode();

                if (ddcamera == 1 || button == 1)
                {
                    // If in navigate mode, then to, from and up are
                    // set elsewhere.
                    if (imode != DirectInteractionMode.NAVIGATE || ddcamera == 1)
                    {
                        this.setTo(to, false);
                        this.setFrom(from, false);
                        this.setUp(up, false);
                    }

                    setResolution(x, y, false);
                    setWidth(w, false);
                    setAspect(a, false);
                    setBox(box, false);
                    setProjection(persp, false);
                    setViewAngle(viewAngle, false);
                    enableVector(true, false);
                    sendValuesQuietly();
                    image.newCamera(box, aamat, from, to, up, x, y, w, persp, viewAngle);
                }
                else if (!image.IsCameraInitialized || imode == DirectInteractionMode.NAVIGATE)
                    image.newCamera(box, aamat, from, to, up, x, y, w, persp, viewAngle);

                image.allowDirectInteraction(true);

                if (this.saveInteractionMode != DirectInteractionMode.NONE)
                {
                    image.setInteractionMode(saveInteractionMode);
                    saveInteractionMode = DirectInteractionMode.NONE;
                }
            }
            else
            {
                regex = new Regex(@"\d+:  IMAGE:  ##\d+ (\d+)x(\d+)");
                m = regex.Match(line);

                if (m.Success)
                {
                    int x = int.Parse(m.Groups[1].Value);
                    int y = int.Parse(m.Groups[2].Value);

                    setResolution(x, y, false);
                    image.allowDirectInteraction(false);
                    image.clearFrameBufferOverlay();
                }
            }
        }

        public override void openDefaultWindow(System.Windows.Forms.Form parent)
        {
            throw new Exception("Not Yet Implemented");
            base.openDefaultWindow(parent);
        }

        // Let the caller of openDefaultWindow() know what kind of window she's getting.
        // This is intended for use in EditorWindow so that we can sanity check the number
        // of cdbs were going to open before kicking off the operation and so that we
        // don't question the user before opening large numbers of interactors.
        // A name describing the type of window can be written into window_name in order
        // to enable nicer warning messages.
        protected virtual bool defaultWindowIsCDB(String window_name)
        {
            if (window_name != null)
                window_name = "Image Window";
            return false;
        }

        protected double[,] boundingBox = new double[4,3];

        // Overrides of Node members to ensure that the correct stuff
        // gets printed and sent to the server.  The image node prevents
        // "RECENABLE", whether to record frames or not, from being saved.
        protected override string inputValueString(int i, string prefix)
        {
            throw new Exception("Not Yet Implemented");
            return base.inputValueString(i, prefix);
        }
        protected override bool printIOComment(StreamWriter s, bool input, int index, string indent, bool valueOnly)
        {
            throw new Exception("Not Yet Implemented");
            return base.printIOComment(s, input, index, indent, valueOnly);
        }

        protected virtual void notifyProjectionChange(bool newPersp)
        {
            int parameter;
            if (newPersp)
                parameter = ParamConst.WIDTH;
            else
                parameter = ParamConst.VIEWANGLE;
            useDefaultInputValue(parameter, false);
            if (newPersp)
                parameter = ParamConst.VIEWANGLE;
            else
                parameter = ParamConst.WIDTH;
            useAssignedInputValue(parameter, false);
        }
        protected virtual void notifyUseVectorChange(bool newUse)
        {
            if (newUse == UseVector)
                return;

            DXPacketIF pif = DXApplication.theDXApplication.getPacketIF();
            if (pif != null)
            {
                if (newUse)
                {
                    useAssignedInputValue(ParamConst.TO, false);
                    useAssignedInputValue(ParamConst.FROM, false);
                    useAssignedInputValue(ParamConst.WIDTH, false);
                    useAssignedInputValue(ParamConst.UP, false);
                    useAssignedInputValue(ParamConst.VIEWANGLE, false);
                    useAssignedInputValue(ParamConst.PROJECTION, false);
                    setInputDirty(ParamConst.TO);
                    setInputDirty(ParamConst.FROM);
                    setInputDirty(ParamConst.WIDTH);
                    setInputDirty(ParamConst.UP);
                    setInputDirty(ParamConst.VIEWANGLE);
                    setInputDirty(ParamConst.PROJECTION);
                }
                else
                {
                    useDefaultInputValue(ParamConst.TO, false);
                    useDefaultInputValue(ParamConst.FROM, false);
                    useDefaultInputValue(ParamConst.WIDTH, false);
                    useDefaultInputValue(ParamConst.UP, false);
                    useDefaultInputValue(ParamConst.VIEWANGLE, false);
                }
            }
        }

        protected override string netEndOfMacroNodeString(string prefix)
        {
            String buf = "";
            String gpn = getGroupName(SymbolManager.theSymbolManager.getSymbol(ProcessGroupManager.ProcessGroup));
            if (gpn != null)
                buf = String.Format("CacheScene({0}Image_{1}_in_{2}, {3}Image_{4}_out_1, {5}Image_{6}_out_2)[group: \"{7}\"];\n",
                    prefix, InstanceNumber, ParamConst.IMAGETAG,
                    prefix, InstanceNumber, prefix, InstanceNumber, gpn);
            else
                buf = String.Format("CacheScene({0}Image_{1}_in_{2}, {3}Image_{4}_out_1, {5}Image_{6}_out_2);\n",
                    prefix, InstanceNumber, ParamConst.IMAGETAG,
                    prefix, InstanceNumber, prefix, InstanceNumber);

            return buf;
        }

        public override bool netParseComment(string comment, string file, int lineno)
        {
            int major, minor, micro;
            String buf;

            if (getNetwork().getDXMajorVersion() < 3)
            {
                if (comment.Contains("input["))
                {
                    Regex regex = new Regex(@"(.*input\[)(\d)+(\].*)");
                    Match m = regex.Match(comment);

                    if (m.Success)
                    {
                        int input = Int32.Parse(m.Groups[2].Value);
                        String newcom = m.Groups[1].Value + ParamConst.translateInputs[input].ToString() +
                            m.Groups[3].Value;
                        comment = newcom;
                    }
                }
            }
            getNetwork().getVersion(out major, out minor, out micro);

            if (major == 2 && minor >= 0 && micro >= 1)
                translating = true;
            bool res = base.netParseComment(comment, file, lineno);
            translating = false;

            return res;
        }

        protected override bool netPrintAuxComment(StreamWriter s)
        {
            throw new Exception("Not Yet Implemented");
            return base.netPrintAuxComment(s);
        }
        protected override bool netParseAuxComment(string comment, string filename, int lineno)
        {
            return base.netParseAuxComment(comment, filename, lineno) ||
                parseCommonComments(comment, filename, lineno);
        }

        protected override int handleNodeMsgInfo(string line)
        {
            throw new Exception("Not Yet Implemented");
            return base.handleNodeMsgInfo(line);
        }
        protected override void reflectStateChange(bool unmanage)
        { // Intentionally left blank
        }
        protected override void ioParameterStatusChanged(bool input, int index, NodeParameterStatusChange status)
        {
            switch (index)
            {
                case ParamConst.THROTTLE:
                    if (image != null)
                    {
                        if (status == NodeParameterStatusChange.ParameterArkAdded ||
                            status == NodeParameterStatusChange.ParameterArkRemoved)
                        {
                            bool st = isInputDefaulting(ParamConst.THROTTLE);
                            image.sensitizeThrottleDialog(st);
                        }
                        else if (status == NodeParameterStatusChange.ParameterValueChanged ||
                            status == NodeParameterStatusChange.PatemeterSetValueChanged)
                        {
                            double t;

                            getThrottle(out t);
                            image.updateThrottleDialog(t);
                        }
                    }
                    break;

                case ParamConst.RECENABLE:
                case ParamConst.RECFILE:
                case ParamConst.RECFORMAT:
                case ParamConst.RECRESOLUTION:
                case ParamConst.RECASPECT:
                    if (image != null)
                    {
                        // This used to say isRecFileInputSet() instead of TRUE
                        // but it always worked because isRecFileInputSet always returns
                        // the wrong value.  Nowdays, we only want to revisit the sensitivity
                        // of the dialogs, not the sensitivity of the command anyway.
                        image.sensitizePrintImageDialog(true);
                        image.sensitizeSaveImageDialog(true);
                    }
                    break;

                case ParamConst.BACKGROUND:
                    if (image != null)
                    {
                        if ((long)(status & NodeParameterStatusChange.ParameterArkAdded) > 0 ||
                            (long)(status & NodeParameterStatusChange.ParameterArkRemoved) > 0)
                        {
                            image.sensitizeBackgroundColorDialog(!IsBGColorConnected);
                        }
                        else if ((long)(status & NodeParameterStatusChange.ParameterValueChanged) > 0 ||
                            (long)(status & NodeParameterStatusChange.PatemeterSetValueChanged) > 0)
                        {
                            String color;
                            getBackgroundColor(out color);
                            image.updateBGColorDialog(color);
                        }
                    }
                    break;

                case ParamConst.AAENABLE:
                    if (image != null)
                        image.setAutoAxesDialogEnable();
                    break;

                case ParamConst.AALABELS:
                    if (image != null)
                        image.setAutoAxesDialogLabels();
                    break;

                case ParamConst.AATICKS:
                    if (image != null)
                        image.setAutoAxesDialogTicks();
                    break;

                case ParamConst.AA_XTICK_LOCS:
                    if (image != null)
                        image.setAutoAxesDialogXTickLocs();
                    break;

                case ParamConst.AA_YTICK_LOCS:
                    if (image != null)
                        image.setAutoAxesDialogYTickLocs();
                    break;

                case ParamConst.AA_ZTICK_LOCS:
                    if (image != null)
                        image.setAutoAxesDialogZTickLocs();
                    break;

                case ParamConst.AA_XTICK_LABELS:
                    if (image != null)
                        image.setAutoAxesDialogXTickLabels();
                    break;

                case ParamConst.AA_YTICK_LABELS:
                    if (image != null)
                        image.setAutoAxesDialogYTickLabels();
                    break;

                case ParamConst.AA_ZTICK_LABELS:
                    if (image != null)
                        image.setAutoAxesDialogZTickLabels();
                    break;

                case ParamConst.AACORNERS:
                    if (image != null)
                        image.setAutoAxesDialogCorners();
                    break;

                case ParamConst.AAFRAME:
                    if (image != null)
                        image.setAutoAxesDialogFrame();
                    break;

                case ParamConst.AAADJUST:
                    if (image != null)
                        image.setAutoAxesDialogAdjust();
                    break;

                case ParamConst.AACURSOR:
                    if (image != null)
                        image.setAutoAxesDialogCursor();
                    break;

                case ParamConst.AAGRID:
                    if (image != null)
                        image.setAutoAxesDialogGrid();
                    break;

                case ParamConst.AACOLORS:
                    if (image != null)
                        image.setAutoAxesDialogAnnotationColors();
                    break;

                case ParamConst.AAANNOTATION:
                    if (image != null)
                        image.setAutoAxesDialogAnnotationColors();
                    break;

                case ParamConst.AALABELSCALE:
                    if (image != null)
                        image.setAutoAxesDialogLabelScale();
                    break;

                case ParamConst.AAFONT:
                    if(image != null)
                        image.setAutoAxesDialogFont();
                    break;

                case ParamConst.INTERACTIONMODE:
                    if (image != null)
                    {
                        bool stat = IsInteractionModeConnected;
                        image.sensitizeViewControl(!stat);
                    }
                    break;

                case ParamConst.IMAGENAME:
                    if (image != null)
                    {
                        bool stat = isInputConnected(ParamConst.IMAGENAME);
                        if ((!stat) && (isInputDefaulting(ParamConst.IMAGENAME)))
                            setTitle(null);
                        else
                            setTitle(getInputValueString(ParamConst.IMAGENAME));
                        image.sensitizeChangeImageName(!stat);
                    }
                    break;

                case ParamConst.RENDER_MODE:
                    if (image != null)
                    {
                        if (status == NodeParameterStatusChange.ParameterArkAdded)
                            image.sensitizeRenderMode(false);
                        else if (status == NodeParameterStatusChange.ParameterArkRemoved)
                            image.sensitizeRenderMode(true);
                        else if ((long)(status & (NodeParameterStatusChange.ParameterValueChanged |
                       NodeParameterStatusChange.PatemeterSetValueChanged)) > 0)
                            image.updateRenderingOptionsDialog();
                    }
                    break;

                case ParamConst.BUTTON_UP_APPROX:
                    if (image != null)
                    {
                        if (status == NodeParameterStatusChange.ParameterArkAdded)
                            image.sensitizeButtonUpApprox(false);
                        else if (status == NodeParameterStatusChange.ParameterArkRemoved)
                            image.sensitizeButtonUpApprox(true);
                        else if ((long)(status & (NodeParameterStatusChange.ParameterValueChanged |
                            NodeParameterStatusChange.PatemeterSetValueChanged)) > 0)
                            image.updateRenderingOptionsDialog();
                    }
                    break;

                case ParamConst.BUTTON_DOWN_APPROX:
                    if (image != null)
                    {
                        if (status == NodeParameterStatusChange.ParameterArkAdded)
                            image.sensitizeButtonDownApprox(false);
                        else if (status == NodeParameterStatusChange.ParameterArkRemoved)
                            image.sensitizeButtonDownApprox(true);
                        else if ((long)(status & (NodeParameterStatusChange.ParameterValueChanged |
                            NodeParameterStatusChange.PatemeterSetValueChanged)) > 0)
                            image.updateRenderingOptionsDialog();
                    }
                    break;

                case ParamConst.BUTTON_UP_DENSITY:
                    if (image != null)
                    {
                        if (status == NodeParameterStatusChange.ParameterArkAdded)
                            image.sensitizeButtonUpDensity(false);
                        else if (status == NodeParameterStatusChange.ParameterArkRemoved)
                            image.sensitizeButtonUpDensity(true);
                        else if ((long)(status & (NodeParameterStatusChange.ParameterValueChanged |
                            NodeParameterStatusChange.PatemeterSetValueChanged)) > 0)
                            image.updateRenderingOptionsDialog();
                    }
                    break;

                case ParamConst.BUTTON_DOWN_DENSITY:
                    if (image != null)
                    {
                        if (status == NodeParameterStatusChange.ParameterArkAdded)
                            image.sensitizeButtonDownDensity(false);
                        else if (status == NodeParameterStatusChange.ParameterArkRemoved)
                            image.sensitizeButtonDownDensity(true);
                        else if ((long)(status & (NodeParameterStatusChange.ParameterValueChanged |
                            NodeParameterStatusChange.PatemeterSetValueChanged)) > 0)
                            image.updateRenderingOptionsDialog();
                    }
                    break;
                default:
                    break;
            }
            base.ioParameterStatusChanged(input, index, status);
        }


        protected void setAutoAxesTickLocs(int param, ref double t, int size, bool send)
        {
            throw new Exception("Not Yet Implemented");
        }

        public ImageNode(NodeDefinition nd, Network net, int instnc)
            : base(nd, net, instnc)
        {
            ImageDefinition imnd = (ImageDefinition)nd;
            macroDirty = true;
            translating = false;

            // Anything below here also belongs in this->setDefaultCfgState().
            saveInteractionMode = DirectInteractionMode.NONE;
            internalCache = imnd.DefaultInternalCacheability;
        }

        ~ImageNode()
        { }

        public override bool initialize()
        {
            DXApplication.theDXApplication.setBusyCursor(true);
            base.initialize();
            if (!setMessageIdParameter(ParamConst.IMAGETAG))
                return false;

            enableVector(false, false);
            if (image != null)
                image.allowDirectInteraction(false);

            height = -1;

            enableSoftwareRendering(true, false);
            setButtonUp(true, false);

            DXApplication.theDXApplication.setBusyCursor(false);

            return true;
        }

        public override void setTitle(string title, bool fromServer)
        {
            if (!isInputConnected(ParamConst.IMAGENAME))
            {
                if (title == null || title.Length == 0)
                    useDefaultInputValue(ParamConst.IMAGENAME, false);
                else
                {
                    if (fromServer && isInputDefaulting(ParamConst.IMAGENAME))
                        setInputAttributeFromServer(ParamConst.IMAGENAME, title, DXTypeVals.StringType);
                    else
                    {
                        String v = getInputValueString(ParamConst.IMAGENAME);
                        if (v != title)
                            setInputValue(ParamConst.IMAGENAME, title, DXTypeVals.StringType, false);
                    }
                }
            }
            if (title != null && title.StartsWith("\""))
            {
                String tmp = title.Substring(1).Trim();
                if (tmp.EndsWith("\""))
                    tmp = tmp.Substring(0, tmp.Length - 1);
                base.setTitle(tmp);
            }
            else
                base.setTitle(title, fromServer);
        }

        // FIXME: I am confused.  (At last a genuine FIXME comment.)
        // If the param is defaulting, then rely on the superclass.  If the param isn't
        // defaulting then fetch the value from the node.  If the node has a null value,
        // then rely on the superclass.  Should there ever be a difference between
        // what the superclass thinks and what this thinks?  I don't think so.
        // Wierdness: this and the the superclass support {set,get}Title,
        // but the superclass versions use an ioComment whereas this uses an input
        // parameter.
        public override string getTitle()
        {
            // Using the node's value if the input is defaulting would prevent us
            // from using "nodename: filename".
            if (isInputDefaulting(ParamConst.IMAGENAME))
                return base.getTitle();

            // Make sure the value is a valid string and strip off the quotes
            // and use it, if it is.
            if (getInputSetValueType(ParamConst.IMAGENAME) == DXTypeVals.StringType)
            {
                String v = getInputValueString(ParamConst.IMAGENAME);
                if (v != null || v.Length != 0 || v == "NULL")
                    return base.getTitle();

                // Match quoted string
                Regex regex = new Regex(@"""([^""]+)""");
                Match m = regex.Match(v);
                if(!m.Success)
                    return base.getTitle();

                String t = m.Groups[1].Value;

                title = t;
                return title;
            }

            return base.getTitle();
        }

        public override DXTypeVals setInputValue(int index, string value, 
            DXTypeVals type, bool send)
        {
            DXTypeVals result;

            bool trans = translating;
            translating = false;

            switch (index)
            {
                case ParamConst.USEVECTOR:
                    if (trans)
                    {
                        if (value.StartsWith("1"))
                            value = "0";
                        else if (value.StartsWith("2"))
                            value = "1";
                    }
                    if (value == "NULL")
                        value = "0";
                    notifyUseVectorChange(!value.StartsWith("0"));
                    break;

                case ParamConst.AAENABLE:
                    if (trans)
                    {
                        if (value.StartsWith("1"))
                            value = "0";
                        else if (value.StartsWith("2"))
                            value = "1";
                    }
                    break;

                case ParamConst.RECENABLE:
                    if (trans)
                    {
                        if (value.StartsWith("1"))
                            value = "0";
                        else if (value.StartsWith("2"))
                            value = "1";
                    }
                    break;

                case ParamConst.PROJECTION:
                    notifyProjectionChange(!value.StartsWith("0"));
                    break;

                case ParamConst.RENDER_MODE:
                    if (value == "\"hardware\"" ||
                    value == "hardware")
                        value = "1";
                    else if (value == "\"software\"" ||
                        value == "software")
                        value = "0";
                    else if (trans)
                    {
                        if (value.StartsWith("1"))
                            value = "0";
                        else if (value.StartsWith("2"))
                            value = "1";
                    }
                    if (type == DXTypeVals.StringType)
                        type = DXTypeVals.FlagType;
                    break;
                case ParamConst.BUTTON_UP_APPROX:
                case ParamConst.BUTTON_DOWN_APPROX:
                    if (value == "\"flat\"")
                        value = "\"none\"";
                    break;
            }

            result = base.setInputValue(index, value, type, send);
            translating = trans;
            return result;
        }

        public override bool sendValues() { return sendValues(true); }
        public override bool sendValues(bool ignoreDirty)
        {
            bool sendMacro = true;
            foreach (ImageWindow w in getNetwork().getImageList())
            {
                if (w == this.image)
                {
                    sendMacro = true;
                    break;
                }
                else if (w.getAssociatedNode() is ImageNode)
                {
                    sendMacro = false;
                    break;
                }
            }

            if (sendMacro && (ignoreDirty || macroDirty))
            {
                DXPacketIF pif = DXApplication.theDXApplication.getPacketIF();
                if (pif == null || !this.sendMacro(pif))
                    return false;
                macroDirty = false;
            }
            return base.sendValues(ignoreDirty);
        }

        public override bool printValues(StreamWriter sw, string prefix, PrintType dest)
        {
            throw new Exception("Not Yet Implemented");
            return base.printValues(sw, prefix, dest);
        }
        public override bool associateImage(ImageWindow w)
        {
            bool result = base.associateImage(w);

            if (result && w != null)
                w.allowDirectInteraction(false);

            return result;
        }

        Cacheability InternalCacheability
        {
            get { return internalCache; }
            set { internalCache = value; }
        }

        public bool UseVector
        {
            get
            {
                Parameter p = getInputParameter(ParamConst.USEVECTOR);
                String s = p.getValueOrDefaultString();
                return s != "0";
            }
        }
        public void enableVector(bool use, bool send)
        {
            if (use == UseVector)
                return;

            setInputValue(ParamConst.USEVECTOR, use ? "1" : "0", DXTypeVals.IntegerType, send);
            Parameter p = getInputParameter(ParamConst.USEVECTOR);
            p.setDirty();
        }
        public void setTo(double[] to, bool send)
        {
            String s = String.Format("[{0} {1} {2}]", to[0], to[1], to[2]);
            setInputValue(ParamConst.TO, s, DXTypeVals.VectorType, send);
        }
        public void setFrom(double[] from, bool send)
        {
            String s = String.Format("[{0} {1} {2}]", from[0], from[1], from[2]);
            setInputValue(ParamConst.FROM, s, DXTypeVals.VectorType, send);
        }
        public void setResolution(int x, int y, bool send)
        {
            setInputValue(ParamConst.RESOLUTION, x.ToString(), DXTypeVals.IntegerType, send);
            height = y;
        }
        public void setWidth(double w, bool send)
        {
            bool persp;
            getProjection(out persp);

            if (persp)
                setInputSetValue(ParamConst.WIDTH, w.ToString(), DXTypeVals.ScalarType, send);
            else
                setInputValue(ParamConst.WIDTH, w.ToString(), DXTypeVals.ScalarType, send);
        }
        public void setAspect(double a, bool send)
        {
            setInputValue(ParamConst.ASPECT, a.ToString(), DXTypeVals.ScalarType, send);
        }
        public void setThrottle(double a, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setUp(double[] up, bool send)
        {
            String s = String.Format("[{0} {1} {2}]", up[0], up[1], up[2]);
            setInputValue(ParamConst.UP, s, DXTypeVals.VectorType, send);
        }
        public void setBox(double[,] box, bool send)
        {
            boundingBox = box;
        }
        public void setProjection(bool persp, bool send)
        {
            int i = (persp?1:0);
            setInputValue(ParamConst.PROJECTION, i.ToString(), DXTypeVals.IntegerType, send);
        }
        public void setViewAngle(double angle, bool send)
        {
            bool persp;
            getProjection(out persp);

            if (persp)
                setInputValue(ParamConst.VIEWANGLE, angle.ToString(), DXTypeVals.ScalarType, send);
            else
                setInputSetValue(ParamConst.VIEWANGLE, angle.ToString(), DXTypeVals.ScalarType, send);
        }
        
        public void setButtonUp(bool up, bool send) {
            String s = (up ? "1" : "2");
            setInputValue(ParamConst.BUTTON_STATE, s, DXTypeVals.IntegerType, send);
        }

        public void setApprox(bool up, String approx, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setDensity(bool up, int density, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setBackgroundColor(String color, bool send) { throw new Exception("Not Yet Implemented"); }

        public void getTo(out double to) { throw new Exception("Not Yet Implemented"); }
        public void getFrom(out double from) { throw new Exception("Not Yet Implemented"); }
        public void getResolution(out int x, out int y) { throw new Exception("Not Yet Implemented"); }
        public void getWidth(out double w) { throw new Exception("Not Yet Implemented"); }
        public void getAspect(out double a) { throw new Exception("Not Yet Implemented"); }
        public void getThrottle(out double v) { throw new Exception("Not Yet Implemented"); }
        public void getUp(out double up) { throw new Exception("Not Yet Implemented"); }
        public void getBox(out double[,] box) { throw new Exception("Not Yet Implemented"); }
        public void getProjection(out bool persp)
        {
            String s;
            int ii;
            if (isInputDefaulting(ParamConst.PROJECTION))
                s = getInputDefaultValueString(ParamConst.PROJECTION);
            else
                s = getInputValueString(ParamConst.PROJECTION);

            if (s == null || s == "NULL")
                persp = false;
            else
            {
                ii = int.Parse(s);
                persp = ii > 0;
            }
        }
        public void getViewAngle(out double angle) { throw new Exception("Not Yet Implemented"); }
        public bool IsButtonUp { get { throw new Exception("Not Yet Implemented"); } }
        public void getApprox(bool up, out String approx) { throw new Exception("Not Yet Implemented"); }
        public void getDensity(bool up, out int density) { throw new Exception("Not Yet Implemented"); }
        public void getBackgroundColor(out String color) { throw new Exception("Not Yet Implemented"); }
        public void getRecordEnable(out int x) { throw new Exception("Not Yet Implemented"); }
        public void getRecordResolution(out int x, out int y) { throw new Exception("Not Yet Implemented"); }
        public void getRecordAspect(out double aspect) { throw new Exception("Not Yet Implemented"); }

        public bool useAutoAxes() { throw new Exception("Not Yet Implemented"); }

        public void setRecordEnable(int use, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setRecordResolution(int x, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setRecordAspect(double aspect, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setRecordFile(String file, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setRecordFormat(String format, bool send) { throw new Exception("Not Yet Implemented"); }
        public void getRecordFile(out String file) { throw new Exception("Not Yet Implemented"); }
        public void getRecordFormat(out String format) { throw new Exception("Not Yet Implemented"); }

        public void enableSoftwareRendering(bool use, bool send)
        {
            String s = use ? "0" : "1";

            if (use)
            {
                if (!isInputDefaulting(ParamConst.BUTTON_UP_DENSITY))
                    useDefaultInputValue(ParamConst.BUTTON_UP_DENSITY, false);
                if (!isInputDefaulting(ParamConst.BUTTON_DOWN_DENSITY))
                    useDefaultInputValue(ParamConst.BUTTON_DOWN_DENSITY, false);
            }
            else
            {
                if (isInputSet(ParamConst.BUTTON_UP_DENSITY) &&
                    isInputDefaulting(ParamConst.BUTTON_UP_DENSITY))
                    useAssignedInputValue(ParamConst.BUTTON_UP_DENSITY, false);
                if (isInputSet(ParamConst.BUTTON_DOWN_DENSITY) &&
                    isInputDefaulting(ParamConst.BUTTON_DOWN_DENSITY))
                    useAssignedInputValue(ParamConst.BUTTON_DOWN_DENSITY, false);
            }
            setInputValue(ParamConst.RENDER_MODE, s, DXTypeVals.StringType, send);
        }

        //
        public void getAutoAxesCorners(out double[] dval) { throw new Exception("Not Yet Implemented"); }
        public void getAutoAxesCursor(out double x, out double y, out double z) { throw new Exception("Not Yet Implemented"); }
        public int getAutoAxesStringList(int index, out String[] sval) { throw new Exception("Not Yet Implemented"); }
        public int getAutoAxesLabels(out String[] sval) { throw new Exception("Not Yet Implemented"); }
        public int getAutoAxesAnnotation(out String[] sval) { throw new Exception("Not Yet Implemented"); }
        public int getAutoAxesColors(out String[] sval) { throw new Exception("Not Yet Implemented"); }
        public int getAutoAxesXTickLabels(out String[] sval) { throw new Exception("Not Yet Implemented"); }
        public int getAutoAxesYTickLabels(out String[] sval) { throw new Exception("Not Yet Implemented"); }
        public int getAutoAxesZTickLabels(out String[] sval) { throw new Exception("Not Yet Implemented"); }
        public int getAutoAxesString(int index, out String sval) { throw new Exception("Not Yet Implemented"); }
        public int getAutoAxesFont(out String sval) { throw new Exception("Not Yet Implemented"); }
        public void getAutoAxesTicks(out int t1, out int t2, out int t3) { throw new Exception("Not Yet Implemented"); }
        public void getAutoAxesTicks(out int t) { throw new Exception("Not Yet Implemented"); }
        public void getAutoAxesXTickLocs(out double[] t) { throw new Exception("Not Yet Implemented"); }
        public void getAutoAxesYTickLocs(out double[] t) { throw new Exception("Not Yet Implemented"); }
        public void getAutoAxesZTickLocs(out double[] t) { throw new Exception("Not Yet Implemented"); }
        public int getAutoAxesInteger(int index) { throw new Exception("Not Yet Implemented"); }
        public int getAutoAxesEnable() { throw new Exception("Not Yet Implemented"); }
        public double getAutoAxesDouble(int index) { throw new Exception("Not Yet Implemented"); }
        public double getAutoAxesLabelScale() { throw new Exception("Not Yet Implemented"); }
        public int getAutoAxesTicksCount() { throw new Exception("Not Yet Implemented"); }


        public void setAutoAxesCorners(double[] dval, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesCursor(double x, double y, double z, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesFlag(int index, bool state, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesFrame(bool state, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesGrid(bool state, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesAdjust(bool state, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesInteger(int index, int d, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesEnable(int d, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesDouble(int index, double d, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesLabelScale(double d, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesStringList(int index, String value, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesLabels(String value, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesAnnotation(String value, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesColors(String value, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesXTickLocs(double[] t, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesYTickLocs(double[] t, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesZTickLocs(double[] t, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesXTickLabels(String value, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesYTickLabels(String value, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesZTickLabels(String value, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesString(int index, String value, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesFont(String value, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesTicks(int t1, int t2, int t3, bool send) { throw new Exception("Not Yet Implemented"); }
        public void setAutoAxesTicks(int t, bool send) { throw new Exception("Not Yet Implemented"); }

        public void disableAutoAxesCorners(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesCorners(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesCursor(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesTicks(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesXTickLocs(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesYTickLocs(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesZTickLocs(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesStringList(int index, bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesAnnotation(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesLabels(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesColors(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesXTickLabels(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesYTickLabels(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesZTickLabels(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesString(int index, bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesFont(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesEnable(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesFrame(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesGrid(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesAdjust(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetAutoAxesLabelScale(bool send) { throw new Exception("Not Yet Implemented"); }

        public void unsetRecordResolution(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetRecordAspect(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetRecordFile(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetRecordFormat(bool send) { throw new Exception("Not Yet Implemented"); }
        public void unsetRecordEnable(bool send) { throw new Exception("Not Yet Implemented"); }

        public bool isAutoAxesCornersSet() { throw new Exception("Not Yet Implemented"); }
        public bool isAutoAxesCursorSet() { throw new Exception("Not Yet Implemented"); }
        public bool isSetAutoAxesFlag(int index) { throw new Exception("Not Yet Implemented"); }
        public bool isSetAutoAxesFrame() { throw new Exception("Not Yet Implemented"); }
        public bool isSetAutoAxesGrid() { throw new Exception("Not Yet Implemented"); }
        public bool isSetAutoAxesAdjust() { throw new Exception("Not Yet Implemented"); }
        public bool isAutoAxesStringListSet(int index) { throw new Exception("Not Yet Implemented"); }
        public bool isAutoAxesAnnotationSet() { throw new Exception("Not Yet Implemented"); }
        public bool isAutoAxesLabelsSet() { throw new Exception("Not Yet Implemented"); }
        public bool isAutoAxesColorsSet() { throw new Exception("Not Yet Implemented"); }
        public bool isAutoAxesStringSet(int index) { throw new Exception("Not Yet Implemented"); }
        public bool isAutoAxesFontSet() { throw new Exception("Not Yet Implemented"); }
        public bool isAutoAxesTicksSet() { throw new Exception("Not Yet Implemented"); }
        public bool isAutoAxesXTickLocsSet() { throw new Exception("Not Yet Implemented"); }
        public bool isAutoAxesYTickLocsSet() { throw new Exception("Not Yet Implemented"); }
        public bool isAutoAxesZTickLocsSet() { throw new Exception("Not Yet Implemented"); }
        public bool isAutoAxesXTickLabelsSet() { throw new Exception("Not Yet Implemented"); }
        public bool isAutoAxesYTickLabelsSet() { throw new Exception("Not Yet Implemented"); }
        public bool isAutoAxesZTickLabelsSet() { throw new Exception("Not Yet Implemented"); }
        public bool isAutoAxesDoubleSet(int index) { throw new Exception("Not Yet Implemented"); }
        public bool isAutoAxesLabelScaleSet() { throw new Exception("Not Yet Implemented"); }

        public bool useSoftwareRendering() { throw new Exception("Not Yet Implemented"); }

        public virtual String getPickIdentifier() { throw new Exception("Not Yet Implemented"); }

        // Save and retrieve image window state (camera, approx, render mode...)
        // to and from the .cfg file.
        public override bool cfgParseComment(string comment, string file, int lineno)
        {
            throw new Exception("Not Yet Implemented");
            return base.cfgParseComment(comment, file, lineno);
        }
        public override bool cfgPrintNode(StreamWriter sw, PrintType destination)
        {
            throw new Exception("Not Yet Implemented");
            return base.cfgPrintNode(sw, destination);
        }

        public override void setDefaultCfgState()
        {
            saveInteractionMode = DirectInteractionMode.NONE;

            // Before resetting internal caching, check the net version number.
            // If it's 3.1.1 or later, then proceed.  We're preventing this reset
            // for older nets because older versions of dx did not write internal cache
            // value into both .net and .cfg files.  They wrote it only into the .net file.
            // So if we reset here, then we'll be throwing out the saved value.  For current
            // versions of dxui, it's OK to reset because we'll find a cache value in the 
            // .cfg file.

            Network net = getNetwork();
            int net_major = net.getNetMajorVersion();
            int net_minor = net.getNetMinorVersion();
            int net_micro = net.getNetMicroVersion();
            int net_version = Utils.VersionNumber(net_major, net_minor, net_micro);
            int fixed_version = Utils.VersionNumber(3, 1, 1);
            if (net_version >= fixed_version)
            {
                ImageDefinition imnd = (ImageDefinition) Definition;
                internalCache = imnd.DefaultInternalCacheability;
            }
        }

        public override DXTypeVals setInputSetValue(int index, string value)
        {
            throw new Exception("Not Yet Implemented");
            return base.setInputSetValue(index, value);
        }

        public bool IsAutoAxesEnableConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsAutoAxesCornersConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsAutoAxesCursorConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsAutoAxesFrameConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsAutoAxesGridConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsAutoAxesAdjustConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsAutoAxesAnnotationConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsAutoAxesLabelsConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsAutoAxesColorsConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsAutoAxesFontConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsAutoAxesTicksConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsAutoAxesXTickLocsConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsAutoAxesYTickLocsConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsAutoAxesZTickLocsConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsAutoAxesXTickLabelsConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsAutoAxesYTickLabelsConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsAutoAxesZTickLabelsConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsAutoAxesLabelScaleConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsBGColorConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsThrottleConnected { get { throw new Exception("Not Yet Implemented"); } }

        public bool IsViewControlInputSet { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsImageNameInputSet { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsRecordEnableSet { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsRecordFileSet { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsRecordFormatSet { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsRecordResolutionSet { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsRecordAspectSet { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsRecFileInputSet { get { throw new Exception("Not Yet Implemented"); } }

        public bool IsRecordEnableConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsRecordFileConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsRecordFormatConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsRecordResolutionConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsRecordAspectConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsInteractionModeConnected { get { throw new Exception("Not Yet Implemented"); } }

        public bool IsRenderModeSet { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsButtonUpApproxSet { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsButtonDownApproxSet { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsButtonUpDensitySet { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsButtonDownDensitySet { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsRenderModeConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsButtonUpApproxConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsButtonDownApproxConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsButtonUpDensityConnected { get { throw new Exception("Not Yet Implemented"); } }
        public bool IsButtonDownDensityConnected { get { throw new Exception("Not Yet Implemented"); } }

        public bool IsDataDriven { get { throw new Exception("Not Yet Implemented"); } }

        public bool setInteractionMode(String mode) { throw new Exception("Not Yet Implemented"); }
        public void setInteractionModeParameter(DirectInteractionMode mode) { throw new Exception("Not Yet Implemented"); }
        public override void openImageWindow(bool manage)
        {
            base.openImageWindow(manage);
        }

        // Most nodes' id parameter is number 1 but a few aren't.  This number is
        // important because whenever you merge 2 nets, you update instance numbers.
        // When you do that, you must also change the id parameter and for that you
        // need its number.
        public override int getMessageIdParamNumber()
        {
            return ParamConst.IMAGETAG;
        }

        // On behalf of ImageFormatDialog (Save/Print Image dialogs) which needs to
        // know what strategy to use for saving the current image.
        public bool hardwareMode() { throw new Exception("Not Yet Implemented"); }

        // Determine if this node is a node of the given class
        public override bool isA(Symbol classname)
        {
            throw new Exception("Not Yet Implemented");
            return base.isA(classname);
        }

        public virtual void enableJava(String base_name, bool send) { throw new Exception("Not Yet Implemented"); }
        public virtual void disableJava(bool send) { throw new Exception("Not Yet Implemented"); }
        public virtual bool isJavified() { throw new Exception("Not Yet Implemented"); }
        public virtual bool isJavified(Node webOptions) { throw new Exception("Not Yet Implemented"); }
        public virtual void javifyNode(Node webOptions, Node w2) { throw new Exception("Not Yet Implemented"); }
        public virtual void unjavifyNode() { throw new Exception("Not Yet Implemented"); }
        public virtual String getJavaNodeName() { return "ImageNode"; }
        public virtual bool printInputAsJava(int input) { throw new Exception("Not Yet Implemented"); }
        public String getWebOptionsFormat() { throw new Exception("Not Yet Implemented"); }
        public bool isWebOptionsOrbit() { throw new Exception("Not Yet Implemented"); }
        public override bool printAsJava(StreamWriter sw)
        {
            throw new Exception("Not Yet Implemented");
            return base.printAsJava(sw);
        }
        public bool isWebOptionsImgIdConnected()
        {
            throw new Exception("Not Yet Implemented");
        }
    }
}
