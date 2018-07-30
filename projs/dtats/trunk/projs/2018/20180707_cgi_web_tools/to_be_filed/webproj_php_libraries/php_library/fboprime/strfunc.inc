<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/strfunc.inc 205 2018-07-15 19:00:51Z dashley $
//********************************************************************************
//Copyright (C)2006 David T. Ashley
//********************************************************************************
//This program or source file is free software; you can redistribute it and/or 
//modify it under the terms of the GNU General Public License as published by
//the Free Software Foundation; either version 2 of the License, or (at your 
//option) any later version.
//
//This program or source file is distributed in the hope that it will 
//be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You may have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//********************************************************************************
//Dave Ashley, 04/06
//
//This source file contains string functions.
//
//The site hash key must be included, as this is used for all hashing functions.
//
//require_once("sitehashkey.inc");
//
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
//
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
//For the passed string, will return a string of "&nbsp;"'s that approximately
//equals the length when displayed in a table.
//
function STRFUNC_nbsp_padding($arg)
   {
   $n = (int)(1.95 * strlen($arg));

   $rv = "";

   for ($i = 0; $i < $n; $i++)
      {
      $rv .= "&nbsp;";
      }

   return($rv);
   }
//
//--------------------------------------------------------------------------------
//Escapes a JavaScript internal string that is delimited by single quotes.
//This allows the use of contractions and other constructs within the
//string.
//
//The string is not truncated in any way (it should be known in advance
//that the string is of a suitable length).
//
//This function is used to preprocess strings (usually from a database) that
//will occur embedded in JavaScript within single quotes.
//
function STRFUNC_js_escape_sglquote_notrunc($arg)
   {
   //Be sure no funky stuff in string.
   $temp = STRFUNC_force_into_subset
             (
             $arg, 
             "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ;.,()<>{}:'\"-*+/0123456789"
             );
   //
   //For each single quote in string, replace it with \'.  For each double-quote,
   //since I haven't figured out how to properly escape it, it is turned into an
   //escaped single quote.
   $rv = "";
   $count = strlen($temp);
   for ($i=0; $i<$count; $i++)
      {
      $c = SubStr($temp, $i, 1);
      if ($c == "'")
         $rv .= "\\'";
      else if ($c == "\"")
         $rv .= "\\'";
      else
         $rv .= $c;
      }

   return($rv);
   }
//
//--------------------------------------------------------------------------------
//Escapes an HTML "title" string that is delimited by double quotes.
//This allows the use of quoted text and other constructs within the
//string.
//
//The string is not truncated in any way (it should be known in advance
//that the string is of a suitable length).
//
function STRFUNC_html_title_escape_dblquote_notrunc($arg)
   {
   //Be sure no funky stuff in string.
   $temp = STRFUNC_force_into_subset
             (
             $arg, 
             "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ;.,()<>{}:'\"-*+/0123456789"
             );
   //
   //For each double quote in string, replace it with \".
   $rv = "";
   $count = strlen($temp);
   for ($i=0; $i<$count; $i++)
      {
      $c = SubStr($temp, $i, 1);
      if ($c == "\"")
         $rv .= "&quot;";
      else
         $rv .= $c;
      }

   return($rv);
   }
//
//--------------------------------------------------------------------------------
//Creates a GET string (including the ?) that should be appended to a URL to
//pass the date and time.
//
function STRFUNC_datetime_get_url_trailer($sddt, $sdtim)
   {
   if (($sddt === FALSE) && ($sdtim === FALSE))
      {
      //Nothing to append.
      return("");
      }
   else if (($sddt === FALSE) && ($sdtim !== FALSE))
      {
      //Time only.
      return("?sdtim=" . $sdtim);
      }
   else if (($sddt !== FALSE) && ($sdtim === FALSE))
      {
      //Date only.
      return("?sddt=" . $sddt);
      }
   else
      {
      //Both date and time.
      return("?sddt=" . $sddt . "&sdtim=" . $sdtim);
      }
   }
//
//--------------------------------------------------------------------------------
//End of $RCSfile: strfunc.inc,v $.
//--------------------------------------------------------------------------------
?>
