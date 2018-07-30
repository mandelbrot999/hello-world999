<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/config.inc 205 2018-07-15 19:00:51Z dashley $
//********************************************************************************
//config.inc--FboPrime FBO Configuration
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
//This file must be customized for each FBO.  The following information is
//customizable:
//
//   o MySQL database information (which host to connect to, which database to use, 
//     and the password to use for the database).
//
//   o FBO name, address, phone numbers, and e-mail contact information.
//
//   o Scheduling behavior parameters, such as how long information should be
//     retained, how close to a reservation time a reservation may be made or
//     canceled without contacting the FBO, how standby reservations are
//     handled, etc. 
//
//   o Colors.
//
//==============================================================================================================
//==============================================================================================================
//====  MySQL Information ======================================================================================
//==============================================================================================================
//==============================================================================================================
//MySQL connection configuration.  This information must be kept absolutely
//private (i.e. with this information, an attack could potentially be mounted).
//
define("CONFIG_MYSQL_SERVER",   "localhost");
define("CONFIG_MYSQL_DATABASE", "fboprimedevel");
define("CONFIG_MYSQL_USERNAME", "fboprimedevel");
define("CONFIG_MYSQL_PASSWORD", "quelle0");
//
//Prefix to use in the system logs when there is a database problem and a system log entry must be
//made.
//
define("CONFIG_MYSQL_ERR_SYSLOG_PREFIX", "FBO-PRIME");
//
//==============================================================================================================
//==============================================================================================================
//====  Web Location/URL/Cookie Options  =======================================================================
//==============================================================================================================
//==============================================================================================================
//These options control how certain URLs are formed, how cookies are issued, etc.  It is important to get
//these right, or logins won't work (among other things).
//
define("CONFIG_URL_DOMAIN",       "fboprimedevel.e3ft.com" ); //The server name as used in the URL.  This is
                                                              //used for cookies and to create some URLs.
define("CONFIG_URL_FSPATH",       "/flightschedule"        ); //The path within the base URL where the flight
                                                              //scheduler is.  This is used for cookies and
                                                              //to create some URLs.

//==============================================================================================================
//==============================================================================================================
//====  FBO Name, Address, and Other Information  ==============================================================
//==============================================================================================================
//==============================================================================================================
//FBO name and identity information.
//
define("CONFIG_FBO_NAME_LONG",     "Acme Aviation, LLC");     //Long name.
define("CONFIG_FBO_NAME_MEDIUM",   "Acme Aviation");          //Medium name.
define("CONFIG_FBO_NAME_SHORT",    "Acme");                   //Short name.
define("CONFIG_FBO_NAME_TINY",     "AA");                     //Tiny name, typically an acronym.
//--------------------------------------------------------------------------------------------------------------
//FBO physical address information.  The physical address is where a person would visit the FBO.
//
define("CONFIG_FBO_VADDRESS_COUNTRY",     "U.S.A.");          //Country.  Not normally displayed, so separated
                                                              //out.
define("CONFIG_FBO_VADDRESS_01", "123 Anywhere Lane");
define("CONFIG_FBO_VADDRESS_02", "Pleasantville IA 12345-6789");
define("CONFIG_FBO_VADDRESS",    CONFIG_FBO_VADDRESS_01 . "//" . CONFIG_FBO_VADDRESS_02 );
//--------------------------------------------------------------------------------------------------------------
//FBO correspondence address information.  For most FBOs, this will be the same as the physical
//address.
//
define("CONFIG_FBO_CADDRESS_COUNTRY",     CONFIG_FBO_VADDRESS_COUNTRY);
define("CONFIG_FBO_CADDRESS",             CONFIG_FBO_VADDRESS_01 . "//" . CONFIG_FBO_VADDRESS_02 );
//--------------------------------------------------------------------------------------------------------------
//FBO package delivery address information.  For most FBOs, this will be the same as the physical
//address.
//
define("CONFIG_FBO_PADDRESS_COUNTRY",     CONFIG_FBO_VADDRESS_COUNTRY);
define("CONFIG_FBO_PADDRESS",             CONFIG_FBO_VADDRESS_01 . "//" . CONFIG_FBO_VADDRESS_02 );
//--------------------------------------------------------------------------------------------------------------
//FBO phone numbers.
//
define("CONFIG_FBO_OPHONE",               "123-456-7890"   );    //The general office phone number.
define("CONFIG_FBO_SPHONE",               CONFIG_FBO_OPHONE);    //The phone number to use for scheduling matters.
define("CONFIG_FBO_FPHONE",               CONFIG_FBO_OPHONE);    //The FAX number.
define("CONFIG_FBO_PPHONE",               CONFIG_FBO_OPHONE);    //The phone number to use for package delivery.
//
//--------------------------------------------------------------------------------------------------------------
//Automatically-generated e-mail options.
//
define("CONFIG_FBO_AUTOMAIL_FROM",        "automailer@acmeaviation.com");  //Address that e-mail should be from.
define("CONFIG_FBO_AUTOMAIL_LINELENGTH",  69                           );  //Line length of automatically-generated
                                                                           //e-mail.  69 should not be exceeded
                                                                           //due to documentation of mail() function.
//
//Returns the footer text to be used in automatically-generated e-mails.  Has to be defined
//as a function to prevent evaluation of global variables before they have been set.
//
function CONFIG_fbo_automail_footer_text()
   {
   global $GLOBAL_stime_year;
   global $GLOBAL_stime_month;
   global $GLOBAL_stime_day;
   global $GLOBAL_stime_hour;
   global $GLOBAL_stime_minute;

   $hyphen_line = "";
   for ($i=0; $i<(CONFIG_FBO_AUTOMAIL_LINELENGTH + 1); $i++)
      $hyphen_line .= "-";

   return(
         $hyphen_line 
         .
         " "
         .
         "This e-mail was automatically generated by the server on "
         .
         DATEFUNC_stdlongdate_w_dow($GLOBAL_stime_year, $GLOBAL_stime_month, $GLOBAL_stime_day)
         .
         " at "
         .
         DATEFUNC_stdtimenosec($GLOBAL_stime_hour, $GLOBAL_stime_minute)
         .
         "  "
         .
         "Please contact "
         .
         CONFIG_FBO_NAME_LONG
         .
         " at "
         .
         CONFIG_FBO_OPHONE
         .
         " if you have any questions or concerns about this e-mail.  "
         .
         "Please do not reply to this e-mail, as it is "
         .
         "automatically generated and replies are not processed."
         );
   }
//
//
//==============================================================================================================
//==============================================================================================================
//====  Time Locale  ===========================================================================================
//==============================================================================================================
//==============================================================================================================
//Time locale is tricky because of U.S. daylight savings time, which is sometimes problematic because of 
//local legislation and pending legislation being inconsistent with the Linux code base.  For that reason,
//the translation between the server's time and the client local time used for scheduling is handled with a 
//function in the CONFIG file--that gives the option of making very sophisticated mappings if it ever becomes
//necessary.
//
//This mapping is provided because the server's time may be different than the time at the FBO.  It would be
//possible, for example, to have an FBO in Los Angeles, California, USA served by a server in Paris, France.
//
//If you use FBO-Prime and have developed alternate mappings, please e-mail them to the authors so they
//can be included in the documentation.
//
function CONFIG_unix_sched_time_map( $unix_seconds,         //Input, Unix server seconds, string (string to
                                                            //deal with the 2037 A.D. Unix epoch issue).
                                     $unix_nanoseconds,     //Input, Unix server nanoseconds, integer, 0-999,999,999.
                                    &$sched_year,           //Output, client locale year, integer, 2,000-2,099.
                                    &$sched_month,          //Output, client locale month, integer, 1-12.
                                    &$sched_day,            //Output, client locale day of month, integer, 1-31.
                                    &$sched_hour,           //Output, client locale hour, integer, 0-23.
                                    &$sched_minute,         //Output, client locale minute, integer, 0-59.
                                    &$sched_second,         //Output, client locale second, integer, 0-59.
                                    &$sched_microsecond,    //Output, client locale microsecond, integer, 0-999,999.
                                    &$sched_dow             //Output, day of week, integer, 0-6, 0=Sunday.
                                     )
   {
   //At the present time, should use the built-in PHP functions to convert from integer seconds to
   //the time and so on.  Later on, may do it another way.  The built-in PHP functions will probably
   //not work for anything over 2037.  Probably want to use bcmath, subtract out the GMT seconds
   //at midnight on Jan 1, 2000, etc.
   
   //Integer Unix seconds for use with PHP date() function--simple typecast should work until 2037 A.D.
   $unix_seconds_int = (int)$unix_seconds;
  
   //Integer year in locale.
   $sched_year   = (int) date("Y", $unix_seconds_int);

   //Integer month in locale.
   $sched_month  = (int) date("n", $unix_seconds_int);
   
   //Integer day in locale.
   $sched_day    = (int) date("j", $unix_seconds_int);
   
   //Integer hour in locale.
   $sched_hour   = (int) date("G", $unix_seconds_int);
   
   //Integer minute in locale.
   $sched_minute_string 
                 =       date("i", $unix_seconds_int);
   if (SubStr($sched_minute_string, 0, 1) == "0")
      $sched_minute_string = SubStr($sched_minute_string, 1, 1);
   $sched_minute = (int)$sched_minute_string;

   //Integer second in locale.
   $sched_second_string 
                 =       date("s", $unix_seconds_int);
   if (SubStr($sched_second_string, 0, 1) == "0")
      $sched_second_string = SubStr($sched_second_string, 1, 1);
   $sched_second = (int)$sched_second_string;
   
   //Integer microseconds in locale.  Since any locale can only adjust by
   //integer seconds, the fractional time is carried through.
   $sched_microsecond = $unix_nanoseconds / 1000;

   //Integer day of week in locale.
   $sched_dow  = (int) date("w", $unix_seconds_int);
   }
//
//==============================================================================================================
//==============================================================================================================
//====  Miscellaneous Global Options  ==========================================================================
//==============================================================================================================
//==============================================================================================================
//Time format.
//
define("CONFIG_TIME_FORMAT_24HR",     FALSE);  //Change to TRUE for military time.
//
//Date format.
//
define("CONFIG_DATE_FORMAT_EUROPEAN", FALSE);  //Change to TRUE to get European dates (DD/MM/YY).
//
//==============================================================================================================
//==============================================================================================================
//====  Global Appearance Options  =============================================================================
//==============================================================================================================
//==============================================================================================================
//Default color used for most backgrounds, etc. to give a consistent color scheme.
define("CONFIG_GLOBAL_COLOR_BACKGROUND",            "AAAACC");
//
//Default colors used for small banner bars, such as appear in the scheduling
//mini-calendar.
define("CONFIG_GLOBAL_BANNERBAR_MINI_A",            "ADD8E6");
define("CONFIG_GLOBAL_BANNERBAR_MINI_B",            "888888");
//
//Color used for unvisited, visited, and active links.
define("CONFIG_GLOBAL_COLOR_LINK",                 "4040C0"                      );
define("CONFIG_GLOBAL_COLOR_UVLINK",               CONFIG_GLOBAL_COLOR_LINK      );
define("CONFIG_GLOBAL_COLOR_VLINK",                CONFIG_GLOBAL_COLOR_LINK      );
define("CONFIG_GLOBAL_COLOR_ALINK",                CONFIG_GLOBAL_COLOR_LINK      );
//
//Colors used for serious error notices.
define("CONFIG_GLOBAL_COLOR_ERROR_BG",                 "FF8080"                  );
define("CONFIG_GLOBAL_COLOR_ERROR_TEXT",               "000000"                  );
//
//Whether to generate pretty HTML (pretty = formatted for human viewing).  Pretty
//HTML is good for human viewing and useful in debugging, but takes longer for the browser to load,
//especially over a slow communication channel.
define("CONFIG_HTML_PRETTY",                       TRUE);
//
//==============================================================================================================
//==============================================================================================================
//====  Scheduling Day View Appearance Options  ================================================================
//==============================================================================================================
//==============================================================================================================
//Color used for the background of the login box, choices, mini-calendars.
define("CONFIG_SCHED_COLOR_BACKGROUND",            CONFIG_GLOBAL_COLOR_BACKGROUND);
//
//Color used for the table cells displaying time.
define("CONFIG_SCHED_COLOR_TABLE_TIME_CELL",       CONFIG_GLOBAL_COLOR_BACKGROUND);
//
//Colors used for calendar dates in the mini-calendar when the day is both the current
//day and the one being viewed, the calendar day only, and the day being viewed only.
define("CONFIG_SCHED_COLOR_MINICAL_CURVIEW",       "FFFFFF"                      );
define("CONFIG_SCHED_COLOR_MINICAL_CURONLY",       "5F9EA0"                      );
define("CONFIG_SCHED_COLOR_MINICAL_VIEWONLY",      "3CB371"                      );
//
//Colors used for cells in the scheduling matrix.
define("CONFIG_SCHED_COLOR_DSMAT_THEAD",           "AAAAAA"                      );  //Top/bot column headings.
define("CONFIG_SCHED_COLOR_DSMAT_LHEAD",           "AAAAAA"                      );  //Left row headings.
define("CONFIG_SCHED_COLOR_DSMAT_RIDLE",           "FFFFFF"                      );  //Idle reservation cells.
define("CONFIG_SCHED_COLOR_DSMAT_RBANN",           "80FF80"                      );  //Banner reservation cells.
define("CONFIG_SCHED_COLOR_DSMAT_RACTV",           "8080FF"                      );  //Active reservation cells.
define("CONFIG_SCHED_COLOR_DSMAT_RSTBY",           "B0B0B0"                      );  //Standby reservation cells.
//
//==============================================================================================================
//==============================================================================================================
//====  Scheduling Behavior Options  ===========================================================================
//==============================================================================================================
//==============================================================================================================
//The number of months before and after the current date where a user is able to view and (in the future
//only) change the schedule.  The limit works in a whole month sense, i.e. either an entire month is or is
//not viewable and schedulable.  Both of these limits work in a <= or >= sense.  For the lower limit,
//   PRES   -   PAST   <=   PAST_LIMIT
//and for the upper limit,
//   FUTU   -   PRES   <=   FUTURE_LIMIT
//So, for example, a limit of one for both would allow one to view the past month and the next month.
//
define("CONFIG_SCHED_SCHEDACC_PREV_MO",            4       );
define("CONFIG_SCHED_SCHEDACC_FUTU_MO",            7       );
//
//The lockout period where a user can't make reservations any fewer than this many hours before the
//scheduled time.
define("CONFIG_SCHED_RESV_BUFF_HRS",              12       );
//
//The number of hours days that a reservation purely in the past can be modified by _anyone_.  After some
//period of time it becomes a historical record and should not be modified.
define("CONFIG_SCHED_RESV_PAST_LOCK_DAYS",         2       );
//
//The layout of the scheduling day view in terms of the hours of the day displayed.  The hours of the day
//are divided into panels, not necessarily non-overlapping.  This array defines the panels.
//The upper limits on the panels are "closed", i.e. 0,9 means midnight through 9:59 a.m.
//The paneling scheme may not have a panel that crosses midnight (reservations may cross midnight,
//of course, but one of the assumptions made in the reservation display code is that panels do not
//cross midnight).
$CONFIG_SCHED_DAY_PANELS = array(  0,   9,
                                   7,  18,
                                  14,  23 );
//
//==============================================================================================================
//==============================================================================================================
//====  Logging Options  =======================================================================================
//==============================================================================================================
//==============================================================================================================
//The number of log entries that should be retained in the log.  500,000 seems like a reasonable number.  For
//an FBO that gets 2,000 log entries per day, this gives a history of the better part of a year--seems good
//enough.  Disk space consumption has not been estimated.
//
define("CONFIG_LOG_MAX_ENTRIES", 500000);
//
//==============================================================================================================
//==============================================================================================================
//====  Login Recovery Options  ================================================================================
//==============================================================================================================
//==============================================================================================================
//The number of minutes for which temporary passwords are valid.
//
define("CONFIG_LOGIN_REC_TEMP_PW_LIFETIME", 30);
//
//==============================================================================================================
//==============================================================================================================
//====  User Creation and Privilege Options  ===================================================================
//==============================================================================================================
//==============================================================================================================
//The array below represents the pecking order at the typical FBO.  For each category of user, the array
//contains, in order:
//   a)The security level of the category.  (A smaller integer corresponds to more privilege.)
//   b)The text description of the category of user.  This is suitable for drop-down lists in web forms.
//   c)A shorter text tag of the category of user.  This must contain no spaces.
//   d)The privilege string to use when creating this category of user.
//
//Note that the integer index of the category of user is implied by its location in the table.
//
$CONFIG_FBO_USER_CATEGORIES = array(
   //--------------------------------------------------------------------------------
   //The database administrator has even more privileges than the owner/operator of the FBO.
   //There may be technical changes to the database and so on that the DB admin may make but which
   //would be dangerous for non-technical users to make.
   0,  
   "Database Administrator",                 
   "CONFIG_FBO_USR_CAT_DBADMIN",
   "",
   //--------------------------------------------------------------------------------
   //The owner/partner of the FBO has every non-technical privilege.  Additionally, because
   //they have a security level with more privilege than any other category of user, nobody at
   //the business may alter their privileges.
   1,  
   "Owner/Partner",                 
   "CONFIG_FBO_USR_CAT_OWNERPARTNER",
   "\\canviewlogentries=\"\""           .       //Can view logs.
   "\\canresetpasswords=\"\""           .       //Can reset passwords.
   "\\canviewreservationdetails=\"\""   .       //Can view reservation details.
   "\\sesslifetimedefault=\"900\"",             //15 minutes default logout time.
   //--------------------------------------------------------------------------------
   //The manager of the FBO is/are the individual(s) who run the FBO on a day-to-day
   //basis.
   2,  
   "Manager",                 
   "CONFIG_FBO_USR_CAT_MANAGER",
   "\\canviewlogentries=\"\""           .       //Can view logs.
   "\\canresetpasswords=\"\""           .       //Can reset passwords.
   "\\canviewreservationdetails=\"\""   .       //Can view reservation details.
   "\\sesslifetimedefault=\"900\"",             //15 minutes default logout time.
   //--------------------------------------------------------------------------------
   //The office manager is typically below the manager.  Just to prevent accidents,
   //this is probably the lowest-ranking employee that should be able to modify
   //resources.  Other employees are certainly trustworthy, but human curiousity
   //is what it is, and computers are what they are.
   3,  
   "Office Manager",                 
   "CONFIG_FBO_USR_CAT_OFFICEMANAGER",
   "\\canviewlogentries=\"\""           .       //Can view logs.
   "\\canresetpasswords=\"\""           .       //Can reset passwords.
   "\\canviewreservationdetails=\"\""   .       //Can view reservation details.
   "\\sesslifetimedefault=\"900\"",             //15 minutes default logout time.
   //--------------------------------------------------------------------------------
   //The flight instructors, office employees, and mechanics have quite liberal 
   //privileges, but less than the office manager (to prevent accidents).
   4,  
   "Flight Instructor",                 
   "CONFIG_FBO_USR_CAT_FLIGHTINSTRUCTOR",
   "\\canviewlogentries=\"\""           .       //Can view logs.
   "\\canresetpasswords=\"\""           .       //Can reset passwords.
   "\\canviewreservationdetails=\"\""   .       //Can view reservation details.
   "\\sesslifetimedefault=\"900\"",             //15 minutes default logout time.
   //--------------------------------------------------------------------------------
   //Office employee
   4,  
   "Office Employee",                 
   "CONFIG_FBO_USR_CAT_OFFICEEMPLOYEE",
   "\\canviewlogentries=\"\""           .       //Can view logs.
   "\\canresetpasswords=\"\""           .       //Can reset passwords.
   "\\canviewreservationdetails=\"\""   .       //Can view reservation details.
   "\\sesslifetimedefault=\"900\"",             //15 minutes default logout time.
   //--------------------------------------------------------------------------------
   //Mechanic
   4,  
   "Mechanic",                 
   "CONFIG_FBO_USR_CAT_MECHANIC",
   "\\canviewlogentries=\"\""           .       //Can view logs.
   "\\canresetpasswords=\"\""           .       //Can reset passwords.
   "\\canviewreservationdetails=\"\""   .       //Can view reservation details.
   "\\sesslifetimedefault=\"900\"",             //15 minutes default logout time.
   //--------------------------------------------------------------------------------
   //Line Employee:  Fewer privileges than flight instructors and others.
   5,  
   "Line Employee",                 
   "CONFIG_FBO_USR_CAT_LINEEMPLOYEE",
   "\\canviewlogentries=\"\""           .       //Can view logs.
   "\\canresetpasswords=\"\""           .       //Can reset passwords.
   "\\canviewreservationdetails=\"\""   .       //Can view reservation details.
   "\\sesslifetimedefault=\"900\"",             //15 minutes default logout time.
   //--------------------------------------------------------------------------------
   //Customer:  fewest privileges of all.
   20,
   "Customer",                 
   "CONFIG_FBO_USR_CAT_CUSTOMER",
   "\\sesslifetimedefault=\"1800\"",            //30 minutes default logout time.
                                   );
//The session lifetime (seconds) to use if the user who logs in does not have the necessary
//information in the permission string.
define("CONFIG_SESS_LIFETIME_DEFAULT",          1200);                           //20 minutes
//
//--------------------------------------------------------------------------------------------------------------
//End of $RCSfile: config.inc,v $.
//--------------------------------------------------------------------------------------------------------------
?>
