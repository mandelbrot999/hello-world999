<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/log.inc 205 2018-07-15 19:00:51Z dashley $
//--------------------------------------------------------------------------------------------------------------
//log.inc--FboPrime Logging Functions and Constants
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
//This contains functions used to log events, both to the loge table of the
//database, and to the system log.
//--------------------------------------------------------------------------------------------------------------
require_once("global.inc");
require_once("strfunc.inc");
require_once("utime.inc");
//
//--------------------------------------------------------------------------------------------------------------
//Different types of log entries that can be made.
//------------------------------------------------
//These can be differentiated into categories using integer division, code / 10.
//
//Unknown or miscellaneous log entries.
   define("LOG_ET_UNKNOWN_MISC",                     0);  //Unknown or miscellaneous.
//Page statistics.
   define("LOG_ET_PAGEHIT",                         10);  //Ordinary page hit.
//Database connection or authentication problems.
   define("LOG_ET_ERRDBCONN",                       20);  //An error connecting or authenticating to the
                                                          //MySQL database.
//Authentication and authentication failures.
   define("LOG_ET_LOGIN_OK",                        30);  //Login of a user.
   define("LOG_ET_LOGIN_FAIL",                      31);  //Login failure.
   define("LOG_ET_LOGOUT_VOL",                      32);  //Voluntary user logout.
   define("LOG_ET_LOGOUT_TIME",                     33);  //Forced logout due to time.
   define("LOG_ET_REVAL_OK",                        34);  //Session revalidated successfully.
//Security threats.
   define("LOG_ET_SEC_SID_FORGED",                  40);  //An apparently forged or otherwise tampered SID.
   define("LOG_ET_SEC_LOGOUT_IP",                   41);  //Forced logout due to an IP that has changed
//Maintenance entries.
   define("LOG_ET_MAINT_PERIODIC",                  50);  //An ordinary periodic maintenance entry.
//Internal server or software errors.
   define("LOG_ET_UNCATEGORIZED",                  100);  //Errors not otherwise specified.
   define("LOG_ET_INVALID_SPECIFIED",              200);  //Errors not otherwise specified.
//
//--------------------------------------------------------------------------------------------------------------
//Inserts a log entry into the MySQL log.
//  type         :  Enumerated type.
//  stime        :  STIME time stamp, time page started.
//  ip           :  The IP address on record with the server.
//  userid       :  The userid of the currently logged in user (text string).
//  sid          :  The current session identifier.
//  scriptfile   :  The PHP script being executed, usually obtained by PHP_SELF.
//  getpostpars  :  The GET/POST parameters to the script.
//  phpfilek     :  The PHP __FILE__ directive from the caller.
//  phplinek     :  The PHP __LINE__ directive from the caller.
//  logentry     :  The log entry itself.
//
function LOG_log($type, $stime, $ip, $userid, $sid, $scriptfile, $getpostpars, $phpfilek, $phplinek, $logentry)
   {
   global $GLOBAL_dbhandle;  //Database handle.

   //Obtain the Unix timestamp.
   $utime = UTIME_utime();

   //Sanitize the type of log entry.  It can only be certain types.  If it
   //isn't valid, flag it as invalidly specified at the interface.
   $type = LOG_force_type_set($type);

   //if (is_string($stime))
   //   echo " is string ";

   //echo " ? " . strlen($stime) . " ? ";
   //echo " ! " . $stime . " ! ";

   //Sanitize the STIME.
   $stime = STRFUNC_force_stringtype_subset_truncate($stime, "ST0123456789", 22);

   //echo " * " . strlen($stime) . " * ";
   //echo " @ " . $stime . " @ ";

   //Sanitize the IP.
   $ip = STRFUNC_force_stringtype_subset_truncate($ip, ".ABCDEFabcdef0123456789", 40);

   //Sanitize the user id.
   $userid = STRFUNC_force_stringtype_subset_truncate
                (
                $userid, 
                "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ",  
                20
                );

   //Sanitize the session identifier.
   $sid = STRFUNC_force_stringtype_subset_truncate($sid, "SISG0123456789abcdefABCDEF", 66);

   //Sanitize the scriptfile.
   $scriptfile = STRFUNC_force_stringtype_subset_truncate($scriptfile, 
                                                          "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-._/",
                                                          1024);

   //Sanitize the getpost pars.
   $getpostpars = STRFUNC_force_stringtype_subset_truncate
                  (
                  $getpostpars, 
                  "0123456789"                                               //Digits
                  . "abcdefghijklmnopqrstuvwxyz"                             //Lower-case letters
                  . "ABCDEFGHIJKLMNOPQRSTUVWXYZ"                             //Upper-case letters
                  . " "                                                      //Spaces
                  . "(){}_.,;:-+*/=@\"'",                                    //Punctuation
                  1024);

   //Sanitize the phpfilek.
   $phpfilek = STRFUNC_force_stringtype_subset_truncate($phpfilek, 
                                                        "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-._/",
                                                        1024);

   //Sanitize the phplinek.
   $phplinek = STRFUNC_force_stringtype_subset_truncate((string)$phplinek,
                                                        "0123456789",
                                                        1024);

   //Sanitize the log entry itself.
   $logentry = STRFUNC_force_stringtype_subset_truncate
                  (
                  $logentry, 
                  "0123456789"                                               //Digits
                  . "abcdefghijklmnopqrstuvwxyz"                             //Lower-case letters
                  . "ABCDEFGHIJKLMNOPQRSTUVWXYZ"                             //Upper-case letters
                  . " "                                                      //Spaces
                  . "<>(){}_.,;:-+*/=@\"'\$",                                //Punctuation
                  4000);

   //Issue the MySQL query.
   mysql_query("INSERT INTO loge SET type=" . $type . 
               ", utime=\""       .  $utime                                                    . "\" " .
               ", stime=\""       .  mysql_real_escape_string ($stime, $GLOBAL_dbhandle)       . "\" " .
               ", ip=\""          .  mysql_real_escape_string ($ip, $GLOBAL_dbhandle)          . "\" " .
               ", userid=\""      .  mysql_real_escape_string ($userid, $GLOBAL_dbhandle)      . "\" " .
               ", sid=\""         .  mysql_real_escape_string ($sid, $GLOBAL_dbhandle)         . "\" " .
               ", scriptfile=\""  .  mysql_real_escape_string ($scriptfile, $GLOBAL_dbhandle)  . "\" " .
               ", getpostpars=\"" .  mysql_real_escape_string ($getpostpars, $GLOBAL_dbhandle) . "\" " .
               ", phpfilek=\""    .  mysql_real_escape_string ($phpfilek, $GLOBAL_dbhandle)    . "\" " .
               ", phplinek=\""    .  mysql_real_escape_string ($phplinek, $GLOBAL_dbhandle)    . "\" " .
               ", logentry=\""    .  mysql_real_escape_string ($logentry, $GLOBAL_dbhandle)    . "\"",
               $GLOBAL_dbhandle);
   }
//
//
//--------------------------------------------------------------------------------------------------------------
//Forces a log entry type into a valid type and range.  Return value is the
//sanitized value.
//
function LOG_force_type_set($type)
   {
   if (!is_int($type))
      {
      //It is not an integer.  Flag this as invalid.
      $type = (int) LOG_ET_INVALID_SPECIFIED;
      }
   else
      {
      //It is an integer.  Force it into set of allowed values.
      switch($type)
         {
         case LOG_ET_UNKNOWN_MISC:
         case LOG_ET_PAGEHIT:
         case LOG_ET_ERRDBCONN:
         case LOG_ET_LOGIN_OK:
         case LOG_ET_LOGIN_FAIL:
         case LOG_ET_LOGOUT_VOL:
         case LOG_ET_LOGOUT_TIME:
         case LOG_ET_REVAL_OK:
         case LOG_ET_SEC_SID_FORGED:
         case LOG_ET_SEC_LOGOUT_IP:
         case LOG_ET_MAINT_PERIODIC:
         case LOG_ET_UNCATEGORIZED:
         case LOG_ET_INVALID_SPECIFIED:
            //Do nothing.  This is already in bounds.
            break;
         default:
            //It is out of range.  Force it in.
            $type = (int) LOG_ET_INVALID_SPECIFIED;
         }
      }

   //Sanitization is complete.  Return it.
   return($type);
   }
//
//--------------------------------------------------------------------------------------------------------------
//Makes a system log entry, with a constant prefix.
//
function LOG_syslog($text)
   {
   syslog(LOG_WARNING, CONFIG_MYSQL_ERR_SYSLOG_PREFIX . ": " . $text);
   }
//
//--------------------------------------------------------------------------------------------------------------
//End of $RCSfile: log.inc,v $.
//--------------------------------------------------------------------------------------------------------------
?>
