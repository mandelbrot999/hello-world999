<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/stdformat.inc 205 2018-07-15 19:00:51Z dashley $
//--------------------------------------------------------------------------------------------------------------
//stdformat--FboPrime Page Standard "Look and Feel" Functions
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
require_once("config.inc");
require_once("confighard.inc");
require_once("htmlformat.inc");
require_once("strfunc.inc");
require_once("usrs.inc");
//
//--------------------------------------------------------------------------------------------------------------
//This file contains functions that emit standard elements of FboPrime pages and otherwise give the set of
//pages a consistent (and hopefully easy to modify) look and feel.
//--------------------------------------------------------------------------------------------------------------
//Emits the standard page when the script can't connect to MySQL or select the database of interest.
//
function STDFORMAT_dbstartuperrorpage()
   {
   ?>
   <html>
      <head>
         <title>Server Internal Database Connect/Select Error</title>
      </head>
   <body>
      <p align="center">
          <font size="6">
             <b>
                There has been an internal server error (unable to connect to database and/or unable
                to select database).
             </b>
          </font>
      </p>
      <p align="center">
          <font size="6">
             <b>
                If this problem persists, please contact <?php echo CONFIG_FBO_NAME_LONG;?>
                at <?php echo CONFIG_FBO_OPHONE;?>.
             </b>
          </font>
      </p>
   </body>
   </html>
   <?php
   }
//
//--------------------------------------------------------------------------------------------------------------
//Emits the standard page when the client page requires that a user be logged in but there is no user logged in.
//
function STDFORMAT_nologgedinerrorpage($sddt, $sdtim)
   {
   HTMLFORMAT_echo_push_nl("<html>");
      HTMLFORMAT_echo_push_nl("<head>");
         HTMLFORMAT_echo_noop_nl("<title>FBO-Prime User Login Required</title>");
      HTMLFORMAT_echo_pull_nl("</head>");
      HTMLFORMAT_echo_push_nl("<body>");
         HTMLFORMAT_echo_push_nl("<table width=\"100%\" border=\"1\" cellspacing=\"0\" cellpadding=\"4\" rules=\"none\">");
            HTMLFORMAT_echo_push_nl("<tr>");
               HTMLFORMAT_echo_push_nl("<td align=\"center\">");
                  HTMLFORMAT_echo_noop_nl("<title>FBO-Prime User Login Required</title>");
                     HTMLFORMAT_echo_noop_nl("<br><br><br><br><br><p>In order to use this page, you must be logged in as a user.&nbsp; The most");
                     HTMLFORMAT_echo_noop_nl("likely reason for this message is that your session timed out due to");
                     HTMLFORMAT_echo_noop_nl("inactivity.</p>");

                     HTMLFORMAT_echo_noop_nl("<p>Click ");

                     $baseurl = "index.php";
                     if (($sddt === FALSE) && ($sdtim === FALSE))
                        {
                        //No adjustment to the base URL needed.
                        }
                     else if (($sddt === FALSE) && ($sdtim !== FALSE))
                        {
                        $baseurl = $baseurl . "?sdtim=" . $sdtim;
                        }
                     else if (($sddt !== FALSE) && ($sdtim === FALSE))
                        {
                        $baseurl = $baseurl . "?sddt=" . $sddt;
                        }
                     else
                        {
                        $baseurl = $baseurl . "?sddt=" . $sddt . "&sdtim=" . $sdtim;
                        }
                     HTMLFORMAT_echo_noop_nl("<a href=\"" . $baseurl . "\">here</a> to return to the day view scheduler.</p><br><br><br><br><br>");
               HTMLFORMAT_echo_pull_nl("</td>");
            HTMLFORMAT_echo_pull_nl("</tr>");
         HTMLFORMAT_echo_pull_nl("</table>");
         STDFORMAT_stdfooter_tabular(FALSE, $sddt, $sdtim);
       HTMLFORMAT_echo_pull_nl("</body>");
   HTMLFORMAT_echo_pull_nl("</html>");
   }
//
//--------------------------------------------------------------------------------------------------------------
//Forms the standard string characteristic of an FBO-prime footer.
//
//Parameters:
//  uiarray      :  An associative array containing user information for the logged-in user,
//                  or FALSE if no user is logged in.
//  sddate       :  The date string to use when returning to the main scheduling page if the
//                  logout link is clicked.  If FALSE is passed for this parameter, it is
//                  omitted.
//  sdtime       :  The time string to use when returning to the main scheduling page if the
//                  logout link is clicked.  If FALSE is passed for this parameter, it is
//                  omitted. 
//
function STDFORMAT_stdfooter_string($uiarray, $sddate, $sdtime)
   {
   global $GLOBAL_stime_year;
   global $GLOBAL_stime_month;
   global $GLOBAL_stime_day;
   global $GLOBAL_stime_hour;
   global $GLOBAL_stime_minute;
   global $GLOBAL_stime_second;

   $s  = "";
   $s .= "This page was generated by the server on ";
   $s .= DATEFUNC_stdlongdate_w_dow($GLOBAL_stime_year, $GLOBAL_stime_month, $GLOBAL_stime_day);
   $s .= " at ";
   $s .= DATEFUNC_stdtimenosec($GLOBAL_stime_hour, $GLOBAL_stime_minute);
   $s .= " local time.&nbsp; ";
   if ($uiarray === FALSE)
      {
      $s .= "You are not logged in.";
      }
   else
      {
      USRS_form_display_strings_a($uiarray, $dispuserid, $dispname);
      $s .= "You are logged in as ";
      $s .= $dispname;
      $s .= " (<i>";
      $s .= $dispuserid;
      $s .= "</i>) (<a href=\"index.php?logout=1";
      if (($sddate !== FALSE) && ($sdtime !== FALSE))
         {
         $s = $s . "&amp;sddt=" . $sddate . "&amp;sdtim=" . $sdtime;
         }
      else if ($sddate !== FALSE)
         {
         $s = $s . "&amp;sddt=" . $sddate;
         }
      else if ($sdtime !== FALSE)
         {
         $s = $s . "&amp;stim=" . $sdtime;
         }
      $s .= "\">logout</a>).";
      }

   $s .=   "&nbsp; <i>FBO-Prime</i> is free open-source software&#8212;it can be downloaded <a href=\""
         . CONFIGHARD_FBOPRIME_HOME_PAGE_URL
         . "\" target=\"_blank\">here</a>.";
   return($s);
   }
//
//--------------------------------------------------------------------------------------------------------------
//Emits the standard footer characteristic of the FBO-Prime software.
//
//Parameters:
//  uiarray      :  An associative array containing user information for the logged-in user,
//                  or FALSE if no user is logged in. 
//
function STDFORMAT_stdfooter_tabular($uiarray, $sddate, $sdtime)
   {

   HTMLFORMAT_echo_push_nl("<table width=\"100%\" border=\"1\" cellspacing=\"0\" cellpadding=\"4\">");
      HTMLFORMAT_echo_push_nl("<tr>");
         HTMLFORMAT_echo_push_nl("<td align=\"center\">");
            HTMLFORMAT_echo_push_nl("<font size=\"2\">");
               HTMLFORMAT_echo_noop_nl(STDFORMAT_stdfooter_string($uiarray, $sddate, $sdtime));
            HTMLFORMAT_echo_pull_nl("</font>");
         HTMLFORMAT_echo_pull_nl("</td>");
      HTMLFORMAT_echo_pull_nl("</tr>");
   HTMLFORMAT_echo_pull_nl("</table>");
   }
//
//--------------------------------------------------------------------------------------------------------------
//End of $RCSfile: stdformat.inc,v $.
//--------------------------------------------------------------------------------------------------------------
?>
