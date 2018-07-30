<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/parx.inc 205 2018-07-15 19:00:51Z dashley $
//********************************************************************************
//parx.inc--FboPrime Parameter and Cookie Processing of Parameters Not Required
//          By Day View Scheduler
//
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
//This file contains functions that carefully control GET/POST input parameters
//and cookies and bring them into the global variable space.
//
//The most conservative approach is to restrict such parameters to a language,
//i.e. to confine the form they may have.
//--------------------------------------------------------------------------------
require_once("par.inc");
//
//--------------------------------------------------------------------------------
//
//For more documentation, please see par.inc.
//
//--------------------------------------------------------------------------------
//Obtains the resourceidx parameter and assigns it to the variable
//$PAR_resourceidx if it exists.  If it does not exist, the value of FALSE
//is assigned.
//
function PAR_get_resourceidx()
   {
   global $PAR_resourceidx;

   if ((! isset($_GET["resourceidx"])) && (! isset($_POST["resourceidx"])))
      {
      $PAR_resourceidx = FALSE;
      return;
      }
   else if (isset($_POST["resourceidx"])) //Post gets precedence--arbitrary choice.
      {
      $starting_point = $_POST["resourceidx"];
      }
   else if (isset($_GET["resourceidx"]))
      {
      $starting_point = $_GET["resourceidx"];
      }

   //Trim all disallowed characters.
   $starting_point = STRFUNC_force_into_subset($starting_point, "0123456789");

   //Strip off any leading zeros.
   while ((strlen($starting_point) > 1) && (SubStr($starting_point, 0, 1) == "0"))
      $starting_point = SubStr($starting_point, 1);

   //Convert/cast it to an integer if possible, else signal failure with
   //FALSE.
   if (is_numeric($starting_point))
      $starting_point = (int)$starting_point;
   else
      $starting_point = FALSE;

   //Assign final value.
   $PAR_resourceidx = $starting_point;
   }
//
//--------------------------------------------------------------------------------
//Obtains the useridx parameter and assigns it to the variable
//$PAR_useridx if it exists.  If it does not exist, the value of FALSE
//is assigned.
//
function PAR_get_useridx()
   {
   global $PAR_useridx;

   if ((! isset($_GET["useridx"])) && (! isset($_POST["useridx"])))
      {
      $PAR_useridx = FALSE;
      return;
      }
   else if (isset($_POST["useridx"])) //Post gets precedence--arbitrary choice.
      {
      $starting_point = $_POST["useridx"];
      }
   else if (isset($_GET["useridx"]))
      {
      $starting_point = $_GET["useridx"];
      }

   //Trim all disallowed characters.
   $starting_point = STRFUNC_force_into_subset($starting_point, "0123456789");

   //Strip off any leading zeros.
   while ((strlen($starting_point) > 1) && (SubStr($starting_point, 0, 1) == "0"))
      $starting_point = SubStr($starting_point, 1);

   //Convert/cast it to an integer if possible, else signal failure with
   //FALSE.
   if (is_numeric($starting_point))
      $starting_point = (int)$starting_point;
   else
      $starting_point = FALSE;

   //Assign final value.
   $PAR_useridx = $starting_point;
   }
//
//--------------------------------------------------------------------------------
//Determines whether the commitbuttonpressed parameter is present and assigns
//the variable $PAR_commitbuttonpressed FALSE if it does not exist or TRUE if it
//does not exist.
//
function PAR_get_commitbuttonpressed()
   {
   global $PAR_commitbuttonpressed;

   if (isset($_GET["commitbuttonpressed"]) || isset($_POST["commitbuttonpressed"]))
      {
      $PAR_commitbuttonpressed = TRUE;
      }
   else
      {
      $PAR_commitbuttonpressed = FALSE;
      }
   }
//
//--------------------------------------------------------------------------------
//Determines whether the addbuttonpressed parameter is present and assigns
//the variable $PAR_addbuttonpressed FALSE if it does not exist or TRUE if it
//does not exist.
//
function PAR_get_addbuttonpressed()
   {
   global $PAR_addbuttonpressed;

   if (isset($_GET["addbuttonpressed"]) || isset($_POST["addbuttonpressed"]))
      {
      $PAR_addbuttonpressed = TRUE;
      }
   else
      {
      $PAR_addbuttonpressed = FALSE;
      }
   }
//
//--------------------------------------------------------------------------------
//End of $RCSfile: parx.inc,v $.
//--------------------------------------------------------------------------------
?>
