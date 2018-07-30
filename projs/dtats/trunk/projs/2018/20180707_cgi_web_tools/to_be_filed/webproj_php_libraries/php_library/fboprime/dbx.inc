<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/dbx.inc 205 2018-07-15 19:00:51Z dashley $
//--------------------------------------------------------------------------------------------------------------
//dbx.inc--FboPrime Database Functions Not Required in the Day View Scheduler
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
//This contains constants and functions used to operate on the MySQL database
//as a whole.
//--------------------------------------------------------------------------------------------------------------
require_once("db.inc");
require_once("usrs.inc");
//
//--------------------------------------------------------------------------------------------------------------
//Gathers the group of database statistics necessary for the statistics page.  The database is
//locked for the operation to ensure consistency of the results returned.
//
//An associative array is returned with the following elements (all integers).
//    loge                       : Number of elements in loge table.
//    logemaxidx                 : Maximum index from the loge table.
//    resv                       : Number of elements in resv table.
//    rscs                       : Number of elements in resources table.
//    sess                       : Number of elements in sess table.
//    usrs                       : Number of elements in usrs table.
//    usrsactive                 : Active users.
//    usrsinactive               : Inactive users.
//    usrsmale                   : Male users, both active and inactive.
//    usrsfemale                 : Female users, both active and inactive.
//    usrssexunspecifed          : Users with gender unspecified.
//    usrsmaleactive             : Male users, active.
//    usrsmaleinactive           : Male users, inactive.
//    usrsfemaleactive           : Female users, active.
//    usrsfemaleinactive         : Female users, inactive.
//    usrssexunspecifiedactive   : Users with gender unspecified, active.
//    usrssexunspecifiedinactive : Users with gender unspecified, inactive.
//
function DB_stats_statspage_01()
   {
   global $GLOBAL_dblocked;
   global $GLOBAL_dbhandle;

   //Lock the database to ensure consistent snapshot statistics.
   $db_was_locked = $GLOBAL_dblocked;
   if (! $GLOBAL_dblocked)
      {
      DB_db_lock();
      $GLOBAL_dblocked = TRUE;
      }

   //-----------------------------------------------
   //loge
   //
   $query_string = "SELECT COUNT(*) FROM loge";

   $result = mysql_query($query_string, $GLOBAL_dbhandle);

   if ($result === FALSE)
      {
      //Unknown query failure.  Return 0.
      $rv["loge"] = 0;
      }
   else
      {
      if (mysql_num_rows($result) > 0)
         {
         $row = mysql_fetch_array($result, MYSQL_NUM);
         $rv["loge"] = $row[0];
         }
      else
         {
         //Unexplained why this query would return no rows.
         $rv["loge"] = 0;
         }

      mysql_free_result($result);
      }

   //-----------------------------------------------
   //logemaxidx
   //
   $query_string = "SELECT MAX(idx) FROM loge";

   $result = mysql_query($query_string, $GLOBAL_dbhandle);

   if ($result === FALSE)
      {
      //Unknown query failure.  Return 0.
      $rv["logemaxidx"] = 0;
      }
   else
      {
      if (mysql_num_rows($result) > 0)
         {
         $row = mysql_fetch_array($result, MYSQL_NUM);
         $rv["logemaxidx"] = $row[0];
         }
      else
         {
         //Unexplained why this query would return no rows.
         $rv["logemaxidx"] = 0;
         }

      mysql_free_result($result);
      }

   //-----------------------------------------------
   //resv
   //
   $query_string = "SELECT COUNT(*) FROM resv";

   $result = mysql_query($query_string, $GLOBAL_dbhandle);

   if ($result === FALSE)
      {
      //Unknown query failure.  Return 0.
      $rv["resv"] = 0;
      }
   else
      {
      if (mysql_num_rows($result) > 0)
         {
         $row = mysql_fetch_array($result, MYSQL_NUM);
         $rv["resv"] = $row[0];
         }
      else
         {
         //Unexplained why this query would return no rows.
         $rv["resv"] = 0;
         }

      mysql_free_result($result);
      }

   //-----------------------------------------------
   //rscs
   //
   $query_string = "SELECT COUNT(*) FROM rscs";

   $result = mysql_query($query_string, $GLOBAL_dbhandle);

   if ($result === FALSE)
      {
      //Unknown query failure.  Return 0.
      $rv["rscs"] = 0;
      }
   else
      {
      if (mysql_num_rows($result) > 0)
         {
         $row = mysql_fetch_array($result, MYSQL_NUM);
         $rv["rscs"] = $row[0];
         }
      else
         {
         //Unexplained why this query would return no rows.
         $rv["rscs"] = 0;
         }

      mysql_free_result($result);
      }

   //-----------------------------------------------
   //sess
   //
   $query_string = "SELECT COUNT(*) FROM sess";

   $result = mysql_query($query_string, $GLOBAL_dbhandle);

   if ($result === FALSE)
      {
      //Unknown query failure.  Return 0.
      $rv["sess"] = 0;
      }
   else
      {
      if (mysql_num_rows($result) > 0)
         {
         $row = mysql_fetch_array($result, MYSQL_NUM);
         $rv["sess"] = $row[0];
         }
      else
         {
         //Unexplained why this query would return no rows.
         $rv["sess"] = 0;
         }

      mysql_free_result($result);
      }

   //-----------------------------------------------
   //usrs
   //
   $query_string = "SELECT COUNT(*) FROM usrs";

   $result = mysql_query($query_string, $GLOBAL_dbhandle);

   if ($result === FALSE)
      {
      //Unknown query failure.  Return 0.
      $rv["usrs"] = 0;
      }
   else
      {
      if (mysql_num_rows($result) > 0)
         {
         $row = mysql_fetch_array($result, MYSQL_NUM);
         $rv["usrs"] = $row[0];
         }
      else
         {
         //Unexplained why this query would return no rows.
         $rv["usrs"] = 0;
         }

      mysql_free_result($result);
      }

   //-----------------------------------------------
   //usrsactive
   //
   $query_string = "SELECT COUNT(*) FROM usrs WHERE status=\"" . (string)USRS_STATUS_ACTIVE  . "\"";

   $result = mysql_query($query_string, $GLOBAL_dbhandle);

   if ($result === FALSE)
      {
      //Unknown query failure.  Return 0.
      $rv["usrsactive"] = 0;
      }
   else
      {
      if (mysql_num_rows($result) > 0)
         {
         $row = mysql_fetch_array($result, MYSQL_NUM);
         $rv["usrsactive"] = $row[0];
         }
      else
         {
         //Unexplained why this query would return no rows.
         $rv["usrsactive"] = 0;
         }

      mysql_free_result($result);
      }

   //-----------------------------------------------
   //usrsinactive
   //
   $query_string = "SELECT COUNT(*) FROM usrs WHERE status=\"" . (string)USRS_STATUS_INACTIVE  . "\"";

   $result = mysql_query($query_string, $GLOBAL_dbhandle);

   if ($result === FALSE)
      {
      //Unknown query failure.  Return 0.
      $rv["usrsinactive"] = 0;
      }
   else
      {
      if (mysql_num_rows($result) > 0)
         {
         $row = mysql_fetch_array($result, MYSQL_NUM);
         $rv["usrsinactive"] = $row[0];
         }
      else
         {
         //Unexplained why this query would return no rows.
         $rv["usrsinactive"] = 0;
         }

      mysql_free_result($result);
      }

   //-----------------------------------------------
   //usrsmale
   //
   $query_string = "SELECT COUNT(*) FROM usrs WHERE sex=\"" . (string)USRS_SEX_MALE  . "\"";

   $result = mysql_query($query_string, $GLOBAL_dbhandle);

   if ($result === FALSE)
      {
      //Unknown query failure.  Return 0.
      $rv["usrsmale"] = 0;
      }
   else
      {
      if (mysql_num_rows($result) > 0)
         {
         $row = mysql_fetch_array($result, MYSQL_NUM);
         $rv["usrsmale"] = $row[0];
         }
      else
         {
         //Unexplained why this query would return no rows.
         $rv["usrsmale"] = 0;
         }

      mysql_free_result($result);
      }

   //-----------------------------------------------
   //usrsfemale
   //
   $query_string = "SELECT COUNT(*) FROM usrs WHERE sex=\"" . (string)USRS_SEX_FEMALE  . "\"";

   $result = mysql_query($query_string, $GLOBAL_dbhandle);

   if ($result === FALSE)
      {
      //Unknown query failure.  Return 0.
      $rv["usrsfemale"] = 0;
      }
   else
      {
      if (mysql_num_rows($result) > 0)
         {
         $row = mysql_fetch_array($result, MYSQL_NUM);
         $rv["usrsfemale"] = $row[0];
         }
      else
         {
         //Unexplained why this query would return no rows.
         $rv["usrsfemale"] = 0;
         }

      mysql_free_result($result);
      }

   //-----------------------------------------------
   //usrssexunspecified
   //
   $query_string = "SELECT COUNT(*) FROM usrs WHERE sex=\"" . (string)USRS_SEX_UNSPECIFIED  . "\"";

   $result = mysql_query($query_string, $GLOBAL_dbhandle);

   if ($result === FALSE)
      {
      //Unknown query failure.  Return 0.
      $rv["usrssecunspecified"] = 0;
      }
   else
      {
      if (mysql_num_rows($result) > 0)
         {
         $row = mysql_fetch_array($result, MYSQL_NUM);
         $rv["usrssexunspecified"] = $row[0];
         }
      else
         {
         //Unexplained why this query would return no rows.
         $rv["usrssexunspecified"] = 0;
         }

      mysql_free_result($result);
      }

   //-----------------------------------------------
   //usrsmaleactive
   //
   $query_string = "SELECT COUNT(*) FROM usrs WHERE sex=\"" . (string)USRS_SEX_MALE  
                   . "\" AND status=\"" . (string)USRS_STATUS_ACTIVE . "\"";

   $result = mysql_query($query_string, $GLOBAL_dbhandle);

   if ($result === FALSE)
      {
      //Unknown query failure.  Return 0.
      $rv["usrsmaleactive"] = 0;
      }
   else
      {
      if (mysql_num_rows($result) > 0)
         {
         $row = mysql_fetch_array($result, MYSQL_NUM);
         $rv["usrsmaleactive"] = $row[0];
         }
      else
         {
         //Unexplained why this query would return no rows.
         $rv["usrsmaleactive"] = 0;
         }

      mysql_free_result($result);
      }

   //-----------------------------------------------
   //usrsfemaleactive
   //
   $query_string = "SELECT COUNT(*) FROM usrs WHERE sex=\"" . (string)USRS_SEX_FEMALE  
                   . "\" AND status=\"" . (string)USRS_STATUS_ACTIVE . "\"";

   $result = mysql_query($query_string, $GLOBAL_dbhandle);

   if ($result === FALSE)
      {
      //Unknown query failure.  Return 0.
      $rv["usrsfemaleactive"] = 0;
      }
   else
      {
      if (mysql_num_rows($result) > 0)
         {
         $row = mysql_fetch_array($result, MYSQL_NUM);
         $rv["usrsfemaleactive"] = $row[0];
         }
      else
         {
         //Unexplained why this query would return no rows.
         $rv["usrsfemaleactive"] = 0;
         }

      mysql_free_result($result);
      }

   //-----------------------------------------------
   //usrssexunspecifiedactive
   //
   $query_string = "SELECT COUNT(*) FROM usrs WHERE sex=\"" . (string)USRS_SEX_UNSPECIFIED  
                   . "\" AND status=\"" . (string)USRS_STATUS_ACTIVE . "\"";

   $result = mysql_query($query_string, $GLOBAL_dbhandle);

   if ($result === FALSE)
      {
      //Unknown query failure.  Return 0.
      $rv["usrssexunspecifiedactive"] = 0;
      }
   else
      {
      if (mysql_num_rows($result) > 0)
         {
         $row = mysql_fetch_array($result, MYSQL_NUM);
         $rv["usrssexunspecifiedactive"] = $row[0];
         }
      else
         {
         //Unexplained why this query would return no rows.
         $rv["usrssexunspecifiedactive"] = 0;
         }

      mysql_free_result($result);
      }

   //-----------------------------------------------
   //usrsmaleinactive
   //
   $query_string = "SELECT COUNT(*) FROM usrs WHERE sex=\"" . (string)USRS_SEX_MALE  
                   . "\" AND status=\"" . (string)USRS_STATUS_INACTIVE . "\"";

   $result = mysql_query($query_string, $GLOBAL_dbhandle);

   if ($result === FALSE)
      {
      //Unknown query failure.  Return 0.
      $rv["usrsmaleinactive"] = 0;
      }
   else
      {
      if (mysql_num_rows($result) > 0)
         {
         $row = mysql_fetch_array($result, MYSQL_NUM);
         $rv["usrsmaleinactive"] = $row[0];
         }
      else
         {
         //Unexplained why this query would return no rows.
         $rv["usrsmaleinactive"] = 0;
         }

      mysql_free_result($result);
      }

   //-----------------------------------------------
   //usrsfemaleinactive
   //
   $query_string = "SELECT COUNT(*) FROM usrs WHERE sex=\"" . (string)USRS_SEX_FEMALE  
                   . "\" AND status=\"" . (string)USRS_STATUS_INACTIVE . "\"";

   $result = mysql_query($query_string, $GLOBAL_dbhandle);

   if ($result === FALSE)
      {
      //Unknown query failure.  Return 0.
      $rv["usrsfemaleinactive"] = 0;
      }
   else
      {
      if (mysql_num_rows($result) > 0)
         {
         $row = mysql_fetch_array($result, MYSQL_NUM);
         $rv["usrsfemaleinactive"] = $row[0];
         }
      else
         {
         //Unexplained why this query would return no rows.
         $rv["usrsfemaleinactive"] = 0;
         }

      mysql_free_result($result);
      }

   //-----------------------------------------------
   //usrssexunspecifiedinactive
   //
   $query_string = "SELECT COUNT(*) FROM usrs WHERE sex=\"" . (string)USRS_SEX_UNSPECIFIED  
                   . "\" AND status=\"" . (string)USRS_STATUS_INACTIVE . "\"";

   $result = mysql_query($query_string, $GLOBAL_dbhandle);

   if ($result === FALSE)
      {
      //Unknown query failure.  Return 0.
      $rv["usrssexunspecifiedinactive"] = 0;
      }
   else
      {
      if (mysql_num_rows($result) > 0)
         {
         $row = mysql_fetch_array($result, MYSQL_NUM);
         $rv["usrssexunspecifiedinactive"] = $row[0];
         }
      else
         {
         //Unexplained why this query would return no rows.
         $rv["usrssexunspecifiedinactive"] = 0;
         }

      mysql_free_result($result);
      }

   //-----------------------------------------------
   //Unlock the database.
   //
   if (! $db_was_locked)
      {
      DB_db_unlock();
      $GLOBAL_dblocked = FALSE;
      }

   //Return the return value.
   return($rv);
   }
//--------------------------------------------------------------------------------------------------------------
//Parses an input argument to be sure it is a suitable short index for a table.  "zna" = Zero is not allowed.
//  This means it must be either:
//  a)A positive integer.
//  b)A string representing a positive integer <= (2^32 - 1).
//
//Returns TRUE if valid or FALSE if not.
//
function DB_table_index_short_validity_check_zna($idx_in)
   {
   if (is_int($idx_in))
      {
      if ($idx_in > 0)
         {
         return(TRUE);
         }
      else
         {
         return(FALSE);
         }
      }
   else if (is_string($idx_in))
      {
      $temp = intval($idx_in);

      if ($temp === FALSE)
         {
         return(FALSE);
         }
      else if ($temp > 0)
         {
         return(TRUE);
         }
      else
         {
         return(FALSE);
         }
      }
   else
      {
      //Unknown type.
      return(FALSE);
      }
   }
//--------------------------------------------------------------------------------------------------------------
//End of $RCSfile: dbx.inc,v $.
//--------------------------------------------------------------------------------------------------------------
?>
