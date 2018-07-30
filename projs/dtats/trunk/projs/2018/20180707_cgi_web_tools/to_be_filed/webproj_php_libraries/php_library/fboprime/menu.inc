<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/menu.inc 205 2018-07-15 19:00:51Z dashley $
//--------------------------------------------------------------------------------------------------------------
//menu.inc--FboPrime Menu Generation Functions
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
//This contains functions used to log events, both to the loge table of the
//database, and to the system log.
//--------------------------------------------------------------------------------------------------------------
require_once("global.inc");
require_once("strfunc.inc");
require_once("utime.inc");
//
//--------------------------------------------------------------------------------------------------------------
//Generates a menu list as a function of:
//
//INPUTS
//   a)The full set of user information (the database record as
//     an associative array), or FALSE if no user is logged in.
//   b)The desired menu level.  The menu level
//     is an integer, with 0 representing the fewest options, 1 representing
//     a medium number of options, and 2 represents the largest number
//     of options.
//   c)The target date as a DT8 (for example "20060516"), or FALSE if
//     not required.
//   d)The target time as a T4 (for example, "0500"), or FALSE if not
//     required.
//   e)The name of the script (final element of path).
//
//OUTPUT
//   An array arranged as 3-tuples (starting at [0]), 
//      [N]          :  "H" if the 3-tuple is a category heading, or
//                      "E" if it is an entry.
//      [N+1]        :  Text of the category heading or entry.
//      [N+2]        :  Hyperlink corresponding to the entry (or the
//                      empty string for headings).
//
function MENU_menu_gen($userinfo, $menulevel, $dt8in, $t4in, $scriptname_in)
   {
   //Form a string containing the date and time arranged as GET parameters.  This will be tacked
   //on to certain URLs.
   if (($dt8in === FALSE) && ($t4in === FALSE))
      {
      //No parameters to be appended.
      $get_par_append = FALSE;
      } 
   else if (($dt8in === FALSE) && ($t4in !== FALSE))
      {
      //Time has been specified, but date not.
      $get_par_append = "sdtim=" . $t4in;
      }
   else if (($dt8in !== FALSE) && ($t4in === FALSE))
      {
      //Date has been specified, but time not.
      $get_par_append = "sddt=" . $dt8in;
      }
   else //Both have been specified.
      {
      $get_par_append = "sddt=" . $dt8in . "&sdtim=" . $t4in;
      }

   $i = 0;
   
   //The heading "Scheduling Views" is always appropriate.
   $rv[$i  ]  = "H";     
   $rv[$i+1]  = "Scheduling Views";
   $rv[$i+2]  = "";
   $i        += 3;
   //
   //Scheduling day view is always appropriate.
   $rv[$i  ]  = "E";     
   $rv[$i+1]  = "Day View";
   if ($get_par_append === FALSE)
      $rv[$i+2]  = "index.php";
   else
      $rv[$i+2]  = "index.php?" . $get_par_append;
   $i        += 3;
   //
   //Scheduling week view is only appropriate at menu level 1 and above.
   if ($menulevel >= 1)
      {
      $rv[$i  ]  = "E";     
      $rv[$i+1]  = "Week View";
      if ($get_par_append === FALSE)
         $rv[$i+2]  = "schedweekview.php";
      else
         $rv[$i+2]  = "schedweekview.php?" . $get_par_append;
      $i        += 3;
      }
   //
   //Scheduling month view is only appropriate at menu level 2 and above.
   if ($menulevel >= 2)
      {
      $rv[$i  ]  = "E";     
      $rv[$i+1]  = "Month View";
      if ($get_par_append === FALSE)
         $rv[$i+2]  = "schedmonthview.php";
      else
         $rv[$i+2]  = "schedmonthview.php?" . $get_par_append;
      $i        += 3;
      }
   //
   //The heading "Queries" is only appropriate when a user is logged in.
   if ($userinfo !== FALSE)
      {
      $rv[$i  ]  = "H";     
      $rv[$i+1]  = "Queries";
      $rv[$i+2]  = "";
      $i        += 3;
      //
      //Showing "My Reservations" is only appropriate when a user is logged in.
      $rv[$i  ]  = "E";     
      $rv[$i+1]  = "Show My Reservations";
      if ($get_par_append === FALSE)
         $rv[$i+2]  = "myresshow.php";
      else
         $rv[$i+2]  = "myresshow.php?" . $get_par_append;
      $i        += 3;
      }
   //
   //Utilities should be shown if the user is cleared to view the users list, clear to
   //edit resources, to view the log entries, or to view the database statistics and
   //if the menu level is 2.
   //
   if (
         ($userinfo !== FALSE) 
         && 
         (
            (PERM_get_val_from_string($userinfo["perm"], "canviewuserslist"       ) !== FALSE)
            || 
            (PERM_get_val_from_string($userinfo["perm"], "canvieweditresources"   ) !== FALSE)
            || 
            (PERM_get_val_from_string($userinfo["perm"], "canviewlogentries"      ) !== FALSE) 
            || 
            (PERM_get_val_from_string($userinfo["perm"], "canviewdbstats"         ) !== FALSE)
         ) 
         && 
         ($menulevel >= 2)
      )
      {
      $rv[$i  ]  = "H";     
      $rv[$i+1]  = "Utilities";
      $rv[$i+2]  = "";
      $i        += 3;

      //Display the view/edit active users option if the permission string says it is OK.
      if (PERM_get_val_from_string($userinfo["perm"], "canviewuserslist") !== FALSE)
         {
         $rv[$i  ]  = "E";     
         $rv[$i+1]  = "View/Edit Active Users";
         $rv[$i+2]  = "userlistactive.php";
         $i        += 3;
         }

      //Display the view/edit inactive users option if the permission string says it is OK.
      if (PERM_get_val_from_string($userinfo["perm"], "canviewuserslist") !== FALSE)
         {
         $rv[$i  ]  = "E";     
         $rv[$i+1]  = "View/Edit Inactive Users";
         $rv[$i+2]  = "userlistinactive.php";
         $i        += 3;
         }

      //Display the view/edit resources option if the permission string says it is OK.
      if (PERM_get_val_from_string($userinfo["perm"], "canvieweditresources") !== FALSE)
         {
         $rv[$i  ]  = "E";     
         $rv[$i+1]  = "View/Edit Resources";
         $rv[$i+2]  = "resourcelist.php";
         $i        += 3;
         }

      //Display the logview option if the permission string says it is OK.
      if (PERM_get_val_from_string($userinfo["perm"], "canviewlogentries") !== FALSE)
         {
         $rv[$i  ]  = "E";     
         $rv[$i+1]  = "View Resource Scheduler Log";
         if ($get_par_append === FALSE)
            $rv[$i+2]  = "viewresschedlog.php";
         else
            $rv[$i+2]  = "viewresschedlog.php?" . $get_par_append;
         $i        += 3;
         }

      //Display the database view option if the permission string says it is OK.
      if (PERM_get_val_from_string($userinfo["perm"], "canviewdbstats") !== FALSE)
         {
         $rv[$i  ]  = "E";     
         $rv[$i+1]  = "View Database Statistics";
         if ($get_par_append === FALSE)
            $rv[$i+2]  = "viewdbstats.php";
         else
            $rv[$i+2]  = "viewdbstats.php?" . $get_par_append;
         $i        += 3;
         }
      }
   //
   //The self-administration heading applies only when a user is logged in and the 
   //menu level is 2 or greater.
   //
   if (($userinfo !== FALSE) && ($menulevel >= 2))
      {
      $rv[$i  ]  = "H";     
      $rv[$i+1]  = "Self-Administration";
      $rv[$i+2]  = "";
      $i        += 3;
      }
   //
   //The password change applies only when a user is logged in and when the 
   //menu level >= 1.
   //
   if (($userinfo !== FALSE) && ($menulevel >= 2))
      {
      $rv[$i  ]  = "E";     
      $rv[$i+1]  = "Change Password";
      if ($get_par_append === FALSE)
         $rv[$i+2]  = "userpwchange.php";
      else
         $rv[$i+2]  = "userpwchange.php?" . $get_par_append;
      $i        += 3;
      }
   //
   //The change personal information only applies when a user is 
   //logged in and the menu level >= 1.
   //
   if (($userinfo !== FALSE) && ($menulevel >= 2))
      {
      $rv[$i  ]  = "E";     
      $rv[$i+1]  = "Change Personal Information";
      if ($get_par_append === FALSE)
         $rv[$i+2]  = "userpersinfochange.php";
      else
         $rv[$i+2]  = "userpersinfochange.php?" . $get_par_append;
      $i        += 3;
      }
   //
   //Menus heading is only appropriate when a user is logged in and at the day view
   //scheduler.
   if (($userinfo !== FALSE)  && ($scriptname_in == "index.php"))
      {
      $rv[$i  ]  = "H";     
      $rv[$i+1]  = "Menus";
      $rv[$i+2]  = "";
      $i        += 3;
      //
      //Showing "More Options" is appropriate only when options level is 1 or less.
      if ($menulevel <= 1)
         {
         $rv[$i  ]  = "E";     
         $rv[$i+1]  = "Show More Options";
         if ($get_par_append === FALSE)
            $rv[$i+2]  = "index.php?menulvladjst=u";
         else
            $rv[$i+2]  = "index.php?" . "menulvladjst=u&" . $get_par_append;
         $i        += 3;
         }
      //Showing "Fewer Options" is appropriate only when options level is 1 or more.
      if ($menulevel >= 1)
         {
         $rv[$i  ]  = "E";     
         $rv[$i+1]  = "Show Fewer Options";
         if ($get_par_append === FALSE)
            $rv[$i+2]  = "index.php?menulvladjst=d";
         else
            $rv[$i+2]  = "index.php?" . "menulvladjst=d&" . $get_par_append;
         $i        += 3;
         }
      }
   //
   //Session administration heading and subheadings are only appropriate when a user is logged in, and
   //should only be performed from the dayview page.
   if ($userinfo !== FALSE)
      {
      $rv[$i  ]  = "H";     
      $rv[$i+1]  = "Session Administration";
      $rv[$i+2]  = "";
      $i        += 3;
      //
      //Showing "Logout" is appropriate only when user logged in.
      $rv[$i  ]  = "E";     
      $rv[$i+1]  = "Logout";
      if ($get_par_append === FALSE)
         $rv[$i+2]  = "index.php?logout=1";
      else
         $rv[$i+2]  = "index.php?" . "logout=1&" . $get_par_append;
      $i        += 3;
      }
   //
   return($rv);
   }
//
//--------------------------------------------------------------------------------------------------------------
//End of $RCSfile: menu.inc,v $.
//--------------------------------------------------------------------------------------------------------------
?>
