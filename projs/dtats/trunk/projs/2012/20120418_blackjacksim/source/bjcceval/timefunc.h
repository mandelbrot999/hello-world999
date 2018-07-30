//----------------------------------------------------------------------------------------------------
//$Header: /home/dashley/cvsrep/e3ft_gpl01/e3ft_gpl01/dtaipubs/cron/2010/blackjack_201010/source/bjcceval/timefunc.h,v 1.2 2012/03/30 01:05:31 dashley Exp $
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
#ifndef TIMEFUNC_H_INCLUDED
#define TIMEFUNC_H_INCLUDED

#include <stdio.h>

#ifdef MODULE_TIMEFUNC
    #define DECMOD_TIMEFUNC
#else
    #define DECMOD_TIMEFUNC extern
#endif

//Guaranteed to be long enough for longest result from any function that specifies
//this as a return value.
typedef struct
{
    char result[35];   //Zero terminated by any function that specifies it as output.
} TIMEFUNC_TIME_ASCII_RESULT;

DECMOD_TIMEFUNC void TIMEFUNC_to_ascii_logstamp(const struct __timeb64 *in_arg, TIMEFUNC_TIME_ASCII_RESULT *out_arg);
DECMOD_TIMEFUNC void TIMEFUNC_to_ascii_hr_form(const struct __timeb64 *in_arg, TIMEFUNC_TIME_ASCII_RESULT *out_arg);
DECMOD_TIMEFUNC void TIMEFUNC_to_ascii_filename_base(const struct __timeb64 *in_arg, TIMEFUNC_TIME_ASCII_RESULT *out_arg);

DECMOD_TIMEFUNC const char *TIMEFUNC_Vcinfo_C(void);
DECMOD_TIMEFUNC const char *TIMEFUNC_Vcinfo_H(void);

#define TIMEFUNC_VCINFO_H  "$Revision: 1.2 $"

#endif

//----------------------------------------------------------------------------------------------------
//$Log: timefunc.h,v $
//Revision 1.2  2012/03/30 01:05:31  dashley
//Edits.
//
//Revision 1.1  2012/03/30 00:59:16  dashley
//Initial checkin.
//----------------------------------------------------------------------------------------------------
//End of $RCSfile: timefunc.h,v $
//----------------------------------------------------------------------------------------------------
