<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/pamc_gen_a/ref_tables/db_design_tablelistonly.inc 205 2018-07-15 19:00:51Z dashley $
//--------------------------------------------------------------------------------
//db_design_tablelistonly.inc -- List of tables in the PAMC MySQL database (only).
//                               This list is used on a "LOCK TABLES" statement
//                               to lock every table in the database for atomic
//                               operations.  The more detailed database 
//                               design information isn't included unless
//                               necessary, because it is complex and may slow
//                               down the PHP interpreter stream.
//--------------------------------------------------------------------------------
//Copyright (C) 2007  David T. Ashley
//--------------------------------------------------------------------------------
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
//Author contact information:
//   David T. Ashley
//   P.O. Box 918
//   Marshall, Michigan, 49068
//   dta@e3ft.com
//--------------------------------------------------------------------------------
$config_hard['dbdesign']['tablelist'] = "tokens users";
   //For simplicity, list should be in alphabetical order.  If necessary (but
   //probably never necessary), a software component that needs this information
   //in another form can explode() it at the spaces to get an array.
//--------------------------------------------------------------------------------
//End of $RCSfile: db_design_tablelistonly.inc,v $.
//--------------------------------------------------------------------------------
?>
