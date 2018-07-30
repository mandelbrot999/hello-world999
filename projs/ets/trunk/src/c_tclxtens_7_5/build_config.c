//$Header: svn://localhost/dtapublic/projs/ets/trunk/src/c_tclxtens_7_5/build_config.c 71 2016-11-05 11:07:06Z dashley $
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
#define MODULE_BUILD_CONFIG

#include "build_config.h"

/* Statically embedded script to display opening message when
** tool starts up.
*/
char *BUILD_CONFIG_StartupMessageScript = 
   "puts stderr \"% ------------------------------------------------------------------------\"\n"
   "puts stderr \"% $" BUILD_CONFIG_PRODUCT_NAME_VARIABLE 
      ", v$" 
      BUILD_CONFIG_PRODUCT_VERSION_VARIABLE 
      ", "
	  BUILD_CONFIG_RELEASE_YEAR ".  This is an open-source script inter-\"\n"
   "puts stderr \"% preter tailored for embedded product software builds, based on Tcl/Tk\"\n"
   "puts stderr \"% 8.3.1 originally from Scriptics (www.scriptics.com), plus generous\"\n"
   "puts stderr \"% contributions of ideas, software, software components, and documentation\"\n"
   "puts stderr \"% from many others.  For a full list of contributors and contact infor-\"\n"
   "puts stderr \"% mation, type \\\"credits\\\", or type \\\"exit\\\" to end.  This product is licensed\"\n"
   "puts stderr \"% under the GNU Public License (GPL), and this product and its source code\"\n"
   "puts stderr \"% can be downloaded without cost from http://ijutools.sourceforge.net.\"\n"
   "puts stderr \"% ------------------------------------------------------------------------\"\n"
;


/* Standard identification string for message boxes displayed in
** response to HELP->ABOUT.  This part of the identification string
** is the long paragraph after the specific component identification.
*/
const char *BUILD_CONFIG_HelpAboutMsgIdString =
   "This program is a component of The ESRG Tool Set, Version " BUILD_CONFIG_RELEASE_VERSION ".      \n"
   "This tool set is free software distributed under the GNU GPL.  This\n"
   "tool set, any of its components, and its source code may be\n"
   "distributed without restriction provided that no fee is charged and\n"
   "no changes are made without also changing program titles and\n"
   "identification strings so as to prevent confusion with official\n"
   "releases of The ESRG Tool Set.  Please see the license (included\n"
   "with the tool set) for all details.\n"
   "\n"
   "Please send any bug reports or suggestions for ehnacements to\n"
   "toolbugs@esrg.org.  Note that there are no plans to support Unicode,\n"
   "because not all Windows flavors support it, and the increased tool\n"
   "complexity is not justified by the benefit.";

/* End of build_config.c */
