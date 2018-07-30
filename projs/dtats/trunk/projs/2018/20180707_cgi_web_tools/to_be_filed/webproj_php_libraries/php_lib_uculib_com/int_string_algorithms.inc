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
//This file implements algorithms on integers (typically large integers) 
//represented as strings.
//--------------------------------------------------------------------------------
//Notes on canonical form:  for use with the numerical functions in this
//library, the following conventions apply:
//   a)Zero has one representation, "0".
//   b)On non-zero numbers, no leading 0's are allowed.
//   c)Positive numbers have no leading "+", but negative numbers have a
//     leading "-".
//   d)No commas, spaces, or extraneous characters are allowed.
//
//The notes above apply only to the form used for calculation.  For presentation
//in human-readable form, commas are allowed.
//--------------------------------------------------------------------------------
require_once("int_string_arithmetic.inc");
//--------------------------------------------------------------------------------
//
//Calculates the GCD of the two integers n1 and n2, using Euclid's classic
//algorithm.
//
//Results returned:
//  out_gcd:     The gcd, as a string.  FALSE is returned if there is an
//               error condition and the out_icalcs value is undefined.
//
//  out_icalcs:  The calculation intermediate results, as an array.  Each
//               subscripted element of the array has these fields:
//                  dividend  : The dividend in that round.
//                  divisor   : The divisor in that round.
//                  quotient  : The quotient in that round.
//                  remainder : The remainder in that round.
//
function ISALG_gcd($in_n1, $in_n2, &$out_gcd, &$out_icalcs)
   {
   if ((ISARITH_cmp(1, $in_n1) > 0) || (ISARITH_cmp(1, $in_n2) > 0))
      {
      //Input parameter(s) illegal.  Must return FALSE.
      $out_gcd    = FALSE;
      $out_icalcs = FALSE;
      }
   else
      {
      $i = -1;
      $out_icalcs[0]['dividend'] = $in_n1;
      $out_icalcs[0]['divisor']  = $in_n2;
      do
         {
         $i++;

         $out_icalcs[$i]['quotient']  = ISARITH_div($out_icalcs[$i]['dividend'], $out_icalcs[$i]['divisor']);
         $out_icalcs[$i]['remainder'] = ISARITH_mod($out_icalcs[$i]['dividend'], $out_icalcs[$i]['divisor']);
         if (ISARITH_cmp($out_icalcs[$i]['remainder'], 0) > 0)
            {
            $out_icalcs[$i+1]['dividend']  = $out_icalcs[$i]['divisor'];
            $out_icalcs[$i+1]['divisor']   = $out_icalcs[$i]['remainder'];
            }
         } while(ISARITH_cmp($out_icalcs[$i]['remainder'], 0) > 0);

      //Unless we completed in a single round, GCD is the last non-zero remainder.
      //Since the last remainder is zero to terminate the loop, this must be it.
      if ($i <= 0)
         $out_gcd = $out_icalcs[0]['divisor'];
      else
         $out_gcd = $out_icalcs[$i-1]['remainder'];
      }
   }
?>
