#define MAGICK5
/* Magick5 is actually incompatible with Magick <= 5.1.1 : go figure */
/* remove the MAGICK5 define above for Magick 4.0.29 */
/* remove the MAGICK5 define above for Magick 5.1.1, it may work, but how? */
/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
/*
* _IM_image.c : calls ImageMagick API to write files, especially useful for those files
*  whose formats DX does not support natively. 
* FIXME:  needs read modifications too!
* FIXME:  needs to avail itself of newly added IM 4.2.8  blob support rather than write
*         intermediate miff file.  requires dx be able to read/write miff from/to memory image.
*FIXME: dx does not know all extensions that IM supports, can dx query IM API for the
*	supported extensions and thereby alleviate the tedious supplying of both format and extension?
*/

/*
* This was coded to preserve dx's prior behavior for other extensions/formats, entailing some complexity.
* How did we get here? 
*
* Currently from WriteImage, there are two ways to get here: 
* (1) special cases e.g. gif where an entry in ImageTable(in _rw_image.c) 
*     specifies the format and acceptable extensions and write_im is specified as the write function.
*     The special case is triggered by giving the format and/or a listed extension.
* (2) "Image Magick supported format" format was specified and or the extension was first matched in 
*	the table entry for "Image Magick supported format" format.
*     The extension must be included, recognized or not, in this case so ImageMagick knows what to write.
*     This scheme permits the user to specify, via an extention, an output format the dx coders did not know about
*	but that Image Magick has added (perhaps later, perhaps as a delegate).
*     This scheme also allows the coexistence of DX methods and IM methods for writing image files.  For example,
*	a format of null and an .rgb (or missing) extension gives the DX rgb output, while a format of 
*	"Image Magick supported format" and an .rgb extension gives the more conventional raw red/green/blue bytes in a file.
*	Another example is specifying "filename.miff" and "Image Magick supported format", where dx writes its miff
*	and IM converts and overwrites it to its liking.
*
* DX prefers the "format" to the extension, IM goes by the extension.
* WriteImage parameters can be (optional) format and (optional) filename+extension or filename .
* Whether dot-anything is accepted as an extension depends on the listing in ImageTable (_rw_image.c).  
* dx will assume dx rgb format if the
*format is null and the filename's extension is not recognized (i.e. we won't get to this function).
*if dx recognized the extension for the format, the extension was
*removed from the basename and now the ImageArgs.extension points to the extension.
*however, dx will not (currently) have hardcoded all extensions that IM supports.
*So it is easily possible that by the time we get here, we have a format of "Image Magick supported format" or null
* and a filename
* with or without an extension appended, with or without a null imageargs.extension.
*/
/*
* DX and IM name spaces collide on these terms (for IM 4.2.8 at least)
*/
#define ImageInfo DXImageInfo
#define ImageType DXImageType
#include <dxconfig.h>


#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <dx/dx.h>
#include <_helper_jea.h>
#include <_rw_image.h>
#include <sys/types.h>

#if ( CAN_HAVE_ARRAY_DASD == 1 )
#include <iop/mov.h>
#include <iop/pfs.h>
#endif

#if defined(HAVE_SYS_STAT_H)
#include <sys/stat.h>
#endif

#ifdef HAVE_LIBMAGICK
/* we have some namespace conflicts with Image Magick */
#undef ImageInfo
#undef ImageType
#include <magick/api.h>
#endif /* def HAVE_LIBMAGICK */

#if (0)
#define DEBUGMESSAGE(mess) DXMessage((mess)) 
#else
#define DEBUGMESSAGE(mess)
#endif

static Error write_im(RWImageArgs *iargs);
/*
 * DXWrite out the given image in some format supported by Image Magick
 * currently through an intermediary file in miff (Magick Image File Format)
 * though ideally this would use ImageMagick-4.2.8+'s blob support for in-memory translation.
 */
Error
_dxf_write_im(RWImageArgs *iargs)
{
/*
*    how does one error check ?  let IM flag the error for an unsupported image format
*    if (iargs->imgtyp != img_typ_fb)
*	DXErrorGoto(ERROR_INTERNAL, "_dxf_write_fb: mismatched image types");
*/

    return write_im(iargs);
/*
  error:
    return ERROR;
 */
}

static Error write_im(RWImageArgs *iargs)
{
#ifdef HAVE_LIBMAGICK
	RWImageArgs tmpargs = *iargs;
	Image
	   *image;


#ifdef MAGICK5
	ExceptionInfo
	   exception_info;
	ImageInfo
           * image_info;
#else
	ImageInfo
           image_info;
	MagickInfo * magick_info;

#endif

	int miff_exists_flag ;
	char* miff_filename ;
	FILE* miff_fp;

	DEBUGMESSAGE("requested extension is ");
/* if basename's .ext recognized as a format, it is removed from basename and iargs->extension points to it */
	if(!iargs->extension)
	   {
		/* no extension or not recognized */
		if(iargs->format)
			{
				if(strcmp(iargs->format,"Image Magick supported format"))
					{
						char* firstspace;
						/* not "Image Magick supported format" format, use format for extension */
						iargs->extension=iargs->format;
						/* strip junk we can't deal withafter format... like "gif delayed=1" */
						firstspace=strchr(iargs->extension, ' ');
						if(firstspace != NULL) *firstspace='\0';
						
					}
			}
	   }
/* still no recognized extension or "unique" format?  it had better be on the filename! */
	if(!iargs->extension)
	   {
		int i;
		for(i=strlen(iargs->basename);i>0;--i)
			{
				if(iargs->basename[i]=='.')
					{
						iargs->extension=&((iargs->basename)[i+1]);
						iargs->basename[i]='\0';
						i=0;
					} else if (iargs->basename[i]=='/') i=0;
			}
	   }
/*
* before proceeding,
* find out if we can handle the conversion to the requested extension
*/
#ifndef MAGICK5
	DEBUGMESSAGE(iargs->extension);
	magick_info=GetMagickInfo(iargs->extension);
	if(magick_info){
		DEBUGMESSAGE("magick_info successful for requested extension, assuming support");
	   } else {
	  	DXMessage("The specified extension or format was unrecognized or unsupported, tried to use:");
	  	DXMessage(iargs->extension);
	  	DXMessage("if format specified is *exactly* 'Image Magick supported format' then perhaps the file extension is faulty.");
	  	DXErrorReturn(ERROR_BAD_PARAMETER,"invalid extension, format, or unsupported by ImageMagick");
	   }
	
#endif
/*
* 8/99 some ambiguity here, since miff files are appendable.
* My arbitrary choice: if the miff file exists already, we append and do not erase.
* if the miff file does not exist, we erase when we are done.
* So if you want a multi-image file in some non-natively-supported-dx-format,
* writeimage to a miff, then on the last frame writeimage to e.g. an
* mpeg of the same name, specifying "im" format.  Then it is up to you to erase it.
* Maybe some other scenario will prevail.
*/
	
/*
* write the miff file from DX
*/
        tmpargs.format="miff";
        tmpargs.imgtyp=img_typ_miff;

/* does file exist? */
	miff_filename = (char *)DXAllocateLocal(strlen(iargs->basename)+strlen(tmpargs.format)+2);
	strcpy(miff_filename,iargs->basename);
	strcat(miff_filename,".");
	strcat(miff_filename,tmpargs.format);
	if((miff_fp=fopen(miff_filename,"r")))
		{
			miff_exists_flag=1;
			fclose(miff_fp);
		} else {
			miff_exists_flag=0;
		}
	
	DEBUGMESSAGE("starting miff conversion");
	DEBUGMESSAGE(iargs->basename);
	_dxf_write_miff(&tmpargs);

      /*
        Initialize the image info structure and read an image.
      */
#ifdef MAGICK5
      GetExceptionInfo(&exception_info); 
      image_info=CloneImageInfo((ImageInfo *) NULL);
#else
      GetImageInfo(&image_info);
#endif
	
#ifdef MAGICK5
      (void) strcpy(image_info->filename,iargs->basename);
      (void) strcat(image_info->filename,".");
      (void) strcat(image_info->filename,tmpargs.format);
	DEBUGMESSAGE("reading following file");
	DEBUGMESSAGE(image_info->filename);
#else
      (void) strcpy(image_info.filename,iargs->basename);
      (void) strcat(image_info.filename,".");
      (void) strcat(image_info.filename,tmpargs.format);
	DEBUGMESSAGE("reading following file");
	DEBUGMESSAGE(image_info.filename);
#endif
#ifdef MAGICK5
      image=ReadImage(image_info,&exception_info); 
#else
      image=ReadImage(&image_info);
#endif
	DEBUGMESSAGE("back from ReadImage");
      if (image == (Image *) NULL) {
	DEBUGMESSAGE("oops it was null");
	  DXErrorReturn(ERROR_BAD_PARAMETER,"Image Magick API could not read file");
	}
	DEBUGMESSAGE("looks like ReadImage successful, we're going to try to write:");
      /*
        Write the image with ImageMagick
      */
      (void) strcpy(image->filename,iargs->basename);
    if(iargs->extension)
	{
      (void) strcat(image->filename,".");
      (void) strcat(image->filename,iargs->extension);
	}
	
	DEBUGMESSAGE(image->filename);
#ifdef MAGICK5
      WriteImage(image_info,image);
#else
      WriteImage(&image_info,image);
#endif
	DEBUGMESSAGE("back from WriteImage, what did I get?");
      DestroyImage(image);
	DEBUGMESSAGE("back from DestroyImage");
	if((iargs->extension) && (!miff_exists_flag) && (strcmp("miff",iargs->extension))) /* if using IM to write an "official" miff file, don't erase! */
	   {
		DEBUGMESSAGE("miff file did not exist, trying to remove it");
		remove(miff_filename);
		DEBUGMESSAGE(miff_filename);
	   }
	DXFree((Pointer)miff_filename);
   return (OK);
#else /* ndef HAVE_LIBMAGICK */
	/* FIXME ERROR_BAD_PARAMETER is poor choice of error to throw */
	  DXErrorReturn(ERROR_BAD_PARAMETER,"Image Magick not included in build");
#endif /* def HAVE_LIBMAGICK */
    }

