<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/usrs.inc 205 2018-07-15 19:00:51Z dashley $
//--------------------------------------------------------------------------------------------------------------
//usrs.inc--FboPrime Database usrs Table Manipulation Functions
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
//Contains functions related to [operations on] the usrs table of the database.
//--------------------------------------------------------------------------------------------------------------
//
require_once("db.inc");
require_once("global.inc");
//
//--------------------------------------------------------------------------------------------------------------
//Constants for usrs table fields.
//
//Constants for the status field of the usrs table.
define("USRS_STATUS_INACTIVE",                             0                         );
define("USRS_STATUS_ACTIVE",                               1                         );
define("USRS_STATUS_MAX",                                  2                         );
//
//Constants for the "role" of the usrs table.  Note that only short tags and descriptive strings and included,
//the integer index (starting at 0) is implied by the location in the table.
//
define("USRS_ROLE_UNSPECIFIED",                            0                         );
define("USRS_ROLE_STUDPRESOLO",                            1                         );
define("USRS_ROLE_STUDSOLO",                               2                         );
define("USRS_ROLE_CUSTNONPILOT",                           3                         );
define("USRS_ROLE_CUSTPILOT",                              4                         );
define("USRS_ROLE_EMPLINE",                                5                         );
define("USRS_ROLE_EMPMECHANIC",                            6                         );
define("USRS_ROLE_EMPOFFICE",                              7                         );
define("USRS_ROLE_EMPFINST",                               8                         );
define("USRS_ROLE_OWNER",                                  9                         );
define("USRS_ROLE_MAX",                                   10                         );
$USRS_ROLE_ARRAY = array(
                        "unspecified",                      "Unspecified",
                        "studpresolo",                      "Student, Pre-Solo",
                        "studsolo",                         "Student, Solo",
                        "custnonpilot",                     "Customer, Non-Pilot",
                        "custpilot",                        "Customer, Pilot",
                        "empline",                          "Employee, Line",
                        "empmechanic",                      "Employee, Mechanic",
                        "empoffice",                        "Employee, Office",
                        "empfinst",                         "Employee, Flight Instructor",
                        "owner",                            "Owner"
                        );
//
//Constants for the sex (gender) of the user.
define("USRS_SEX_UNSPECIFIED",                             0                         );
define("USRS_SEX_FEMALE",                                  1                         );
define("USRS_SEX_MALE",                                    2                         );
//
//--------------------------------------------------------------------------------------------------------------
//Warning codes for the functions in usrs.inc and usrsx.inc.  Warnings are typically returned as an array.
//
define("USRS_WARN_NONE",                                   0 );  //No warning.
//
//--------------------------------------------------------------------------------------------------------------
//Error codes for the functions in usrs.inc and usrsx.inc.  Errors are typically returned as an array.
//
define("USRS_ERROR_NONE",                                  0 );  //No error.
define("USRS_ERROR_ACTION_PAR_ILLEGAL",                    1 );  //The "action" parameter was illegal.
define("USRS_ERROR_IDX_ILLEGAL",                           2 );  //The integer index supplied is illegal.
define("USRS_ERROR_USERID_ILLEGAL",                        3 );  //The userid supplied is illegal.
define("USRS_ERROR_IDX_ON_ADD",                            4 );  //The idx was specified on an add (illegal).
define("USRS_ERROR_NO_USERID_ON_ADD",                      5 );  //The userid was missing on an add operation.
define("USRS_ERROR_DUP_USERID_ON_ADD",                     6 );  //The userid was already in the table on an add operation.
define("USRS_ERROR_MOD_REC_NOT_PRESENT",                   7 );  //The user record specified was not present.
define("USRS_ERROR_MOD_IDX_USERID_INCONSISTENT",           8 );  //The index and userid were both specified for modification,
                                                                 //and they were inconsistent.
define("USRS_ERROR_EDITING_COLLISION",                     9 );  //Attempt to modify a record that was modified since browser
                                                                 //form copy loaded.
define("USRS_ERROR_UNSPECIFIED",                          10 );  //An error of an unknown, unspecified, or unexpected type.
//
//--------------------------------------------------------------------------------------------------------------
//Returns TRUE if the passed string is acceptable for a userid, or an array of complaints
//if the passed string is not acceptable.
//
function USRS_userid_membership_test($arg)
   {
   $rvidx = 0;

   //Must be string type.
   if (! is_string($arg))
      {
      $rv[$rvidx] = "The <i>userid</i> must be a string (internal software error).";
      $rvidx++;
      return($rv);
      }

   //Must not be zero length.
   $len = strlen($arg);
   if ($len == 0)
      {
      $rv[$rvidx] = "The <i>userid</i> must be at least one character long.";
      $rvidx++;
      return($rv);
      }

   //Must not be too long.
   if ($len > 20)
      {
      $rv[$rvidx] = "The <i>userid</i> may not be longer than 20 characters.";
      $rvidx++;
      return($rv);
      }

   //Split the string for further analysis.
   $first_char = SubStr($arg, 0, 1);
   $remainder = SubStr($arg, 1, $len-1);

   //First character must be lower-case letter.
   if (strpos("abcdefghijklmnopqrstuvwxyz", $first_char) === FALSE)
      {
      $rv[$rvidx] = "The first character of the <i>userid</i> must be a letter.";
      $rvidx++;
      return($rv);
      }

   //Remaining characters must be lower-case letters or digits.
   for ($i=0; $i < ($len-1); $i++)
      {
      $c = SubStr($remainder, $i, 1);
      if (strpos("abcdefghijklmnopqrstuvwxyz0123456789", $c) === FALSE)
         {
         $rv[$rvidx] = "All characters of the <i>userid</i> must be letters or digits.";
         $rvidx++;
         return($rv);
         }
      }

   //Seems OK.
   return(TRUE);
   }
//
//--------------------------------------------------------------------------------------------------------------
//Returns the index of the entry from the usrs table where the userid matches, or
//FALSE if the entry does not exist.
//
function USRS_userid_idx_map($arg)
   {
   global $GLOBAL_dbhandle;

   //Form the query string.
   $query_string = "SELECT idx FROM usrs WHERE userid=\""
                   .
                   mysql_real_escape_string($arg, $GLOBAL_dbhandle)
                   .
                   "\"";

   //Execute the query.
   $result = mysql_query($query_string, $GLOBAL_dbhandle);

   if ($result === FALSE)
      {
      //Unknown query failure.  Return FALSE to the caller.  No need to free,
      //as this is not a result.
      return(FALSE);
      }
   else
      {
      //Get the integer result.
      $row = mysql_fetch_array($result, MYSQL_NUM);

      $rv = $row[0];

      //Free the result.
      mysql_free_result($result);

      //Return the appropriate.
      if($rv > 0)
         return($rv);
      else
         return(FALSE); 
      }
   }
//
//--------------------------------------------------------------------------------------------------------------
//Retrieves a two dimensional associative array corresponding to the USRS record
//with the passed USERID, or FALSE if the record does not exist.
//
function USRS_retrieve_by_userid($userid)
   {
   global $GLOBAL_dbhandle;

   //Form the query string.
   $query_string = "SELECT * FROM usrs WHERE userid=\""
                   .
                   mysql_real_escape_string($userid, $GLOBAL_dbhandle)
                   .
                   "\"";

   //Execute the query.
   $result = mysql_query($query_string, $GLOBAL_dbhandle);

   if ($result === FALSE)
      {
      //Unknown query failure.  Return FALSE to the caller.  No need to free,
      //as this is not a result.
      $rv = FALSE;
      }
   else
      {
      //Figure out how many rows in the result.
      $nrows = mysql_num_rows($result);

      if ($nrows == 0)
         {
         //No rows in the result.  The query failed to give us a record, but still
         //we need to free the result set.

         //Free the result.
         mysql_free_result($result);

         //The caller gets FALSE.  No record with that SID.
         $rv = FALSE;
         }
      else
         {
         //We have at least one record.  Assume just one, because the USERID is supposed
         //to be unique.
         $rv = mysql_fetch_assoc($result);  //Get the associative record.

         //Free the result.
         mysql_free_result($result);
         }

      //Return the value to the caller.
      return($rv);
      }
   }
//
//--------------------------------------------------------------------------------------------------------------
//Retrieves a two dimensional associative array corresponding to the USRS record
//with the passed IDX, or FALSE if the record does not exist.
//
function USRS_retrieve_by_idx($idx)
   {
   global $GLOBAL_dbhandle;

   //Form the query string.
   $query_string = "SELECT * FROM usrs WHERE idx=\""
                   .
                   mysql_real_escape_string($idx, $GLOBAL_dbhandle)
                   .
                   "\"";

   //Execute the query.
   $result = mysql_query($query_string, $GLOBAL_dbhandle);

   if ($result === FALSE)
      {
      //Unknown query failure.  Return FALSE to the caller.  No need to free,
      //as this is not a result.
      $rv = FALSE;
      }
   else
      {
      //Figure out how many rows in the result.
      $nrows = mysql_num_rows($result);

      if ($nrows == 0)
         {
         //No rows in the result.  The query failed to give us a record, but still
         //we need to free the result set.

         //Free the result.
         mysql_free_result($result);

         //The caller gets FALSE.  No record with that SID.
         $rv = FALSE;
         }
      else
         {
         //We have at least one record.  Assume just one, because the IDX is supposed
         //to be unique.
         $rv = mysql_fetch_assoc($result);  //Get the associative record.

         //Free the result.
         mysql_free_result($result);
         }

      //Return the value to the caller.
      return($rv);
      }
   }
//
//--------------------------------------------------------------------------------------------------------------
//Given an associative array containing information about a user, returns:
//  a)The userid.
//  b)The name to be displayed.  The database rules may be lax, so need to protect for the possibility that
//    the last name, first name, or both are missing.
//
function USRS_form_display_strings_a($uinfo, &$userid, &$dname)
   {
   if ($uinfo === FALSE)
      {
      $userid = "invaliduser";
      $dname  = "Invalid User";
      }
   else if ((strlen($uinfo["lname"]) > 0) && (strlen($uinfo["fname"]) > 0))
      {
      //This is the very normal case where we have a first and last name.
      $userid = $uinfo["userid"];
      $dname  = $uinfo["fname"] . " " . $uinfo["lname"];
      }
   else if ((strlen($uinfo["lname"]) > 0) && (strlen($uinfo["fname"]) == 0))
      {
      //First name seems to be absent.
      if ($uinfo["sex"] == USRS_SEX_UNSPECIFIED)
         {
         $title = "Mr. or Ms.";
         }
      else if ($uinfo["sex"] == USRS_SEX_FEMALE)
         {
         $title = "Ms.";
         }
      else
         {
         $title = "Mr.";
         }

      $userid = $uinfo["userid"];
      $dname  = $title . " " . $uinfo["lname"];
      }
   else
      {
      //We want to refer to this user by number rather than name.  The name seems to be
      //critically absent.
      $userid = $uinfo["userid"];
      $dname  = sprintf("User #%d", $uinfo["idx"]);
      }
   }
//
//--------------------------------------------------------------------------------------------------------------
//Updates the "mostrecentlogin" string of a user's database record.  Input parameter is minimally 
//checked to be sure no surprises.
//
//The crmodsguid of the record isn't updated or checked.  Reason is that this is an independent
//matter (the most recent login time) and not something that can ever be changed directly by
//a user.
//
function USRS_set_mostrecentlogin($userinfo, $mrl_in)
   {
   global $GLOBAL_dbhandle;

   //echo "<pre>\n";
   //print_r($sid_in);
   //print_r($sddt_in);
   //print_r($sdtim_in);
   //echo "</pre>\n";

   //Force this to be a string.
   $mrl_in = (string)$mrl_in;

   //Force this to be all numeric.
   $mrl_in = STRFUNC_force_into_subset($mrl_in, "0123456789");

   //If it is longer than 8 characters, whack it down.
   if (strlen($mrl_in) > 8)
      $mrl_in = SubStr($mrl_in, 0, 8);

   //Do the query.  Nothing should go wrong.
   $query_string = "UPDATE usrs set mostrecentlogin=\""
                   .
                   mysql_real_escape_string ($mrl_in, $GLOBAL_dbhandle)
                   .
                   "\" WHERE idx=\""
                   .
                   $userinfo["idx"]
                   .
                   "\"";
   //Run the query.  We don't much care whether it fails or succeeds (nothing to be done, anyway).
   mysql_query($query_string, $GLOBAL_dbhandle);
   }
//
//--------------------------------------------------------------------------------------------------------------
//End of $RCSfile: usrs.inc,v $.
//--------------------------------------------------------------------------------------------------------------
?>
