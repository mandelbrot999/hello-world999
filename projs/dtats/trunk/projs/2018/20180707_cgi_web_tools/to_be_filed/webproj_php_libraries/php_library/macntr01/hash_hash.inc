<?php
//------------------------------------------------------------------------
//Marshall Aviation Center FBO Management Software
//Copyright (C)2005 David T. Ashley
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
//
//The author (David T. Ashley) may be contacted by e-mail at dta@e3ft.com
//and by postal mail at P.O. Box 918, Marshall MI 49068.
//------------------------------------------------------------------------
//Functions for generating MD5 hashes (the only type of hash used
//in this set of web pages).
//
//Generally, this file defines how hashes are implemented in the entire
//web site.  These functions can't in general be changed after the site
//is in operation, because it will break functionality where hashes
//are already stored.
//------------------------------------------------------------------------
if (!$INCLUDED_HKEY_HASHKEY)
   {
   include("macntr01/hkey_hashkey.inc");
   $INCLUDED_HKEY_HASHKEY = 1;
   }
//------------------------------------------------------------------------
function hash_1($arg1)
   {
   $key = hkey_hkey();

    return(
            md5(
               $key   . 
               $arg1  . 
               $key   . 
               $arg1  . 
               $key
               )
         );
   }
//------------------------------------------------------------------------
function hash_2($arg1, $arg2)
   {
   $key = hkey_hkey();

   return(
            md5(
               $key   . 
               $arg1  . 
               $key   . 
               $arg2  . 
               $key
               )
         );
   }
//------------------------------------------------------------------------
function hash_3($arg1, $arg2, $arg3)
   {
   $key = hkey_hkey();

   return(
            md5(
               $key   . 
               $arg1  . 
               $key   . 
               $arg2  . 
               $key   .
               $arg3  . 
               $key
               )
         );
   }
//------------------------------------------------------------------------
function hash_4($arg1, $arg2, $arg3, $arg4)
   {
   $key = hkey_hkey();

   return(
            md5(
               $key   . 
               $arg1  . 
               $key   . 
               $arg2  . 
               $key   .
               $arg3  . 
               $key   .
               $arg4  . 
               $key
               )
         );
   }
//------------------------------------------------------------------------
function hash_5($arg1, $arg2, $arg3, $arg4, $arg5)
   {
   $key = hkey_hkey();

   return(
            md5(
               $key   . 
               $arg1  . 
               $key   . 
               $arg2  . 
               $key   .
               $arg3  . 
               $key   .
               $arg4  . 
               $key   .
               $arg5  . 
               $key
               )
         );
   }
//------------------------------------------------------------------------
function hash_6($arg1, $arg2, $arg3, $arg4, $arg5, $arg6)
   {
   $key = hkey_hkey();

   return(
            md5(
               $key   . 
               $arg1  . 
               $key   . 
               $arg2  . 
               $key   .
               $arg3  . 
               $key   .
               $arg4  . 
               $key   .
               $arg5  . 
               $key   .
               $arg6  . 
               $key
               )
         );
   }
//------------------------------------------------------------------------
function hash_7($arg1, $arg2, $arg3, $arg4, $arg5, $arg6, $arg7)
   {
   $key = hkey_hkey();

   return(
            md5(
               $key   . 
               $arg1  . 
               $key   . 
               $arg2  . 
               $key   .
               $arg3  . 
               $key   .
               $arg4  . 
               $key   .
               $arg5  . 
               $key   .
               $arg6  . 
               $key   .
               $arg7  . 
               $key
               )
         );
   }
//------------------------------------------------------------------------
function hash_8($arg1, $arg2, $arg3, $arg4, $arg5, $arg6, $arg7, $arg8)
   {
   $key = hkey_hkey();

   return(
            md5(
               $key   . 
               $arg1  . 
               $key   . 
               $arg2  . 
               $key   .
               $arg3  . 
               $key   .
               $arg4  . 
               $key   .
               $arg5  . 
               $key   .
               $arg6  . 
               $key   .
               $arg7  . 
               $key   .
               $arg8  . 
               $key
               )
         );
   }
//------------------------------------------------------------------------
function hash_9($arg1, $arg2, $arg3, $arg4, $arg5, $arg6, $arg7, $arg8, $arg9)
   {
   $key = hkey_hkey();

   return(
            md5(
               $key   . 
               $arg1  . 
               $key   . 
               $arg2  . 
               $key   .
               $arg3  . 
               $key   .
               $arg4  . 
               $key   .
               $arg5  . 
               $key   .
               $arg6  . 
               $key   .
               $arg7  . 
               $key   .
               $arg8  . 
               $key   .
               $arg9  . 
               $key
               )
         );
   }
//------------------------------------------------------------------------
function hash_10($arg1, $arg2, $arg3, $arg4, $arg5, $arg6, $arg7, $arg8, $arg9, $arg10)
   {
   $key = hkey_hkey();

   return(
            md5(
               $key   . 
               $arg1  . 
               $key   . 
               $arg2  . 
               $key   .
               $arg3  . 
               $key   .
               $arg4  . 
               $key   .
               $arg5  . 
               $key   .
               $arg6  . 
               $key   .
               $arg7  . 
               $key   .
               $arg8  . 
               $key   .
               $arg9  . 
               $key   .
               $arg10 . 
               $key
               )
         );
   }
//------------------------------------------------------------------------
?>
