/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>


#ifndef	__SYSVARS_H
#define	__SYSVARS_H

#define	VCR_ID_START		"@startframe"
#define	VCR_ID_END		"@endframe"
#define	VCR_ID_DELTA		"@deltaframe"
#define	VCR_ID_NEXT		"@nextframe"
#define	VCR_ID_FRAME		"@frame"

#define PROMPT_ID_PROMPT	"@prompt"
#define PROMPT_ID_CPROMPT	"@cprompt"

#ifndef EX_PROMPT
#define EX_PROMPT	"dx> " 
#endif
#ifndef EX_CPROMPT
#define EX_CPROMPT	"  > "
#endif

void _dxf_ExPromptSet(char *var, char *val);
char *_dxf_ExPromptGet(char *var);

#endif	/* __SYSVARS_H */
