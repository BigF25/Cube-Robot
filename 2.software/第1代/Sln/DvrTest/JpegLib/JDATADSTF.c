////////////////////////////////////////////////////////////////////////
//
//	Note : this file is included as part of the Smaller Animals Software
//	JpegFile package. Though this file has not been modified from it's 
//	original IJG 6a form, it is not the responsibility on the Independent
//	JPEG Group to answer questions regarding this code.
//	
//	Any questions you have about this code should be addressed to :
//
//	CHRISDL@PAGESZ.NET	- the distributor of this package.
//
//	Remember, by including this code in the JpegFile package, Smaller 
//	Animals Software assumes all responsibilities for answering questions
//	about it. If we (SA Software) can't answer your questions ourselves, we 
//	will direct you to people who can.
//
//	Thanks, CDL.
//
////////////////////////////////////////////////////////////////////////

/*
 * jdatadst.c
 *
 * Copyright (C) 1994-1996, Thomas G. Lane.
 * This file is part of the Independent JPEG Group's software.
 * For conditions of distribution and use, see the accompanying README file.
 *
 * This file contains compression data destination routines for the case of
 * emitting JPEG data to a file (or any stdio stream).  While these routines
 * are sufficient for most applications, some will want to use a different
 * destination manager.
 * IMPORTANT: we assume that fwrite() will correctly transcribe an array of
 * JOCTETs into 8-bit-wide elements on external storage.  If char is wider
 * than 8 bits on your machine, you may need to do some tweaking.
 */

/* this is not a core library module, so it doesn't define JPEG_INTERNALS */
#include "jinclude.h"
#include "jpeglib.h"
#include "jerror.h"


/* Expanded data destination object for stdio output */

typedef struct {
  struct jpeg_destination_mgr pub; /* public fields */

  XXX_JPEG_FILE_BUFFER * outfile;  /* target stream */
  JOCTET * buffer;  /* start of buffer */
} my_destination_mgrf;

typedef my_destination_mgrf * my_dest_ptrf;

#define OUTPUT_BUF_SIZE  4096 /* ??????????С*/


/*
 * Initialize destination --- called by jpeg_start_compress
 * before any data is actually written.
 */

METHODDEF(void)
init_destination (j_compress_ptr cinfo)
{
my_dest_ptrf dest = (my_dest_ptrf) cinfo->dest;

  dest->buffer = (JOCTET *)
      (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
      OUTPUT_BUF_SIZE * SIZEOF(JOCTET));

  dest->pub.next_output_byte = dest->buffer;
  dest->pub.free_in_buffer = OUTPUT_BUF_SIZE;

}


/*
 * Empty the output buffer --- called whenever buffer fills up.
 *
 * In typical applications, this should write the entire output buffer
 * (ignoring the current state of next_output_byte & free_in_buffer),
 * reset the pointer & count to the start of the buffer, and return TRUE
 * indicating that the buffer has been dumped.
 *
 * In applications that need to be able to suspend compression due to output
 * overrun, a FALSE return indicates that the buffer cannot be emptied now.
 * In this situation, the compressor will return to its caller (possibly with
 * an indication that it has not accepted all the supplied scanlines).  The
 * application should resume compression after it has made more room in the
 * output buffer.  Note that there are substantial restrictions on the use of
 * suspension --- see the documentation.
 *
 * When suspending, the compressor will back up to a convenient restart point
 * (typically the start of the current MCU). next_output_byte & free_in_buffer
 * indicate where the restart point will be if the current call returns FALSE.
 * Data beyond this point will be regenerated after resumption, so do not
 * write it out when emptying the buffer externally.
 */

METHODDEF(boolean)
empty_output_buffer (j_compress_ptr cinfo)
{
 my_dest_ptrf dest = (my_dest_ptrf) cinfo->dest;
 unsigned char * destbuff = dest->outfile->buff + dest->outfile->next_byte_to_write;
 memcpy(destbuff, dest->buffer, OUTPUT_BUF_SIZE);
 dest->outfile->next_byte_to_write += OUTPUT_BUF_SIZE;
   // ERREXIT(cinfo, JERR_FILE_WRITE);

  dest->pub.next_output_byte = dest->buffer;
  dest->pub.free_in_buffer = OUTPUT_BUF_SIZE;

  return TRUE;

}


/*
 * Terminate destination --- called by jpeg_finish_compress
 * after all data has been written.  Usually needs to flush buffer.
 *
 * NB: *not* called by jpeg_abort or jpeg_destroy; surrounding
 * application must deal with any cleanup that should happen even
 * for error exit.
 */

METHODDEF(void)
term_destination (j_compress_ptr cinfo)
{
  my_dest_ptrf dest = (my_dest_ptrf) cinfo->dest;
  size_t datacount = OUTPUT_BUF_SIZE - dest->pub.free_in_buffer;
 unsigned char * destbuff = dest->outfile->buff + dest->outfile->next_byte_to_write;
  /* Write any data remaining in the buffer */
  if (datacount > 0) {
    memcpy(destbuff, dest->buffer, datacount);
 dest->outfile->next_byte_to_write += datacount;
  }


  //fflush(dest->outfile);
  /* Make sure we wrote the output file OK */
  //if (ferror(dest->outfile))
  //  ERREXIT(cinfo, JERR_FILE_WRITE);


}


/*
 * Prepare for output to a stdio stream.
 * The caller must have already opened the stream, and is responsible
 * for closing it after finishing compression.
 */

GLOBAL(void)
jpeg_stdio_destf  (j_compress_ptr cinfo,  XXX_JPEG_FILE_BUFFER * outbuffer)
{

	my_dest_ptrf dest;
	if(outbuffer== NULL)
	{
		return ;
	}	
	if (cinfo->dest == NULL) { /* first time for this JPEG object? */
		cinfo->dest = (struct jpeg_destination_mgr *)
			(*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_PERMANENT,
			SIZEOF(my_destination_mgrf));
	}
	
	dest = (my_dest_ptrf) cinfo->dest;
	dest->pub.init_destination = init_destination;
	dest->pub.empty_output_buffer = empty_output_buffer;
	dest->pub.term_destination = term_destination;
	dest->outfile = outbuffer;
}
