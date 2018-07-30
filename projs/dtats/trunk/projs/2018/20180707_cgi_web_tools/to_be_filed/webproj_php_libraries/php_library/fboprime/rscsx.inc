<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/rscsx.inc 205 2018-07-15 19:00:51Z dashley $
//--------------------------------------------------------------------------------------------------------------
//rscsx.inc--FboPrime Database rscs Table Manipulation Functions Not Required by Day View Scheduler
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
//
require_once("cslx.inc");
require_once("datefunc.inc");
require_once("db.inc");
require_once("global.inc");
require_once("rscs.inc");
require_once("sguid.inc");
//
//--------------------------------------------------------------------------------------------------------------
//The set of characters allowed in the initials field.
//
define("RSCS_INITIALS_ALLOWEDCHARS",  " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ:-_.,;'0123456789");
define("RSCS_SHORTDESC_ALLOWEDCHARS", " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ:-_.,;'0123456789");
define("RSCS_LONGDESC_ALLOWEDCHARS",  " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ:-_.,;'0123456789");
//
//--------------------------------------------------------------------------------------------------------------
//Modifies a RSCS record.  The record is keyed by the index of the record in.
//All errors are tolerated except three:
//  a)Record does not exist, so can't modify it.  No changes made.
//  b)Editing collision:  SGUID shows concurrent editing.  In this case, no changes are made.
//  c)Unknown query failure.  Presumably no changes made.
//
//All error flags are FALSE if no error, TRUE if error.
//
//If all are FALSE, operation probably succeeded.
//
function RSCS_modify_record(
                             $record_in,
                            &$record_noexist_error_out,
                            &$editing_collision_error_out,
                            &$query_failure_error_out
                           )
   {
   global $GLOBAL_dbhandle;
   global $GLOBAL_dblocked;

   //Assume by default no errors.
   $record_noexist_error_out     = FALSE;
   $editing_collision_error_out  = FALSE;
   $query_failure_error_out      = FALSE;

   //Grab a new SGUID.  This will be used for the mod stamp in the event we can commit
   //the changes.
   $new_sguid = SGUID_sguid();

   //Lock the database using the recursive critical section method (discussed in the
   //manual).  This is necessary because the test for presence and the modification have to
   //be combined atomically.
   //
   $db_was_locked = $GLOBAL_dblocked;
   if (! $GLOBAL_dblocked)
      {
      DB_db_lock();
      $GLOBAL_dblocked = TRUE;
      }
   //
   //Try to yank the record with the specified idx.
   $existing_record = RSCS_retrieve_by_idx($record_in["idx"]);

   //If the record doesn't already exist, we can't go forward.  Error out.
   if ($existing_record === FALSE)
      {
      //Unlock the database (if it was locked) using the recursive critical section
      //method.
      if (! $db_was_locked)
         {
         DB_db_unlock();
         $GLOBAL_dblocked = FALSE;
         }

      $record_noexist_error_out = TRUE;

      return; //Back to caller.
      }

   //Test for an editing collision.
   if ($existing_record["crmodsguid"] != $record_in["crmodsguid"])
      {
      //Unlock the database (if it was locked) using the recursive critical section
      //method.
      if (! $db_was_locked)
         {
         DB_db_unlock();
         $GLOBAL_dblocked = FALSE;
         }

      $editing_collision_error_out = TRUE;

      return; //Back to caller.
      }

   //Build the query string with each successive parameter.
   //
   //type
   //------
   if (! isset($record_in["type"]))
      $pushval = RSCS_TYPE_AIRCRAFT;
   else
      $pushval = $record_in["type"];
   $query_string = "UPDATE rscs SET type=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"";
   //
   //status
   //------
   if (! isset($record_in["status"]))
      $pushval = RSCS_STATUS_ONLINE;
   else
      $pushval = $record_in["status"];
   $query_string .= (", status=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //disporder
   //---------
   if (! isset($record_in["disporder"]))
      $pushval = 0;
   else
      $pushval = $record_in["disporder"];
   $query_string .= (", disporder=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
    //
   //longdesc
   //--------
   if (! isset($record_in["longdesc"]))
      $pushval = "";
   else
      $pushval = $record_in["longdesc"];
   $query_string .= (", longdesc=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //shortdesc
   //---------
   if (! isset($record_in["shortdesc"]))
      $pushval = "";
   else
      $pushval = $record_in["shortdesc"];
   $query_string .= (", shortdesc=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //initials
   //--------
   if (! isset($record_in["initials"]))
      $pushval = "";
   else
      $pushval = $record_in["initials"];
   $query_string .= (", initials=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //rstdtime
   //--------
   if (! isset($record_in["rstdtime"]))
      $pushval = "UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU";
   else
      $pushval = $record_in["rstdtime"];
   $query_string .= (", rstdtime=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
    //
   //schedaheadhrs
   //-------------
   if (! isset($record_in["schedaheadhrs"]))
      $pushval = (int) 0;
   else
      $pushval = $record_in["schedaheadhrs"];
   $query_string .= (", schedaheadhrs=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //usercorres
   //----------
   if (! isset($record_in["usercorres"]))
      $pushval = (int) 0;
   else
      $pushval = $record_in["usercorres"];
   $query_string .= (", usercorres=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //crmodsguid
   //----------
   $pushval = $new_sguid;
   $query_string .= (", crmodsguid=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //echo " " . $query_string . " ";
   //
   //idx qualifier
   //-------------
   $pushval = $record_in["idx"];
   $query_string .= (" WHERE idx=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");

   //echo "<br>";
   //print_r($query_string);
   //echo "<br>";

    //Execute the query to insert the record.
   $result = mysql_query($query_string, $GLOBAL_dbhandle);
   //
   //If the update failed, set the query failure flag.
   if ($result == FALSE)
      {
      $query_failure_error_out = TRUE;
      }

   //Unlock the database (if it was locked) using the recursive critical section
   //method.
   if (! $db_was_locked)
      {
      DB_db_unlock();
      $GLOBAL_dblocked = FALSE;
      }
   }
//
//--------------------------------------------------------------------------------------------------------------
//Retrieves an associative array containing full information about the resource whose index is
//passed, or FALSE if it can't be located.
//
function RSCS_retrieve_by_idx($idx)
   {
   global $GLOBAL_dbhandle;

   //Form the query string.
   $query_string = "SELECT * FROM rscs WHERE idx=\""
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
//Retrieves an array containing the indices of all flight instructors in the resources
//table that are online, or FALSE if none exist.
//
function RSCS_get_fi_online_idxs()
   {
   global $GLOBAL_dbhandle;

   //Form the query string.
   $query_string = "SELECT idx FROM rscs WHERE type=\""
                   .
                   mysql_real_escape_string((string)RSCS_TYPE_FLIGHTINSTRUCTOR, $GLOBAL_dbhandle)
                   .
                   "\" AND status=\""
                   .
                   mysql_real_escape_string((string)RSCS_STATUS_ONLINE, $GLOBAL_dbhandle)
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

         //The caller gets FALSE.  No records.
         $rv = FALSE;
         }
      else
         {
         //We have at least one record.  Grab the indices.
         //
         for ($i=0; $i<$nrows; $i++)
            {
            $temp   = mysql_fetch_assoc($result);
            $rv[$i] = $temp["idx"];
            }

         //Free the result.
         mysql_free_result($result);
         }

      //Return the value to the caller.
      return($rv);
      }
   }
//
//--------------------------------------------------------------------------------------------------------------
//Retrieves an array containing the indices of all aircraft/simulators in the resources
//table that are online, or FALSE if none exist.
//
function RSCS_get_acftsim_online_idxs()
   {
   global $GLOBAL_dbhandle;

   //Form the query string.
   $query_string = "SELECT idx FROM rscs WHERE ( type=\""
                   .
                   mysql_real_escape_string((string)RSCS_TYPE_AIRCRAFT, $GLOBAL_dbhandle)
                   .
                   "\" OR type=\""
                   .
                   mysql_real_escape_string((string)RSCS_TYPE_SIMULATOR, $GLOBAL_dbhandle)
                   .
                   "\" ) AND status=\""
                   .
                   mysql_real_escape_string((string)RSCS_STATUS_ONLINE, $GLOBAL_dbhandle)
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

         //The caller gets FALSE.  No records.
         $rv = FALSE;
         }
      else
         {
         //We have at least one record.  Grab the indices.
         //
         for ($i=0; $i<$nrows; $i++)
            {
            $temp   = mysql_fetch_assoc($result);
            $rv[$i] = $temp["idx"];
            }

         //Free the result.
         mysql_free_result($result);
         }

      //Return the value to the caller.
      return($rv);
      }
   }
//
//--------------------------------------------------------------------------------------------------------------
//Retrieves an array containing the indices of _all_ resources, ordered by status, sort index, then index
//for display on the resource list page.
//
function RSCS_get_idxs_all_rscslist_a()
   {
   global $GLOBAL_dbhandle;

   //Form the query string.
   $query_string = "SELECT idx FROM rscs ORDER BY status DESC, disporder ASC, idx ASC";

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

         //The caller gets FALSE.  No records.
         $rv = FALSE;
         }
      else
         {
         //We have at least one record.  Grab the indices.
         //
         for ($i=0; $i<$nrows; $i++)
            {
            $temp   = mysql_fetch_assoc($result);
            $rv[$i] = $temp["idx"];
            }

         //Free the result.
         mysql_free_result($result);
         }

      //Return the value to the caller.
      return($rv);
      }
   }
//
//--------------------------------------------------------------------------------------------------------------
//Retrieves an array containing the short description, medium description, database index, status, and
//corresponding user for each entry in the resources table.  The array returned is indexed by the database index
//(not sequentially), meaning that some gaps in the indexing may occur.
//
//Returns FALSE if no records.
//
function RSCS_get_key_info_rscslist_a()
   {
   global $GLOBAL_dbhandle;

   //Form the query string.
   $query_string = "SELECT idx,type,status,initials,shortdesc,usercorres FROM rscs";

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

         //The caller gets FALSE.  No records.
         $rv = FALSE;
         }
      else
         {
         //We have at least one record.  Grab the data.
         //
         for ($i=0; $i<$nrows; $i++)
            {
            $temp   = mysql_fetch_assoc($result);
            $rv[$temp["idx"]] = $temp;
            }

         //Free the result.
         mysql_free_result($result);
         }

      //Return the value to the caller.
      return($rv);
      }
   }
//
//--------------------------------------------------------------------------------------------------------------
//Renumbers the disporder fields of the resource table at a fixed interval.
//
function RSCS_renumber_disporder_autointerval()
   {
   global $GLOBAL_dblocked;
   global $GLOBAL_dbhandle;

   $renumber_interval = 100;  //Interval to use.  100 should be large enough for any practical
                              //number of resources.

   //Lock the database using the recursive locking protocol to ensure that there won't be 
   //any changes while we are going through tampering with each resource.
   //
   $db_was_locked = $GLOBAL_dblocked;
   if (! $GLOBAL_dblocked)
      {
      DB_db_lock();
      $GLOBAL_dblocked = TRUE;
      }
   //-----------------------------------------------
   //Get the complete set of indices from the resource table.  We want to preserve the old
   //order, so primary sort key is the display order, but then we have a couple (somewhat
   //arbitrary) tiebreakers.  We calculate the value FALSE (in place of an array)
   //if something goes wrong.
   //
   //Form the query string.
   $query_string = "SELECT idx FROM rscs ORDER BY disporder ASC, status DESC, idx ASC";

   //Execute the query.
   $result = mysql_query($query_string, $GLOBAL_dbhandle);

   if ($result === FALSE)
      {
      //Unknown query failure.  Return FALSE to the caller.  No need to free,
      //as this is not a result.
      $indices = FALSE;
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

         //The caller gets FALSE.  No records.
         $indices = FALSE;
         }
      else
         {
         //We have at least one record.  Grab the indices.
         //
         for ($i=0; $i<$nrows; $i++)
            {
            $temp   = mysql_fetch_assoc($result);
            $indices[$i] = $temp["idx"];
            }

         //Free the result.
         mysql_free_result($result);
         }
      }

   //-----------------------------------------------
   //If we had success in getting the list of indices (in the order we want),
   //loop through them all and give them the right values.  We loop backwards to avoid
   //changing resource order in the event that the httpd process dies in the middle of this.
   //We also need to change the modification sguid to make sure any editing collisions
   //will be detected.
   //
   if ($indices !== FALSE)
      {
      $n = count($indices);
      $number_to_assign = $n * $renumber_interval;

      for ($i=0; $i<$n; $i++)
         {
         $sguid  = SGUID_sguid();

         $target = $indices[$n-1-$i];

         mysql_query("UPDATE rscs SET disporder=\""
                     .
                     (string)(($n - $i) * $renumber_interval)
                     .
                     "\", crmodsguid=\""
                     .
                     $sguid
                     .
                     "\" WHERE idx=\""
                     .
                     $target
                     .
                     "\"", $GLOBAL_dbhandle);          
         }
      }

   //-----------------------------------------------
   //Unlock the database using the recursive locking protocol.
   //
   if (! $db_was_locked)
      {
      DB_db_unlock();
      $GLOBAL_dblocked = FALSE;
      }
   }
//
//--------------------------------------------------------------------------------------------------------------
//Maps from the resource status to a short description for the resource views.
//
function RSCS_status_map_long($status_in)
   {
   switch($status_in)
      {
      default:
         {
         $rv = "Unknown";

         break;
         }
      case RSCS_STATUS_OFFLINE :
         {
         $rv = "Offline";

         break;
         }
      case RSCS_STATUS_ONLINE :
         {
         $rv = "Online";

         break;
         }
      }

   return($rv);
   }
//--------------------------------------------------------------------------------------------------------------
//Maps from the resource status to a short description for the resource views.
//
function RSCS_type_map_long($status_in)
   {
   switch($status_in)
      {
      default:
         {
         $rv = "Unknown";

         break;
         }
      case RSCS_TYPE_AIRCRAFT :
         {
         $rv = "Aircraft";

         break;
         }
      case RSCS_TYPE_SIMULATOR :
         {
         $rv = "Simulator";

         break;
         }
      case RSCS_TYPE_FLIGHTINSTRUCTOR :
         {
         $rv = "Flight Instructor";

         break;
         }
      }

   return($rv);
   }
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//Returns the HTML that should be used to identify the resource index on the EDIT and ADD pages.  HTML may
//be marked up with <i> and <b> and includes the trailing colon.
//
function RSCS_idx_id_html_01()
   {
   return("<i>idx:</i>");
   }
//--------------------------------------------------------------------------------------------------------------
//Returns the HTML that should be used to display the resource index on the EDIT and ADD pages.
//
function RSCS_idx_disp_html_01($idx_in)
   {
   $rv = number_format($idx_in);
   return($rv);
   }
//--------------------------------------------------------------------------------------------------------------
//Returns the HTML that should be used to identify the resource index description on the EDIT and ADD pages.
//HTML may be marked up with <i>, <b>, and <b>.
//
function RSCS_idx_desc_html_01()
   {
   $rv =   "The <i>idx</i> field is assigned automatically by the database "
         . "when a resource is created and may not be modified.";
 
   return($rv);
   }
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//Returns the HTML that should be used to identify the resource type on the EDIT and ADD pages.  HTML may
//be marked up with <i> and <b> and includes the trailing colon.
//
function RSCS_type_id_html_01()
   {
   return("<i>type:</i>");
   }
//--------------------------------------------------------------------------------------------------------------
//Returns the HTML that should be used to display the resource type select control on the EDIT and ADD pages.
//
function RSCS_type_disp_html_01($type_in)
   {
   //Turn the input into a numeric value.  If it can't be turned into a numeric value, 
   //make it an aircraft.
   if (is_numeric($type_in))
      {
      $type_in = (int)$type_in;
      if (
            ($type_in != RSCS_TYPE_AIRCRAFT) 
            && 
            ($type_in != RSCS_TYPE_SIMULATOR) 
            && 
            ($type_in != RSCS_TYPE_FLIGHTINSTRUCTOR)
         )
         {
         //This is nothing we recognize.  Assume aircraft.
         $type_in = (int)RSCS_TYPE_AIRCRAFT;
         }
      }
   else
      {
      //This is nothing we recognize.  Assume aircraft.
      $type_in = (int)RSCS_TYPE_AIRCRAFT;
      }

   //Do the control.
   $rv  = "<select name=\"type\">";
   //--------
   $rv .= "<option value=\"" . (string)RSCS_TYPE_AIRCRAFT . "\"";
   if ($type_in == RSCS_TYPE_AIRCRAFT)
      $rv .= " SELECTED";
   $rv .= ">Aircraft";
   //--------
   $rv .= "<option value=\"" . (string)RSCS_TYPE_SIMULATOR . "\"";
   if ($type_in == RSCS_TYPE_SIMULATOR)
      $rv .= " SELECTED";
   $rv .= ">Simulator";
   //--------
   $rv .= "<option value=\"" . (string)RSCS_TYPE_FLIGHTINSTRUCTOR . "\"";
   if ($type_in == RSCS_TYPE_FLIGHTINSTRUCTOR)
      $rv .= " SELECTED";
   $rv .= ">Flight Instructor";
   //
   $rv .= "</SELECT>";

   return($rv);
   }
//--------------------------------------------------------------------------------------------------------------
//Returns the HTML that should be used to identify the resource index description on the EDIT and ADD pages.
//HTML may be marked up with <i>, <b>, and <b>.
//
function RSCS_type_desc_html_01()
   {
   $rv =   "The <i>type</i> identifies whether the resource is an aircraft, a simulator, "
         . "or a flight instructor.";
 
   return($rv);
   }
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//Returns the HTML that should be used to identify the resource status on the EDIT and ADD pages.  HTML may
//be marked up with <i> and <b> and includes the trailing colon.
//
function RSCS_status_id_html_01()
   {
   return("<i>status:</i>");
   }
//--------------------------------------------------------------------------------------------------------------
//Returns the HTML that should be used to display the resource status select control on the EDIT and ADD pages.
//
function RSCS_status_disp_html_01($status_in)
   {
   //Turn the input into a numeric value.  If it can't be turned into a numeric value, 
   //make it online.
   if (is_numeric($status_in))
      {
      $status_in = (int)$status_in;
      if (
            ($status_in != RSCS_STATUS_OFFLINE) 
            && 
            ($status_in != RSCS_STATUS_ONLINE) 
         )
         {
         //This is nothing we recognize.  Assume online.
         $status_in = (int)RSCS_STATUS_ONLINE;
         }
      }
   else
      {
      //This is nothing we recognize.  Assume online.
      $status_in = (int)RSCS_STATUS_ONLINE;
      }

   //Do the control.
   $rv  = "<select name=\"status\">";
   //--------
   $rv .= "<option value=\"" . (string)RSCS_STATUS_OFFLINE . "\"";
   if ($status_in == RSCS_STATUS_OFFLINE)
      $rv .= " SELECTED";
   $rv .= ">Offline";
   //--------
   $rv .= "<option value=\"" . (string)RSCS_STATUS_ONLINE . "\"";
   if ($status_in == RSCS_STATUS_ONLINE)
      $rv .= " SELECTED";
   $rv .= ">Online";
   //--------
   $rv .= "</SELECT>";

   return($rv);
   }
//--------------------------------------------------------------------------------------------------------------
//Returns the HTML that should be used to identify the resource index description on the EDIT and ADD pages.
//HTML may be marked up with <i>, <b>, and <b>.
//
function RSCS_status_desc_html_01()
   {
   $rv =   "The <i>status</i> identifies whether a resource is in service.&nbsp; A resource that is <i>offline</i> "
         . "is not displayed in scheduling views and cannot be scheduled.&nbsp; Placing a resource <i>offline</i> "
         . "will make the resource invisible without deleting information about the resource.";
 
   return($rv);
   }
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//Returns the HTML that should be used to identify the disporderstatus on the EDIT and ADD pages.  HTML may
//be marked up with <i> and <b> and includes the trailing colon.
//
function RSCS_disporder_id_html_01()
   {
   return("<i>disporder:</i>");
   }
//--------------------------------------------------------------------------------------------------------------
//Returns the HTML that should be used to display the disporder form field on the EDIT and ADD pages.
//
function RSCS_disporder_disp_html_01($disporder_in)
   {
   //Turn the input into a numeric value.  If it can't be turned into a numeric value, 
   //make it online.
   if (is_numeric($disporder_in))
      {
      $disporder_in = (int)$disporder_in;
      if ($disporder_in <= 0)
         {
         //Can't be non-positive integer.
         $disporder_in = 1;
         }
      }
   else
      {
      //This is nothing we recognize.  Assume number 1.
      $disporder_in = 1;
      }

   //Do the text input field.
   $rv  = "<input type=\"text\" name=\"disporder\" size=\"15\" value=\""
          .
          (string)$disporder_in
          .
          "\">";

   return($rv);
   }
//--------------------------------------------------------------------------------------------------------------
//Returns the HTML that should be used to identify the resource index description on the EDIT and ADD pages.
//HTML may be marked up with <i>, <b>, and <b>.
//
function RSCS_disporder_desc_html_01()
   {
   $rv =   "The <i>disporder</i> is a positive integer that defines which resource is displayed first "
         . "in contexts where information about more than one resource may be displayed.&nbsp; Resources "
         . "with the smaller <i>disporder</i> field are displayed first.&nbsp; An option to renumber the "
         . "<i>disporder</i> fields exists on the resource list page.";
 
   return($rv);
   }
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//Returns the HTML that should be used to identify the initials on the EDIT and ADD pages.  HTML may
//be marked up with <i> and <b> and includes the trailing colon.
//
function RSCS_initials_id_html_01()
   {
   return("<i>initials:</i>");
   }
//--------------------------------------------------------------------------------------------------------------
//Returns the HTML that should be used to display the initials form field on the EDIT and ADD pages.
//
function RSCS_initials_disp_html_01($initials_in)
   {
   //Do the text input field.
   $rv  = "<input type=\"text\" name=\"initials\" size=\"15\" value=\""
          .
          htmlentities((string)$initials_in)
          .
          "\">";

   return($rv);
   }
//--------------------------------------------------------------------------------------------------------------
//Returns the HTML that should be used to identify the resource index description on the EDIT and ADD pages.
//HTML may be marked up with <i>, <b>, and <b>.
//
function RSCS_initials_desc_html_01()
   {
   $rv =   "The <i>initials</i> field is the shortest possible description to uniquely identify an "
         . "aircraft, simulator, or flight instructor.&nbsp; For an aircraft, this field traditionally "
         . "is the registration number of the aircraft (i.e. &quot;N1234N&quot;).&nbsp; For a flight instructor, "
         . "this field traditionally holds just the instructor's initials (i.e. &quot;J.S.&quot;).";
 
   return($rv);
   }
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//Returns the HTML that should be used to identify the shortdesc on the EDIT and ADD pages.  HTML may
//be marked up with <i> and <b> and includes the trailing colon.
//
function RSCS_shortdesc_id_html_01()
   {
   return("<i>shortdesc:</i>");
   }
//--------------------------------------------------------------------------------------------------------------
//Returns the HTML that should be used to display the shortdesc form field on the EDIT and ADD pages.
//
function RSCS_shortdesc_disp_html_01($shortdesc_in)
   {
   //Do the text input field.
   $rv  = "<input type=\"text\" name=\"shortdesc\" size=\"50\" value=\""
          .
          htmlentities((string)$shortdesc_in)
          .
          "\">";

   return($rv);
   }
//--------------------------------------------------------------------------------------------------------------
//Returns the HTML that should be used to identify the resource shortdesc description on the EDIT and ADD pages.
//HTML may be marked up with <i>, <b>, and <b>.
//
function RSCS_shortdesc_desc_html_01()
   {
   $rv =   "The <i>shortdesc</i> field is the medium-length description to uniquely identify an "
         . "aircraft, simulator, or flight instructor.&nbsp; For an aircraft, this field traditionally "
         . "is the registration number of the aircraft (i.e. &quot;N1234N&quot;).&nbsp; For a flight instructor, "
         . "this field traditionally holds the instructor's first initial and last name (i.e. &quot;J. Smith&quot;).";
 
   return($rv);
   }
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//Returns the HTML that should be used to identify the longdesc on the EDIT and ADD pages.  HTML may
//be marked up with <i> and <b> and includes the trailing colon.
//
function RSCS_longdesc_id_html_01()
   {
   return("<i>longdesc:</i>");
   }
//--------------------------------------------------------------------------------------------------------------
//Returns the HTML that should be used to display the longdesc form field on the EDIT and ADD pages.
//
function RSCS_longdesc_disp_html_01($longdesc_in)
   {
   //Do the text input field.
   $rv  = "<input type=\"text\" name=\"longdesc\" size=\"100\" value=\""
          .
          htmlentities((string)$longdesc_in)
          .
          "\">";

   return($rv);
   }
//--------------------------------------------------------------------------------------------------------------
//Returns the HTML that should be used to identify the resource longdesc description on the EDIT and ADD pages.
//HTML may be marked up with <i>, <b>, and <b>.
//
function RSCS_longdesc_desc_html_01()
   {
   $rv =   "The <i>longdesc</i> field is the longest description to uniquely identify an "
         . "aircraft, simulator, or flight instructor.&nbsp; For an aircraft, this field traditionally "
         . "is the registration number of the aircraft followed by the manufacturer and model "
         . "(i.e. &quot;N1234N Cessna 172P&quot;).&nbsp; For a flight instructor, "
         . "this field traditionally holds the instructor's last name, a comma, and then the first "
         . "name (i.e. &quot;Smith, John&quot;).";
 
   return($rv);
   }
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//Returns the HTML that should be used to identify the schedaheadhrs on the EDIT and ADD pages.  HTML may
//be marked up with <i> and <b> and includes the trailing colon.
//
function RSCS_schedaheadhrs_id_html_01()
   {
   return("<i>schedaheadhrs:</i>");
   }
//--------------------------------------------------------------------------------------------------------------
//Returns the HTML that should be used to display the schedaheadhrs form field on the EDIT and ADD pages.
//
function RSCS_schedaheadhrs_disp_html_01($schedaheadhrs_in)
   {
   //Turn the input into a numeric value.  If it can't be turned into a numeric value, 
   //make it online.
   if (is_numeric($schedaheadhrs_in))
      {
      $schedaheadhrs_in = (int)$schedaheadhrs_in;
      if ($schedaheadhrs_in < 0)
         {
         //Can't be negative integer.
         $schedaheadhrs_in = 0;
         }
      }
   else
      {
      //This is nothing we recognize.  Assume number 0.
      $schedaheadhrs_in = 0;
      }

   //Do the text input field.
   $rv  = "<input type=\"text\" name=\"schedaheadhrs\" size=\"15\" value=\""
          .
          (string)$schedaheadhrs_in
          .
          "\">";

   return($rv);
   }
//--------------------------------------------------------------------------------------------------------------
//Returns the HTML that should be used to identify the schedaheadhrs description on the EDIT and ADD pages.
//HTML may be marked up with <i>, <b>, and <b>.
//
function RSCS_schedaheadhrs_desc_html_01()
   {
   $rv =   "The <i>schedaheadhrs</i> is a non-negative integer that specifies the minimum number of hours that a "
         . "reservation must be made ahead of its start time by those without permission to violate scheduling rules.&nbsp; A "
         . "typical value for this field is 8.&nbsp; The intent "
         . "of the scheduling rules facilitated by this field is to ensure that an FBO has enough time to prepare an aircraft "
         . "and/or that a flight instructor has enough time to plan ahead for a lesson.&nbsp; A reservation that must be made "
         . "too close to the start time is typically made by calling the FBO.";
 
   return($rv);
   }
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//Returns the HTML that should be used to identify the usercorres on the EDIT and ADD pages.  HTML may
//be marked up with <i> and <b> and includes the trailing colon.
//
function RSCS_usercorres_id_html_01()
   {
   return("<i>usercorres:</i>");
   }
//--------------------------------------------------------------------------------------------------------------
//Returns the HTML that should be used to display the usercorres form field on the EDIT and ADD pages.
//
function RSCS_usercorres_disp_html_01($usercorres_in)
   {
   //Turn the input into a numeric value.  If it can't be turned into a numeric value, 
   //make it 0.
   if (is_numeric($usercorres_in))
      {
      $usercorres_in = (int)$usercorres_in;
      if ($usercorres_in < 0)
         {
         //Can't be negative integer.
         $usercorres_in = 0;
         }
      }
   else
      {
      //This is nothing we recognize.  Assume number 0.
      $usercorres_in = 0;
      }

   //If the integer is non-zero, try to look up the user with that index.
   if ($usercorres_in != 0)
      {
      $userdata = USRS_retrieve_by_idx($usercorres_in);
      if ($userdata !== FALSE)
         {
         $userid = $userdata["userid"];
         }
      else
         {
         $userid = $usercorres_in;
         }
      }
   else
      {
      $userid = 0;
      }

   //Do the text input field.
   $rv  = "<input type=\"text\" name=\"usercorres\" size=\"20\" value=\""
          .
          (string)$userid
          .
          "\">";

   return($rv);
   }
//--------------------------------------------------------------------------------------------------------------
//Returns the HTML that should be used to identify the schedaheadhrs description on the EDIT and ADD pages.
//HTML may be marked up with <i>, <b>, and <b>.
//
function RSCS_usercorres_desc_html_01()
   {
   $rv =   "The <i>usercorres</i> field specifies the user account of the flight instructor corresponding to the "
         . "resource, if the resource is a flight instructor.&nbsp; (It is not required that a flight instructor "
         . "resource be linked to a user account, but such linkage is the usual case.)&nbsp; If provided, this link "
         . "allows the scheduling software to send the flight instructor notification e-mails when a relevant scheduling "
         . "change is made, and to make other intelligent decisions about scheduling, permissions, and notification.&nbsp; "
         . "The user account must be specified as the userid of the account (i.e. &quot;jsmith&quot;).&nbsp; If "
         . "no user account should be linked to the resource, the integer "
         . "&quot;0&quot; should be used.";
 
   return($rv);
   }
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//Returns the HTML that should be used to identify the rstdtime on the EDIT and ADD pages.  HTML may
//be marked up with <i> and <b> and includes the trailing colon.
//
function RSCS_rstdtime_id_html_01()
   {
   return("<i>rstdtime:</i>");
   }
//--------------------------------------------------------------------------------------------------------------
//Returns the HTML that should be used to display the rstdtime form field on the EDIT and ADD pages.
//
function RSCS_rstdtime_disp_html_01($rstdtime_in)
   {
   $rv = "";

   $rstdtime_in = (string)$rstdtime_in;  //Be sure it is a string.
   
   for ($i=0; $i<48; $i++)  //For each half-hour time slot.
      {
      $hour_start   = (int)($i >> 1);
      $minute_start = (int)(($i % 2) * 30);

      $hour_end     = (int)((($i+1) % 48) >> 1);
      $minute_end   = (int)(((($i+1) % 48) % 2) * 30);

      $time_string_start = DATEFUNC_stdtimenosec($hour_start, $minute_start);
      $time_string_end   = DATEFUNC_stdtimenosec($hour_end,   $minute_end);

      $is_restricted = FALSE;
      if (strlen($rstdtime_in) >= ($i+1))
         {
         if (SubStr($rstdtime_in, $i, 1) == "R")
            $is_restricted = TRUE;
         }

      $rv .= "<input type=\"checkbox\" name=\"";
      $rv .= sprintf("rstdtime%02d", $i);
      $rv .= "\"";
      if ($is_restricted)
         $rv .= " checked";
      $rv .= ">&nbsp;";
      $rv .= $time_string_start . " - " . $time_string_end;
      if ($i != 47)
         $rv .= "<br>";      
      }

   return($rv);
   }
//--------------------------------------------------------------------------------------------------------------
//Returns the HTML that should be used to identify the schedaheadhrs description on the EDIT and ADD pages.
//HTML may be marked up with <i>, <b>, and <b>.
//
function RSCS_rstdtime_desc_html_01()
   {
   $rv =   "The <i>rstdtime</i> field specifies those half-hour time slots of a 24-hour day during which "
         . "a user without permission to break scheduling rules may not reserve a resource.&nbsp; This field "
         . "is intended to prevent students and aircraft renters from reserving flight instructors at times "
         . "of the day during which they do not desire to teach or aircraft during times of the day when they "
         . "are not available for rental.";
 
   return($rv);
   }
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//Returns the HTML that should be used to identify the password on the EDIT and ADD pages.  HTML may
//be marked up with <i> and <b> and includes the trailing colon.
//
function RSCS_password_id_html_01($curuserinfo_in)
   {
   return("<i>Password for user <b>" . $curuserinfo_in["userid"] . "</b>:</i>");
   }
//--------------------------------------------------------------------------------------------------------------
//Returns the HTML that should be used to display the rstdtime form field on the EDIT and ADD pages.
//
function RSCS_password_disp_html_01()
   {
   return("<input type=\"password\" name=\"password\" size=\"20\">");
   }
//--------------------------------------------------------------------------------------------------------------
//Returns the HTML that should be used to identify the schedaheadhrs description on the EDIT and ADD pages.
//HTML may be marked up with <i>, <b>, and <b>.
//
function RSCS_password_desc_html_01()
   {
   $rv =   "The <i>password</i> field is used to verify that the logged-in user is actually the individual "
         . "attempting to make this change.&nbsp; This is an attempt to guard against data modification or "  
         . "destruction due to unattended computers.&nbsp; If the password entered is incorrect, the user "
         . "will be automatically logged out.";
 
   return($rv);
   }
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
function RSCS_idx_validate_a(
                            $field_val_in,           //Value to be considered.
                            $action_in,              //"A" for add or "M" for modify.
                            &$field_val_out,         //May be sanitized.
                            &$errors_out,            //Appended errors.
                            &$warnings_out           //Appended warnings
                            )
   {
   //Restrict the field value in to just digits.
   $field_val_in = STRFUNC_force_stringtype_subset_truncate($field_val_in, "0123456789", 12);

   //See if can pack it into an integer.  Errors create "0", which will fail as a commit
   //attempt.
   if (is_numeric($field_val_in))
      {
      $field_val_in = (int)$field_val_in;
      if ($field_val_in < 0)
         $field_val_in = 0;
      }
   else
      {
      $field_val_in = 0;
      }

   //If the value is 0, this is suspicious.
   if ($field_val_in == 0)
      {
      $errors_out[] = "The <i>idx</i> field is not a valid integer index.";
      }

   //Return the sanitized output.
   $field_val_out = (string)$field_val_in;
   }
//--------------------------------------------------------------------------------------------------------------
function RSCS_type_validate_a(
                              $field_val_in,           //Value to be considered.
                              $action_in,              //"A" for add or "M" for modify.
                              &$field_val_out,         //May be sanitized.
                              &$errors_out,            //Appended errors.
                              &$warnings_out           //Appended warnings
                             )
   {
   //Restrict the field value in to just one digit.
   $field_val_in = STRFUNC_force_stringtype_subset_truncate($field_val_in, "0123456789", 1);

   //See if can pack it into an integer.  Errors create "-1", which will fail as a commit
   //attempt.
   if (is_numeric($field_val_in))
      {
      $field_val_in = (int)$field_val_in;
      if ($field_val_in < 0)
         $field_val_in = -1;
      }
   else
      {
      $field_val_in = -1;
      }

   //If the value is -1, this is suspicious.
   if ($field_val_in == -1)
      {
      $errors_out[] = "The <i>type</i> field is not a valid integer type.";
      }
   else if (
             ($field_val_in != RSCS_TYPE_AIRCRAFT)
             &&
             ($field_val_in != RSCS_TYPE_SIMULATOR)
             &&
             ($field_val_in != RSCS_TYPE_FLIGHTINSTRUCTOR)
           )
      {
      //This isn't an allowed value.
      $errors_out[] = "The <i>type</i> field is not a valid type (aircraft, simulator, or flight instructor).";
      }

   //Return the sanitized output.
   $field_val_out = (string)$field_val_in;
   }
//--------------------------------------------------------------------------------------------------------------
function RSCS_status_validate_a(
                                $field_val_in,           //Value to be considered.
                                $action_in,              //"A" for add or "M" for modify.
                                &$field_val_out,         //May be sanitized.
                                &$errors_out,            //Appended errors.
                                &$warnings_out           //Appended warnings
                               )
   {
   //Restrict the field value in to just one digit.
   $field_val_in = STRFUNC_force_stringtype_subset_truncate($field_val_in, "0123456789", 1);

   //See if can pack it into an integer.  Errors create "-1", which will fail as a commit
   //attempt.
   if (is_numeric($field_val_in))
      {
      $field_val_in = (int)$field_val_in;
      if ($field_val_in < 0)
         $field_val_in = -1;
      }
   else
      {
      $field_val_in = -1;
      }

   //If the value is -1, this is suspicious.
   if ($field_val_in == -1)
      {
      $errors_out[] = "The <i>status</i> field is not a valid integer.";
      }
   else if (
             ($field_val_in != RSCS_STATUS_OFFLINE)
             &&
             ($field_val_in != RSCS_STATUS_ONLINE)
           )
      {
      //This isn't an allowed value.
      $errors_out[] = "The <i>status</i> field is not a valid integer (offline or online).";
      }

   //Return the sanitized output.
   $field_val_out = (string)$field_val_in;
   }
//--------------------------------------------------------------------------------------------------------------
function RSCS_disporder_validate_a(
                                   $field_val_in,           //Value to be considered.
                                   $action_in,              //"A" for add or "M" for modify.
                                   &$field_val_out,         //May be sanitized.
                                   &$errors_out,            //Appended errors.
                                   &$warnings_out           //Appended warnings
                                  )
   {
   //Restrict the field value in to 12 digits.
   $field_val_in = STRFUNC_force_stringtype_subset_truncate($field_val_in, "0123456789", 12);

   //See if can pack it into an integer.  Errors create "0", which is acceptable for disporder.
   if (is_numeric($field_val_in))
      {
      $field_val_in = (int)$field_val_in;
      if ($field_val_in <= 0)
         $field_val_in = -1;
      }
   else
      {
      $field_val_in = -1;
      }

   //If the value is -1, this means an error was encountered.
   if ($field_val_in == -1)
      {
      $errors_out[] = "The <i>disporder</i> field is not a valid positive integer.";
      $field_val_in = 1;
      }

   //Return the sanitized output.
   $field_val_out = (string)$field_val_in;
   }
//--------------------------------------------------------------------------------------------------------------
function RSCS_initials_validate_a(
                                   $field_val_in,          //Value to be considered.
                                   $action_in,             //"A" for add or "M" for modify.
                                  &$field_val_out,         //May be sanitized.
                                  &$errors_out,            //Appended errors.
                                  &$warnings_out           //Appended warnings
                                  )
   {
   //Restrict the field value in a set of characters and to 25 characters.
   $field_val_in = STRFUNC_force_stringtype_subset_truncate($field_val_in, RSCS_INITIALS_ALLOWEDCHARS, 25);

   //Trim both sides.
   $field_val_in = Trim($field_val_in);

   //The only error is if this is zero length.
   if (strlen($field_val_in) == 0)
      {
      $errors_out[] = "The <i>initials</i> field may not be left blank.";
      }

   //Return the sanitized output.
   $field_val_out = (string)$field_val_in;
   }
//--------------------------------------------------------------------------------------------------------------
function RSCS_shortdesc_validate_a(
                                    $field_val_in,          //Value to be considered.
                                    $action_in,             //"A" for add or "M" for modify.
                                   &$field_val_out,         //May be sanitized.
                                   &$errors_out,            //Appended errors.
                                   &$warnings_out           //Appended warnings
                                  )
   {
   //Restrict the field value in a set of characters and to 50 characters.
   $field_val_in = STRFUNC_force_stringtype_subset_truncate($field_val_in, RSCS_SHORTDESC_ALLOWEDCHARS, 50);

   //Trim both sides.
   $field_val_in = Trim($field_val_in);

   //The only error is if this is zero length.
   if (strlen($field_val_in) == 0)
      {
      $errors_out[] = "The <i>shortdesc</i> field may not be left blank.";
      }

   //Return the sanitized output.
   $field_val_out = (string)$field_val_in;
   }
//--------------------------------------------------------------------------------------------------------------
function RSCS_longdesc_validate_a(
                                    $field_val_in,          //Value to be considered.
                                    $action_in,             //"A" for add or "M" for modify.
                                   &$field_val_out,         //May be sanitized.
                                   &$errors_out,            //Appended errors.
                                   &$warnings_out           //Appended warnings
                                  )
   {
   //Restrict the field value in a set of characters and to 100 characters.
   $field_val_in = STRFUNC_force_stringtype_subset_truncate($field_val_in, RSCS_LONGDESC_ALLOWEDCHARS, 100);

   //Trim both sides.
   $field_val_in = Trim($field_val_in);

   //The only error is if this is zero length.
   if (strlen($field_val_in) == 0)
      {
      $errors_out[] = "The <i>longdesc</i> field may not be left blank.";
      }

   //Return the sanitized output.
   $field_val_out = (string)$field_val_in;
   }
//--------------------------------------------------------------------------------------------------------------
function RSCS_schedaheadhrs_validate_a( 
                                        $field_val_in,          //Value to be considered.
                                        $action_in,             //"A" for add or "M" for modify.
                                       &$field_val_out,         //May be sanitized.
                                       &$errors_out,            //Appended errors.
                                       &$warnings_out           //Appended warnings
                                       )
   {
   //Restrict the field value in to 12 digits.
   $field_val_in = STRFUNC_force_stringtype_subset_truncate($field_val_in, "0123456789", 12);

   //See if can pack it into an integer.  Errors create "0", which is acceptable for schedaheadhrs.
   if (is_numeric($field_val_in))
      {
      $field_val_in = (int)$field_val_in;
      if ($field_val_in < 0)
         $field_val_in = -1;
      }
   else
      {
      $field_val_in = -1;
      }

   //If the value is -1, this means an error was encountered.
   if ($field_val_in == -1)
      {
      $errors_out[] = "The <i>schedaheadhrs</i> field is not a valid non-negative integer.";
      $field_val_in = 0;
      }

   //Return the sanitized output.
   $field_val_out = (string)$field_val_in;
   }
//--------------------------------------------------------------------------------------------------------------
function RSCS_usercorres_validate_a(
                                     $field_val_in,          //Value to be considered.
                                     $action_in,             //"A" for add or "M" for modify.
                                    &$field_val_out,         //May be sanitized.
                                    &$errors_out,            //Appended errors.
                                    &$warnings_out           //Appended warnings
                                   )
   {
   //Restrict the field value in a set of characters and to 20 characters.
   $field_val_in = STRFUNC_force_stringtype_subset_truncate($field_val_in, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", 20);

   //Force the upper-case elements of the string to lower-case.
   $field_val_in = StrToLower($field_val_in);

   if (strlen($field_val_in) == 0)
      {
      //The string length seems to be zero.  This may be a synonym for "no linked user".  Just
      //say "0".
      $field_val_out = "0";
      return;
      }
   else if ($field_val_in == "0")
      {
      //"0".
      $field_val_out = "0";
      return;
      }
   else
      {
      if (! USRS_userid_membership_test($field_val_in))
         {
         $errors_out[] = "The <i>usercorres</i> cannot be parsed.";
         $field_val_out = "0";
         return;
         }

      //See if this is a user.
      $result = USRS_userid_idx_map($field_val_in);
      if ($result === FALSE)
         {
         //No such user can be found.  This is an error.
         $errors_out[] = "The <i>usercorres</i> user <i>" . $field_val_in . "</i> does not exist.";
         $field_val_out = "0";
         return;
         }
      else
         {
         //User found.
         $field_val_out = (string)$result;
         return;
         }
      }
   }
//--------------------------------------------------------------------------------------------------------------
//Given a comma-separated list of integers (direct from the schedalonerscs), and an associative array
//of resources indexed by idx then field, creates a comma-separated list of short descriptors.  Used to format resources
//for display of what each user is allowed to rent without an instructor.  Any indices that don't correspond
//to resources are just ignored.
//
function RSCS_csl_to_short_rscs_list_a($csl_in, $rscs_in)
   {
   //If the resource list is non-existent, can't do much, anyway.
   if ($rscs_in === FALSE)
      return("");

   $exploded_list = CSL_csl_to_string_array($csl_in);

   if ($exploded_list === FALSE)
      {
      return("");
      }

   $rv = "";

   for ($i=0; $i<count($exploded_list); $i++)
      {
      $index = (int)$exploded_list[$i];

      if (isset($rscs_in[$index]["initials"]))
         {
         $rv =   $rv
               . $rscs_in[$index]["initials"]
               . ", ";
         }      
      }

   //If we're here, we just need to remove the final two characters.
   $rv = SubStr($rv, 0, strlen($rv) - 2);

   return($rv);
   }
//
//--------------------------------------------------------------------------------------------------------------
//End of $RCSfile: rscsx.inc,v $.
//--------------------------------------------------------------------------------------------------------------
?>
