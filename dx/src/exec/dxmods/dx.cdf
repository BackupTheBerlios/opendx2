#####################################################################
# (c) COPYRIGHT International Business Machines Corporation 1991-1995
# ALL RIGHTS RESERVED.
#####################################################################
# 1 "userTmp.c"


MODULE AmbientLight
CATEGORY Rendering
DESCRIPTION produces an ambient light
INPUT color; vector or string; [0.2 0.2 0.2]; color and intensity of light
OPTIONS red ; green ; blue ; white
OUTPUT light; light; the ambient light

MODULE Append
CATEGORY Structuring
DESCRIPTION adds objects to an existing group
INPUT input; group; (no default); group to add objects to
INPUT object; object; (no default); object to be added
INPUT id; scalar or string; (no default); series position or name of object
REPEAT 2
OUTPUT group; group; the group with objects added

MODULE Arrange
CATEGORY Rendering
DESCRIPTION arranges images for display
INPUT group; image group; (none); images to be displayed
INPUT horizontal; integer; (infinity); number of images in horizontal dimension
OPTIONS 1 ; 2 ; 3 ; 4
INPUT compact [visible:0]; vector; [0 0]; make image compact in x and/or y
INPUT position [visible:0]; vector; [0.5 0.5]; position of each image in its frame
INPUT size [visible:0]; vector; [0 0]; force size of each frame to this number of pixels
OUTPUT image; image; resulting image

MODULE Attribute
CATEGORY Structuring
DESCRIPTION extracts an attribute from an object
INPUT input; object; (none); object from which attribute is obtained
INPUT attribute; string; "name"; attribute name
OUTPUT object; object; attribute value

MODULE AutoAxes
CATEGORY Annotation
DESCRIPTION produces an axes box to enclose a given object
INPUT input; object; (none); object to enclose
INPUT camera; camera; (none); viewpoint
INPUT labels; string list; (no labels); labels for axes
INPUT ticks [visible:0]; integer or integer list; 15; the approximate number of major ticks (0 to suppress)
INPUT corners [visible:0]; vector list or object; (input object); bounds of axes
INPUT frame [visible:0]; flag; 0; type of framing
OPTIONS false ; true
INPUT adjust [visible:0]; flag; 1; whether to adjust the endpoints to match tick marks
OPTIONS true; false
INPUT cursor [visible:0]; vector; (no cursor); cursor position
INPUT grid [visible:0]; flag; 0; show grid lines on background
OPTIONS false; true
INPUT colors [visible:0]; vector list or string list; (appropriate); colors for annotation
INPUT annotation [visible:0]; string list; "all"; annotation objects to color
OPTIONS all; background; grid; labels; ticks
INPUT labelscale [visible:0]; scalar; 1.0; scale factor for labels
INPUT font [visible:0]; string; (standard); font to use for labels
OPTIONS area; cyril_d; fixed; gothiceng_t; gothicger_t; gothicit_t
OPTIONS greek_d; greek_s; italic_d; italic_t; pitman; roman_d
OPTIONS roman_dser; roman_s; roman_tser; roman_ext; script_d
OPTIONS script_s; variable;
OPTIONS swiss; swissbld; swissit; swissbldit; dutch; dutchit; 
OPTIONS swisscnd; domcasual; symbol; monospace;
INPUT xticklocations [visible:0]; scalar list; (appropriate); set of x tick locations
INPUT yticklocations [visible:0]; scalar list; (appropriate); set of y tick locations
INPUT zticklocations [visible:0]; scalar list; (appropriate); set of z tick locations
INPUT xticklabels [visible:0]; string list; (xticklocations); labels for x tick locations
INPUT yticklabels [visible:0]; string list; (yticklocations); labels for y tick locations
INPUT zticklabels [visible:0]; string list; (zticklocations); labels for z tick locations
OUTPUT axes; color field; the axes box plus the input

MODULE AutoCamera
CATEGORY Rendering
DESCRIPTION produces a camera
INPUT object; vector or object; (none); object to look at
INPUT direction; vector or string or object; "front"; position of camera
OPTIONS front; back; top; bottom; left; right; diagonal
OPTIONS off-front; off-back; off-top; off-bottom; off-left; off-right
OPTIONS off-diagonal
INPUT width [visible:0]; scalar or object; (input dependent); width of field of view
INPUT resolution [visible:0]; integer; 640; pixels across image
INPUT aspect [visible:0]; scalar; 0.75; height/width
OPTIONS .25 ; .50 ; .75; 1.0; 1.25; 1.5
INPUT up [visible:0]; vector; [0 1 0]; up direction
OPTIONS [1 0 0 ] ; [0 1 0 ]; [0 0 1]
INPUT perspective [visible:0]; flag; 0; orthographic (0) or perspective (1) camera
OPTIONS false; true
INPUT angle [visible:0]; scalar; 30.0; view angle in degrees (for perspective projection)
OPTIONS 15 ; 30 ; 45 
INPUT background [visible:0]; vector or string; "black"; image background color
OPTIONS black ; white ; red ; green ; blue
OUTPUT camera; camera; resulting camera

MODULE AutoColor
CATEGORY Transformation
DESCRIPTION automatically colors a field
INPUT data; data field; (none); field to color
INPUT opacity [visible:0]; scalar; (input dependent); opacity, between 0 and 1
OPTIONS 0.1; 0.25; 0.5; 0.75; 1.0
INPUT intensity [visible:0]; scalar; 1.0; color intensity
INPUT start [visible:0]; scalar; 0.6666; starting color (default=blue)
INPUT range [visible:0]; scalar; 0.6666; range of color (default=blue to red)
INPUT saturation [visible:0]; scalar; 1; saturation, between 0 and 1
INPUT min; scalar or data field; (min of data); minimum of data to color
INPUT max [visible:0]; scalar or data field; (max of data); maximum of data to color
INPUT delayed [visible:0]; flag; 0; delay applying color and opacity maps (byte data only)
OPTIONS false; true
INPUT outofrange [visible:0]; vector list or string list; [.3 .3 .3]; how to color out of range points
OPTIONS color of min; color of max; gray; red; black
OUTPUT mapped; color field; color mapped input field
OUTPUT colormap; field; RGB color map used

MODULE AutoGlyph
CATEGORY Annotation
DESCRIPTION assigns an appropriate glyph to each point; scale is in relative units
INPUT data; data field; (none); set of points to which glyphs will be assigned
INPUT type; scalar or string or field or group; (input dependent); glyph type
OPTIONS speedy; spiffy; standard; 0.0; 1.0; 0.5; text
OPTIONS colored text; cube; square
OPTIONS arrow2D; circle; diamond; needle
OPTIONS needle2D; rocket; rocket2D; sphere
INPUT shape; scalar; 1.0; factor to describe shape of glyph
OPTIONS .25 ; .50 ; 1.0; 2.0; 3.0
INPUT scale; scalar; 1.0; scale factor for size of glyphs
OPTIONS .25 ; .50 ; 1.0; 2.0; 3.0;
INPUT ratio; scalar; (0.05 or 0); ratio in size (scalars or vectors) between smallest and largest glyphs
INPUT min [visible:0]; scalar or field; (min of data value or 0); data value which gets the minimum size glyph
INPUT max [visible:0]; scalar or field; (max of data); data value which gets the maximum size glyph
OUTPUT glyphs; color field; set of glyphs

MODULE AutoGrayScale
CATEGORY Transformation
DESCRIPTION automatically colors a field using a gray scale
INPUT data; data field; (none); field to color
INPUT opacity [visible:0]; scalar; (input dependent); opacity, between 0 and 1
INPUT hue [visible:0]; scalar; 0.0; hue
INPUT start [visible:0]; scalar; 0.0; starting intensity
INPUT range [visible:0]; scalar; 1.0; range of intensity
INPUT saturation [visible:0]; scalar; 0; saturation, between 0 and 1
INPUT min [visible:0]; scalar or data field; (min of data); minimum of data to color
INPUT max [visible:0]; scalar or data field; (max of data); maximum of data to color
INPUT delayed [visible:0]; flag; 0; delay applying color and opacity maps (byte data only)
OPTIONS false; true 
INPUT outofrange [visible:0]; vector list or string list; {"color of min", "color of max"}; how to color out of range data values
OPTIONS color of min; color of max; gray; red; black
OUTPUT mapped; color field; color mapped input field
OUTPUT colormap; field; RGB color map used

MODULE AutoGrid
CATEGORY Realization
DESCRIPTION Regrids a field of scattered positions
INPUT input; field or vector list; (none); field with positions to regrid
INPUT densityfactor; scalar or vector; 1.0 ; density factor for grid 
INPUT nearest; integer or string; 1; number of nearest neighbors to use
OPTIONS 1; 2; 5; infinity
INPUT radius; scalar or string; (appropriate); radius from grid point to consider
INPUT exponent [visible:0]; scalar; 2.0; weighting exponent
OPTIONS 1; 2; 3
INPUT missing [visible:0]; value; (no default); missing value to insert if necessary
OUTPUT output; field; Regridded field


MODULE Band
CATEGORY Realization
DESCRIPTION divides a field into bands based on given division values
INPUT data; scalar field; (none); field to subdivide
INPUT value; scalar or scalar list; (data mean); band divisions
INPUT number; integer; (no default); number of divisions
OPTIONS 2 ; 3 ; 4 ; 5 ; 6 ; 7 ; 8 ; 9 ; 10 ; 15 ; 20
INPUT remap; string; "low"; data values applied to bands
OPTIONS low ; high ; original
OUTPUT band; field or group; Divided input


MODULE CacheScene
DESCRIPTION saves render object and camera in cache for picking
INPUT name; string; (none); name of cached scene
INPUT pickobject; object; (none); object to be picked from
INPUT pickcamera; camera; (none); camera for pick view


MODULE Camera
CATEGORY Rendering
DESCRIPTION produces a camera
INPUT to; vector or object; [0 0 0]; look-to point
INPUT from; vector or object; [0 0 1]; position of camera
INPUT width; scalar or object; 100; width of field of view (for orthographic projection)
INPUT resolution; integer; 640; horizontal resolution of image in pixels
INPUT aspect; scalar; 0.75; height/width
INPUT up; vector; [0 1 0]; up direction
OPTIONS [1 0 0] ; [0 1 0] ; [0 0 1]
INPUT perspective; flag; 0; projection method: (0) orthographic, (1) perspective
OPTIONS false; true 
INPUT angle; scalar; 30.0; view angle in degrees (for perspective projection)
OPTIONS 15.0 ; 30.0 ; 45.0
INPUT background; vector or string; "black"; image background color
OPTIONS black ; white ; red ; green ; blue
OUTPUT camera; camera; resulting camera

MODULE Caption
CATEGORY Annotation
DESCRIPTION displays a caption on the screen
INPUT string; string or string list; (none); the caption to display
INPUT position; vector; [.5 .05]; where to display the caption
INPUT flag [visible:0]; flag; 0; 0=viewport relative coordinates; 1=pixel coordinates
OPTIONS false; true 
INPUT reference [visible:0]; vector; (same as position); reference point on caption
INPUT alignment [visible:0]; scalar; (input dependent); examples: 0=left-justify, 0.5=center, 1=right-justify
OPTIONS 0.0 ; 0.5 ; 1.0
INPUT height [visible:0]; integer; 15; height of the caption in pixels
INPUT font [visible:0]; string; "variable"; caption font
OPTIONS area; cyril_d; fixed; gothiceng_t; gothicger_t; gothicit_t
OPTIONS greek_d; greek_s; italic_d; italic_t; pitman; roman_d
OPTIONS roman_dser; roman_s; roman_tser; roman_ext; script_d
OPTIONS script_s; variable;
OPTIONS swiss; swissbld; swissit; swissbldit; dutch; dutchit; 
OPTIONS swisscnd; domcasual; symbol; monospace;
INPUT direction [visible:0]; vector; [1 0]; direction of baseline
OPTIONS [1 0] ; [0 1]
INPUT up [visible:0]; vector; (perpendicular to baseline); direction of vertical strokes
OUTPUT caption; color field; string object that can be rendered

MODULE Categorize
CATEGORY Transformation
DESCRIPTION categorizes a component of a field
INPUT field; field; (none); the field to categorize
INPUT name; string list; "data"; the components to categorize
OUTPUT categorized; field; field with categorized components and lookups

MODULE CategoryStatistics
CATEGORY Transformation
DESCRIPTION computes statistics of categorical data
INPUT input; field;  (none); field containing categorical and data components
INPUT operation; string; "count"; calculation to perform 
OPTIONS "count"; "mean"; "sd"; "var"; "min"; "max"; "accum"
INPUT category [visible:0]; string; "data"; component with categorical values
INPUT data [visible:0]; string; "data"; data component for statistics
INPUT lookup [visible:0]; integer or string or value list; (catname lookup); optional lookup component or number of categories
OUTPUT statistics; field; field containing statistics on data for each category

MODULE ChangeGroupMember
CATEGORY Structuring
DESCRIPTION alter a member of a group
INPUT data; group; (none); input group object
INPUT operation; string; (none); how to alter the group
OPTIONS insert; replace; delete; insert before; insert after
INPUT id; integer or string; (no default); index or name of existing group member
INPUT newmember; object; (operation dependent); new or replacement group member
INPUT newtag; scalar or string; (no default); new series position or member name
OUTPUT changed; group; group with one member changed

MODULE ChangeGroupType
CATEGORY Structuring
DESCRIPTION Changes group type - series, multigrid, generic
INPUT data; group; (none); input group object
INPUT newtype; string; (none); type for output group
OPTIONS series; multigrid; generic
INPUT idlist; scalar list or string list; (no default); series positions or member names
OUTPUT changed; group; different type of group with same members as input

MODULE ClipBox
CATEGORY Rendering
DESCRIPTION clips an object by a box
INPUT object; object; (none); object to be clipped
INPUT corners; vector list or object; (no clipping); corners specifying clipping box
OUTPUT clipped; object; object marked to be clipped

MODULE ClipPlane
CATEGORY Rendering
DESCRIPTION clips an object by an infinite plane
INPUT object; object; (none); object to be clipped
INPUT point; vector; (center of object); a point on the clipping plane
INPUT normal; vector; [0 0 1]; perpendicular to the clipping plane
OPTIONS [0 0 1] ; [1 0 0]; [0 1 0]
OUTPUT clipped; object; object marked to be clipped

MODULE Collect
CATEGORY Structuring
DESCRIPTION collects objects into a group
FLAGS ERR_CONT
INPUT object; object; (no default); object to be collected
REPEAT 1
OUTPUT group; group; the group of objects

MODULE CollectNamed
CATEGORY Structuring
DESCRIPTION collects objects into a group
INPUT object; object; (no default); object to be collected
INPUT name; string; (no default); name of object
REPEAT 2
OUTPUT group; group; the group of objects

MODULE CollectMultiGrid
CATEGORY Structuring
DESCRIPTION collects objects into a multigrid
INPUT object; object; (no default); object to be collected
INPUT name; string; (no default); name of object
REPEAT 2
OUTPUT multigrid; group; the output multigrid

MODULE CollectSeries
CATEGORY Structuring
DESCRIPTION collects objects into a series
INPUT object; object; (no default); object to be collected or group of objects
INPUT position; scalar or scalar list; (no default); series position of object or list of series positions
INPUT object; object; (no default); object to be collected
INPUT position; scalar; (no default); series position of object
REPEAT 2
OUTPUT series; series; the output series

MODULE Color
CATEGORY Transformation
DESCRIPTION colors a field
INPUT input; field; (none); field to color
INPUT color; field or vector or string; (no color added); RGB color, expected range 0-1
OPTIONS red ; green ; blue; yellow; orange; purple; black; white 
OPTIONS cyan; magenta 
INPUT opacity; field or scalar; (input dependent); opacity, expected range 0-1
INPUT component [visible:0]; string; "colors"; component to color
OPTIONS colors ; front colors ; back colors
INPUT delayed [visible:0]; flag; 0; delay applying colors and opacities (byte data only)
OPTIONS false; true 
OUTPUT colored; color field; color mapped input field

MODULE ColorBar
CATEGORY Annotation
DESCRIPTION creates a color bar to add to a scene
INPUT colormap; field; (none); colormap
INPUT position; vector; [0.95 0.95]; the position of the colorbar in viewport relative coordinates
INPUT shape; vector; [300 25]; length and width of colorbar in pixels
INPUT horizontal; flag; 0; horizontal (0) or vertical (1) orientation
OPTIONS false; true 
INPUT ticks [visible:0]; integer; (input dependent); approximate number of ticks along the bar
INPUT min [visible:0]; scalar or object; (map min); minimum value on bar
INPUT max [visible:0]; scalar or object; (map max); maximum value on bar
INPUT label; string; (no default); label for color bar
INPUT colors [visible:0]; vector list or string list; (appropriate); colors for annotation
INPUT annotation [visible:0]; string list; "all"; annotation objects to color
OPTIONS all; frame; labels; ticks
INPUT labelscale [visible:0]; scalar; 1.0; scale factor for labels
INPUT font [visible:0]; string; (standard); font to use for labels
OPTIONS area; cyril_d; fixed; gothiceng_t; gothicger_t; gothicit_t
OPTIONS greek_d; greek_s; italic_d; italic_t; pitman; roman_d
OPTIONS roman_dser; roman_s; roman_tser; roman_ext; script_d
OPTIONS script_s; variable;
OPTIONS swiss; swissbld; swissit; swissbldit; dutch; dutchit; 
OPTIONS swisscnd; domcasual; symbol; monospace;
INPUT ticklocations [visible:0]; scalar list; (appropriate); tick locations
INPUT ticklabels [visible:0]; string list; (appropriate); tick labels
INPUT usefixedfontsize [visible:0]; flag; 0; use fixed font size for labels
INPUT fixedfontsize [visible:0]; integer; 10; fontsize in pixels, when usefixedfontsize is set to 1
OUTPUT colorbar; color field; the colorbar

MODULE Compute
CATEGORY Transformation
DESCRIPTION computes a pointwise expression over a field
INPUT expression [visible:2]; string; (none); expression to compute
INPUT input; value list or field or string or string list; (no default); input value
REPEAT 1
OUTPUT output; value or value list or field; output values

MODULE Compute2
CATEGORY Transformation
DESCRIPTION computes a pointwise expression over a field using input expressions and names
INPUT expression; string or string list; (none); expression(s) to compute
INPUT name; string; (no default); name of next input, defaults to a, b, ...
INPUT input; value list or field or string list; (no default); input value
REPEAT 2
OUTPUT output; value or value list or field; output values

MODULE Connect
CATEGORY Realization
DESCRIPTION creates triangle connections for a field of scattered positions
INPUT input; field or vector list; (none); field with positions to connect
INPUT method; string; "triangulation"; connection method to use
OPTIONS triangulation
INPUT normal; vector; [0 0 1]; normal of projection plane
OPTIONS [0 0 1]; [0 1 0] ; [1 0 0]
OUTPUT output; field; connected field

MODULE Construct
CATEGORY Realization
DESCRIPTION constructs an arbitrary field with regular connections
INPUT origin; vector list; (input dependent); origin for positions, or list of positions
INPUT deltas; vector list; (input dependent); deltas for positions
INPUT counts; integer or vector; (input dependent); number of positions in each dimension
INPUT data; value list or string list; (no default); data, last index varies fastest
OUTPUT output; field; the output field

MODULE Convert
CATEGORY Transformation
DESCRIPTION converts between hue, saturation, value and red, green, blue color spaces
INPUT data; vector list or field; (none); input colors or color map
INPUT incolorspace; string; "hsv"; color space of input
OPTIONS hsv ; rgb
INPUT outcolorspace; string; "rgb"; color space of output
OPTIONS rgb ; hsv
INPUT addpoints; flag; (input dependent); add positions to ensure valid color transformation
OPTIONS false; true 
OUTPUT output; vector list or field; output colors or color map

MODULE CopyContainer
CATEGORY Structuring
DESCRIPTION Copy only the top container object including attributes
INPUT input; field or group; (none); object to copy
OUTPUT copy; object; copy of container object without any members or components

MODULE Describe
CATEGORY Debugging
DESCRIPTION print description of the input object
FLAGS SIDE_EFFECT
INPUT object; object; (none); object to describe
INPUT options; string; "all"; select which information to print
OPTIONS all; structure; details; render

MODULE DFT
CATEGORY Transformation
DESCRIPTION computes the discrete Fourier transform of a field
INPUT input; field; (none); field to transform
INPUT direction; string; "forward"; direction of the transform: "forward","inverse", or "backward"
INPUT center; flag; 0; center the result of the transform
OPTIONS false; true 
OUTPUT output; field; the transformed data

MODULE Direction
CATEGORY Transformation
DESCRIPTION converts from azimuth, elevation, and distance
INPUT azimuth; scalar; 0; azimuth in degrees
INPUT elevation; scalar; 0; elevation in degrees
INPUT distance; scalar; 1; distance
OUTPUT point; vector; x, y, z position

MODULE Display
CATEGORY Rendering
DESCRIPTION renders a scene and/or sends an image to the display
FLAGS PIN SIDE_EFFECT
INPUT object; object; (none); object to render or image to display
INPUT camera; camera; (no default); camera if rendering is required
INPUT where [visible:0]; window or string; (the users terminal); host and window for display
INPUT throttle [visible:0]; scalar; 0; minimum time in seconds between frames
INPUT name [visible:0]; string; (no name); Option name
INPUT value [visible:0]; object; (no default); Option value
REPEAT 2
OUTPUT where; window; host and window id for display

MODULE DivCurl
CATEGORY Transformation
DESCRIPTION computes divergence and curl
INPUT data; vector field; (none); field of which to compute divergence and curl
INPUT method [visible:0]; string; "manhattan"; method to use
OPTIONS manhattan
OUTPUT div; scalar field; divergence field
OUTPUT curl; vector field; curl field


MODULE Done
CATEGORY Flow Control 
DESCRIPTION Specifies whether a loop should be terminated
FLAGS LOOP
INPUT done; flag; (none); set to 1 to terminate loop 


MODULE Echo
CATEGORY Debugging
DESCRIPTION echoes a message
FLAGS SIDE_EFFECT
INPUT string; value list or string list; (no default); message to print
REPEAT 1

MODULE Enumerate
CATEGORY Realization
DESCRIPTION generates a numeric list
INPUT start; value; (input dependent); starting value in list
INPUT end; value; (input dependent); ending value in list
INPUT count; integer; (input dependent); number of entries in list
INPUT delta; value; (input dependent); numeric stepsize
INPUT method; string; "linear"; how to interpret stepsize
OPTIONS linear
OUTPUT list; value list; the numeric list

MODULE Equalize
CATEGORY Transformation
DESCRIPTION applies histogram equalization
INPUT data; scalar field; (none); data to equalize
INPUT bins; integer; (input dependent); number of equalization bins
INPUT min [visible:0]; scalar or field; (min of data); lower bound for equalization
INPUT max [visible:0]; scalar or field; (max of data); upper bound for equalization
INPUT ihist [visible:0]; field; (histogram of data); input distribution
INPUT ohist [visible:0]; field; (uniform distribution); output distribution
OUTPUT equalized; scalar field; the histogram equalized data


MODULE Executive
DESCRIPTION executes an executive command
FLAGS SIDE_EFFECT
INPUT command; string; (none); command to be executed
INPUT value; object; (no default); command dependent values
REPEAT 1


MODULE Export
CATEGORY Import and Export
DESCRIPTION writes an external data file
FLAGS SIDE_EFFECT
INPUT object; object; (none); object to write
INPUT name; string; (none); file name to write to
INPUT format; string; "dx"; format in which to write the file
OPTIONS dx ; dx text ; dx text follows ; array ; array headers ; vrml

MODULE Extract
CATEGORY Structuring
DESCRIPTION extracts a component from a field
INPUT input; field; (none); the field from which to extract a component
INPUT name; string; "data"; the component to extract
OPTIONS data ; positions ; connections ; colors
OUTPUT output; object; the named component

MODULE FaceNormals
CATEGORY Rendering
DESCRIPTION computes face normals for flat shading
INPUT surface; geometry field; (none); surface on which to compute face normals
OUTPUT normals; field; the surface with face normals

MODULE Filter
CATEGORY Transformation
DESCRIPTION applies a filter to a field
INPUT input; field; (none); data to filter
INPUT filter; value or string; "gaussian"; filter to use
OPTIONS 4-connected ; 8-connected ; 6-connected ; 26-connected
OPTIONS box ; box:1d ; box:3d
OPTIONS compass:e; compass:n; compass:ne; compass:nw
OPTIONS compass:s; compass:se; compass:sw; compass:w
OPTIONS gaussian; gaussian:2d;gaussian:3x3;gaussian:5x5;gaussian:7x7
OPTIONS isotropic;kirsch
OPTIONS laplacian; laplacian:1d; laplacian:2d; laplacian:3d
OPTIONS line:e-w; line:n-s; line:ne-sw; line:nw-se
OPTIONS prewitt; roberts; sobel
INPUT component [visible:0]; string; "data"; component on which to operate
OPTIONS data ; colors
INPUT mask [visible:0]; value or string; "box"; rank-value filter mask
OUTPUT output; field; filtered data










MODULE First
FLAGS LOOP
CATEGORY Flow Control 
DESCRIPTION  Indicates whether this is the first time through the loop
OUTPUT first; flag;  Is this the first time through loop?

MODULE ForEachMember
FLAGS LOOP
CATEGORY Flow Control 
DESCRIPTION  Iterate over members of a group/array
INPUT object; object; (none); object to iterate over
OUTPUT member; object; selected member 
OUTPUT index; integer; 0-based index number of member
OUTPUT last; flag; Is this the last time through the loop?

MODULE ForEachN
FLAGS LOOP
CATEGORY Flow Control 
DESCRIPTION  Iterates over a specified set of integers 
INPUT start; integer; (none);  start value 
OPTIONS 0 ; 1
INPUT end; integer; (none);  end value 
INPUT delta; integer; 1;  delta value 
OPTIONS  -1 ; 1 ; 2 
OUTPUT current; integer; current value 
OUTPUT last; flag; Is this the last time through the loop?


MODULE Format
CATEGORY Annotation
DESCRIPTION formats a string
INPUT template; string; (none); format control string
INPUT value; value list or string; (no default); value to format
REPEAT 1
OUTPUT string; string; formatted string object

MODULE FFT
CATEGORY Transformation
DESCRIPTION computes the fast Fourier transform of a field
INPUT input; field; (none); field to transform
INPUT direction; string; "forward"; direction of the transform:"forward", "inverse" or "backward"
INPUT center; flag; 0; center the result of the transform
OPTIONS false; true 
OUTPUT output; field; the transformed data


MODULE Get
DESCRIPTION retrieve an object saved by Set
FLAGS ASYNCLOCAL CHANGES_STATE
INPUT initial; object; (no default); initial object, sent to output if nothing has been Set
INPUT reset; flag;  0; If set, initial object (rather than cached object) is passed to output
INPUT key [visible:2, rerun_key:1]; string;  (none); Optional cache key string
OUTPUT object; object; retrieved object
OUTPUT link; string; link to Set, must be connected to second input of Set

MODULE GetGlobal
CATEGORY Flow Control 
DESCRIPTION retrieve an object saved by SetGlobal
FLAGS ASYNCLOCAL CHANGES_STATE
INPUT initial; object; (no default); initial object, sent to output if nothing has been Set
INPUT reset; flag;  0; If set, initial object (rather than cached object) is passed to output
INPUT key [visible:2, rerun_key:1]; string;  (none); Optional cache key string
OUTPUT object; object; retrieved object
OUTPUT link; string; link to SetGlobal, must be connected to second input of SetGlobal

MODULE GetLocal
CATEGORY Flow Control 
DESCRIPTION retrieve an object saved by SetLocal
FLAGS ASYNCLOCAL
INPUT initial; object; (no default); initial object, sent to output if nothing has been Set
INPUT reset; flag;  0; If set, initial object (rather than cached object) is passed to output
INPUT key [visible:2]; string;  (none); Optional cache key string
OUTPUT object; object; retrieved object
OUTPUT link; string; link to SetLocal, must be connected to second input of SetLocal

MODULE GetScene
FLAGS SIDE_EFFECT
DESCRIPTION retrieve object and camera saved by an Image window
INPUT imagetag [visible:2]; string; (none); tag of image
OUTPUT object; object; cached object
OUTPUT camera; camera; cached camera


MODULE Glyph
CATEGORY Annotation
DESCRIPTION assigns an appropriate glyph to each point; scale is in absolute units
INPUT data; data field; (none); set of points to which glyphs will be assigned
INPUT type; scalar or string or field or group; (input dependent); glyph type
OPTIONS speedy; spiffy; standard; 0.0; 1.0; 0.5; text
OPTIONS colored text; cube; square
OPTIONS arrow2D; circle; diamond; needle
OPTIONS needle2D; rocket; rocket2D; sphere
INPUT shape; scalar; 1.0; factor to describe the shape of the glyph
OPTIONS .25; .50; .75; 1.0; 1.5; 2.0
INPUT scale; scalar; (input dependent); scale factor for size of glyphs
OPTIONS .25; .50; .75; 1.0; 1.5; 2.0
INPUT ratio; scalar; (0.05 or 0); ratio in size (scalars or vectors) between smallest and largest glyphs
INPUT min [visible:0]; scalar or field; (min of data or 0); data value which gets the minimum size glyph
INPUT max [visible:0]; scalar or field; (max of data); data value which gets the maximum size glyph
OUTPUT glyphs; color field; set of glyphs

MODULE Gradient
CATEGORY Transformation
DESCRIPTION computes the gradient of a scalar field
INPUT data; scalar field; (none); field of which to compute gradient
INPUT method [visible:0]; string; "manhattan"; method to use
OUTPUT gradient; vector field; gradient field

MODULE Grid
CATEGORY Realization
DESCRIPTION produces a set of points on a grid
INPUT point; vector; (none); point around which to build the grid
INPUT structure; string; "brick"; shape of the grid
OPTIONS line; rectangle; crosshair; ellipse; brick
INPUT shape; vector list; (structure dependent); size and shape of structure
INPUT density; integer list; ({3, 3, ... }); number of points to put on each element of the grid
OUTPUT grid; geometry field; output grid

MODULE Histogram
CATEGORY Transformation
DESCRIPTION computes a histogram
INPUT data; scalar list or vector list or field or series; (none); field to histogram
INPUT bins; integer or vector; (256 for bytes, 100 otherwise); number of bins in histogram
INPUT min [visible:0]; scalar or vector or field; (min of data); minimum value to histogram
INPUT max [visible:0]; scalar or vector or field; (max of data); maximum value to histogram
INPUT out [visible:0]; flag or vector; 0; if 1, then include outliers
OPTIONS false; true 
OUTPUT histogram; field or series; the histogram
OUTPUT median; scalar or scalar list; median of the input field

MODULE ImageMessage
DESCRIPTION returns info from exec to ui for data-driven Image
FLAGS SIDE_EFFECT
INPUT id; object; (none);
INPUT bkgndColor; vector or string; (none);
INPUT throttle; scalar; (none);
INPUT recordEnable; flag; (none);
INPUT recordFile; string; (none);
INPUT recordFormat; string; (none);
INPUT recordResolution; integer; (none);
INPUT recordAspect; scalar; (none);
INPUT axesEnabled; flag; (none);
INPUT axesLabels; string list;  (none);
INPUT axesTicks; integer or integer list;  (none);
INPUT axesCorners; vector list or object;  (none);
INPUT axesFrame; flag;  (none);
INPUT axesAdjust; flag;  (none);
INPUT axesCursor; vector; (none);
INPUT axesGrid; flag; (none);
INPUT axesColors; vector list or string list; (none);
INPUT axesAnnotate; string list; (none);
INPUT axesLabelScale; scalar; (none);
INPUT axesFont; string; (none);
INPUT axesXTickLocs; scalar list; (none);
INPUT axesYTickLocs; scalar list; (none);
INPUT axesZTickLocs; scalar list; (none);
INPUT axesXTickLabels; string list; (none);
INPUT axesYTickLabels; string list; (none);
INPUT axesZTickLabels; string list; (none);
INPUT interactionMode; string; (none);
INPUT title; string; (none);
INPUT renderMode; integer; (none);
INPUT buttonUpApprox; string; (none);
INPUT buttonDownApprox; string; (none);
INPUT buttonUpDensity; integer; (none);
INPUT buttonDownDensity; integer; (none);

MODULE Import
CATEGORY Import and Export
DESCRIPTION reads an external data file
FLAGS PIN
INPUT name; string; (none); file name containing data to be read, or !command
INPUT variable; string or string list; (format dependent); variable to be read
INPUT format; string; (file extension or content); "dx text", "cdf", "general"
OPTIONS dx; general; netCDF ; CDF ; cm ; hdf
INPUT start [visible:0]; integer; (first frame); starting data frame
INPUT end [visible:0]; integer; (last frame); ending data frame
INPUT delta [visible:0]; integer; 1; increment between frames
OUTPUT data; object; object containing requested variables

MODULE ImportSpreadsheet
CATEGORY Import and Export
DESCRIPTION Imports spreadsheet data
INPUT filename; string;(none) ; filename to import
INPUT delimiter; string; " "; delimiter
OPTIONS "\t"
INPUT columnname [visible:0]; string list; (all); list of columns to import
INPUT format [visible:0]; string; "1-d"; import as 1-d or 2-d field
OPTIONS "1-d"; "2-d"
INPUT categorize [visible:0]; string list; (no columns); list of columns to categorize
OPTIONS "allstring"
INPUT start [visible:0]; integer; (first record); starting record
INPUT end [visible:0]; integer; (last record); ending record
INPUT delta [visible:0]; integer; 1; increment between records
INPUT headerlines [visible:0]; integer; 0; lines to skip before data
INPUT labelline [visible:0]; integer; (no lines); line that labels are on
OUTPUT data; field; requested data
OUTPUT labellist; string list; list of column labels

MODULE Include
CATEGORY Import and Export
DESCRIPTION includes (or excludes) points based on data
INPUT data; data field; (none); field from which to select points
INPUT min; scalar or vector; (min of data); minimum value to include
INPUT max; scalar or vector; (max of data); maximum value to include
INPUT exclude; flag; 0; 0: include selected range, 1: exclude selected range
OPTIONS false; true 
INPUT cull; flag; 1; if 0, leave culled points in field, marked invalid
OPTIONS true; false 
INPUT pointwise; flag; 0; if 1, ignore connections when selecting points
OPTIONS false; true
OUTPUT output; field; field with selected points

MODULE Inquire
CATEGORY Structuring
DESCRIPTION return information about the input object
INPUT input; object; (none); the input object being queried
INPUT inquiry; string; "is null"; what information is requested
OPTIONS is null; is empty; items; grid counts
INPUT value; string; (no default); additional qualifiers about this inquiry
OUTPUT output; integer or object; 1 or 0 for yes/no inquiries, or the value

MODULE Isolate
CATEGORY Realization
DESCRIPTION isolates and shrinks connection elements
INPUT field; field; (none); the field to be isolated
INPUT scale; scalar; .5; factor by which to shrink the cells
OUTPUT output; field; field of isolated connections

MODULE Isosurface
CATEGORY Realization
DESCRIPTION computes isosurfaces or contour lines
INPUT data; scalar field; (none); field of which to construct isosurface(s)
INPUT value; scalar or scalar list; (data mean); isosurface value(s)
INPUT number; integer; (no default); number of isosurfaces or contours
INPUT gradient [visible:0]; vector field; (no gradient); gradient field
INPUT flag [visible:0]; flag; 1; whether to compute normals
OPTIONS true; false
INPUT direction [visible:0]; integer; -1; how to orient normals
OUTPUT surface; field or group; isosurface

MODULE KeyIn
DESCRIPTION waits for a line from the terminal
FLAGS SIDE_EFFECT
INPUT prompt; string; "Type <ENTER> to continue"; string printed

MODULE Legend
CATEGORY Annotation
DESCRIPTION creates a legend for string data
INPUT stringlist; string list; (none); list of strings
INPUT colorlist; field or vector list or string list; (none); color map or list of colors
INPUT position; vector; [0.95 0.95]; the position of the legend in viewport relative coordinates
INPUT shape; vector; [300 25]; length and width of legend in pixels
INPUT horizontal; flag; 0; horizontal (0) or vertical (1) orientation
OPTIONS false; true
INPUT label; string; (no default); label for the legend 
INPUT colors [visible:0]; vector list or string list; (appropriate); colors for annotation
INPUT annotation [visible:0]; string list; "all"; annotation objects to color 
OPTIONS all; frame; labels; ticks
INPUT labelscale [visible:0]; scalar; 1.0; scale factor for labels
INPUT font [visible:0]; string; (standard); font to use for labels
OPTIONS area; cyril_d; fixed; gothiceng_t; gothicger_t; gothicit_t
OPTIONS greek_d; greek_s; italic_d; italic_t; pitman; roman_d
OPTIONS roman_dser; roman_s; roman_tser; roman_ext; script_d
OPTIONS script_s; variable;
OPTIONS swiss; swissbld; swissit; swissbldit; dutch; dutchit; 
OPTIONS swisscnd; domcasual; symbol; monospace;
OUTPUT legend; color field; the legend 


MODULE Light
CATEGORY Rendering
DESCRIPTION produces a distant point light
INPUT where; vector or camera; [0 0 1]; position or direction of light
INPUT color; vector or string; [1 1 1]; color and intensity of light
INPUT camera; flag; 0; 0=fixed direction, 1=direction relative to camera
OPTIONS false; true
OUTPUT light; light; a distant light

MODULE List
CATEGORY Structuring
DESCRIPTION concatinates items into a single list
INPUT object; value or value list or string list; (no default); list item to concatenate
REPEAT 1
OUTPUT list; value list or string list; the object list

MODULE Lookup
CATEGORY Transformation
DESCRIPTION replaces values using a lookup table
INPUT input; field or string list or value or value list; (none); object to lookup
INPUT table; field or string or value list; (dataname lookup); lookup table
INPUT data [visible:0]; string; "data"; component of input to lookup
INPUT lookup [visible:0]; string; "positions"; component of table in which to look
INPUT value [visible:0]; string; "data"; component of table containing lookup results
INPUT destination [visible:0]; string; "lookedup"; component of input in which to put result
INPUT ignore [visible:0]; string list; (no default); properties to ignore in string lookup
OPTIONS case; space; lspace; rspace; lrspace; punctuation
OUTPUT lookedup; field or value or value list; the lookedup values

MODULE Map
CATEGORY Transformation
DESCRIPTION applies a function defined by a map to a field
INPUT input; field or value or value list; (none); field to map
INPUT map; scalar or vector or field; (identity); map to use
INPUT source [visible:0]; string; "positions"; component to use as index into map
OPTIONS positions; data; colors
INPUT destination [visible:0]; string; "data"; component in which to put result
OPTIONS data; positions; colors
OUTPUT output; field or value or value list; input field mapped according to map

MODULE MapToPlane
CATEGORY Realization
DESCRIPTION maps a field onto a plane
INPUT data; data field; (none); data to be mapped
INPUT point; vector; (center of object); a point on the map plane
INPUT normal; vector; [0 0 1]; normal to the map plane
OPTIONS [0 0 1]; [0 1 0]; [1 0 0]
OUTPUT plane; data field; mapped plane

MODULE Mark
CATEGORY Structuring
DESCRIPTION marks a component
INPUT input; field; (none); the field in which to mark a component
INPUT name; string; (none); the component to mark
OPTIONS positions; connections; colors
OUTPUT output; field; the field with the named component marked

MODULE Measure
CATEGORY Transformation
DESCRIPTION performs measurement on a data object
INPUT input; data field; (none); data to be measured
INPUT what; string; (input dependent); measurement to perform
OPTIONS length; area; volume; element
OUTPUT output; value or field; measurement result

# 894 "userTmp.c"


MODULE Message
CATEGORY Debugging
DESCRIPTION prints a user-generated message, warning, or error
FLAGS SIDE_EFFECT
INPUT message; string; (no default); message to print
INPUT type; string; "message"; type of information: error, warning, or message
OPTIONS error; warning; message
INPUT popup; flag; 0; if set, put the message in a separate popup window
OPTIONS false; true

MODULE Morph
CATEGORY Transformation
DESCRIPTION applies a binary morphological operator
INPUT input; field; (none); input data
INPUT operation; string; "erode"; the operation to apply
OPTIONS erode; dilate; open; close
INPUT mask; value or string; "box"; the mask element
OUTPUT output; field; morphologically transformed input

MODULE Normals
CATEGORY Rendering
DESCRIPTION computes point normals for shading
INPUT surface; geometry field; (none); surface on which to compute normals
INPUT method; string; "positions"; component on which to base normals
OPTIONS positions; connections; face
OUTPUT normals; field; the surface with normals

MODULE Options
CATEGORY Structuring
DESCRIPTION associates attributes with an object
INPUT input; object; (none); object of which to set attributes
INPUT attribute; string; (no default); attribute to set
OPTIONS label; scatter; mark; mark every; mark scale; pickable
OPTIONS ambient; diffuse; specular; shininess; rendering mode
OPTIONS rendering approximation; render every
INPUT value; value or string or object; (no default); value of the attribute
REPEAT 2
OUTPUT output; object; the object with attributes set

MODULE Overlay
CATEGORY Rendering
DESCRIPTION overlays one image on another
INPUT overlay; image; (none); overlay image
INPUT base; image; (none); base image
INPUT blend; scalar or vector or string or field; .5; 0 for base image only; 1 for overlay image only, or chromakey color or mask field, or chromakey color or mask field
OUTPUT combined; image; combined image

MODULE Parse
CATEGORY Annotation
DESCRIPTION separates a string up into strings and/or values
INPUT input; string; (none); string to separate
INPUT format; string; "%s"; format control string
OUTPUT value; value or string; value extracted from string
REPEAT 1

MODULE Partition
CATEGORY Import and Export
DESCRIPTION partitions a data set
INPUT input; field or group; (none); field to partition
INPUT n; integer; (machine dependent); maximum number of subparts
INPUT size [visible:0]; integer; (one primitive); threshold for partitioning
OUTPUT partitioned; field or group; set of partitioned fields

MODULE Pick
CATEGORY Special
DESCRIPTION
INPUT pickname [visible:2]; string; (none); name of associated cached picks
INPUT imagename [visible:2]; string; (none); name of associated cached scene
INPUT locations [visible:0]; vector list; (no default); 2-D screen coordinate pick positions
INPUT reexecute [visible:2]; flag; (none); cause re-execution whenever pick list is reset
OPTIONS false; true
INPUT first; flag; 1; first intersection only instead of all intersections
OPTIONS true; false
INPUT persistent [visible:0]; flag; 1; if no new picks, reuse previous picks
OPTIONS true; false
INPUT interpolate [visible:0]; flag; 0; include data from pick object in picked
OPTIONS false; true
INPUT object [visible:0]; object; (no default); object to pick in
INPUT camera [visible:0]; camera; (no default); camera used to render scene
OUTPUT picked; field; pick information

# 990 "userTmp.c"


MODULE Pie
CATEGORY Realization
DESCRIPTION Creates 2D or 3D Piechart Wedges
INPUT percents; scalar list or field ;  (none); wedge data
INPUT percentflag; string ;  "values"; type of percents
OPTIONS "values";"percents";"fractions"
INPUT radius; scalar list or field; 1; radius/radii of piechart
INPUT radiusscale[visible:0]; scalar; 1; radius for "radiusmax" value
INPUT radiusmin[visible:0]; scalar; (minimum radius value); radius value which gets the minimum radius size
INPUT radiusmax[visible:0]; scalar; (maximum radius value); radius value which gets the maximum radius size
INPUT radiusratio[visible:0]; scalar; (.10); ratio in radius size between radiusmin and radiusmax
INPUT height; scalar list or field; 0.0; height(s) of piechart (0 for 2D)
INPUT heightscale[visible:0]; scalar; 1; height for "heightmax" value
INPUT heightmin[visible:0]; scalar; (minimum height value); height value which gets the minimum height size
INPUT heightmax[visible:0]; scalar; (maximum height value); height value which gets the maximum height size
INPUT heightratio[visible:0]; scalar; (.10); ratio in height size between heightmin and heightmax
INPUT quality; scalar;  0.25; 0.0 < quality < 1
INPUT colors[visible:0]; vector list or string list; (no default); colors for piechart
INPUT labels; value list or string list or field;  (percentages); labels for each wedge
INPUT labelformat[visible:0]; string;  (appropriate); format for labels
INPUT showpercents[visible:0]; flag;  0; display percentage with labels
OUTPUT wedges; series; the piechart
OUTPUT edges; series; the piechart edges
OUTPUT labels; field; the piechart labels
OUTPUT percents; string list; the wedge percents
OUTPUT colors; vector list; the wedge colors

MODULE Plot
CATEGORY Annotation
DESCRIPTION creates a plot
INPUT input; field or group; (none); data to plot
INPUT labels; string list; {"x", "y"}; axis labels
INPUT ticks; integer list; (input dependent); approximate number of ticks
INPUT corners; vector list or object; ([xmin, ymin][xmax, ymax]); plot limits
INPUT adjust [visible:0]; flag; (input dependent); whether to adjust end points
OPTIONS false; true
INPUT frame [visible:0]; integer; 0; framing style for plot
OPTIONS 0; 1; 2
INPUT type [visible:0]; string list; {"lin", "lin"}; plot type
OPTIONS lin; log; {"lin", "log"}; {"log", "lin"}
INPUT grid [visible:0]; integer; 0; grid style for plot
OPTIONS 0; 1; 2; 3
INPUT aspect; scalar or string; 1.0; y to x aspect ratio of resulting plot
OPTIONS 1.0; .75;  1.2; "inherent"
INPUT colors [visible:0]; vector list or string list; (appropriate); colors for annotation
INPUT annotation [visible:0]; string list; "all"; annotation objects to color
OPTIONS all; axes; background; grid; labels; ticks
INPUT labelscale [visible:0]; scalar; 1.0; scale factor for labels
INPUT font [visible:0]; string; (standard); font to use for labels
OPTIONS area; cyril_d; fixed; gothiceng_t; gothicger_t; gothicit_t
OPTIONS greek_d; greek_s; italic_d; italic_t; pitman; roman_d
OPTIONS roman_dser; roman_s; roman_tser; roman_ext; script_d
OPTIONS script_s; variable;
OPTIONS swiss; swissbld; swissit; swissbldit; dutch; dutchit; 
OPTIONS swisscnd; domcasual; symbol; monospace;
INPUT input2 [visible:0]; field or group; (no default); second set of data to plot
INPUT label2 [visible:0]; string; {"y2"}; axis label for second y axis
INPUT ticks2 [visible:0]; integer; (input dependent); approximate number of ticks on second y axis
INPUT corners2 [visible:0]; vector or object; ([ymin, ymax]); plot limits on second y axis
INPUT type2 [visible:0]; string; "lin"; plot type for second y axis
OPTIONS lin; log
INPUT xticklocations [visible:0]; scalar list; (appropriate); x tick locations
INPUT y1ticklocations [visible:0]; scalar list; (appropriate); y1 tick locations
INPUT y2ticklocations [visible:0]; scalar list; (appropriate); y2 tick locations
INPUT xticklabels [visible:0]; string list; (xticklocations); x tick labels
INPUT y1ticklabels [visible:0]; string list; (y1ticklocations); y1 tick labels
INPUT y2ticklabels [visible:0]; string list; (y2ticklocations); y2 tick labels
INPUT usefixedfontsize [visible:0]; flag; 0; use fixed font size for labels
INPUT fixedfontsize [visible:0]; scalar; .1; fontsize as fraction of x axis, when usefixedfontsize is set to 1
OUTPUT plot; field; the plot

MODULE Post
CATEGORY Transformation
DESCRIPTION change data dependency between positions and connections
INPUT input; field; (none); field to have its dependency changed
INPUT dependency; string; "positions"; desired output dependency
OPTIONS positions; connections
OUTPUT output; field; field with data dependent on given component

MODULE Print
CATEGORY Debugging
DESCRIPTION prints an object
FLAGS SIDE_EFFECT
INPUT object; object; (none); object to print
INPUT options; string; "o"; printing options
OPTIONS o; rd; rD
INPUT component; string or string list; (all components); component or components to print
OPTIONS positions; connections; data; colors

MODULE QuantizeImage
CATEGORY Transformation
DESCRIPTION Reduces an RGB image to a ubyte image with colormap
INPUT images; image or image series; (none); image(s) to quantize
INPUT nColors; integer; 256; max. number of colors to use
OUTPUT images; image or image series; resulting quantized images

MODULE ReadImage
CATEGORY Import and Export
DESCRIPTION reads an image from a file
INPUT name; string; "image"; file name
INPUT format; string; ("rgb" or input dependent); format of file
OPTIONS rgb; r+g+b; tiff; gif; miff
INPUT start [visible:0]; integer; (first frame); starting movie frame
INPUT end [visible:0]; integer; (last frame); ending movie frame
INPUT delta [visible:0]; integer; 1; delta of images to read
INPUT width [visible:0]; integer; (input dependent); width of image
INPUT height [visible:0]; integer; (input dependent); height of image
INPUT delayed [visible:0]; flag; (environment-dependent); use delayed colors if present in image file
OPTIONS false ; true
INPUT colortype [visible:0]; string; (environment-dependent); data type for colors 
OPTIONS "float" ; "byte" 
OUTPUT image; image or image series; resulting image

MODULE ReadImageWindow
CATEGORY Windows
FLAGS PIN
DESCRIPTION  Retrieve the contents of a display window
INPUT where; window; (no default); window identifier
OUTPUT image; field; image found in the window

MODULE Reduce
CATEGORY Import and Export
DESCRIPTION reduces the resolution of a data set
INPUT input; field; (none); field to reduce
INPUT factor; scalar list or vector list; 2; reduction factor(s)
OUTPUT reduced; field or group; set of reduced-resolution data

MODULE Refine
CATEGORY Import and Export
DESCRIPTION resamples a grid at a finer resolution, or changes the element type of a grid
INPUT input; field; (none); field to refine
INPUT level; integer or string; 1; level of refinement
OPTIONS 1; 2; 3; 4; triangles; quads
OUTPUT refined; field; refined input

MODULE Regrid
CATEGORY Realization
DESCRIPTION Regrids a field of scattered positions
INPUT input; field or vector list; (none); field with positions to regrid
INPUT grid; field; (none); grid to use as template
INPUT nearest; integer or string; 1; number of nearest neighbors to use
OPTIONS 1; 2; 5; infinity
INPUT radius; scalar or string; "infinity"; radius from grid point to consider
INPUT exponent; scalar; 1.0; weighting exponent
OPTIONS 1; 2; 3
INPUT missing; value; (no default); missing value to insert if necessary
OUTPUT output; field; Regridded field










MODULE Remove
CATEGORY Structuring
DESCRIPTION remove components from a field
INPUT input; field; (none); the field from which to remove the component(s)
INPUT name; string or string list; (none); the component(s) to remove
OPTIONS positions; connections; data; colors; normals; invalid positions
OPTIONS invalid connections
OUTPUT output; field; the field without the named component(s)

MODULE Rename
CATEGORY Structuring
DESCRIPTION renames a component in a field
INPUT input; field; (none); the field in which to rename something
INPUT oldname; string; (none); the old component name
OPTIONS positions; connections; data; colors
INPUT newname; string; "data"; the new component name
OPTIONS positions; connections; data; colors
OUTPUT output; field; field with component renamed

MODULE Render
CATEGORY Rendering
DESCRIPTION renders an object
INPUT object; object; (none); object to be rendered
INPUT camera; camera; (none); camera for rendering
INPUT format [visible:0]; string; (standard); format of resulting image
OUTPUT image; image; resulting image

MODULE Reorient
CATEGORY Rendering
DESCRIPTION change the orientation of an image 
INPUT image; field or group; (none); image(s) to be reoriented
INPUT how; integer; 0; how to change the orientation by rotation or inversion
OPTIONS 0;1;2;3;4;5;6;7
OUTPUT image; image; resulting rotated or inverted image

MODULE Replace
CATEGORY Structuring
DESCRIPTION replaces a component in one field with a component from another field
INPUT srcfield; field or value list; (none); field from which to get component
INPUT dstfield; field; (none); the field in which to replace
INPUT srcname; string; "data"; which component from srcfield
OPTIONS data ; positions; connections; colors
INPUT dstname; string; "data"; the new component name
OPTIONS data ; positions; connections; colors
OUTPUT out; field; dstfield with component from srcfield

MODULE Ribbon
CATEGORY Annotation
DESCRIPTION produces a ribbon that follows a path
INPUT line; field; (none); line to be drawn as a ribbon
INPUT width; scalar; (input dependent); the width of the ribbon
OUTPUT ribbon; field; the line turned into a ribbon

MODULE Rotate
CATEGORY Rendering
DESCRIPTION rotates an object
INPUT input; object; (none); object to rotate
INPUT axis; integer or string; "y"; axis about which to rotate
OPTIONS y ; x ; z
INPUT rotation; scalar; 0; amount of rotation in degrees
OPTIONS 30 ; 45 ; 60 ; 90; 135; 180
INPUT axis; integer or string; (no default); axis about which to rotate
OPTIONS y ; x ; z
INPUT rotation; scalar; (no default); amount of rotation in degrees
OPTIONS 30 ; 45 ; 60 ; 90; 135; 180
REPEAT 2
OUTPUT output; object; object marked to be rotated


MODULE Route
CATEGORY Flow Control 
DESCRIPTION routes an object through selector-specified output path(s)
INPUT selector; integer or integer list; 0; path(s) through which to route input object
INPUT input; value list or string list or object; (no default); object to route
OUTPUT output; object; a possible path through which the input object may be routed






REPEAT 1



MODULE RubberSheet
CATEGORY Realization
DESCRIPTION deforms a surface based on data values
INPUT data; scalar field; (none); the field to deform
INPUT scale; scalar; (input dependent); displacement scaling
INPUT min [visible:0]; scalar or field; 0.0; offset to apply to data values
INPUT max [visible:0]; scalar or field; (max of data); data value to use to set maximum displacement
OUTPUT graph; scalar field; the deformed field

MODULE Sample
CATEGORY Realization
DESCRIPTION samples a field at points on a surface or within a volume
INPUT manifold; field; (none); the surface or volume to sample
INPUT density; integer; 100; approximate number of samples
OUTPUT samples; field; a set of samples of the field

MODULE Scale
CATEGORY Rendering
DESCRIPTION scales an object
INPUT input; object; (none); object to scale
INPUT scaling; scalar or vector; [1 1 1]; scaling factor along x, y and z axes
OUTPUT output; object; object marked to be scaled

MODULE  ScaleScreen
CATEGORY Rendering 
DESCRIPTION scales screen objects by given amount
INPUT object; object; (none) ; object to scale
INPUT scalefactor; scalar; 1; scale factor for screen objects
INPUT finalres; integer; (no default); final (x) resolution of desired image
INPUT currentcamera; camera; (no default); current camera used to view object
OUTPUT output; object; object with screen objects scaled as specified
OUTPUT newcamera; camera; current camera updated by specified scale factor

# 1278 "userTmp.c"


MODULE Select
CATEGORY Structuring
DESCRIPTION selects a member of a group or list
INPUT input; group or series or value list or string list; (none); the object from which to select
INPUT which; integer or integer list or string or string list; 0; which member(s) to select
INPUT except [visible:0]; flag; 0; copy all listed members (0) or all but listed members (1)
OPTIONS false; true
OUTPUT object; object; the selected member(s)

# 1298 "userTmp.c"



MODULE Set
DESCRIPTION save an object to be retrieved by Get
INPUT object; object; (no default); object to be saved
INPUT link; string; (none); link to Get, must be connected to second output of Get
INPUT key [visible:2]; string;  (none); Optional cache key string

MODULE SetGlobal
CATEGORY Flow Control 
DESCRIPTION save an object to be retrieved by GetGlobal
INPUT object; object; (no default); object to be saved
INPUT link; string; (none); link to GetGlobal, must be connected to second output of GetGlobal
INPUT key [visible:2]; string;  (none); Optional cache key string

MODULE SetLocal
CATEGORY Flow Control 
DESCRIPTION save an object to be retrieved by GetLocal
INPUT object; object; (no default); object to be saved
INPUT link; string; (none); link to GetLocal, must be connected to second output of GetLocal
INPUT key [visible:2]; string;  (none); Optional cache key string


MODULE Shade
CATEGORY Rendering
DESCRIPTION specifies object shading parameters
INPUT input; field; (none); object to shade
INPUT shade; flag; 1; whether to shade this object
OPTIONS true; false
INPUT how; string; (no default); "smooth" or "faceted"
OPTIONS smooth ; faceted
INPUT specular [visible:0]; scalar; (no default); specular coefficient (standard = 0.5)
INPUT shininess [visible:0]; integer; (no default); shininess exponent (standard = 10)
INPUT diffuse [visible:0]; scalar; (no default); diffuse coefficient (standard = 0.7)
INPUT ambient [visible:0]; scalar; (no default); ambient coefficient (standard = 1.0)
INPUT reversefront [visible:0]; flag; 0; reverse front and back sides
OUTPUT output; field; shaded object

MODULE ShowBoundary
CATEGORY Realization
DESCRIPTION shows the boundary of a field
INPUT input; field; (none); field of which to show boundary
INPUT validity; flag; 0; 0=create boundary of all data, 1=create boundary of valid data only
OPTIONS false; true
OUTPUT output; color field; renderable boundary of input field

MODULE ShowBox
CATEGORY Realization
DESCRIPTION draws a bounding box
INPUT input; field; (none); the field of which to show the bounding box
OUTPUT box; color field; renderable bounding box of input field
OUTPUT center; vector; center of bounding box

MODULE ShowConnections
CATEGORY Realization
DESCRIPTION shows the outline of connective elements
INPUT input; field; (none); field of which to show connections
OUTPUT output; color field; renderable connections of input field

MODULE ShowPositions
CATEGORY Realization
DESCRIPTION shows the positions of a field
INPUT input; field; (none); field of which to show positions
INPUT every [visible:0]; scalar; 1.0; reduction factor for how many positions are shown
OUTPUT output; color field; renderable positions of input field

# 1375 "userTmp.c"


# 1385 "userTmp.c"


MODULE SimplifySurface
CATEGORY Transformation
DESCRIPTION approximates a triangulated surface and resamples data
INPUT original_surface; field;  (none); triangulated surface
INPUT max_error; scalar;  (1% of bbox diagonal); maximum positional error
INPUT max_data_error; scalar; (10% of data bbox diagonal); maximum data error
INPUT volume [visible:0]; flag; 1; preserve volume
OPTIONS true; false
INPUT boundary [visible:0]; flag; 0; simplify surface boundaries
OPTIONS false; true
INPUT length [visible:0]; flag; 1; preserve the length of boundaries
OPTIONS true; false
INPUT data [visible:0]; flag; 1; use position-dependent data to constrain simplification
OPTIONS true; false
INPUT stats [visible:0]; flag; 0; provide simple statistics
OPTIONS false; true
OUTPUT simplified; field;  simplified triangulated surface

MODULE Slab
CATEGORY Import and Export
DESCRIPTION takes a slab of multidimensional data
INPUT input; field; (none); object to slab
INPUT dimension; integer or string; 0; dimension along which to take slab
OPTIONS x ; y ; z
INPUT position; integer or integer list; (all); starting position(s)
INPUT thickness; integer; (0 or 1); thickness of slab (in number of elements)
OUTPUT output; field or field series; slabbed data

MODULE Slice
CATEGORY Import and Export
DESCRIPTION slices multi-dimensional data
INPUT input; field; (none); object to slice
INPUT dimension; integer or string; 0; dimension to eliminate
OPTIONS x ; y ; z
INPUT position; integer list; (all); which slices to take
OUTPUT output; field or field series; sliced data

MODULE Sort
CATEGORY Transformation
DESCRIPTION Sort an object
INPUT field; scalar list or field; (none); object to sort
INPUT descending; flag; 0; sort in descending order
OPTIONS false; true
OUTPUT result; scalar list or field; sorted object

MODULE Stack
CATEGORY Import and Export
DESCRIPTION stacks multi-dimensional data
INPUT input; field or field series; (none); data to stack
INPUT dimension; integer or string; 0; dimension in which to stack
OPTIONS x ; y ; z
OUTPUT output; field; stacked data

MODULE Statistics
CATEGORY Transformation
DESCRIPTION computes statistics over a field
INPUT data; data field or value list; (none); field over which to compute statistics
OUTPUT mean; scalar; the mean
OUTPUT sd; scalar; the standard deviation
OUTPUT var; scalar; the variance
OUTPUT min; scalar; the minimum value
OUTPUT max; scalar; the maximum value

MODULE Streakline
CATEGORY Realization
DESCRIPTION computes streaklines
INPUT name [visible:0]; string or object ; (no default); name of streakline
INPUT data; vector field or vector field series; (none); vector series time step or vector series
INPUT start; vector list or geometry field; (center of first series member); starting point or points
INPUT time; scalar list; (series start time); starting time or times
INPUT head; integer; (final series frame number); series time step at which to end streaks
INPUT frame; integer; (current frame); current frame
INPUT curl; vector field or vector field series; (no curl); curl to use for twist
INPUT flag; flag; (input dependent); whether to use curl to generate twist
OPTIONS true; false
INPUT stepscale; value; 0.1; step length as fraction of element size
INPUT hold; flag; 0; whether to hold current streak or start anew
OPTIONS true; false
OUTPUT line; field group; the resulting streakline or streaklines

MODULE Streamline
CATEGORY Realization
DESCRIPTION computes streamlines
INPUT data; vector field; (none); vector field
INPUT start; vector list or geometry field; (center of object); starting point(s)
INPUT time; scalar list; 0; starting time(s)
INPUT head; scalar; (infinity); ending time
INPUT curl; vector field; (no curl); curl to use for twist
INPUT flag; flag; (input dependent); whether to use curl to generate twist
OPTIONS true ; false
INPUT stepscale; value; 0.1; step length as fraction of element size
OUTPUT line; field or group; the resulting streamline(s)

MODULE SuperviseState
CATEGORY Windows
DESCRIPTION manages window state
FLAGS ASYNC
INPUT where; window; (none); where
INPUT defaultCamera; camera; (none); initial or default camera
INPUT resetCamera; flag; 0; reset to default camera
INPUT object; object; (none); initial or default object
INPUT resetObject; flag; 0; reset to default object
INPUT size; vector or value list; (no default); resolution
INPUT events; object; (none); mouse events
INPUT mode; integer; -1; mode (default is all modes turned off)
INPUT args; object; (no default); interactor arguments
OUTPUT object; object; current object
OUTPUT camera; camera; window camera
OUTPUT where; window; input where
OUTPUT events; vector list; unhandled events

MODULE SuperviseWindow
DESCRIPTION manages a window 
CATEGORY Windows
FLAGS ASYNC PIN
INPUT name; string; "SuperviseWindow"; title for window
INPUT display; string; "localhost"; display
INPUT size; vector or value list; [640,480]; resolution
INPUT offset; vector or value list; [0, 0]; offset of window in parent
INPUT parent; window; (no default); parent window
INPUT depth; integer; 8; depth
INPUT visibility; flag; 1; visibility of window 0:closed, 1:open, 2:open on top 
INPUT pick; flag; 0; whether to consider only button down events
INPUT sizeFlag; flag; 0; whether to force the size of an already-existant window
INPUT offsetFlag; flag; 0; whether to force the offset of an already-existant window
INPUT decorations; flag; 1; whether to let the window manager decorate the window
OUTPUT where; window; output where param
OUTPUT size; vector; window size
OUTPUT events; vector list; button events


MODULE Switch
CATEGORY Flow Control 
DESCRIPTION switches an object on or off
INPUT selector; integer; 0; which object to switch
INPUT input; value list or string list or object; (no default); potential object to switch
REPEAT 1
OUTPUT output; object; the object switched


MODULE System
CATEGORY Debugging
DESCRIPTION executes a system function
FLAGS SIDE_EFFECT
INPUT string; string; (none); shell command to execute

MODULE Text
CATEGORY Annotation
DESCRIPTION displays text in space
INPUT string; string or field; (none); the text to display
INPUT position; vector; [0 0 0]; where to display the text
INPUT height; scalar; 1; height of the text in world coordinates
INPUT font; string; "variable"; text font
OPTIONS area; cyril_d; fixed; gothiceng_t; gothicger_t; gothicit_t
OPTIONS greek_d; greek_s; italic_d; italic_t; pitman; roman_d
OPTIONS roman_dser; roman_s; roman_tser; roman_ext; script_d
OPTIONS script_s; variable;
OPTIONS swiss; swissbld; swissit; swissbldit; dutch; dutchit; 
OPTIONS swisscnd; domcasual; symbol; monospace;
INPUT direction [visible:0]; vector; [1 0 0]; direction of baseline
OPTIONS [1 0 0]; [0 1 0]; [0 0 1]
INPUT up [visible:0]; vector; (perpendicular to baseline); direction of vertical strokes
OUTPUT text; color field; string object that can be rendered

MODULE Trace
CATEGORY Debugging
DESCRIPTION enables or disables tracing options
FLAGS SIDE_EFFECT
INPUT what; string; (none); what to trace
OPTIONS time
INPUT how; integer; 1; level of tracing (0=off)
OPTIONS 0 ; 1

MODULE Transform
CATEGORY Rendering
DESCRIPTION generalized transform of an object
INPUT input; object; (none); object to transform
INPUT transform; tensor; (none); 3x3 or 3x4 transformation matrix
OUTPUT output; object; object marked to be transformed

MODULE Translate
CATEGORY Rendering
DESCRIPTION translates an object
INPUT input; object; (none); object to translate
INPUT translation; vector; [0 0 0]; translation amount along x, y and z axes
OUTPUT output; object; object marked to be translated

MODULE Transpose
CATEGORY Import and Export
DESCRIPTION performs a generalized transpose
INPUT input; field; (none); object to transpose
INPUT dimensions; integer list or string list; (no transposition); new coordinate list
OPTIONS 0 1 ; 1 0 
OPTIONS 0 1 2 ; 1 0 2 ; 0 2 1 ; 1 2 0; 2 1 0 ; 2 0 1
OUTPUT output; field; transposed data









MODULE Tube
CATEGORY Annotation
DESCRIPTION produces a tube that follows a path
INPUT line; field; (none); line to be drawn as a tube
INPUT diameter; scalar; (input dependent); the diameter of the tube
INPUT ngon [visible:0]; integer; 8; the number of sides to the tube
OPTIONS 6 ; 8 ; 12 ; 16
INPUT style [visible:0]; string; "sphere"; the style with which to cap ends
OUTPUT tube; field; the line turned into a tube

MODULE Unmark
CATEGORY Structuring
DESCRIPTION unmarks a marked component
INPUT input; field; (none); field with a marked component
INPUT name; string; (input dependent); the component to unmark
OPTIONS data ; positions ; connections ; colors 
OUTPUT output; field; the field with the named component not marked

MODULE UpdateCamera
CATEGORY Rendering
DESCRIPTION alters an existing camera
INPUT camera; camera; (none); camera to be altered
INPUT to; vector or object; (no default); new look-to point
INPUT from; vector or object; (no default); new position of camera
INPUT width; scalar or object; (no default); new width of field of view (for orthographic projection)
INPUT resolution; integer; (no default); new horizontal resolution of image in pixels
INPUT aspect; scalar; (no default); new height/width
INPUT up; vector; (no default); new up direction
OPTIONS [1 0 0] ; [0 1 0] ; [0 0 1]
INPUT perspective; flag; (no default); new projection method: (0) orthographic, (1) perspective
OPTIONS false; true
INPUT angle; scalar; (no default); new view angle in degrees (for perspective projection)
OPTIONS 15.0 ; 30.0 ; 45.0
INPUT background; vector or string; (no default); new image background color
OPTIONS black ; white ; red ; green ; blue
OUTPUT camera; camera; resulting camera altered by inputs

MODULE Usage
CATEGORY Debugging
DESCRIPTION prints current resource utilization
FLAGS SIDE_EFFECT
INPUT what; string; (none); what to print
OPTIONS memory
INPUT how; integer; 0; level of detail

MODULE Verify
CATEGORY Debugging
DESCRIPTION checks an object for internal consistancy
INPUT input ; object; (none); object to check
INPUT how; string; (no default); level of verification
OUTPUT output; object; same object

MODULE VisualObject
CATEGORY Debugging
DESCRIPTION create a renderable representation of input object
INPUT input; object; (none); object to see
INPUT options; string; "v"; layout direction, "v" or "h"
OPTIONS v ; h
OUTPUT output; field; visual representation of the object

MODULE WriteImage
CATEGORY Import and Export
DESCRIPTION writes an image to a file
FLAGS SIDE_EFFECT
INPUT image; image or image series; (none); the image to write
INPUT name; string; "image"; file name
INPUT format; string; ("rgb" or input dependent); format of file
OPTIONS rgb; r+g+b; tiff ; ps color ; ps gray; eps color; eps gray ; gif ; yuv ; miff
INPUT frame; integer; (current + 1); frame to write














MODULE DXLInputNamed
CATEGORY DXLink
FLAGS ASYNC
DESCRIPTION
INPUT name; string; (none); name of input
INPUT default; value or string or object; (no default); default value
OUTPUT output; object; the default value or value sent from remote application 

MODULE DXLOutput
CATEGORY DXLink 
DESCRIPTION Send a string representation of the input to a DXLink application 
FLAGS SIDE_EFFECT
INPUT label[visible:2]; string ; (none); The label associated with the value sent 
INPUT value; value or string or value list or string list; (none);  value sent to the DXLink application 

MODULE DXLOutputNamed
CATEGORY DXLink
DESCRIPTION Send a string representation of the input to a named recipient in a DXLink application
FLAGS SIDE_EFFECT
INPUT name; string ; (none); The label associated with the value sent
INPUT value; value or string or value list or string list; (none);  value sent to the DXLink application

MODULE Execute
CATEGORY Flow Control 
DESCRIPTION changes the execution state
INPUT action; string;  "end"; execution action ("end", "once", "on change")
OPTIONS end; once; on change










MODULE ManageColormapEditor
CATEGORY Interface Control 
DESCRIPTION opens or closes one or more colormap editors 
INPUT name; string list;  (no default); name of colormap editors to open or close(default all)
INPUT open; flag or flag list or string list;  0; open (1) or close (0) the colormap editor, or list of editors which should be open 
OPTIONS false ; true 
INPUT how; string;  "title"; open or close colormap editor by "title" or "label" 
OPTIONS title ; label

MODULE ManageControlPanel
CATEGORY Interface Control 
DESCRIPTION opens or closes one or more control panels
INPUT name; string list;  (no default); names of control panels to open or close(default all)
INPUT open; flag or flag list or string list;  0; open (1) or close (0) the control panels, or list of panels which should be open 
OPTIONS false ; true 

MODULE ManageImageWindow
CATEGORY Interface Control 
DESCRIPTION opens or closes one or more image windows
INPUT name; string list;  (no default); names of windows to open or close(default all)
INPUT open; flag or flag list or string list;  0; open (1) or close (0) the image window, or list of image windows which should be open 
OPTIONS false ; true 
INPUT how; string;  "title"; open or close image window by "title" or "label" 
OPTIONS title ; label

MODULE ManageSequencer
CATEGORY Interface Control 
DESCRIPTION opens or closes the sequencer
INPUT open; flag;  0; open (1) or close (0) the sequencer 
OPTIONS false ; true 









MODULE Integer
CATEGORY Interactor
DESCRIPTION integer interactor
FLAGS REROUTABLE REACH
INPUT id [visible:2] ; string; (none) ;
INPUT data [cache:2]; object; (no default) ; object from which to generate interactor attributes and output value (if required).
INPUT value [visible:2, reroute:0] ; integer; (no default) ; current value of this interactor
INPUT refresh [visible:0, cache:2] ; flag ; 0 ; force reset using current inputs
INPUT min [visible:0,cache:2] ; integer; (min of data) ; minimum of output
INPUT max [visible:0,cache:2] ; integer; (max of data) ; maximum of output
INPUT delta [visible:0,cache:2]; scalar ; (input dependent) ; the interactor increment
INPUT method [visible:0,cache:2]; string ; (rounded, relative or absolute) ; how to interpret delta input
OPTIONS rounded; relative; absolute
INPUT reserved2 [visible:2] ; integer ; 0 ; reserved for later use.
INPUT reserved3 [visible:2] ; integer ; 0 ; reserved for later use.
INPUT label [visible:0, cache:2] ; string ; "Integer" ; global name applied to interactor instances
OUTPUT output; integer; interactor output

MODULE IntegerList
CATEGORY Interactor
DESCRIPTION integer list interactor
FLAGS REROUTABLE REACH
INPUT id [visible:2] ; string; (none) ;
INPUT data [cache:2]; object; (no default) ; object from which to generate interactor attributes and output value (if required).
INPUT value [visible:2,reroute:0]; integer list; (none);current value of this interactor
INPUT refresh [visible:0, cache:2] ; flag ; 0 ; force reset using current inputs
INPUT min [visible:0,cache:2] ; integer; (min of data) ; minimum of output
INPUT max [visible:0,cache:2] ; integer; (max of data) ; maximum of output
INPUT delta [visible:0,cache:2]; scalar ; (input dependent) ; the interactor increment
INPUT method [visible:0,cache:2]; string ; (rounded, relative or absolute) ; how to interpret delta input
OPTIONS rounded; relative; absolute
INPUT reserved2 [visible:2] ; integer; (input dependent) ; reserved for later.
INPUT nitems [visible:0,cache:2] ; integer ; 11 ; number of items in initial list
INPUT label [visible:0, cache:2] ; string ; "IntegerList" ; global name applied to interactor instances
OUTPUT output; integer list; interactor output

MODULE Scalar
CATEGORY Interactor
DESCRIPTION scalar interactor
FLAGS REROUTABLE REACH
INPUT id [visible:2] ; string; (none) ;
INPUT data [cache:2]; object; (no default) ; object from which to generate interactor attributes and output value (if required).
INPUT value [visible:2,reroute:0]; scalar; (no default) ; current value of this interactor
INPUT refresh [visible:0, cache:2] ; flag ; 0 ; force reset using current inputs
INPUT min [visible:0,cache:2] ; scalar; (min of data) ; minimum of output
INPUT max [visible:0,cache:2] ; scalar; (max of data) ; maximum of output
INPUT delta [visible:0,cache:2]; scalar ; (input dependent) ; the interactor increment
INPUT method [visible:0,cache:2]; string ; (rounded, relative or absolute) ; how to interpret delta input
OPTIONS rounded; relative; absolute
INPUT decimals [visible:0,cache:2] ; integer; (input dependent) ; number of decimal places to be displayed
INPUT reserved2 [visible:2] ; scalar ; 0 ; reserved for later use.
INPUT label [visible:0, cache:2] ; string ; "Scalar" ; global name applied to interactor instances
OUTPUT output; scalar; interactor output

MODULE ScalarList
CATEGORY Interactor
DESCRIPTION scalar list interactor
FLAGS REROUTABLE REACH
INPUT id [visible:2] ; string; (none) ;
INPUT data [cache:2]; object; (no default) ; object from which to generate interactor attributes and output value (if required).
INPUT value [visible:2,reroute:0] ; scalar list; (none);current value of this interactor
INPUT refresh [visible:0, cache:2] ; flag ; 0 ; force reset using current inputs
INPUT min [visible:0,cache:2] ; scalar; (min of data) ; minimum of output
INPUT max [visible:0,cache:2] ; scalar; (max of data) ; maximum of output
INPUT delta [visible:0,cache:2]; scalar ; (input dependent) ; the interactor increment
INPUT method [visible:0,cache:2]; string ; (rounded, relative or absolute) ; how to interpret delta input
OPTIONS rounded; relative; absolute
INPUT decimals [visible:0,cache:2] ; integer ; (input dependent) ; number of decimal places to be displayed
INPUT nitems [visible:0,cache:2] ; integer ; 11 ; number of items in initial list
INPUT label [visible:0, cache:2] ; string ; "ScalarList" ; global name applied to interactor instances
OUTPUT output; scalar list; interactor output

MODULE SetDXLInputNamed
INPUT name; string; (no default); name of input to set
INPUT object; object; (no default); value to set named input to

MODULE Vector
CATEGORY Interactor
DESCRIPTION vector interactor
FLAGS REROUTABLE REACH
INPUT id [visible:2] ; string; (none) ;
INPUT data [cache:2]; object; (no default) ; object from which to generate interactor attributes and output value (if required).
INPUT value [visible:2,reroute:0]; vector; (no default) ; current value of this interactor
INPUT refresh [visible:0, cache:2] ; flag ; 0 ; force reset using current inputs
INPUT min [visible:0,cache:2] ; scalar or vector; (min of data) ; minimum of output vector components
INPUT max [visible:0,cache:2] ; scalar or vector; (max of data) ; maximum of output vector components
INPUT delta [visible:0,cache:2]; scalar or vector ; (input dependent) ; the interactor increment
INPUT method [visible:0,cache:2]; string ; (rounded, relative or absolute) ; how to interpret delta input
OPTIONS rounded; relative; absolute
INPUT decimals [visible:0,cache:2] ; integer or vector; (input dependent) ; number of decimal places to show in vector components
INPUT reserved2 [visible:2] ; vector ; [0 0 0] ; reserved for later use.
INPUT label [visible:0, cache:2] ; string ; "Vector" ; global name applied to interactor instances
OUTPUT output; vector; interactor output

MODULE VectorList
CATEGORY Interactor
DESCRIPTION vector list interactor
FLAGS REROUTABLE REACH
INPUT id [visible:2] ; string; (none) ;
INPUT data [cache:2]; object; (no default) ; object from which to generate interactor attributes and output value (if required).
INPUT value [visible:2,reroute:0] ; vector list; (none);current value of this interactor
INPUT refresh [visible:0, cache:2] ; flag ; 0 ; force reset using current inputs
INPUT min [visible:0,cache:2] ; scalar or vector ; (min of data) ; minimum of output vector components
INPUT max [visible:0,cache:2] ; scalar or vector ; (max of data) ; maximum of output vector components
INPUT delta [visible:0,cache:2]; scalar or vector ; (input dependent) ; the interactor increment
INPUT method [visible:0,cache:2]; string ; (rounded, relative or absolute) ; how to interpret delta input
OPTIONS rounded; relative; absolute
INPUT decimals [visible:0,cache:2] ; integer or vector; (input dependent) ; number of decimal places to show in vector components
INPUT nitems [visible:0,cache:2] ; integer ; 11 ; number of items in initial list
INPUT label [visible:0, cache:2] ; string ; "VectorList" ; global name applied to interactor instances
OUTPUT output; vector list; interactor output

MODULE Selector
CATEGORY Interactor
DESCRIPTION selector interactor
FLAGS REROUTABLE REACH
INPUT id [visible:2] ; string; (none) ;
INPUT currentstring [visible:2,reroute:1]; string; (no default) ; current output string
INPUT currentvalue [visible:2,reroute:0]; value or string; (no default) ; current output value
INPUT stringdata [cache:2] ; string list or group; (no default) ; specifies or derives list of potential output strings
INPUT valuelist [visible:0,cache:2] ; integer or value list or string list; (0 based list) ; list of potential output values
INPUT cull [visible:0, cache:2] ; flag ; 0 ; controls handling of zero length strings
OPTIONS false; true
INPUT label [visible:0,cache:2] ; string; "Selector" ; global name applied to interactor
OUTPUT value; value or string; value
OUTPUT name; string ; string value


MODULE SelectorList
CATEGORY Interactor
DESCRIPTION Selector list interactor
FLAGS  REROUTABLE REACH
INPUT  id [visible:2] ; string; (none) ;
INPUT  currentstring [visible:2,reroute:1] ; string list; (no default) ; current output st ring
INPUT  currentvalue [visible:2,reroute:0] ; value list or string or string list; (no default) ; current output value
INPUT  stringdata [cache:2] ; string list or group; (no default) ; specifies or derives list of potential output strings
INPUT  valuelist [visible:0,cache:2] ; integer or value list or string list; (0 based list) ; list of potential output values
INPUT  cull [visible:0, cache:2] ; flag ; 0 ; controls handling of zero length strings
INPUT  label [visible:0,cache:2] ; string; "SelectorList" ; global name applied to interactor
OUTPUT value; value list or string list ; value
OUTPUT name;  string list; string value







MODULE Colormap
CATEGORY Special
DESCRIPTION represents the colormap generated by a colormap editor
FLAGS REROUTABLE REACH
INPUT huemap [visible:2] ; vector list or scalar list; (no default); 2-vector list of data-value/hue pairs
INPUT satmap [visible:2] ; vector list; (no default); 2-vector list of data-value/saturation pairs
INPUT valmap [visible:2] ; vector list or scalar list; (no default); 2-vector list of data-value/value pairs
INPUT opmap [visible:2] ; vector list or scalar list; (no default); 2-vector list of data-value/opacity pairs
INPUT id [visible:2] ; string ; (none) ;
INPUT data [cache:2] ; field or group ; (no default) ; object from which to generate interactor attributes and output value (if required)
INPUT min [visible:0, cache:2] ; scalar ; (min of data) ; minimum of colormap range
INPUT max [visible:0, cache:2] ; scalar ; (max of data) ; maximum of colormap range
INPUT nbins [visible:0, cache:2] ; integer ; 20 ; number of bins in histogram
INPUT colormap [cache:2] ; field or group ; (no default) ; rgb colormap to use
INPUT opacity [cache:2] ; field ; (no default) ; opacity map to use
INPUT minmax [visible:2] ; scalar list ; (no default) ; ui minimum and maximum
INPUT defaulthue [visible:2] ; vector list; (no default); default data-value/huepairs
INPUT defaultsat [visible:2] ; vector list; (no default); default data-value/sat pairs
INPUT defaultval [visible:2] ; vector list; (no default); default data-value/val pairs
INPUT defaultop [visible:2] ; vector list; (no default); default data-value/op pairs
INPUT defaultmin [visible:2] ; scalar ; (no default); default min of map space
INPUT defaultmax [visible:2] ; scalar ; (no default); default max of map space
INPUT title [visible:0, cache:2] ; string ; "Colormap Editor" ; title of editor 
OUTPUT rgb; field; rgb color field
OUTPUT opacity; field; opacity field

MODULE Sequencer
CATEGORY Special
DESCRIPTION Sequence Controller
FLAGS REROUTABLE REACH
INPUT id [visible:2] ; string; (none) ;
INPUT data [visible:2] ; object ; (no default) ; reserved for later use
INPUT frame [visible:2, reroute:0] ; integer; (no default) ; current value of @frame
INPUT min [cache:2] ; integer ; 1 ; minimum of integer sequence
INPUT max [cache:2] ; integer ; 100 ; maximum of integer sequence
INPUT delta [visible:0,cache:2]; integer ; 1 ; indicates the step between numbers in the sequence
INPUT attr [visible:2]; integer list ; (no default) ; holds frame control values (min, max, delta...)
OUTPUT frame; integer ; frame number

MODULE Toggle
CATEGORY Interactor
DESCRIPTION Select between two different values
FLAGS REROUTABLE  REACH
INPUT id     [visible:2]; object; (none) ;
INPUT currentval [visible:2,reroute:0]; value or string; (none); current output value
INPUT isset [visible:2] ;  flag ; (no default) ; is the toggle set
INPUT setvalue [cache:2] ;  value or string; 1 ; output value toggle when set
INPUT unsetvalue [cache:2] ;  value or string; 0 ; output value toggle when unset
INPUT label  [visible:0, cache:2] ;  string; (no default) ; global name applied to interactor
OUTPUT output ;  value or string; the selected toggle value


