<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/perm.inc 205 2018-07-15 19:00:51Z dashley $
//--------------------------------------------------------------------------------------------------------------
//perm.inc--FboPrime User Permission String Processing
//Copyright (C) 2006  David T. Ashley
//
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
//********************************************************************************
//This includes functions used to process user permission strings, and explains
//the format of permission strings (but not textual descriptions of what the
//variables mean or the semantics).  For explanation of the semantics of the 
//permission string variables, please see permview.inc.
//--------------------------------------------------------------------------------------------------------------
require_once("global.inc");
require_once("strfunc.inc");
//
//--------------------------------------------------------------------------------------------------------------
//Format of an individual permission:
//  a)Begins with a single backslash.
//  b)Followed by at least one letter of either case (parameter names are case-sensitive).
//  c)Followed by aribitrarily many letters and numbers.
//  d)Followed by "=".
//  e)Followed by a quotation mark.
//  f)Followed by the actual parameter--only spaces, letters, hyphens, periods, and numbers are allowed.
//    The empty string is allowed.
//  g)Concluded by another quotation mark.
//
//Format of a permission string:
//  a)Simple concatenation of aribitrarily many individual permissions as described above.
//
//The format in general is designed for rapid search.  The string functions will find parameter
//names quite quickly.
//--------------------------------------------------------------------------------------------------------------
//Retrieves the value of a parameter within a string, or FALSE if the parameter does not
//exist in the string.
//
//The permission string must be properly formatted.
//
//Unit-tested 20060427.
//
function PERM_get_val_from_string($permstring, $permname)
   {
   $idx = strpos($permstring, "\\" . $permname . "=");

   if ($idx === FALSE)
      {
      //Value not found.  Indicate this to the caller with FALSE.
      return(FALSE);
      }
   else
      {
      //Value was found.
      $len = strlen($permstring);  //Record the length for efficiency.

      //Grab the offset of the two quotes following the parameter name.
      $q1pos = FALSE;
      $q2pos = FALSE;
      $q1pos = strpos($permstring, "\"", $idx);
      if (($q1pos !== FALSE) && ($q1pos < ($len-1)))
         $q2pos = strpos($permstring, "\"", $q1pos + 1);

      //Return the appropriate result.
      if (($q1pos !== FALSE) && ($q2pos !== FALSE))
         {
         //We have a properly-quoted result.  Return it.
         return(SubStr($permstring, $q1pos+1, $q2pos-$q1pos-1));
         }
      else
         {
         //Something went wrong.  Return FALSE.
         return(FALSE);
         }
      }
   }
//
//--------------------------------------------------------------------------------------------------------------
//Splits a permission string into its components, and returns an associative array containing the permission
//string names as the keys and the values as the elements.
//
//If there are no permissions in the string, returns FALSE.
//
//The string should be a properly-formatted permission string.
//
//If the are multiple entries in the string, the later value will be written
//over the earlier one in the associative array.
//
//Unit-tested 20060427.
//
function PERM_split_aa($arg)
   {
   $temp = explode("\\", $arg);

   if ($temp === FALSE)
      {
      return(FALSE);
      }
   else if (count($temp) == 0)
      {
      return(FALSE);
      }
   else
      {
      $putidx = 0;

      for ($i=0; $i<count($temp); $i++)
         {
         $val = $temp[$i];
         $len = strlen($val);

         if ($len >= 4)
            {
            $q1pos = FALSE;
            $q2pos = FALSE;
            $q1pos = strpos($val, "\"");
            if (($q1pos !== FALSE) && ($q1pos < ($len-1)))
               $q2pos = strpos($val, "\"", $q1pos + 1);

            if (($q1pos !== FALSE) && ($q2pos !== FALSE) && ($q1pos >= 2))
               {
               $rv[SubStr($val, 0, $q1pos-1)] = SubStr($val, $q1pos+1, $q2pos-$q1pos-1);
               $putidx++;
               }
            }
         }

      //Unless we couldn't find anything seemingly valid, return the array.
      if ($putidx > 0)
         return($rv);
      else
         return(FALSE);
      }
   }
//
//--------------------------------------------------------------------------------------------------------------
//Recombines a permission string that has been split from an associative array into a permission string.
//No hard error checking is performed, i.e. array names with invalid characters or strings with invalid
//characters will slip through in the interest of speed.
//
function PERM_combine_aa($arg)
   {
   $rv = "";

   reset($arg);
   while (list($key, $val) = each($arg))
      {
      $rv = $rv . "\\" . $key . "=\"" . $val . "\"";
      }

   return($rv);
   }
//
//--------------------------------------------------------------------------------------------------------------
//Recombines a permission string that has been split from an associative array into a permission string.
//All invalid characters are stripped from both key names and values (and empty keys are dropped), leading
//to a guaranteed valid permission string.  This function is naturally slower than the function above because
//of the error checking.
//
function PERM_combine_aa_error_trap($arg)
   {   
   $rv = "";

   //Since we're doing an expensive operation, might as well sort the array, too.
   ksort($arg);

   reset($arg);
   while (list($key, $val) = each($arg))
      {
      if (strlen($key) > 0)  //Don't want to go further if key is empty.
         {
         //Force the string into numbers and letters for the key.
         $key = STRFUNC_force_into_subset($key, "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
         
         //It is still possible that the first character is a digit, which is a no-no.
         //Rip characters off the string until we have either a letter or an empty string.
         while ((strlen($key) > 0) && (strpos("0123456789", SubStr($key, 0, 1)) !== FALSE))
            {
            $key = SubStr($key, 1, strlen($key) - 1);  //Rip the character off the front.
            }

         //If we have an empty string, don't proceed.
         if (strlen($key) > 0)
            {
            //Force the value into the allowable character set.
            $val = STRFUNC_force_into_subset($val, " abcdefghijklmnopqrstuvwxyz-.ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");

            //Add to the string.
            $rv = $rv . "\\" . $key . "=\"" . $val . "\"";
            }
         }
      }

   return($rv);
   }
//
//--------------------------------------------------------------------------------------------------------------
//Forces a permission string into valid space.
//
//This can be done inefficiently by just splitting and then recombining.
//
//Unit-tested 20060427.
//
function PERM_force_into_valid_space($arg)
   {
   $splitval = PERM_split_aa($arg);               //Split it.
   $rv = PERM_combine_aa_error_trap($splitval);   //Recombine it.

   //Return value to caller.
   return($rv);
   }
//
//--------------------------------------------------------------------------------------------------------------
//End of $RCSfile: perm.inc,v $.
//--------------------------------------------------------------------------------------------------------------
?>
