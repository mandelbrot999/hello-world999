<?php
//********************************************************************************
//Copyright (C) 2007 David T. Ashley
//********************************************************************************
//This program or source file is free software; you can redistribute it and/or
//modify it under the terms of the GNU Lesser General Public License as published
//by the Free Software Foundation; either version 2 of the License, or (at your
//option) any later version.
//
//This program or source file is distributed in the hope that it will
//be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You may have received a copy of the GNU Lesser General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//********************************************************************************
//
//Obtains a data snapshot used for outputting web page
//statistics at the end of a page.  This should be the first
//function call made.  The data format is not proprietary (i.e.
//the caller is conceptually free to pick it apart).
//
function STDFORMAT_page_begin_snapshot()
   {
   $rv['time_rv']      = time();
   $rv['getrusage_rv'] = getrusage();
   return($rv);
   }

//Returns the complete top portion of a web page as a string,
//formatted with newlines for human readability.
//
function STDFORMAT_page_top($in_snapshot, 
                            $in_htmldeclaredtitle,
                            $in_htmlselfdonetitle,
                            $in_background,
                            $in_link,
                            $in_vlink,
                            $in_alink)
   {
   $rv  = "<html>\n";
   $rv .= "<head>\n";
   $rv .= "<title>" . $in_htmldeclaredtitle . "</title>\n";
   $rv .= "</head>\n";
   $rv .= STDFORMAT_body_tag($in_background, $in_link, $in_vlink, $in_alink) . "\n";
   $rv .= STDFORMAT_default_font_tag() . "\n";
   $rv .= "<p align=\"center\">\n";
   $rv .= "<font size=\"5\">\n";
   $rv .= "<b>" . $in_htmlselfdonetitle . "</b>\n";
   $rv .= "</font>\n";
   $rv .= "</p>\n";
   $rv .= STDFORMAT_hline_thin() . "\n";

   return($rv);
   }


//Returns the Google AdSense bottom banner that appears on most pages.  All
//HTML is balanced and no other material is provided.
//
function STDFORMAT_advertising_bottom()
   {
   $rv = "<p align=\"center\">\n"
         .
         "<table border=\"0\" width=\"80%\">\n"
         .
         "<tr>\n"
         .
         "<td align=\"left\">\n"
         .
         "<script type=\"text/javascript\"><!--\n"
         .
         "google_ad_client = \"pub-0968676922395080\";\n"
         .
         "/* UCULIB, Left Bottom */\n"
         .
         "google_ad_slot = \"7493291831\";\n"
         .
         "google_ad_width = 300;\n"
         .
         "google_ad_height = 250;\n"
         .
         "//-->\n"
         .
         "</script>\n"
         .
         "<script type=\"text/javascript\"\n"
         .
         "src=\"http://pagead2.googlesyndication.com/pagead/show_ads.js\">\n"
         .
         "</script>\n"
         .
         "</td>\n"
         .
         "<td align=\"center\">\n"
         .
         "<script type=\"text/javascript\"><!--\n"
         .
         "google_ad_client = \"pub-0968676922395080\";\n"
         .
         "/* UCULIB, Center Bottom */\n"
         .
         "google_ad_slot = \"1148830860\";\n"
         .
         "google_ad_width = 300;\n"
         .
         "google_ad_height = 250;\n"
         .
         "//-->\n"
         .
         "</script>\n"
         .
         "<script type=\"text/javascript\"\n"
         .
         "src=\"http://pagead2.googlesyndication.com/pagead/show_ads.js\">\n"
         .
         "</script>\n"
         .
         "</td>\n"
         .
         "<td align=\"right\">\n"
         .
         "<script type=\"text/javascript\"><!--\n"
         .
         "google_ad_client = \"pub-0968676922395080\";\n"
         .
         "/* UCULIB, Right Bottom */\n"
         .
         "google_ad_slot = \"7526152668\";\n"
         .
         "google_ad_width = 300;\n"
         .
         "google_ad_height = 250;\n"
         .
         "//-->\n"
         .
         "</script>\n"
         .
         "<script type=\"text/javascript\"\n"
         .
         "src=\"http://pagead2.googlesyndication.com/pagead/show_ads.js\">\n"
         .
         "</script>\n"
         .
         "</td>\n"
         .
         "</tr>\n"
         .
         "</table>\n"
         .
         "</p>\n"
         ;
   return($rv);
   }


//Returns the complete bottom portion of a web page.  This starts
//from the horizontal line delineating the footer and moves downward.
//Newlines are included for human-friendly reading.
//
function STDFORMAT_page_bottom($in_snapshot)
   {
   //Make the second call to get more resource usage data, which will be
   //used to display system and user time consumed.
   $ru2 = getrusage();

   $rv  = STDFORMAT_std_footer($in_snapshot['time_rv'], $ru2, $in_snapshot['getrusage_rv']);
 
   $rv .= "</font>\n";
   $rv .= "</body>\n";
   $rv .= "</html>\n";
   return($rv);
   }

//Returns the HTML for the standard footer of a web page, including top
//and bottom horizontal lines.  All HTML is balanced.  Newlines
//are provided for human readability of the HTML.
//
function STDFORMAT_std_footer($in_time, $in_ru2, $in_ru1)
   {
   $rv  = STDFORMAT_hline_thin() . "\n";
   $rv .= "<font size=\"2\">\n";
   $rv .= "<p align=\"center\" style=\"margin-top:0; margin-bottom:0\">\n";
   $rv  = $rv . STDFORMAT_std_footer_text($in_time, $in_ru2, $in_ru1);
   $rv .= "</p>\n";
   $rv .= "</font>\n";
   $rv .= STDFORMAT_hline_thick() . "\n";
   return($rv);
   }

//Returns the HTML for the text occurring in the standard footer of a web page,
//with no newlines or preceding horizontal lines or following horizontal lines.
//No HTML formatting codes are used.
//
function STDFORMAT_std_footer_text($in_time, $in_ru2, $in_ru1)
   {
   //Figure out the total, system, and user time to generate.
   STDFORMAT_getrusagediff($in_ru2, $in_ru1, $out_totaltime, $out_systime, $out_usertime);

   $rv  = "This web page was obtained from the server at ";
   $rv .= date("H:i:s", $in_time) 
          . " on "
          . date("l, ", $in_time)
          . date("F j, Y", $in_time) 
          . " (UTC " . date("O", $in_time)
          . ", server time), and required approximately " . $out_totaltime . "s CPU time (" . $out_systime . "s system, "
          . $out_usertime . "s user) to generate.&nbsp; ";
   $rv .= "Please contact <a href=\"mailto:" 
          . STDFORMAT_webmaster_email() 
          . "\">" . STDFORMAT_webmaster_name() . "</a> with any feedback about this "
          . "web page.\n";
   return($rv);
   }

//Returns the <body> HTML tag for a standard web page, which includes the
//link colors (on demand) and specification of the background to
//use.  No newline is included.
//
//The caller may optionally override the background and may also
//optionally override the link, vlink, and alink specification.
//For these specifications:
//   "" means use the default.
//   FALSE means don't specify them in the body.
//   Any other value means use that instead.
//
function STDFORMAT_body_tag($in_background, $in_link, $in_vlink, $in_alink)
   {
   $rv = "<body";

   if ($in_background === "")
      {
      //Default
      //
      $rv .= " background=\"/bkgnds/bk_garlic.jpg\"";
      }
   else if ($in_background !== FALSE)
      {
      //Use the passed specification instead.
      $rv .= (" background=\"" . $in_background . "\"");
      }
   else
      {
      //Don't include it.
      }

   if ($in_link === "")
      {
      //Default
      //
      $rv .= " link=\"#4040C0\"";
      }
   else if ($in_link !== FALSE)
      {
      //Use the passed specification instead.
      $rv .= (" link=\"" . $in_link . "\"");
      }
   else
      {
      //Don't include it.
      }

   if ($in_vlink === "")
      {
      //Default
      //
      $rv .= " vlink=\"#4040C0\"";
      }
   else if ($in_vlink !== FALSE)
      {
      //Use the passed specification instead.
      $rv .= (" vlink=\"" . $in_vlink . "\"");
      }
   else
      {
      //Don't include it.
      }

   if ($in_alink === "")
      {
      //Default
      //
      $rv .= " alink=\"#4040C0\"";
      }
   else if ($in_alink !== FALSE)
      {
      //Use the passed specification instead.
      $rv .= (" alink=\"" . $in_alink . "\"");
      }
   else
      {
      //Don't include it.
      }

   $rv .= ">";

   return($rv);
   }

//Returns the system time and user time, as strings in seconds,
//corresponding to the difference between the first getrusage()
//call and the second getrusage() call.
//
function STDFORMAT_getrusagediff($in_ru_second, $in_ru_first, &$out_totaltime, &$out_systime, &$out_usertime)
   {
   //echo "\n";
   //echo print_r($in_ru_first);
   //echo "\n";
   //echo print_r($in_ru_second);
   //echo "\n";
   
   //System time.
   //
   if ($in_ru_second['ru_stime.tv_usec'] >= $in_ru_first['ru_stime.tv_usec'])
      {
      //Can do a straight subtract with no borrow.
      $systime_secs  = $in_ru_second['ru_stime.tv_sec']  - $in_ru_first['ru_stime.tv_sec'];
      $systime_usecs = $in_ru_second['ru_stime.tv_usec'] - $in_ru_first['ru_stime.tv_usec'];
      }
   else
      {
      //Need a borrow.
      $systime_secs  = $in_ru_second['ru_stime.tv_sec']  - $in_ru_first['ru_stime.tv_sec'] - 1;
      $systime_usecs = 1000000 + $in_ru_second['ru_stime.tv_usec'] - $in_ru_first['ru_stime.tv_usec'];
      }

   $system_time_string = (string)$systime_usecs;
   while (strlen($system_time_string) < 6)
      {
      $system_time_string = "0" . $system_time_string;
      }

   $system_time_string = (string)$systime_secs . "." . $system_time_string;

   //User time.
   //
   if ($in_ru_second['ru_utime.tv_usec'] >= $in_ru_first['ru_utime.tv_usec'])
      {
      //Can do a straight subtract with no borrow.
      $usertime_secs  = $in_ru_second['ru_utime.tv_sec']  - $in_ru_first['ru_utime.tv_sec'];
      $usertime_usecs = $in_ru_second['ru_utime.tv_usec'] - $in_ru_first['ru_utime.tv_usec'];
      }
   else
      {
      //Need a borrow.
      $usertime_secs  = $in_ru_second['ru_utime.tv_sec']  - $in_ru_first['ru_utime.tv_sec'] - 1;
      $usertime_usecs = 1000000 + $in_ru_second['ru_utime.tv_usec'] - $in_ru_first['ru_utime.tv_usec'];
      }

   $user_time_string = (string)$usertime_usecs;
   while (strlen($user_time_string) < 6)
      {
      $user_time_string = "0" . $user_time_string;
      }

   $user_time_string = (string)$usertime_secs . "." . $user_time_string;

   //Total time.
   //
   $totaltime_usecs = $systime_usecs + $usertime_usecs;
   $totaltime_secs  = $systime_secs  + $usertime_secs;
   if ($totaltime_usecs >= 1000000)
      {
      $totaltime_usecs -= 1000000;
      $totaltime_secs  += 1;
      }

   $total_time_string = (string)$totaltime_usecs;
   while (strlen($total_time_string) < 6)
      {
      $total_time_string = "0" . $total_time_string;
      }

   $total_time_string = (string)$totaltime_secs . "." . $total_time_string;


   $out_totaltime = $total_time_string;
   $out_systime   = $system_time_string;
   $out_usertime  = $user_time_string;
   }

//Returns the HTML for a thin horizontal line, with no terminating newline or
//similar.
//
function STDFORMAT_hline_thin()
   {
   return("<hr size=\"1\" style=\"color:#404040\">");
   }

//Returns the HTML for a thick horizontal line, with no terminating newline or
//similar.
//
function STDFORMAT_hline_thick()
   {
   return("<hr size=\"4\" style=\"color:#404040\">");
   }

//Returns the <font> tag corresponding to the desired default font,
//with no newline.
//
function STDFORMAT_default_font_tag()
   {
   return("<font face=\"arial\">");
   }

//Returns the webmaster name as a string, with no terminating newlines
//or similar.
//
function STDFORMAT_webmaster_name()
   {
   return("David T. Ashley");
   }

//Returns the webmaster e-mail address as a string, with no terminating newlines
//or similar.
//
function STDFORMAT_webmaster_email()
   {
   return("dashley@gmail.com");
   }
?>
