/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>


#define LOG_FATAL	0
#define LOG_ERROR	1
#define LOG_WARNING	2
#define LOG_STATUS	3
#define LOG_INFO	4
#define LOG_VERBOSE	5

#define LOG_APPEND	0x8000
#define LOG_MASK	0x7fff

extern int _dxd_exErrorPrintLevel;

int lprintf(int type, char *format, ...);
