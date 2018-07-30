<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/sess.inc 205 2018-07-15 19:00:51Z dashley $
//--------------------------------------------------------------------------------------------------------------
//sess.inc--FboPrime Session and Authentication Management Functions and Constants
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
//Implement session and authentication functions.
//--------------------------------------------------------------------------------------------------------------
require_once("global.inc");
require_once("log.inc");
require_once("passwd.inc");
require_once("perm.inc");
require_once("sguid.inc");
require_once("sid.inc");
require_once("strfunc.inc");
require_once("usrs.inc");
require_once("utime.inc");
//
//--------------------------------------------------------------------------------------------------------------
//Constants for database storage, software internals, function parameters, and function return values of
//this module.
//
//Session reap time, in seconds.  This is how old an inactive session must be in order to reap it by
//nightly cron job.
//
define("SESS_REAP_INACTIVE_TIME",                  172800 );  //48 hours, in seconds.                        
//
//
//Function return values.
define("SESS_RCODE_SUCCESS",                            0 );  //Successful action.
define("SESS_RCODE_SUCCESS_TEMP_PASSWORD",              1 );  //Authentication action was successful, but
                                                              //authentication was performed based on the
                                                              //temporary password.  The user should be
                                                              //prompted to change their password as soon as
                                                              //possible.
define("SESS_RCODE_FAIL_USERID_EXPIRED_INACTIVE",       2 );  //Intended action failed because the userid
                                                              //and password specified authenticated
                                                              //properly, but the underlying userid is either
                                                              //expired or inactive.  The user should be
                                                              //granted no privileges and instructed to contact
                                                              //the FBO.
define("SESS_RCODE_FAIL_USERID_NOEXIST",                3 );  //Intended action failed because specified
                                                              //userid does not exist.
define("SESS_RCODE_FAIL_PASSWD",                        4 );  //Intended action failed because the password
                                                              //supplied was incorrect.
//
//Session constants for the logical page currently being visited.
//
define("SESS_LPAGE_UNDEFINED",                          0);   //Not yet defined or invalid SQL query
                                                              //result.
define("SESS_LPAGE_SCHEDDAYVIEW",                       1);   //Day view scheduler.
define("SESS_LPAGE_SCHEDWEEKVIEW",                      2);   //Week view scheduler.
define("SESS_LPAGE_SCHEDMONTHVIEW",                     3);   //Month view scheduler.
define("SESS_LPAGE_LOGRESOURCESCHEDULER",               4);   //Log file viewing.
define("SESS_LPAGE_DBSTATS",                            5);   //Database statistics.
define("SESS_LPAGE_RESOURCELIST",                       6);   //Resource list (or all resources).    
define("SESS_LPAGE_RESOURCERENUMBER",                   7);   //Resource list.    
define("SESS_LPAGE_RESOURCEVIEW",                       8);   //Resource view (of individual resource).    
define("SESS_LPAGE_RESOURCEEDIT",                       9);   //Resource edit (of individual resource).    
define("SESS_LPAGE_RESOURCEADD",                       10);   //Resource edit (of individual resource).    
define("SESS_LPAGE_USERSACTIVELIST",                   11);   //Users list (active).
define("SESS_LPAGE_USERSINACTIVELIST",                 12);   //Users list (active).
define("SESS_LPAGE_USERSVIEW",                         13);   //User view.
define("SESS_LPAGE_USERSEDIT",                         14);   //User edit.
define("SESS_LPAGE_USERSADD",                          15);   //User add.
define("SESS_LPAGE_MYRESERVATIONSLIST",                16);   //Self-reservations list.
//
//
//--------------------------------------------------------------------------------------------------------------
//Eats the session identifier cookie, if any exists on the browser side.
//
function SESS_eat_fbopsid_cookie()
   {
   setcookie("fbopsid",                    //Cookie name.
             FALSE,                        //Value.  FALSE means eat the cookie.
             0,                            //Expire when browser closes.  The PHP documentation
                                           //suggests to set this to a time well before the current
                                           //time, but I don't believe this is necessary to eat a cookie.
             CONFIG_URL_FSPATH . "/",      //Path within the domain.
             CONFIG_URL_DOMAIN,            //Domain.
             0);                           //Don't require secure connection.
   }
//
//--------------------------------------------------------------------------------------------------------------
//Issues the SID to the browser.
//
function SESS_issue_fbopsid_cookie($sid)
   {
   setcookie("fbopsid",                    //Cookie name.
             $sid,                         //Value.  FALSE means eat the cookie.
             0,                            //Value.  0 (according to the manual) means to keep cookie
                                           //until browser closed.
             CONFIG_URL_FSPATH . "/",      //Path within the domain.
             CONFIG_URL_DOMAIN,            //Domain.
             0);                           //Don't require secure connection.
   }
//
//--------------------------------------------------------------------------------------------------------------
//Inserts a new record into the SESS database, using the passed associative array to assign the fields.
//Each element of the associative array is indexed by a field name.
//
//The function returns the integer index of the record added.
//
//This operation cannot fail.  The autoincrement index is the primary key, so no duplicates or other
//error conditions are meaningful.
//
function SESS_insert($arg)
   {
   global $GLOBAL_dbhandle;
   global $GLOBAL_dblocked;

   //Build the query string with each successive parameter.
   //
   //sguid
   //-----
   if (! isset($arg["sguid"]))
      $pushval = "";
   else
      $pushval = $arg["sguid"];
   $query_string = "INSERT INTO sess SET sguid=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"";
   //
   //ip
   //------
   if (! isset($arg["ip"]))
      $pushval = "";
   else
      $pushval = $arg["ip"];
   $query_string .= (", ip=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //sid
   //---
   if (! isset($arg["sid"]))
      $pushval = "";
   else
      $pushval = $arg["sid"];
   $query_string .= (", sid=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //revaltime
   //---------
   if (! isset($arg["revaltime"]))
      $pushval = "";
   else
      $pushval = $arg["revaltime"];
   $query_string .= (", revaltime=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //lifetime
   //--------
   if (! isset($arg["lifetime"]))
      $pushval = 0;
   else
      $pushval = $arg["lifetime"];
   $query_string .= (", lifetime=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //usrsidx
   //-------
   if (! isset($arg["usrsidx"]))
      $pushval = 0;
   else
      $pushval = $arg["usrsidx"];
   $query_string .= (", usrsidx=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //menulvl
   //-------
   if (! isset($arg["menulvl"]))
      $pushval = 0;
   else
      $pushval = $arg["menulvl"];
   $query_string .= (", menulvl=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //pagereloadtime
   //--------------
   if (! isset($arg["pagereloadtime"]))
      $pushval = 0;
   else
      $pushval = $arg["pagereloadtime"];
   $query_string .= (", pagereloadtime=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //sddt
   //----
   if (! isset($arg["sddt"]))
      $pushval = "";
   else
      $pushval = $arg["sddt"];
   $query_string .= (", sddt=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //sdtim
   //-----
   if (! isset($arg["sdtim"]))
      $pushval = "";
   else
      $pushval = $arg["sdtim"];
   $query_string .= (", sdtim=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //logicalpage
   //-----------
   if (! isset($arg["logicalpage"]))
      $pushval = 0;
   else
      $pushval = $arg["logicalpage"];
   $query_string .= (", logicalpage=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //curuser
   //-------
   if (! isset($arg["curuser"]))
      $pushval = 0;
   else
      $pushval = $arg["curuser"];
   $query_string .= (", curuser=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //curresource
   //-----------
   if (! isset($arg["curresource"]))
      $pushval = 0;
   else
      $pushval = $arg["curresource"];
   $query_string .= (", curresource=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //curreservation
   //--------------
   if (! isset($arg["curreservation"]))
      $pushval = 0;
   else
      $pushval = $arg["curreservation"];
   $query_string .= (", curreservation=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //Execute the query to insert the record.
   $result = mysql_query($query_string, $GLOBAL_dbhandle);
   //
   //If the insert failed, our caller gets FALSE.
   if ($result == FALSE)
      {
      $rv = FALSE;
      }
   else
      {
      //The insert was successful.  Figure out the index that was assigned.
      $result = mysql_query("SELECT LAST_INSERT_ID()");

      //If we have a failure, the caller gets FALSE, otherwise the caller gets the
      //index.
      if ($result === FALSE)
         {
         $rv = FALSE;
         }
      else
         {
         //Pick apart the result.
         $row = mysql_fetch_array($result, MYSQL_NUM);

         //Extract the integer.
         $rv = $row[0];

         //Free the result memory.
         mysql_free_result($result);
         }
      }

   //Return the result.
   return($rv);
   }
//
//--------------------------------------------------------------------------------------------------------------
//Retrieves a two dimensional associative array corresponding to the SESS record with
//the passed SID, or FALSE if the record does not exist.
//
function SESS_retrieve_by_sid($sid)
   {
   global $GLOBAL_dbhandle;

   //Form the query string.
   $query_string = "SELECT * FROM sess WHERE sid=\""
                   .
                   mysql_real_escape_string($sid, $GLOBAL_dbhandle)
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
         //We have at least one record.  Assume just one, because the SID is supposed
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
//Deletes the server-side session information corresponding to the passed SID, if it exists in the
//SESS table.  Returns TRUE if at least one record is deleted, or FALSE otherwise.
//
function SESS_delete_by_sid($sid)
   {
   global $GLOBAL_dbhandle;

   //Form the query string.
   $query_string = "DELETE FROM sess WHERE sid=\""
                   .
                   mysql_real_escape_string($sid, $GLOBAL_dbhandle)
                   .
                   "\"";

   //Execute the query.
   mysql_query($query_string, $GLOBAL_dbhandle);

   //Figure out how many rows were affected.
   $ar = mysql_affected_rows($GLOBAL_dbhandle);

   //Return the right value to the caller.
   if ($ar <= 0)
      return(FALSE);
   else
      return(TRUE);
   }
//
//--------------------------------------------------------------------------------------------------------------
//Description:
//  Authenticates a supplied password against the non-temporary password hash stored with the supplied
//  database record from the user information.  There is also a possibility that the non-temporary
//  hash field is the empty string, which means that no password will authenticate.
//
//  Returns TRUE if the authentication was successful or FALSE otherwise.
//
function SESS_nontemppwauth($userinfo, $password)
   {
   if (PASSWD_pwd_hash_auth($userinfo["pwhash"], $password) == 1)
      return(TRUE);
   else
      return(FALSE);
   }
//
//--------------------------------------------------------------------------------------------------------------
//Description:
//  Authenticates a supplied password against the temporary password hash stored with the supplied
//  database record from the user information.  In order to authenticate, the the temporary
//  password also must not be expired.
//
//  Returns TRUE if the authentication was successful or FALSE otherwise.
//
function SESS_temppwauth($userinfo, $password)
   {
   global $GLOBAL_utime_ut;

   if (!strlen($userinfo["lostpwgentime"]) || !strlen($userinfo["lostpwhash"]))
      {
      return(FALSE);
      }
   else
      {
      if (
         UTIME_time_diff_coarse_28($GLOBAL_utime_ut, $userinfo["lostpwgentime"])
         > //Waiting time elapsed.
         (CONFIG_LOGIN_REC_TEMP_PW_LIFETIME * 60) //*60 because constant in minutes.
         )
         {
         return(FALSE);  //Temporary password has expired, so can't authenticate.
         }
      else
         {
         if (PASSWD_pwd_hash_auth($userinfo["lostpwhash"], $password) == 1)
            return(TRUE);
         }
      }
 
   //If we're lost and get here, authentication failed.
   return(FALSE);
   }
//
//--------------------------------------------------------------------------------------------------------------
//Description:
//  Opens a new session on the server based on the passed user information and returns the
//  SID.
//
function SESS_open_new_uinfo($userinfo)
   {
   global $GLOBAL_client_ip;
   global $GLOBAL_utime_ut;

   //Populate the SGUID.
   $sess["sguid"]        = SGUID_sguid();

   //Populate the IP address.
   $sess["ip"]           = $GLOBAL_client_ip;

   //Populate the session identifier.
   $sid                  = SID_sid();
   $sess["sid"]          = $sid;

   //Populate the revalidation time.
   $sess["revaltime"]    = $GLOBAL_utime_ut;

   //Populate the lifetime.  The lifetime is either the value stored in the permission string (if it
   //exists there), or else the default value.
   $sess["lifetime"] = PERM_get_val_from_string($userinfo["perm"], "sesslifetimedefault");
   if ($sess["lifetime"] === FALSE)                      //If that permission/attribute does not exist.
      $sess["lifetime"] = CONFIG_SESS_LIFETIME_DEFAULT;

   //Populate the index of the relevant user.
   $sess["usrsidx"]      = $userinfo["idx"];

   //Insert the record into the database.
   SESS_insert($sess);

   //Return the session ID to the caller.
   return($sid);
   }
//
//--------------------------------------------------------------------------------------------------------------
//Description:
//  Authenticates a supplied userid and password, and returns result information to the caller.
//  If the userid/password authenticate, retract the old cookie, open a new session on the server side,
//  and issue a new cookie.
//
//  This function is called from the main scheduling page when a userid/password is entered.
//
//  If the userid supplied corresponds to a non-existent account:
//
//     a)Destroy any existing server-side session information based on the current SID cookie.
//     b)Eat the current SID cookie, if any, on the client side.
//     c)Set the $curuserinfo to FALSE.
//     d)Set the $cursessioninfo to FALSE.
//     e)Set the $rcode to SESS_RCODE_FAIL_USERID_NOEXIST.
//
//  Else if the userid exists and the password authenticates:
//
//     If the account is inactive or expired:
//
//        a)Destroy any existing server-side session information based on the current SID
//          cookie.
//        b)Eat the current SID cookie, if any, on the client side.
//        c)Set the $curuserinfo to FALSE.
//        d)Set the $cursessioninfo to FALSE.
//        e)Set the $rcode to SESS_RCODE_FAIL_USERID_EXPIRED_INACTIVE.
//
//     Else if authentication was successful based on a temporary password:
//
//        a)Destroy any existing server-side session information based on the current SID
//          cookie.
//        b)Open a new session on the server side.
//        c)Issue a new SID cookie to the client.
//        d)Set the $curuserinfo to the user specified.
//        e)Set the $cursessioninfo to the newly-created session.
//        f)Set the $rcode to SESS_RCODE_SUCCESS_TEMP_PASSWORD.
//
//     Else if authentication was successful:
//
//        a)Destroy any existing server-side session information based on the current SID
//          cookie.
//        b)Open a new session on the server side.
//        c)Issue a new SID cookie to the client.
//        d)Set the $curuserinfo to the user specified.
//        e)Set the $cursessioninfo to the newly-created session.
//        f)Set the $rcode to SESS_RCODE_SUCCESS.
//
//  Else if the userid exists but the password does not authenticate:
//
//     a)Destroy any existing server-side session information based on the current SID
//       cookie.
//     b)Eat the current SID cookie, if any, on the client side.
//     c)Set the $curuserinfo to FALSE.
//     d)Set the $cursessioninfo to FALSE.
//     e)Set the $rcode to SESS_RCODE_FAIL_PASSWD.
//
//Return Value:
//  $rcode          : Set to a constant defined at the start of this file to indicate
//                    what occurred.
//  $curuserinfo    : Set to an associative array containing full user information
//                    about a user who logs in, or FALSE if no user has successfully
//                    authenticated.
//  $cursessioninfo : An associative array containing the complete record for the now
//                    active session, or FALSE if no session is active.
//
function SESS_userid_pwd_authenticate_open_session($userid, $password, &$rcode, &$curuserinfo, &$cursessioninfo)
   {
   global $PAR_fbopsid;
   global $GLOBAL_stime_string; 
   global $GLOBAL_client_ip;

   //Condition the userid to exclude forbidden characters.
   $userid = STRFUNC_force_into_subset($userid, "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");

   //Convert the userid to all lower-case.  This is the canonical form for userids.
   $userid = StrToLower($userid);

   //Remove all invalid characters from the password.  However, don't convert it to lower-case.  Passwords are
   //case-sensitive.
   $password = STRFUNC_force_into_subset($password, "-0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");

   //Try to obtain the user information from the database corresponding to the userid.
   $curuserinfo =  USRS_retrieve_by_userid($userid);

   //print_r($curuserinfo);
   //return;

   //If the userid does not exist, return the correct error code.
   if ($curuserinfo === FALSE)
      {
      //Log the authentication failure.
      LOG_log(LOG_ET_LOGIN_FAIL, 
              $GLOBAL_stime_string, 
              $GLOBAL_client_ip, 
              "", 
              ($PAR_fbopsid === FALSE) ? ("") : ($PAR_fbopsid), 
              $_SERVER["PHP_SELF"],
              "",
              __FILE__,
              __LINE__,
              "Password authentication failure, non-existent userid=\"" .  $userid . "\".");

      //Destroy any existing server-side session information based on the current SID cookie.
      if ($PAR_fbopsid !== FALSE)
         SESS_delete_by_sid($PAR_fbopsid);

      //Eat the client-side cookie.
      SESS_eat_fbopsid_cookie();

      //Set the $curuserinfo to FALSE.
      $curuserinfo = FALSE;

      //Set the $cursessioninfo to FALSE.
      $cursessioninfo = FALSE;
 
      //Set the $rcode to SESS_RCODE_FAIL_USERID_NOEXIST.
      $rcode = SESS_RCODE_FAIL_USERID_NOEXIST;

      return;
      }

   //If the userid exists but is not active, refuse the authentication.
   if ($curuserinfo["status"] != USRS_STATUS_ACTIVE)
      {
      //Log the authentication failure.
      LOG_log(LOG_ET_LOGIN_FAIL, 
              $GLOBAL_stime_string, 
              $GLOBAL_client_ip, 
              "", 
              ($PAR_fbopsid === FALSE) ? ("") : ($PAR_fbopsid), 
              $_SERVER["PHP_SELF"],
              "",
              __FILE__,
              __LINE__,
              "Password authentication failure, expired or inactive userid=\"" .  $userid . "\".");

      //Destroy any existing server-side session information based on the current SID cookie.
      if ($PAR_fbopsid !== FALSE)
         SESS_delete_by_sid($PAR_fbopsid);

      //Eat the client-side cookie.
      SESS_eat_fbopsid_cookie();

      //Set the $curuserinfo to FALSE.
      $curuserinfo = FALSE;

      //Set the $cursessioninfo to FALSE.
      $cursessioninfo = FALSE;
 
      //Set the $rcode to SESS_RCODE_FAIL_USERID_EXPIRED_INACTIVE.
      $rcode = SESS_RCODE_FAIL_USERID_EXPIRED_INACTIVE;

      return;
      }

   //The user exists and the user's status is active.  Figure out if the password is consistent
   //with the stored non-temporary password.
   //
   if (SESS_nontemppwauth($curuserinfo, $password))
      {
      //The password supplied matches the non-temporary password hash in the database.
      //
      //Open a new session on the server side.
      $sid = SESS_open_new_uinfo($curuserinfo);
      //
      //Log the authentication success.
      LOG_log(LOG_ET_LOGIN_OK, 
              $GLOBAL_stime_string, 
              $GLOBAL_client_ip, 
              $userid, 
              $sid, 
              $_SERVER["PHP_SELF"],
              "",
              __FILE__,
              __LINE__,
              "Password authentication.");
      //
      //Issue the new cookie to the browser.  It isn't necessary to replace any existing old,
      //as this one will just replace it.
      SESS_issue_fbopsid_cookie($sid);
      //
      //The current user information has already been obtained.  Pull the
      //session information.
      $cursessioninfo = SESS_retrieve_by_sid($sid);
      //
      //Set the return code.
      $rcode = SESS_RCODE_SUCCESS;
      //
      return;
      }


   //The user exists and the user's status is active.  Figure out if the password is consistent
   //with the stored temporary password.
   //
   if (SESS_temppwauth($curuserinfo, $password))
      {
      //The password supplied matches the temporary password hash in the database.
      //
      //Open a new session on the server side.
      $sid = SESS_open_new_uinfo($curuserinfo);
      //
      //Log the authentication success.
      LOG_log(LOG_ET_LOGIN_OK, 
              $GLOBAL_stime_string, 
              $GLOBAL_client_ip, 
              $userid, 
              $sid, 
              $_SERVER["PHP_SELF"],
              "",
              __FILE__,
              __LINE__,
              "Temporary password authentication.");
      //
      //Issue the new cookie to the browser.  It isn't necessary to replace any existing old,
      //as this one will just replace it.
      SESS_issue_fbopsid_cookie($sid);
      //
      //The current user information has already been obtained.  Pull the
      //session information.
      $cursessioninfo = SESS_retrieve_by_sid($sid);
      //
      //Set the return code.
      $rcode = SESS_RCODE_SUCCESS_TEMP_PASSWORD;
      //
      return;
      }

   //If we're here, the userid was OK, but the password was wrong.
   //Log the authentication failure.
   LOG_log(LOG_ET_LOGIN_FAIL, 
           $GLOBAL_stime_string, 
           $GLOBAL_client_ip, 
           $userid, 
           ($PAR_fbopsid === FALSE) ? ("") : ($PAR_fbopsid),
           $_SERVER["PHP_SELF"],
           "",
           __FILE__,
           __LINE__,
           "Password authentication failure, bad password.");

   //Destroy any existing server-side session information based on the current SID cookie.
   if ($PAR_fbopsid !== FALSE)
      SESS_delete_by_sid($PAR_fbopsid);

   //Eat the client-side cookie.
   SESS_eat_fbopsid_cookie();

   //Set the $curuserinfo to FALSE.
   $curuserinfo = FALSE;

   //Set the $cursessioninfo to FALSE.
   $cursessioninfo = FALSE;
 
   //Set the $rcode to indicate simple password failure.
   $rcode = SESS_RCODE_FAIL_PASSWD;
   }
//
//--------------------------------------------------------------------------------------------------------------
//Logs out the user implied by the current SID cookie.  The specific actions are:
//  a)Destroy any existing server-side session information.
//  b)Eat the client side SID cookie.
//
//Return Values:
//   $curuserinfo        :  By the definition of this what this function does, FALSE.
//   $cursessioninfo     :  By the definition of this what this function does, FALSE.
//
function SESS_logout(&$curuserinfo, &$cursessioninfo)
   {
   global $PAR_fbopsid;
   global $GLOBAL_stime_string; 
   global $GLOBAL_client_ip;

   //Save the $sid cookie, so we can log it.
   $log_sid = $PAR_fbopsid;

   //Look up the session table entry.
   $cursessioninfo = SESS_retrieve_by_sid($log_sid);

   //Look up the user information based on the index stored with
   //the session.
   if ($cursessioninfo !== FALSE)
      {
      $curuserinfo = USRS_retrieve_by_idx($cursessioninfo["usrsidx"]);
      }
   else
      {
      $curuserinfo = FALSE;
      }

   //Swallow any session cookie.
   SESS_eat_fbopsid_cookie();

   //Destroy the server-side session state, if any.
   if ($PAR_fbopsid !== FALSE)
     SESS_delete_by_sid($PAR_fbopsid);

   //Log the voluntary logout.
   LOG_log(LOG_ET_LOGOUT_VOL, 
           $GLOBAL_stime_string, 
           $GLOBAL_client_ip, 
           ($curuserinfo !== FALSE) ? ($curuserinfo["userid"]) : (""), 
           ($log_sid === FALSE) ? ("") : ($log_sid), 
           $_SERVER["PHP_SELF"],
           "",
           __FILE__,
           __LINE__,
           "Logout.");


   //Return values are, by definition, FALSE.
   $curuserinfo    = FALSE;
   $cursessioninfo = FALSE;
   }
//
//--------------------------------------------------------------------------------------------------------------
//Revalidates the session using the current SID cookie.  The specific actions are:
//
//   If the SID does not exist on the server side:
//      a)Eat the current client SID cookie.
//   Else if the session has expired due to inactivity:
//      a)Destroy the server-side session state.
//      b)Eat the client-side SID cookie.
//   Else [if the session is still active]:
//      Obtain the user information.
//      If the user does not exist or is inactive:
//         a)Destroy the server-side session state.
//         b)Eat the client-side SID cookie.
//      Else
//         If the privilege escalation period has expired
//            Lower the privelege escalation level.
//         Update the revalidation time.
//
//Return Values:
//   $curuserinfo        :  An associative array containing the complete record for the currently
//                          authenticated user, or FALSE if no user is authenticated.
//   $cursessioninfo     :  An associative array containing the complete record for the currently
//                          active session, or FALSE if no session is active.
//
function SESS_revalidate(&$curuserinfo, &$cursessioninfo)
   {
   global $GLOBAL_dbhandle;
   global $GLOBAL_dblocked;
   global $PAR_fbopsid;
   global $GLOBAL_stime_string; 
   global $GLOBAL_client_ip;
   global $GLOBAL_utime_ut;

   $cursessioninfo = FALSE;
   $curuserinfo    = FALSE;

   //If the SID isn't defined, no user and no session.
   if ($PAR_fbopsid === FALSE)
      {
      $curuserinfo    = FALSE;
      $cursessioninfo = FALSE;
      return;
      }

   //Try to look up the session in the database.  If it does not exist
   //in the database, this is a bit suspicious but not impossible.  The database
   //could have been reaped while somebody left their browser open for a long time.
   //If this is the case, no session and no user.
   //
   $cursessioninfo = SESS_retrieve_by_sid($PAR_fbopsid);
   //
   if ($cursessioninfo === FALSE)
      {
      //It is suspicious.  Log it.
      LOG_log(LOG_ET_SEC_SID_FORGED, 
              $GLOBAL_stime_string, 
              $GLOBAL_client_ip, 
              "", 
              $PAR_fbopsid, 
              $_SERVER["PHP_SELF"],
              "",
              __FILE__,
              __LINE__,
              "SID cookie value does not exist in server database, and was possibly forged.");

      //Return value is no session and no user.
      $curuserinfo    = FALSE;
      $cursessioninfo = FALSE;
      return;
      }

   //Session exists.  Try to look up the user identified in the session.  If the user does not
   //exist, this is also suspicious.  The only scenario under which this might happen is if a
   //user is expired or deleted during a session.
   //   
   $curuserinfo    = USRS_retrieve_by_idx($cursessioninfo["usrsidx"]);
   //
   if ($curuserinfo === FALSE)
      {
      //It is suspicious.  Log it.
      LOG_log(LOG_ET_SEC_SID_FORGED, 
              $GLOBAL_stime_string, 
              $GLOBAL_client_ip, 
              "", 
              $PAR_fbopsid, 
              $_SERVER["PHP_SELF"],
              "",
              __FILE__,
              __LINE__,
              "User index pointed to by SID record does not exist (idx=" . (string)$cursessioninfo["usrsidx"] . ").");

      //Return value is no session and no user.
      $curuserinfo    = FALSE;
      $cursessioninfo = FALSE;
      return;
      }
   
   //If the user pointed to by the session isn't active, this probably means that
   //the user was expired or had the status changed manually during a session.
   //Destroy the server-side and client side session state, log it, and indicate
   //to the caller no user and no session.
   //If the userid exists but is not active, refuse the authentication.
   if ($curuserinfo["status"] != USRS_STATUS_ACTIVE)
      {
      //It is suspicious.  Log it.
      LOG_log(LOG_ET_SEC_SID_FORGED, 
              $GLOBAL_stime_string, 
              $GLOBAL_client_ip, 
              "", 
              $PAR_fbopsid, 
              $_SERVER["PHP_SELF"],
              "",
              __FILE__,
              __LINE__,
              "User pointed to by SID record has inactive status (idx=" . (string)$cursessioninfo["usrsidx"] . ").");

      //Destroy any existing server-side session information based on the current SID cookie.
      if ($PAR_fbopsid !== FALSE)
         SESS_delete_by_sid($PAR_fbopsid);

      //Eat the client-side cookie.
      SESS_eat_fbopsid_cookie();

      //Return value is no session and no user.
      $curuserinfo    = FALSE;
      $cursessioninfo = FALSE;
      return;
      }

   //If the session has expired due to time, then log it and force the user out.
   //
   if (UTIME_time_diff_coarse_28($GLOBAL_utime_ut, $cursessioninfo["revaltime"]) > (int)$cursessioninfo["lifetime"])
      {
      //Log it.
      LOG_log(LOG_ET_LOGOUT_TIME,
              $GLOBAL_stime_string, 
              $GLOBAL_client_ip,
              $curuserinfo["userid"],
              $PAR_fbopsid,
              $_SERVER["PHP_SELF"],
              "",
              __FILE__,
              __LINE__,
              "Session expired due to inactive time.");

      //Destroy any existing server-side session information based on the current SID cookie.
      if ($PAR_fbopsid !== FALSE)
         SESS_delete_by_sid($PAR_fbopsid);

      //Eat the client-side cookie.
      SESS_eat_fbopsid_cookie();

      //Return value is no session and no user.
      $curuserinfo    = FALSE;
      $cursessioninfo = FALSE;
      return;
      }

   //If the connecting IP of the session has changed, this is bad news and probably some type of
   //security issue.
   //
   if ($cursessioninfo["ip"] != $GLOBAL_client_ip)
      {
      //Log it.
      LOG_log(LOG_ET_SEC_LOGOUT_IP,
              $GLOBAL_stime_string, 
              $GLOBAL_client_ip,
              $curuserinfo["userid"],
              $PAR_fbopsid,
              $_SERVER["PHP_SELF"],
              "",
              __FILE__,
              __LINE__,
              "Stored session IP:" . $cursessioninfo["ip"] . " Current connection IP:" . $GLOBAL_client_ip . ".");

      //Destroy any existing server-side session information based on the current SID cookie.
      if ($PAR_fbopsid !== FALSE)
         SESS_delete_by_sid($PAR_fbopsid);

      //Eat the client-side cookie.
      SESS_eat_fbopsid_cookie();

      //Return value is no session and no user.
      $curuserinfo    = FALSE;
      $cursessioninfo = FALSE;
      return;
      }

   //All the error conditions have been ruled out.  Give the session a newer timestamp, log it, and return the
   //correct user and session information.
   mysql_query("UPDATE sess SET revaltime=\""
               . mysql_real_escape_string($GLOBAL_utime_ut, $GLOBAL_dbhandle)
               . "\" WHERE sid=\""
               . mysql_real_escape_string($PAR_fbopsid, $GLOBAL_dbhandle)
               . "\"",
               $GLOBAL_dbhandle);
   //
   LOG_log(LOG_ET_REVAL_OK,
           $GLOBAL_stime_string, 
           $GLOBAL_client_ip,
           $curuserinfo["userid"],
           $PAR_fbopsid,
           $_SERVER["PHP_SELF"],
           "",
           __FILE__,
           __LINE__,
           "Session revalidation.");

   //The $curuserinfo and $cursessioninfo values are OK for return.
   }
//
//--------------------------------------------------------------------------------------------------------------
//Decrements the current menu level, stores it in the correct session record of the database,
//and returns the new level, clipped to [0, 2].
//
//No mutual exclusion should be necessary, as a session is tied to one terminal IP--unless a user
//has multiple browsers open and is doing something unusual, there should be nothing noticeable.
//Even then it is iffy and there will be no ill effects.
//
function SESS_menulevel_decrement($sid_in, $menulevel_current)
   {
   global $GLOBAL_dbhandle;

   //Adjust the menulevel to be one smaller.
   if ($menulevel_current == 2)
      $menulevel_new = 1;
   else if ($menulevel_current == 1)
      $menulevel_new = 0;
   else
      $menulevel_new = 0;

   //Form a query to reflect assigning the new menu level to the session ID
   //record.
   $query_string = "UPDATE sess SET menulvl=\"" . (string)$menulevel_new . "\" WHERE sid=\"" . $sid_in . "\"";

   //Run the query.  We don't much care whether it fails or succeeds (nothing to be done, anyway).
   mysql_query($query_string, $GLOBAL_dbhandle);

   //Return the new value.
   return($menulevel_new); 
   }
//
//--------------------------------------------------------------------------------------------------------------
//Increments the current menu level, stores it in the correct session record of the database,
//and returns the new level, clipped to [0, 2].
//
//No mutual exclusion should be necessary, as a session is tied to one terminal IP--unless a user
//has multiple browsers open and is doing something unusual, there should be nothing noticeable.
//Even then it is iffy and there will be no ill effects.
//
function SESS_menulevel_increment($sid_in, $menulevel_current)
   {
   global $GLOBAL_dbhandle;

   //Adjust the menulevel to be one larger.
   if ($menulevel_current == 0)
      $menulevel_new = 1;
   else if ($menulevel_current == 1)
      $menulevel_new = 2;
   else
      $menulevel_new = 2;

   //Form a query to reflect assigning the new menu level to the session ID
   //record.
   $query_string = "UPDATE sess SET menulvl=\"" . (string)$menulevel_new . "\" WHERE sid=\"" . $sid_in . "\"";

   //Run the query.  We don't much care whether it fails or succeeds (nothing to be done, anyway).
   mysql_query($query_string, $GLOBAL_dbhandle);

   //Return the new value.
   return($menulevel_new); 
   }
//
//--------------------------------------------------------------------------------------------------------------
//Updates the SDDT and SDTIM associated with the session, session identifier passed.
//
//To update only SDDT or SDTIM, set the other parameter FALSE.
//
//If both parameters are FALSE, nothing will be updated.
//
function SESS_update_sddt_sdtim($sid_in, $sddt_in, $sdtim_in)
   {
   global $GLOBAL_dbhandle;

   //echo "<pre>\n";
   //print_r($sid_in);
   //print_r($sddt_in);
   //print_r($sdtim_in);
   //echo "</pre>\n";

   if (($sddt_in !== FALSE) && ($sdtim_in !== FALSE))
      {
      //Both parameters are specified, the most common case.
      $query_string = "UPDATE sess SET sddt=\"" 
                      . 
                      mysql_real_escape_string ((string)$sddt_in, $GLOBAL_dbhandle) 
                      . 
                      "\", sdtim=\""
                      . 
                      mysql_real_escape_string ((string)$sdtim_in, $GLOBAL_dbhandle)
                      .
                      "\" WHERE sid=\"" 
                      . 
                      $sid_in 
                      . 
                      "\"";

      //Run the query.  We don't much care whether it fails or succeeds (nothing to be done, anyway).
      mysql_query($query_string, $GLOBAL_dbhandle);
      }
   else if (($sddt_in === FALSE) && ($sdtim_in !== FALSE))
      {
      //Only time is specified.
      $query_string = "UPDATE sess SET sdtim=\""
                      . 
                      mysql_real_escape_string ((string)$sdtim_in, $GLOBAL_dbhandle)
                      .
                      "\" WHERE sid=\"" 
                      . 
                      $sid_in 
                      . 
                      "\"";

      //Run the query.  We don't much care whether it fails or succeeds (nothing to be done, anyway).
      mysql_query($query_string, $GLOBAL_dbhandle);
      }
   else if (($sddt_in !== FALSE) && ($sdtim_in === FALSE))
      {
      //Only date is specified.
      $query_string = "UPDATE sess SET sddt=\"" 
                      . 
                      mysql_real_escape_string ((string)$sddt_in, $GLOBAL_dbhandle) 
                      . 
                      "\" WHERE sid=\"" 
                      . 
                      $sid_in 
                      . 
                      "\"";

      //Run the query.  We don't much care whether it fails or succeeds (nothing to be done, anyway).
      mysql_query($query_string, $GLOBAL_dbhandle);
      }
   else
      {
      //Do nothing.  Neither parameter is specified.
      }
   }
//
//--------------------------------------------------------------------------------------------------------------
//Updates the logicalpage associated with a session.
//
function SESS_logicalpage_set($sid_in, $logicalpage_in)
   {
   global $GLOBAL_dbhandle;

   $query_string = "UPDATE sess SET logicalpage=\"" 
                   . 
                   mysql_real_escape_string ((string)$logicalpage_in, $GLOBAL_dbhandle) 
                   . 
                   "\" WHERE sid=\"" 
                   . 
                   $sid_in 
                   . 
                   "\"";

   //Run the query.  We don't much care whether it fails or succeeds (nothing to be done, anyway).
   mysql_query($query_string, $GLOBAL_dbhandle);
   }
//
//--------------------------------------------------------------------------------------------------------------
//Gets the logicalpage integer associated with a session.  Returns SESS_LPAGE_UNDEFINED if can't figure
//out what that is.
//
function SESS_logicalpage_get($sid_in)
   {
   global $GLOBAL_dbhandle;

   //Form the query string.
   $query_string = "SELECT logicalpage FROM sess WHERE sid=\""
                   .
                   mysql_real_escape_string($sid_in, $GLOBAL_dbhandle)
                   .
                   "\"";

   //Execute the query.
   $result = mysql_query($query_string, $GLOBAL_dbhandle);

   if ($result === FALSE)
      {
      //Unknown query failure.  Return a result code to the caller indicating
      //don't know.
      return(SESS_LPAGE_UNDEFINED);
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
         return(SESS_LPAGE_UNDEFINED);
      }
   }
//
//--------------------------------------------------------------------------------------------------------------
//End of $RCSfile: sess.inc,v $.
//--------------------------------------------------------------------------------------------------------------
?>
