/* $Header: svn://localhost/dtapublic/projs/ets/trunk/src/c_tk_base_7_5_w_mods/default.h 71 2016-11-05 11:07:06Z dashley $ */

/*
 * default.h --
 *
 *	This file defines the defaults for all options for all of
 *	the Tk widgets.
 *
 * Copyright (c) 1991-1994 The Regents of the University of California.
 * Copyright (c) 1994 Sun Microsystems, Inc.
 *
 * See the file "license.terms" for information on usage and redistribution
 * of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 *
 * RCS: @(#) $Id: default.h,v 1.1.1.1 2001/06/13 04:52:35 dtashley Exp $
 */

#ifndef MODULE_TK_VCAUX

#ifndef _DEFAULT
#define _DEFAULT

#if defined(__WIN32__) || defined(_WIN32)
#   include "tkWinDefault.h"
#else
#   if defined(MAC_TCL)
#	include "tkMacDefault.h"
#   else
#	include "tkUnixDefault.h"
#   endif
#endif

#endif /* _DEFAULT */

#else
   #define DEFAULT_H_VERSION ("$Revision: 1.1.1.1 $ $Modtime: 1/02/01 2:17a $ $Author: dtashley $")
#endif

/* End of default.h */
