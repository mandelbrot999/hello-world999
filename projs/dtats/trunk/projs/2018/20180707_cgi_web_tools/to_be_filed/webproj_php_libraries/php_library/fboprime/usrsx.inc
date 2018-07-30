<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/usrsx.inc 205 2018-07-15 19:00:51Z dashley $
//--------------------------------------------------------------------------------------------------------------
//usrsx.inc--FboPrime Database usrs Table Manipulation Functions (Not Scheduler Critical)
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
require_once("global.inc");
require_once("sguid.inc");
require_once("usrs.inc");
//
//--------------------------------------------------------------------------------------------------------------
//Retrieves key information about active users, ordered by:
//  a)Last name.
//  b)First name.
//  c)Middle Initial.
//  d)Database index (the decisive tie breaker).
//
//This information is displayed on the active users list page.
//
//Although there is some minor risk of memory exhaustion, it is too slow to grab only the indices
//and then yank the info as the table is generated.
//
//Returns FALSE if no records.
//
function USRS_get_info_users_active_a()
   {
   global $GLOBAL_dbhandle;

   //Form the query string.
   $query_string = "SELECT idx,fname,lname,mname,userid,mostrecentlogin,acctexpdate,schedalonerscs FROM usrs WHERE status=\""
                   .
                   USRS_STATUS_ACTIVE
                   .
                   "\" ORDER BY lname ASC, fname ASC, mname ASC, idx ASC";

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
            $rv[$i] = $temp;
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
//Retrieves key information about inactive users, ordered by:
//  a)Last name.
//  b)First name.
//  c)Middle Initial.
//  d)Database index (the decisive tie breaker).
//
//This information is displayed on the inactive users list page.
//
//Although there is some minor risk of memory exhaustion, it is too slow to grab only the indices
//and then yank the info as the table is generated.
//
//Returns FALSE if no records.
//
function USRS_get_info_users_inactive_a()
   {
   global $GLOBAL_dbhandle;

   //Form the query string.
   $query_string = "SELECT idx,fname,lname,mname,userid,mostrecentlogin,acctexpdate,schedalonerscs FROM usrs WHERE status=\""
                   .
                   USRS_STATUS_INACTIVE
                   .
                   "\" ORDER BY lname ASC, fname ASC, mname ASC, idx ASC";

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
            $rv[$i] = $temp;
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
//Retrieves key information about all users, and populates an array indexed by the database index with this
//information.  If there are no users, FALSE is returned.
//
function USRS_get_info_users_all_a()
   {
   global $GLOBAL_dbhandle;

   //Form the query string.
   $query_string = "SELECT idx,fname,mname,lname FROM usrs";

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
            $temp             = mysql_fetch_assoc($result);
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
//Given a user's first name, middle name or intitial, and last name, forms a name
//string.  This is used for the users lists.
//
function USRS_display_name_string($fname_in, $mname_in, $lname_in)
   {
   $fnl = strlen($fname_in);
   $mnl = strlen($mname_in);
   $lnl = strlen($lname_in);

   if (!$lnl)
      {
      //This is a no-no.
      return("UNKNOWN USER");
      }
   else if ($lnl && !$fnl)
      {
      return($lname_in);
      }
   else
      {
      if ($mnl)
         {
         return($lname_in . ", " . $fname_in . " " . SubStr($mname_in, 0, 1) . ".");
         }
      else
         {
         return($lname_in . ", " . $fname_in);
         }
      }
   }
//--------------------------------------------------------------------------------------------------------------
//Stuffs the pwhash field of a usrs record by index.  There is
//no result code.  The temporary password is destroyed at the same time.
//
//This operation is considered exempt from the modification SGUID checks--the password
//is a separate matter and not part of the normal field edits.
//
function USRS_pwhash_stuff($idx_in, $pwhash_in)
   {
   global $GLOBAL_dbhandle;

   //Set the password hash with a single SQL statement.
   $query_string = "UPDATE usrs SET pwhash=\"" . $pwhash_in . "\", lostpwhash=\"\", lostpwgentime=\"\" WHERE idx=\"" . $idx_in . "\"";

   //Run the query.  We don't much care whether it fails or succeeds (nothing to be done, anyway).
   mysql_query($query_string, $GLOBAL_dbhandle);
   }
//
//--------------------------------------------------------------------------------------------------------------
//Description
//   Adds or modifies a USRS record.  Certain parameters specify what is expected.
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
function USRS_record_add_modify($action_in, $rec_in, &$result_code_out, &$errors_out, &$warnings_out)
   {
   global $GLOBAL_dbhandle;
   global $GLOBAL_dblocked;
   global $CONFIG_FBO_USER_CATEGORIES;

   //Variable remembers if are terminating the function (i.e. something fatal has been
   //encountered).
   $in_termination_sequence = FALSE;

   //Error array and warnings array start at element 0.
   //
   $e_array_idx = 0;
   $w_array_idx = 0;

   //Take a look at the action.  It must be one of the two valid codes, "A" or "M".
   //
   if (!$in_termination_sequence)
      {
      if (($action_in != "A") && ($action_in != "M"))
         {
         $errors_out_local[$e_array_idx] = USRS_ERROR_ACTION_PAR_ILLEGAL;
         $e_array_idx++;
         $in_termination_sequence = TRUE;
         }
      }

   //Take a look at the index.  If it is present, it must be a positive integer or the
   //string equivalent of a positive integer.
   //
   if (!$in_termination_sequence)
      {
      if (isset($rec_in["idx"]))
         {
         if (DB_table_index_short_validity_check_zna($rec_in["idx"]))
            {
            //The variable is logically an integer, and the function said it was
            //in the valid range.  If it is an integer, leave it alone, otherwise
            //convert it to an integer.
            //
            if (!is_int($rec_in["idx"]))
               {
               $rec_in["idx"] = intval($rec_in["idx"]);
               }
            }
         else
            {
            //The value isn't an integer and can't be converted to an integer.
            //Error out.
            $errors_out_local[$e_array_idx] = USRS_ERROR_IDX_ILLEGAL;
            $e_array_idx++;
            $in_termination_sequence = TRUE;
            }
         }
      }

   //Take a look at the userid.  If that is present, it has to be sane.
   //
   if (!$in_termination_sequence)
      {
      if (isset($rec_in["userid"]))
         {
         //Canonically, the userid has to be all lower-case and can't
         //contain any extra padding.  If it ain't a string, it will
         //be flagged as an error a few lines down by the membership test
         //function.
         //
         if (is_string($rec_in["userid"]))
            {
            $rec_in["userid"] = StrToLower(Trim($rec_in["userid"]));
            } 

         if (USRS_userid_membership_test($rec_in["userid"]) === TRUE)
            {
            //The userid is fine.
            //
            }
         else
            {
            //The userid is illegal.
            //
            $errors_out_local[$e_array_idx] = USRS_ERROR_USERID_ILLEGAL;
            $e_array_idx++;
            $in_termination_sequence = TRUE;
            }
         }
      }

   //-----------------------------------------------------------
   //TODO:  Add code to confine and error-trap the other fields.
   //-----------------------------------------------------------

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
         if (isset($rec_in["idx"]))
            {
            //This is an error because the index is assigned automatically--it isn't
            //allowed to specify it.
            //
            $errors_out_local[$e_array_idx] = USRS_ERROR_IDX_ON_ADD;
            $e_array_idx++;
            $in_termination_sequence = TRUE;
            }
         else if (!isset($rec_in["userid"]))
            {
            //The userid has to be present on an add.  Note that it is checked
            //for validity if it is present above.
            //
            $errors_out_local[$e_array_idx] = USRS_ERROR_NO_USERID_ON_ADD;
            $e_array_idx++;
            $in_termination_sequence = TRUE;
            }
         else if (USRS_userid_idx_map($rec_in["userid"]) !== FALSE)
            {
            //The userid already exists ... illegal.
            //
            $errors_out_local[$e_array_idx] = USRS_ERROR_DUP_USERID_ON_ADD;
            $e_array_idx++;
            $in_termination_sequence = TRUE;
            }
         }
      else //action is modify
         {
         //If the index is present, try to get the record with the passed
         //index.  If not present, error.
         //
         if (isset($rec_in["idx"]))
            {
            $modify_rec = USRS_retrieve_by_userid($rec_in["idx"]);

            if ($modify_rec === FALSE)
               {
               //Rec with that idx does not exist.
               //
               $errors_out_local[$e_array_idx] = USRS_ERROR_MOD_REC_NOT_PRESENT;
               $e_array_idx++;
               $in_termination_sequence = TRUE;
               }
            else //Record was found by index.
               {
               //Check to be sure userid, if it exists, is consistent.
               if (isset($rec_in["userid"]))
                  {
                  if ($rec_in["userid"] != $modify_rec["userid"])
                     {
                     //On modification, index and userid do not match.
                     //
                     $errors_out_local[$e_array_idx] = USRS_ERROR_MOD_IDX_USERID_INCONSISTENT;
                     $e_array_idx++;
                     $in_termination_sequence = TRUE;
                     }
                  }
               }
            }
         else if (isset($rec_in["userid"]))
            {
            //The userid was specified, but not the idx.  Check to be sure that record exists,
            //if not, error out, if so, keep track of the index.
            //
            $modify_rec = USRS_userid_idx_map($rec_in["userid"]);

            if ($modify_rec === FALSE)
               {
               //The userid does not exist.  Can't identify this record to modify.
               //Error out.
               //
               $errors_out_local[$e_array_idx] = USRS_ERROR_MOD_REC_NOT_PRESENT;
               $e_array_idx++;
               $in_termination_sequence = TRUE;
               }
            else
               {
               //The record corresponding to the userid does exist.  Stuff the
               //index to save us time later.
               //
               $rec_in["idx"] = $modify_rec["idx"];
               }
            }
         else
            {
            //There isn't enough information to identify the record to modify (no idx,
            //no userid).  Have to error out.
            //
            $errors_out_local[$e_array_idx] = USRS_ERROR_MOD_REC_NOT_PRESENT;
            $e_array_idx++;
            $in_termination_sequence = TRUE;
            }
         }

      //If the command is to modify, look for an editing collision.
      //
      if (!$in_termination_sequence)
         {
         if ($action_in == "M")
            {
            if ($rec_in["crmodsguid"] != $modify_rec["crmodsguid"])
               {
               $errors_out_local[$e_array_idx] = USRS_ERROR_EDITING_COLLISION;
               $e_array_idx++;
               $in_termination_sequence = TRUE;
               }
            }
         }

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

         if ($action_in == "A")
            {
            //Add
            //
            $query_string = "INSERT INTO usrs SET status=\"";
            //
            //-----------------------------------------------------------------------------------------
            //status
            //-----------------------------------------------------------------------------------------
            if (isset($rec_in["status"]))
               {
               $query_string .= mysql_real_escape_string((string)$rec_in["status"], $GLOBAL_dbhandle);
               }
            else
               {
               $query_string .= mysql_real_escape_string((string)USRS_STATUS_ACTIVE, $GLOBAL_dbhandle);
               }
            $query_string .= "\", seclvl=\"";
            //
            //-----------------------------------------------------------------------------------------
            //seclvl
            //-----------------------------------------------------------------------------------------
            if (isset($rec_in["seclvl"]))
               {
               $query_string .= mysql_real_escape_string((string)$rec_in["seclvl"], $GLOBAL_dbhandle);
               }
            else
               {
               //Expression below gets last entry from the lookup table.
               //
               $query_string .= mysql_real_escape_string((string)($CONFIG_FBO_USER_CATEGORIES[count($CONFIG_FBO_USER_CATEGORIES) - 4]), 
                                                         $GLOBAL_dbhandle);
               }
            $query_string .= "\", userid=\"";
            //
            //-----------------------------------------------------------------------------------------
            //userid (this field is mandatory)
            //-----------------------------------------------------------------------------------------
            $query_string .= mysql_real_escape_string((string)$rec_in["userid"], $GLOBAL_dbhandle);
            $query_string .= "\", role=\"";
            //
            //-----------------------------------------------------------------------------------------
            //role
            //-----------------------------------------------------------------------------------------
            if (isset($rec_in["role"]))
               {
               $query_string .= mysql_real_escape_string((string)$rec_in["role"], $GLOBAL_dbhandle);
               }
            else
               {
               $query_string .= mysql_real_escape_string((string)USRS_ROLE_CUSTNONPILOT, $GLOBAL_dbhandle);
               }
            $query_string .= "\", perm=\"";
            //
            //-----------------------------------------------------------------------------------------
            //perm
            //-----------------------------------------------------------------------------------------
            if (isset($rec_in["perm"]))
               {
               $query_string .= mysql_real_escape_string($rec_in["perm"], $GLOBAL_dbhandle);
               }
            else
               {
               $query_string .= mysql_real_escape_string("", $GLOBAL_dbhandle);
               }
            $query_string .= "\", sex=\"";
            //
            //-----------------------------------------------------------------------------------------
            //sex
            //-----------------------------------------------------------------------------------------
            if (isset($rec_in["sex"]))
               {
               $query_string .= mysql_real_escape_string((string)$rec_in["sex"], $GLOBAL_dbhandle);
               }
            else
               {
               $query_string .= mysql_real_escape_string((string)USRS_SEX_UNSPECIFIED, $GLOBAL_dbhandle);
               }
            $query_string .= "\", title=\"";
            //
            //-----------------------------------------------------------------------------------------
            //title
            //-----------------------------------------------------------------------------------------
            if (isset($rec_in["title"]))
               {
               $query_string .= mysql_real_escape_string((string)$rec_in["title"], $GLOBAL_dbhandle);
               }
            else
               {
               //Empty string.
               }
            $query_string .= "\", fname=\"";
            //
            //-----------------------------------------------------------------------------------------
            //fname
            //-----------------------------------------------------------------------------------------
            if (isset($rec_in["fname"]))
               {
               $query_string .= mysql_real_escape_string((string)$rec_in["fname"], $GLOBAL_dbhandle);
               }
            else
               {
               //Empty string.
               }
            $query_string .= "\", mname=\"";
            //
            //-----------------------------------------------------------------------------------------
            //mname
            //-----------------------------------------------------------------------------------------
            if (isset($rec_in["mname"]))
               {
               $query_string .= mysql_real_escape_string((string)$rec_in["mname"], $GLOBAL_dbhandle);
               }
            else
               {
               //Empty string.
               }
            $query_string .= "\", lname=\"";
            //
            //-----------------------------------------------------------------------------------------
            //lname
            //-----------------------------------------------------------------------------------------
            if (isset($rec_in["lname"]))
               {
               $query_string .= mysql_real_escape_string((string)$rec_in["lname"], $GLOBAL_dbhandle);
               }
            else
               {
               //Empty string.
               }
            $query_string .= "\", suffix=\"";
            //
            //-----------------------------------------------------------------------------------------
            //suffix
            //-----------------------------------------------------------------------------------------
            if (isset($rec_in["suffix"]))
               {
               $query_string .= mysql_real_escape_string((string)$rec_in["suffix"], $GLOBAL_dbhandle);
               }
            else
               {
               //Empty string.
               }
            $query_string .= "\", adl1=\"";
            //
            //-----------------------------------------------------------------------------------------
            //adl1
            //-----------------------------------------------------------------------------------------
            if (isset($rec_in["adl1"]))
               {
               $query_string .= mysql_real_escape_string((string)$rec_in["adl1"], $GLOBAL_dbhandle);
               }
            else
               {
               //Empty string.
               }
            $query_string .= "\", adl2=\"";
            //
            //-----------------------------------------------------------------------------------------
            //adl2
            //-----------------------------------------------------------------------------------------
            if (isset($rec_in["adl1"]))
               {
               $query_string .= mysql_real_escape_string((string)$rec_in["adl2"], $GLOBAL_dbhandle);
               }
            else
               {
               //Empty string.
               }
            $query_string .= "\", city=\"";
            //
            //-----------------------------------------------------------------------------------------
            //city
            //-----------------------------------------------------------------------------------------
            if (isset($rec_in["city"]))
               {
               $query_string .= mysql_real_escape_string((string)$rec_in["city"], $GLOBAL_dbhandle);
               }
            else
               {
               //Empty string.
               }
            $query_string .= "\", stateprovince=\"";
            //
            //-----------------------------------------------------------------------------------------
            //stateprovince
            //-----------------------------------------------------------------------------------------
            if (isset($rec_in["stateprovince"]))
               {
               $query_string .= mysql_real_escape_string((string)$rec_in["stateprovince"], $GLOBAL_dbhandle);
               }
            else
               {
               //Empty string.
               }
            $query_string .= "\", zippostalcode=\"";
            //
            //-----------------------------------------------------------------------------------------
            //zippostalcode
            //-----------------------------------------------------------------------------------------
            if (isset($rec_in["zippostalcode"]))
               {
               $query_string .= mysql_real_escape_string((string)$rec_in["zippostalcode"], $GLOBAL_dbhandle);
               }
            else
               {
               //Empty string.
               }
            $query_string .= "\", country=\"";
            //
            //-----------------------------------------------------------------------------------------
            //country
            //-----------------------------------------------------------------------------------------
            if (isset($rec_in["country"]))
               {
               $query_string .= mysql_real_escape_string((string)$rec_in["country"], $GLOBAL_dbhandle);
               }
            else
               {
               //Empty string.
               }
            $query_string .= "\", pwhash=\"";
            //
            //-----------------------------------------------------------------------------------------
            //pwhash
            //-----------------------------------------------------------------------------------------
            if (isset($rec_in["pwhash"]))
               {
               $query_string .= mysql_real_escape_string((string)$rec_in["pwhash"], $GLOBAL_dbhandle);
               }
            else
               {
               //Empty string.
               }
            $query_string .= "\", lostpwhash=\"";
            //
            //-----------------------------------------------------------------------------------------
            //lostpwhash
            //-----------------------------------------------------------------------------------------
            if (isset($rec_in["lostpwhash"]))
               {
               $query_string .= mysql_real_escape_string((string)$rec_in["lostpwhash"], $GLOBAL_dbhandle);
               }
            else
               {
               //Empty string.
               }
            $query_string .= "\", lostpwgentime=\"";
            //
            //-----------------------------------------------------------------------------------------
            //lostpwgentime
            //-----------------------------------------------------------------------------------------
            if (isset($rec_in["lostpwgentime"]))
               {
               $query_string .= mysql_real_escape_string((string)$rec_in["lostpwgentime"], $GLOBAL_dbhandle);
               }
            else
               {
               //Empty string.
               }
            $query_string .= "\", ratings=\"";
            //
            //-----------------------------------------------------------------------------------------
            //ratings
            //-----------------------------------------------------------------------------------------
            if (isset($rec_in["ratings"]))
               {
               $query_string .= mysql_real_escape_string((string)$rec_in["ratings"], $GLOBAL_dbhandle);
               }
            else
               {
               //Empty string.
               }
            $query_string .= "\", bfrlicexpdate=\"";
            //
            //-----------------------------------------------------------------------------------------
            //bfrlicexpdate
            //-----------------------------------------------------------------------------------------
            if (isset($rec_in["bfrlicexpdate"]))
               {
               $query_string .= mysql_real_escape_string((string)$rec_in["bfrlicexpdate"], $GLOBAL_dbhandle);
               }
            else
               {
               //Empty string.
               }
            $query_string .= "\", medexpdate=\"";
            //
            //-----------------------------------------------------------------------------------------
            //medexpdate
            //-----------------------------------------------------------------------------------------
            if (isset($rec_in["medexpdate"]))
               {
               $query_string .= mysql_real_escape_string((string)$rec_in["medexpdate"], $GLOBAL_dbhandle);
               }
            else
               {
               //Empty string.
               }
            $query_string .= "\", restrictions=\"";
            //
            //-----------------------------------------------------------------------------------------
            //restrictions
            //-----------------------------------------------------------------------------------------
            if (isset($rec_in["restrictions"]))
               {
               $query_string .= mysql_real_escape_string((string)$rec_in["restrictions"], $GLOBAL_dbhandle);
               }
            else
               {
               //Empty string.
               }
            $query_string .= "\", dayphone=\"";
            //
            //-----------------------------------------------------------------------------------------
            //dayphone
            //-----------------------------------------------------------------------------------------
            if (isset($rec_in["dayphone"]))
               {
               $query_string .= mysql_real_escape_string((string)$rec_in["dayphone"], $GLOBAL_dbhandle);
               }
            else
               {
               //Empty string.
               }
            $query_string .= "\", eveningphone=\"";
            //
            //-----------------------------------------------------------------------------------------
            //eveningphone
            //-----------------------------------------------------------------------------------------
            if (isset($rec_in["eveningphone"]))
               {
               $query_string .= mysql_real_escape_string((string)$rec_in["eveningphone"], $GLOBAL_dbhandle);
               }
            else
               {
               //Empty string.
               }
            $query_string .= "\", em1=\"";
            //
            //-----------------------------------------------------------------------------------------
            //em1
            //-----------------------------------------------------------------------------------------
            if (isset($rec_in["em1"]))
               {
               $query_string .= mysql_real_escape_string((string)$rec_in["em1"], $GLOBAL_dbhandle);
               }
            else
               {
               //Empty string.
               }
            $query_string .= "\", em2=\"";
            //
            //-----------------------------------------------------------------------------------------
            //em2
            //-----------------------------------------------------------------------------------------
            if (isset($rec_in["em2"]))
               {
               $query_string .= mysql_real_escape_string((string)$rec_in["em2"], $GLOBAL_dbhandle);
               }
            else
               {
               //Empty string.
               }
            $query_string .= "\", acctexpdate=\"";
            //
            //-----------------------------------------------------------------------------------------
            //acctexpdate
            //-----------------------------------------------------------------------------------------
            if (isset($rec_in["acctexpdate"]))
               {
               $query_string .= mysql_real_escape_string((string)$rec_in["acctexpdate"], $GLOBAL_dbhandle);
               }
            else
               {
               //Empty string.
               }
            $query_string .= "\", mostrecentlogin=\"";
            //
            //-----------------------------------------------------------------------------------------
            //mostrecentlogin
            //-----------------------------------------------------------------------------------------
            if (isset($rec_in["mostrecentlogin"]))
               {
               $query_string .= mysql_real_escape_string((string)$rec_in["mostrecentlogin"], $GLOBAL_dbhandle);
               }
            else
               {
               //Empty string.
               }
            $query_string .= "\", schedalonerscs=\"";
            //
            //-----------------------------------------------------------------------------------------
            //schedalonerscs
            //-----------------------------------------------------------------------------------------
            if (isset($rec_in["schedalonerscs"]))
               {
               $query_string .= mysql_real_escape_string((string)$rec_in["schedalonerscs"], $GLOBAL_dbhandle);
               }
            else
               {
               //Empty string.
               }
            $query_string .= "\", fboremarks=\"";
            //
            //-----------------------------------------------------------------------------------------
            //fboremarks
            //-----------------------------------------------------------------------------------------
            if (isset($rec_in["fboremarks"]))
               {
               $query_string .= mysql_real_escape_string((string)$rec_in["fboremarks"], $GLOBAL_dbhandle);
               }
            else
               {
               //Empty string.
               }
            $query_string .= "\", userremarks=\"";
            //
            //-----------------------------------------------------------------------------------------
            //userremarks
            //-----------------------------------------------------------------------------------------
            if (isset($rec_in["userremarks"]))
               {
               $query_string .= mysql_real_escape_string((string)$rec_in["userremarks"], $GLOBAL_dbhandle);
               }
            else
               {
               //Empty string.
               }
            $query_string .= "\"";
            //
            //echo $query_string;

            //Execute the query to insert the record.
            $result = mysql_query($query_string, $GLOBAL_dbhandle);
            //
            //If the insert failed, our caller gets FALSE.
            if ($result == FALSE)
               {
               $result_code_out = -1;
               }
            else
               {
               //The insert was successful.  Figure out the index that was assigned.
               $result = mysql_query("SELECT LAST_INSERT_ID()");

               //If we have a failure, the caller gets FALSE, otherwise the caller gets the
               //index.
               if ($result === FALSE)
                  {
                  $result_code_out = -1;
                  }
               else
                  {
                  //Pick apart the result.
                  $row = mysql_fetch_array($result, MYSQL_NUM);

                  //Extract the integer.
                  $result_code_out = $row[0];

                  //Free the result memory.
                  mysql_free_result($result);
                  }
               }
            }
         else
            {
            //Modify
            //
            }
         }

      //Unlock the database (if it was locked) using the recursive critical section
      //method.
      if (! $db_was_locked)
         {
         DB_db_unlock();
         $GLOBAL_dblocked = FALSE;
         }
      } //if not in termination sequence.

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
//E-mails a user by index (meaning sends the e-mail to each of the contact addresses).
//
//Input parameters:
//   a)Idx:       index of user in the database.
//   b)Subject:   the subject of the e-mail.
//   c)Message:   an array of lines containing the body.
//
//Output parameters:
//   a)The number of e-mails actually injected (depends on what is in the database).
//
//A notice about automatically-generated e-mail is automatically appended to the e-mail.
//
function USRS_em_notify($idx_in, $subj_in, $msg_in)
   {
   global $GLOBAL_stime_year;
   global $GLOBAL_stime_month;
   global $GLOBAL_stime_day;
   global $GLOBAL_stime_hour;
   global $GLOBAL_stime_minute;
   global $GLOBAL_stime_dow;

   $rv = 0;

   //Form a footer string that explains the origin of the e-mail.
   $footer_text =  CONFIG_fbo_automail_footer_text();
      //Standard footer.

   $footer_split = wordwrap($footer_text, CONFIG_FBO_AUTOMAIL_LINELENGTH, "\n");
   $footer_array = explode("\n", $footer_split);

   //Trim any empty lines from the end of the array.  In the actual e-mail, at least
   //as viewed using Outlook, there seem to be two empty lines at the end.  
   //This hasn't cured it.  Trivial issue, but may eventually want to figure
   //it out.
   //
   $n = count($footer_array);
   if (($n-1) >= 0)
      {
      if (strlen($footer_array[$n-1]) == 0)
         unset($footer_array[$n-1]);
      }
   if (($n-2) >= 0)
      {
      if (strlen($footer_array[$n-2]) == 0)
         unset($footer_array[$n-2]);
      }

   $userinfo = USRS_retrieve_by_idx($idx_in);

   if ($userinfo !== FALSE)
      {
      //Form up the message txt block.
      //
      $msgtext = "";
      for ($i=0; $i<count($msg_in); $i++)
         {
         $msgtext .= $msg_in[$i];
         $msgtext .= "\n";
         }

      for ($i=0; $i<count($footer_array); $i++)
         {
         $msgtext .= $footer_array[$i];
         if ($i < (count($footer_array) - 1))
            $msgtext .= "\n";
         }

      //Form and send the mail to em1.
      if (strlen($userinfo["em1"]))
         {
         mail(
             $userinfo["em1"], 
             $subj_in, 
             $msgtext,
             "From: " . CONFIG_FBO_AUTOMAIL_FROM . "\r\n" . "Reply-To: " . CONFIG_FBO_AUTOMAIL_FROM
             );

         $rv++;
         }

      //Form and send the mail to em2.
      if (strlen($userinfo["em2"]))
         {
         mail(
             $userinfo["em2"], 
             $subj_in, 
             $msgtext,
             "From: " . CONFIG_FBO_AUTOMAIL_FROM . "\r\n" . "Reply-To: " . CONFIG_FBO_AUTOMAIL_FROM
             );

         $rv++;
         }
      }

   return($rv);
   }
//
//--------------------------------------------------------------------------------------------------------------
//Retrieves an array containing the indices of all flight instructors in the resources
//table that are online, or FALSE if none exist.
//
function USRS_get_user_online_idxs()
   {
   global $GLOBAL_dbhandle;

   //Form the query string.
   $query_string = "SELECT idx FROM usrs WHERE status=\""
                   .
                   mysql_real_escape_string((string)USRS_STATUS_ACTIVE, $GLOBAL_dbhandle)
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

//--------------------------------------------------------------------------------------------------------------
//End of $RCSfile: usrsx.inc,v $.
//--------------------------------------------------------------------------------------------------------------
?>
