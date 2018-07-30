#!/usr/bin/php -q
<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/dbconncheck.php 205 2018-07-15 19:00:51Z dashley $
//--------------------------------------------------------------------------------
//dbconncheck.php--Checks Database Connectivity To The FBO-Prime Database
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
//Returns a version control string.  Used for randomness.
//
function vc_info()
   {
   return("\$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/dbconncheck.php 205 2018-07-15 19:00:51Z dashley $");
   }
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//------  M A I N    S C R I P T  ------------------------------------------------
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//
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

   $result = mysql_close($handle);
   if ($result === FALSE)
      {
      echo "ERROR:  Unable to close MySQL connection.\n";
      exit(1);
      }
   
   //If we've made it this far, things are OK.
   echo "Success (";
   echo vc_info();
   echo ")\n";
   echo "Server          :  " . CONFIG_MYSQL_SERVER    . "\n";
   echo "Username        :  " . CONFIG_MYSQL_USERNAME  . "\n";
   echo "Password        :  " . CONFIG_MYSQL_PASSWORD  . "\n";
   echo "Database        :  " . CONFIG_MYSQL_DATABASE  . "\n";
   echo "Handle returned :  " . $handle_copy           . "\n";

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
//End of $RCSfile: dbconncheck.php,v $.
//--------------------------------------------------------------------------------
?>
