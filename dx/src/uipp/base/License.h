/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/License.h,v 1.1 1999/03/24 15:17:23 gda Exp $
 */


#ifndef _License_h
#define _License_h

#define AUTH_MSG_LEN 		1024 

enum LicenseTypeEnum {
    Unlicensed		= 0,
    UndeterminedLicense	= 1,

    // Note that these must match thouse used by dxshadow.
    ConcurrentLicense	= 0xafe3,
    FullyLicensed	= ConcurrentLicense,
    NodeLockedLicense	= 0xb673,
    TimedLicense	= 0x3ad0,

    // These are actually different classes of the above.
    // For example, one may have a concurrent runtime license.
    // Note that these must match thouse used by dxshadow.
    ViewerLicense	= 0x0348,	// Standard DX (development) license 
    RunTimeLicense	= 0x4398,	// Standard DX (development) license 
    DeveloperLicense	= 0xde1d, 	// DX Run-time license
    FullFunctionLicense = DeveloperLicense
};

#include <X11/Intrinsic.h>

void UIGetLicense(const char *root, 
			XtInputCallbackProc lostLicense,
                        LicenseTypeEnum *appLic,
                        LicenseTypeEnum *funcLic);

char *GenerateExecKey(const char *inkey, LicenseTypeEnum licenseType);



#endif // _License_h
