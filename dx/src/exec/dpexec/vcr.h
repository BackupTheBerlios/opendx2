/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>


#ifndef	__VCR_H
#define	__VCR_H

/*
 * Commands
 */

#define VCR_C_STOP		0		/* stop vcr 		*/
#define VCR_C_PAUSE		1		/* pause playing	*/
#define VCR_C_PLAY		2		/* play			*/
#define VCR_C_STEP		3		/* step one frame	*/
#define VCR_C_FLAG		4		/* set a flag		*/
#define VCR_C_TREE		5		/* attach a new graph	*/
#define	VCR_C_DIR		6		/* set the direction	*/

/*
 * Flags to change
 */

#define	VCR_F_FORWARD		4
#define	VCR_F_PALIN		2
#define	VCR_F_LOOP		1

#define	VCR_STATE_B__		0x0
#define	VCR_STATE_B_L		0x1
#define	VCR_STATE_BP_		0x2
#define	VCR_STATE_BPL		0x3
#define	VCR_STATE_F__		0x4
#define	VCR_STATE_F_L		0x5
#define	VCR_STATE_FP_		0x6
#define	VCR_STATE_FPL		0x7

/*
 * Directions for the play and step commands
 */

#define	VCR_D_FORWARD		(1)
#define	VCR_D_BACKWARD		(- VCR_D_FORWARD)

extern void _dxf_ExVCRRedo(void);
extern void _dxf_ExVCRChange(void);


#endif /* __VCR_H */
