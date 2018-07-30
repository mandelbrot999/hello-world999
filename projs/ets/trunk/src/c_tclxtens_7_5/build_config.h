//$Header: svn://localhost/dtapublic/projs/ets/trunk/src/c_tclxtens_7_5/build_config.h 71 2016-11-05 11:07:06Z dashley $
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
#ifndef BUILD_CONFIG_H_INCLUDED
   #define BUILD_CONFIG_H_INCLUDED

   #ifdef MODULE_BUILD_CONFIG
      #define DECMOD_BUILD_CONFIG
   #else
      #define DECMOD_BUILD_CONFIG extern
   #endif

   /* Define the version number of this release.
   ** This number appears throughout the build.
   */
   #define BUILD_CONFIG_RELEASE_VERSION "1.07.A0001"

   /* Year in which the software with version
   ** number above is released.
   */
   #define BUILD_CONFIG_RELEASE_YEAR "2003"

   /* Define what the static build of Wish is called.
   */
   #define BUILD_CONFIG_STATIC_WISH_ALIAS "EsrgConsole"

   /* Define what the static build of Tclsh is called.
   */
   #define BUILD_CONFIG_STATIC_TCLSH_ALIAS "EsrgScripter"

   /* Define the Tcl variable name where the product
   ** version is stored.
   */
   #define BUILD_CONFIG_PRODUCT_VERSION_VARIABLE "esrgtools_version"

   /* Define the Tcl variable where the product name
   ** is stored.
   */
   #define BUILD_CONFIG_PRODUCT_NAME_VARIABLE "esrgtools_product_name"

   /* String which contains the script executed to display
   ** the startup message on the console.
   */
   DECMOD_BUILD_CONFIG char *BUILD_CONFIG_StartupMessageScript;

   /* String containing lower part of HELP->ABOUT box contents.
   */
   DECMOD_BUILD_CONFIG const char *BUILD_CONFIG_HelpAboutMsgIdString;

   /* Function prototypes here.
   */
#endif

/* End of build_config.h */
