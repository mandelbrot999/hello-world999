//----------------------------------------------------------------------------------------------------
//$Header: /home/dashley/cvsrep/e3ft_gpl01/e3ft_gpl01/dtaipubs/cron/2010/blackjack_201010/source/bjcceval/vcinfo.h,v 1.5 2012/03/30 00:20:15 dashley Exp $
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
#ifndef VCINFO_H_INCLUDED
#define VCINFO_H_INCLUDED

#ifdef MODULE_VCINFO
    #define DECMOD_VCINFO
#else
    #define DECMOD_VCINFO extern
#endif

typedef struct
{
    char sig[129];
} VCINFO_SIGNATURE;
//Type that holds a version control information signature.  An SHA-1 is 512 bits, or 128 hexadecimal digits.  129 characters are
//used to give space for a zero terminator.

DECMOD_VCINFO void VCINFO_signature( VCINFO_SIGNATURE *out_sig );

DECMOD_VCINFO const char *VCINFO_Vcinfo_C(void);
DECMOD_VCINFO const char *VCINFO_Vcinfo_H(void);

#define VCINFO_VCINFO_H  "$Revision: 1.5 $"

#endif

//----------------------------------------------------------------------------------------------------
//$Log: vcinfo.h,v $
//Revision 1.5  2012/03/30 00:20:15  dashley
//Edits.
//
//Revision 1.4  2012/03/29 23:44:01  dashley
//Edits.
//
//Revision 1.3  2012/03/28 23:58:42  dashley
//Edits.
//
//Revision 1.2  2012/03/15 23:38:08  dashley
//License text enhanced.
//
//Revision 1.1  2012/03/14 01:44:02  dashley
//Initial checkin.
//----------------------------------------------------------------------------------------------------
//End of $RCSfile: vcinfo.h,v $
//----------------------------------------------------------------------------------------------------
