/*****************************************************************************/
/*                            DX  SOURCEFILE                                 */
/*****************************************************************************/

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/help.h,v 1.1 1999/03/24 15:17:25 gda Exp $
 */

#include "defines.h"

#include "history.h"
#include "helplist.h"
#include "helpstack.h"
#if !defined(OS2)  && !defined(DXD_WIN)
#include <sys/param.h>
#endif

#define SPOTFILE "spots"
#define README_PREFIX "README"
#define README_PLATFORM "README_PLATFORM"
#define README_GENERIC "README_GENERIC"

typedef struct {
   Widget toplevel;
   Widget goback;
   Widget menushell;
   Widget hbar;
   Widget vbar;
   Widget swin;
   Stack  *fontstack;
   Stack  *colorstack;
   HistoryList  *historylist;
   int    linkType;
   char   filename[MAXPATHLEN];
   char   label[MAXPATHLEN];
   Bool   getposition;
   SpotList   *spotlist;
   Bool   mapped;

} UserData;


typedef struct {
 char *String;
 char *FileName;
 char *Font;
 char *Color;

} HelpIndex;


HelpIndex *MakeIndexEntry (char *File, char *str);

char *BuildHelpIndex(Widget RefWidget, HelpIndex **IndexTable, int Entries);

extern const char *GetHelpDirectory();
