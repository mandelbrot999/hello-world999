<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/htmlformatx.inc 205 2018-07-15 19:00:51Z dashley $
//********************************************************************************
//htmlformatx.inc--FboPrime HTML Formatting Functions Not Used for Dayview
//                 Scheduler Page
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
//This file contains functions that assist in formatting HTML.  Please also see
//htmlformat.inc.
//--------------------------------------------------------------------------------
require_once("htmlformat.inc");
//--------------------------------------------------------------------------------
//Outputs the number of "&nbsp;" tokens specified.
//
function HTMLFORMAT_nbsp_output($count)
   {
   $s = "";

   for ($i=0; $i<$count; $i++)
      {
      $s .= "&nbsp;";
      }

   HTMLFORMAT_echo_noop_nl($s);
   }
//--------------------------------------------------------------------------------
//End of $RCSfile: htmlformatx.inc,v $.
//--------------------------------------------------------------------------------
?>
