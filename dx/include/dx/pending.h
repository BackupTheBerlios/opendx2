/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

Error
DXSetPendingCmd(char *, char *, int (*)(Private), Private);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif
