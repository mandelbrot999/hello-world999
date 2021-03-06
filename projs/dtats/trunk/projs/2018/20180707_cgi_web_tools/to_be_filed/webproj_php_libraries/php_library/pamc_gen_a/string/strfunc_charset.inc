<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/pamc_gen_a/string/strfunc_charset.inc 205 2018-07-15 19:00:51Z dashley $
//--------------------------------------------------------------------------------
//str_charset.inc -- PAMC string functions related to sets of characters.
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
//Returns 1 if the string is purely digits '0'-'9', or 0 otherwise.
//
//Unit tested 20060408.
//
function STRFUNC_is_pure_digits($arg)
   {
   //Must be a string.
   if (! is_string($arg))
      return(0);

   $len = strlen($arg);

   for ($i=0; $i<$len; $i++)
      {
      $c = SubStr($arg, $i, 1);
      if (strpos("0123456789", $c) === FALSE)
         return(0);
      }

   return(1);
   }
//
//
//--------------------------------------------------------------------------------
//Returns 1 if each character in the subset is present in the set, i.e.
//if it is a proper or improper subset, or 0 otherwise.
//
//Unit tested 20060408.
//
function STRFUNC_is_char_subset($conjectured_subset, $reference_set)
   {
   $conjsubsetlen = strlen($conjectured_subset);
   $refsetlen     = strlen($reference_set);
   
   for ($i=0; $i<$conjsubsetlen; $i++)
      {
      $c = SubStr($conjectured_subset, $i, 1);

      if (strpos($reference_set, $c) === FALSE)
         return(0);
      }

   //If we've made it this far, no character has failed to pan out.
   return(1);
   }
//--------------------------------------------------------------------------------
//Removes all characters from the input that are not in the set of
//allowed characters.
//
function STRFUNC_force_into_subset($input, $subset)
   {
   $inputlen  = strlen($input);
   $subsetlen = strlen($subset);
   
   $rv = "";
   for ($i=0; $i<$inputlen; $i++)
      {
      $c = SubStr($input, $i, 1);

      if (strpos($subset, $c) === FALSE)
         {
         //Character is not in the set.  Do not add it to
         //the result.
         }
      else
         {
         //Character is in the set.  Add it.
         $rv .= $c;
         }
      }

   return($rv);
   }
//
//--------------------------------------------------------------------------------
//Forces the variable to be a string, removes all characters from the input that 
//are not in the set of allowed characters, then truncates the string if it is 
//too long.
//
function STRFUNC_force_stringtype_subset_truncate($input, $subset, $maxlen)
   {
   //Force the type.  Only numerics and strings can reliably be
   //strings.
   //
   if (is_string($input))
      {
      //It is already a string.  Do nothing.
      }
   else if (is_numeric($input))
      {
      //A number can be reliably made to a string.
      $input = (string) $input;
      }
   else
      {
      //We don't know what it is.  Make the empty string out of it.
      $input = (string) "";
      }

   //Force it into the allowed character set.
   $input = STRFUNC_force_into_subset($input, $subset);

   //Take care of the length.
   if (strlen($input) > $maxlen)
      $input = SubStr($input, 0, $maxlen);

   //echo " / " . $input . " / ";

   return($input);
   }
//
//--------------------------------------------------------------------------------
//End of $RCSfile: strfunc_charset.inc,v $.
//--------------------------------------------------------------------------------
?>
