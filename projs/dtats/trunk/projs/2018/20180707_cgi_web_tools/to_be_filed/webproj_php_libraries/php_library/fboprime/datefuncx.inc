<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/datefuncx.inc 205 2018-07-15 19:00:51Z dashley $
//********************************************************************************
//Copyright (C)2006 David T. Ashley
//********************************************************************************
//This program or source file is free software; you can redistribute it and/or 
//modify it under the terms of the GNU General Public License as published by
//the Free Software Foundation; either version 2 of the License, or (at your 
//option) any later version.
//
//This program or source file is distributed in the hope that it will 
//be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You may have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//********************************************************************************
//Dave Ashley, 04/06
//
//This source file contains date and time calculation and
//manipulation functions.
//
require_once("datefunc.inc");          //Basic date functions.
//
//================================================================================
//================================================================================
//====  R A W    C A L C U L A T I O N  ==========================================
//================================================================================
//================================================================================
//
//================================================================================
//================================================================================
//====  S T R I N G    M A P P I N G  ============================================
//================================================================================
//================================================================================
//
//Returns the string associated with an ordinal month number 1-12.
//
function DATEFUNC_string_month_short($month_no)
   {
   return(SubStr(DATEFUNC_string_month_long($month_no), 0, 3));
   }
//
//--------------------------------------------------------------------------------
//End of $RCSfile: datefuncx.inc,v $.
//--------------------------------------------------------------------------------
?>
