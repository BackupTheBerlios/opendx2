Notes
--------
This directory is used for building OpenDX with Visual Studio. There
are a few requirements that must be met.

1) Many source files must be created on a UN*X system before trying 
   to compile or even open the Visual Studio project. These files
   are created with awk scripts and Bison. Included in this directory
   is a UN*X script that can be run on the src tree to create these
   files (unix-build-sources).

2) The libraries are being built as dll's only. If you require static
   libs, you will have to do the work yourself. Good luck.

3) A valid dxconfig.h script is included, but may need editted if you
   don't have things like ImageMagick installed and ready to link to.


The following are some notes about the additional libraries needed 
for added functionality.

netcdf - 
------------------------
Place netcdf-3.6.0-p1 at same level as VisualDX. 
In ncx.h, it will be required to change the def of X_FLOAT_MAX to
#define X_FLOAT_MAX	3.402823466e+38f
due to MS's new def of FLT_MAX.


ImageMagick - 
------------------------
Place ImageMagick 6.2.6-1 at same level as VisualDX.
This project includes a modified version of the VisualMagick
project, but the source files are still located in the original
source directory.


cdf - 
------------------------
Place cdf31-dist at same level as VisualDX.
in cdfdist.h -- need to fix line to read
#    if (_MSC_VER >= 1300) && (_MSC_VER < 1400) && (WINVER < 0x0500)
A modified cdf vcproj is included here, but still links to the
original source files.


zlib -
------------------------
For cdf, zlib must be available. Download and place zlib123-dll
at the same level as VisualDx.


hdf - 
------------------------
Get the HDF4.2r1 source and inside extract the Win32.nofortan 
folder.