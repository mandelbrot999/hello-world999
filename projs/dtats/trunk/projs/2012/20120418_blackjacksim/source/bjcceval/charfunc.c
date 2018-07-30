//----------------------------------------------------------------------------------------------------
//$Header: /home/dashley/cvsrep/e3ft_gpl01/e3ft_gpl01/dtaipubs/cron/2010/blackjack_201010/source/bjcceval/charfunc.c,v 1.6 2012/03/30 00:58:36 dashley Exp $
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
#define MODULE_CHARFUNC

#include <string.h>

#include "cassert.h"
#include "charfunc.h"


int CHARFUNC_is_digit(char c)
{
    switch (c)
    {
    case '0':  return(1);
        break;
    case '1':  return(1);
        break;
    case '2':  return(1);
        break;
    case '3':  return(1);
        break;
    case '4':  return(1);
        break;
    case '5':  return(1);
        break;
    case '6':  return(1);
        break;
    case '7':  return(1);
        break;
    case '8':  return(1);
        break;
    case '9':  return(1);
        break;
    default:   return(0);
        break;
    }
}


int CHARFUNC_is_letter_lc(char c)
{
    switch (c)
    {
    case 'a':
        return(1);
        break;
    case 'b':
        return(1);
        break;
    case 'c':
        return(1);
        break;
    case 'd':
        return(1);
        break;
    case 'e':
        return(1);
        break;
    case 'f':
        return(1);
        break;
    case 'g':
        return(1);
        break;
    case 'h':
        return(1);
        break;
    case 'i':
        return(1);
        break;
    case 'j':
        return(1);
        break;
    case 'k':
        return(1);
        break;
    case 'l':
        return(1);
        break;
    case 'm':
        return(1);
        break;
    case 'n':
        return(1);
        break;
    case 'o':
        return(1);
        break;
    case 'p':
        return(1);
        break;
    case 'q':
        return(1);
        break;
    case 'r':
        return(1);
        break;
    case 's':
        return(1);
        break;
    case 't':
        return(1);
        break;
    case 'u':
        return(1);
        break;
    case 'v':
        return(1);
        break;
    case 'w':
        return(1);
        break;
    case 'x':
        return(1);
        break;
    case 'y':
        return(1);
        break;
    case 'z':
        return(1);
        break;
    default:
        return(0);
        break;
    }
}


int CHARFUNC_is_letter_uc(char c)
{
    switch (c)
    {
    case 'A':
        return(1);
        break;
    case 'B':
        return(1);
        break;
    case 'C':
        return(1);
        break;
    case 'D':
        return(1);
        break;
    case 'E':
        return(1);
        break;
    case 'F':
        return(1);
        break;
    case 'G':
        return(1);
        break;
    case 'H':
        return(1);
        break;
    case 'I':
        return(1);
        break;
    case 'J':
        return(1);
        break;
    case 'K':
        return(1);
        break;
    case 'L':
        return(1);
        break;
    case 'M':
        return(1);
        break;
    case 'N':
        return(1);
        break;
    case 'O':
        return(1);
        break;
    case 'P':
        return(1);
        break;
    case 'Q':
        return(1);
        break;
    case 'R':
        return(1);
        break;
    case 'S':
        return(1);
        break;
    case 'T':
        return(1);
        break;
    case 'U':
        return(1);
        break;
    case 'V':
        return(1);
        break;
    case 'W':
        return(1);
        break;
    case 'X':
        return(1);
        break;
    case 'Y':
        return(1);
        break;
    case 'Z':
        return(1);
        break;
    default:
        return(0);
        break;
    }
}


int CHARFUNC_is_whitespace(char c)
{
    if ((c==' ') || (c=='\t') || (c=='\n'))
        return(1);
    else
        return(0);
}


int CHARFUNC_digit_to_val(char digit)
{
    switch (digit)
    {
    case '0':  return(0);
        break;
    case '1':  return(1);
        break;
    case '2':  return(2);
        break;
    case '3':  return(3);
        break;
    case '4':  return(4);
        break;
    case '5':  return(5);
        break;
    case '6':  return(6);
        break;
    case '7':  return(7);
        break;
    case '8':  return(8);
        break;
    case '9':  return(9);
        break;
    default:   return(-1);
        break;
    }
}


char CHARFUNC_nibble_to_lc_hex_digit(int nibble)
{
    switch (nibble & 0x0F)
    {
    case  0:
        return('0');
        break;
    case  1:
        return('1');
        break;
    case  2:
        return('2');
        break;
    case  3:
        return('3');
        break;
    case  4:
        return('4');
        break;
    case  5:
        return('5');
        break;
    case  6:
        return('6');
        break;
    case  7:
        return('7');
        break;
    case  8:
        return('8');
        break;
    case  9:
        return('9');
        break;
    case 10:
        return('a');
        break;
    case 11:
        return('b');
        break;
    case 12:
        return('c');
        break;
    case 13:
        return('d');
        break;
    case 14:
        return('e');
        break;
    case 15:
        return('f');
        break;
    default:
#ifdef P_CASSERT
        CASSERT_Assert(0, __FILE__, __LINE__);
#endif
        return('?');
        break;
    }
}


void CHARFUNC_int_to_lc_hex_rev(int arg, char *s)
{
    int i;

#ifdef P_CASSERT
    CASSERT_Assert(s != NULL, __FILE__, __LINE__);
#endif

    for (i=0; i<8; i++)
    {
        s[i] = CHARFUNC_nibble_to_lc_hex_digit(arg);
        arg >>= 4;
    }
}


char CHARFUNC_to_upper(char c)
{
    switch (c)
    {
    case 'a':
        return('A');
        break;
    case 'b':
        return('B');
        break;
    case 'c':
        return('C');
        break;
    case 'd':
        return('D');
        break;
    case 'e':
        return('E');
        break;
    case 'f':
        return('F');
        break;
    case 'g':
        return('G');
        break;
    case 'h':
        return('H');
        break;
    case 'i':
        return('I');
        break;
    case 'j':
        return('J');
        break;
    case 'k':
        return('K');
        break;
    case 'l':
        return('L');
        break;
    case 'm':
        return('M');
        break;
    case 'n':
        return('N');
        break;
    case 'o':
        return('O');
        break;
    case 'p':
        return('P');
        break;
    case 'q':
        return('Q');
        break;
    case 'r':
        return('R');
        break;
    case 's':
        return('S');
        break;
    case 't':
        return('T');
        break;
    case 'u':
        return('U');
        break;
    case 'v':
        return('V');
        break;
    case 'w':
        return('W');
        break;
    case 'x':
        return('X');
        break;
    case 'y':
        return('Y');
        break;
    case 'z':
        return('Z');
        break;
    default:
        return(c);
        break;
    }
}


char CHARFUNC_to_lower(char c)
{
    switch (c)
    {
    case 'A':
        return('a');
        break;
    case 'B':
        return('b');
        break;
    case 'C':
        return('c');
        break;
    case 'D':
        return('d');
        break;
    case 'E':
        return('e');
        break;
    case 'F':
        return('f');
        break;
    case 'G':
        return('g');
        break;
    case 'H':
        return('h');
        break;
    case 'I':
        return('i');
        break;
    case 'J':
        return('j');
        break;
    case 'K':
        return('k');
        break;
    case 'L':
        return('l');
        break;
    case 'M':
        return('m');
        break;
    case 'N':
        return('n');
        break;
    case 'O':
        return('o');
        break;
    case 'P':
        return('p');
        break;
    case 'Q':
        return('q');
        break;
    case 'R':
        return('r');
        break;
    case 'S':
        return('s');
        break;
    case 'T':
        return('t');
        break;
    case 'U':
        return('u');
        break;
    case 'V':
        return('v');
        break;
    case 'W':
        return('w');
        break;
    case 'X':
        return('x');
        break;
    case 'Y':
        return('y');
        break;
    case 'Z':
        return('z');
        break;
    default:
        return(c);
        break;
    }
}

char CHARFUNC_int_to_lower(int arg)
{
    static const char *ref = "abcdefghijklmnopqrstuvwxyz";

    if ((arg >= 0) && ((unsigned)arg < strlen(ref)))
    {
        return(ref[arg]);
    } else
    {
        return('?');
    }
}


const char *CHARFUNC_Vcinfo_C(void)
{
    return("$Revision: 1.6 $");
}


const char *CHARFUNC_Vcinfo_H(void)
{
    return(CHARFUNC_VCINFO_H);
}


//----------------------------------------------------------------------------------------------------
//$Log: charfunc.c,v $
//Revision 1.6  2012/03/30 00:58:36  dashley
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
//End of $RCSfile: charfunc.c,v $
//----------------------------------------------------------------------------------------------------
