<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/stdformatx.inc 205 2018-07-15 19:00:51Z dashley $
//--------------------------------------------------------------------------------------------------------------
//stdformatx--FboPrime Page Standard "Look and Feel" Functions Not Necessary for Day Scheduling View
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
require_once("stdformat.inc");
//
//--------------------------------------------------------------------------------------------------------------
//This file contains functions that emit standard elements of FboPrime pages and otherwise give the set of
//pages a consistent (and hopefully easy to modify) look and feel.
//--------------------------------------------------------------------------------------------------------------
//Emits the standard page when the user does not have adequate permissions to access the page.
//
function STDFORMAT_inadequatepermissionspage($pagetitle, $sddt, $sdtim)
   {
   HTMLFORMAT_echo_push_nl("<html>");
      HTMLFORMAT_echo_push_nl("<head>");
         HTMLFORMAT_echo_noop_nl("<title>FBO-Prime Inadequate User Permissions</title>");
      HTMLFORMAT_echo_pull_nl("</head>");
      HTMLFORMAT_echo_push_nl("<body>");
         HTMLFORMAT_echo_push_nl("<table width=\"100%\" border=\"1\" cellspacing=\"0\" cellpadding=\"4\" rules=\"none\">");
            HTMLFORMAT_echo_push_nl("<tr>");
               HTMLFORMAT_echo_push_nl("<td align=\"center\">");
                  HTMLFORMAT_echo_noop_nl("<title>FBO-Prime Inadequate User Permissions</title>");
                     HTMLFORMAT_echo_noop_nl("<br><br><br><br><br><p>You do not have adequate user permissions to use the ");
                     HTMLFORMAT_echo_noop_nl($pagetitle . " page.</p>");

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
//Emits the standard page when the client page requires that a user be logged in but there is no user logged in.
//
function STDFORMAT_underconstructionpage($desc_in, $curuserinfo_in, $cursessioninfo_in, $sddt_in, $sdtim_in)
   {
   HTMLFORMAT_echo_push_nl("<html>");
      HTMLFORMAT_echo_push_nl("<head>");
         HTMLFORMAT_echo_noop_nl("<title>FBO-Prime Page Under Construction</title>");
      HTMLFORMAT_echo_pull_nl("</head>");
      HTMLFORMAT_echo_push_nl("<body>");
         HTMLFORMAT_echo_push_nl("<table width=\"100%\" border=\"1\" cellspacing=\"0\" cellpadding=\"4\" rules=\"none\">");
            HTMLFORMAT_echo_push_nl("<tr>");
               HTMLFORMAT_echo_push_nl("<td align=\"center\">");
                  HTMLFORMAT_echo_noop_nl("<br><br><br><br><br><p>This page (" . $desc_in . ") is under construction.</p>");
                  HTMLFORMAT_echo_noop_nl("<p>Please click ");

                  $baseurl = "index.php";
                  if (($sddt_in === FALSE) && ($sdtim_in === FALSE))
                     {
                     //No adjustment to the base URL needed.
                     }
                  else if (($sddt_in === FALSE) && ($sdtim_in !== FALSE))
                     {
                     $baseurl = $baseurl . "?sdtim=" . $sdtim_in;
                     }
                  else if (($sddt_in !== FALSE) && ($sdtim_in === FALSE))
                     {
                     $baseurl = $baseurl . "?sddt=" . $sddt_in;
                     }
                  else
                     {
                     $baseurl = $baseurl . "?sddt=" . $sddt_in . "&sdtim=" . $sdtim_in;
                     }
                  HTMLFORMAT_echo_noop_nl("<a href=\"" . $baseurl . "\">here</a> to return to the day view scheduler.</p><br><br><br><br><br>");
               HTMLFORMAT_echo_pull_nl("</td>");
            HTMLFORMAT_echo_pull_nl("</tr>");
         HTMLFORMAT_echo_pull_nl("</table>");
         STDFORMAT_stdfooter_tabular($curuserinfo_in, $sddt_in, $sdtim_in);
       HTMLFORMAT_echo_pull_nl("</body>");
   HTMLFORMAT_echo_pull_nl("</html>");
   }
//
//--------------------------------------------------------------------------------------------------------------
//End of $RCSfile: stdformatx.inc,v $.
//--------------------------------------------------------------------------------------------------------------
?>
