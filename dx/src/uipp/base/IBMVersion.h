/* //////////////////////////////////////////////////////////////////////// */
/*                            DX  SOURCEFILE                                */
/* IBMVersion.h -							    */
/* Version numbers.							    */
/* //////////////////////////////////////////////////////////////////////// */

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/IBMVersion.h,v 1.1 1999/03/24 15:17:23 gda Exp $
 */


#ifndef _IBMVersion_h
#define _IBMVersion_h


/*
 * Create a single number from the 3 version numbers that can be used to
 * do integer compares to determine relative versions. 
 *
 */
#define VERSION_NUMBER(maj,min,mic)     (((maj) << 16) + ((min) << 8) + (mic))


/*
 * Define this while code is in development, but undef it before a release.
 */
#if 1 
#define BETA_VERSION 
#endif

/* The DX release version number. */
#define IBM_MAJOR_VERSION	4
#define IBM_MINOR_VERSION	1
#define IBM_MICRO_VERSION	1


#endif /* _IBMVersion_h */
