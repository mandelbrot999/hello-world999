/* $Header: svn://localhost/dtapublic/projs/ets/trunk/src/c_tcl_base_7_5_w_mods/tclport.h 71 2016-11-05 11:07:06Z dashley $ */
/*
 * tclPort.h --
 *
 *	This header file handles porting issues that occur because
 *	of differences between systems.  It reads in platform specific
 *	portability files.
 *
 * Copyright (c) 1994-1995 Sun Microsystems, Inc.
 *
 * See the file "license.terms" for information on usage and redistribution
 * of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 *
 * RCS: @(#) $Id: tclport.h,v 1.1.1.1 2001/06/13 04:45:05 dtashley Exp $
 */

#ifndef _TCLPORT
#define _TCLPORT

#include "tcl.h"

#if defined(__WIN32__)
#   include "tclWinPort.h"
#else
#   if defined(MAC_TCL)
#	include "tclMacPort.h"
#    else
#	include "../unix/tclUnixPort.h"
#    endif
#endif

#endif /* _TCLPORT */

/* End of tclport.h */
