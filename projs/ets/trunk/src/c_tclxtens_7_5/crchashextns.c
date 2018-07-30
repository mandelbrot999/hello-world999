//$Header: svn://localhost/dtapublic/projs/ets/trunk/src/c_tclxtens_7_5/crchashextns.c 71 2016-11-05 11:07:06Z dashley $
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
#define MODULE_CRCHASHEXTNS

#include <string.h>

#include "tcl.h"
#include "tcldecls.h"

#include "crchashextns.h"
#include "crchashfuncs.h"

#include "strfuncs.h"
#include "tclalloc.h"


//Procedure called when the "crc32" command is encountered in a Tcl script.
//
int CRCHASHEXTNS_Crc32extnCommand(ClientData dummy, 
                                  Tcl_Interp *interp, 
                                  int objc,
                                  Tcl_Obj *objv[]) 
   {
   Tcl_Obj *rv;
      //Value that will be returned.
   Tcl_Obj *block_obj;
      //Used for file reads.
   char buffer[11];
      //Space for "0x" followed by 8 hex chars and terminator.
   struct CRCHASHFUNCS_Crc32StateStruct crc_state;
      //CRC state structure, internals nominally known and accessible to another
      //another software module.
   unsigned long crc;
      //Calculated CRC.
   unsigned long bytearraysize;
      //Size of block allocated or portion used.
   char *bytearrayptr;
      //Pointer to array of bytes.
   char *fname;
      //File name specified.
   char *blockbuf;
      //Pointer to array of bytes.
   Tcl_Channel chan;
      //Channel opened using the Tcl libraries.
   int return_code, return_code_b;
      //Return codes from Tcl library functions.
   int loop_exit_flag;
      //Looping exit flag.
   int chars_read;
      //Number of characters read (i.e. for short read).
   int block_obj_n;


   if (objc < 2 || objc > 3)
      {
      Tcl_WrongNumArgs(interp, 
                       1, 
                       objv, 
                       "?-string? filename_or_string_value");

      return TCL_ERROR;
      }
   else if (objc == 2)
      {
      //Be sure that the internal crc table has been built.  This function
      //also returns a table correctness code.  Error out severely if the
      //CRC module believes its internal data has been corrupted.
      if (!CRCHASHFUNCS_Crc32TableCheck())
         {
         //Serious internal error.  Error out.

         //Create the return object.
         rv = Tcl_NewStringObj("CRCHASHEXTNS.C:  Serious internal error:  CRC-32 lookup table corrupted.", -1);

         //Set the return value to be the error message.
         Tcl_SetObjResult(interp, rv);

         //Error return.
         return TCL_ERROR;
         }

      //We need to open a channel, run it through the CRC algorithm, and
      //return results.

      //Get the string representation of the object.
      fname = Tcl_GetString(objv[1]);

      //Attempt to open a file channel.  The error information, if any,
      //will be placed in the interpreter's state.
      chan = Tcl_OpenFileChannel(interp, fname, "r", 0);

      //There is the possibility that the channel could not be opened
      //successfully.  If there was an error, error out.
      if (!chan)
         {
         //Create the return object.
         rv = Tcl_NewStringObj("crc32: Tcl_OpenFileChannel() failure on file name: ", -1);

         //Tack on the offensive argument.
         Tcl_AppendToObj(rv, fname, -1);

         //Set the return value to be the error message.
         Tcl_SetObjResult(interp, rv);

         //Error return.
         return TCL_ERROR;
         }

      //Try to set the channel encoding to binary and record the return code.
      return_code   = Tcl_SetChannelOption(interp, chan, "-encoding", "binary");

      //Try to set the channel translation mode to binary and record the return
      //code.
      if (return_code == TCL_OK)
         return_code_b = Tcl_SetChannelOption(interp, chan, "-translation", "binary");

      //If the attempt to set the channel encoding or translation 
      //didn't go well, error out.  Must also try to chose the channel because
      //it was successfully opened.
      if ((return_code != TCL_OK) || (return_code_b != TCL_OK))
         {
         //Try to close the channel.  "interp" not supplied so as not
         //to overwrite error info.
         Tcl_Close(NULL, chan);

         //Create the return object.
         rv = Tcl_NewStringObj("crc32: Tcl_SetChannelOption() failure.", -1);

         //Set the return value to be the error message.
         Tcl_SetObjResult(interp, rv);

         //Error return.
         return TCL_ERROR;
         }

      //Allocate the object to hold the block buffer.  I've examined the
      //function, and cannot do it with with a NULL pointer.  Must instead
      //allocate SOMETHING, although it will be destroyed immediately on
      //the first read.  This will have reference count zero.
      block_obj = Tcl_NewByteArrayObj("Trash", 5);

      //Calculate the CRC.  The essential process is to keep reading
      //and adding to the CRC until end of file.
      //Open and initialize the necessary structure.
      CRCHASHFUNCS_Crc32StateStructOpen(&crc_state);

      loop_exit_flag = 0;

      do
         {
         //Grab as many chars as possible, up to 65536 of them.
         //65536 was chosen because this is large enough for great
         //performance, but small enough that it won't make a significant
         //virtual memory impact.
         chars_read = Tcl_ReadChars(chan, block_obj, 65536, 0);

         //If the characters read shows as <0, this is an error
         //condition.  Trap.
         if (chars_read < 0)
            {
             //Try to close the channel.  "interp" not supplied so as not
            //to overwrite error info.
            Tcl_Close(NULL, chan);

            //Deallocate the buffer used to accept block file reads.  Because the
            //creation process set the reference count to zero, a single
            //decrement will destroy the object.
            Tcl_DecrRefCount(block_obj);

            //Create the return object.
            rv = Tcl_NewStringObj("crc32: Tcl_ReadChars() failure.", -1);

            //Set the return value to be the error message.
            Tcl_SetObjResult(interp, rv);

            //Error return.
            return TCL_ERROR;
            }

         //Obtain a pointer to the binary block that was read.
         blockbuf = Tcl_GetByteArrayFromObj(block_obj, &block_obj_n);

         //Add to the CRC for those chars read.  Skip the zero case.
         if (block_obj_n > 0)
            {
            CRCHASHFUNCS_Crc32StateStructAddData(&crc_state,
                                                 blockbuf,
                                                 block_obj_n);
            }

         //We want to exit if EOF is true.  A short read would
         //also be an indication, but short read should imply
         //EOF, so should not test both.
         return_code = Tcl_Eof(chan);
         loop_exit_flag = (return_code != 0);
         } while(!loop_exit_flag);

      //Extract the CRC.
      crc = CRCHASHFUNCS_Crc32Extract(&crc_state);

      //Postprocess the structure.
      CRCHASHFUNCS_Crc32StateStructClose(&crc_state);

      //Close the channel.
      return_code = Tcl_Close(interp, chan);

      //If there was an error closing the channel, error out.
      if (return_code != TCL_OK)
         {
         //Create the return object.
         rv = Tcl_NewStringObj("crc32: Tcl_Close() failure.", -1);

         //Set the return value to be the error message.
         Tcl_SetObjResult(interp, rv);

         //Error return.
         return TCL_ERROR;
         }

      //Deallocate the buffer used to accept block file reads.  Because the
      //creation process set the reference count to zero, a single
      //decrement will destroy the object.
      Tcl_DecrRefCount(block_obj);

      //Return the CRC to the caller.  No detectable errors
      //are possible at this point.

      //Convert the long integer to a hexadecimal representation.
      Strfuncs_UlToHexString(crc, buffer+2, 1);

      //Stuff the leading characters of the hexadecimal representation.
      buffer[0]  = '0';
      buffer[1]  = 'x';

      //Stuff the string terminator.
      buffer[10] =  0;

      //Create the return object.
      rv = Tcl_NewStringObj(buffer, -1);

      //Set the return value to be the hexadecimal representation of the
      //CRC.
      Tcl_SetObjResult(interp, rv);

      //Everything went well, return the OK code.
      return TCL_OK;
      }
   else /* if (objc == 3) */
      {
      //The second parameter positively must be "-string" or a substring
      //of that.  At present, there are no competing option flags, so 
      //a simple substring lookup will handle it.
      //Yank the string pointer.
      bytearrayptr = Tcl_GetString(objv[1]);

      //If not a substring, error out.
      if ((strlen(bytearrayptr)<2) || !Strfuncs_IsSubstring(bytearrayptr, "-string"))
         {
         //Create the return object.
         rv = Tcl_NewStringObj("crc32: Unrecognized switch: ", -1);

         //Tack on the offensive argument.
         Tcl_AppendToObj(rv, bytearrayptr, -1);

         //Set the return value to be the error message.
         Tcl_SetObjResult(interp, rv);

         //Error return.
         return TCL_ERROR;
         }

      //Convert the last parameter to its byte representation and get a
      //pointer to this representation and the length.  This was the 
      //library call that Ajuba recommended.
      bytearrayptr = Tcl_GetByteArrayFromObj(objv[2], &bytearraysize);

      //Be sure that the internal crc table has been built.  This function
      //also returns a table correctness code.  Error out severely if the
      //CRC module believes its internal data has been corrupted.
      if (!CRCHASHFUNCS_Crc32TableCheck())
         {
         //Serious internal error.  Error out.

         //Create the return object.
         rv = Tcl_NewStringObj("CRCHASHEXTNS.C:  Serious internal error:  CRC-32 lookup table corrupted.", -1);

         //Set the return value to be the error message.
         Tcl_SetObjResult(interp, rv);

         //Error return.
         return TCL_ERROR;
         }

      //Open and initialize the necessary structure.
      CRCHASHFUNCS_Crc32StateStructOpen(&crc_state);

      //Process the string.
      CRCHASHFUNCS_Crc32StateStructAddData(&crc_state,
                                          bytearrayptr,
                                          bytearraysize);
      //Extract the CRC.
      crc = CRCHASHFUNCS_Crc32Extract(&crc_state);

      //Postprocess the structure.
      CRCHASHFUNCS_Crc32StateStructClose(&crc_state);

      //Convert the long integer to a hexadecimal representation.
      Strfuncs_UlToHexString(crc, buffer+2, 1);

      //Stuff the leading characters of the hexadecimal representation.
      buffer[0]  = '0';
      buffer[1]  = 'x';

      //Stuff the string terminator.
      buffer[10] =  0;

      //Create the return object.
      rv = Tcl_NewStringObj(buffer, -1);

      //Set the return value to be the hexadecimal representation of the
      //CRC.
      Tcl_SetObjResult(interp, rv);

      //Everything went well, return the OK code.
      return TCL_OK;
      }
   }


//Performs initial registration to the hash table.
//
void CRCHASHEXTNS_Crc32extnInit(Tcl_Interp *interp)
   {
   //Register a command named "crc32".
   Tcl_CreateObjCommand(interp, 
                        "crc32",
                        (Tcl_ObjCmdProc *)CRCHASHEXTNS_Crc32extnCommand,
                        NULL,
                        NULL);
   }


//Returns version control string for file.
//
const char *CRCHASHEXTNS_cvcinfo(void)
{   
    return ("$Header: svn://localhost/dtapublic/projs/ets/trunk/src/c_tclxtens_7_5/crchashextns.c 71 2016-11-05 11:07:06Z dashley $");
}


//Returns version control string for associated .H file.
//
const char *CRCHASHEXTNS_hvcinfo(void)
{   
    return (CRCHASHEXTNS_H_VERSION);
}

//End of crchashextns.c.
