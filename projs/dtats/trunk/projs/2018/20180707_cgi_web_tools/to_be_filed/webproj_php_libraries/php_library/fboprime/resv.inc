<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/resv.inc 205 2018-07-15 19:00:51Z dashley $
//--------------------------------------------------------------------------------------------------------------
//resv.inc--FboPrime Database resv Table Manipulation Functions
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
//Constants for different types of reservations.
define("RESV_TYPE_BANNER",                                 0                         );
define("RESV_TYPE_ACTIVE",                                 1                         );
define("RESV_TYPE_STANDBY",                                2                         );
//
//--------------------------------------------------------------------------------------------------------------
//Retrieves a two dimensional associative array corresponding to the RESV record
//with the passed IDX, or FALSE if the record does not exist.
//
function RESV_retrieve_by_idx($idx)
   {
   global $GLOBAL_dbhandle;

   //Form the query string.
   $query_string = "SELECT * FROM resv WHERE idx=\""
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
//Retrieves two two-dimensional arrays of elements containing full information about each reservation that 
//overlaps into the passed time window.  Two arrays are necessary because we have the need to sort both by
//flight instructor and by aircraft/simulator.
//
//Reservations are sorted first by index of the flight instructor/resource, then by reservation, then by the 
//start time, then by the tie-breaker SGUID.
//
//The start-time ordering is necessary to be sure that within a displayed row, one doesn't have to sort
//before trying to display.
//
//For each of the two arrays, a parallel search array is also returned.  The indices of the parallel search
//array are the same as the corresponding indices of the data array, and the values are the flight
//instructor/resource index.  The purpose of the parallel search array are to assist in locating the data
//for a given flight instructor/resource by index in the data array as rapidly as possible.
//
//If no reservations apply for either of the two queries, FALSE is returned in both the data array and
//the search array.
//
function RESV_resvns_in_time_window( $stime_startwindow_in, 
                                     $stime_endwindow_in,
                                    &$flight_inst_data_array,
                                    &$flight_inst_search_array,
                                    &$resource_data_array,
                                    &$resource_search_array )
   {
   global $GLOBAL_dbhandle;

   //------------------------------------------------------------------------------------------------------------
   //Start with a clean slate for the output variables.
   //
   if (isset($flight_inst_data_array))
      unset($flight_inst_data_array);
   if (isset($flight_inst_search_array))
      unset($flight_inst_search_array);
   if (isset($resource_data_array))
      unset($resource_data_array);
   if (isset($resource_search_array))
      unset($resource_search_array);
   //
   //------------------------------------------------------------------------------------------------------------
   //Flight instructor half.
   //
   $query_string = "SELECT * FROM resv WHERE finstid!=\"0\" AND finsttimestart<\""
                   .
                   $stime_endwindow_in
                   .
                   "\" AND finsttimeend>\""
                   .
                   $stime_startwindow_in
                   .
                   "\" ORDER BY finstid, type, finsttimestart, crsguid ASC";

   $result = mysql_query($query_string, $GLOBAL_dbhandle);

   //If the query did not go through successfully, return FALSE to the caller.
   //
   if ($result === FALSE)
      {
      //The caller gets FALSE signaling no data.
      $flight_inst_data_array   = FALSE;
      $flight_inst_search_array = FALSE;
      }
   //
   //If the number of rows in the result set is 0, also give the caller FALSE.
   else if (mysql_num_rows($result) <= 0)
      {
      //Technically, we got a result set, so free it.
      mysql_free_result($result);
   
      //The caller gets FALSE signaling no data.
      $flight_inst_data_array   = FALSE;
      $flight_inst_search_array = FALSE;
      }
   else
      {
      //If we're here, we have a valid result set.  Each row of the returned array is 
      //the expected fields from the resv table.

      //Copy out the results to the array we'll return.
      while ($row = mysql_fetch_assoc($result))
         {
         $flight_inst_data_array[]   = $row;              //Assign the data.
         $flight_inst_search_array[] = $row["finstid"];   //Set the search index.
         }   

      //Free memory.
      mysql_free_result($result);
      }

   //------------------------------------------------------------------------------------------------------------
   //Resource half.
   //
   $query_string = "SELECT * FROM resv WHERE acftsimid!=\"0\" AND acftsimtimestart<\""
                   .
                   $stime_endwindow_in
                   .
                   "\" AND acftsimtimeend>\""
                   .
                   $stime_startwindow_in
                   .
                   "\" ORDER BY acftsimid, type, acftsimtimestart, crsguid ASC";

   $result = mysql_query($query_string, $GLOBAL_dbhandle);

   //If the query did not go through successfully, return FALSE to the caller.
   //
   if ($result === FALSE)
      {
      //The caller gets FALSE signaling no data.
      $resource_data_array   = FALSE;
      $resource_search_array = FALSE;
      }
   //
   //If the number of rows in the result set is 0, also give the caller FALSE.
   else if (mysql_num_rows($result) <= 0)
      {
      //Technically, we got a result set, so free it.
      mysql_free_result($result);
   
      //The caller gets FALSE signaling no data.
      $resource_data_array   = FALSE;
      $resource_search_array = FALSE;
      }
   else
      {
      //If we're here, we have a valid result set.  Each row of the returned array is 
      //the expected fields from the resv table.

      //Copy out the results to the array we'll return.
      while ($row = mysql_fetch_assoc($result))
         {
         $resource_data_array[]   = $row;                //Assign the data.
         $resource_search_array[] = $row["acftsimid"];   //Set the search index.
         }   

      //Free memory.
      mysql_free_result($result);
      }
   }
//
//--------------------------------------------------------------------------------------------------------------
//Extracts the records pertaining to a certain flight instructor from an array returned from
//the RESV_resvns_in_time_window() function, using the search array as a search aid.  Returns FALSE
//if no match.
//
//Records must not have been rearranged (they must still be sorted by the flight instructor ID).
// 
function RESV_extract_finst_records($data_array_in, $search_array_in, $idx_to_find_in)
   {
   //If the data array or search array are FALSE, then the result is FALSE, i.e. subset of the
   //empty set is also the empty set.
   if (($data_array_in === FALSE) || ($search_array_in === FALSE))
      {
      return(FALSE);
      }

   //Find the first record with the passed index, if any.  This is enough, as the others will be contiguous.
   $index = array_search($idx_to_find_in, $search_array_in);

   //If there is no match, return FALSE.
   if (($index === FALSE) || ($index === NULL))
      {
      return(FALSE);
      }

   //If we're here, we have success.  Find out how many elements in the array, for reference.
   $n = count($data_array_in);

   //Tack the original search success onto the return value.
   $rv[] = $data_array_in[$index];

   //Find any others.
   $index++;
   while (($index < $n) && ($search_array_in[$index] == $idx_to_find_in))
      {
      $rv[] = $data_array_in[$index];
      $index++;
      }

   //Return the results.
   return($rv);
   }
//
//--------------------------------------------------------------------------------------------------------------
//Extracts the records pertaining to a certain resource (aircraft/simulator) from an array returned from
//the RESV_resvns_in_time_window() function, using the search array as a search aid.  Returns FALSE
//if no match.
//
//Records must not have been rearranged (they must still be sorted by the resource ID).
// 
function RESV_extract_resource_records($data_array_in, $search_array_in, $idx_to_find_in)
   {
   //If the data array or search array are FALSE, then the result is FALSE, i.e. subset of the
   //empty set is also the empty set.
   if (($data_array_in === FALSE) || ($search_array_in === FALSE))
      {
      return(FALSE);
      }

   //Find the first record with the passed index, if any.  This is enough, as the others will be contiguous.
   $index = array_search($idx_to_find_in, $search_array_in);

   //If there is no match, return FALSE.
   if (($index === FALSE) || ($index === NULL))
      {
      return(FALSE);
      }

   //If we're here, we have success.  Find out how many elements in the array, for reference.
   $n = count($data_array_in);

   //Tack the original search success onto the return value.
   $rv[] = $data_array_in[$index];

   //Find any others.
   $index++;
   while (($index < $n) && ($search_array_in[$index] == $idx_to_find_in))
      {
      $rv[] = $data_array_in[$index];
      $index++;
      }

   //Return the results.
   return($rv);
   }
//
//--------------------------------------------------------------------------------------------------------------
//End of $RCSfile: resv.inc,v $.
//--------------------------------------------------------------------------------------------------------------
?>
