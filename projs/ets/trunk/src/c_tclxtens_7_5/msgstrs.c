//$Header: svn://localhost/dtapublic/projs/ets/trunk/src/c_tclxtens_7_5/msgstrs.c 71 2016-11-05 11:07:06Z dashley $
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
#define MODULE_MSGSTRS

#include "tcl.h"
#include "tcldecls.h"

#include "msgstrs.h"

#include <string.h>

#include "vcinfo.h"


//PP constant defining reference baseline with = signs.
#define MSGSTRS_REFHLINEEQ   \
   "============================================================================"

//Reference baseline with = signs.
static const char * MsgstrsRefHlineEq = MSGSTRS_REFHLINEEQ;

#define MSGSTRS_REFLINEHYPHEN  \
   "----------------------------------------------------------------------------"

//Reference baseline populated with hyphens.
static const char *  MsgstrsRefHlineHyphen = MSGSTRS_REFLINEHYPHEN;

#define MSGSTRS_CORPCOPYRIGHTSTRING  \
   "Copyright David T. Ashley, Detroit, Michigan, USA."

//Copyright string.
static const char *MsgstrsCopyrightString = MSGSTRS_CORPCOPYRIGHTSTRING;

//Credits string, giving credit to who produced it.
#define MSGSTRS_CREDITSSTRING_A  \
   "Powered by static embedded Ajuba/Scriptics Tcl 8.3.1"

//Instruction strings.
#define MSGSTRS_INSTRUCTSTRING_A  \
   "Type \"credits\" for credit and contact information; or \"exit\" to end session."


//Returns the length of the standard separator line.  This is taken
//to be the right length for all horizontal lines.

DECMOD_MSGSTRS int MsgstrsGetStdSepLen(void)
{
	return(strlen(MsgstrsRefHlineEq));
}

//Returns the standard horizontal line populated with "=".

DECMOD_MSGSTRS const char *MsgstrsGetRefHlineEq(void)
{
	return(MsgstrsRefHlineEq);
}

//Returns the standard horizontal line populated with "-".

DECMOD_MSGSTRS const char *MsgstrsGetRefHlineHyphen(void)
{
	return(MsgstrsRefHlineHyphen);
}


//Initializes this software module.  The only function to perform is to 
//calculate the CRC-32 of all available version control information and
//stuff it in the string which will be used for the opening message.
DECMOD_MSGSTRS void MsgstrsInit(void)
   {
#if 0
   Tcl_Obj *objptr;
   char *srcptr;
   char *dstptr;
   int i;
   int errflag;
#endif

#if 0
   //First, form the CRC-32 of all available version control information.
   //Get a Tcl object with this information.
   objptr = VcinfoRetrieveVcData(0,NULL,&errflag);

   //If there was an error generating the CRC, don't want to go any
   //further.  Free the returned object.
   if (errflag)
      goto free_obj_exit;

   //Get a pointer to the string represented by the object.
   srcptr = Tcl_GetString(objptr);

   //Go two forward in the string to bypass the "0x".
   if (srcptr)
      {
      if (strlen(srcptr) >= 2)
         {
         srcptr += 2;
         }
      }

   //Loop through the list of opening message strings and substitute
   //in the correct information wherever the string 00000000 is found.
   //It is assumed that there will be only one such occurance in the
   //set of opening strings.  If the strstr() function indicates a match,
   //it is known that there is enough room in the destination to copy
   //in the string, otherwise there would not have been a match.
   if (srcptr)
      {
      for (i=0; i<(sizeof(MsgstrsStartupMsg)/sizeof(MsgstrsStartupMsg[0])); i++)
         {
         if (MsgstrsStartupMsg[i])
            {
            dstptr = strstr(MsgstrsStartupMsg[i], "00000000");
/*
            if (dstptr)
               {
               while (*srcptr && *dstptr)
                  {
                  *dstptr++ = *srcptr++;
                  }
               
               break;
               }
*/
            }
         }
      }

   free_obj_exit:

   //We are done with the Tcl object.  We can free it.
   Tcl_DecrRefCount(objptr);
#endif
   }

/* End of msgstrs.c */
