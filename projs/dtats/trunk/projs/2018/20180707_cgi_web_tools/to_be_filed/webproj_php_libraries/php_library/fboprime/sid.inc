<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/sid.inc 205 2018-07-15 19:00:51Z dashley $
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
//identifiers (SIDs).  The format of the SGUID is documented in the 
//FBO-Prime manual.
//
require_once("sguid.inc");       //Necesssary to generate SGUIDs.
require_once("crhsh.inc");
//
//
//--------------------------------------------------------------------------------
//Returns a complete SID (including the "SI" prefix).
//
function SID_sid()
   {
   return("SI" . SID_sid_raw());
   }
//
//
//--------------------------------------------------------------------------------
//Returns a raw SID (without the "SI" prefix).
//
function SID_sid_raw()
   {
   $sguid  = SGUID_sguid();
   $crhash = CRHSH_hashva($sguid);

   //Convert any lower-case letters in the hash to upper-case.  This is canonical form.
   $crhash = StrToUpper($crhash);

   return($sguid . $crhash);
   }
//
//
//--------------------------------------------------------------------------------
//Returns the length of a SID (in characters).
//
function SID_sid_len()
   {
   return(66);
   }
//
//
//--------------------------------------------------------------------------------
//Validates the syntactic form of a SID.  Returns 0 if it isn't
//valid or 1 if it is.  Note that this validates only the form and the
//hash--the server session state aspect is not validated.
//
function SID_is_syntactically_valid($sid_to_check)
   {
   //Must be a string.
   if (! is_string($sid_to_check))
      return(0);

   //Must be of the right length.
   if (strlen($sid_to_check) != 66)
      return(0);

   //First two characters must be "SI".
   if (substr($sid_to_check, 0, 2) !== "SI")
      return(0);

   //The encapsulated SGUID must be valid.
   if (! SGUID_is_syntactically_valid(SubStr($sid_to_check, 2, 32)))
      return(0);

   //Generate a hash to match against.
   $original_hash   = SubStr($sid_to_check, 34, 32);
   $comparison_hash = StrToUpper(CRHSH_hashva(SubStr($sid_to_check, 2, 32)));

   //Compare the hashes.  Note that we don't have to check the string to be sure
   //hash chars are digits and hexadecimal digits--the comparison indirectly does
   //that for us.
   if ($original_hash != $comparison_hash)
      return(0);

   //If we're here, nothing obvious wrong with it.
   return(1);
   }
//--------------------------------------------------------------------------------
?>
