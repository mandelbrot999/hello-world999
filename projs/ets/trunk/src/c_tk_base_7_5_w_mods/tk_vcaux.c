/* $Header: svn://localhost/dtapublic/projs/ets/trunk/src/c_tk_base_7_5_w_mods/tk_vcaux.c 71 2016-11-05 11:07:06Z dashley $ */

#define MODULE_TK_VCAUX

#include "tk_vcaux.h"

#include "cursorfont.h"
#include "default.h"
#include "error.bmp"
#include "gray12.bmp"
#include "gray25.bmp"
#include "gray50.bmp"
#include "gray75.bmp"


const char *ErrorBmpversion(void)
   {   
   return (ERROR_BMP_VERSION);
   }


const char *Gray12Bmpversion(void)
   {   
   return (GRAY12_BMP_VERSION);
   }


const char *Gray25Bmpversion(void)
   {   
   return (GRAY25_BMP_VERSION);
   }


const char *Gray50Bmpversion(void)
   {   
   return (GRAY50_BMP_VERSION);
   }


const char *Gray75Bmpversion(void)
   {   
   return (GRAY75_BMP_VERSION);
   }


const char *CursorfontHversion(void)
   {   
   return (CURSORFONT_H_VERSION);
   }


const char *DefaultHversion(void)
   {   
   return (DEFAULT_H_VERSION);
   }


const char *Tk_VcAuxCversion(void)
   {
   return ("$Revision: 1.1.1.1 $ $Modtime: 1/02/01 2:01a $ $Author: dtashley $");
   }


const char *Tk_VcAuxHversion(void)
   {   
   return (TK_VCAUX_H_VERSION);
   }

/* End of tk_vcaux.c */
