//$Header: svn://localhost/dtapublic/projs/ets/trunk/src/c_tclxtens_7_5/msgstrs.h 71 2016-11-05 11:07:06Z dashley $
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
#ifndef MSGSTRS_H_INCLUDED
   #define MSGSTRS_H_INCLUDED

   #ifdef MODULE_MSGSTRS
      #define DECMOD_MSGSTRS
   #else
      #define DECMOD_MSGSTRS extern
   #endif

   DECMOD_MSGSTRS int MsgstrsGetStdSepLen(void);
   DECMOD_MSGSTRS const char *MsgstrsGetRefHlineEq(void);
   DECMOD_MSGSTRS const char *MsgstrsGetRefHlineHyphen(void);
   DECMOD_MSGSTRS void MsgstrsInit(void);
   DECMOD_MSGSTRS const char *MsgstrsGetstartupMsgStrings(int n);
   DECMOD_MSGSTRS const char *MsgstrsCversion(void);
   DECMOD_MSGSTRS const char *MsgstrsHversion(void);

   #define MSGSTRS_H_VERSION ("$Header: svn://localhost/dtapublic/projs/ets/trunk/src/c_tclxtens_7_5/msgstrs.h 71 2016-11-05 11:07:06Z dashley $")

#endif

/* End of msgstrs.h */
