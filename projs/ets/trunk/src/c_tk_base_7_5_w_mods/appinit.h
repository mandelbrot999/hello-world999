/* $Header: svn://localhost/dtapublic/projs/ets/trunk/src/c_tk_base_7_5_w_mods/appinit.h 71 2016-11-05 11:07:06Z dashley $ */

/* Automatically generated code */
/* DO NOT EDIT */

#define ET_TCL_LIBRARY "C:/PROGRAM FILES/TCL/lib/tcl8.3"
#define ET_TK_LIBRARY "C:/PROGRAM FILES/TCL/lib/tk8.3"

#ifndef MODULE_APPINIT
   #ifndef ET_TCLARGS
   #include <tcl.h>
   #ifdef __cplusplus
   # define ET_EXTERN extern "C"
   #else
   # define ET_EXTERN extern
   #endif
   ET_EXTERN int Et_Local_Init(int argc, char **argv);
   ET_EXTERN int Et_DoInit(Tcl_Interp *interp);
   ET_EXTERN char *mprintf(const char*,...);
   ET_EXTERN char *vmprintf(const char*,...);
   ET_EXTERN int Et_EvalF(Tcl_Interp*,const char *,...);
   ET_EXTERN int Et_GlobalEvalF(Tcl_Interp*,const char *,...);
   ET_EXTERN int Et_DStringAppendF(Tcl_DString*,const char*,...);
   ET_EXTERN int Et_ResultF(Tcl_Interp*,const char*,...);
   ET_EXTERN int Et_Init(int,char**);
   ET_EXTERN Tcl_Interp *Et_Interp;
   #if TCL_RELEASE_VERSION>=8
   ET_EXTERN int Et_AppendObjF(Tcl_Obj*,const char*,...);
   #endif
   #define ET_TCLARGS ClientData clientData,Tcl_Interp*interp,int argc,char**argv
   #define ET_OBJARGS ClientData clientData,Tcl_Interp*interp,int objc,Tcl_Obj *CONST objv[]
   #endif
#endif

/* End of appinit.h */
