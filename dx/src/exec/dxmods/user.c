/* Automatically generated - do not edit! */

#include <dx/dx.h>
#include <dx/modflags.h>

_dxf_user_modules()
{
    {
        extern Error m_AmbientLight(Object *, Object *);
        DXAddModule("AmbientLight", m_AmbientLight, 0,
            1, "color",
            1, "light");
    }
    {
        extern Error m_Append(Object *, Object *);
        DXAddModule("Append", m_Append, 0,
            43, "input", "object", "id", "object1", "id1", "object2", "id2", "object3", "id3", "object4", "id4", "object5", "id5", "object6", "id6", "object7", "id7", "object8", "id8", "object9", "id9", "object10", "id10", "object11", "id11", "object12", "id12", "object13", "id13", "object14", "id14", "object15", "id15", "object16", "id16", "object17", "id17", "object18", "id18", "object19", "id19", "object20", "id20",
            1, "group");
    }
    {
        extern Error m_Arrange(Object *, Object *);
        DXAddModule("Arrange", m_Arrange, 0,
            5, "group", "horizontal", "compact[visible:0]", "position[visible:0]", "size[visible:0]",
            1, "image");
    }
    {
        extern Error m_Attribute(Object *, Object *);
        DXAddModule("Attribute", m_Attribute, 0,
            2, "input", "attribute",
            1, "object");
    }
    {
        extern Error m_AutoAxes(Object *, Object *);
        DXAddModule("AutoAxes", m_AutoAxes, 0,
            19, "input", "camera", "labels", "ticks[visible:0]", "corners[visible:0]", "frame[visible:0]", "adjust[visible:0]", "cursor[visible:0]", "grid[visible:0]", "colors[visible:0]", "annotation[visible:0]", "labelscale[visible:0]", "font[visible:0]", "xticklocations[visible:0]", "yticklocations[visible:0]", "zticklocations[visible:0]", "xticklabels[visible:0]", "yticklabels[visible:0]", "zticklabels[visible:0]",
            1, "axes");
    }
    {
        extern Error m_AutoCamera(Object *, Object *);
        DXAddModule("AutoCamera", m_AutoCamera, 0,
            9, "object", "direction", "width[visible:0]", "resolution[visible:0]", "aspect[visible:0]", "up[visible:0]", "perspective[visible:0]", "angle[visible:0]", "background[visible:0]",
            1, "camera");
    }
    {
        extern Error m_AutoColor(Object *, Object *);
        DXAddModule("AutoColor", m_AutoColor, 0,
            10, "data", "opacity[visible:0]", "intensity[visible:0]", "start[visible:0]", "range[visible:0]", "saturation[visible:0]", "min", "max[visible:0]", "delayed[visible:0]", "outofrange[visible:0]",
            2, "mapped", "colormap");
    }
    {
        extern Error m_AutoGlyph(Object *, Object *);
        DXAddModule("AutoGlyph", m_AutoGlyph, 0,
            7, "data", "type", "shape", "scale", "ratio", "min[visible:0]", "max[visible:0]",
            1, "glyphs");
    }
    {
        extern Error m_AutoGrayScale(Object *, Object *);
        DXAddModule("AutoGrayScale", m_AutoGrayScale, 0,
            10, "data", "opacity[visible:0]", "hue[visible:0]", "start[visible:0]", "range[visible:0]", "saturation[visible:0]", "min[visible:0]", "max[visible:0]", "delayed[visible:0]", "outofrange[visible:0]",
            2, "mapped", "colormap");
    }
    {
        extern Error m_AutoGrid(Object *, Object *);
        DXAddModule("AutoGrid", m_AutoGrid, 0,
            6, "input", "densityfactor", "nearest", "radius", "exponent[visible:0]", "missing[visible:0]",
            1, "output");
    }
    {
        extern Error m_Band(Object *, Object *);
        DXAddModule("Band", m_Band, 0,
            4, "data", "value", "number", "remap",
            1, "band");
    }
    {
        extern Error m_CacheScene(Object *, Object *);
        DXAddModule("CacheScene", m_CacheScene, 0,
            3, "name", "pickobject", "pickcamera",
            0);
    }
    {
        extern Error m_Camera(Object *, Object *);
        DXAddModule("Camera", m_Camera, 0,
            9, "to", "from", "width", "resolution", "aspect", "up", "perspective", "angle", "background",
            1, "camera");
    }
    {
        extern Error m_Caption(Object *, Object *);
        DXAddModule("Caption", m_Caption, 0,
            9, "string", "position", "flag[visible:0]", "reference[visible:0]", "alignment[visible:0]", "height[visible:0]", "font[visible:0]", "direction[visible:0]", "up[visible:0]",
            1, "caption");
    }
    {
        extern Error m_Categorize(Object *, Object *);
        DXAddModule("Categorize", m_Categorize, 0,
            2, "field", "name",
            1, "categorized");
    }
    {
        extern Error m_CategoryStatistics(Object *, Object *);
        DXAddModule("CategoryStatistics", m_CategoryStatistics, 0,
            5, "input", "operation", "category[visible:0]", "data[visible:0]", "lookup[visible:0]",
            1, "statistics");
    }
    {
        extern Error m_ChangeGroupMember(Object *, Object *);
        DXAddModule("ChangeGroupMember", m_ChangeGroupMember, 0,
            5, "data", "operation", "id", "newmember", "newtag",
            1, "changed");
    }
    {
        extern Error m_ChangeGroupType(Object *, Object *);
        DXAddModule("ChangeGroupType", m_ChangeGroupType, 0,
            3, "data", "newtype", "idlist",
            1, "changed");
    }
    {
        extern Error m_ClipBox(Object *, Object *);
        DXAddModule("ClipBox", m_ClipBox, 0,
            2, "object", "corners",
            1, "clipped");
    }
    {
        extern Error m_ClipPlane(Object *, Object *);
        DXAddModule("ClipPlane", m_ClipPlane, 0,
            3, "object", "point", "normal",
            1, "clipped");
    }
    {
        extern Error m_Collect(Object *, Object *);
        DXAddModule("Collect", m_Collect, 
            MODULE_ERR_CONT,
            21, "object", "object1", "object2", "object3", "object4", "object5", "object6", "object7", "object8", "object9", "object10", "object11", "object12", "object13", "object14", "object15", "object16", "object17", "object18", "object19", "object20",
            1, "group");
    }
    {
        extern Error m_CollectNamed(Object *, Object *);
        DXAddModule("CollectNamed", m_CollectNamed, 0,
            42, "object", "name", "object1", "name1", "object2", "name2", "object3", "name3", "object4", "name4", "object5", "name5", "object6", "name6", "object7", "name7", "object8", "name8", "object9", "name9", "object10", "name10", "object11", "name11", "object12", "name12", "object13", "name13", "object14", "name14", "object15", "name15", "object16", "name16", "object17", "name17", "object18", "name18", "object19", "name19", "object20", "name20",
            1, "group");
    }
    {
        extern Error m_CollectMultiGrid(Object *, Object *);
        DXAddModule("CollectMultiGrid", m_CollectMultiGrid, 0,
            42, "object", "name", "object1", "name1", "object2", "name2", "object3", "name3", "object4", "name4", "object5", "name5", "object6", "name6", "object7", "name7", "object8", "name8", "object9", "name9", "object10", "name10", "object11", "name11", "object12", "name12", "object13", "name13", "object14", "name14", "object15", "name15", "object16", "name16", "object17", "name17", "object18", "name18", "object19", "name19", "object20", "name20",
            1, "multigrid");
    }
    {
        extern Error m_CollectSeries(Object *, Object *);
        DXAddModule("CollectSeries", m_CollectSeries, 0,
            44, "object", "position", "object", "position", "object1", "position1", "object2", "position2", "object3", "position3", "object4", "position4", "object5", "position5", "object6", "position6", "object7", "position7", "object8", "position8", "object9", "position9", "object10", "position10", "object11", "position11", "object12", "position12", "object13", "position13", "object14", "position14", "object15", "position15", "object16", "position16", "object17", "position17", "object18", "position18", "object19", "position19", "object20", "position20",
            1, "series");
    }
    {
        extern Error m_Color(Object *, Object *);
        DXAddModule("Color", m_Color, 0,
            5, "input", "color", "opacity", "component[visible:0]", "delayed[visible:0]",
            1, "colored");
    }
    {
        extern Error m_ColorBar(Object *, Object *);
        DXAddModule("ColorBar", m_ColorBar, 0,
            16, "colormap", "position", "shape", "horizontal", "ticks[visible:0]", "min[visible:0]", "max[visible:0]", "label", "colors[visible:0]", "annotation[visible:0]", "labelscale[visible:0]", "font[visible:0]", "ticklocations[visible:0]", "ticklabels[visible:0]", "usefixedfontsize[visible:0]", "fixedfontsize[visible:0]",
            1, "colorbar");
    }
    {
        extern Error m_Compute(Object *, Object *);
        DXAddModule("Compute", m_Compute, 0,
            22, "expression[visible:2]", "input", "input1", "input2", "input3", "input4", "input5", "input6", "input7", "input8", "input9", "input10", "input11", "input12", "input13", "input14", "input15", "input16", "input17", "input18", "input19", "input20",
            1, "output");
    }
    {
        extern Error m_Compute2(Object *, Object *);
        DXAddModule("Compute2", m_Compute2, 0,
            43, "expression", "name", "input", "name1", "input1", "name2", "input2", "name3", "input3", "name4", "input4", "name5", "input5", "name6", "input6", "name7", "input7", "name8", "input8", "name9", "input9", "name10", "input10", "name11", "input11", "name12", "input12", "name13", "input13", "name14", "input14", "name15", "input15", "name16", "input16", "name17", "input17", "name18", "input18", "name19", "input19", "name20", "input20",
            1, "output");
    }
    {
        extern Error m_Connect(Object *, Object *);
        DXAddModule("Connect", m_Connect, 0,
            3, "input", "method", "normal",
            1, "output");
    }
    {
        extern Error m_Construct(Object *, Object *);
        DXAddModule("Construct", m_Construct, 0,
            4, "origin", "deltas", "counts", "data",
            1, "output");
    }
    {
        extern Error m_Convert(Object *, Object *);
        DXAddModule("Convert", m_Convert, 0,
            4, "data", "incolorspace", "outcolorspace", "addpoints",
            1, "output");
    }
    {
        extern Error m_CopyContainer(Object *, Object *);
        DXAddModule("CopyContainer", m_CopyContainer, 0,
            1, "input",
            1, "copy");
    }
    {
        extern Error m_Describe(Object *, Object *);
        DXAddModule("Describe", m_Describe, 
            MODULE_SIDE_EFFECT,
            2, "object", "options",
            0);
    }
    {
        extern Error m_DFT(Object *, Object *);
        DXAddModule("DFT", m_DFT, 0,
            3, "input", "direction", "center",
            1, "output");
    }
    {
        extern Error m_Direction(Object *, Object *);
        DXAddModule("Direction", m_Direction, 0,
            3, "azimuth", "elevation", "distance",
            1, "point");
    }
    {
        extern Error m_Display(Object *, Object *);
        DXAddModule("Display", m_Display, 
            MODULE_PIN | MODULE_SIDE_EFFECT,
            46, "object", "camera", "where[visible:0]", "throttle[visible:0]", "name[visible:0]", "value[visible:0]", "name1[visible:0]", "value1[visible:0]", "name2[visible:0]", "value2[visible:0]", "name3[visible:0]", "value3[visible:0]", "name4[visible:0]", "value4[visible:0]", "name5[visible:0]", "value5[visible:0]", "name6[visible:0]", "value6[visible:0]", "name7[visible:0]", "value7[visible:0]", "name8[visible:0]", "value8[visible:0]", "name9[visible:0]", "value9[visible:0]", "name10[visible:0]", "value10[visible:0]", "name11[visible:0]", "value11[visible:0]", "name12[visible:0]", "value12[visible:0]", "name13[visible:0]", "value13[visible:0]", "name14[visible:0]", "value14[visible:0]", "name15[visible:0]", "value15[visible:0]", "name16[visible:0]", "value16[visible:0]", "name17[visible:0]", "value17[visible:0]", "name18[visible:0]", "value18[visible:0]", "name19[visible:0]", "value19[visible:0]", "name20[visible:0]", "value20[visible:0]",
            1, "where");
    }
    {
        extern Error m_DivCurl(Object *, Object *);
        DXAddModule("DivCurl", m_DivCurl, 0,
            2, "data", "method[visible:0]",
            2, "div", "curl");
    }
    {
        extern Error m_Done(Object *, Object *);
        DXAddModule("Done", m_Done, 
            MODULE_LOOP,
            1, "done",
            0);
    }
    {
        extern Error m_Echo(Object *, Object *);
        DXAddModule("Echo", m_Echo, 
            MODULE_SIDE_EFFECT,
            21, "string", "string1", "string2", "string3", "string4", "string5", "string6", "string7", "string8", "string9", "string10", "string11", "string12", "string13", "string14", "string15", "string16", "string17", "string18", "string19", "string20",
            0);
    }
    {
        extern Error m_Enumerate(Object *, Object *);
        DXAddModule("Enumerate", m_Enumerate, 0,
            5, "start", "end", "count", "delta", "method",
            1, "list");
    }
    {
        extern Error m_Equalize(Object *, Object *);
        DXAddModule("Equalize", m_Equalize, 0,
            6, "data", "bins", "min[visible:0]", "max[visible:0]", "ihist[visible:0]", "ohist[visible:0]",
            1, "equalized");
    }
    {
        extern Error m_Executive(Object *, Object *);
        DXAddModule("Executive", m_Executive, 
            MODULE_SIDE_EFFECT,
            22, "command", "value", "value1", "value2", "value3", "value4", "value5", "value6", "value7", "value8", "value9", "value10", "value11", "value12", "value13", "value14", "value15", "value16", "value17", "value18", "value19", "value20",
            0);
    }
    {
        extern Error m_Export(Object *, Object *);
        DXAddModule("Export", m_Export, 
            MODULE_SIDE_EFFECT,
            3, "object", "name", "format",
            0);
    }
    {
        extern Error m_Extract(Object *, Object *);
        DXAddModule("Extract", m_Extract, 0,
            2, "input", "name",
            1, "output");
    }
    {
        extern Error m_FaceNormals(Object *, Object *);
        DXAddModule("FaceNormals", m_FaceNormals, 0,
            1, "surface",
            1, "normals");
    }
    {
        extern Error m_Filter(Object *, Object *);
        DXAddModule("Filter", m_Filter, 0,
            4, "input", "filter", "component[visible:0]", "mask[visible:0]",
            1, "output");
    }
    {
        extern Error m_First(Object *, Object *);
        DXAddModule("First", m_First, 
            MODULE_LOOP,
            0,
            1, "first");
    }
    {
        extern Error m_ForEachMember(Object *, Object *);
        DXAddModule("ForEachMember", m_ForEachMember, 
            MODULE_LOOP,
            1, "object",
            3, "member", "index", "last");
    }
    {
        extern Error m_ForEachN(Object *, Object *);
        DXAddModule("ForEachN", m_ForEachN, 
            MODULE_LOOP,
            3, "start", "end", "delta",
            2, "current", "last");
    }
    {
        extern Error m_Format(Object *, Object *);
        DXAddModule("Format", m_Format, 0,
            22, "template", "value", "value1", "value2", "value3", "value4", "value5", "value6", "value7", "value8", "value9", "value10", "value11", "value12", "value13", "value14", "value15", "value16", "value17", "value18", "value19", "value20",
            1, "string");
    }
    {
        extern Error m_FFT(Object *, Object *);
        DXAddModule("FFT", m_FFT, 0,
            3, "input", "direction", "center",
            1, "output");
    }
    {
        extern Error m_Get(Object *, Object *);
        DXAddModule("Get", m_Get, 
            MODULE_ASYNCLOCAL | MODULE_CHANGES_STATE,
            3, "initial", "reset", "key[visible:2,rerun_key:1]",
            2, "object", "link");
    }
    {
        extern Error m_GetGlobal(Object *, Object *);
        DXAddModule("GetGlobal", m_GetGlobal, 
            MODULE_ASYNCLOCAL | MODULE_CHANGES_STATE,
            3, "initial", "reset", "key[visible:2,rerun_key:1]",
            2, "object", "link");
    }
    {
        extern Error m_GetLocal(Object *, Object *);
        DXAddModule("GetLocal", m_GetLocal, 
            MODULE_ASYNCLOCAL,
            3, "initial", "reset", "key[visible:2]",
            2, "object", "link");
    }
    {
        extern Error m_GetScene(Object *, Object *);
        DXAddModule("GetScene", m_GetScene, 
            MODULE_SIDE_EFFECT,
            1, "imagetag[visible:2]",
            2, "object", "camera");
    }
    {
        extern Error m_Glyph(Object *, Object *);
        DXAddModule("Glyph", m_Glyph, 0,
            7, "data", "type", "shape", "scale", "ratio", "min[visible:0]", "max[visible:0]",
            1, "glyphs");
    }
    {
        extern Error m_Gradient(Object *, Object *);
        DXAddModule("Gradient", m_Gradient, 0,
            2, "data", "method[visible:0]",
            1, "gradient");
    }
    {
        extern Error m_Grid(Object *, Object *);
        DXAddModule("Grid", m_Grid, 0,
            4, "point", "structure", "shape", "density",
            1, "grid");
    }
    {
        extern Error m_Histogram(Object *, Object *);
        DXAddModule("Histogram", m_Histogram, 0,
            5, "data", "bins", "min[visible:0]", "max[visible:0]", "out[visible:0]",
            2, "histogram", "median");
    }
    {
        extern Error m_ImageMessage(Object *, Object *);
        DXAddModule("ImageMessage", m_ImageMessage, 
            MODULE_SIDE_EFFECT,
            33, "id", "bkgndColor", "throttle", "recordEnable", "recordFile", "recordFormat", "recordResolution", "recordAspect", "axesEnabled", "axesLabels", "axesTicks", "axesCorners", "axesFrame", "axesAdjust", "axesCursor", "axesGrid", "axesColors", "axesAnnotate", "axesLabelScale", "axesFont", "axesXTickLocs", "axesYTickLocs", "axesZTickLocs", "axesXTickLabels", "axesYTickLabels", "axesZTickLabels", "interactionMode", "title", "renderMode", "buttonUpApprox", "buttonDownApprox", "buttonUpDensity", "buttonDownDensity",
            0);
    }
    {
        extern Error m_Import(Object *, Object *);
        DXAddModule("Import", m_Import, 
            MODULE_PIN,
            6, "name", "variable", "format", "start[visible:0]", "end[visible:0]", "delta[visible:0]",
            1, "data");
    }
    {
        extern Error m_ImportSpreadsheet(Object *, Object *);
        DXAddModule("ImportSpreadsheet", m_ImportSpreadsheet, 0,
            10, "filename", "delimiter", "columnname[visible:0]", "format[visible:0]", "categorize[visible:0]", "start[visible:0]", "end[visible:0]", "delta[visible:0]", "headerlines[visible:0]", "labelline[visible:0]",
            2, "data", "labellist");
    }
    {
        extern Error m_Include(Object *, Object *);
        DXAddModule("Include", m_Include, 0,
            6, "data", "min", "max", "exclude", "cull", "pointwise",
            1, "output");
    }
    {
        extern Error m_Inquire(Object *, Object *);
        DXAddModule("Inquire", m_Inquire, 0,
            3, "input", "inquiry", "value",
            1, "output");
    }
    {
        extern Error m_Isolate(Object *, Object *);
        DXAddModule("Isolate", m_Isolate, 0,
            2, "field", "scale",
            1, "output");
    }
    {
        extern Error m_Isosurface(Object *, Object *);
        DXAddModule("Isosurface", m_Isosurface, 0,
            6, "data", "value", "number", "gradient[visible:0]", "flag[visible:0]", "direction[visible:0]",
            1, "surface");
    }
    {
        extern Error m_KeyIn(Object *, Object *);
        DXAddModule("KeyIn", m_KeyIn, 
            MODULE_SIDE_EFFECT,
            1, "prompt",
            0);
    }
    {
        extern Error m_Legend(Object *, Object *);
        DXAddModule("Legend", m_Legend, 0,
            10, "stringlist", "colorlist", "position", "shape", "horizontal", "label", "colors[visible:0]", "annotation[visible:0]", "labelscale[visible:0]", "font[visible:0]",
            1, "legend");
    }
    {
        extern Error m_Light(Object *, Object *);
        DXAddModule("Light", m_Light, 0,
            3, "where", "color", "camera",
            1, "light");
    }
    {
        extern Error m_List(Object *, Object *);
        DXAddModule("List", m_List, 0,
            21, "object", "object1", "object2", "object3", "object4", "object5", "object6", "object7", "object8", "object9", "object10", "object11", "object12", "object13", "object14", "object15", "object16", "object17", "object18", "object19", "object20",
            1, "list");
    }
    {
        extern Error m_Lookup(Object *, Object *);
        DXAddModule("Lookup", m_Lookup, 0,
            7, "input", "table", "data[visible:0]", "lookup[visible:0]", "value[visible:0]", "destination[visible:0]", "ignore[visible:0]",
            1, "lookedup");
    }
    {
        extern Error m_Map(Object *, Object *);
        DXAddModule("Map", m_Map, 0,
            4, "input", "map", "source[visible:0]", "destination[visible:0]",
            1, "output");
    }
    {
        extern Error m_MapToPlane(Object *, Object *);
        DXAddModule("MapToPlane", m_MapToPlane, 0,
            3, "data", "point", "normal",
            1, "plane");
    }
    {
        extern Error m_Mark(Object *, Object *);
        DXAddModule("Mark", m_Mark, 0,
            2, "input", "name",
            1, "output");
    }
    {
        extern Error m_Measure(Object *, Object *);
        DXAddModule("Measure", m_Measure, 0,
            2, "input", "what",
            1, "output");
    }
    {
        extern Error m_Message(Object *, Object *);
        DXAddModule("Message", m_Message, 
            MODULE_SIDE_EFFECT,
            3, "message", "type", "popup",
            0);
    }
    {
        extern Error m_Morph(Object *, Object *);
        DXAddModule("Morph", m_Morph, 0,
            3, "input", "operation", "mask",
            1, "output");
    }
    {
        extern Error m_Normals(Object *, Object *);
        DXAddModule("Normals", m_Normals, 0,
            2, "surface", "method",
            1, "normals");
    }
    {
        extern Error m_Options(Object *, Object *);
        DXAddModule("Options", m_Options, 0,
            43, "input", "attribute", "value", "attribute1", "value1", "attribute2", "value2", "attribute3", "value3", "attribute4", "value4", "attribute5", "value5", "attribute6", "value6", "attribute7", "value7", "attribute8", "value8", "attribute9", "value9", "attribute10", "value10", "attribute11", "value11", "attribute12", "value12", "attribute13", "value13", "attribute14", "value14", "attribute15", "value15", "attribute16", "value16", "attribute17", "value17", "attribute18", "value18", "attribute19", "value19", "attribute20", "value20",
            1, "output");
    }
    {
        extern Error m_Overlay(Object *, Object *);
        DXAddModule("Overlay", m_Overlay, 0,
            3, "overlay", "base", "blend",
            1, "combined");
    }
    {
        extern Error m_Parse(Object *, Object *);
        DXAddModule("Parse", m_Parse, 0,
            2, "input", "format",
            21, "value", "value1", "value2", "value3", "value4", "value5", "value6", "value7", "value8", "value9", "value10", "value11", "value12", "value13", "value14", "value15", "value16", "value17", "value18", "value19", "value20");
    }
    {
        extern Error m_Partition(Object *, Object *);
        DXAddModule("Partition", m_Partition, 0,
            3, "input", "n", "size[visible:0]",
            1, "partitioned");
    }
    {
        extern Error m_Pick(Object *, Object *);
        DXAddModule("Pick", m_Pick, 0,
            9, "pickname[visible:2]", "imagename[visible:2]", "locations[visible:0]", "reexecute[visible:2]", "first", "persistent[visible:0]", "interpolate[visible:0]", "object[visible:0]", "camera[visible:0]",
            1, "picked");
    }
    {
        extern Error m_Pie(Object *, Object *);
        DXAddModule("Pie", m_Pie, 0,
            17, "percents", "percentflag", "radius", "radiusscale[visible:0]", "radiusmin[visible:0]", "radiusmax[visible:0]", "radiusratio[visible:0]", "height", "heightscale[visible:0]", "heightmin[visible:0]", "heightmax[visible:0]", "heightratio[visible:0]", "quality", "colors[visible:0]", "labels", "labelformat[visible:0]", "showpercents[visible:0]",
            5, "wedges", "edges", "labels", "percents", "colors");
    }
    {
        extern Error m_Plot(Object *, Object *);
        DXAddModule("Plot", m_Plot, 0,
            26, "input", "labels", "ticks", "corners", "adjust[visible:0]", "frame[visible:0]", "type[visible:0]", "grid[visible:0]", "aspect", "colors[visible:0]", "annotation[visible:0]", "labelscale[visible:0]", "font[visible:0]", "input2[visible:0]", "label2[visible:0]", "ticks2[visible:0]", "corners2[visible:0]", "type2[visible:0]", "xticklocations[visible:0]", "y1ticklocations[visible:0]", "y2ticklocations[visible:0]", "xticklabels[visible:0]", "y1ticklabels[visible:0]", "y2ticklabels[visible:0]", "usefixedfontsize[visible:0]", "fixedfontsize[visible:0]",
            1, "plot");
    }
    {
        extern Error m_Post(Object *, Object *);
        DXAddModule("Post", m_Post, 0,
            2, "input", "dependency",
            1, "output");
    }
    {
        extern Error m_Print(Object *, Object *);
        DXAddModule("Print", m_Print, 
            MODULE_SIDE_EFFECT,
            3, "object", "options", "component",
            0);
    }
    {
        extern Error m_QuantizeImage(Object *, Object *);
        DXAddModule("QuantizeImage", m_QuantizeImage, 0,
            2, "images", "nColors",
            1, "images");
    }
    {
        extern Error m_ReadImage(Object *, Object *);
        DXAddModule("ReadImage", m_ReadImage, 0,
            9, "name", "format", "start[visible:0]", "end[visible:0]", "delta[visible:0]", "width[visible:0]", "height[visible:0]", "delayed[visible:0]", "colortype[visible:0]",
            1, "image");
    }
    {
        extern Error m_ReadImageWindow(Object *, Object *);
        DXAddModule("ReadImageWindow", m_ReadImageWindow, 
            MODULE_PIN,
            1, "where",
            1, "image");
    }
    {
        extern Error m_Reduce(Object *, Object *);
        DXAddModule("Reduce", m_Reduce, 0,
            2, "input", "factor",
            1, "reduced");
    }
    {
        extern Error m_Refine(Object *, Object *);
        DXAddModule("Refine", m_Refine, 0,
            2, "input", "level",
            1, "refined");
    }
    {
        extern Error m_Regrid(Object *, Object *);
        DXAddModule("Regrid", m_Regrid, 0,
            6, "input", "grid", "nearest", "radius", "exponent", "missing",
            1, "output");
    }
    {
        extern Error m_Remove(Object *, Object *);
        DXAddModule("Remove", m_Remove, 0,
            2, "input", "name",
            1, "output");
    }
    {
        extern Error m_Rename(Object *, Object *);
        DXAddModule("Rename", m_Rename, 0,
            3, "input", "oldname", "newname",
            1, "output");
    }
    {
        extern Error m_Render(Object *, Object *);
        DXAddModule("Render", m_Render, 0,
            3, "object", "camera", "format[visible:0]",
            1, "image");
    }
    {
        extern Error m_Reorient(Object *, Object *);
        DXAddModule("Reorient", m_Reorient, 0,
            2, "image", "how",
            1, "image");
    }
    {
        extern Error m_Replace(Object *, Object *);
        DXAddModule("Replace", m_Replace, 0,
            4, "srcfield", "dstfield", "srcname", "dstname",
            1, "out");
    }
    {
        extern Error m_Ribbon(Object *, Object *);
        DXAddModule("Ribbon", m_Ribbon, 0,
            2, "line", "width",
            1, "ribbon");
    }
    {
        extern Error m_Rotate(Object *, Object *);
        DXAddModule("Rotate", m_Rotate, 0,
            45, "input", "axis", "rotation", "axis", "rotation", "axis1", "rotation1", "axis2", "rotation2", "axis3", "rotation3", "axis4", "rotation4", "axis5", "rotation5", "axis6", "rotation6", "axis7", "rotation7", "axis8", "rotation8", "axis9", "rotation9", "axis10", "rotation10", "axis11", "rotation11", "axis12", "rotation12", "axis13", "rotation13", "axis14", "rotation14", "axis15", "rotation15", "axis16", "rotation16", "axis17", "rotation17", "axis18", "rotation18", "axis19", "rotation19", "axis20", "rotation20",
            1, "output");
    }
    {
        extern Error m_Route(Object *, Object *);
        DXAddModule("Route", m_Route, 0,
            2, "selector", "input",
            21, "output", "output1", "output2", "output3", "output4", "output5", "output6", "output7", "output8", "output9", "output10", "output11", "output12", "output13", "output14", "output15", "output16", "output17", "output18", "output19", "output20");
    }
    {
        extern Error m_RubberSheet(Object *, Object *);
        DXAddModule("RubberSheet", m_RubberSheet, 0,
            4, "data", "scale", "min[visible:0]", "max[visible:0]",
            1, "graph");
    }
    {
        extern Error m_Sample(Object *, Object *);
        DXAddModule("Sample", m_Sample, 0,
            2, "manifold", "density",
            1, "samples");
    }
    {
        extern Error m_Scale(Object *, Object *);
        DXAddModule("Scale", m_Scale, 0,
            2, "input", "scaling",
            1, "output");
    }
    {
        extern Error m_ScaleScreen(Object *, Object *);
        DXAddModule("ScaleScreen", m_ScaleScreen, 0,
            4, "object", "scalefactor", "finalres", "currentcamera",
            2, "output", "newcamera");
    }
    {
        extern Error m_Select(Object *, Object *);
        DXAddModule("Select", m_Select, 0,
            3, "input", "which", "except[visible:0]",
            1, "object");
    }
    {
        extern Error m_Set(Object *, Object *);
        DXAddModule("Set", m_Set, 0,
            3, "object", "link", "key[visible:2]",
            0);
    }
    {
        extern Error m_SetGlobal(Object *, Object *);
        DXAddModule("SetGlobal", m_SetGlobal, 0,
            3, "object", "link", "key[visible:2]",
            0);
    }
    {
        extern Error m_SetLocal(Object *, Object *);
        DXAddModule("SetLocal", m_SetLocal, 0,
            3, "object", "link", "key[visible:2]",
            0);
    }
    {
        extern Error m_Shade(Object *, Object *);
        DXAddModule("Shade", m_Shade, 0,
            8, "input", "shade", "how", "specular[visible:0]", "shininess[visible:0]", "diffuse[visible:0]", "ambient[visible:0]", "reversefront[visible:0]",
            1, "output");
    }
    {
        extern Error m_ShowBoundary(Object *, Object *);
        DXAddModule("ShowBoundary", m_ShowBoundary, 0,
            2, "input", "validity",
            1, "output");
    }
    {
        extern Error m_ShowBox(Object *, Object *);
        DXAddModule("ShowBox", m_ShowBox, 0,
            1, "input",
            2, "box", "center");
    }
    {
        extern Error m_ShowConnections(Object *, Object *);
        DXAddModule("ShowConnections", m_ShowConnections, 0,
            1, "input",
            1, "output");
    }
    {
        extern Error m_ShowPositions(Object *, Object *);
        DXAddModule("ShowPositions", m_ShowPositions, 0,
            2, "input", "every[visible:0]",
            1, "output");
    }
    {
        extern Error m_SimplifySurface(Object *, Object *);
        DXAddModule("SimplifySurface", m_SimplifySurface, 0,
            8, "original_surface", "max_error", "max_data_error", "volume[visible:0]", "boundary[visible:0]", "length[visible:0]", "data[visible:0]", "stats[visible:0]",
            1, "simplified");
    }
    {
        extern Error m_Slab(Object *, Object *);
        DXAddModule("Slab", m_Slab, 0,
            4, "input", "dimension", "position", "thickness",
            1, "output");
    }
    {
        extern Error m_Slice(Object *, Object *);
        DXAddModule("Slice", m_Slice, 0,
            3, "input", "dimension", "position",
            1, "output");
    }
    {
        extern Error m_Sort(Object *, Object *);
        DXAddModule("Sort", m_Sort, 0,
            2, "field", "descending",
            1, "result");
    }
    {
        extern Error m_Stack(Object *, Object *);
        DXAddModule("Stack", m_Stack, 0,
            2, "input", "dimension",
            1, "output");
    }
    {
        extern Error m_Statistics(Object *, Object *);
        DXAddModule("Statistics", m_Statistics, 0,
            1, "data",
            5, "mean", "sd", "var", "min", "max");
    }
    {
        extern Error m_Streakline(Object *, Object *);
        DXAddModule("Streakline", m_Streakline, 0,
            10, "name[visible:0]", "data", "start", "time", "head", "frame", "curl", "flag", "stepscale", "hold",
            1, "line");
    }
    {
        extern Error m_Streamline(Object *, Object *);
        DXAddModule("Streamline", m_Streamline, 0,
            7, "data", "start", "time", "head", "curl", "flag", "stepscale",
            1, "line");
    }
    {
        extern Error m_SuperviseState(Object *, Object *);
        DXAddModule("SuperviseState", m_SuperviseState, 
            MODULE_ASYNC,
            9, "where", "defaultCamera", "resetCamera", "object", "resetObject", "size", "events", "mode", "args",
            4, "object", "camera", "where", "events");
    }
    {
        extern Error m_SuperviseWindow(Object *, Object *);
        DXAddModule("SuperviseWindow", m_SuperviseWindow, 
            MODULE_ASYNC | MODULE_PIN,
            11, "name", "display", "size", "offset", "parent", "depth", "visibility", "pick", "sizeFlag", "offsetFlag", "decorations",
            3, "where", "size", "events");
    }
    {
        extern Error m_Switch(Object *, Object *);
        DXAddModule("Switch", m_Switch, 0,
            22, "selector", "input", "input1", "input2", "input3", "input4", "input5", "input6", "input7", "input8", "input9", "input10", "input11", "input12", "input13", "input14", "input15", "input16", "input17", "input18", "input19", "input20",
            1, "output");
    }
    {
        extern Error m_System(Object *, Object *);
        DXAddModule("System", m_System, 
            MODULE_SIDE_EFFECT,
            1, "string",
            0);
    }
    {
        extern Error m_Text(Object *, Object *);
        DXAddModule("Text", m_Text, 0,
            6, "string", "position", "height", "font", "direction[visible:0]", "up[visible:0]",
            1, "text");
    }
    {
        extern Error m_Trace(Object *, Object *);
        DXAddModule("Trace", m_Trace, 
            MODULE_SIDE_EFFECT,
            2, "what", "how",
            0);
    }
    {
        extern Error m_Transform(Object *, Object *);
        DXAddModule("Transform", m_Transform, 0,
            2, "input", "transform",
            1, "output");
    }
    {
        extern Error m_Translate(Object *, Object *);
        DXAddModule("Translate", m_Translate, 0,
            2, "input", "translation",
            1, "output");
    }
    {
        extern Error m_Transpose(Object *, Object *);
        DXAddModule("Transpose", m_Transpose, 0,
            2, "input", "dimensions",
            1, "output");
    }
    {
        extern Error m_Tube(Object *, Object *);
        DXAddModule("Tube", m_Tube, 0,
            4, "line", "diameter", "ngon[visible:0]", "style[visible:0]",
            1, "tube");
    }
    {
        extern Error m_Unmark(Object *, Object *);
        DXAddModule("Unmark", m_Unmark, 0,
            2, "input", "name",
            1, "output");
    }
    {
        extern Error m_UpdateCamera(Object *, Object *);
        DXAddModule("UpdateCamera", m_UpdateCamera, 0,
            10, "camera", "to", "from", "width", "resolution", "aspect", "up", "perspective", "angle", "background",
            1, "camera");
    }
    {
        extern Error m_Usage(Object *, Object *);
        DXAddModule("Usage", m_Usage, 
            MODULE_SIDE_EFFECT,
            2, "what", "how",
            0);
    }
    {
        extern Error m_Verify(Object *, Object *);
        DXAddModule("Verify", m_Verify, 0,
            2, "input", "how",
            1, "output");
    }
    {
        extern Error m_VisualObject(Object *, Object *);
        DXAddModule("VisualObject", m_VisualObject, 0,
            2, "input", "options",
            1, "output");
    }
    {
        extern Error m_WriteImage(Object *, Object *);
        DXAddModule("WriteImage", m_WriteImage, 
            MODULE_SIDE_EFFECT,
            4, "image", "name", "format", "frame",
            0);
    }
    {
        extern Error m_DXLInputNamed(Object *, Object *);
        DXAddModule("DXLInputNamed", m_DXLInputNamed, 
            MODULE_ASYNC,
            2, "name", "default",
            1, "output");
    }
    {
        extern Error m_DXLOutput(Object *, Object *);
        DXAddModule("DXLOutput", m_DXLOutput, 
            MODULE_SIDE_EFFECT,
            2, "label[visible:2]", "value",
            0);
    }
    {
        extern Error m_DXLOutputNamed(Object *, Object *);
        DXAddModule("DXLOutputNamed", m_DXLOutputNamed, 
            MODULE_SIDE_EFFECT,
            2, "name", "value",
            0);
    }
    {
        extern Error m_Execute(Object *, Object *);
        DXAddModule("Execute", m_Execute, 0,
            1, "action",
            0);
    }
    {
        extern Error m_ManageColormapEditor(Object *, Object *);
        DXAddModule("ManageColormapEditor", m_ManageColormapEditor, 0,
            3, "name", "open", "how",
            0);
    }
    {
        extern Error m_ManageControlPanel(Object *, Object *);
        DXAddModule("ManageControlPanel", m_ManageControlPanel, 0,
            2, "name", "open",
            0);
    }
    {
        extern Error m_ManageImageWindow(Object *, Object *);
        DXAddModule("ManageImageWindow", m_ManageImageWindow, 0,
            3, "name", "open", "how",
            0);
    }
    {
        extern Error m_ManageSequencer(Object *, Object *);
        DXAddModule("ManageSequencer", m_ManageSequencer, 0,
            1, "open",
            0);
    }
    {
        extern Error m_Integer(Object *, Object *);
        DXAddModule("Integer", m_Integer, 
            MODULE_REROUTABLE | MODULE_REACH,
            11, "id[visible:2]", "data[cache:2]", "value[visible:2,reroute:0]", "refresh[visible:0,cache:2]", "min[visible:0,cache:2]", "max[visible:0,cache:2]", "delta[visible:0,cache:2]", "method[visible:0,cache:2]", "reserved2[visible:2]", "reserved3[visible:2]", "label[visible:0,cache:2]",
            1, "output");
    }
    {
        extern Error m_IntegerList(Object *, Object *);
        DXAddModule("IntegerList", m_IntegerList, 
            MODULE_REROUTABLE | MODULE_REACH,
            11, "id[visible:2]", "data[cache:2]", "value[visible:2,reroute:0]", "refresh[visible:0,cache:2]", "min[visible:0,cache:2]", "max[visible:0,cache:2]", "delta[visible:0,cache:2]", "method[visible:0,cache:2]", "reserved2[visible:2]", "nitems[visible:0,cache:2]", "label[visible:0,cache:2]",
            1, "output");
    }
    {
        extern Error m_Scalar(Object *, Object *);
        DXAddModule("Scalar", m_Scalar, 
            MODULE_REROUTABLE | MODULE_REACH,
            11, "id[visible:2]", "data[cache:2]", "value[visible:2,reroute:0]", "refresh[visible:0,cache:2]", "min[visible:0,cache:2]", "max[visible:0,cache:2]", "delta[visible:0,cache:2]", "method[visible:0,cache:2]", "decimals[visible:0,cache:2]", "reserved2[visible:2]", "label[visible:0,cache:2]",
            1, "output");
    }
    {
        extern Error m_ScalarList(Object *, Object *);
        DXAddModule("ScalarList", m_ScalarList, 
            MODULE_REROUTABLE | MODULE_REACH,
            11, "id[visible:2]", "data[cache:2]", "value[visible:2,reroute:0]", "refresh[visible:0,cache:2]", "min[visible:0,cache:2]", "max[visible:0,cache:2]", "delta[visible:0,cache:2]", "method[visible:0,cache:2]", "decimals[visible:0,cache:2]", "nitems[visible:0,cache:2]", "label[visible:0,cache:2]",
            1, "output");
    }
    {
        extern Error m_SetDXLInputNamed(Object *, Object *);
        DXAddModule("SetDXLInputNamed", m_SetDXLInputNamed, 0,
            2, "name", "object",
            0);
    }
    {
        extern Error m_Vector(Object *, Object *);
        DXAddModule("Vector", m_Vector, 
            MODULE_REROUTABLE | MODULE_REACH,
            11, "id[visible:2]", "data[cache:2]", "value[visible:2,reroute:0]", "refresh[visible:0,cache:2]", "min[visible:0,cache:2]", "max[visible:0,cache:2]", "delta[visible:0,cache:2]", "method[visible:0,cache:2]", "decimals[visible:0,cache:2]", "reserved2[visible:2]", "label[visible:0,cache:2]",
            1, "output");
    }
    {
        extern Error m_VectorList(Object *, Object *);
        DXAddModule("VectorList", m_VectorList, 
            MODULE_REROUTABLE | MODULE_REACH,
            11, "id[visible:2]", "data[cache:2]", "value[visible:2,reroute:0]", "refresh[visible:0,cache:2]", "min[visible:0,cache:2]", "max[visible:0,cache:2]", "delta[visible:0,cache:2]", "method[visible:0,cache:2]", "decimals[visible:0,cache:2]", "nitems[visible:0,cache:2]", "label[visible:0,cache:2]",
            1, "output");
    }
    {
        extern Error m_Selector(Object *, Object *);
        DXAddModule("Selector", m_Selector, 
            MODULE_REROUTABLE | MODULE_REACH,
            7, "id[visible:2]", "currentstring[visible:2,reroute:1]", "currentvalue[visible:2,reroute:0]", "stringdata[cache:2]", "valuelist[visible:0,cache:2]", "cull[visible:0,cache:2]", "label[visible:0,cache:2]",
            2, "value", "name");
    }
    {
        extern Error m_SelectorList(Object *, Object *);
        DXAddModule("SelectorList", m_SelectorList, 
            MODULE_REROUTABLE | MODULE_REACH,
            7, "id[visible:2]", "currentstring[visible:2,reroute:1]", "currentvalue[visible:2,reroute:0]", "stringdata[cache:2]", "valuelist[visible:0,cache:2]", "cull[visible:0,cache:2]", "label[visible:0,cache:2]",
            2, "value", "name");
    }
    {
        extern Error m_Colormap(Object *, Object *);
        DXAddModule("Colormap", m_Colormap, 
            MODULE_REROUTABLE | MODULE_REACH,
            19, "huemap[visible:2]", "satmap[visible:2]", "valmap[visible:2]", "opmap[visible:2]", "id[visible:2]", "data[cache:2]", "min[visible:0,cache:2]", "max[visible:0,cache:2]", "nbins[visible:0,cache:2]", "colormap[cache:2]", "opacity[cache:2]", "minmax[visible:2]", "defaulthue[visible:2]", "defaultsat[visible:2]", "defaultval[visible:2]", "defaultop[visible:2]", "defaultmin[visible:2]", "defaultmax[visible:2]", "title[visible:0,cache:2]",
            2, "rgb", "opacity");
    }
    {
        extern Error m_Sequencer(Object *, Object *);
        DXAddModule("Sequencer", m_Sequencer, 
            MODULE_REROUTABLE | MODULE_REACH,
            7, "id[visible:2]", "data[visible:2]", "frame[visible:2,reroute:0]", "min[cache:2]", "max[cache:2]", "delta[visible:0,cache:2]", "attr[visible:2]",
            1, "frame");
    }
    {
        extern Error m_Toggle(Object *, Object *);
        DXAddModule("Toggle", m_Toggle, 
            MODULE_REROUTABLE | MODULE_REACH,
            6, "id[visible:2]", "currentval[visible:2,reroute:0]", "isset[visible:2]", "setvalue[cache:2]", "unsetvalue[cache:2]", "label[visible:0,cache:2]",
            1, "output");
    }
}
