#include "../base/UIConfig.h"

#include <dxconfig.h>
#include "../base/defines.h"
#include "../base/Strings.h"
#include "../base/ErrorDialogManager.h"
#include "oem.h"

char *ScrambleString(const char *str, const char *hash)
{
    ErrorMessage("Net file encryption algorithms have been removed from OpenDX");
    abort();
}

char *ScrambleAndEncrypt(const char *src, const char *hash, char *cryptbuf)
{
    ErrorMessage("Net file encryption algorithms have been removed from OpenDX");
    abort();
}
