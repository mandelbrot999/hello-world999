//----------------------------------------------------------------------------------------------------
//$Header: /home/dashley/cvsrep/e3ft_gpl01/e3ft_gpl01/dtaipubs/cron/2010/blackjack_201010/source/bjcceval/timefunc.c,v 1.2 2012/03/30 01:05:31 dashley Exp $
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
#define MODULE_TIMEFUNC

#include <assert.h>
#include <stdio.h>
#include <sys/timeb.h>
#include <time.h>

#include "timefunc.h"

#include "charfunc.h"


static unsigned TIMEFUNC_ascii_month_to_unsigned(char c1, char c2, char c3)
{
    unsigned rv = 0;

    c1 = CHARFUNC_to_upper(c1);
    c2 = CHARFUNC_to_upper(c2);
    c3 = CHARFUNC_to_upper(c3);

    if (c1 == 'J')
    {
        if ((c2 == 'A') && (c3 == 'N'))
        {
            rv = 1;
        } else if ((c2 == 'U') && (c3 == 'N'))
        {
            rv = 6;
        } else if ((c2 == 'U') && (c3 == 'L'))
        {
            rv = 7;
        }
    } else if (c1 == 'F')
    {
        if ((c2 == 'E') && (c3 == 'B'))
        {
            rv = 2;
        }
    } else if (c1 == 'M')
    {
        if ((c2 == 'A') && (c3 == 'R'))
        {
            rv = 3;
        } else if ((c2 == 'A') && (c3 == 'Y'))
        {
            rv = 5;
        }
    } else if (c1 == 'A')
    {
        if ((c2 == 'P') && (c3 == 'R'))
        {
            rv = 4;
        } else if ((c2 == 'U') && (c3 == 'G'))
        {
            rv = 8;
        }
    } else if (c1 == 'S')
    {
        if ((c2 == 'E') && (c3 == 'P'))
        {
            rv = 9;
        }
    } else if (c1 == 'O')
    {
        if ((c2 == 'C') && (c3 == 'T'))
        {
            rv = 10;
        }
    } else if (c1 == 'N')
    {
        if ((c2 == 'O') && (c3 == 'V'))
        {
            rv = 11;
        }
    } else if (c1 == 'D')
    {
        if ((c2 == 'E') && (c3 == 'C'))
        {
            rv = 12;
        }
    }

    return(rv);
}


void TIMEFUNC_to_ascii_logstamp(const struct __timeb64 *in_arg, TIMEFUNC_TIME_ASCII_RESULT *out_arg)
{
    __time64_t time64;
    errno_t error_return;
    char buffer[100];

    //Be sure we don't have an unbounded string just in case something goes wrong.
    buffer[0]                  = 0;
    buffer[sizeof(buffer) - 1] = 0;

    //Extract the 64-bit time.
    time64 = in_arg->time;

    //Convert the 64-bit time to a string.
    error_return = _ctime64_s(buffer, sizeof(buffer), &time64);
    assert(error_return == 0);

    //The first two digits of the logstamp should be the hour.
    out_arg->result[0] = buffer[11];
    out_arg->result[1] = buffer[12];

    //The next two digits should be the minute.
    out_arg->result[2] = buffer[14];
    out_arg->result[3] = buffer[15];

    //The next two digits should be the second.
    out_arg->result[4] = buffer[17];
    out_arg->result[5] = buffer[18];

    //Then a decimal point.
    out_arg->result[6] = '.';

    //The next three (7, 8, 9) should be the milliseconds.
    sprintf_s(&(out_arg->result[7]), 4, "%03d", in_arg->millitm);

    //The tenth should be the terminator.  It was probably handled by sprintf() above.
    out_arg->result[10] = 0;

    //printf("\n0000000000111111111122222222223\n0123456789012345678901234567890\n%s\n", buffer);
    //printf("\n%s\n", out_arg->result);
}


void TIMEFUNC_to_ascii_hr_form(const struct __timeb64 *in_arg, TIMEFUNC_TIME_ASCII_RESULT *out_arg)
{
    //Library function form.
    //0000000000111111111122222222223
    //0123456789012345678901234567890
    //Sun Dec 14 00:36:36 2008
    //
    //Target form:
    //000000000011111111112222222222333
    //012345678901234567890123456789012
    //Sun, Dec 14, 2008 at 00:36:36.123 

    __time64_t time64;
    errno_t error_return;
    char buffer[100];

    //Be sure we don't have an unbounded string just in case something goes wrong.
    buffer[0]                  = 0;
    buffer[sizeof(buffer) - 1] = 0;

    //Extract the 64-bit time.
    time64 = in_arg->time;

    //Convert the 64-bit time to a string.
    error_return = _ctime64_s(buffer, sizeof(buffer), &time64);
    assert(error_return == 0);

    //The first three characters should be the day of the week.
    out_arg->result[0]  = buffer[0];
    out_arg->result[1]  = buffer[1];
    out_arg->result[2]  = buffer[2];

    //Comma and a space.
    out_arg->result[3]  = ',';
    out_arg->result[4]  = ' ';

    //Month
    out_arg->result[5]  = buffer[4];
    out_arg->result[6]  = buffer[5];
    out_arg->result[7]  = buffer[6];

    //Space
    out_arg->result[8]  = ' ';

    //Day of month, perhaps with preceding space.
    out_arg->result[9]  = buffer[8];
    out_arg->result[10] = buffer[9];

    //Comma and a space.
    out_arg->result[11] = ',';
    out_arg->result[12] = ' ';

    //Year
    out_arg->result[13] = buffer[20];
    out_arg->result[14] = buffer[21];
    out_arg->result[15] = buffer[22];
    out_arg->result[16] = buffer[23];

    //" at "
    out_arg->result[17] = ' ';
    out_arg->result[18] = 'a';
    out_arg->result[19] = 't';
    out_arg->result[20] = ' ';

    //Hour
    out_arg->result[21] = buffer[11];
    out_arg->result[22] = buffer[12];

    //Separating colon.
    out_arg->result[23] = ':';

    //Minute
    out_arg->result[24] = buffer[14];
    out_arg->result[25] = buffer[15];

    //Separating colon.
    out_arg->result[26] = ':';

    //Integer seconds.
    out_arg->result[27] = buffer[17];
    out_arg->result[28] = buffer[18];

    //"." Separator
    out_arg->result[29] = '.';

    //The next three (30, 31, 32) should be the milliseconds.
    sprintf_s(&(out_arg->result[30]), 4, "%03d", in_arg->millitm);

    //The tenth should be the terminator.  It was probably handled by sprintf() above.
    out_arg->result[33] = 0;

    //printf("\n0000000000111111111122222222223\n0123456789012345678901234567890\n%s\n", buffer);
    //printf("\n%s\n", out_arg->result);
}


void TIMEFUNC_to_ascii_filename_base(const struct __timeb64 *in_arg, TIMEFUNC_TIME_ASCII_RESULT *out_arg)
{
    //Library function form.
    //0000000000111111111122222222223
    //0123456789012345678901234567890
    //Sun Dec 14 00:36:38 2008
    //
    //Target form:
    //000000000011111
    //012345678901234
    //20081214_003638

    __time64_t time64;
    errno_t error_return;
    unsigned month;
    char buffer[100];

    //Be sure we don't have an unbounded string just in case something goes wrong.
    buffer[0]                  = 0;
    buffer[sizeof(buffer) - 1] = 0;

    //Extract the 64-bit time.
    time64 = in_arg->time;

    //Convert the 64-bit time to a string.
    error_return = _ctime64_s(buffer, sizeof(buffer), &time64);
    assert(error_return == 0);

    //Year
    out_arg->result[0] = buffer[20];
    out_arg->result[1] = buffer[21];
    out_arg->result[2] = buffer[22];
    out_arg->result[3] = buffer[23];

    //Month
    month = TIMEFUNC_ascii_month_to_unsigned(buffer[4], buffer[5], buffer[6]);

    if (month == 0)
    {
        out_arg->result[4]  = '?';
        out_arg->result[5]  = '?';
    } else
    {
        sprintf_s(&(out_arg->result[4]), 3, "%02u", month);
    }

    //Day of month, perhaps with preceding space.
    out_arg->result[6]  = buffer[8];
    out_arg->result[7]  = buffer[9];

    //Underscore.
    out_arg->result[8]  = '_';

    //Hour
    out_arg->result[9]  = buffer[11];
    out_arg->result[10] = buffer[12];

    //Minute
    out_arg->result[11] = buffer[14];
    out_arg->result[12] = buffer[15];

    //Second
    out_arg->result[13] = buffer[17];
    out_arg->result[14] = buffer[18];

    //Zero terminator
    out_arg->result[15] = 0;

    //printf("\n0000000000111111111122222222223\n0123456789012345678901234567890\n%s\n", buffer);
    //printf("\n%s\n", out_arg->result);
}


const char *TIMEFUNC_Vcinfo_C(void)
{
    return("$Revision: 1.2 $");
}


const char *TIMEFUNC_Vcinfo_H(void)
{
    return(TIMEFUNC_VCINFO_H);
}


//----------------------------------------------------------------------------------------------------
//$Log: timefunc.c,v $
//Revision 1.2  2012/03/30 01:05:31  dashley
//Edits.
//
//Revision 1.1  2012/03/30 00:59:16  dashley
//Initial checkin.
//----------------------------------------------------------------------------------------------------
//End of $RCSfile: timefunc.c,v $
//----------------------------------------------------------------------------------------------------
