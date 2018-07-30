<?php
//------------------------------------------------------------------------
//Marshall Aviation Center FBO Management Software
//Copyright (C)2005 David T. Ashley
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
//
//The author (David T. Ashley) may be contacted by e-mail at dta@e3ft.com
//and by postal mail at P.O. Box 918, Marshall MI 49068.
//------------------------------------------------------------------------
//Logging functions.
//
//These are written to the Apache error log.
//------------------------------------------------------------------------
//Defines the character membership for things that can be placed into
//system logs.
//
function slog_char_membership($c)
   {
   if (strstr(" ,.;:+-*/0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", $c))
      return(1);
   else
      return(0);
   }

//------------------------------------------------------------------------
//Forces a string into the set of characters allowed for logging.
//
function slog_logstring_member_force($s_in)
   {
   $len = strlen($s_in);

   //Let's not allow anything in longer than 1023 characters, as this is very likely
   //to break logging.
   if ($len > 1023)
      {
      $s_in = substr($s_in, 0, 1023);
      $len  = strlen($s_in);
      }

   $s_out = "";
   for ($i=0; $i<$len; $i++)
      {
      $c = substr($s_in, $i, 1);
      if (slog_char_membership($c))
         {
         $s_out = $s_out . $c;
         }
      else
         {
         //Use an underscore as a filler.
         $s_out = $s_out . "_";
         }
      }

   return($s_out);
   }

//------------------------------------------------------------------------
//Date/time format used for logging.  This function returns
//the canonical date/time string.
//
function slog_datetime_string()
   {
   $s = date("D m/d/y H:i:s");
   return($s);
   }

//------------------------------------------------------------------------
//Errors (something very wrong).
//
function slog_error($msg)
   {
   $logged_msg = "[ERR_, ". slog_datetime_string() . "] " . slog_logstring_member_force($msg);
   error_log($logged_msg);
   }

//------------------------------------------------------------------------
//Warnings (something odd and/or potentially dangerous).
//
function slog_warn($msg)
   {
   $logged_msg = "[WARN, ". slog_datetime_string() . "] " . slog_logstring_member_force($msg);
   error_log($logged_msg);
   }

//------------------------------------------------------------------------
//Informational entries (routine occurrences where there might be some
//benefit of tracking it later.
//
function slog_info($msg)
   {
   $logged_msg = "[INFO, ". slog_datetime_string() . "] " . slog_logstring_member_force($msg);
   error_log($logged_msg);
   }

//------------------------------------------------------------------------
?>
