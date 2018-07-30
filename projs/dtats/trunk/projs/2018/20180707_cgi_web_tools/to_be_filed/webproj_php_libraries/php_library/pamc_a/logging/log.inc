<?php
//********************************************************************************
//Copyright (C)2006 David T. Ashley
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
//Dave Ashley, 01/06
//
//This source file is a wrapper for functions that emit information into the
//log files.
//
//Replaces unruly characters with the underscore.
//
function LOG_replace_unruly_chars($arg)
   {
   $allowed_chars = "abcdefghijklmnopqrstuvwxyz" .
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ" .
                    "0123456789"                 .
                    " .,_:;-+*/"                 .
                    "()[]";

   $len = strlen($arg);
   $rv = "";

   for ($i = 0; $i < $len; $i++)
      {
      $c = substr($arg, $i, 1);

      if (strpos($allowed_chars, $c) === FALSE)
         {
         //The character involved isn't in the allowed set.  Replace it with an underscore.
         $rv .= "_";
         }
      else
         {
         //The character involved is allowed.  Put it directly in the result.
         $rv .= $c;
         }
      }

   return($rv);
   }
//
//
//Writes environmental information to the log file that may be helpful in error or
//security debugging.
//
function LOG_log_environment($prefix)
   {
   //Copy the server arguments.  Don't want to accidentally change something.
   $tgt = $_SERVER;

   //Reset to first value.
   reset($tgt);

   //Loop through, emitting args.
   while (list($key, $val) = each($tgt)) 
      {
      syslog(
            LOG_NOTICE,
            $prefix
            . "_SERVER[\""
            . $key
            . "\"]: "
            . $val
            );
      }
   //-----------------------------------------------------------------------
   //Copy the environment arguments.  Don't want to accidentally change something.
   $tgt = $_ENV;

   //Reset to first value.
   reset($tgt);

   //Loop through, emitting args.
   while (list($key, $val) = each($tgt)) 
      {
      syslog(
            LOG_NOTICE,
            $prefix
            . "_ENV[\""
            . $key
            . "\"]: "
            . $val
            );
      }
   //-----------------------------------------------------------------------
   //Copy the request arguments.  Don't want to accidentally change something.
   $tgt = $_REQUEST;

   //Reset to first value.
   reset($tgt);

   //Loop through, emitting args.
   while (list($key, $val) = each($tgt)) 
      {
      syslog(
            LOG_NOTICE,
            $prefix
            . "_REQUEST[\""
            . $key
            . "\"]: "
            . $val
            );
      }
   }
//
//
//Writes the debug backtrace information to the log file.
//
function LOG_log_debug_backtrace($prefix)
   {
   //Grab backtrace.
   $bt = debug_backtrace();

   //Iterate through each element.
   reset($bt);
   $i=0;
   while (list($key, $val) = each($bt))
      {
      //Spit the function name.
      if (isset($val["function"]))
         syslog(LOG_NOTICE, $prefix . "FUNCTION[" . sprintf("%02d", $i) . "]: " . $val["function"]);
      else
         syslog(LOG_NOTICE, $prefix . "No function name specified in traceback.");

      //Spit the file name.
      if (isset($val["file"]))
         syslog(LOG_NOTICE, $prefix . "FILE    [" . sprintf("%02d", $i) . "]: " . $val["file"]);
      else
         syslog(LOG_NOTICE, $prefix . "No file name specified in traceback.");

      //Spit the line number.
      if (isset($val["line"]))
         syslog(LOG_NOTICE, $prefix . "LINE    [" . sprintf("%02d", $i) . "]: " . $val["line"]);
      else
         syslog(LOG_NOTICE, $prefix . "No line number specified in traceback.");

      $i++;
      }
   }
//
//
//Writes a horizontal line to the log file.
//
function LOG_log_hline($prefix)
   {
   $val = $prefix;
   
   for ($i=0; $i<80; $i++)
      {
      $val .= "-";
      }

   error_log($val);
   }
//
//Emits "hard" error messages.  An "error" for these purposes is a very unexpected event,
//such as not being able to connect to a database, conditions that should not
//occur, etc.  This includes a backtrace.
//
function LOG_error_hard($msgstring)
   {
   $prefix = "PAMC_ERROR_HARD: ";

   //Sanitize the input string to allow only certain characters.
   $msgstring = LOG_replace_unruly_chars($msgstring);

   //Open with a horizontal line.
   LOG_log_hline($prefix);

   //Insert the message.
   syslog(LOG_NOTICE, $prefix . $msgstring);

   //Do the backtrace.
   LOG_log_debug_backtrace($prefix);

   //Log the environment.
   LOG_log_environment($prefix);

   //Close with a horizontal line.
   LOG_log_hline($prefix);
   }
//
//Emits "soft" error messages.  An "error" for these purposes is a very unexpected event,
//such as not being able to connect to a database, conditions that should not
//occur, etc.  This does not include a backtrace.
//
function LOG_error_soft($msgstring)
   {
   $prefix = "PAMC_ERROR_SOFT: ";

   //Sanitize the input string to allow only certain characters.
   $msgstring = LOG_replace_unruly_chars($msgstring);

   //Insert the message.
   syslog(LOG_NOTICE, $prefix . $msgstring);
   }
//
//Emits security messages.  An "security" message is something security-related.
//
function LOG_security($msgstring)
   {
   $prefix = "PAMC_SECURITY: ";

   //Sanitize the input string to allow only certain characters.
   $msgstring = LOG_replace_unruly_chars($msgstring);

   //Open with a horizontal line.
   LOG_log_hline($prefix);

   //Insert the message.
   syslog(LOG_NOTICE, $prefix . $msgstring);

   //Log the environment.
   LOG_log_environment($prefix);

   //Close with a horizontal line.
   LOG_log_hline($prefix);
   }
//
//Emits alert messages.  An "alert" message is something significant that one
//might want to look into.
//
function LOG_alert($msgstring)
   {
   $prefix = "PAMC_ALERT: ";

   //Sanitize the input string to allow only certain characters.
   $msgstring = LOG_replace_unruly_chars($msgstring);

   //Insert the message.
   syslog(LOG_NOTICE, $prefix . $msgstring);
   }
//
//Emits informational messages.  An "informational" message is just something ordinary
//that occurs.
//
function LOG_info($msgstring)
   {
   $prefix = "PAMC_INFO: ";

   //Sanitize the input string to allow only certain characters.
   $msgstring = LOG_replace_unruly_chars($msgstring);

   //Insert the message.
   syslog(LOG_NOTICE, $prefix . $msgstring);
   }
?>
