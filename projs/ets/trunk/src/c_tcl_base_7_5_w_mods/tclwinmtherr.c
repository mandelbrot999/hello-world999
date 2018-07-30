/* $Header: svn://localhost/dtapublic/projs/ets/trunk/src/c_tcl_base_7_5_w_mods/tclwinmtherr.c 71 2016-11-05 11:07:06Z dashley $ */
/* 
 * tclWinMtherr.c --
 *
 *	This function provides a default implementation of the
 *	_matherr function for Borland C++.
 *
 * Copyright (c) 1995 Sun Microsystems, Inc.
 *
 * See the file "license.terms" for information on usage and redistribution
 * of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 *
 * RCS: @(#) $Id: tclwinmtherr.c,v 1.1.1.1 2001/06/13 04:49:20 dtashley Exp $
 */

#include "tclWinInt.h"
#include <math.h>


/*
 *----------------------------------------------------------------------
 *
 * _matherr --
 *
 *	This procedure is invoked by Borland C++ when certain
 *	errors occur in mathematical functions.  This procedure
 *	replaces the default implementation which generates pop-up
 *	warnings.
 *
 * Results:
 *	Returns 1 to indicate that we've handled the error
 *	locally.
 *
 * Side effects:
 *	Sets errno based on what's in xPtr.
 *
 *----------------------------------------------------------------------
 */

int
_matherr(xPtr)
    struct exception *xPtr;	/* Describes error that occurred. */
{
    if (!TclMathInProgress()) {
	return 0;
    }
    if ((xPtr->type == DOMAIN) || (xPtr->type == SING)) {
	errno = EDOM;
    } else {
	errno = ERANGE;
    }
    return 1;
}

/* End of tclwinmtherr.c */
