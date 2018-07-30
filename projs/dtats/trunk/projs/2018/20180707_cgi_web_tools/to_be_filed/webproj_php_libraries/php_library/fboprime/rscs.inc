<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/rscs.inc 205 2018-07-15 19:00:51Z dashley $
//--------------------------------------------------------------------------------------------------------------
//rscs.inc--FboPrime Database rscs Table Manipulation Functions
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
//Contains functions related to [operations on] the rscs table of the database.
//--------------------------------------------------------------------------------------------------------------
//
require_once("db.inc");
require_once("global.inc");
require_once("sguid.inc");
//
//--------------------------------------------------------------------------------------------------------------
//Constants for rscs table fields.
//
//Constants for the type field of the rscs table.
define("RSCS_TYPE_AIRCRAFT",                               0                         );
define("RSCS_TYPE_SIMULATOR",                              1                         );
define("RSCS_TYPE_FLIGHTINSTRUCTOR",                       2                         );
//
//Constants for the status field of the rscs table.
define("RSCS_STATUS_OFFLINE",                              0                         );
define("RSCS_STATUS_ONLINE",                               1                         );
//
//--------------------------------------------------------------------------------------------------------------
//Inserts a new record into the RSCS database, using the passed associative array to assign the fields.
//Each element of the associative array is indexed by a field name.
//
//The function returns the integer index of the record added.
//
//This operation cannot fail.  The autoincrement index is the primary key, so no duplicates or other
//error conditions are meaningful.
//
function RSCS_insert($arg)
   {
   global $GLOBAL_dbhandle;
   global $GLOBAL_dblocked;

   //Build the query string with each successive parameter.
   //
   //type
   //------
   if (! isset($arg["type"]))
      $pushval = RSCS_TYPE_AIRCRAFT;
   else
      $pushval = $arg["type"];
   $query_string = "INSERT INTO rscs SET type=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"";
   //
   //status
   //------
   if (! isset($arg["status"]))
      $pushval = RSCS_STATUS_ONLINE;
   else
      $pushval = $arg["status"];
   $query_string .= (", status=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //disporder
   //---------
   if (! isset($arg["disporder"]))
      $pushval = 0;
   else
      $pushval = $arg["disporder"];
   $query_string .= (", disporder=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //longdesc
   //--------
   if (! isset($arg["longdesc"]))
      $pushval = "";
   else
      $pushval = $arg["longdesc"];
   $query_string .= (", longdesc=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //shortdesc
   //---------
   if (! isset($arg["shortdesc"]))
      $pushval = "";
   else
      $pushval = $arg["shortdesc"];
   $query_string .= (", shortdesc=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //initials
   //--------
   if (! isset($arg["initials"]))
      $pushval = "";
   else
      $pushval = $arg["initials"];
   $query_string .= (", initials=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //rstdtime
   //--------
   if (! isset($arg["rstdtime"]))
      $pushval = "UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU";
   else
      $pushval = $arg["rstdtime"];
   $query_string .= (", rstdtime=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //schedaheadhrs
   //-------------
   if (! isset($arg["schedaheadhrs"]))
      $pushval = (int) 0;
   else
      $pushval = $arg["schedaheadhrs"];
   $query_string .= (", schedaheadhrs=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //usercorres
   //----------
   if (! isset($arg["usercorres"]))
      $pushval = (int) 0;
   else
      $pushval = $arg["usercorres"];
   $query_string .= (", usercorres=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //crmodsguid
   //----------
   if (! isset($arg["crmodsguid"]))
      $pushval = SGUID_sguid();
   else
      $pushval = $arg["crmodsguid"];
   $query_string .= (", crmodsguid=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //echo " " . $query_string . " ";

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
//Retrieves a two-dimensional array of elements containing full information about each resource that is
//online for the purpose of displaying the dayview scheduling page.  Resources are sorted by the 
//specified display order, then by type, then (as the ultimate tie-breaker), by index.
//
//If no resources are online, FALSE is returned.
//
function RSCS_rscs_list_dayview_online()
   {
   global $GLOBAL_dbhandle;

   $query_string = "SELECT * FROM rscs WHERE status="
                   .
                   RSCS_STATUS_ONLINE
                   .
                   " ORDER BY disporder, type, idx ASC";

   $result = mysql_query($query_string, $GLOBAL_dbhandle);

   //If the query did not go through successfully, return FALSE to the caller.
   //
   if ($result === FALSE)
      {
      return(FALSE);
      }

   //If the number of rows in the result set is 0, also give the caller FALSE.
   if (mysql_num_rows($result) <= 0)
      {
      //Technically, we got a result set, so free it.
      mysql_free_result($result);
   
      //The caller gets FALSE.
      return(FALSE);
      }

   //If we're here, we have a valid result set.  Each row of the returned array is 
   //the expected fields from the rscs table.

   //Copy out the results to the array we'll return.
   while ($row = mysql_fetch_assoc($result))
      {
      $rv[] = $row;
      }   

   //Free memory.
   mysql_free_result($result);

   //Give the caller the array.
   return($rv);
   }
//
//--------------------------------------------------------------------------------------------------------------
//End of $RCSfile: rscs.inc,v $.
//--------------------------------------------------------------------------------------------------------------
?>
