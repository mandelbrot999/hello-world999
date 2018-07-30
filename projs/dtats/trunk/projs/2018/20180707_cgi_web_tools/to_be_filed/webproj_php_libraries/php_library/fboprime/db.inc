<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/db.inc 205 2018-07-15 19:00:51Z dashley $
//--------------------------------------------------------------------------------------------------------------
//db.inc--FboPrime Database Functions
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
require_once("confighard.inc");
require_once("global.inc");
//--------------------------------------------------------------------------------------------------------------
//Locks all MySQL database tables in write mode (effectively locking the database).  This is the only
//form of locking supported by FBO-Prime--all or nothing.
//
//Unit-tested 20060422.
//
function DB_db_lock()
   {
   global $GLOBAL_dbhandle;
   global $CONFIGHARD_DBTABLES_ARRAY;

   $c = count($CONFIGHARD_DBTABLES_ARRAY);
   $query_string = "LOCK TABLES";
   for ($i=0; $i<$c; $i++)
      {
      $query_string .= (" " . $CONFIGHARD_DBTABLES_ARRAY[$i] . " WRITE");
      if ($i < ($c-1))
         $query_string .= ",";
      }

   //echo " " . $query_string . " ";

   mysql_query($query_string, $GLOBAL_dbhandle);
   }
//
//--------------------------------------------------------------------------------------------------------------
//Unocks all MySQL database tables.
//
//Unit-tested 20060422.
//
function DB_db_unlock()
   {
   global $GLOBAL_dbhandle;

   //In the case of the UNLOCK command, things are simpler.  If the list of tables is omitted,
   //everything is unlocked.
   mysql_query("UNLOCK TABLES", $GLOBAL_dbhandle);
   }
//
//--------------------------------------------------------------------------------------------------------------
//Performs the necessary shutdown actions in the event that the PHP script shuts down abnormally.  At
//present, this consists only of unlocking the database tables.  The FBO-Prime manual contains
//more information about locking, persistent connections, etc.
//
function DB_db_shutdown_func()
   {
   global $GLOBAL_dbhandle;

   //If the global variable is FALSE, this is a signal that either the database connection
   //could not be opened, or else that the connection has already been closed.
   //
   if ($GLOBAL_dbhandle !== FALSE)
      {
      //In the case of the UNLOCK command, things are simpler.  If the list of tables is omitted,
      //everything is unlocked.
      mysql_query("UNLOCK TABLES", $GLOBAL_dbhandle);
      }
   }
//
//--------------------------------------------------------------------------------------------------------------
//End of $RCSfile: db.inc,v $.
//--------------------------------------------------------------------------------------------------------------
?>
