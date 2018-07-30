<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/passwd.inc 205 2018-07-15 19:00:51Z dashley $
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
require_once("sguid.inc");       //Necesssary to generate SGUIDs.
require_once("crhsh.inc");
//
//
//Characters allowed in a password.
define("PASSWD_ALLOWED_CHARS", "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-");
//
//Characters that will be used when generating an automatic replacement password.
define("PASSWD_AUTOGEN_CHARS", "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
//
//Minimum and maximum lengths for a password.
define("PASSWD_LEN_MIN", 4);
define("PASSWD_LEN_MAX", 22);
//
//
//--------------------------------------------------------------------------------
//Returns a random password suitable for use when e-mailing a user a replacement
//for a lost password.
//
//Unit-tested 20060408.
//
function PASSWD_random_password_gen()
   {
   //Assuming 12 chars, this will be about 62^10 = 3.2E21 possibilities.
   //This will be adequate, although it is substantially less information
   //than an MD5 (2^128 = 3.4E38).  Strictly speaking, this appears to be
   //the weak link.  However, even guessing 1,000 passwords per second,
   //expected value of solution time is 102 billion years.
   // 
   $len = 12; //PASSWD_LEN_MAX;
   $pwd = "";

   for ($i=0; $i<$len; $i++)
      {
      $pos = rand(0, strlen(PASSWD_AUTOGEN_CHARS)-1);
      $c = SubStr(PASSWD_AUTOGEN_CHARS, $pos, 1);
      $pwd .= $c;
      }
   
   return($pwd);
   }
//
//
//--------------------------------------------------------------------------------
//Given a password, returns the salt and the hash that should be stored in
//the database.  The salt is an SGUID (32 characters), and the hash proper
//will be another 32 characters, giving a total of 64 characters.
//
//The password used isn't checked--that should have been done before
//this function is used.
//
//Unit-tested 20060408.
//
function PASSWD_stored_hash_gen($passwd)
   {
   $salt = SGUID_sguid();
   $hash = CRHSH_hashva($salt, $passwd);
   return(StrToUpper($salt . $hash));
   }
//
//
//--------------------------------------------------------------------------------
//Authenticates a password against a 64-character stored salt/hash.
//Returns 0 for authentication failure or 1 for authentication success.
//
//Unit-tested 20060408.
//
function PASSWD_pwd_hash_auth($stored_hash, $passwd)
   {
   //We can only accept strings.  Failure to provide
   //two strings is authentication failure.
   if ((! is_string($stored_hash)) || (! is_string($passwd)))
      return(0);

   //Stored hash must be of the right length.
   if (strlen($stored_hash) != 64)
      return(0);

   //Extract the salt from the stored hash.
   $salt = SubStr($stored_hash, 0, 32);

   //The salt should be a properly formed SGUID.  If not, failure.
   if (! SGUID_is_syntactically_valid($salt))
      return(0);

   //The comparison hash is formed from the stored salt and the password.
   $comparison_hash = StrToUpper(CRHSH_hashva($salt, $passwd));

   //The full value that should be stored and that we compare against is
   //the concatenation of the salt and the hash with upper-case letters.
   $comparison_stored_hash    = $salt . $comparison_hash;

   //If the strings don't match, authentication failure.
   if ($stored_hash != $comparison_stored_hash)
      return(0);

   //If we're here, authentication success.
   return(1);
   }
//
//
//--------------------------------------------------------------------------------
//Accepts as input a password that was either entered by a user either
//to authenticate or change passwords.  Checks the password
//against design rules for passwords.  Returns TRUE if the password
//is acceptable, or returns an array of complaints with HTML markup if not.
//
//Unit-tested 20060408.
//
function PASSWD_passwd_rules_check($passwd)
   {
   //Index into the complaints.
   $i = 0;

   //If we have been passed a non-string type, that is the ultimate complaint.
   if (! is_string($passwd))
      {
      $complaints[0] = "A non-string password was supplied to software internals.";
      return($complaints);
      }

   //Can't be too short.
   if (strlen($passwd) < PASSWD_LEN_MIN)
      {
      $complaints[$i] = "The password supplied is too short.&nbsp; Passwords must be at least 4 characters long.";
      $i++;
      }
   
   //Can't be too long.
   if (strlen($passwd) > PASSWD_LEN_MAX)
      {
      $complaints[$i] = "The password supplied is too long.&nbsp; Passwords can be no longer than 20 characters.";
      $i++;
      }

   //Can't contain illegal characters."
   if (! STRFUNC_is_char_subset($passwd, PASSWD_ALLOWED_CHARS))
      {
      $complaints[$i] = "The password supplied contains illegal characters.&nbsp; Passwords may contain only " .
                        "characters from the set &quot;" . PASSWD_ALLOWED_CHARS . "&quot;.";
      $i++;
      }

   //If we've registered no complaints, return TRUE, else return the complaints.
   if ($i)
      {
      return($complaints);
      }
   else
      {
      return(TRUE);
      }
   }
//--------------------------------------------------------------------------------
?>
