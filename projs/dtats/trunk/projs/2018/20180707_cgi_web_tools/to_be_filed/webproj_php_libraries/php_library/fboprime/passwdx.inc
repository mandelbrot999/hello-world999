<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/passwdx.inc 205 2018-07-15 19:00:51Z dashley $
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
//This source file provides the code to deal with the manipulation of
//passwords.
//
require_once("passwd.inc");
require_once("strfunc.inc");
//
//--------------------------------------------------------------------------------
//Parses a field that is purported to be a password entered for the purpose
//of validating an operation.  Returns any warnings, errors, status, etc.
//
function PASSWD_operation_validate_a(
                                     $passwd_in,           //Password in.
                                     $userinfo_in,         //Associative array of user information.
                                     &$validated_out,      //TRUE if password validates, FALSE otherwise.
                                     &$forced_logout_out,  //TRUE if should force a logout, FALSE otherwise.
                                     &$errors_out,         //Errors are added to the array.
                                     &$warnings_out        //Warnings are added to the array.
                                    )
   {
   //Force password to a string.
   $passwd_in = (string)$passwd_in;

   //Forcibly trim the password down to the allowed characters.
   $passwd_in = STRFUNC_force_into_subset($passwd_in, PASSWD_ALLOWED_CHARS);

   //Trim blanks from both sides of the password.
   $passwd_in = Trim($passwd_in);

   //If the password is empty, this represents an omission (rather than a forced logout).
   if (strlen($passwd_in) == 0)
      {
      $errors_out[]    = "A password must be supplied in order to complete this operation.";
      $validated_out     = FALSE;
      $forced_logout_out = FALSE;
      }
   //Try to validate the password.
   else if (PASSWD_pwd_hash_auth($userinfo_in["pwhash"], $passwd_in))
      {
      //The password has successfully validated.
      $validated_out     = TRUE;
      $forced_logout_out = FALSE;
      }
   else
      {
      //Validation has failed.
      $validated_out     = FALSE;
      $forced_logout_out = TRUE;
      }
   }
//
//--------------------------------------------------------------------------------
?>
