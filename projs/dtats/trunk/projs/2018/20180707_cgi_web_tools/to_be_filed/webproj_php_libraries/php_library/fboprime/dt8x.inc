<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/dt8x.inc 205 2018-07-15 19:00:51Z dashley $
//--------------------------------------------------------------------------------------------------------------
//dt8.inc--FboPrime Functions Manipulating DT8 Data Type
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
//This contains functions that deal with the DT8 data type (calenadar dates in
//the form "YYYYMMDD", for example "20060415") that are not needed for dayview
//scheduling.
//--------------------------------------------------------------------------------------------------------------
require_once("dt8.inc");
require_once("datefuncx.inc");
//
//--------------------------------------------------------------------------------------------------------------
//Returns a string of the form DD-Mon-YYYY (example:  03-Sep-2006) based on a
//passed DT8.  If the DT8 is blank or invalid, returns "Never".
//
function DT8_ddmmmyyyy_string($dt8_in)
   {
   $dt8_in = Trim($dt8_in);

   if (strlen($dt8_in) != 8)
      {
      return("Never");
      }
   else
      {
      DT8_extract_components($dt8_in, $valid, $components);

      if (!$valid)
         {
         return("Never");
         }
      else
         {
         return(sprintf("%02d-%s-%04d", 
                        $components[2],
                        DATEFUNC_string_month_short($components[1]),
                        $components[0] 
                        ));
         }
      } 
   }
//
//--------------------------------------------------------------------------------------------------------------
//End of $RCSfile: dt8x.inc,v $.
//--------------------------------------------------------------------------------------------------------------
?>
