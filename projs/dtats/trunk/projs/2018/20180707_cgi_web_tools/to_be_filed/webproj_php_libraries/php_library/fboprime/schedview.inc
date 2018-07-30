<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/schedview.inc 205 2018-07-15 19:00:51Z dashley $
//********************************************************************************
//schedview.inc--FboPrime Scheduling View Functions
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
//This file contains functions that assist in the scheduling views (daily,
//weekly, monthly) and may be common between them.
//--------------------------------------------------------------------------------
require_once("menu.inc");
require_once("rscs.inc");
require_once("stime.inc");
require_once("t4.inc");
//
//--------------------------------------------------------------------------------
//Emits the standard login form, or else a welcome/login message if a user is
//logged in.  This may appear on more than one scheduling view.
//
//Parameters:
//   userinfo      :  FALSE if no user is logged in, otherwise an associative
//                    array with the user's information from the MySQL database.
//   dt8           :  Date, if specified to page.
//   t4in          :  Time is specified to page.
//   prevloginfail :  TRUE if login has failed so that 
//
function SCHEDVIEW_login_form_echo($userinfo, $dt8in, $t4in, $prevloginfail)
   {
   if ($userinfo === FALSE)
      {
      HTMLFORMAT_echo_push_nl("<form name=\"loginform\" method=\"post\" action=\"index.php\">");
         HTMLFORMAT_echo_push_nl("<table border=\"0\" cellspacing=\"0\" cellpadding=\"4\" bgcolor=\"#"
                                 . CONFIG_SCHED_COLOR_BACKGROUND . "\">");
            HTMLFORMAT_echo_push_nl("<tr>");
               HTMLFORMAT_echo_noop_nl("<td align=\"center\">Username</td>");
            HTMLFORMAT_echo_pull_nl("</tr>");
            HTMLFORMAT_echo_push_nl("<tr>");
               HTMLFORMAT_echo_noop_nl("<td align=\"center\"><input type=\"text\" name=\"authuserid\" size=\"15\" maxlength=\"20\"></td>");
            HTMLFORMAT_echo_pull_nl("</tr>");
            HTMLFORMAT_echo_push_nl("<tr>");
               HTMLFORMAT_echo_noop_nl("<td align=\"center\">Password</td>");
            HTMLFORMAT_echo_pull_nl("</tr>");
            HTMLFORMAT_echo_push_nl("<tr>");
               HTMLFORMAT_echo_noop_nl("<td align=\"center\"><input type=\"password\" name=\"authuserpasswd\" size=\"16\" maxlength=\"20\"></td>");
            HTMLFORMAT_echo_pull_nl("</tr>");
            HTMLFORMAT_echo_push_nl("<tr valign=\"bottom\">");
               HTMLFORMAT_echo_noop_nl("<td height=\"80%\" align=\"center\"><input align=\"BOTTOM\" type=\"submit\" name=\"submit\" value=\"Login\"></td>");
            HTMLFORMAT_echo_pull_nl("</tr>");
         HTMLFORMAT_echo_pull_nl("</table>");
      if ($dt8in !== FALSE)
         {
         HTMLFORMAT_echo_noop_nl("<input type=\"hidden\" name=\"sddt\" value=\"" . $dt8in . "\">");
         }
      if ($t4in !== FALSE)
         {
         HTMLFORMAT_echo_noop_nl("<input type=\"hidden\" name=\"sdtim\" value=\"" . $t4in . "\">");
         }
      HTMLFORMAT_echo_pull_nl("</form>");
      if ($prevloginfail)
         {
         HTMLFORMAT_echo_push_nl("<p>");
            if (($dt8in === FALSE) && ($t4in === FALSE))
               {
               $baseurl = "userloginrecovery.php";
               }
            else if (($dt8in === FALSE) && ($t4in !== FALSE))
               {
               $baseurl = "userloginrecovery.php?sdtim=" . $t4in;
               }
            else if (($dt8in !== FALSE) && ($t4in === FALSE))
               {
               $baseurl = "userloginrecovery.php?sddt=" . $dt8in;
               }
            else
               {
               $baseurl = "userloginrecovery.php?sddt=" . $dt8in . "&sdtim=" . $t4in;
               }

            HTMLFORMAT_echo_noop_nl("&nbsp;<a href=\"" . $baseurl . "\">Trouble logging in?</a>&nbsp;<br><br>");
         HTMLFORMAT_echo_pull_nl("</p>");
         }
      }
   }
//
//--------------------------------------------------------------------------------
//Displays a mini-calendar at the top of the dayview screen.
//
//Parameters:
//   $disp_year       :  The calendar to create year.
//   $disp_month      :  The calendar to create month.
//   $schedviewyear   :  The year of the date currently being displayed on the
//                       scheduler.
//   $schedviewmonth  :  The month of the date currently being displayed on the
//                       scheduler.
//   $schedviewday    :  The day of the date currently being displayed on the
//                       scheduler.
//
function SCHEDVIEW_dayview_calendar($disp_year, $disp_month, $schedviewyear, $schedviewmonth, $schedviewday)
   {
   global $GLOBAL_stime_year;
   global $GLOBAL_stime_month;
   global $GLOBAL_stime_day;

   //echo " Display year is : " . $disp_year . " ";

   //Figure out the name of the month (as opposed to number).
   $month_string = DATEFUNC_string_month_long($disp_month);

   //Figure out what day of the week the first day of this month occurs on.
   $dow_first = DATEFUNC_intdayofweek_intdate($disp_year, $disp_month, 1);
   
   //Figure out how many days are in this month.
   $ndays = DATEFUNC_year_month_days($disp_year, $disp_month);

   HTMLFORMAT_echo_push_nl("<table border=\"0\" frame=\"void\" cellspacing=\"2\">");
      HTMLFORMAT_echo_push_nl("<tr>");

         //Display the banner containing the month name and the year.
         //
         HTMLFORMAT_echo_noop_nl("<td colspan=\"7\" align=\"center\" bgcolor=\"#"
                                 . CONFIG_GLOBAL_BANNERBAR_MINI_A . "\"><b>"
                                 . $month_string . " " . $disp_year . "</b></td>");

      HTMLFORMAT_echo_pull_nl("</tr>");

         //Display the table containing the days of the week, Sun - Sat.
         HTMLFORMAT_echo_push_nl("<tr>");
            HTMLFORMAT_echo_noop_nl("<td align=\"center\" bgcolor=\"#" . CONFIG_GLOBAL_BANNERBAR_MINI_B . "\">S</td>");
            HTMLFORMAT_echo_noop_nl("<td align=\"center\" bgcolor=\"#" . CONFIG_GLOBAL_BANNERBAR_MINI_B . "\">M</td>");
            HTMLFORMAT_echo_noop_nl("<td align=\"center\" bgcolor=\"#" . CONFIG_GLOBAL_BANNERBAR_MINI_B . "\">T</td>");
            HTMLFORMAT_echo_noop_nl("<td align=\"center\" bgcolor=\"#" . CONFIG_GLOBAL_BANNERBAR_MINI_B . "\">W</td>");
            HTMLFORMAT_echo_noop_nl("<td align=\"center\" bgcolor=\"#" . CONFIG_GLOBAL_BANNERBAR_MINI_B . "\">T</td>");
            HTMLFORMAT_echo_noop_nl("<td align=\"center\" bgcolor=\"#" . CONFIG_GLOBAL_BANNERBAR_MINI_B . "\">F</td>");
            HTMLFORMAT_echo_noop_nl("<td align=\"center\" bgcolor=\"#" . CONFIG_GLOBAL_BANNERBAR_MINI_B . "\">S</td>");
         HTMLFORMAT_echo_pull_nl("</tr>");

         //Start up a table row.
         HTMLFORMAT_echo_push_nl("<tr>");

            //Put in the spacers that occur before the first day of the month.
            for ($i=0; $i<$dow_first; $i++)
               {
               HTMLFORMAT_echo_noop_nl("<td align=\"right\">&nbsp;</td>");
               }

            //Write the days of the month.
            for ($i=1; $i<=$ndays; $i++)
               {
               //Calculate Boolean variables to record if the day whose day number is being written is
               //the current calendar day and/or the day currently being viewed in the scheduler.
               //
               if (($disp_year == $schedviewyear) && ($disp_month == $schedviewmonth) && ($i == $schedviewday))
                 $is_sched_view_day = TRUE;
               else
                 $is_sched_view_day = FALSE;
               //
               if (($disp_year == $GLOBAL_stime_year) && ($disp_month == $GLOBAL_stime_month) && ($i == $GLOBAL_stime_day))
                 $is_cal_day = TRUE;
               else
                 $is_cal_day = FALSE;
              

               if ($is_sched_view_day && $is_cal_day)
                  {
                  //The day whose calendar number is being written is the same as the day being
                  //displayed in the scheduler, and the same as today's date.
                  //
                  HTMLFORMAT_echo_noop_nl("<td bgcolor=\"#" . CONFIG_SCHED_COLOR_MINICAL_CURVIEW . "\" align=\"right\"><a href=\"index.php?sddt=" 
                                           .
                                           sprintf("%04d", $disp_year)
                                           .
                                           sprintf("%02d", $disp_month)
                                           .
                                           sprintf("%02d", $i)
                                           .
                                           "\">" 
                                           .
                                           "<font color=\"#000000\">" . sprintf("%d", $i) . "</font>" . "</a></td>");
                  }
               else if ($is_sched_view_day)
                  {
                  //The day whose calendar number is being written is the same as the day being
                  //displayed in the scheduler.
                  //
                  HTMLFORMAT_echo_noop_nl("<td bgcolor=\"#" . CONFIG_SCHED_COLOR_MINICAL_VIEWONLY . "\" align=\"right\"><a href=\"index.php?sddt=" 
                                           .
                                           sprintf("%04d", $disp_year)
                                           .
                                           sprintf("%02d", $disp_month)
                                           .
                                           sprintf("%02d", $i)
                                           .
                                           "\">" 
                                           .
                                           "<font color=\"#000000\">" . sprintf("%d", $i) . "</font>" . "</a></td>");
                  }
               else if ($is_cal_day)
                  {
                  //The day being displayed is today.
                  //
                  HTMLFORMAT_echo_noop_nl("<td bgcolor=\"#" . CONFIG_SCHED_COLOR_MINICAL_CURONLY . "\" align=\"right\"><a href=\"index.php?sddt=" 
                                           .
                                           sprintf("%04d", $disp_year)
                                           .
                                           sprintf("%02d", $disp_month)
                                           .
                                           sprintf("%02d", $i)
                                           .
                                           "\">" 
                                           .
                                           "<font color=\"#000000\">" . sprintf("%d", $i) . "</font>" . "</a></td>");
                  }
               else
                  {
                  HTMLFORMAT_echo_noop_nl("<td align=\"right\"><a href=\"index.php?sddt=" 
                                           .
                                           sprintf("%04d", $disp_year)
                                           .
                                           sprintf("%02d", $disp_month)
                                           .
                                           sprintf("%02d", $i)
                                           .
                                           "\">" 
                                           .
                                           sprintf("%d", $i) . "</a></td>");
                  }

               //We end a row and start a new one under this set of circumstances.
               //   a)It is not the last day of the month we just printed.
               //   b)The day of the week on which the month starts plus the day we
               //     just printed mod 7 is zero.
               if ($i != $ndays)
                  {
                  if ((($i + $dow_first) % 7) == 0)
                     {
                     HTMLFORMAT_echo_pull_nl("</tr>");
                     HTMLFORMAT_echo_push_nl("<tr>");
                     }
                  }
               }
            
            //Round out the final row that contains calendar days.
            $i = $ndays + $dow_first;
            while (($i % 7) != 0)
               {
               HTMLFORMAT_echo_noop_nl("<td align=\"right\">&nbsp;</td>");
               $i++;
               }
            
         //Terminate the final row of calendar days.
         HTMLFORMAT_echo_pull_nl("</tr>");

         //Output bottom spacer rows so that every month created has six
         //rows of days.  In general, the number of rows created by days
         //alone is:
         //
         //   ( month_start_dayofweek + days_in_month + 6 ) div 7
         //
         //The shortest case is a February with 28 days where Feb 1 falls
         //on a Sunday, i.e.
         //
         //   (0 + 28 + 6) / 7 = 4
         //
         //Many months require six rows to display.  This is the worst case.
         //So, round it out to six rows.
         $rows_due_to_cal_days = (int)(( $dow_first + $ndays + 6 ) / 7);

         for ($i = $rows_due_to_cal_days + 1; $i <= 6; $i++)
            {
            HTMLFORMAT_echo_push_nl("<tr>");
               HTMLFORMAT_echo_noop_nl("<td align=\"right\">&nbsp;</td>");
               HTMLFORMAT_echo_noop_nl("<td align=\"right\">&nbsp;</td>");
               HTMLFORMAT_echo_noop_nl("<td align=\"right\">&nbsp;</td>");
               HTMLFORMAT_echo_noop_nl("<td align=\"right\">&nbsp;</td>");
               HTMLFORMAT_echo_noop_nl("<td align=\"right\">&nbsp;</td>");
               HTMLFORMAT_echo_noop_nl("<td align=\"right\">&nbsp;</td>");
               HTMLFORMAT_echo_noop_nl("<td align=\"right\">&nbsp;</td>");
            HTMLFORMAT_echo_pull_nl("</tr>");
            }

      //HTMLFORMAT_echo_pull_nl("</tr>");
   HTMLFORMAT_echo_pull_nl("</table>");
   }
// 
//--------------------------------------------------------------------------------
//Emits a temporal navigation bar.
//
function SCHEDVIEW_temporal_navigation_bar(
                                          $userinfo,
                                          $dateyear, $datemonth, $dateday,
                                          $timehour, $timemin,
                                          $diff_time_perm_array,
                                          $panel
                                          )
   {
   global $GLOBAL_stime_year;
   global $GLOBAL_stime_month;
   global $GLOBAL_stime_day;
   global $GLOBAL_stime_hour;
   global $GLOBAL_stime_minute;

   global $CONFIG_SCHED_DAY_PANELS;

   //Table header emitted unconditionally.
   HTMLFORMAT_echo_push_nl("<table width=\"100%\" border=\"1\" cellspacing=\"0\" cellpadding=\"4\" rules=\"rows\">");

      //Table row emitted unconditionally.
      HTMLFORMAT_echo_push_nl("<tr>");

         //"Go To" text emitted unconditionally.
         HTMLFORMAT_echo_push_nl("<td align=\"center\">");
         HTMLFORMAT_echo_noop_nl("<b>Go To:</b>");
         HTMLFORMAT_echo_pull_nl("</td>");

         //-1 month text.
         //--------------
         //The previous month should be displayed unless we are already at the lower limit
         //of navigation.
         //
         DATEFUNC_offset_month($dateyear, $datemonth, -1, $prev_month_year, $prev_month_month, $prev_month_result_code);

         if ($diff_time_perm_array[0])
            {
            //We should display the previous month's link.
            //
            HTMLFORMAT_echo_push_nl("<td align=\"center\">");
            //
            //We need to figure out what day of the month to use.  There is the possibility
            //that we are going back to a month with fewer days.
            //
            $prev_month_days_in_month = DATEFUNC_year_month_days($prev_month_year, $prev_month_month);
         
            if ($dateday > $prev_month_days_in_month)
               {
               $prev_month_day = $prev_month_days_in_month;
               }
            else
               {
               $prev_month_day = $dateday;
               }

            HTMLFORMAT_echo_noop_nl("<a href=\"index.php?sddt="
                                    .
                                    sprintf("%04d", $prev_month_year)
                                    .
                                    sprintf("%02d", $prev_month_month)
                                    .
                                    sprintf("%02d", $prev_month_day)
                                    .
                                    "\">-1 month</a>");            
            HTMLFORMAT_echo_pull_nl("</td>");
            }
         else
            {
            HTMLFORMAT_echo_push_nl("<td align=\"center\">");
            HTMLFORMAT_echo_noop_nl(STRFUNC_nbsp_padding("-1 month"));
            HTMLFORMAT_echo_pull_nl("</td>");
            }

         //-1 week text.
         //-------------
         //The previous week should be displayed unless we are already at the lower
         //limit of navigation or viewability.
         //
         if ($diff_time_perm_array[1])
            {
            HTMLFORMAT_echo_push_nl("<td align=\"center\">");

            DATEFUNC_one_week_ago($dateyear, 
                                  $datemonth, 
                                  $dateday, 
                                  $year_oneweekago, 
                                  $month_oneweekago, 
                                  $day_oneweekago);
            HTMLFORMAT_echo_noop_nl("<a href=\"index.php?sddt="
                                    .
                                    sprintf("%04d", $year_oneweekago)
                                    .
                                    sprintf("%02d", $month_oneweekago)
                                    .
                                    sprintf("%02d", $day_oneweekago)
                                    .
                                    "\">-1 week</a>");            
            HTMLFORMAT_echo_pull_nl("</td>");
            }
         else
            {
            HTMLFORMAT_echo_push_nl("<td align=\"center\">");
            HTMLFORMAT_echo_noop_nl(STRFUNC_nbsp_padding("-1 week"));
            HTMLFORMAT_echo_pull_nl("</td>");
            }

         //-1 day text.
         //------------
         //The previous day should be displayed unless we are already at the lower
         //limit or navigation or viewability.
         //
         if ($diff_time_perm_array[2])
            {
            HTMLFORMAT_echo_push_nl("<td align=\"center\">");

            DATEFUNC_one_day_ago($dateyear, 
                                 $datemonth, 
                                 $dateday, 
                                 $year_onedayago, 
                                 $month_onedayago, 
                                 $day_onedayago);
            HTMLFORMAT_echo_noop_nl("<a href=\"index.php?sddt="
                                    .
                                    sprintf("%04d", $year_onedayago)
                                    .
                                    sprintf("%02d", $month_onedayago)
                                    .
                                    sprintf("%02d", $day_onedayago)
                                    .
                                    "\">-1 day</a>");            
            HTMLFORMAT_echo_pull_nl("</td>");
            }
         else
            {
            HTMLFORMAT_echo_push_nl("<td align=\"center\">");
            HTMLFORMAT_echo_noop_nl(STRFUNC_nbsp_padding("-1 day"));
            HTMLFORMAT_echo_pull_nl("</td>");
            }

         //Previous Panel
         //--------------
         //Previous panel that can be displayed.  A "panel" is a view of a certain
         //set of hours.
         //
         if ($diff_time_perm_array[3])
            {
            //We can display the link.  Calculate the previous panel.
            if ($panel > 0)
               {
               //Simplest case:  just back off the panel.
               $prevpanel       = $panel - 1;
               $prevpanel_year  = $dateyear;
               $prevpanel_month = $datemonth;
               $prevpanel_day   = $dateday;
               }
            else
               {
               //The panel is the first one.  To back off, we need to change
               //the date backwards.
               $prevpanel       = ((int)(count($CONFIG_SCHED_DAY_PANELS) / 2)) - 1;
               DATEFUNC_one_day_ago($dateyear, 
                                    $datemonth, 
                                    $dateday, 
                                    $prevpanel_year, 
                                    $prevpanel_month, 
                                    $prevpanel_day);
               }

            //We need to figure out for the panel what a good time to choose is
            //that will guarantee that this panel is the right one to display.
            $sdtim_string_prev_panel = TOD_panel_center_t4($prevpanel);

            //Form the URL reference.
            HTMLFORMAT_echo_push_nl("<td align=\"center\">");
            HTMLFORMAT_echo_noop_nl("<a href=\"index.php?sddt=" 
                                    .
                                    sprintf("%04d", $prevpanel_year)
                                    .       
                                    sprintf("%02d", $prevpanel_month)
                                    .       
                                    sprintf("%02d", $prevpanel_day)
                                    .
                                    "&amp;sdtim="
                                    .
                                    $sdtim_string_prev_panel
                                    .
                                    "\">-hours</a>");
            HTMLFORMAT_echo_pull_nl("</td>");
            }
         else
            {
            //We cannot display a link to the previous because it would violate
            //calendaring or viewability rules.  Just use a placeholder.
            //
            HTMLFORMAT_echo_push_nl("<td align=\"center\">");
            HTMLFORMAT_echo_noop_nl(STRFUNC_nbsp_padding("-hours"));
            HTMLFORMAT_echo_pull_nl("</td>");
            }


         //Today, now text.
         HTMLFORMAT_echo_push_nl("<td align=\"center\">");
         HTMLFORMAT_echo_noop_nl("<a href=\"index.php?todaynow=1\">Today, Now</a>");
         HTMLFORMAT_echo_pull_nl("</td>");


         //Next Panel
         //----------
         //Next panel that can be displayed.  A "panel" is a view of a certain
         //set of hours.
         //
         if ($diff_time_perm_array[4])
            {
            $npanels = ((int)(count($CONFIG_SCHED_DAY_PANELS) / 2));

            //We can display the link.  Calculate the next panel.
            if ($panel < ($npanels - 1))
               {
               //Simplest case:  just add to the panel.
               $nextpanel       = $panel + 1;
               $nextpanel_year  = $dateyear;
               $nextpanel_month = $datemonth;
               $nextpanel_day   = $dateday;
               }
            else
               {
               //The panel is the last one.  To add, we need to change
               //the date forwards.
               $nextpanel       = 0;
               DATEFUNC_one_day_future($dateyear, 
                                       $datemonth, 
                                       $dateday, 
                                       $nextpanel_year, 
                                       $nextpanel_month, 
                                       $nextpanel_day);
               }

            //We need to figure out for the panel what a good time to choose is
            //that will guarantee that this panel is the right one to display.
            $sdtim_string_next_panel = TOD_panel_center_t4($nextpanel);

            //Form the URL reference.
            HTMLFORMAT_echo_push_nl("<td align=\"center\">");
            HTMLFORMAT_echo_noop_nl("<a href=\"index.php?sddt=" 
                                    .
                                    sprintf("%04d", $nextpanel_year)
                                    .       
                                    sprintf("%02d", $nextpanel_month)
                                    .       
                                    sprintf("%02d", $nextpanel_day)
                                    .
                                    "&amp;sdtim="
                                    .
                                    $sdtim_string_next_panel
                                    .
                                    "\">+hours</a>");
            HTMLFORMAT_echo_pull_nl("</td>");
            }
         else
            {
            //We cannot display a link to the previous because it would violate
            //calendaring or viewability rules.  Just use a placeholder.
            //
            HTMLFORMAT_echo_push_nl("<td align=\"center\">");
            HTMLFORMAT_echo_noop_nl(STRFUNC_nbsp_padding("+hours"));
            HTMLFORMAT_echo_pull_nl("</td>");
            }


         //+1 day text.
         //------------
         //The next day should be displayed unless we are already at the upper
         //limit of navigation or viewability.
         //
         if ($diff_time_perm_array[5])
            {
            HTMLFORMAT_echo_push_nl("<td align=\"center\">");

            DATEFUNC_one_day_future($dateyear, 
                                    $datemonth, 
                                    $dateday, 
                                    $year_onedayfuture, 
                                    $month_onedayfuture, 
                                    $day_onedayfuture);
            HTMLFORMAT_echo_noop_nl("<a href=\"index.php?sddt="
                                    .
                                    sprintf("%04d", $year_onedayfuture)
                                    .
                                    sprintf("%02d", $month_onedayfuture)
                                    .
                                    sprintf("%02d", $day_onedayfuture)
                                    .
                                    "\">+1 day</a>");            
            HTMLFORMAT_echo_pull_nl("</td>");
            }
         else
            {
            HTMLFORMAT_echo_push_nl("<td align=\"center\">");
            HTMLFORMAT_echo_noop_nl(STRFUNC_nbsp_padding("+1 day"));
            HTMLFORMAT_echo_pull_nl("</td>");
            }

         //+1 week text.
         //-------------
         //The next week should be displayed unless we are already at the upper
         //limit of navigation or viewability.
         //
         if ($diff_time_perm_array[6])
            {
            HTMLFORMAT_echo_push_nl("<td align=\"center\">");

            DATEFUNC_one_week_future($dateyear, 
                                     $datemonth, 
                                     $dateday, 
                                     $year_oneweekfuture, 
                                     $month_oneweekfuture, 
                                     $day_oneweekfuture);
            HTMLFORMAT_echo_noop_nl("<a href=\"index.php?sddt="
                                    .
                                    sprintf("%04d", $year_oneweekfuture)
                                    .
                                    sprintf("%02d", $month_oneweekfuture)
                                    .
                                    sprintf("%02d", $day_oneweekfuture)
                                    .
                                    "\">+1 week</a>");            
            HTMLFORMAT_echo_pull_nl("</td>");
            }
         else
            {
            HTMLFORMAT_echo_push_nl("<td align=\"center\">");
            HTMLFORMAT_echo_noop_nl(STRFUNC_nbsp_padding("+1 week"));
            HTMLFORMAT_echo_pull_nl("</td>");
            }


         //+1 month text.
         //--------------
         //The next month should be displayed unless we are already at the upper limit
         //of navigation.
         //
         DATEFUNC_offset_month($dateyear, $datemonth, 1, $next_month_year, $next_month_month, $next_month_result_code);

         if ($diff_time_perm_array[7])
            {
            //We should display the next month's link.
            //
            HTMLFORMAT_echo_push_nl("<td align=\"center\">");
            //
            //We need to figure out what day of the month to use.  There is the possibility
            //that we are going forward to a month with fewer days.
            //
            $next_month_days_in_month = DATEFUNC_year_month_days($next_month_year, $next_month_month);
         
            if ($dateday > $next_month_days_in_month)
               {
               $next_month_day = $next_month_days_in_month;
               }
            else
               {
               $next_month_day = $dateday;
               }

            HTMLFORMAT_echo_noop_nl("<a href=\"index.php?sddt="
                                    .
                                    sprintf("%04d", $next_month_year)
                                    .
                                    sprintf("%02d", $next_month_month)
                                    .
                                    sprintf("%02d", $next_month_day)
                                    .
                                    "\">+1 month</a>");            
            HTMLFORMAT_echo_pull_nl("</td>");
            }
         else
            {
            HTMLFORMAT_echo_push_nl("<td align=\"center\">");
            HTMLFORMAT_echo_noop_nl(STRFUNC_nbsp_padding("+1 month"));
            HTMLFORMAT_echo_pull_nl("</td>");
            }


         //Padding to balance the Go To text.
         HTMLFORMAT_echo_push_nl("<td align=\"center\">");
         HTMLFORMAT_echo_noop_nl("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;");
         HTMLFORMAT_echo_pull_nl("</td>");

      HTMLFORMAT_echo_pull_nl("</tr>");
      HTMLFORMAT_echo_push_nl("<tr>");

         //Date Displayed information.
         HTMLFORMAT_echo_noop_nl("<td colspan=\"11\" align=\"center\"><b>Flight Schedule for " 
                                 . 
                                 DATEFUNC_stdlongdate_w_dow( $dateyear, $datemonth, $dateday)
                                 . "</b></td>");
     
      HTMLFORMAT_echo_pull_nl("</tr>");

   //Table footer emitted unconditionally.
   HTMLFORMAT_echo_pull_nl("</table>");
   }
//--------------------------------------------------------------------------------
//Emits the default view page navigation bar.
//
function SCHEDVIEW_dayview_page_navigation_bar($userinfo, $sessioninfo, $dt8in, $t4in)
   {
   //Grab the menu entries.
   if ($sessioninfo === FALSE)
      $menu_choices = MENU_menu_gen($userinfo, 0, $dt8in, $t4in, "index.php");
   else
      $menu_choices = MENU_menu_gen($userinfo, $sessioninfo["menulvl"], $dt8in, $t4in, "index.php");

   $n = count($menu_choices);
 
   for ($i=0; $i<$n; $i+=3)
      {
      if ($menu_choices[$i] == "H")
         {
         HTMLFORMAT_echo_noop_nl("&nbsp;&nbsp;<b>" . $menu_choices[$i+1] . "</b>&nbsp;&nbsp;<br>");
         }
      else
         {
         HTMLFORMAT_echo_noop_nl("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href=\"" 
                                 . $menu_choices[$i+2] . "\">" . $menu_choices[$i+1] . "</a>&nbsp;&nbsp;<br>");
         }
      }
   }
//
//
//----------------------------------------------------------------------------------------------------
//Given the start hour and end-hour for a panel, calculates the number of time columns involved.
//For example, if the start hour is 8 and the end hour is 10, the columns are:
//  a) 8:00 -  8:30
//  b) 8:30 -  9:00
//  c) 9:00 -  9:30
//  d) 9:30 - 10:00
//  e)10:00 - 10:30
//  f)10:30 - 11:00
//
function SCHEDVIEW_panel_n_time_columns($start_hour_in, $end_hour_in)
   {
   $rv = ($end_hour_in - $start_hour_in + 1) * 2;

   return($rv);
   }
//
//----------------------------------------------------------------------------------------------------
//Decorates a list of reservation information with additional fields that help with
//quickness.  The fields are:
//
//   emitted
//      Set to 0.  Will be used later as the reservation is displayed.
//
//   finsttimefloor
//      The reservation stime start (for a flight instructor), or the left panel time if
//      the time is clipped.
//
//   finsttimefloorint
//      An integer corresponding to the first half-hour time slot of the appointment (clipped).
//      Zero if not applicable.
//
//   finsttimeceiling
//      The reservation stime end (for a flight instructor), or the right panel time if
//      the time is clipped.
//
//   finsttimeceilingint
//      An integer corresponding to one past the last half-hour time slot of the appointment (clipped).
//      Zero if not applicable.  This may be 48.
//
//   finsttimeleftclip
//      1 if the displayed flight instructor appt left time was clipped on the left, or 0
//      if not.
//
//   finsttimerightclip
//      1 if the displayed flight instructor appt right time was clipped on the right, or 0
//      if not.
//
//   acftsimtimefloor
//      The reservation stime start (for an aircraft or simulator), or the left panel time if
//      the time is clipped.
//   
//   acftsimtimefloorint
//      An integer corresponding to the first half-hour time slot of the appointment (clipped).
//      Zero if not applicable.
//
//   acftsimtimeceiling
//      The reservation stime end (for an aircraft or simulator), or the right panel time if
//      the time is clipped.
//
//   acftsimtimeceilingint
//      An integer corresponding to one past the last half-hour time slot of the appointment (clipped).
//      Zero if not applicable.
//
//   acftsimtimeleftclip
//      1 if the displayed aircraft or simulator appt left time was clipped on the left, or 0
//      if not.
//
//   acftsimttimerightclip
//      1 if the displayed aircraft or simulator right time was clipped on the right, or 0
//      if not.
//
function SCHEDVIEW_resv_list_decorate(&$flight_inst_data_array, $panel_left_stime, $panel_right_stime)
   {
   //Return if there is an empty array.
   //
   if ($flight_inst_data_array === FALSE)
      return;

   $n = count($flight_inst_data_array);
   for ($i=0; $i<$n; $i++)
      {
      //---------------------------------------------------------------------------------
      //Emitted -- whether the reservation has been output yet.
      //---------------------------------------------------------------------------------
      $flight_inst_data_array[$i]["emitted"]                = 0;
      //
      //---------------------------------------------------------------------------------
      //Flight instructor left.
      //---------------------------------------------------------------------------------
      if (strlen($flight_inst_data_array[$i]["finsttimestart"]))
         {
         //Do the clipping, if applicable.
         if (strcmp($flight_inst_data_array[$i]["finsttimestart"], $panel_left_stime) < 0)
            {
            //Clipping is appropriate.
            $flight_inst_data_array[$i]["finsttimefloor"]    = $panel_left_stime;
            $flight_inst_data_array[$i]["finsttimefloorint"] = STIME_T4_lb_int($panel_left_stime);
            $flight_inst_data_array[$i]["finsttimeleftclip"] = 1;
            }
         else
            {
            //Clipping is not appropriate.
            $flight_inst_data_array[$i]["finsttimefloor"]    = $flight_inst_data_array[$i]["finsttimestart"];
            $flight_inst_data_array[$i]["finsttimefloorint"] = STIME_T4_lb_int($flight_inst_data_array[$i]["finsttimestart"]);
            $flight_inst_data_array[$i]["finsttimeleftclip"] = 0;
            }
         }
      else
         {
         //Floor and floor int are meaningless.
         $flight_inst_data_array[$i]["finsttimefloor"]           = "";
         $flight_inst_data_array[$i]["finsttimefloorint"]        =  0;
         $flight_inst_data_array[$i]["finsttimeleftclip"]        =  0;
         }

      //---------------------------------------------------------------------------------
      //Flight instructor right.
      //---------------------------------------------------------------------------------
      if (strlen($flight_inst_data_array[$i]["finsttimeend"]))
         {
         //Do the clipping, if applicable.
         if (strcmp($flight_inst_data_array[$i]["finsttimeend"], $panel_right_stime) > 0)
            {
            //Clipping is appropriate.
            $flight_inst_data_array[$i]["finsttimeceiling"]    = $panel_right_stime;
            $flight_inst_data_array[$i]["finsttimeceilingint"] = STIME_T4_lb_int($panel_right_stime);

            //Adjust for a clip to midnight.
            if ($flight_inst_data_array[$i]["finsttimeceilingint"] == 0)
               $flight_inst_data_array[$i]["finsttimeceilingint"] = 48;

            $flight_inst_data_array[$i]["finsttimerightclip"]  = 1;
            }
         else
            {
            //Clipping is not appropriate.
            $flight_inst_data_array[$i]["finsttimeceiling"]    = $flight_inst_data_array[$i]["finsttimeend"];
            $flight_inst_data_array[$i]["finsttimeceilingint"] = STIME_T4_lb_int($flight_inst_data_array[$i]["finsttimeend"]);

            //Adjust for a reservation that ends at midnight.
            if ($flight_inst_data_array[$i]["finsttimeceilingint"] == 0)
               $flight_inst_data_array[$i]["finsttimeceilingint"] = 48;

            $flight_inst_data_array[$i]["finsttimerightclip"]  = 0;
            }
         }
      else
         {
         //Floor and floor int are meaningless.
         $flight_inst_data_array[$i]["finsttimeceiling"]         = "";
         $flight_inst_data_array[$i]["finsttimeceilingint"]      =  0;
         $flight_inst_data_array[$i]["finsttimerightclip"]       =  0;
         }

      //---------------------------------------------------------------------------------
      //Aircraft/simulator left.
      //---------------------------------------------------------------------------------
      if (strlen($flight_inst_data_array[$i]["acftsimtimestart"]))
         {
         //Do the clipping, if applicable.
         if (strcmp($flight_inst_data_array[$i]["acftsimtimestart"], $panel_left_stime) < 0)
            {
            //Clipping is appropriate.
            $flight_inst_data_array[$i]["acftsimtimefloor"]    = $panel_left_stime;
            $flight_inst_data_array[$i]["acftsimtimefloorint"] = STIME_T4_lb_int($panel_left_stime);
            $flight_inst_data_array[$i]["acftsimtimeleftclip"] = 1;
            }
         else
            {
            //Clipping is not appropriate.
            $flight_inst_data_array[$i]["acftsimtimefloor"]    = $flight_inst_data_array[$i]["acftsimtimestart"];
            $flight_inst_data_array[$i]["acftsimtimefloorint"] = STIME_T4_lb_int($flight_inst_data_array[$i]["acftsimtimestart"]);
            $flight_inst_data_array[$i]["acftsimtimeleftclip"] = 0;
            }
         }
      else
         {
         //Floor and floor int are meaningless.
         $flight_inst_data_array[$i]["acftsimtimefloor"]         = "";
         $flight_inst_data_array[$i]["acftsimtimefloorint"]      =  0;
         $flight_inst_data_array[$i]["acftsimtimeleftclip"]      =  0;
         }

      //---------------------------------------------------------------------------------
      //Aircraft/simulator right.
      //---------------------------------------------------------------------------------
      if (strlen($flight_inst_data_array[$i]["acftsimtimeend"]))
         {
         //Do the clipping, if applicable.
         if (strcmp($flight_inst_data_array[$i]["acftsimtimeend"], $panel_right_stime) > 0)
            {
            //Clipping is appropriate.
            $flight_inst_data_array[$i]["acftsimtimeceiling"]    = $panel_right_stime;
            $flight_inst_data_array[$i]["acftsimtimeceilingint"] = STIME_T4_lb_int($panel_right_stime);

            //Adjust for a clip to midnight.
            if ($flight_inst_data_array[$i]["acftsimtimeceilingint"] == 0)
               $flight_inst_data_array[$i]["acftsimtimeceilingint"] = 48;

            $flight_inst_data_array[$i]["acftsimtimerightclip"]  = 1;
            }
         else
            {
            //Clipping is not appropriate.
            $flight_inst_data_array[$i]["acftsimtimeceiling"]    = $flight_inst_data_array[$i]["acftsimtimeend"];
            $flight_inst_data_array[$i]["acftsimtimeceilingint"] = STIME_T4_lb_int($flight_inst_data_array[$i]["acftsimtimeend"]);

            //Adjust for a reservation that ends at midnight.
            if ($flight_inst_data_array[$i]["acftsimtimeceilingint"] == 0)
               $flight_inst_data_array[$i]["acftsimtimeceilingint"] = 48;

            $flight_inst_data_array[$i]["acftsimtimerightclip"]  = 0;
            }
         }
      else
         {
         //Floor and floor int are meaningless.
         $flight_inst_data_array[$i]["acftsimtimeceiling"]       = "";
         $flight_inst_data_array[$i]["acftsimtimeceilingint"]    =  0;
         $flight_inst_data_array[$i]["acftsimtimerightclip"]     =  0;
         }
      }
   }
//
//----------------------------------------------------------------------------------------------------
//Returns TRUE if the reservation passed has time intersection with at least one element of the
//array for the aircraft or simulator time, or FALSE if not.
//
function SCHEDVIEW_resv_finst_array_intersection($array_in, $element_in)
   {
   //echo "<pre>\n----------\nIn Intersection Func\n---------\n";
   //echo "Array in:\n---------";
   //print_r($array_in);
   //echo "\nElement in:\n---------";
   //print_r($element_in);
   //echo "\n----------\n";

   if (($array_in === FALSE) || ($element_in === FALSE))
      {
      //echo "\nReturning FALSE\n---------\n</pre>\n";
      return(FALSE);
      }

   for ($i = 0; $i < count($array_in); $i++)
      {
      if (
            (strcmp($array_in[$i]["finsttimestart"], $element_in["finsttimeend"]) < 0)
            &&
            (strcmp($array_in[$i]["finsttimeend"], $element_in["finsttimestart"]) > 0)
         )
         //echo "\nReturning TRUE\n---------\n</pre>\n";
         return(TRUE);
      }

   //No collision found, return FALSE.
   //echo "\nReturning FALSE\n---------\n</pre>\n";
   return(FALSE);
   }
//----------------------------------------------------------------------------------------------------
//Returns TRUE if the reservation passed has time intersection with at least one element of the
//array for the aircraft or simulator time, or FALSE if not.
//
function SCHEDVIEW_resv_actfsim_array_intersection($array_in, $element_in)
   {
   //echo "<pre>\n----------\nIn Intersection Func\n---------\n";
   //echo "Array in:\n---------";
   //print_r($array_in);
   //echo "\nElement in:\n---------";
   //print_r($element_in);
   //echo "\n----------\n";

   if (($array_in === FALSE) || ($element_in === FALSE))
      {
      //echo "\nReturning FALSE\n---------\n</pre>\n";
      return(FALSE);
      }

   for ($i = 0; $i < count($array_in); $i++)
      {
      if (
            (strcmp($array_in[$i]["acftsimtimestart"], $element_in["acftsimtimeend"]) < 0)
            &&
            (strcmp($array_in[$i]["acftsimtimeend"], $element_in["acftsimtimestart"]) > 0)
         )
         //echo "\nReturning TRUE\n---------\n</pre>\n";
         return(TRUE);
      }

   //No collision found, return FALSE.
   //echo "\nReturning FALSE\n---------\n</pre>\n";
   return(FALSE);
   }
//----------------------------------------------------------------------------------------------------
//Generates HTML lines corresponding to the left resource area description area.  This will generally
//be a single <td> cell with a rowspan potentially > 1.
//
//The returned value is an array of lines.
//
function SCHEDVIEW_do_left_resource_title_area( $userinfo_in,
                                                $rscs_rec_in,
                                                $resv_recs_in,
                                                $panel_low_hour_in,
                                                $panel_high_hour_in,
                                                $resourcecolumnwidth_in,
                                                $schedcolumnwidth_in,
                                                $rowspan_in,
                                               &$queued_html_lines)
   {
   $queued_html_lines[] =   "<td colspan=\"1\" rowspan=\""
                          . $rowspan_in
                          . "\" width=\"" . $resourcecolumnwidth_in . "%\" nowrap bgcolor=\"#"
                          .  CONFIG_SCHED_COLOR_DSMAT_THEAD 
                          .  "\" onClick=\"javascript:window.location='http://www.pageresource.com/jscript/newpage.htm';\" "
                          . "onmouseover=\"javascript:window.status='Comment: "
                          . STRFUNC_js_escape_sglquote_notrunc($rscs_rec_in["longdesc"])
                          . "';\" onmouseout=\"javascript:window.status='';\" "
                          . "title=\""
                          . STRFUNC_html_title_escape_dblquote_notrunc($rscs_rec_in["longdesc"])
                          . "\""
                          . ">";
   $queued_html_lines[] =   "&nbsp;" 
                          . $rscs_rec_in["shortdesc"] 
                          . "&nbsp;";
   $queued_html_lines[] =   "</td>";

   //echo "<pre>\n";
   //echo "In SCHEDVIEW_do_left_resource_title_area() ...\n";
   //print_r($queued_html_lines2);
   //echo "----------------------------\n</pre>\n";
   }
//
//----------------------------------------------------------------------------------------------------
//Does the terminator (white area) bar beneath the last row of banner, active, and/or standby
//reservations.  The item returned is an array of HTML lines.  This function will always produce
//an array of lines, as it is always possible to produce the terminator area.
//
function SCHEDVIEW_form_resource_scheduling_area_terminator_bar( $userinfo_in,
                                                                 $rscs_rec_in,
                                                                 $resv_recs_in,
                                                                 $panel_low_hour_in,
                                                                 $panel_high_hour_in,
                                                                 $resourcecolumnwidth_in,
                                                                 $schedcolumnwidth_in,
                                                                &$sched_right_table_rows,
                                                                &$queued_html_lines)
   {
   for ($i=$panel_low_hour_in * 2; $i<=(($panel_high_hour_in * 2) + 1); $i++)
      {
      $queued_html_lines[] =   "<td align=\"center\" width=\"" 
                             . $schedcolumnwidth_in . "%\" bgcolor=\"#" 
                             . CONFIG_SCHED_COLOR_DSMAT_RIDLE 
                             . "\" onClick=\"window.location='http://www.google.com?testpar=30'\">";
      $queued_html_lines[] =   "&nbsp;";
      $queued_html_lines[] =   "</td>";
      }

   //We've added a full row.
   $sched_right_table_rows++;
   }
//
//----------------------------------------------------------------------------------------------------
//Does the rows corresponding to the banner reservations for a flight instructor.
//
function SCHEDVIEW_form_resource_scheduling_area_finst_banner( $userinfo_in,
                                                               $rscs_rec_in,
                                                               $banner_reservations_in,
                                                               $panel_low_hour_in,
                                                               $panel_high_hour_in,
                                                               $resourcecolumnwidth_in,
                                                               $schedcolumnwidth_in,
                                                               $can_view_banner_reservations_in,
                                                              &$sched_right_table_rows,
                                                              &$queued_html_rows)
   {
   $done = FALSE;
   $grabpoint = 0;
   $panel_low_hour_in_int        =  $panel_low_hour_in       * 2;
   $panel_high_hour_in_int_limit = ($panel_high_hour_in + 1) * 2;

   while (!$done)
      {
      //Due to the loop, need to unset the display set to keep it from accumulating too many
      //elements.
      if (isset($display_set))
         unset($display_set);

      //Grab one element.  This is our trial set to start with.
      $display_set[] = $banner_reservations_in[$grabpoint];

      //Next grabpoint.
      $grabpoint++;

      //Keep on grabbing until there is a set intersection or we're out of things to grab.
      while (
               ($grabpoint < count($banner_reservations_in))
               &&
               (! SCHEDVIEW_resv_finst_array_intersection($display_set, $banner_reservations_in[$grabpoint]))
            )
         {
         $display_set[] = $banner_reservations_in[$grabpoint];
         $grabpoint ++;
         }

      //If we can't go further grabbing, we're done.
      if ($grabpoint >= count($banner_reservations_in))
         $done = TRUE;

      //Display the set that was collected for debugging, if necessary.
      //echo "<pre>\n----------\nDisplay Set\n----------\n";
      //print_r($display_set);
      //echo "\n--------\n";

      //Our display set now contains a set of records to display.  We know there is at least one,
      //we know the times don't overlap, and we know that these are in ascending order of start time 
      //(due to the SQL query).  Therefore, we can proceed in order.
      $cur_output_time_int = $panel_low_hour_in_int;
      $cur_display_record  = 0;
      //$panel_high_hour_in_int_limit = ($panel_high_hour_in + 1) * 2;

      while ($cur_display_record < count($display_set))
         {
         //Space out the blank cells until the first reservation or next reservation.
         while($cur_output_time_int < $display_set[$cur_display_record]["finsttimefloorint"])
            {
            $html_lines[] = "<td>&nbsp;</td>";
            $cur_output_time_int ++;
            }

         //Get the text that should be displayed for the reservation.
         if ($userinfo_in === FALSE)
            {
            //echo " Clause 1 ";
            $box_string = "&nbsp;";
            }
         else
            {
            //Try to get the user name.
            //
            //echo "\n<pre>\n";
            //print_r($display_set[$cur_display_record]);
            //print_r($display_set[$cur_display_record]["useridx"]);
            //echo "\n</pre>\n";

            if ($display_set[$cur_display_record]["useridx"] > 0)
               {
               $temp_user_info = USRS_retrieve_by_idx($display_set[$cur_display_record]["useridx"]);
               if ($temp_user_info === FALSE)
                  {
                  //echo " Clause 2 ";
                  $box_string = "&nbsp;";
                  }
               else
                  {
                  //echo " Clause 3 ";
                  $box_string = $temp_user_info["lname"] 
                                . 
                                " (" 
                                . 
                                (string)($display_set[$cur_display_record]["idx"]) 
                                .
                                ")";
                  }
               }
            else
               {
               //echo " Clause 4 ";
               $box_string = "&nbsp;";
               }
            }

         //Spit the reservation.
         $html_lines[] =   "<td colspan=\""
                         . ($display_set[$cur_display_record]["finsttimeceilingint"] - $display_set[$cur_display_record]["finsttimefloorint"])
                         . "\" bgcolor=\""
                         . CONFIG_SCHED_COLOR_DSMAT_RBANN
                         . "\" align=\"center\">"
                         . $box_string
                         . "</td>";

         //This takes the time forward.
         $cur_output_time_int = $display_set[$cur_display_record]["finsttimeceilingint"];
         
         $cur_display_record ++;
         }

      //Do any remaining cells at the end.
      while($cur_output_time_int < $panel_high_hour_in_int_limit)
         {
         $html_lines[] = "<td>&nbsp;</td>";
         $cur_output_time_int ++;
         }
      
      
      //The lines are formed.  Add the row.
      $queued_html_rows[] = $html_lines;
      unset($html_lines);
      $sched_right_table_rows++;            
      }
   }
//
//----------------------------------------------------------------------------------------------------
//Does the rows corresponding to the active reservations for a flight instructor.
//
function SCHEDVIEW_form_resource_scheduling_area_finst_active( $userinfo_in,
                                                               $rscs_rec_in,
                                                               $active_reservations_in,
                                                               $panel_low_hour_in,
                                                               $panel_high_hour_in,
                                                               $resourcecolumnwidth_in,
                                                               $schedcolumnwidth_in,
                                                               $can_view_banner_reservations_in,
                                                              &$sched_right_table_rows,
                                                              &$queued_html_rows)
   {
   $done = FALSE;
   $grabpoint = 0;
   $panel_low_hour_in_int        =  $panel_low_hour_in       * 2;
   $panel_high_hour_in_int_limit = ($panel_high_hour_in + 1) * 2;

   while (!$done)
      {
      //Due to the loop, need to unset the display set to keep it from accumulating too many
      //elements.
      if (isset($display_set))
         unset($display_set);

      //Grab one element.  This is our trial set to start with.
      $display_set[] = $active_reservations_in[$grabpoint];

      //Next grabpoint.
      $grabpoint++;

      //Keep on grabbing until there is a set intersection or we're out of things to grab.
      while (
               ($grabpoint < count($active_reservations_in))
               &&
               (! SCHEDVIEW_resv_finst_array_intersection($display_set, $active_reservations_in[$grabpoint]))
            )
         {
         $display_set[] = $active_reservations_in[$grabpoint];
         $grabpoint ++;
         }

      //If we can't go further grabbing, we're done.
      if ($grabpoint >= count($active_reservations_in))
         $done = TRUE;

      //Display the set that was collected for debugging, if necessary.
      //echo "<pre>\n----------\nDisplay Set\n----------\n";
      //print_r($display_set);
      //echo "\n--------\n";

      //Our display set now contains a set of records to display.  We know there is at least one,
      //we know the times don't overlap, and we know that these are in ascending order of start time 
      //(due to the SQL query).  Therefore, we can proceed in order.
      $cur_output_time_int = $panel_low_hour_in_int;
      $cur_display_record  = 0;
      //$panel_high_hour_in_int_limit = ($panel_high_hour_in + 1) * 2;

      while ($cur_display_record < count($display_set))
         {
         //Space out the blank cells until the first reservation or next reservation.
         while($cur_output_time_int < $display_set[$cur_display_record]["finsttimefloorint"])
            {
            $html_lines[] = "<td>&nbsp;</td>";
            $cur_output_time_int ++;
            }

         //Get the text that should be displayed for the reservation.
         if ($userinfo_in === FALSE)
            {
            //echo " Clause 1 ";
            $box_string = "&nbsp;";
            }
         else
            {
            //Try to get the user name.
            //
            //echo "\n<pre>\n";
            //print_r($display_set[$cur_display_record]);
            //print_r($display_set[$cur_display_record]["useridx"]);
            //echo "\n</pre>\n";

            if ($display_set[$cur_display_record]["useridx"] > 0)
               {
               $temp_user_info = USRS_retrieve_by_idx($display_set[$cur_display_record]["useridx"]);
               if ($temp_user_info === FALSE)
                  {
                  //echo " Clause 2 ";
                  $box_string = "&nbsp;";
                  }
               else
                  {
                  //echo " Clause 3 ";
                  $box_string = $temp_user_info["lname"] 
                                . 
                                " (" 
                                . 
                                (string)($display_set[$cur_display_record]["idx"]) 
                                .
                                ")";
                  }
               }
            else
               {
               //echo " Clause 4 ";
               $box_string = "&nbsp;";
               }
            }

         //Spit the reservation.
         $html_lines[] =   "<td colspan=\""
                         . ($display_set[$cur_display_record]["finsttimeceilingint"] - $display_set[$cur_display_record]["finsttimefloorint"])
                         . "\" bgcolor=\""
                         . CONFIG_SCHED_COLOR_DSMAT_RACTV
                         . "\" align=\"center\">"
                         . $box_string
                         . "</td>";

         //This takes the time forward.
         $cur_output_time_int = $display_set[$cur_display_record]["finsttimeceilingint"];
         
         $cur_display_record ++;
         }

      //Do any remaining cells at the end.
      while($cur_output_time_int < $panel_high_hour_in_int_limit)
         {
         $html_lines[] = "<td>&nbsp;</td>";
         $cur_output_time_int ++;
         }
      
      
      //The lines are formed.  Add the row.
      $queued_html_rows[] = $html_lines;
      unset($html_lines);
      $sched_right_table_rows++;            
      }
   }
//
//----------------------------------------------------------------------------------------------------
//Does the rows corresponding to the standby reservations for a flight instructor.
//
function SCHEDVIEW_form_resource_scheduling_area_finst_standby( $userinfo_in,
                                                                $rscs_rec_in,
                                                                $standby_reservations_in,
                                                                $panel_low_hour_in,
                                                                $panel_high_hour_in,
                                                                $resourcecolumnwidth_in,
                                                                $schedcolumnwidth_in,
                                                                $can_view_banner_reservations_in,
                                                               &$sched_right_table_rows,
                                                               &$queued_html_rows)
   {
   $done = FALSE;
   $grabpoint = 0;
   $panel_low_hour_in_int        =  $panel_low_hour_in       * 2;
   $panel_high_hour_in_int_limit = ($panel_high_hour_in + 1) * 2;

   while (!$done)
      {
      //Due to the loop, need to unset the display set to keep it from accumulating too many
      //elements.
      if (isset($display_set))
         unset($display_set);

      //Grab one element.  This is our trial set to start with.
      $display_set[] = $standby_reservations_in[$grabpoint];

      //Next grabpoint.
      $grabpoint++;

      //Keep on grabbing until there is a set intersection or we're out of things to grab.
      while (
               ($grabpoint < count($standby_reservations_in))
               &&
               (! SCHEDVIEW_resv_finst_array_intersection($display_set, $standby_reservations_in[$grabpoint]))
            )
         {
         $display_set[] = $standby_reservations_in[$grabpoint];
         $grabpoint ++;
         }

      //If we can't go further grabbing, we're done.
      if ($grabpoint >= count($standby_reservations_in))
         $done = TRUE;

      //Display the set that was collected for debugging, if necessary.
      //echo "<pre>\n----------\nDisplay Set\n----------\n";
      //print_r($display_set);
      //echo "\n--------\n";

      //Our display set now contains a set of records to display.  We know there is at least one,
      //we know the times don't overlap, and we know that these are in ascending order of start time 
      //(due to the SQL query).  Therefore, we can proceed in order.
      $cur_output_time_int = $panel_low_hour_in_int;
      $cur_display_record  = 0;
      //$panel_high_hour_in_int_limit = ($panel_high_hour_in + 1) * 2;

      while ($cur_display_record < count($display_set))
         {
         //Space out the blank cells until the first reservation or next reservation.
         while($cur_output_time_int < $display_set[$cur_display_record]["finsttimefloorint"])
            {
            $html_lines[] = "<td>&nbsp;</td>";
            $cur_output_time_int ++;
            }

         //Get the text that should be displayed for the reservation.
         if ($userinfo_in === FALSE)
            {
            //echo " Clause 1 ";
            $box_string = "&nbsp;";
            }
         else
            {
            //Try to get the user name.
            //
            //echo "\n<pre>\n";
            //print_r($display_set[$cur_display_record]);
            //print_r($display_set[$cur_display_record]["useridx"]);
            //echo "\n</pre>\n";

            if ($display_set[$cur_display_record]["useridx"] > 0)
               {
               $temp_user_info = USRS_retrieve_by_idx($display_set[$cur_display_record]["useridx"]);
               if ($temp_user_info === FALSE)
                  {
                  //echo " Clause 2 ";
                  $box_string = "&nbsp;";
                  }
               else
                  {
                  //echo " Clause 3 ";
                  $box_string = $temp_user_info["lname"] 
                                . 
                                " (" 
                                . 
                                (string)($display_set[$cur_display_record]["idx"]) 
                                .
                                ")";
                  }
               }
            else
               {
               //echo " Clause 4 ";
               $box_string = "&nbsp;";
               }
            }

         //Spit the reservation.
         $html_lines[] =   "<td colspan=\""
                         . ($display_set[$cur_display_record]["finsttimeceilingint"] - $display_set[$cur_display_record]["finsttimefloorint"])
                         . "\" bgcolor=\""
                         . CONFIG_SCHED_COLOR_DSMAT_RSTBY
                         . "\" align=\"center\">"
                         . $box_string
                         . "</td>";

         //This takes the time forward.
         $cur_output_time_int = $display_set[$cur_display_record]["finsttimeceilingint"];
         
         $cur_display_record ++;
         }

      //Do any remaining cells at the end.
      while($cur_output_time_int < $panel_high_hour_in_int_limit)
         {
         $html_lines[] = "<td>&nbsp;</td>";
         $cur_output_time_int ++;
         }
      
      
      //The lines are formed.  Add the row.
      $queued_html_rows[] = $html_lines;
      unset($html_lines);
      $sched_right_table_rows++;            
      }
   }
//
//----------------------------------------------------------------------------------------------------
//Does the resource scheduling area for an individual flight instructor.
//
function SCHEDVIEW_form_resource_scheduling_area_finst( $userinfo_in,
                                                        $rscs_rec_in,
                                                        $resv_recs_in,
                                                        $panel_low_hour_in,
                                                        $panel_high_hour_in,
                                                        $resourcecolumnwidth_in,
                                                        $schedcolumnwidth_in,
                                                        $can_view_banner_reservations_in,
                                                       &$sched_right_table_rows,
                                                       &$queued_html_rows)
   {
   if ($resv_recs_in !== FALSE)  //Can't parse reservations if none there.
      {
      //Identify the banner reservations, active reservations, and standby reservations.
      //
      $banner_first  = -1;
      $banner_last   = -1;
      $active_first  = -1;
      $active_last   = -1;
      $standby_first = -1;
      $standby_last  = -1;

      $n = count($resv_recs_in);
      for ($i=0; $i<$n; $i++)
         {
         if ($resv_recs_in[$i]["type"] == RESV_TYPE_BANNER)
            {
            if ($banner_first == -1)
               $banner_first = $i;
            $banner_last = $i;
            }

         if ($resv_recs_in[$i]["type"] == RESV_TYPE_ACTIVE)
            {
            if ($active_first == -1)
               $active_first = $i;
            $active_last = $i;
            }

         if ($resv_recs_in[$i]["type"] == RESV_TYPE_STANDBY)
            {
            if ($standby_first == -1)
               $standby_first = $i;
            $standby_last = $i;
            }
         }
      //
      //-----------------------------------------------------------------------------
      //Do the banner reservations, if there are any, and if it is appropriate.
      //
      if (($banner_first != -1) && ($can_view_banner_reservations_in))
         {
         //Extract the records.
         $banner_reservations = array_slice ($resv_recs_in,
                                             $banner_first,
                                             $banner_last - $banner_first + 1);

         //echo "<pre>\n----------\nBanner Reservations\n----------\n";
         //print_r($banner_reservations);
         //echo "\n---------\n</pre>\n";

         SCHEDVIEW_form_resource_scheduling_area_finst_banner( $userinfo_in,
                                                               $rscs_rec_in,
                                                               $banner_reservations,
                                                               $panel_low_hour_in,
                                                               $panel_high_hour_in,
                                                               $resourcecolumnwidth_in,
                                                               $schedcolumnwidth_in,
                                                               $can_view_banner_reservations_in,
                                                               $sched_right_table_rows,
                                                               $queued_html_rows);
         }
      //
      //-----------------------------------------------------------------------------
      //Do the active reservations, if there are any.
      //
      if ($active_first != -1)
         {
         //Extract the records.
         $active_reservations = array_slice ($resv_recs_in,
                                             $active_first,
                                             $active_last - $active_first + 1);

         //echo "<pre>\n----------\nActive Reservations\n----------\n";
         //print_r($active_reservations);
         //echo "\n---------\n</pre>\n";

         SCHEDVIEW_form_resource_scheduling_area_finst_active( $userinfo_in,
                                                               $rscs_rec_in,
                                                               $active_reservations,
                                                               $panel_low_hour_in,
                                                               $panel_high_hour_in,
                                                               $resourcecolumnwidth_in,
                                                               $schedcolumnwidth_in,
                                                               $can_view_banner_reservations_in,
                                                               $sched_right_table_rows,
                                                               $queued_html_rows);
         }
      //
      //-----------------------------------------------------------------------------
      //Do the standby reservations, if there are any.
      //
      if ($standby_first != -1)
         {
         //Extract the records.
         $standby_reservations = array_slice ($resv_recs_in,
                                              $standby_first,
                                              $standby_last - $standby_first + 1);

         //echo "<pre>\n----------\nStandby Reservations\n----------\n";
         //print_r($standby_reservations);
         //echo "\n---------\n</pre>\n";

         SCHEDVIEW_form_resource_scheduling_area_finst_standby( $userinfo_in,
                                                                $rscs_rec_in,
                                                                $standby_reservations,
                                                                $panel_low_hour_in,
                                                                $panel_high_hour_in,
                                                                $resourcecolumnwidth_in,
                                                                $schedcolumnwidth_in,
                                                                $can_view_banner_reservations_in,
                                                                $sched_right_table_rows,
                                                                $queued_html_rows);
         }
      //
      }

   SCHEDVIEW_form_resource_scheduling_area_terminator_bar($userinfo_in,
                                                          $rscs_rec_in,
                                                          $resv_recs_in,
                                                          $panel_low_hour_in,
                                                          $panel_high_hour_in,
                                                          $resourcecolumnwidth_in,
                                                          $schedcolumnwidth_in,
                                                          $sched_right_table_rows,
                                                          $queued_html_lines);
   $queued_html_rows[] = $queued_html_lines;
   unset($queued_html_lines);
   }
//
//----------------------------------------------------------------------------------------------------
//Does the rows corresponding to the banner reservations for an aircraft or simulator.
//
function SCHEDVIEW_form_resource_scheduling_area_acftsim_banner( $userinfo_in,
                                                                 $rscs_rec_in,
                                                                 $banner_reservations_in,
                                                                 $panel_low_hour_in,
                                                                 $panel_high_hour_in,
                                                                 $resourcecolumnwidth_in,
                                                                 $schedcolumnwidth_in,
                                                                 $can_view_banner_reservations_in,
                                                                &$sched_right_table_rows,
                                                                &$queued_html_rows)
   {
   $done = FALSE;
   $grabpoint = 0;
   $panel_low_hour_in_int        =  $panel_low_hour_in       * 2;
   $panel_high_hour_in_int_limit = ($panel_high_hour_in + 1) * 2;

   while (!$done)
      {
      //Due to the loop, need to unset the display set to keep it from accumulating too many
      //elements.
      if (isset($display_set))
         unset($display_set);

      //Grab one element.  This is our trial set to start with.
      $display_set[] = $banner_reservations_in[$grabpoint];

      //Next grabpoint.
      $grabpoint++;

      //Keep on grabbing until there is a set intersection or we're out of things to grab.
      while (
               ($grabpoint < count($banner_reservations_in))
               &&
               (! SCHEDVIEW_resv_actfsim_array_intersection($display_set, $banner_reservations_in[$grabpoint]))
            )
         {
         $display_set[] = $banner_reservations_in[$grabpoint];
         $grabpoint ++;
         }

      //If we can't go further grabbing, we're done.
      if ($grabpoint >= count($banner_reservations_in))
         $done = TRUE;

      //Display the set that was collected for debugging, if necessary.
      //echo "<pre>\n----------\nDisplay Set\n----------\n";
      //print_r($display_set);
      //echo "\n--------\n";

      //Our display set now contains a set of records to display.  We know there is at least one,
      //we know the times don't overlap, and we know that these are in ascending order of start time 
      //(due to the SQL query).  Therefore, we can proceed in order.
      $cur_output_time_int = $panel_low_hour_in_int;
      $cur_display_record  = 0;
      //$panel_high_hour_in_int_limit = ($panel_high_hour_in + 1) * 2;

      while ($cur_display_record < count($display_set))
         {
         //Space out the blank cells until the first reservation or next reservation.
         while($cur_output_time_int < $display_set[$cur_display_record]["acftsimtimefloorint"])
            {
            $html_lines[] = "<td>&nbsp;</td>";
            $cur_output_time_int ++;
            }

         //Get the text that should be displayed for the reservation.
         if ($userinfo_in === FALSE)
            {
            //echo " Clause 1 ";
            $box_string = "&nbsp;";
            }
         else
            {
            //Try to get the user name.
            //
            //echo "\n<pre>\n";
            //print_r($display_set[$cur_display_record]);
            //print_r($display_set[$cur_display_record]["useridx"]);
            //echo "\n</pre>\n";

            if ($display_set[$cur_display_record]["useridx"] > 0)
               {
               $temp_user_info = USRS_retrieve_by_idx($display_set[$cur_display_record]["useridx"]);
               if ($temp_user_info === FALSE)
                  {
                  //echo " Clause 2 ";
                  $box_string = "&nbsp;";
                  }
               else
                  {
                  //echo " Clause 3 ";
                  $box_string = $temp_user_info["lname"] 
                                . 
                                " (" 
                                . 
                                (string)($display_set[$cur_display_record]["idx"]) 
                                .
                                ")";
                  }
               }
            else
               {
               //echo " Clause 4 ";
               $box_string = "&nbsp;";
               }
            }

         //Spit the reservation.
         $html_lines[] =   "<td colspan=\""
                         . ($display_set[$cur_display_record]["acftsimtimeceilingint"] - $display_set[$cur_display_record]["acftsimtimefloorint"])
                         . "\" bgcolor=\""
                         . CONFIG_SCHED_COLOR_DSMAT_RBANN
                         . "\" align=\"center\">"
                         . $box_string
                         . "</td>";

         //This takes the time forward.
         $cur_output_time_int = $display_set[$cur_display_record]["acftsimtimeceilingint"];
         
         $cur_display_record ++;
         }

      //Do any remaining cells at the end.
      while($cur_output_time_int < $panel_high_hour_in_int_limit)
         {
         $html_lines[] = "<td>&nbsp;</td>";
         $cur_output_time_int ++;
         }
      
      
      //The lines are formed.  Add the row.
      $queued_html_rows[] = $html_lines;
      unset($html_lines);
      $sched_right_table_rows++;            
      }
   }
//
//----------------------------------------------------------------------------------------------------
//Does the rows corresponding to the active reservations for an aircraft or simulator.
//
function SCHEDVIEW_form_resource_scheduling_area_acftsim_active( $userinfo_in,
                                                                 $rscs_rec_in,
                                                                 $active_reservations_in,
                                                                 $panel_low_hour_in,
                                                                 $panel_high_hour_in,
                                                                 $resourcecolumnwidth_in,
                                                                 $schedcolumnwidth_in,
                                                                 $can_view_banner_reservations_in,
                                                                &$sched_right_table_rows,
                                                                &$queued_html_rows)
   {
   $done = FALSE;
   $grabpoint = 0;
   $panel_low_hour_in_int        =  $panel_low_hour_in       * 2;
   $panel_high_hour_in_int_limit = ($panel_high_hour_in + 1) * 2;

   while (!$done)
      {
      //Due to the loop, need to unset the display set to keep it from accumulating too many
      //elements.
      if (isset($display_set))
         unset($display_set);

      //Grab one element.  This is our trial set to start with.
      $display_set[] = $active_reservations_in[$grabpoint];

      //Next grabpoint.
      $grabpoint++;

      //Keep on grabbing until there is a set intersection or we're out of things to grab.
      while (
               ($grabpoint < count($active_reservations_in))
               &&
               (! SCHEDVIEW_resv_actfsim_array_intersection($display_set, $active_reservations_in[$grabpoint]))
            )
         {
         $display_set[] = $active_reservations_in[$grabpoint];
         $grabpoint ++;
         }

      //If we can't go further grabbing, we're done.
      if ($grabpoint >= count($active_reservations_in))
         $done = TRUE;

      //Display the set that was collected for debugging, if necessary.
      //echo "<pre>\n----------\nDisplay Set\n----------\n";
      //print_r($display_set);
      //echo "\n--------\n";

      //Our display set now contains a set of records to display.  We know there is at least one,
      //we know the times don't overlap, and we know that these are in ascending order of start time 
      //(due to the SQL query).  Therefore, we can proceed in order.
      $cur_output_time_int = $panel_low_hour_in_int;
      $cur_display_record  = 0;
      //$panel_high_hour_in_int_limit = ($panel_high_hour_in + 1) * 2;

      while ($cur_display_record < count($display_set))
         {
         //Space out the blank cells until the first reservation or next reservation.
         while($cur_output_time_int < $display_set[$cur_display_record]["acftsimtimefloorint"])
            {
            $html_lines[] = "<td>&nbsp;</td>";
            $cur_output_time_int ++;
            }

         //Get the text that should be displayed for the reservation.
         if ($userinfo_in === FALSE)
            {
            //echo " Clause 1 ";
            $box_string = "&nbsp;";
            }
         else
            {
            //Try to get the user name.
            //
            //echo "\n<pre>\n";
            //print_r($display_set[$cur_display_record]);
            //print_r($display_set[$cur_display_record]["useridx"]);
            //echo "\n</pre>\n";

            if ($display_set[$cur_display_record]["useridx"] > 0)
               {
               $temp_user_info = USRS_retrieve_by_idx($display_set[$cur_display_record]["useridx"]);
               if ($temp_user_info === FALSE)
                  {
                  //echo " Clause 2 ";
                  $box_string = "&nbsp;";
                  }
               else
                  {
                  //echo " Clause 3 ";
                  $box_string = $temp_user_info["lname"] 
                                . 
                                " (" 
                                . 
                                (string)($display_set[$cur_display_record]["idx"]) 
                                .
                                ")";
                  }
               }
            else
               {
               //echo " Clause 4 ";
               $box_string = "&nbsp;";
               }
            }


         //Spit the reservation.
         $html_lines[] =   "<td colspan=\""
                         . ($display_set[$cur_display_record]["acftsimtimeceilingint"] - $display_set[$cur_display_record]["acftsimtimefloorint"])
                         . "\" bgcolor=\""
                         . CONFIG_SCHED_COLOR_DSMAT_RACTV
                         . "\" align=\"center\">"
                         . $box_string
                         . "</td>";

         //This takes the time forward.
         $cur_output_time_int = $display_set[$cur_display_record]["acftsimtimeceilingint"];
         
         $cur_display_record ++;
         }

      //Do any remaining cells at the end.
      while($cur_output_time_int < $panel_high_hour_in_int_limit)
         {
         $html_lines[] = "<td>&nbsp;</td>";
         $cur_output_time_int ++;
         }
      
      
      //The lines are formed.  Add the row.
      $queued_html_rows[] = $html_lines;
      unset($html_lines);
      $sched_right_table_rows++;            
      }
   }
//
//----------------------------------------------------------------------------------------------------
//Does the rows corresponding to the standby reservations for an aircraft or simulator.
//
function SCHEDVIEW_form_resource_scheduling_area_acftsim_standby( $userinfo_in,
                                                                 $rscs_rec_in,
                                                                 $standby_reservations_in,
                                                                 $panel_low_hour_in,
                                                                 $panel_high_hour_in,
                                                                 $resourcecolumnwidth_in,
                                                                 $schedcolumnwidth_in,
                                                                 $can_view_banner_reservations_in,
                                                                &$sched_right_table_rows,
                                                                &$queued_html_rows)
   {
   $done = FALSE;
   $grabpoint = 0;
   $panel_low_hour_in_int        =  $panel_low_hour_in       * 2;
   $panel_high_hour_in_int_limit = ($panel_high_hour_in + 1) * 2;

   while (!$done)
      {
      //Due to the loop, need to unset the display set to keep it from accumulating too many
      //elements.
      if (isset($display_set))
         unset($display_set);

      //Grab one element.  This is our trial set to start with.
      $display_set[] = $standby_reservations_in[$grabpoint];

      //Next grabpoint.
      $grabpoint++;

      //Keep on grabbing until there is a set intersection or we're out of things to grab.
      while (
               ($grabpoint < count($standby_reservations_in))
               &&
               (! SCHEDVIEW_resv_actfsim_array_intersection($display_set, $standby_reservations_in[$grabpoint]))
            )
         {
         $display_set[] = $standby_reservations_in[$grabpoint];
         $grabpoint ++;
         }

      //If we can't go further grabbing, we're done.
      if ($grabpoint >= count($standby_reservations_in))
         $done = TRUE;

      //Display the set that was collected for debugging, if necessary.
      //echo "<pre>\n----------\nDisplay Set\n----------\n";
      //print_r($display_set);
      //echo "\n--------\n";

      //Our display set now contains a set of records to display.  We know there is at least one,
      //we know the times don't overlap, and we know that these are in ascending order of start time 
      //(due to the SQL query).  Therefore, we can proceed in order.
      $cur_output_time_int = $panel_low_hour_in_int;
      $cur_display_record  = 0;
      //$panel_high_hour_in_int_limit = ($panel_high_hour_in + 1) * 2;

      while ($cur_display_record < count($display_set))
         {
         //Space out the blank cells until the first reservation or next reservation.
         while($cur_output_time_int < $display_set[$cur_display_record]["acftsimtimefloorint"])
            {
            $html_lines[] = "<td>&nbsp;</td>";
            $cur_output_time_int ++;
            }

         //Get the text that should be displayed for the reservation.
         if ($userinfo_in === FALSE)
            {
            //echo " Clause 1 ";
            $box_string = "&nbsp;";
            }
         else
            {
            //Try to get the user name.
            //
            //echo "\n<pre>\n";
            //print_r($display_set[$cur_display_record]);
            //print_r($display_set[$cur_display_record]["useridx"]);
            //echo "\n</pre>\n";

            if ($display_set[$cur_display_record]["useridx"] > 0)
               {
               $temp_user_info = USRS_retrieve_by_idx($display_set[$cur_display_record]["useridx"]);
               if ($temp_user_info === FALSE)
                  {
                  //echo " Clause 2 ";
                  $box_string = "&nbsp;";
                  }
               else
                  {
                  //echo " Clause 3 ";
                  $box_string = $temp_user_info["lname"] 
                                . 
                                " (" 
                                . 
                                (string)($display_set[$cur_display_record]["idx"]) 
                                .
                                ")";
                  }
               }
            else
               {
               //echo " Clause 4 ";
               $box_string = "&nbsp;";
               }
            }


         //Spit the reservation.
         $html_lines[] =   "<td colspan=\""
                         . ($display_set[$cur_display_record]["acftsimtimeceilingint"] - $display_set[$cur_display_record]["acftsimtimefloorint"])
                         . "\" bgcolor=\""
                         . CONFIG_SCHED_COLOR_DSMAT_RSTBY
                         . "\" align=\"center\">"
                         . $box_string
                         . "</td>";

         //This takes the time forward.
         $cur_output_time_int = $display_set[$cur_display_record]["acftsimtimeceilingint"];
         
         $cur_display_record ++;
         }

      //Do any remaining cells at the end.
      while($cur_output_time_int < $panel_high_hour_in_int_limit)
         {
         $html_lines[] = "<td>&nbsp;</td>";
         $cur_output_time_int ++;
         }
      
      
      //The lines are formed.  Add the row.
      $queued_html_rows[] = $html_lines;
      unset($html_lines);
      $sched_right_table_rows++;            
      }
   }
//
//----------------------------------------------------------------------------------------------------
function SCHEDVIEW_form_resource_scheduling_area_acftsim( $userinfo_in,
                                                          $rscs_rec_in,
                                                          $resv_recs_in,
                                                          $panel_low_hour_in,
                                                          $panel_high_hour_in,
                                                          $resourcecolumnwidth_in,
                                                          $schedcolumnwidth_in,
                                                          $can_view_banner_reservations_in,
                                                         &$sched_right_table_rows,
                                                         &$queued_html_rows)
   {
   if ($resv_recs_in !== FALSE)  //Can't parse reservations if none there.
      {
      //echo "<pre>\n----------\nReservations Passed In\n----------\n";
      //print_r($resv_recs_in);
      //echo "\n---------\n</pre>\n";
      //
      //Identify the banner reservations, active reservations, and standby reservations.
      //
      $banner_first  = -1;
      $banner_last   = -1;
      $active_first  = -1;
      $active_last   = -1;
      $standby_first = -1;
      $standby_last  = -1;

      $n = count($resv_recs_in);
      for ($i=0; $i<$n; $i++)
         {
         if ($resv_recs_in[$i]["type"] == RESV_TYPE_BANNER)
            {
            if ($banner_first == -1)
               $banner_first = $i;
            $banner_last = $i;
            }

         if ($resv_recs_in[$i]["type"] == RESV_TYPE_ACTIVE)
            {
            if ($active_first == -1)
               $active_first = $i;
            $active_last = $i;
            }

         if ($resv_recs_in[$i]["type"] == RESV_TYPE_STANDBY)
            {
            if ($standby_first == -1)
               $standby_first = $i;
            $standby_last = $i;
            }
         }
      //
      //-----------------------------------------------------------------------------
      //Do the banner reservations, if there are any, and if it is appropriate.
      //
      if (($banner_first != -1) && ($can_view_banner_reservations_in))
         {
         //Extract the records.
         $banner_reservations = array_slice ($resv_recs_in,
                                             $banner_first,
                                             $banner_last - $banner_first + 1);

         //echo "<pre>\n----------\nBanner Reservations\n----------\n";
         //print_r($banner_reservations);
         //echo "\n---------\n</pre>\n";

         SCHEDVIEW_form_resource_scheduling_area_acftsim_banner( $userinfo_in,
                                                                 $rscs_rec_in,
                                                                 $banner_reservations,
                                                                 $panel_low_hour_in,
                                                                 $panel_high_hour_in,
                                                                 $resourcecolumnwidth_in,
                                                                 $schedcolumnwidth_in,
                                                                 $can_view_banner_reservations_in,
                                                                 $sched_right_table_rows,
                                                                 $queued_html_rows);
         }
      //
      //-----------------------------------------------------------------------------
      //Do the active reservations, if there are any.
      //
      if ($active_first != -1)
         {
         //Extract the records.
         $active_reservations = array_slice ($resv_recs_in,
                                             $active_first,
                                             $active_last - $active_first + 1);

         //echo "<pre>\n----------\nActive Reservations\n----------\n";
         //print_r($active_reservations);
         //echo "\n---------\n</pre>\n";

         SCHEDVIEW_form_resource_scheduling_area_acftsim_active( $userinfo_in,
                                                                 $rscs_rec_in,
                                                                 $active_reservations,
                                                                 $panel_low_hour_in,
                                                                 $panel_high_hour_in,
                                                                 $resourcecolumnwidth_in,
                                                                 $schedcolumnwidth_in,
                                                                 $can_view_banner_reservations_in,
                                                                 $sched_right_table_rows,
                                                                 $queued_html_rows);
         }
      //
      //-----------------------------------------------------------------------------
      //Do the standby reservations, if there are any.
      //
      if ($standby_first != -1)
         {
         //Extract the records.
         $standby_reservations = array_slice ($resv_recs_in,
                                              $standby_first,
                                              $standby_last - $standby_first + 1);

         //echo "<pre>\n----------\nStandby Reservations\n----------\n";
         //print_r($standby_reservations);
         //echo "\n---------\n</pre>\n";

         SCHEDVIEW_form_resource_scheduling_area_acftsim_standby( $userinfo_in,
                                                                  $rscs_rec_in,
                                                                  $standby_reservations,
                                                                  $panel_low_hour_in,
                                                                  $panel_high_hour_in,
                                                                  $resourcecolumnwidth_in,
                                                                  $schedcolumnwidth_in,
                                                                  $can_view_banner_reservations_in,
                                                                  $sched_right_table_rows,
                                                                  $queued_html_rows);
         }
      //
      }

   SCHEDVIEW_form_resource_scheduling_area_terminator_bar($userinfo_in,
                                                          $rscs_rec_in,
                                                          $resv_recs_in,
                                                          $panel_low_hour_in,
                                                          $panel_high_hour_in,
                                                          $resourcecolumnwidth_in,
                                                          $schedcolumnwidth_in,
                                                          $sched_right_table_rows,
                                                          $queued_html_lines);
   $queued_html_rows[] = $queued_html_lines;
   unset($queued_html_lines);
   }
//
//----------------------------------------------------------------------------------------------------
//Does a dayview table row.
//
function SCHEDVIEW_do_dayview_table_row(
                              $userinfo_in,                                //User record, or FALSE if none.
                              $rscs_rec_in,                                //Resource record.
                              $resv_recs_in,                               //Applicable reservations, or FALSE if none.
                              $panel_low_hour_in,                          //Low panel hour.
                              $panel_high_hour_in,                         //High panel hour (inclusive)
                              $resourcecolumnwidth_in,                     //Column width, in percent, for left resource header.
                              $schedcolumnwidth_in,                        //Column width for each scheduling cell. 
                              $can_view_banner_reservations_in             //TRUE if this user is allowed to see banners.                     
                              )
   {
   //Start a table row.  This encompasses the left area that identifies the resource (with potentially a
   //rowspan > 1) and the scheduling area at the right.

   //Start off believing no table rows dedicated to the right scheduling area for a resource.
   $sched_right_table_rows = 0;

   //Form the scheduling area of the resource row as an array of HTML rows.  Each HTML row is an array of 
   //one or more HTML lines.  We have to do this first, because otherwise won't know how large the rowspan
   //for the resource name at the left should be.
   //
   //We have to differentiate between forming the scheduling area for a flight instructor versus an
   //aircraft/simulator, as different fields are checked.
   //
   if ($rscs_rec_in["type"] == RSCS_TYPE_FLIGHTINSTRUCTOR)
      {
      SCHEDVIEW_form_resource_scheduling_area_finst($userinfo_in,
                                                    $rscs_rec_in,
                                                    $resv_recs_in,
                                                    $panel_low_hour_in,
                                                    $panel_high_hour_in,
                                                    $resourcecolumnwidth_in,
                                                    $schedcolumnwidth_in,
                                                    $can_view_banner_reservations_in,
                                                    $sched_right_table_rows,
                                                    $queued_html_sched_rows);
      }
   else
      {
      SCHEDVIEW_form_resource_scheduling_area_acftsim($userinfo_in,
                                                      $rscs_rec_in,
                                                      $resv_recs_in,
                                                      $panel_low_hour_in,
                                                      $panel_high_hour_in,
                                                      $resourcecolumnwidth_in,
                                                      $schedcolumnwidth_in,
                                                      $can_view_banner_reservations_in,
                                                      $sched_right_table_rows,
                                                      $queued_html_sched_rows);
      }

   //Form the HTML for the left area with the resource short name.  We can do this now because the number of
   //rows is no known.  This will consist of exactly one <TD> cell.
   SCHEDVIEW_do_left_resource_title_area($userinfo_in,
                                         $rscs_rec_in,
                                         $resv_recs_in,
                                         $panel_low_hour_in,
                                         $panel_high_hour_in,
                                         $resourcecolumnwidth_in,
                                         $schedcolumnwidth_in,
                                         $sched_right_table_rows,
                                         $queued_html_head_lines);

   //echo "<pre>\n";
   //print_r($queued_html_head_rows);
   //echo "</pre>\n";

   //Output the HTML that was generated.
   $n = count($queued_html_sched_rows);
   for ($i=0; $i<$n; $i++)
      {
      //Row starts.
      HTMLFORMAT_echo_push_nl("<tr>");

      //If this is the first row, output the left heading.  This will have a rowspan potentially
      //>1.
      if ($i == 0)
         {
         for ($j=0; $j<count($queued_html_head_lines); $j++)
            {
            HTMLFORMAT_echo_noop_nl($queued_html_head_lines[$j]);
            }
         }

      //Output the scheduling row(s).
      $cur_lines = $queued_html_sched_rows[$i];

      for ($j=0; $j<count($cur_lines); $j++)
         {
         HTMLFORMAT_echo_noop_nl($cur_lines[$j]);
         }

      //Row ends.
      HTMLFORMAT_echo_pull_nl("</tr>");
      }
   }
//
//----------------------------------------------------------------------------------------------------
//Display the scheduling area for a given date and time.
//
//Parameters:
//   userinfo             :  The array of user information for the logged in user (pulled from the MySQL
//                           database), or FALSE if no user is logged in.
//
//   sessioninfo_in       :  The array of information about the current login session, or FALSE if
//                           no session is active.
//
//   dateyear             :  The year of the date to display (an integer).
//
//   datemonth            :  The month of the date to display (an integer).
//
//   dateday              :  The day of the date to display (an integer).
//
//   timehour             :  The hour of the time to display (an integer).
//
//   timemin              :  The minute of the time to display (an integer).
//
//   diff_time_perm_array :  An array of permissions about previous and future times
//                           specifying which should be displayed.
//
function SCHEDVIEW_scheduling_area($userinfo, $sessioninfo_in,
                                   $dateyear, $datemonth, $dateday,
                                   $timehour, $timemin,
                                   $diff_time_perm_array,
                                   $panel
                                   )
   {
   global $CONFIG_SCHED_DAY_PANELS;

   SCHEDVIEW_temporal_navigation_bar(
                                    $userinfo,
                                    $dateyear, $datemonth, $dateday,
                                    $timehour, $timemin,
                                    $diff_time_perm_array,
                                    $panel
                                    );

   $panel_low_hour   = $CONFIG_SCHED_DAY_PANELS[$panel * 2];
   $panel_high_hour  = $CONFIG_SCHED_DAY_PANELS[$panel * 2 + 1];

   $nwholehours      = $panel_high_hour - $panel_low_hour + 1;
   $nschedcols       = $nwholehours * 2;

   //Calculate whether the logged in user, if any, can view banner reservations.  Banner reservations
   //are non-restrictive, so this comes down to any logged in user.
   if ($userinfo === FALSE)
      {
      $user_can_view_banner_reservations = FALSE;
      }
   else
      {
      $user_can_view_banner_reservations = TRUE;
      }

   //Calculate how wide to make columns.  The goal is to give a hint to the browser that we want
   //everthing except the first column to be the same width.  Output is an integer percentage.
   //
   $schedcolumnwidth = (int)(100/($nschedcols+1) + 0.5);
   $resourcecolumnwidth = 100 - ($nschedcols * $schedcolumnwidth);

   //Obtain the list of resources to display.  This function will return FALSE if there are no
   //resources that meet eligibility requirements, and this case needs to be handled
   //carefully.
   //
   $rscs_to_display = RSCS_rscs_list_dayview_online();
   //
   //echo "<tt>\n";
   //print_r($rscs_to_display);
   //echo "</tt>\n";

   //Determine the count of resources to be displayed.  If the database retrieval function
   //returned FALSE, this value should be set to 0.  0 will ensure that the array is not
   //dereferenced at all.
   //
   if ($rscs_to_display === FALSE)
      {
      $resource_display_count = 0;
      }
   else
      {
      $resource_display_count = count($rscs_to_display);
      }

   //echo " Value of resource_display_count : " . $resource_display_count . " ";

   //Calculate the number of time columns involved in this panel.  This is constant across all
   //the resources because of the rectangular layout.
   $n_time_columns = SCHEDVIEW_panel_n_time_columns($panel_low_hour, $panel_high_hour);
   //echo "<tt>\n";
   //print_r($n_time_columns);
   //echo "</tt>\n";

   //Calculate an stime corresponding to the left edge of the panel.  This is used for the SQL query.
   //
   $panel_left_stime = STIME_stime_make_medres($dateyear, $datemonth, $dateday, $panel_low_hour, 0);

   //Calculate an stime corresponding to the right edge of the panel.  This is used for the SQL query.
   //We need to be careful at the right edge because of the midnight boundary.
   //
   if ($panel_high_hour < 23)
      {
      $panel_right_stime = STIME_stime_make_medres($dateyear, $datemonth, $dateday, $panel_high_hour + 1, 0);
      }
   else
      {
      //Figure out what one day in the future is.
      DATEFUNC_one_day_future($dateyear, 
                              $datemonth, 
                              $dateday, 
                              $localtemp_year_onedayfuture, 
                              $localtemp_month_onedayfuture, 
                              $localtemp_day_onedayfuture);
      //And calculate the STIME.
      //
      $panel_right_stime = STIME_stime_make_medres($localtemp_year_onedayfuture, 
                                                   $localtemp_month_onedayfuture, 
                                                   $localtemp_day_onedayfuture, 
                                                   0, 
                                                   0);
      }

   //echo "<br><br>\n";
   //print_r($panel_left_stime);
   //echo "<br><br>\n";
   //print_r($panel_right_stime);
   //echo "<br><br>\n";

   //Run the SQL query to identify the reservation records that match the time limit parameters.
   //These will be sorted according to the index, not the resource sort order, and then the reservation
   //type, so a little rearrangement will be necessary posthumously.
   //
   RESV_resvns_in_time_window( $panel_left_stime,
                               $panel_right_stime,
                               $flight_inst_data_array,
                               $flight_inst_search_array,
                               $resource_data_array,
                               $resource_search_array );
   //
   //echo "<br><pre>\n";
   //print_r($flight_inst_data_array);
   //echo "</pre><br>\n";
   //echo "<br><pre>\n";
   //print_r($flight_inst_search_array);
   //echo "</pre><br>\n";
   //echo "<br><pre>\n";
   //print_r($resource_data_array);
   //echo "</pre><br>\n";
   //echo "<br><pre>\n";
   //print_r($resource_search_array);
   //echo "</pre><br>\n";
   //
   //Decorate the lists of reservations with additional information that will allow quicker display
   //of reservations.
   SCHEDVIEW_resv_list_decorate($flight_inst_data_array, $panel_left_stime, $panel_right_stime);
   SCHEDVIEW_resv_list_decorate($resource_data_array,    $panel_left_stime, $panel_right_stime);
   //
   //echo "<pre>\n";
   //echo "Flight Instructor Data\n---------------------\n";
   //print_r($flight_inst_data_array);
   //echo "\nResource Data Array\n";
   //echo "-------------------\n";
   //print_r($resource_data_array);
   //echo "</pre>\n";


   HTMLFORMAT_echo_push_nl("<table border=\"1\" cellspacing=\"0\" cellpadding=\"1\" width=\"100%\">");

   for ($row=-1; $row <= $resource_display_count; $row++)
      {    
      if (($row == -1) || ($row == $resource_display_count))
         {
         //Top or bottom row, containing time headings.
         //
         HTMLFORMAT_echo_push_nl("<tr>");
            HTMLFORMAT_echo_push_nl("<td colspan=\"1\" width=\"" . $resourcecolumnwidth . "%\" bgcolor=\"#" . CONFIG_SCHED_COLOR_DSMAT_THEAD . "\">");
               HTMLFORMAT_echo_noop_nl("&nbsp;");
            HTMLFORMAT_echo_pull_nl("</td>");

            for ($i=$panel_low_hour; $i<=$panel_high_hour; $i++)
               {
               HTMLFORMAT_echo_push_nl("<td align=\"center\" colspan=\"2\" width=\"" . $schedcolumnwidth * 2 
                                       . "%\" bgcolor=\"#" . CONFIG_SCHED_COLOR_DSMAT_THEAD . "\">");
               HTMLFORMAT_echo_noop_nl("<font size=\"3\">" . DATEFUNC_stdtimenosec($i, 0) . "</font>");
               HTMLFORMAT_echo_pull_nl("</td>");
               }
       
         HTMLFORMAT_echo_pull_nl("</tr>");

         //If we have just done the top header and if there are no resources, output a table row indicating that
         //there are no resources that met search criteria.
         //
         if (($row == -1) && ($resource_display_count == 0))
            {
            HTMLFORMAT_echo_noop_nl("<tr align=\"center\"><td colspan=\""
                                    .
                                    sprintf("%d", $nschedcols+1)
                                    .
                                    "\"><br><b>No Resources Online</b><br><br></td></tr>");
            }
         }
      else
         {
         //Pull the current resource from the array.  I haven't figured out the PHP syntax enough to
         //access an element of a 2-D array directly.
         //
         $current_resource = $rscs_to_display[$row];

         //Extract the records from the SQL resv queries that correspond to the flight instructor or resource.
         //
         if ($current_resource["type"] == RSCS_TYPE_FLIGHTINSTRUCTOR)
            {
            //Flight instructor.
            $target_resvs = RESV_extract_finst_records($flight_inst_data_array, $flight_inst_search_array, $current_resource["idx"]);
            //
            //echo "<br><pre>\n";
            //print_r($target_resvs);
            //echo "</pre><br>\n";
            }
         else
            {
            //Aircraft or simulator.
            $target_resvs = RESV_extract_resource_records($resource_data_array, $resource_search_array, $current_resource["idx"]);
            //
            //echo "<br><pre>\n";
            //print_r($target_resvs);
            //echo "</pre><br>\n";
            }

         SCHEDVIEW_do_dayview_table_row(
                                        $userinfo,
                                        $current_resource,
                                        $target_resvs,
                                        $panel_low_hour,
                                        $panel_high_hour,
                                        $resourcecolumnwidth,
                                        $schedcolumnwidth,
                                        $user_can_view_banner_reservations
                                       );
         }
      }  

   HTMLFORMAT_echo_pull_nl("</table>");
   }
//
//--------------------------------------------------------------------------------
//End of $RCSfile: schedview.inc,v $.
//--------------------------------------------------------------------------------
?>
