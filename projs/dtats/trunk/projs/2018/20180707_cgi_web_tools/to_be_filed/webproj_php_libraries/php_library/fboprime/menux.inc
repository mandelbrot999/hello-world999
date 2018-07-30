<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/menux.inc 205 2018-07-15 19:00:51Z dashley $
//--------------------------------------------------------------------------------------------------------------
//menux.inc--FboPrime Menu Generation Functions Not Required from Day View Scheduler
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
//This contains functions used to log events, both to the loge table of the
//database, and to the system log.
//--------------------------------------------------------------------------------------------------------------
require_once("global.inc");
require_once("menux.inc");
require_once("strfunc.inc");
require_once("utime.inc");
//
//--------------------------------------------------------------------------------------------------------------
//Generates menu text that is grouped, with the passed separator used between groups but not at the end.
//
function MENU_menu_inline_text_gen_01($userinfo_in, $menulevel_in, $dt8_in, $t4_in, $separator_in, $scriptname_in)
   {
   //Return value by default empty string.
   $rv = "";

   //Get the base array.
   //
   $menu_array = MENU_menu_gen($userinfo_in, $menulevel_in, $dt8_in, $t4_in, $scriptname_in);

   //Loop through, making the string.
   $num = count($menu_array);

   for ($i=0; $i<$num; $i+=3)
      {
      if ($menu_array[$i] == "H")
         {
         //For any except the first, need the separator.
         if ($i>0)
            $rv = $rv . $separator_in;

         //Heading.
         $rv = $rv . "<b>" . $menu_array[$i+1] . ":</b>&nbsp; ";
         }
      else
         {
         //For anything except the first entry after a heading, need a space.
         if ($menu_array[$i-3] != "H")
            $rv = $rv . " ";

         //Text entry.
         $rv = " " . $rv . "<a href=\"" . $menu_array[$i+2] . "\">" . $menu_array[$i+1] . "</a>";
         }      
      }

   return($rv);
   }
//
//--------------------------------------------------------------------------------------------------------------
//End of $RCSfile: menux.inc,v $.
//--------------------------------------------------------------------------------------------------------------
?>
