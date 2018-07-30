<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/sessx.inc 205 2018-07-15 19:00:51Z dashley $
//--------------------------------------------------------------------------------------------------------------
//sessx.inc--FboPrime Session and Authentication Management Functions and Constants Not Needed by Day View
//           Scheduler
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
//Implement session and authentication functions.
//--------------------------------------------------------------------------------------------------------------
require_once("sess.inc");
//
//--------------------------------------------------------------------------------------------------------------
//Stores the current resource field of the session.  The current resource field is remembered
//as part of the session state in case the resource is ever ambiguous and we need a default.
//
function SESS_curresource_set($sid_in, $curresource_in)
   {
   global $GLOBAL_dbhandle;

   //Form a query to reflect assigning the new current resource to the session record.
   //
   $query_string = "UPDATE sess SET curresource=\"" . (string)$curresource_in . "\" WHERE sid=\"" . $sid_in . "\"";

   //Run the query.  We don't much care whether it fails or succeeds (nothing to be done, anyway).
   mysql_query($query_string, $GLOBAL_dbhandle);
   }
//
//--------------------------------------------------------------------------------------------------------------
//Stores the current user field of the session.  The current user field is remembered
//as part of the session state in case the user is ever ambiguous and we need a default.
//
function SESS_curuser_set($sid_in, $curuser_in)
   {
   global $GLOBAL_dbhandle;

   //Form a query to reflect assigning the new current user to the session record.
   //
   $query_string = "UPDATE sess SET curuser=\"" . (string)$curuser_in . "\" WHERE sid=\"" . $sid_in . "\"";

   //Run the query.  We don't much care whether it fails or succeeds (nothing to be done, anyway).
   mysql_query($query_string, $GLOBAL_dbhandle);
   }
//
//--------------------------------------------------------------------------------------------------------------
//Stores the userlistactive field of the session.  The userlistactive field is remembered
//as part of the session state so we know which of the two user lists to come back to.
//
function SESS_userlistactive_set($sid_in, $userlistactive_in)
   {
   global $GLOBAL_dbhandle;

   //Form a query to reflect assigning the new userlistactive field to the session record.
   //
   $query_string = "UPDATE sess SET userlistactive=\"" . (string)$userlistactive_in . "\" WHERE sid=\"" . $sid_in . "\"";

   //Run the query.  We don't much care whether it fails or succeeds (nothing to be done, anyway).
   mysql_query($query_string, $GLOBAL_dbhandle);
   }
//
//--------------------------------------------------------------------------------------------------------------
//End of $RCSfile: sessx.inc,v $.
//--------------------------------------------------------------------------------------------------------------
?>
