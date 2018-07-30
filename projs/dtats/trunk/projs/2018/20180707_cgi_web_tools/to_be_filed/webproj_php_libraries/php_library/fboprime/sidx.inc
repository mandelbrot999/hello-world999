<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/sidx.inc 205 2018-07-15 19:00:51Z dashley $
//********************************************************************************
//Copyright (C) 2006 David T. Ashley
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
//This source file provides the code to create and manipulate session
//identifiers (SIDs) that is not required in the dayview scheduling page.
//The format of the SGUID is documented in the FBO-Prime manual.
//
require_once("sid.inc");
//
//
//--------------------------------------------------------------------------------
//Reformats an SID string to include dots at strategic places for more
//human-friendly display.
//
function SID_dotted_display_string_a($sid_in)
   {
   if (! is_string($sid_in))
      {
      //Don't know what this is ... it isn't an sid.  Just send it back.
      return($sid_in);
      }
   else if (strlen($sid_in) != 66)
      {
      //This doesn't seem to be the right length for an sid.  Give it back.
      return($sid_in);
      }
   else
      {
      //Seems right.
      return(
            SubStr($sid_in, 0, 2)
            .
            "."
            .
            SubStr($sid_in, 2, 2)
            .
            "."
            .
            SubStr($sid_in, 4, 11)
            .
            "."
            .
            SubStr($sid_in, 15, 9)
            .
            "."
            .
            SubStr($sid_in, 24, 10)
            .
            "."
            .
            SubStr($sid_in, 34, 32)
            );
      }
   }
//
//--------------------------------------------------------------------------------
//End of $RCSfile: sidx.inc,v $.
//--------------------------------------------------------------------------------
?>
