/* $Header: svn://localhost/dtapublic/projs/ets/trunk/src/c_tk_base_7_5_w_mods/tkport.h 71 2016-11-05 11:07:06Z dashley $ */

/*
 * tkPort.h --
 *
 *	This header file handles porting issues that occur because of
 *	differences between systems.  It reads in platform specific
 *	portability files.
 *
 * Copyright (c) 1995 Sun Microsystems, Inc.
 *
 * See the file "license.terms" for information on usage and redistribution
 * of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 *
 * RCS: @(#) $Id: tkport.h,v 1.1.1.1 2001/06/13 05:07:19 dtashley Exp $
 */

#ifndef _TKPORT
#define _TKPORT

#ifndef _TK
#include "tk.h"
#endif
#ifndef _TCL
#include "tcl.h"
#endif

#if defined(__WIN32__) || defined(_WIN32)
#   include "tkWinPort.h"
#else
#   if defined(MAC_TCL)
#	include "tkMacPort.h"
#   else
#	include "../unix/tkUnixPort.h"
#   endif
#endif

#endif /* _TKPORT */

/* End of tkport.h */
