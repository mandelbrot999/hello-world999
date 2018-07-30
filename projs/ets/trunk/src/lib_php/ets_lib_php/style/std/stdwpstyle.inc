<?php
require_once("style/shared/cpuusagestatclock.inc");
?>
<?php
//********************************************************************************
//Copyright (C) 2015 David T. Ashley
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
//This class defines standard styles (HTML styles, ways of doing things)
//for web or all types, including pages with static content, dynamic content,
//file upload, and calculation pages.  This class helps
//to ensure that any changes to the way of thinking about style are
//centralized in one place.
//
class StdWpStyle
   {
   var $cpu_time_clock;
      //Used to remember snapshots to calculate CPU time.

   //The constructor function.  Among other things, collects CPU usage 
   //statistics for later display.
   function StdWpStyle()
       {
       $this->cpu_time_clock = new Cpuusagestatclock;
       $this->cpu_time_clock->start();

       //Set up the timezone.
       date_default_timezone_set("America/Detroit");
       }

   //Dumps out the standard header for a static page where browser or proxy
   //caching is acceptable.  
   //The page title is what is displayed by the
   //browser, while the HTML title is what goes in big letters at the top of the
   //page.  Size and alignment should be set here, italics if necessary can be
   //put in the passed string.  The description is text below the header to 
   //say a little bit more about the page.
   function static_page_header_title_std($Pagetitle, $Htmltitle, $Desc)
      {
      echo "<html>\n";
      echo "<head>\n";
      echo "<title>" . $Pagetitle . "</title>\n";
      echo "</head>\n";
      echo "<body background=\"/bkgnds/bk_garlic.jpg\">\n";
      echo "<p align=\"center\"><b><font size=\"6\">" . $Htmltitle . "</font></b></p>\n";
      if (strlen($Desc))
	 {
         echo "<p align=\"center\"><b><font size=\"5\">(" . $Desc . ")</font></b></p>\n";
         }
      $this->static_page_hrule_std();
      }

   //Prints the message about clicking on thumbnails, plus optionally the horizontal rule.
   //$multiple_pics dictates whether the message is in the singular or plural.
   function static_page_photo_thumbnail_explanation($b_multiple_pics, $b_horizontal_rule)
      {
      if ($b_multiple_pics)
         {
         echo "<p align=\"center\">\n";
         echo "   (Click on any of the thumbnails below to view the full-sized photo.)\n";
         echo "</p>\n";
         }
      else
         {
         echo "<p align=\"center\">\n";
         echo "   (Click on the thumbnail below to view the full-sized photo.)\n";
         echo "</p>\n";
      }

      if ($b_horizontal_rule)
         {
         $this->static_page_hrule_std();
         }
      }


   //This function tallies up the used CPU time and prints out the standard footer which
   //includes this information for a static page.
   function static_page_footer_std()
      {
      $this->static_page_hrule_std();

      //Stop the cpu clock.
      $this->cpu_time_clock->stop();

      //Record a time string.
      $today = date("g:i:s a (e) \o\\n F j, Y.");

      echo "<p align=\"center\" style=\"margin-top: -2; margin-bottom: 0\">\n";
      echo "   <font size=\"2\">\n";
      echo "      Local time on the server (at the time this page was served) is "
           .      $today
           .      "&nbsp;\n";
      echo "      " . $this->cpu_time_clock->std_web_page_cpu_time_usage_footer() . "&nbsp;\n";
      echo "      This page is maintained by <a href=\"mailto:dashley@gmail.com\">David T. Ashley</a>.\n";

      echo "   </font>\n";
      echo "</p>\n";
      echo "<hr noshade size=\"5\">\n";
      echo "</body>\n";
      echo "</html>\n";
      }


   //Dumps out the standard horizontal rule for separating sections for a static page.  The rule for
   //hacking up functionality is that the page application is responsible to use these
   //rules except first after the header and last before the footer.
   function static_page_hrule_std()
      {
      echo "<hr>\n";
      } 
   }
?>
