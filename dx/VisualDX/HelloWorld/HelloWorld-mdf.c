/* Automatically generated - may need to edit! */

#include <dx/dx.h>
#include <dx/modflags.h>

#if defined(intelnt) || defined(WIN32)
#include <windows.h>
#endif

extern Error DXAddModule (char *, ...);

#if defined(intelnt) || defined(WIN32)
void FAR WINAPI DXEntry()
#else
void DXEntry()
#endif
{
    {
        extern Error m_Hello(Object *, Object *);
        DXAddModule("Hello", m_Hello, 0,
            1, "value",
            1, "greeting");
    }
}
