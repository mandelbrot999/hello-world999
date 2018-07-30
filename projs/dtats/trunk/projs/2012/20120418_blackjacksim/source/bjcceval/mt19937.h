//----------------------------------------------------------------------------------------------------
//$Header: /home/dashley/cvsrep/e3ft_gpl01/e3ft_gpl01/dtaipubs/cron/2010/blackjack_201010/source/bjcceval/mt19937.h,v 1.2 2012/04/11 01:48:54 dashley Exp $
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
//Additionally, the C source file (other than minor name changes and edits to customize it for the
//BJCCEVAL program) is based on the program downloaded from the website of Takuji Nishimura and 
//Makoto Matsumoto.  Their licensing conditions are reproduced verbatim below.
//----------------------------------------------------------------------------------------------------
//A C-program for MT19937, with initialization improved 2002/1/26.
//Coded by Takuji Nishimura and Makoto Matsumoto.
//
//Before using, initialize the state by using init_genrand(seed)  
//or init_by_array(init_key, key_length).
//
//Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
//All rights reserved.                          
//
//Redistribution and use in source and binary forms, with or without
//modification, are permitted provided that the following conditions
//are met:
//
//  1. Redistributions of source code must retain the above copyright
//     notice, this list of conditions and the following disclaimer.
//
//  2. Redistributions in binary form must reproduce the above copyright
//     notice, this list of conditions and the following disclaimer in the
//     documentation and/or other materials provided with the distribution.
//
//  3. The names of its contributors may not be used to endorse or promote 
//     products derived from this software without specific prior written 
//     permission.
//
//THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
//CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
//EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
//PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
//PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
//LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
//NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//Any feedback is very welcome.
//http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
//email: m-mat @ math.sci.hiroshima-u.ac.jp (remove space)
//----------------------------------------------------------------------------------------------------
#ifndef MT19937_INCLUDED
#define MT19937_H_INCLUDED

#ifdef MODULE_MT19937
    #define DECMOD_MT19937
#else
    #define DECMOD_MT19937 extern
#endif

#include <stdio.h>

DECMOD_MT19937 unsigned long  MT19937_genrand_int32(void);

DECMOD_MT19937 const char    *MT19937_Vcinfo_C(void);
DECMOD_MT19937 const char    *MT19937_Vcinfo_H(void);

#define MT19937_VCINFO_H  "$Revision: 1.2 $"

#if defined(P_TEST) || defined(P_TEST_MT19937)
DECMOD_MT19937 int MT19937_Test(void);
#endif

#endif

//----------------------------------------------------------------------------------------------------
//$Log: mt19937.h,v $
//Revision 1.2  2012/04/11 01:48:54  dashley
//Edits.
//
//Revision 1.1  2012/04/11 00:52:58  dashley
//Initial checkin.
//----------------------------------------------------------------------------------------------------
//End of $RCSfile: mt19937.h,v $
//----------------------------------------------------------------------------------------------------
