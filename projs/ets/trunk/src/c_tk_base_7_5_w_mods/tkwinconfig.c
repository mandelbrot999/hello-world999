/* $Header: svn://localhost/dtapublic/projs/ets/trunk/src/c_tk_base_7_5_w_mods/tkwinconfig.c 71 2016-11-05 11:07:06Z dashley $ */

/* 
 * tkWinConfig.c --
 *
 *	This module implements the Windows system defaults for
 *	the configuration package.
 *
 * Copyright (c) 1997 by Sun Microsystems, Inc.
 *
 * See the file "license.terms" for information on usage and redistribution
 * of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 *
 * RCS: @(#) $Id: tkwinconfig.c,v 1.1.1.1 2001/06/13 05:12:03 dtashley Exp $
 */

#include "tk.h"
#include "tkInt.h"
#include "tkWinInt.h"


/*
 *----------------------------------------------------------------------
 *
 * TkpGetSystemDefault --
 *
 *	Given a dbName and className for a configuration option,
 *	return a string representation of the option.
 *
 * Results:
 *	Returns a Tk_Uid that is the string identifier that identifies
 *	this option. Returns NULL if there are no system defaults
 *	that match this pair.
 *
 * Side effects:
 *	None, once the package is initialized.
 *
 *----------------------------------------------------------------------
 */

Tcl_Obj *
TkpGetSystemDefault(
    Tk_Window tkwin,		/* A window to use. */
    char *dbName,		/* The option database name. */
    char *className)		/* The name of the option class. */
{
    Tcl_Obj *valueObjPtr;
    Tk_Uid classUid;

    if (tkwin == NULL) {
	return NULL;
    }

    valueObjPtr = NULL;
    classUid = Tk_Class(tkwin);

    if (strcmp(classUid, "Menu") == 0) {
	valueObjPtr = TkWinGetMenuSystemDefault(tkwin, dbName, className);
    }

    return valueObjPtr;
}

/* End of tkwinconfig.c */
