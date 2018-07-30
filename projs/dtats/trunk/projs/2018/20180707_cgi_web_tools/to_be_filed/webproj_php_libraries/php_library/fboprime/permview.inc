<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/permview.inc 205 2018-07-15 19:00:51Z dashley $
//--------------------------------------------------------------------------------------------------------------
//permview.inc--FboPrime Permission String Human Interface Functions
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
//This include file contains functions that provide human display, input, and other
//processing of user permission strings.  These functions are packaged separately
//to try to minimize the include burden for the main scheduling page.
//
//The semantics and meanings of all the permission flags are also documented in
//this file.  For the precise format of permission strings, please see perm.inc
//(which must parse and split them).
//--------------------------------------------------------------------------------------------------------------
require_once("global.inc");
require_once("perm.inc");
//
//--------------------------------------------------------------------------------------------------------------
//Individual permission string attributes.  For the attributes marked P/A (presence/absence), the value of
//of the permission string attribute isn't used--only its existence.
//
//   canviewlogentries           :   P/A    :  Can use the log view page and view all log entries.
//   canviewdbstats              :   P/A    :  Can view database statistics.
//   canincsesslifetime          :   P/A    :  The user is able to increase the time until they are
//                                             automatically logged out (useful for line personnel).
//   canresetpasswords           :   P/A    :  Can reset passwords of any user whose security level is greater
//                                             (numerically) than the user's.
//   canviewreservationdetails   :   P/A    :  Can view the identity and information for all reservations.
//                                             (Normal users can't do this because it is a privacy violation.)
//   sesslifetimedefault         :   int    :  An integer specifying the session lifetime (in seconds) to be
//                                             used for this user.
//   sesslifetimeprivesc         :   int    :  An integer specifying the session lifetime (in seconds) to be
//                                             used when priveleges have been escalated by the user.
//   sesslifetimelong            :   int    :  The session lifetime to use when the user has increased the
//                                             lifetime.
//--------------------------------------------------------------------------------------------------------------
//End of $RCSfile: permview.inc,v $.
//--------------------------------------------------------------------------------------------------------------
?>
