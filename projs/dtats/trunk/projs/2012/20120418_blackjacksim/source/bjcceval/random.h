//----------------------------------------------------------------------------------------------------
//$Header: /home/dashley/cvsrep/e3ft_gpl01/e3ft_gpl01/dtaipubs/cron/2010/blackjack_201010/source/bjcceval/random.h,v 1.5 2012/04/11 03:31:51 dashley Exp $
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
#ifndef RANDOM_H_INCLUDED
#define RANDOM_H_INCLUDED

#ifdef MODULE_RANDOM
    #define DECMOD_RANDOM
#else
    #define DECMOD_RANDOM extern
#endif

DECMOD_RANDOM unsigned RANDOM_Bit(void);
DECMOD_RANDOM unsigned RANDOM_Uint32(void);
DECMOD_RANDOM unsigned RANDOM_UintBounded32(unsigned min, unsigned max);
DECMOD_RANDOM int      RANDOM_Int32(void);
DECMOD_RANDOM int      RANDOM_IntBounded32(int min, int max);

DECMOD_RANDOM const char *RANDOM_Vcinfo_C(void);
DECMOD_RANDOM const char *RANDOM_Vcinfo_H(void);

#define RANDOM_VCINFO_H  "$Revision: 1.5 $"

#if defined(P_TEST) || defined(P_TEST_RANDOM)
DECMOD_RANDOM int RANDOM_Test(void);
#endif

#endif

//----------------------------------------------------------------------------------------------------
//$Log: random.h,v $
//Revision 1.5  2012/04/11 03:31:51  dashley
//Edits.
//
//Revision 1.4  2012/03/30 00:20:15  dashley
//Edits.
//
//Revision 1.3  2012/03/29 23:44:01  dashley
//Edits.
//
//Revision 1.2  2012/03/15 23:38:08  dashley
//License text enhanced.
//
//Revision 1.1  2012/03/11 21:01:46  dashley
//Initial checkin.
//----------------------------------------------------------------------------------------------------
//End of $RCSfile: random.h,v $
//----------------------------------------------------------------------------------------------------
