/* $Header: svn://localhost/dtapublic/projs/ets/trunk/src/c_tcl_base_7_5_w_mods/tclmain.h 71 2016-11-05 11:07:06Z dashley $ */

#ifndef TCLMAIN_H_INCLUDED
   #define TCLMAIN_H_INCLUDED

   #ifdef MODULE_TCLMAIN
      #define DECMOD_TCLMAIN
   #else
      #define DECMOD_TCLMAIN extern
   #endif

   DECMOD_TCLMAIN const char *TclMainCversion(void);
   DECMOD_TCLMAIN const char *TclMainHversion(void);

   #define TCLMAIN_H_VERSION ("$Header: svn://localhost/dtapublic/projs/ets/trunk/src/c_tcl_base_7_5_w_mods/tclmain.h 71 2016-11-05 11:07:06Z dashley $")
#endif

/* End of tcl_main.h */
