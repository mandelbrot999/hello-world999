//$Header: svn://localhost/dtapublic/projs/ets/trunk/src/c_tclxtens_7_5/vcinfo.c 71 2016-11-05 11:07:06Z dashley $
//-------------------------------------------------------------------------------------------------
//This file is part of "David T. Ashley's Shared Source Code", a set of shared components
//integrated into many of David T. Ashley's projects.
//-------------------------------------------------------------------------------------------------
//This source code and any program in which it is compiled/used is provided under the MIT License,
//reproduced below.
//-------------------------------------------------------------------------------------------------
//Permission is hereby granted, free of charge, to any person obtaining a copy of
//this software and associated documentation files(the "Software"), to deal in the
//Software without restriction, including without limitation the rights to use,
//copy, modify, merge, publish, distribute, sublicense, and / or sell copies of the
//Software, and to permit persons to whom the Software is furnished to do so,
//subject to the following conditions :
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.
//-------------------------------------------------------------------------------------------------
#define MODULE_VCINFO

#include <string.h>

#include "tcl.h"
#include "tcldecls.h"

#include "vcinfo.h"

#include "build_config.h"


//Module implements the "vcinfo" command, which emits all version
//control information about the build.

int VcinfoCmd(ClientData dummy, 
              Tcl_Interp *interp, 
	           int objc, 
	           Tcl_Obj *objv[]) 
   {
	Tcl_Obj *rv;

   //Break into cases based on the number of arguments.
   if ((objc == 2) && (!strcmp(Tcl_GetString(objv[1]), "-ijutoolsversion")))
      {
      //Create a string object, initialized to the version number.
      rv = Tcl_NewStringObj("v" BUILD_CONFIG_RELEASE_VERSION, -1);

      //We have a cleanly allocated object.  Return it to the caller.
      Tcl_SetObjResult(interp, rv);

      return(TCL_OK);
      }
   else
      {
      Tcl_WrongNumArgs(interp, 
                       1, 
                       objv, 
                       "-ijutoolsversion");

      return TCL_ERROR;
      }
   }


//Performs initial registration to the hash table.
//
void VcinfoInit(Tcl_Interp *interp)
{
   //Register a command named "credits".
   Tcl_CreateObjCommand(interp, 
	                    "vcinfo",
						(Tcl_ObjCmdProc *)VcinfoCmd,
						NULL,
						NULL);
}


const char *VcinfoCversion(void)
{   
    return ("$Header: svn://localhost/dtapublic/projs/ets/trunk/src/c_tclxtens_7_5/vcinfo.c 71 2016-11-05 11:07:06Z dashley $");
}


const char *VcinfoHversion(void)
{   
    return (VCINFO_H_VERSION);
}

/* End of vcinfo.c */
