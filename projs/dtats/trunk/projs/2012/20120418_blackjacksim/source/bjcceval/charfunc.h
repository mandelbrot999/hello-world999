//----------------------------------------------------------------------------------------------------
//$Header: /home/dashley/cvsrep/e3ft_gpl01/e3ft_gpl01/dtaipubs/cron/2010/blackjack_201010/source/bjcceval/charfunc.h,v 1.7 2012/03/30 00:58:36 dashley Exp $
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
#ifndef CHARFUNC_H_INCLUDED
#define CHARFUNC_H_INCLUDED

#ifdef MODULE_CHARFUNC
    #define DECMOD_CHARFUNC
#else
    #define DECMOD_CHARFUNC extern
#endif

#include <stdlib.h>

//Character classification functions --------------------------
//
//!=0 if digit, 0 otherwise.
DECMOD_CHARFUNC int CHARFUNC_is_digit(char c);
//
//!=0 if lower-case letter, 0 otherwise.
DECMOD_CHARFUNC int CHARFUNC_is_letter_lc(char c);
//
//!=0 if upper-case letter, 0 otherwise.
DECMOD_CHARFUNC int CHARFUNC_is_letter_uc(char c);
//
//!=0 if whitespace, 0 otherwise.  Whitespace is defined as space,
//tab, or newline.
DECMOD_CHARFUNC int CHARFUNC_is_whitespace(char c);

//Hexadecimal arithmetic/presentation functions --------------------------
//
//Returns the value of a digit (0-9), or -1 if the
//passed character is not a digit.
DECMOD_CHARFUNC int CHARFUNC_digit_to_val(char digit);

//Returns a lower-case character corresponding to the 
//lowest nibble of the argument.
DECMOD_CHARFUNC char CHARFUNC_nibble_to_lc_hex_digit(int nibble);

//Converts a passed integer to 8 hex digits, lower case letters,
//in reverse order (LSB first), with no terminator.  s may not
//be null, and caller must provide space for s[0] through s[7].
//s[8] is not necessary (no terminator is appended.
DECMOD_CHARFUNC void CHARFUNC_int_to_lc_hex_rev(int arg, char *s);

//Character case conversion functions --------------------------
//
//If the character is a lower-case letter, converts it to an upper-case
//letter.  All other characters are passed through unchanged.
DECMOD_CHARFUNC char CHARFUNC_to_upper(char c);

//If the character is an upper-case letter, converts it to a lower-case
//letter.  All other characters are passed through unchanged.
DECMOD_CHARFUNC char CHARFUNC_to_lower(char c);

//Returns lower-case letter corresponding to integer [0..25].  If out of 
//range returns '?'.
DECMOD_CHARFUNC char CHARFUNC_int_to_lower(int arg);

DECMOD_CHARFUNC const char *CHARFUNC_Vcinfo_C(void);
DECMOD_CHARFUNC const char *CHARFUNC_Vcinfo_H(void);

#define CHARFUNC_VCINFO_H  "$Revision: 1.7 $"

#endif

//----------------------------------------------------------------------------------------------------
//$Log: charfunc.h,v $
//Revision 1.7  2012/03/30 00:58:36  dashley
//Edits.
//
//Revision 1.6  2012/03/30 00:20:14  dashley
//Edits.
//
//Revision 1.5  2012/03/29 23:44:00  dashley
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
//Revision 1.1  2012/03/12 02:54:25  dashley
//Initial checkin.
//----------------------------------------------------------------------------------------------------
//End of $RCSfile: charfunc.h,v $
//----------------------------------------------------------------------------------------------------
