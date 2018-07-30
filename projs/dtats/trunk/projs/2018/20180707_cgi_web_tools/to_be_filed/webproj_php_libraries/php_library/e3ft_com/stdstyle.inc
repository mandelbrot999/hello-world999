<?php
//********************************************************************************
//Copyright (C) 2003 David T. Ashley
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
//
//Dave Ashley, 07/05
//
//This class defines standard styles (HTML styles, ways of doing things)
//for the E3FT web pages.  Standard style includes the appearance of the pages,
//the CPU usage clock at the bottom, etc.
//
//--------------------------------------------------------------------------------
//Outputs the standard horizontal rule for the page.  This is typically used to
//separate sections of content within the page.
//
function STDSTYLE_hrule_std()
   {
   echo "<hr>\n";
   }
//
//--------------------------------------------------------------------------------
//Dumps out the standard header.  The page title is what is displayed by the
//browser, while the HTML title is what goes in big letters at the top of the
//page.  Size and alignment should be set here, italics if necessary can be
//put in the passed string.  The description is text below the header to 
//say a little bit more about the page.
//
function STDSTYLE_header_title($Pagetitle, $Htmltitle, $Desc)
   {
   echo "<html>\n";
   echo "<head>\n";
   echo "<title>" . $Pagetitle . "</title>\n";
   echo "</head>\n";
   echo "<body background=\"/bkgnds/bk10.gif\">\n";
   echo "<p align=\"center\"><b><font size=\"6\">" . $Htmltitle . "</font></b></p>\n";
   if (strlen($Desc))
      {
      echo "<p align=\"center\"><b><font size=\"5\">(" . $Desc . ")</font></b></p>\n";
      }
   STDSTYLE_hrule_std();
   }
//
//--------------------------------------------------------------------------------
//This function tallies up the used CPU time and prints out the standard footer which
//includes this information.
//
function STDSTYLE_footer_std()
   {
   STDSTYLE_hrule_std();
   echo "<p align=\"center\" style=\"margin-top: -2; margin-bottom: 0\"><font size=\"2\">This web page is maintained by <a href=\"mailto:webmaster@e3ft.com\">webmaster@e3ft.com</a>.<br>\n";
   echo "</font></p>\n";
   echo "<hr noshade size=\"5\">\n";
   echo "</body>\n";
   echo "</html>\n";
   }
//--------------------------------------------------------------------------------
?>
