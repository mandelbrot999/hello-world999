<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/logview.inc 205 2018-07-15 19:00:51Z dashley $
//--------------------------------------------------------------------------------------------------------------
//logview.inc--FboPrime Log Viewing Support Functions
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
//This contains functions used in development and debugging of FBO-Prime.  The
//contents of this file are kept separate to avoid introducing baggage into
//the production software.
//--------------------------------------------------------------------------------------------------------------
require_once("global.inc");
require_once("log.inc");
//
//--------------------------------------------------------------------------------------------------------------
function LOGVIEW_type_to_text($type_in)
   {
   if ($type_in == LOG_ET_UNKNOWN_MISC)
      return("UNKNOWN_MISC");
   else if ($type_in == LOG_ET_PAGEHIT)
      return("PAGEHIT");
   else if ($type_in == LOG_ET_ERRDBCONN)
      return("ERRDBCONN");
   else if ($type_in == LOG_ET_LOGIN_OK)
      return("LOGIN_OK");
   else if ($type_in == LOG_ET_LOGIN_FAIL)
      return("LOGIN_FAIL");
   else if ($type_in == LOG_ET_LOGOUT_VOL)
      return("LOGOUT_VOL");
   else if ($type_in == LOG_ET_LOGOUT_TIME)
      return("LOGOUT_TIME");
   else if ($type_in == LOG_ET_REVAL_OK)
      return("REVAL_OK");
   else if ($type_in == LOG_ET_SEC_SID_FORGED)
      return("SEC_SID_FORGED");
   else if ($type_in == LOG_ET_SEC_LOGOUT_IP)
      return("SEC_LOGOUT_IP");
   else if ($type_in == LOG_ET_MAINT_PERIODIC)
      return("MAINT_PERIODIC");
   else if ($type_in == LOG_ET_UNCATEGORIZED)
      return("UNCATEGORIZED");
   else
      return("INVALID_SPECIFIED");
   }
//
//--------------------------------------------------------------------------------------------------------------
//End of $RCSfile: logview.inc,v $.
//--------------------------------------------------------------------------------------------------------------
?>
