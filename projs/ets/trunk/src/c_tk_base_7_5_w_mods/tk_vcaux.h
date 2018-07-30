/* $Header: svn://localhost/dtapublic/projs/ets/trunk/src/c_tk_base_7_5_w_mods/tk_vcaux.h 71 2016-11-05 11:07:06Z dashley $ */

#ifndef TK_VCAUX_H_INCLUDED
   #define TK_VCAUX_H_INCLUDED

   #ifdef MODULE_TK_VCAUX
      #define DECMOD_TK_VCAUX
   #else
      #define DECMOD_TK_VCAUX extern
   #endif

   #define TK_VCAUX_H_VERSION ("$Revision: 1.1.1.1 $ $Modtime: 1/02/01 2:01a $ $Author: dtashley $")

   DECMOD_TK_VCAUX const char *ErrorBmpversion(void);
   DECMOD_TK_VCAUX const char *Gray12Bmpversion(void);
   DECMOD_TK_VCAUX const char *Gray25Bmpversion(void);
   DECMOD_TK_VCAUX const char *Gray50Bmpversion(void);
   DECMOD_TK_VCAUX const char *Gray75Bmpversion(void);
   DECMOD_TK_VCAUX const char *CursorfontHversion(void);
   DECMOD_TK_VCAUX const char *DefaultHversion(void);
   DECMOD_TK_VCAUX const char *Tk_VcAuxCversion(void);
   DECMOD_TK_VCAUX const char *Tk_VcAuxHversion(void);
#endif

/* End of tk_vcaux.h */
