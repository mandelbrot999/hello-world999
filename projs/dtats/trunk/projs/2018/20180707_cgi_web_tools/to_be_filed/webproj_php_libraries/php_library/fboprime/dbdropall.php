#!/usr/bin/php -q
<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/dbdropall.php 205 2018-07-15 19:00:51Z dashley $
//--------------------------------------------------------------------------------
//dbdropall.php--Drops (Deletes) All Database Tables
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
//--------------------------------------------------------------------------------
//Set the include file path.  This is necessary to get to the configuration
//information, including how to try to connect to the database.
set_include_path("/var/www/php_library/fboprime");
//
//Include the configuration information.
require_once("config.inc");
//
//--------------------------------------------------------------------------------
//Writes a horizontal line.
//
function hline()
   {
   for ($i=0; $i<80; $i++)
      {
      echo "-";
      }
   echo "\n";
   }
//
//--------------------------------------------------------------------------------
//Errors out.
//
function error_out()
   {
   echo "FATAL ERROR\n";
   exit(1);
   }
//--------------------------------------------------------------------------------
//Returns a version control string.  Used for randomness.
//
function vc_info()
   {
   return("\$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/dbdropall.php 205 2018-07-15 19:00:51Z dashley $");
   }
//
//--------------------------------------------------------------------------------
//
function drop_all($handle, $droplist)
   {
   //Figure out how many tables are in the database, and get their names.
   hline();

   $result = mysql_query("show tables", $handle);

   if ($result === FALSE)
      error_out();

   //Figure out the results.
   $ntables = mysql_num_rows($result);
   for ($i=0; $i<$ntables; $i++)
      {
      $temp             = mysql_fetch_row($result);
      $tables_array[$i] = $temp[0];
      }

   //Tell how many tables.
   if ($ntables > 1)
      echo $ntables . " tables found in database:\n";
   else if ($ntables == 1)
      echo $ntables . " table found in database:\n";
   else
      echo "No tables found in database.\n";

   //Emit the table names.
   for ($i = 0; $i < $ntables; $i++)
      {
      echo "   " . $tables_array[$i] . "\n";
      }

   //For each table in the design, if it is in the actual database, issue
   //the drop statement.
   if ($ntables)
      {
      for ($i=0; $i<count($droplist); $i++)
         {
         $found = array_search($droplist[$i], $tables_array);
         if (($found !== FALSE) && ($found !== NULL))
            {
	    echo "Dropping table " . $droplist[$i] . " ... ";

	    //The table exists.  Drop it.
            //Run the query and bug out if it fails.
            $result = mysql_query("drop table " . $droplist[$i], $handle);

            if ($result === FALSE)
               error_out();

            echo "OK.\n";
	    }
         } 
      }
   }
//
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//------  M A I N    S C R I P T  ------------------------------------------------
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//
//
//This is the list of the database tables.  For each one, this script will try to
//trash it if it exists.
//
$tables_to_drop = array
   (
   "usrs",
   "usrsresv",
   "resv",
   "slot",
   "rscs",
   "sess",
   "loge",
   "dpar"
   );

if ($argc == 1)
   {
   //The no-parameters case, as expected.

   $handle = mysql_connect(CONFIG_MYSQL_SERVER, CONFIG_MYSQL_USERNAME, CONFIG_MYSQL_PASSWORD);
   $handle_copy = $handle;
   if ($handle === FALSE)
      {
      echo "ERROR:  Unable to connect and/or authenticate to MySQL database.\n";
      exit(1);
      }

   $result = mysql_select_db(CONFIG_MYSQL_DATABASE, $handle);
   if ($result === FALSE)
      {
      echo "ERROR:  Unable to select MySQL database \"" . CONFIG_MYSQL_DATABASE . "\".\n";
      exit(1);
      }

   //Do the dropping.
   drop_all($handle, $tables_to_drop);
   hline();

   //Try to close the database.
   $result = mysql_close($handle);
   if ($result === FALSE)
      {
      echo "ERROR:  Unable to close MySQL connection.\n";
      exit(1);
      }
   
   exit(0);
   }
else
   {
   echo "ERROR:  This command accepts no command-line parameters.\n";
   exit(1);
   }

//If we're here, success.  Per the standard Unix way of thinking
//say nothing.  Silence means OK.
exit(0);
//
//--------------------------------------------------------------------------------
//End of $RCSfile: dbdropall.php,v $.
//--------------------------------------------------------------------------------
?>
