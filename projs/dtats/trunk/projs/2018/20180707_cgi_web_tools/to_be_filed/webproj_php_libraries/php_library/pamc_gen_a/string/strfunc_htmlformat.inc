<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/pamc_gen_a/string/strfunc_htmlformat.inc 205 2018-07-15 19:00:51Z dashley $
//--------------------------------------------------------------------------------
//strfunc_htmlformat.inc -- PAMC string functions related to HTML formatting.
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
//End of $RCSfile: strfunc_htmlformat.inc,v $.
//--------------------------------------------------------------------------------
?>
