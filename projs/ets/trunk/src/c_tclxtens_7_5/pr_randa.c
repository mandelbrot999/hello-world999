//$Header: svn://localhost/dtapublic/projs/ets/trunk/src/c_tclxtens_7_5/pr_randa.c 71 2016-11-05 11:07:06Z dashley $
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
#define MODULE_PR_RANDA

#include "tcl.h"
#include "tcldecls.h"

#include "pr_randa.h"


/* Random seed used in this module.
*/
static unsigned long seed = 1578127215;


/* Returns the random successor of the argument.
** Uses the power residue method discussed
** in a probability book.  Is public so that other
** modules may use it.
*/
DECMOD_PR_RANDA unsigned long PrRandARandSucc(unsigned long arg)
   {
   __int64 k16807;
   __int64 input_arg;
   __int64 mul_result;
   __int64 return_value;
   __int64 M;

   k16807 = 16807;
   M = 2147483647;
   input_arg = arg;
   mul_result = k16807 * input_arg;
   return_value = mul_result % M;
   return((unsigned long)return_value);
   }


/* The command which requires the previous value to go on to
** the next.
*/
int PrRandA_rngPwrResRndA_cmd(ClientData dummy, 
                              Tcl_Interp *interp, 
	                           int objc, 
	                           Tcl_Obj *objv[]) 
   {
	int i;
      //Passed integer if one present.
	Tcl_Obj *rv;
      //Object to return.
   char *problem_arg;
      //String value of problem argument if we need to announce
      //it to caller.

   //We need to break this into three cases.  Either
   //there is one arg, which means use internal seed.
   //Or, there are two args, which means the predecessor
   //is supplied.  Or, there are more args, which means
   //error.
   if (objc == 1)
      {
      //Use internal seed.
      rv = Tcl_NewIntObj(seed);
      seed = PrRandARandSucc(seed);
      Tcl_SetObjResult(interp, rv);
      return(TCL_OK);
      }
   else if (objc == 2)
      {
      //Form successor of number passed.
      if (Tcl_GetIntFromObj(interp, objv[1], &i) != TCL_OK)
         {
         //We could not retrieve an integer from the passed argument.
         //We can't form the successor of a non-integer.
         //Error out.

         //Create the return object.
         rv = Tcl_NewStringObj("rngPwrResRndA: can't parse this argument as an integer: ", -1);

         //Tack on the offensive argument.
         problem_arg = Tcl_GetString(objv[1]);
         Tcl_AppendToObj(rv, problem_arg, -1);

         //Set the return value to be the error message.
         Tcl_SetObjResult(interp, rv);

         //Error return.
         return(TCL_ERROR);
         }

      rv = Tcl_NewIntObj(PrRandARandSucc(i));
      Tcl_SetObjResult(interp, rv);
      return(TCL_OK);
      }
   else //Wrong number of args.
      {
	   Tcl_WrongNumArgs(interp, 
                       1, 
                       objv, 
                       "?N?");
      return(TCL_ERROR);
      }
   }


//Performs initial registration to the hash table.
//
DECMOD_PR_RANDA void PrRandAInit(Tcl_Interp *interp)
   {
   Tcl_CreateObjCommand(interp, 
	                     "rngPwrResRndA",
                        (Tcl_ObjCmdProc *)PrRandA_rngPwrResRndA_cmd,
					         NULL,
					         NULL);
   }


DECMOD_PR_RANDA const char *PrRandACversion(void)
{   
    return ("$Header: svn://localhost/dtapublic/projs/ets/trunk/src/c_tclxtens_7_5/pr_randa.c 71 2016-11-05 11:07:06Z dashley $");
}


DECMOD_PR_RANDA const char *PrRandAHversion(void)
{   
    return (PR_RANDA_H_VERSION);
}

/* End of pr_randa.c */
