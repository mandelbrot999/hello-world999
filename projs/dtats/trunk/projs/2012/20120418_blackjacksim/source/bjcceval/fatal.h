//----------------------------------------------------------------------------------------------------
//$Header: /home/dashley/cvsrep/e3ft_gpl01/e3ft_gpl01/dtaipubs/cron/2010/blackjack_201010/source/bjcceval/fatal.h,v 1.2 2012/03/30 01:05:31 dashley Exp $
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
#ifndef FATAL_H_INCLUDED
#define FATAL_H_INCLUDED

#ifdef MODULE_FATAL
    #define DECMOD_FATAL
#else
    #define DECMOD_FATAL extern
#endif

DECMOD_FATAL void FATAL_fatal(const char *desc,
                              const char *file,
                              int        line);
DECMOD_FATAL const char *FATAL_Vcinfo_C(void);
DECMOD_FATAL const char *FATAL_Vcinfo_H(void);

#define FATAL_VCINFO_H  "$Revision: 1.2 $"

#endif 


//----------------------------------------------------------------------------------------------------
//$Log: fatal.h,v $
//Revision 1.2  2012/03/30 01:05:31  dashley
//Edits.
//
//Revision 1.1  2012/03/30 00:59:16  dashley
//Initial checkin.
//----------------------------------------------------------------------------------------------------
//End of $RCSfile: fatal.h,v $
//----------------------------------------------------------------------------------------------------
