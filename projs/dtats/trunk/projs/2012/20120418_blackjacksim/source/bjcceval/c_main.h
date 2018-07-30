//----------------------------------------------------------------------------------------------------
//$Header: /home/dashley/cvsrep/e3ft_gpl01/e3ft_gpl01/dtaipubs/cron/2010/blackjack_201010/source/bjcceval/c_main.h,v 1.4 2012/03/29 23:44:00 dashley Exp $
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
#ifndef C_MAIN_H_INCLUDED
#define C_MAIN_H_INCLUDED

#ifdef MODULE_C_MAIN
    #define DECMOD_C_MAIN
#else
    #define DECMOD_C_MAIN extern
#endif

DECMOD_C_MAIN const char * C_MAIN_Vcinfo_H(void);
DECMOD_C_MAIN const char * C_MAIN_Vcinfo_C(void);

#define C_MAIN_VCINFO_H  "$Revision: 1.4 $"

#endif

//----------------------------------------------------------------------------------------------------
//$Log: c_main.h,v $
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
//End of $RCSfile: c_main.h,v $
//----------------------------------------------------------------------------------------------------
