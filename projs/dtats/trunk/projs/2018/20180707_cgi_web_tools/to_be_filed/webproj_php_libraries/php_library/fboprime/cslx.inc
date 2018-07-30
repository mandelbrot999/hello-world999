<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/cslx.inc 205 2018-07-15 19:00:51Z dashley $
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
//This source file contains functions to deal with comma-separated lists not
//required by the dayview scheduler.
//
//require_once("sitehashkey.inc");
//
//--------------------------------------------------------------------------------
//Transitions from a comma-separated list to an array of strings.  Returns
//FALSE if empty set.
//
function CSL_csl_to_string_array($csl_in)
   {
   //Rip of end spaces.
   //
   $csl_in = Trim($csl_in);
   
   if (strlen($csl_in) == 0)
      {
      return(FALSE);
      }
   else
      {
      //Remove any leading comma.
      //
      if (SubStr($csl_in, 0, 1) == ",")
         $csl_in = SubStr($csl_in, 1);

      if (strlen($csl_in) == 0)
         {
         return(FALSE);
         }

      //Remove any trailing comma.
      if (SubStr($csl_in, strlen($csl_in) - 1) == ",")
         $csl_in = SubStr($csl_in, 0, strlen($csl_in) - 1);

      if (strlen($csl_in) == 0)
         {
         return(FALSE);
         }

      //Form the string array.
      return(explode(",", $csl_in));
      }
   }
//
//--------------------------------------------------------------------------------
//Transitions from a comma-separated string list to an array of integers.
//
function CSL_string_array_to_csl($int_array_in)
   {
   if ($int_array_in === FALSE)
      {
      return("");
      }
   else
      {
      return("," . implode(",", $int_array_in) . ",");
      }
   }
//
//--------------------------------------------------------------------------------
//End of $RCSfile: cslx.inc,v $.
//--------------------------------------------------------------------------------
?>
