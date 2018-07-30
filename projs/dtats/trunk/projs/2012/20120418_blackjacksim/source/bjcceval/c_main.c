//----------------------------------------------------------------------------------------------------
//$Header: /home/dashley/cvsrep/e3ft_gpl01/e3ft_gpl01/dtaipubs/cron/2010/blackjack_201010/source/bjcceval/c_main.c,v 1.8 2012/04/15 12:57:08 dashley Exp $
//----------------------------------------------------------------------------------------------------
//Copyright (C) 2012, David T. Ashley.
//
//This file is part of BJCCEVAL, a program that evaluates by simulation
//the best basic strategy, card-counting, and other playing strategies
//for several variants of the game of Blackjack.
//
//BJCCEVAL is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//BJCCEVAL is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program.  If not, see <http://www.gnu.org/licenses/>.
//(A copy of the GNU General Public License, Version 3 is provided in
//the file "COPYING" distributed with BJCCEVAL.)
//
//David T. Ashley can be contacted at DASHLEY@GMAIL.COM and/or at
//P.O. Box 918, Marshall MI 49068.
//----------------------------------------------------------------------------------------------------
//This file contains the actual "main" function, which is called c_main().  The c_main() function in
//this file can be called from from two different files, depending on the operating system for which
//this program is being built.
//
//   a)In the case of a Microsoft Visual Studio 2010 project (which builds a program for Windows),
//     the wrapper function is contained in the file "bjcceval.cpp".
//
//   b)In the case of a Unix/Linux/Cygwin program, the wrapper function is contained in main.c.
//
//There is no attempt to internationalize this program--it is designed for standard ASCII characters
//only.
//----------------------------------------------------------------------------------------------------
#define MODULE_C_MAIN

#include <stdio.h>

#include "c_main.h"
#include "random.h"
#include "vcinfo.h"


void C_MAIN_EmitVersionNumber(void)
{



   // main2();

//    VCINFO_SIGNATURE sig;

//    VCINFO_signature( &sig );

//    printf("%s\n", sig.sig);
}


int c_main(int argc, char* argv[])
{
    int rv;
 
    rv = 0;

    printf("Execution begins.\n");

    
    printf("Execution ends.\n");

    //C_MAIN_EmitVersionNumber();

    return(rv);
}


const char * C_MAIN_Vcinfo_H(void)
{
    return(C_MAIN_VCINFO_H);
}


const char * C_MAIN_Vcinfo_C(void)
{
    return("$Revision: 1.8 $");
}


//----------------------------------------------------------------------------------------------------
//$Log: c_main.c,v $
//Revision 1.8  2012/04/15 12:57:08  dashley
//Unit testing performed.
//
//Revision 1.7  2012/04/12 01:51:57  dashley
//Edits.
//
//Revision 1.6  2012/04/11 03:31:51  dashley
//Edits.
//
//Revision 1.5  2012/04/11 00:52:21  dashley
//Edits.
//
//Revision 1.4  2012/03/29 23:44:00  dashley
//Edits.
//
//Revision 1.3  2012/03/29 00:42:06  dashley
//Edits.
//
//Revision 1.2  2012/03/26 02:17:49  dashley
//Edits.
//
//Revision 1.1  2012/03/26 02:12:04  dashley
//Inital checkin.
//----------------------------------------------------------------------------------------------------
//End of $RCSfile: c_main.c,v $
//----------------------------------------------------------------------------------------------------
