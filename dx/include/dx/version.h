/*********************************************************************/
/*                        DX  SOURCEFILE                             */
/*********************************************************************/


#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif


/* routines to return info about the product version numbers */
Error DXVersion(int *version, int *release, int *modification);
Error DXVersionString(char **name);


/* the following routines are only used when dealing with outboard 
 * modules or dynamically loaded modules.
 */

#define DXD_OUTBOARD_INTERFACE_VERSION  1
#define DXD_SYMBOL_INTERFACE_VERSION    1
#define DXD_HWDD_INTERFACE_VERSION	1

Error DXOutboardInterface(int *version);
Error DXSymbolInterface(int *version);
Error DXHwddInterface(int *version);


#if defined(__cplusplus) || defined(c_plusplus)
}
#endif
