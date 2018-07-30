<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/confighard.inc 205 2018-07-15 19:00:51Z dashley $
//********************************************************************************
//confighard.php--FboPrime FBO "Hard" Configuration
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
//This file contains constants that must not be customized, i.e. constants
//where either:
//   a)There is no reason for an FBO to want to customize these, or
//   b)A change in these constants must be accompanied by a code change.
//
//--------------------------------------------------------------------------------------------------------------
//Database-related constants and variables.
//
//The list of tables in the database.  It is imperative that this list be kept current so that there
//are no race conditions (this list is used to lock tables).
//
$CONFIGHARD_DBTABLES_ARRAY = array("loge",
                                   "resv",
                                   "rscs",
                                   "sess",
                                   "usrs");
//
//--------------------------------------------------------------------------------------------------------------
//Date calculation minimums and maximums.
//
define("CONFIGHARD_DATEFUNC_MINYEAR",     1700);     //The first year for which the scheduler will operate or for
                                                     //which date calculations may be performed.
define("CONFIGHARD_DATEFUNC_MAXYEAR",     2300);     //One past the last year for which the scheduler will operate
                                                     //or for which date calculations will be performed.  This is
                                                     //tested in a "<" sense (hence the "one past").
define("CONFIGHARD_DATEFUNC_EPOCH_DOW",      5);     //January 1, 1700 was a Friday.  This is used for subsequent
                                                     //modulo arithmetic.
//--------------------------------------------------------------------------------------------------------------
//Home page of the FBO-Prime software (the open-source project).  This may change over time ...
define("CONFIGHARD_FBOPRIME_HOME_PAGE_URL",  "http://fboprime.e3ft.com");
//
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//End of $RCSfile: confighard.inc,v $.
//--------------------------------------------------------------------------------
?>
