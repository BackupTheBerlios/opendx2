/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/exec/dxmods/importtable.c,v 1.3 1999/05/10 15:45:27 gda Exp $
 */

#include <dxconfig.h>


#include <dx/dx.h>
#include "import.h"



/* prototypes for functions used in table */
extern Error  _dxftry_ncdf(struct parmlist *p);
extern Object _dxfget_ncdf(struct parmlist *p);
extern Error  _dxftry_hdf(struct parmlist *p);
extern Object _dxfget_hdf(struct parmlist *p);
extern Error  _dxftry_dx(struct parmlist *p);
extern Object _dxfget_dx(struct parmlist *p);
extern Error  _dxftry_cdf(struct parmlist *p);
extern Object _dxfget_cdf(struct parmlist *p);
extern Error  _dxftry_bin(struct parmlist *p);
extern Object _dxfget_bin(struct parmlist *p);
extern Object _dxf_gi_get_gen(struct parmlist *p);
extern Error  _dxftry_wv(struct parmlist *p);
extern Object _dxfget_wv(struct parmlist *p);
extern Object _dxfget_cm(struct parmlist *p);


/* 
 * table of entry points for each format.
 *
 *  for each type of file to be imported, three things must be supplied:
 *   a function to determine if this is a valid file of this type
 *   a function to actually import the data and return it
 *   a list of format strings which indicate this type of file
 * 
 *  if the autotype function is null, the extension must be given for import
 *   to process this type of file.
 *
 */
struct import_table _dxdImportTable[] = {

 /* netCDF */	_dxftry_ncdf,	_dxfget_ncdf,   {"cdf","ncdf", "nc",
							"netcdf","netCDF",0},
 /* HDF */	_dxftry_hdf,	_dxfget_hdf,    {"hdf", 0},
 /* bin */	_dxftry_bin,	_dxfget_bin,    {"bin", 0},
 /* CDF */	_dxftry_cdf,	_dxfget_cdf,    {"CDF", 0},
 /* general */	NULL,	        _dxf_gi_get_gen,{"general", "gai", 0},
 /* DX */	_dxftry_dx,	_dxfget_dx,	{"dx", 0},
 /* wv90 */	_dxftry_wv,	_dxfget_wv,	{"wv90", "fieldhdr", 0},
 /* cm */	NULL,		_dxfget_cm,	{"cm", 0},
 /* ADD HERE */
 /* must be last */  0,              0,         {0},

};

