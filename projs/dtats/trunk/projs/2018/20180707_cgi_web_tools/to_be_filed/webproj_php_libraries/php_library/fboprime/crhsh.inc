<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/crhsh.inc 205 2018-07-15 19:00:51Z dashley $
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
//This source file contains cryptographic hash function(s).
//
//The site hash key must be included, as this is used for all hashing functions.
//
require_once("sitehashkey.inc");
//
//As it turns out, because PHP provides for functions with variable numbers of arguments,
//only one function is required to meet all cryptographic hashing functions.
//
//--------------------------------------------------------------------------------
//The return value is an MD5 hash of the arguments intermingled with the key.
//
//The function is always deterministic (the same inputs will always produce the same 
//output).
//
//Unit-tested 20060408.
//
function CRHSH_hashva()
   {
   $input = SITEHASHKEY_SITEHASHKEY;

   $num_args = func_num_args();

   for ($i=0; $i<$num_args; $i++)
      {
      $input .= ((string) func_get_arg($i));
      $input .= SITEHASHKEY_SITEHASHKEY;
      }

   $rv = md5($input);

   return($rv);
   }
//--------------------------------------------------------------------------------
?>
