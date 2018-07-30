//----------------------------------------------------------------------------------------------------
//$Header: /home/dashley/cvsrep/e3ft_gpl01/e3ft_gpl01/dtaipubs/cron/2010/blackjack_201010/source/bjcceval/vcinfo.c,v 1.8 2012/04/11 03:31:51 dashley Exp $
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
#define MODULE_VCINFO

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "c_main.h"
#include "cassert.h"
#include "charfunc.h"
#include "fatal.h"
#include "memops.h"
#include "mt19937.h"
#include "random.h"
#include "sha512.h"
#include "stdformat.h"
#include "timefunc.h"
#include "vcinfo.h"


#ifdef P_CASSERT   //If assertions enabled, use slightly different salt.
    #define VCINFO_SALT ("a;dhklhewheifgwobviifweio9182634896123461238934938lsgdfoiasiofdaiosgfihasvdhf314159271983274"  __DATE__  __TIME__)
#else
    #define VCINFO_SALT ("a;dhklhewheifgwobviifweio9182634896123461238934938lsgdfoiasiofdaiosgfihasvdhf314159271983274"  __DATE__  __TIME__  "beavisandbutthead-startrek-csilasvegas")
#endif
//The above strings are to add more juice to the SHA1.  The date and time ensure compile uniqueness so that any released
//executable can be verified to be the same or different than any other released executable.  There is no logic to the
//strings (and no logic should be necessary given the nature of a cryptographic hash function).  These are just semi-random
//characters typed on the keyboard.


//Table of all the functions that can be called to get version control information.
const char *((*vcfptrs[])(void)) = 
{
    C_MAIN_Vcinfo_C,
    C_MAIN_Vcinfo_H,
    CASSERT_Vcinfo_C,
    CASSERT_Vcinfo_H,
    CHARFUNC_Vcinfo_C,
    CHARFUNC_Vcinfo_H,
    FATAL_Vcinfo_C,
    FATAL_Vcinfo_H,
    MEMOPS_Vcinfo_C,
    MEMOPS_Vcinfo_H,
    MT19937_Vcinfo_C,
    MT19937_Vcinfo_H,
    RANDOM_Vcinfo_C,
    RANDOM_Vcinfo_H,
    SHA512_Vcinfo_C,
    SHA512_Vcinfo_H,
    STDFORMAT_Vcinfo_C,
    STDFORMAT_Vcinfo_H,
    TIMEFUNC_Vcinfo_C,
    TIMEFUNC_Vcinfo_H,
    VCINFO_Vcinfo_C,
    VCINFO_Vcinfo_H,
};


void VCINFO_signature( VCINFO_SIGNATURE *out_sig )
{
    unsigned i;
    char *temp;
    struct SHA512_Sha512StateStruct sha512calcstate;
    struct SHA512_Sha512ResultStruct sha512result;

    SHA512_Sha512StateStructOpen(&sha512calcstate);

    for (i=0; i<(sizeof(vcfptrs)/sizeof(vcfptrs[0])); i++)
    {
        SHA512_Sha512StateStructAddData(&sha512calcstate,
                                        VCINFO_SALT,
                                        strlen(VCINFO_SALT));

        temp = (char *)((*(vcfptrs[i]))());
        //printf("\n%s\n", temp);
        SHA512_Sha512StateStructAddData(&sha512calcstate,
                                        temp,
                                        strlen(temp));
    }

    //Final salt.
    SHA512_Sha512StateStructAddData(&sha512calcstate,
                                    VCINFO_SALT,
                                    strlen(VCINFO_SALT));

    SHA512_Sha512StateStructClose(&sha512calcstate,
                                  &sha512result);

    strcpy_s(out_sig->sig, sizeof(out_sig->sig), sha512result.sha512_chars);
}


const char *VCINFO_Vcinfo_C(void)
{
    return("$Revision: 1.8 $");
}


const char *VCINFO_Vcinfo_H(void)
{
    return(VCINFO_VCINFO_H);
}


//----------------------------------------------------------------------------------------------------
//$Log: vcinfo.c,v $
//Revision 1.8  2012/04/11 03:31:51  dashley
//Edits.
//
//Revision 1.7  2012/03/30 00:58:36  dashley
//Edits.
//
//Revision 1.6  2012/03/30 00:20:15  dashley
//Edits.
//
//Revision 1.5  2012/03/29 23:44:01  dashley
//Edits.
//
//Revision 1.4  2012/03/29 00:42:06  dashley
//Edits.
//
//Revision 1.3  2012/03/28 23:58:42  dashley
//Edits.
//
//Revision 1.2  2012/03/15 23:38:08  dashley
//License text enhanced.
//
//Revision 1.1  2012/03/14 01:44:01  dashley
//Initial checkin.
//----------------------------------------------------------------------------------------------------
//End of $RCSfile: vcinfo.c,v $
//----------------------------------------------------------------------------------------------------
