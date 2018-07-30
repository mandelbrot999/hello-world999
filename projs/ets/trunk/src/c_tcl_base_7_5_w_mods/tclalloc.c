/* $Header: svn://localhost/dtapublic/projs/ets/trunk/src/c_tcl_base_7_5_w_mods/tclalloc.c 71 2016-11-05 11:07:06Z dashley $ */

#define MODULE_TCLALLOC

#include <malloc.h>

#include "tclalloc.h"


 /*
 *----------------------------------------------------------------------
 *
 * TclpAlloc --
 *
 *	Allocate more memory.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	None.
 *
 *----------------------------------------------------------------------
 */

char *TclpAlloc(unsigned int nbytes)
{
    return (char*) malloc(nbytes);
}


/*
 *----------------------------------------------------------------------
 *
 * TclpFree --
 *
 *	Free memory.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	None.
 *
 *----------------------------------------------------------------------
 */

void TclpFree(char *cp)
{   
    free(cp);
    return;
}


 /*
 *----------------------------------------------------------------------
 *
 * TclpCalloc --
 *
 *	Allocate array of memory.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	None.
 *
 *----------------------------------------------------------------------
 */

char *TclpCalloc(size_t num, size_t size)
{
    return (char*) calloc(num, size);
}


/*
 *----------------------------------------------------------------------
 *
 * TclpRealloc --
 *
 *	Reallocate memory.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	None.
 *
 *----------------------------------------------------------------------
 */

char *TclpRealloc(char *cp, unsigned int nbytes)
{   
    return (char*) realloc(cp, nbytes);
}


/*
 *----------------------------------------------------------------------
 *
 * TclpCversion --
 *
 *	Returns the PVCS version control string for the .C file.  
 *  This is a constant string and may not be modified.
 *
 * Side effects:
 *	None.
 *
 *----------------------------------------------------------------------
 */

const char *TclpCversion(void)
{   
    return ("$Header: svn://localhost/dtapublic/projs/ets/trunk/src/c_tcl_base_7_5_w_mods/tclalloc.c 71 2016-11-05 11:07:06Z dashley $");
}


/*
 *----------------------------------------------------------------------
 *
 * TclpHversion --
 *
 *	Returns the PVCS version control string for the .H file.  
 *  This is a constant string and may not be modified.
 *
 * Side effects:
 *	None.
 *
 *----------------------------------------------------------------------
 */

const char *TclpHversion(void)
{   
    return (TCLALLOC_H_VERSION);
}


/*
 * $Log: tclalloc.c,v $
 * Revision 1.4  2001/07/15 06:44:32  dtashley
 * Keyword expansion mistake corrected.
 *
 * Revision 1.3  2001/07/15 06:40:10  dtashley
 * Adaptation of GNU arbitrary-size integer package integrated into IjuScripter
 * and IjuConsole.
 *
 * Revision 1.2  2001/07/15 06:07:15  dtashley
 * Moved out of binary mode, preparing for use with CVS.
 */
/* $History: tclalloc.c $
 * 
 * *****************  Version 1  *****************
 * User: Dtashley     Date: 1/02/01    Time: 12:16a
 * Created in $/IjuScripter, IjuConsole/Source/Tcl Base
 * Initial check-in.
 */

/*************************************************************************/
/* Original copyright notice below.   This must be retained in the       */
/* source code.                                                          */
/*************************************************************************/

/* 
 * tclAlloc.c --
 *
 *	This is a very fast storage allocator.  It allocates blocks of a
 *	small number of different sizes, and keeps free lists of each size.
 *	Blocks that don't exactly fit are passed up to the next larger size.
 *	Blocks over a certain size are directly allocated from the system.
 *
 * Copyright (c) 1983 Regents of the University of California.
 * Copyright (c) 1996-1997 Sun Microsystems, Inc.
 * Copyright (c) 1998-1999 by Scriptics Corporation.
 *
 * Portions contributed by Chris Kingsley, Jack Jansen and Ray Johnson.
 *
 * See the file "license.terms" for information on usage and redistribution
 * of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 *
 * RCS: @(#) $Id: tclalloc.c,v 1.4 2001/07/15 06:44:32 dtashley Exp $
 */

/* End of tclalloc.c */
