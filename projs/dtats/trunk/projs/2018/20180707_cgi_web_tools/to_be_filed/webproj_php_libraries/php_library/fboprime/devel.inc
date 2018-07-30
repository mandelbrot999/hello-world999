<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/devel.inc 205 2018-07-15 19:00:51Z dashley $
//--------------------------------------------------------------------------------------------------------------
//devel.inc--FboPrime Development Functions
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
//This contains functions used in development and debugging of FBO-Prime.  The
//contents of this file are kept separate to avoid introducing baggage into
//the production software.
//--------------------------------------------------------------------------------------------------------------
require_once("global.inc");
//
//--------------------------------------------------------------------------------------------------------------
//Emits the standard global variables of the pages.
//
function DEVEL_globals_emit()
   {
   global $GLOBAL_dbhandle;
   global $GLOBAL_dblocked;
   global $GLOBAL_html_indent_level;
   global $GLOBAL_utime_sec;
   global $GLOBAL_utime_sec_11;
   global $GLOBAL_utime_nsec;
   global $GLOBAL_stime_year;
   global $GLOBAL_stime_month;
   global $GLOBAL_stime_day;
   global $GLOBAL_stime_hour;
   global $GLOBAL_stime_minute;
   global $GLOBAL_stime_second;
   global $GLOBAL_stime_usec;
   global $GLOBAL_stime_dow;

   echo "<tt>\n";
   echo "--------------------------------------------------------------------------------<br>\n";
   echo "GLOBAL_dbhandle               :   " . $GLOBAL_dbhandle                      . "<br>\n";
   echo "GLOBAL_dblocked               :   " . $GLOBAL_dblocked                      . "<br>\n";
   echo "GLOBAL_html_indent_level      :   " . $GLOBAL_html_indent_level             . "<br>\n";
   echo "GLOBAL_utime_sec              :   " . $GLOBAL_utime_sec                     . "<br>\n";
   echo "GLOBAL_utime_sec_11           :   " . $GLOBAL_utime_sec_11                  . "<br>\n";
   echo "GLOBAL_utime_nsec             :   " . $GLOBAL_utime_nsec                    . "<br>\n";
   echo "GLOBAL_stime_year             :   " . $GLOBAL_stime_year                    . "<br>\n";
   echo "GLOBAL_stime_month            :   " . $GLOBAL_stime_month                   . "<br>\n";
   echo "GLOBAL_stime_day              :   " . $GLOBAL_stime_day                     . "<br>\n";
   echo "GLOBAL_stime_hour             :   " . $GLOBAL_stime_hour                    . "<br>\n";
   echo "GLOBAL_stime_minute           :   " . $GLOBAL_stime_minute                  . "<br>\n";
   echo "GLOBAL_stime_second           :   " . $GLOBAL_stime_second                  . "<br>\n";
   echo "GLOBAL_stime_usec             :   " . $GLOBAL_stime_usec                    . "<br>\n";
   echo "GLOBAL_stime_dow              :   " . $GLOBAL_stime_dow                     . "<br>\n";
   echo "--------------------------------------------------------------------------------<br>\n";
   echo "</tt>\n";
   }
//--------------------------------------------------------------------------------------------------------------
//End of $RCSfile: devel.inc,v $.
//--------------------------------------------------------------------------------------------------------------
?>
