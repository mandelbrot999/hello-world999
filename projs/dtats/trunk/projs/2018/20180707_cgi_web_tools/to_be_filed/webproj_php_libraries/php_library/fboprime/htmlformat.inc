<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/htmlformat.inc 205 2018-07-15 19:00:51Z dashley $
//********************************************************************************
//htmlformat.inc--FboPrime HTML Formatting Functions
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
//This file contains functions that assist in formatting HTML.
//--------------------------------------------------------------------------------
//The number of spaces per indent level.
define("HTMLFORMAT_SPACES_PER_INDENT_LEVEL", 2);
//
//A constant string of spaces.  It has to be long enough to cover the maximum
//indent that will be permitted.  An indent too large will just cause string
//truncation.
//
define("HTMLFORMAT_SPACE_STRING",
       "                                                                                                   ");
//
//--------------------------------------------------------------------------------
//Outputs the correct number of spaces for the indent level in force.
//
function HTMLFORMAT_indent_echo()
   {
   global $GLOBAL_html_indent_level;

   if (CONFIG_HTML_PRETTY)
      {
      echo SubStr(HTMLFORMAT_SPACE_STRING, 
                  0, 
                  $GLOBAL_html_indent_level * HTMLFORMAT_SPACES_PER_INDENT_LEVEL);
      }
   else
      {
      echo " ";
      }
   }
//--------------------------------------------------------------------------------
//Echoes a string with the correct indent level applied and no newline.
//
function HTMLFORMAT_echo_noop_nn($arg)
   {
   HTMLFORMAT_indent_echo();
   echo $arg;
   }
//--------------------------------------------------------------------------------
//Echoes a string with the correct indent level applied and a newline.
//
function HTMLFORMAT_echo_noop_nl($arg)
   {
   HTMLFORMAT_indent_echo();
   echo $arg;
   echo "\n";
   }
//--------------------------------------------------------------------------------
//Echoes a string with the correct indent level applied and no newline,
//then increases the indent level.  This is suitable for tags that
//start a container.
//
function HTMLFORMAT_echo_push_nn($arg)
   {
   global $GLOBAL_html_indent_level;

   HTMLFORMAT_indent_echo();
   echo $arg;
   $GLOBAL_html_indent_level++;
   }
//--------------------------------------------------------------------------------
//Echoes a string with the correct indent level applied and a newline, then
//increases the indent level.  This is suitable for tags that start a
//container.
//
function HTMLFORMAT_echo_push_nl($arg)
   {
   global $GLOBAL_html_indent_level;

   HTMLFORMAT_indent_echo();
   echo $arg;
   echo "\n";
   $GLOBAL_html_indent_level++;
   }
//--------------------------------------------------------------------------------
//Decreases the indent level by one, then echoes a string with the correct
//indent level applied and no newline.  This is suitable for tags that
//end a container.
//
function HTMLFORMAT_echo_pull_nn($arg)
   {
   global $GLOBAL_html_indent_level;

   if ($GLOBAL_html_indent_level > 0)
      $GLOBAL_html_indent_level--;

   HTMLFORMAT_indent_echo();
   echo $arg;
   }
//--------------------------------------------------------------------------------
//Decreases the indent level by one, then echoes a string with the correct 
//indent level applied and a newline.  This is suitable for tags that end a
//container.
//
function HTMLFORMAT_echo_pull_nl($arg)
   {
   global $GLOBAL_html_indent_level;

   if ($GLOBAL_html_indent_level > 0)
      $GLOBAL_html_indent_level--;

   HTMLFORMAT_indent_echo();
   echo $arg;
   echo "\n";
   }
//--------------------------------------------------------------------------------
//Provides a string containing exactly the number of spaces appropriate for the
//indent level.
//
function HTMLFORMAT_indent_string()
   {
   global $GLOBAL_html_indent_level;

   return(
          SubStr(HTMLFORMAT_SPACE_STRING, 
                 0, 
                 $GLOBAL_html_indent_level * HTMLFORMAT_SPACES_PER_INDENT_LEVEL)
         );
   }
//--------------------------------------------------------------------------------
//Increases the indent level by one.
//
function HTMLFORMAT_indent_push()
   {
   global $GLOBAL_html_indent_level;

   $GLOBAL_html_indent_level++;
   }
//--------------------------------------------------------------------------------
//Decreases the indent level by one, but not below zero.
//
function HTMLFORMAT_indent_pop()
   {
   global $GLOBAL_html_indent_level;

   if ($GLOBAL_html_indent_level > 0)
      $GLOBAL_html_indent_level--;
   }
//
//--------------------------------------------------------------------------------
//End of $RCSfile: htmlformat.inc,v $.
//--------------------------------------------------------------------------------
?>
