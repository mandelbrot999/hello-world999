<?php
//********************************************************************************
//Copyright (C) 2007 David T. Ashley
//********************************************************************************
//This program or source file is free software; you can redistribute it and/or
//modify it under the terms of the GNU Lesser General Public License as published
//by the Free Software Foundation; either version 2 of the License, or (at your
//option) any later version.
//
//This program or source file is distributed in the hope that it will
//be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You may have received a copy of the GNU Lesser General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//********************************************************************************
//Arithmetic on rational numbers expressed as strings.
//--------------------------------------------------------------------------------
//Format of rational numbers expressed as strings:
//
//  a)Each rational number is "x:y", where x is an integer with an optional 
//    unary "-" sign, and y is a positive integer.
//
//  b)In addition to numerical values, the string "NAN" (not a number) is
//    recognized.   "NAN" combined with anything else is "NAN".
//
//  c)The canonical representation of zero is 0:y, where y is any positive
//    integer.
//
//  d)Rational numbers are not required to be reduced except where otherwise
//    documented.
//
//       d1)The arithmetic functions reduce results by default, but
//          each has an optional argument to suppress reduction.  The typical reasons
//          for suppressing reduction are:
//
//             d1a)Efficiency.
//
//             d1b)Aesthetics -- some reason the output should be left as-is.
//
//       d2)Functions that require reduced rational numbers must reduce
//          them (in general).
//
//  e)Only the numerator may carry an optional minus sign.  The denominator
//    must not have a negative sign.
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//----  R E D U C T I O N    -----------------------------------------------------
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//Reduces a rational number as two components.
//
function RATSTRARITH_reduce_rn_components(&$arg_num, &$arg_den)
   {
   }
//
//--------------------------------------------------------------------------------
//Reduces a rational number in the allowable canonical form.
//
function RATSTRARITH_reduce_rn_integrated($in_rn)
   {
   }
//
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//----  A S S I G N M E N T  -----------------------------------------------------
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//Assigns a rational number from two integers.  Reduction can be suppressed, but
//treatment of sign and the canonical representation of zero cannot be
//suppressed.
//
//Arguments may be integers or strings or any mix.
//
function RATSTRARITH_assign_from_ints($in_num, $in_den, $in_suppress_reduction = FALSE)
   {
   }
//
//--------------------------------------------------------------------------------
//Splits a rational number in the canonical form as a string into components.
//
function RATSTRARITH_split($in_rn, &out_num, &$out_den, $in_suppress_reduction = FALSE)
   {
   }
//
//--------------------------------------------------------------------------------
//Assigns a rational number from a string.  The formats accepted are:
//  a)Integer format (i.e. "25", "-2,352", etc.).
//  b)Scientific notation, i.e. "3.12451234e+3".
//  c)Integer fraction, i.e. "412/332234".
//  
//
function RATSTRARITH_assign_from_string($in_rn, &out_num, &$out_den, $in_suppress_reduction = FALSE)
   {
   }
//
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//----  T E S T S  ---------------------------------------------------------------
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//Compares two rational numbers.  NAN's in either operand always cause
//zero to be returned.  Returned values are the traditional -1, 0, 1.
//
function RATSTRARITH_cmp($in_rn1, $in_rn2)
   {
   }
//
//--------------------------------------------------------------------------------
//Returns -1 if the rational number is < 0, 0 if it is 0, or 1 if it is
//positive.  Returned value is integer rather than string.  NAN causes
//return value of zero.
//
function RATSTRARITH_sgn($in_arg)
   {
   }
//
//--------------------------------------------------------------------------------
//Returns TRUE if the rational number is NAN, or FALSE otherwise.
//
function RATSTRARITH_is_nan($in_arg)
   {
   }
//
//--------------------------------------------------------------------------------
//Returns TRUE if the rational number is a whole integer, or FALSE otherwise.
//NAN causes return value of zero.
//
function RATSTRARITH_is_int($in_arg)
   {
   }
//
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//----  E L E M E N T A L    O P E R A T I O N S  --------------------------------
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//Adds two rational numbers.
//
function RATSTRARITH_add($in_rn1, $in_rn2, $in_suppress_reduction = FALSE)
   {
   }
//
//--------------------------------------------------------------------------------
//Subtracts two rational numbers.
//
function RATSTRARITH_sub($in_rn1, $in_rn2, $in_suppress_reduction = FALSE)
   {
   }
//
//--------------------------------------------------------------------------------
//Multiplies two rational numbers.
//
function RATSTRARITH_sub($in_rn1, $in_rn2, $in_suppress_reduction = FALSE)
   {
   }
//
//--------------------------------------------------------------------------------
//Divides two rational numbers.
//
function RATSTRARITH_div($in_rn1, $in_rn2, $in_suppress_reduction = FALSE)
   {
   }
//
//
?>
