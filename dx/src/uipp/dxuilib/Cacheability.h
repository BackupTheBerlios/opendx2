//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Cacheability.h,v 1.1 1999/03/24 15:17:38 gda Exp $
 */

#ifndef _Cacheability_h
#define _Cacheability_h
//
// Note: 
//

enum Cacheability {
    //
    // Define constants that indicate the module level cacheability. 
    // NOTE: The number assignments used here should match those used by the
    // server to determine cacheability.
    //
    ModuleNotCached 	 = 0,
    ModuleFullyCached 	 = 1,	
    ModuleCacheOnce	 = 2,

    //
    // This used to define the cacheability of various entities in the server.
    // For now those entities include the Nodes outputs (cached based on all
    // the input values) and individual inputs and outputs.
    // NOTE: The number assignments used here should match those used by the
    // server to determine cacheability.
    // Further, note that the code may assume the these values map 1 to 1 ont
    // the Module* cache enumated values.
    //
    OutputNotCached 	 = 0,
    OutputFullyCached 	 = 1,	
    OutputCacheOnce	 = 2,

    // 
    // Used to define cacheability internal to a system macro (in
    // particular, the Image macro)
    InternalsNotCached	 = 0,
    InternalsFullyCached = 1,
    InternalsCacheOnce   = 2,

    // 
    // Used to map cache attributes on INPUT statemtents in the mdf files.
    // 'cache:0' means that the input is not used to derived the output cache
    // tag, where 'cache:1' means the opposite.
    // NOTE: The number assignments used here should match those used by the
    // mdf file. 
    //
    InputDoesNotDeriveOutputCacheTag 	= 0,	// 'cache:0'
    InputDerivesOutputCacheTag 		= 1 		// 'cache:1'
};

#endif  // _Cacheability_h

