<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/pamc_gen_a/string/strfunc_int.inc 205 2018-07-15 19:00:51Z dashley $
//--------------------------------------------------------------------------------
//strfunc_int.inc -- PAMC string functions related to integer formatting.
//Copyright (C) 2007  David T. Ashley
//--------------------------------------------------------------------------------
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either version 2
//of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//--------------------------------------------------------------------------------
//Author contact information:
//   David T. Ashley
//   P.O. Box 918
//   Marshall, Michigan, 49068
//   dta@e3ft.com
//--------------------------------------------------------------------------------
//Pads a string on the left by zero until it reaches the
//target length.  If the string is longer than the target length,
//it is truncated on the left.
//
//Unit tested 20060408.
//
function STRFUNC_pad_left_zero($str_in, $target_len)
   {
   if ($target_len >= 0)  //Ignore invalid targets
      {
      $len = strlen($str_in);

      if ($target_len == 0)
         {
         $str_in = "";
         }
      else if ($len < $target_len)
         {
         //The input string is too short.  Pad it on the left with zeros.
         $to_add = $target_len - $len;
         for ($i = 0; $i < $to_add; $i++)
            {
            $str_in = "0". $str_in;
            }
         }
      else if ($len > $target_len)
         {
         //The input string is too long.  Remove the extra characters.
         $to_remove = $len - $target_len;

         $str_in = substr($str_in, $to_remove);
         }
      //In the final omitted else case, there is length equality, and hence nothing to do.
      }

   return($str_in);
   }
//
//--------------------------------------------------------------------------------
//End of $RCSfile: strfunc_int.inc,v $.
//--------------------------------------------------------------------------------
?>
