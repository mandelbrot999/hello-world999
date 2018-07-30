/* $Header: svn://localhost/dtapublic/projs/ets/trunk/src/c_tcl_base_7_5_w_mods/tclalloc.h 71 2016-11-05 11:07:06Z dashley $ */

#ifndef TCLALLOC_H_INCLUDED
   #define TCLALLOC_H_INCLUDED

   #ifdef MODULE_TCLALLOC
      #define DECMOD_TCLALLOC
   #else
      #define DECMOD_TCLALLOC extern
   #endif

   DECMOD_TCLALLOC char *TclpAlloc(unsigned int nbytes);
   DECMOD_TCLALLOC void TclpFree(char *cp);
   DECMOD_TCLALLOC char *TclpCalloc(size_t num, size_t size);
   DECMOD_TCLALLOC char *TclpRealloc(char *cp, unsigned int nbytes);
   DECMOD_TCLALLOC const char *TclpCversion(void);
   DECMOD_TCLALLOC const char *TclpHversion(void);

   #define TCLALLOC_H_VERSION ("$Header: svn://localhost/dtapublic/projs/ets/trunk/src/c_tcl_base_7_5_w_mods/tclalloc.h 71 2016-11-05 11:07:06Z dashley $")

#endif

/* End of tclalloc.h */
