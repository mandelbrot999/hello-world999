<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/resvx.inc 205 2018-07-15 19:00:51Z dashley $
//--------------------------------------------------------------------------------------------------------------
//resvx.inc--FboPrime Database resv Table Manipulation Functions (Not Scheduler Critical)
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
//Contains functions related to [operations on] the usrs table of the database that
//aren't necessary for the operation of the dayview scheduler.
//--------------------------------------------------------------------------------------------------------------
//
require_once("config.inc");
require_once("dbx.inc");
require_once("dt8.inc");
require_once("global.inc");
require_once("sguid.inc");
require_once("stimex.inc");
require_once("resv.inc");
//
//--------------------------------------------------------------------------------------------------------------
//Description
//   Adds or modifies a RESV record.  Certain parameters specify what is expected.
//
//Inputs
//   action_in
//      Enumerated type.  Possibilities are:
//         "A"  :  Add new.
//         "M"  :  Modify existing.
//
//   rec_in
//      The data about the record to add or modify, as an associative array.
//
//      Adding a record:
//         a)The index must be absent (it is assigned automatically by the database).
//         b)The userid must be included and must be globally unique, otherwise an error will be 
//           returned and the record won't be added.
//         c)Fields out of range or defective will be corrected, and warnings will be returned.
//           The record will, however, be added if possible.
//         c)All fields not present in the associative array will be assigned default values.
//         d)The creation/modification SGUID is handled automatically and may not be included in the
//           associative array.
//
//      Modifying a record:
//         a)The record is specified by either index or userid.  If both are specified, they must
//           correspond to an existing record and must be consistent.
//         b)Fields not included in the associative array are not touched.
//         c)The creation/modification SGUID is handled automatically.  If this field is included
//           in the associative array, it means to check this against what is in the database
//           and error out on editing collision if the value doesn't match what is in the database.
//
//Outputs
//   result_code_out
//      Adding a record:
//         0 if the operation failed, or the index if it succeeded.
//      Modifying an existing record.
//         0 if the operation failed or 1 if it succeeds.
//
//   errors_out
//      If any errors resulted, an associative array of integers specifying the errors per the defined
//      constants, or FALSE otherwise.
//
//   warnings_out
//      If any warnings resulted, an associative array of integers specifying the warnings per the
//      defined constants, or FALSE otherwise.
//
//Database Locking
//   Locking is performed per the recursive method described in the documentation.  If, for example,
//   the client wishes to call this function from within a larger critical section, as long as the
//   client uses the recursive locking method, everything will operate correctly.
//
function RESV_record_add_modify($action_in, $rec_in, &$result_code_out, &$errors_out, &$warnings_out)
   {
   global $GLOBAL_dbhandle;
   global $GLOBAL_dblocked;
   global $CONFIG_FBO_USER_CATEGORIES;
   global $GLOBAL_stime_string;

   $in_termination_sequence = FALSE;
   $errors_out              = FALSE;
   $warnings_out            = FALSE;


   if (!$in_termination_sequence)
      {
      //Lock the database using the recursive critical section method (discussed in the
      //manual).  This is necessary because the test for presence and the insert have to
      //be combined atomically.
      $db_was_locked = $GLOBAL_dblocked;
      if (! $GLOBAL_dblocked)
         {
         DB_db_lock();
         $GLOBAL_dblocked = TRUE;
         }


      if ($action_in == "A")
         {
         //Form the query strings.  There are two different types, depending on whether
         //we are adding or modifying a record.
         //
         //For adding, the string will be of the form:
         //   INSERT INTO usrs SET fn1=val1, fn2=val2, etc.
         //
         //For modifying, the string will be of the form:
         //   UPDATE usrs SET fn1=val1, fn2=val2, etc. WHERE idx=val.
         //
         if (!$in_termination_sequence)
            {
            //Obtain an SGUID to for the create/modification stamp.
            //
            $crmodsguid = SGUID_sguid();
            }
         }
      else
         {
         //Modify
         //
         }

      } //End if not in termination sequence.
       
   //Unlock the database (if it was locked) using the recursive critical section
   //method.
   if (! $db_was_locked)
      {
      DB_db_unlock();
      $GLOBAL_dblocked = FALSE;
      }

   //-----------------------------------------------------------
   //Clean up the output parameters to go back to the caller.
   //
   if ($in_termination_sequence)
      {
      $result_code_out = 0;
      }
   else if ($result_code_out == -1)
      {
      //Something went wrong with the query.  Return 0 as the
      //error code.
      $result_code_out = 0;
      }
   else
      {
      //The result code contains the index of what was added.
      }
   
   if (isset($errors_out_local))
      {
      $errors_out = $errors_out_local;
      }
   else
      {
      $errors_out = FALSE;
      }

   if (isset($warnings_out_local))
      {
      $warnings_out = $warnings_out_local;
      }
   else
      {
      $warnings_out = FALSE;
      }
   }
//
//--------------------------------------------------------------------------------------------------------------
//Retrieves the reservations for an individual user that:
//   a)Are owned by the user OR
//   b)Are instructional appointments with the user as the flight instructor.
//   c)End at or after the current time (i.e. are currently in progress or in the future).
//   d)Are not banner reservations.
//
//Results returned are information about the reservation except description, as an associative
//array in order from now to the future.
//
//If no such reservations exist, FALSE is returned.
//
function RESV_usrs_cur_future_resv_a($useridx_in, $curtime_in)
   {
   global $GLOBAL_dblocked;
   global $GLOBAL_dbhandle;

   //Lock the database using the recursive protocol.  This is done to be sure that nobody
   //deletes the user or the resource during this operation.
   $db_was_locked = $GLOBAL_dblocked;
   if (! $GLOBAL_dblocked)
      {
      DB_db_lock();
      $GLOBAL_dblocked = TRUE;
      }

   //See if the user record exists.  If not, can't go further, and return FALSE.
   //
   $userinfo = USRS_retrieve_by_idx($useridx_in);
   if ($userinfo === FALSE)
      {
      if (! $db_was_locked)
         {
         DB_db_unlock();
         $GLOBAL_dblocked = FALSE;
         }

      return(FALSE);
      }

   //Figure out if the user is a flight instructor or not.  This is done by
   //looking at the resources to see if there is a resource that points back to the
   //user.
   //
   //Form the query string.
   $query_string = "SELECT idx FROM rscs WHERE usercorres=\""
                   .
                   mysql_real_escape_string((string)$useridx_in, $GLOBAL_dbhandle)
                   .
                   "\"";

   //Execute the query.
   $result = mysql_query($query_string, $GLOBAL_dbhandle);

   if ($result === FALSE)
      {
      //Unknown query failure.  Return FALSE to the caller.  No need to free,
      //as this is not a result.
      $rscs_corresponding = FALSE;
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
         $rscs_corresponding = FALSE;
         }
      else
         {
         //We have at least one record.  Assume just one, because the IDX is supposed
         //to be unique.
         $resource_record = mysql_fetch_assoc($result);  //Get the associative record.
         $rscs_corresponding = $resource_record["idx"];

         //Free the result.
         mysql_free_result($result);
         }
      }
 
   //Form and execute the query to get the relevant reservations.  The query is slightly
   //more complex if the user is also a flight instructor.
   if ($rscs_corresponding === FALSE)
      {
      //User who is not a flight instructor.
      $query_string = "SELECT idx,type,useridx,alias,"
                      .
                      "finstid,finsttimestart,finsttimeend,"
                      .
                      "acftsimid,acftsimtimestart,acftsimtimeend,"
                      .
                      "resvtimestart,resvtimeend "
                      .
                      "FROM resv WHERE useridx=\""
                      .
                      $useridx_in
                      .
                      "\" AND type!=\"" . RESV_TYPE_BANNER . "\" AND resvtimeend>=\""
                      .
                      $curtime_in
                      .
                      "\" ORDER BY resvtimeend ASC, idx ASC";
      //echo "<pre>\n";
      //print_r($query_string);
      //echo "</pre>\n";
      }
   else
      {
      //User who is a flight instructor.
      $query_string = "SELECT idx,type,useridx,alias,"
                      .
                      "finstid,finsttimestart,finsttimeend,"
                      .
                      "acftsimid,acftsimtimestart,acftsimtimeend,"
                      .
                      "resvtimestart,resvtimeend "
                      .
                      "FROM resv WHERE (useridx=\""
                      .
                      $useridx_in
                      .
                      "\" OR finstid=\"" . $rscs_corresponding . "\") AND type!=\"" . RESV_TYPE_BANNER . "\" AND resvtimeend>=\""
                      .
                      $curtime_in
                      .
                      "\" ORDER BY resvtimeend ASC, idx ASC";

      //echo "<pre>\n";
      //print_r($query_string);
      //echo "</pre>\n";
      }

   //Run the query, get the result.
   $result = mysql_query($query_string, $GLOBAL_dbhandle);

   //If the query did not go through successfully, return FALSE to the caller.
   //
   if ($result === FALSE)
      {
      $rv = FALSE;
      }
   //
   //If the number of rows in the result set is 0, also give the caller FALSE.
   else if (mysql_num_rows($result) <= 0)
      {
      //Technically, we got a result set, so free it.
      mysql_free_result($result);

      //The caller gets FALSE signaling no data.
      $rv = FALSE;
      }
   else
      {
      //If we're here, we have a valid result set.  Each row of the returned array is
      //the expected fields from the resv table.

      //Copy out the results to the array we'll return.
      while ($row = mysql_fetch_assoc($result))
         {
         $rv[]  = $row;
         }

      //Free memory.
      mysql_free_result($result);
      }

   //Unlock the database (if it was locked) using the recursive critical section
   //method.
   if (! $db_was_locked)
      {
      DB_db_unlock();
      $GLOBAL_dblocked = FALSE;
      }

   //Return the agreed-on result to the caller.
   return($rv);
   }
//
//--------------------------------------------------------------------------------------------------------------
//Retrieves the reservations for an individual user that:
//   a)Are owned by the user OR
//   b)Are instructional appointments with the user as the flight instructor.
//   c)End before the current time (i.e. have fully finished).
//   d)Are not banner reservations.
//
//Results returned are information about the reservation except description, as an associative
//array in order from now to the future.
//
//If no such reservations exist, FALSE is returned.
//
function RESV_usrs_past_resv_a($useridx_in, $curtime_in)
   {
   global $GLOBAL_dblocked;
   global $GLOBAL_dbhandle;

   //Lock the database using the recursive protocol.  This is done to be sure that nobody
   //deletes the user or the resource during this operation.
   $db_was_locked = $GLOBAL_dblocked;
   if (! $GLOBAL_dblocked)
      {
      DB_db_lock();
      $GLOBAL_dblocked = TRUE;
      }

   //See if the user record exists.  If not, can't go further, and return FALSE.
   //
   $userinfo = USRS_retrieve_by_idx($useridx_in);
   if ($userinfo === FALSE)
      {
      if (! $db_was_locked)
         {
         DB_db_unlock();
         $GLOBAL_dblocked = FALSE;
         }

      return(FALSE);
      }

   //Figure out if the user is a flight instructor or not.  This is done by
   //looking at the resources to see if there is a resource that points back to the
   //user.
   //
   //Form the query string.
   $query_string = "SELECT idx FROM rscs WHERE usercorres=\""
                   .
                   mysql_real_escape_string((string)$useridx_in, $GLOBAL_dbhandle)
                   .
                   "\"";

   //Execute the query.
   $result = mysql_query($query_string, $GLOBAL_dbhandle);

   if ($result === FALSE)
      {
      //Unknown query failure.  Return FALSE to the caller.  No need to free,
      //as this is not a result.
      $rscs_corresponding = FALSE;
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
         $rscs_corresponding = FALSE;
         }
      else
         {
         //We have at least one record.  Assume just one, because the IDX is supposed
         //to be unique.
         $resource_record = mysql_fetch_assoc($result);  //Get the associative record.
         $rscs_corresponding = $resource_record["idx"];

         //Free the result.
         mysql_free_result($result);
         }
      }
 
   //Form and execute the query to get the relevant reservations.  The query is slightly
   //more complex if the user is also a flight instructor.
   if ($rscs_corresponding === FALSE)
      {
      //User who is not a flight instructor.
      $query_string = "SELECT idx,type,useridx,alias,"
                      .
                      "finstid,finsttimestart,finsttimeend,"
                      .
                      "acftsimid,acftsimtimestart,acftsimtimeend,"
                      .
                      "resvtimestart,resvtimeend "
                      .
                      "FROM resv WHERE useridx=\""
                      .
                      $useridx_in
                      .
                      "\" AND type!=\"" . RESV_TYPE_BANNER . "\" AND resvtimeend<\""
                      .
                      $curtime_in
                      .
                      "\" ORDER BY resvtimeend DESC, idx ASC";
      //echo "<pre>\n";
      //print_r($query_string);
      //echo "</pre>\n";
      }
   else
      {
      //User who is a flight instructor.
      $query_string = "SELECT idx,type,useridx,alias,"
                      .
                      "finstid,finsttimestart,finsttimeend,"
                      .
                      "acftsimid,acftsimtimestart,acftsimtimeend,"
                      .
                      "resvtimestart,resvtimeend "
                      .
                      "FROM resv WHERE (useridx=\""
                      .
                      $useridx_in
                      .
                      "\" OR finstid=\"" . $rscs_corresponding . "\") AND type!=\"" . RESV_TYPE_BANNER . "\" AND resvtimeend<\""
                      .
                      $curtime_in
                      .
                      "\" ORDER BY resvtimeend DESC, idx ASC";

      //echo "<pre>\n";
      //print_r($query_string);
      //echo "</pre>\n";
      }

   //Run the query, get the result.
   $result = mysql_query($query_string, $GLOBAL_dbhandle);

   //If the query did not go through successfully, return FALSE to the caller.
   //
   if ($result === FALSE)
      {
      $rv = FALSE;
      }
   //
   //If the number of rows in the result set is 0, also give the caller FALSE.
   else if (mysql_num_rows($result) <= 0)
      {
      //Technically, we got a result set, so free it.
      mysql_free_result($result);

      //The caller gets FALSE signaling no data.
      $rv = FALSE;
      }
   else
      {
      //If we're here, we have a valid result set.  Each row of the returned array is
      //the expected fields from the resv table.

      //Copy out the results to the array we'll return.
      while ($row = mysql_fetch_assoc($result))
         {
         $rv[]  = $row;
         }

      //Free memory.
      mysql_free_result($result);
      }

   //Unlock the database (if it was locked) using the recursive critical section
   //method.
   if (! $db_was_locked)
      {
      DB_db_unlock();
      $GLOBAL_dblocked = FALSE;
      }

   //Return the agreed-on result to the caller.
   return($rv);
   }
//
//--------------------------------------------------------------------------------------------------------------
//Returns the time for a reservation display time.
//
function RESV_time_string_a($st_in)
   {
   //Split apart the hour and minute as integers.
   sscanf(SubStr($st_in, 10, 4), "%02d%02d", $hour, $minute);
 
   if (CONFIG_TIME_FORMAT_24HR)
      {
      $rv = sprintf("%02d:%02d", $hour, $minute);
      }
   else
      {
      if ($hour == 0)
         {
         $rv = sprintf("12:%02d a.m.", $minute);
         }
      else if ($hour == 12)
         {
         $rv = sprintf("12:%02d p.m.", $minute);
         }
      else if ($hour > 12)
         {
         $rv = sprintf("%d:%02d p.m.", $hour-12, $minute);
         }
      else
         {
         $rv = sprintf("%d:%02d a.m.", $hour, $minute);
         }
      }
   
   return($rv);
   }
//
//--------------------------------------------------------------------------------------------------------------
//Returns the date for a reservation display date.
//
function RESV_date_string_a($st_in)
   {
   if (CONFIG_DATE_FORMAT_EUROPEAN)
      {
      $rv = SubStr($st_in, 2, 4) . "/" . SubStr($st_in, 6, 2) . "/" . SubStr($st_in, 8, 2); 
      }
   else
      {
      $rv = SubStr($st_in, 6, 2) . "/" . SubStr($st_in, 8, 2) . "/" . SubStr($st_in, 2, 4);
      }
   
   return($rv);
   }
//
//--------------------------------------------------------------------------------------------------------------
//Returns the text corresponding to the date range for printout of reservations.  If the two
//STIMEs correspond to the same date, the date is compressed into one.
//
function RESV_date_range_string_a($st_start_in, $st_end_in)
   {
   if (SubStr($st_start_in, 0, 10) == SubStr($st_end_in, 0, 10))
      {
      //Dates are the same, so can just do the date once.
      $rv = RESV_date_string_a($st_start_in) 
            . 
            " (" 
            . 
            STIME_dow_string_a($st_start_in)
            .
            ") "
            .
            RESV_time_string_a($st_start_in) 
            . 
            " - " 
            . 
            RESV_time_string_a($st_end_in);
      }
   else
      {
      //Dates are different so must do it twice.
      $rv = RESV_date_string_a($st_start_in) 
            . 
            " (" 
            . 
            STIME_dow_string_a($st_start_in)
            .
            ") " 
            . 
            RESV_time_string_a($st_start_in) 
            . 
            " - " 
            . 
            RESV_date_string_a($st_end_in) 
            .
            " (" 
            . 
            STIME_dow_string_a($st_end_in)
            .
            ") "
            .
            RESV_time_string_a($st_end_in);
      }

   //Tack on the duration.
   $rv = $rv . " (" . STIME_diff_string_a($st_start_in, $st_end_in) . ")";

   return($rv);
   }
//
//--------------------------------------------------------------------------------------------------------------
//Returns the text corresponding to a given reservation, flight instructor first.  If the date
//and time for the aircraft/simulator and flight instructor are the same, only one string is returned.
//
function RESV_resv_date_string_a($resv_in, $personstring, $acftsimstring)
   {
   if (($resv_in["finstid"] != 0) && ($resv_in["acftsimid"] != 0))
      {
      //Both a flight instructor and an aircraft.
      if (($resv_in["finsttimestart"] == $resv_in["acftsimtimestart"]) && ($resv_in["finsttimeend"] == $resv_in["acftsimtimeend"]))
         {
         //Start and end time of the instructor and aircraft are the same.  Can combine them.
         //
         $rv = RESV_date_range_string_a($resv_in["finsttimestart"], $resv_in["finsttimeend"]);
         }
      else
         {
         //Start and end time of instructor and aircraft are different.  Cannot combine them.
         $rv = $personstring
               .
               " " 
               . 
               RESV_date_range_string_a($resv_in["finsttimestart"], $resv_in["finsttimeend"])
               .
               ", "
               .
               $acftsimstring
               .
               " "
               .
               RESV_date_range_string_a($resv_in["acftsimtimestart"], $resv_in["acftsimtimeend"])
               ;
         }

      }
   else if (($resv_in["finstid"] == 0) && ($resv_in["acftsimid"] != 0))
      {
      //Aircraft but no flight instructor.
      $rv = RESV_date_range_string_a($resv_in["acftsimtimestart"], $resv_in["acftsimtimeend"]);
      }
   else if (($resv_in["finstid"] != 0) && ($resv_in["acftsimid"] == 0))
      {
      //Flight instructor but no aircraft.
      $rv = RESV_date_range_string_a($resv_in["finsttimestart"], $resv_in["finsttimeend"]);
      }
   else
      {
      //Should never be here.  Return the empty string to be safe.
      $rv = "";
      }

   return($rv);
   }
//
//--------------------------------------------------------------------------------------------------------------
//End of $RCSfile: resvx.inc,v $.
//--------------------------------------------------------------------------------------------------------------
?>
