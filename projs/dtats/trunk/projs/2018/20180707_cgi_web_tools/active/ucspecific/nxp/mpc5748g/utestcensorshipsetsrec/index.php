<?php
require_once("style/std/stdwpstyle.inc");
//----------------------------------------------------------------------------------------------------
//This program calculates an S-record file that can be used to append to the UTEST area of the NXP MPC
//5748G and will disable censorship.  This program is provided by David T. Ashley (dashley@gmail.com)
//under the MIT License (reproduced immediately below).
//----------------------------------------------------------------------------------------------------
//Copyright (c) 2018 David T. Ashley.
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.
//----------------------------------------------------------------------------------------------------
//Note to self:  On 7/3/2018, I wrote Richard Stallman to inquire about what I should put in CGI
//               output to protect myself from liability (like all software, CGI-BIN programs
//               can contain bugs).  If I don't hear back from Mr. Stallman within a a few weeks,
//               I will have to take my best guess.
//----------------------------------------------------------------------------------------------------
//This program processes the following GET/POST parameters (GET and POST are treated identically):
//   mode
//      0 or not defined 0
//         Display the basic screen with choices of what to do.
//      1
//         Display full instructions about how to modify the UTEST area to enable censorship.
//      2
//         Calculate the correct S-record to modify UTEST.
//      3
//         View the source code for this program.
//      4
//         Provide feedback (a bit of a gag).
//   addrhex
//      A hexadecimal string specifying the starting address at which the UTEST programming should
//      be done.  Leading 0's will be removed, and lower-case and upper-case letters are treated
//      identically.  An empty string, a string containing unrecognized characters, or a string
//      specifying a value outside [0, 2^32-256] will result in an error message.  (By the way,
//      the "256" margin is to avoid any part of the S-record specification exceeding [0, 2^32-1].
//----------------------------------------------------------------------------------------------------

function home_link_paragraph()
{
   echo "<p align=\"center\">\n";
   echo "   Click <a href=\"index.php\">here</a> to return to the home choices screen.\n";
   echo "</p>\n";
}

function screen_bad_mode($in_page_title)
{
   $thispage = new StdWpStyle();

   $thispage->static_page_header_title_std($in_page_title,
                                           $in_page_title,
                                           "");

   echo "<p align=\"center\">\n";
   echo "   The <i>mode</i> HTTP POST/GET parameter was invalid.\n";
   echo "</p>";

   $thispage->static_page_hrule_std();

   home_link_paragraph();

   $thispage->static_page_footer_std();
}

function screen_bad_addr($in_page_title)
{
   $thispage = new StdWpStyle();

   $thispage->static_page_header_title_std($in_page_title,
                                           $in_page_title,
                                           "");

   echo "<p align=\"center\">\n";
   echo "   The <i>addr</i> HTTP POST/GET parameter was invalid.\n";
   echo "</p>";

   $thispage->static_page_hrule_std();

   home_link_paragraph();

   $thispage->static_page_footer_std();
}

function screen_select($in_page_title)
{
   $thispage = new StdWpStyle();

   $thispage->static_page_header_title_std($in_page_title,
                                           $in_page_title,
                                           "");

   echo "<p>\n";
   echo "<form action=\"index.php\">\n";
   echo "<input type=\"radio\" name=\"mode\" value=\"0\" checked>&nbsp;Display available choices (this screen).<br>\n";
   echo "<input type=\"radio\" name=\"mode\" value=\"1\">&nbsp;Display full instructions for Clearing PASS_LCSTAT.CNS.<br>\n";
   echo "<input type=\"radio\" name=\"mode\" value=\"2\">&nbsp;Calculate an S-record File to Add a DCF Record\n";
   echo "to the UTEST Area Starting at Address\n";
   echo "0x<input type=\"text\" name=\"addr\" value=\"0\"> in Order to Clear PASS_LCSTAT.CNS.<br>\n";
   echo "<input type=\"radio\" name=\"mode\" value=\"3\">&nbsp;Display the source code for this page.<br>\n";
   echo "<input type=\"radio\" name=\"mode\" value=\"4\">&nbsp;Provide feedback on this page.<br><br>\n";
   echo "<input type=\"submit\" value=\"Take Action Specified Above ...\">\n";
   echo "</form>\n";
   echo "</p>";

   $thispage->static_page_footer_std();
}

function screen_instructions($in_page_title)
{
   $preamble = array
   (
      "<p>",
      "This page contains the instructions for clearing the PASS_LCSTAT.CNS bit, which is one",
      "prerequisite for the GHS probe working correctly across low-power modes.",
      "</p>"
   );
   
   $step01 = array
   (
      "<p>",
      "<b><u>Step 1:  Install the Latest GHS Tools</u></b>",
      "</p>",
      "<p>",
      "Tool updates are typically made available by GHS in the form of ISO images",
      "that can be downloaded from the GHS support website (<i>support.ghs.com</i>, screen",
      "snapsot below).&nbsp; A valid license and login are required.",
      "</p>",
      "<p align=\"center\">",
      "<img src=\"comp_2018_1_4_final_release.png\">",
      "</p>",
      "<p>",
      "Once a DVD has been produced from the ISO image, three installations are typically",
      "required&mdash;the compiler, the debugger, and the license administrator.&nbsp;",
      "Typically, so that different versions of the same tool can coexist and so that",
      "all developers on a team have tools in exactly the same place, there is a",
      "local policy about the exact paths that must be used for installation.",
      "</p>"
   );

   $step02 = array
   (
      "<p>",
      "<b><u>Step 2:  Re-FLASH the GHS Probe</u></b>",
      "</p>",
      "<p>",
      "After the newest version of the GHS software has been installed (Step 1, above), the most recent",
      "GHS Probe firmware should be in a <i>.frm</i> file in the compiler installation directory.&nbsp;",
      "Use the Probe Administrator to re-FLASH the GHS Probe with this firmware.",
      "</p>",
      "<p>",
      "Verify that the correct updated firmware has been FLASH'd using the <i>target support</i>",
      "command from within the debugger.  As of this writing, the expected information would be:",
      "</p>",
      "<p>",
      "<pre>",
      "MULTI&gt; target support",
      "*************************** Firmware Info ****************************",
      "",
      "Probe Firmware Release Version 5.6.4",
      "</pre>",
      "</p>"
   );

   $step03 = array
   (
      "<p>",
      "<b><u>Step 3:  Check that PASS_LCSTAT[CNS] is 1</u></b>",
      "</p>",
      "<p>",
      "(If it isn't 1, there is no need to write a new DCF record.)",
      "</p>",
      "<p>",
      "Using the debugger, run the application software for a second or two and stop it",
      "(all that matters is that the part has made it out of reset).",
      "</p>",
      "<p align=\"center\">",
      "<img src=\"pass_lcstat_in_debugger_value_1.png\">",
      "</p>",
      "<p>",
      "The debugger output with CNS == 1 is shown above.  If CNS == 1, you have to",
      "write a new DCF record.  If CNS == 0, you can skip all other steps in this e-mail.",
      "</p>"
   );

   $step04 = array
   (
      "<p>",
      "<b><u>Step 4:  Identify the Address Where the New DCR Record Should Be Written</u></b>",
      "</p>",
      "<p>",
      "This step is necessary because not all modules are guaranteed to have the",
      "same number of DCF records.&nbsp; Because DCF records can only be appended,",
      "the address at which a write is required may vary from module to module.",
      "</p>",
      "<p>",
      "The DCF records, each one 64 bits, are processed by the hardware as part",
      "of the RESET process.&nbsp; It is a linear search through FLASH, ending when",
      "a record is found where the least significant bit is 1 (which would be the",
      "case with erased FLASH).",
      "</p>",
      "<p>",
      "You are not free to write the DCF record anywhere (because of the linear",
      "search, you must append it to the last valid DCF record).&nbsp; Also, the",
      "hardware won't allow you to erase existing DCF records&mdash;you can only",
      "append by programming.&nbsp; DCF record programming mistakes can often be",
      "corrected by adding another DCF record writing a register to a different",
      "value (but this is not universally true for all registers).",
      "</p>",
      "<p>",
      "From Table 3-3 in the reference manual:",
      "</p>",
      "<p align=\"center\">",
      "<img src=\"rm_table_3_3.png\">",
      "</p>",
      "<p>",
      "The start address at which you need to write the new DCF record will be",
      "DWORD aligned (address will be a multiple of 8), and somewhere in the range",
      "of 0x00400348 through 0x00400FF8.",
      "</p>",
      "<p>",
      "Using a debugger, examine the UTEST area to find the first 0xFFFFFFFF",
      "(unprogrammed) location.",
      "</p>",
      "<p>",
      "The image below is the UTEST FLASH contents before I programmed the new",
      "DCF record.&nbsp; You can see that 0x400638 is the location at which the new",
      "DCF record must be written.",
      "</p>",
      "<p align=\"center\">",
      "<img src=\"utest_flash_before.png\">",
      "</p>"
   );

   $step05 = array
   (
      "<p>",
      "<b><u>Step 5:  Prepare an S-Record File Specifying the New DCF Record</u></b>",
      "</p>",
      "<p>",
      "The S-Record file I prepared is this one:",
      "</p>",
      "<p>",
      "<pre>",
      "S011000000486578766965772056312E3039D0",
      "S20C400638000055AA001000B0B6",
      "S804FFFFFFFE",
      "</pre>",
      "</p>",
      "<p>",
      "Note that the address to write is embedded in the S19 file,",
      "<i>400638</i>.&nbsp;  (That is why the S19 file you have to use may be different than the",
      "example provided above.)",
      "</p>",
      "<p>",
      "The bytes to write must be, in order:",
      "</p>",
      "<p>",
      "<pre>",
      "00 00 55 AA 00 10 00 B0",
      "</pre>",
      "</p>",
      "<p>",
      "These set <i>Censorship</i> to <i>Uncensored</i>.",
      "</p>",
      "<p>",
      "This set of web pages provides a web-based calculator that can be used",
      "to calculate an appropriate S19 file.",
      "</p>",
      "<p>",
      "Although it can easily be done, I don't recommend &quot;hand-rolling&quot; an S19 file",
      "(for example, by editing the text above).&nbsp;  The issue is that there is a checksum at",
      "the end, and I don't know for sure how the GHS tools will react if that is invalid",
      "(an invalid checksum would be a natural mistake when preparing an S19 manually).",
      "</p>",
      "<p>",
      "Double-check the S19 file to be sure that it covers only the addresses",
      "you wish to program.&nbsp; In my S19 file:",
      "</p>",
      "<p>",
      "<pre>",      
      "S20C 400638 <b><u>000055AA001000B0</u></b> B6",
      "</pre>",
      "</p>",
      "<p>",
      "the payload is underlined.&nbsp; If there are more or less than 8 bytes",
      "specified, you've done something wrong.&nbsp; Also, if the last digit of the address is",
      "not a 0 or an 8, you've done something wrong.",
      "</p>"
   );


   $step06 = array
   (
      "<p>",
      "<b><u>Step 6:  Program the UTEST Area</u></b>",
      "</p>",
      "<p>",
      "The instructions below were provided by a GHS employee.&nbsp; I've reproduced them verbatim (in <i>italics</i>).",
      "</p>",
      "<p><i>",
      "DCFs are 64 bits, and are evaluated by the CPU in order until an invalid record is found.&nbsp; Changing",
      "CNS requires a single new DCF entry at the end of the list.&nbsp; Our flashing tools are somewhat",
      "big for this use case of programming only a few words at a time. Some options for programming",
      "are (in no particular order):",
      "<ul>",
         "<li>",
            "Use the flash programming GUI. This requires one of:",
            "<ul>",
               "<li>",
                  "(a) A raw binary file, OR",
               "</li>",
               "<li>",
                  "(b) an SREC file containing the new DCF record.",
               "</li>",   
            "</ul>",
         "</li>",
      "</ul>",
      "</p>",
      "<p>",
      "The programming address must be the next empty DCF slot in UTEST for",
      "(a) this is specified in the flash GUI; for (b) the address is built",
      "in to the SREC format.&nbsp; You must select a <i>.mbs</i> that allows",
      "downloading to and running code from RAM.&nbsp; All the usual flash GUI",
      "parameters must be set, with an additional",
      "&amp;modify_utest=1 appended to the flash bank parameter to allow u-test access.",
      "</i>",
      "</p>",
      "<p>",
      "The screenshot below shows the choices that I made in the FLASH programming GUI",
      "that I made per GHS instructions.&nbsp;  Changes from normal program FLASH programming:&nbsp;",
      "(a) Addition of &amp;modify_utest=1,",
      "(b) custom S-record file specified, and (c) <i>Erase</i> unchecked.",
      "</p>",
      "<p align=\"center\">",
      "<img src=\"flash_programming.png\">",
      "</p>",
      "<p>",
      "When programming the FLASH, there should be no error messages.",
      "</p>"
   );

   $step07 = array
   (
      "<p>",
      "<b><u>Step 7:  Verify the UTEST Program Operation</u></b>",
      "</p>",
      "<p>",
      "Run the application under the debugger and examine memory.&nbsp; In my case (screenshot below), the program",
      "at 0x400638 was successful.",
      "<p align=\"center\">",
      "<img src=\"utest_after_programming.png\">",
      "</p>"
   );

   $step08 = array
   (
      "<p>",
      "<b><u>Step 8:  Verify that PASS_LCSTAT[CNS] is 0</u></b>",
      "</p>",
      "<p>",
      "Run the application, stop it and examine the PASS module.  Below, CNS is 0, which is the desired outcome.",
      "</p>",
      "<p align=\"center\">",
      "<img src=\"pass_lcstat_in_debugger.png\">",
      "</p>",
      "<p>",
      "Debugging through STANDBY and STOP should now work.",
      "</p>"
   );

   $full_instructions = array
   (
      $preamble,
      $step01,
      $step02,
      $step03,
      $step04,
      $step05,
      $step06,
      $step07,
      $step08
   );

   $thispage = new StdWpStyle();

   $thispage->static_page_header_title_std($in_page_title,
                                           $in_page_title,
                                           "");

   //For each group of content.
   for ($i = 0; $i < count($full_instructions); $i++)
   {
      $group = $full_instructions[$i];

      //For each line in the content.
      for ($j = 0; $j < count($group); $j++)
      {
         echo $group[$j] . "\n";
      }

   $thispage->static_page_hrule_std();
   }

   home_link_paragraph();

   $thispage->static_page_footer_std();
}

function screen_s_record($in_page_title, $in_addr_array)
{
   $thispage = new StdWpStyle();

   $thispage->static_page_header_title_std($in_page_title,
                                           $in_page_title,
                                           "");

   echo "<p align=\"center\">\n";
   echo "The S-record file to program the DCF record at address 0x"
        . sprintf("%02X%02X%02X%02X", $in_addr_array[0], $in_addr_array[1], $in_addr_array[2], $in_addr_array[3]) .
	" is below.&nbsp;\n";
   echo "This can be pasted into an appropriate programming tool.\n";
   echo "</p>";

   $thispage->static_page_hrule_std();

   echo "<pre>\n";

   //The first line, I believe, can be left as a constant.
   echo "S011000000486578766965772056312E3039D0\n";

   //The second line is more complex.
   $checksum = 0;
   $payload = array(0x00, 0x00, 0x55, 0xAA, 0x00, 0x10, 0x00, 0xB0);

   if (($in_addr_array[0] == 0) && ($in_addr_array[1] == 0))
   {
      //S1 record, 2-byte address.
      echo "S1";
      $count = 2 + count($payload) + 1;
      echo sprintf("%02X", $count);
      $checksum += $count;
      echo sprintf("%02X", $in_addr_array[2]);
      $checksum += $in_addr_array[2];
      echo sprintf("%02X", $in_addr_array[3]);
      $checksum += $in_addr_array[3];
   }
   else if ($in_addr_array[0] == 0)
   {
      //S2 record, 3-byte address.
      echo "S2";
      $count = 3 + count($payload) + 1;
      echo sprintf("%02X", $count);
      $checksum += $count;
      echo sprintf("%02X", $in_addr_array[1]);
      $checksum += $in_addr_array[1];
      echo sprintf("%02X", $in_addr_array[2]);
      $checksum += $in_addr_array[2];
      echo sprintf("%02X", $in_addr_array[3]);
      $checksum += $in_addr_array[3];
   }
   else
   {
      //S3 record, 3-byte address.
      echo "S3";
      $count = 4 + count($payload) + 1;
      echo sprintf("%02X", $count);
      $checksum += $count;
      echo sprintf("%02X", $in_addr_array[0]);
      $checksum += $in_addr_array[0];
      echo sprintf("%02X", $in_addr_array[1]);
      $checksum += $in_addr_array[1];
      echo sprintf("%02X", $in_addr_array[2]);
      $checksum += $in_addr_array[2];
      echo sprintf("%02X", $in_addr_array[3]);
      $checksum += $in_addr_array[3];
   }

   //Emit the payload bytes, maintaining the checksum.
   for ($i=0; $i<count($payload); $i++)
   {
      echo sprintf("%02X", $payload[$i]);
      $checksum += $payload[$i];
   }

   //Adjust the checksum.  Because integers in PHP are 32-bit signed,
   //I need to be careful how I calculate the 1's complement, so as not
   //to create a negative number.
   $checksum %= 256;              //Checksum now in [0, 255].
   $checksum = 255 - $checksum;   //Checksum still in [0, 255].

   //Emit the checksum.
   echo sprintf("%02X", $checksum);
   
   echo "\n";
   //echo "S20C400638000055AA001000B0B6\n";

   //The last line, I believe, can be left as a constant.
   echo "S804FFFFFFFE\n";

   echo "</pre>\n";

   $thispage->static_page_hrule_std();

   home_link_paragraph();

   $thispage->static_page_footer_std();
}

function screen_source($in_page_title)
{
   $thispage = new StdWpStyle();

   $thispage->static_page_header_title_std($in_page_title,
                                           $in_page_title,
                                           "");

   echo "<p align=\"center\">\n";
   echo "The page source code is provided below.\n";
   echo "</p>";

   $thispage->static_page_hrule_std();

   echo "<pre>\n";
   
   $source_file_contents = file("index.php");

   for ($i=0; $i<count($source_file_contents); $i++)
   {
      $line = $source_file_contents[$i];

      if (strlen($line) > 0)
      {
         if (substr($line, strlen($line)-1, 1) == "\n")
	 {
	    $line = substr($line, 0, strlen($line)-1);
	 }
	 else
	 {
	 }
	 
         echo htmlspecialchars($line) . "\n";
      }
      else
      {
         echo "\n";
      }
   }

   echo "</pre>\n";

   $thispage->static_page_hrule_std();

   home_link_paragraph();

   $thispage->static_page_footer_std();
}

function screen_feedback($in_page_title)
{
   $thispage = new StdWpStyle();

   $thispage->static_page_header_title_std($in_page_title,
                                           $in_page_title,
                                           "");

   echo "<p align=\"center\">\n";
   echo "I do not care about your opinion.&nbsp; Keep your feedback to yourself, and do not trouble me with it.\n";
   echo "</p>";

   $thispage->static_page_hrule_std();

   home_link_paragraph();

   $thispage->static_page_footer_std();
}

//Output HTTP header info before any other output.  This should
//hopefully prevent any browser or proxy caching.
header("Expires: Tue, 03 Jul 2001 06:00:00 GMT");
header("Last-Modified: " . gmdate("D, d M Y H:i:s") . " GMT");
header("Cache-Control: no-store, no-cache, must-revalidate, max-age=0");
header("Cache-Control: post-check=0, pre-check=0", false);
header("Pragma: no-cache");
header("Connection: close");

//Constants, not quite properly declared.
$page_title = "NXP MPC5748G PASS_LCSTAT.CNS-Clearing UTEST DCF Record S-Record Generation Utility";

//Start off believing no errors.  Parameters are normalized.  Errors are a
//different matter.
$error_bad_mode    = False;
$error_bad_addr    = False;
$status_mode_found = False;
$status_addr_found = False;

//Set the $in_mode parameter based on POST/GET input.  POST gets preference.
if (isset($_POST['mode']))
{
   $in_mode = $_POST['mode'];
   $status_mode_found = True;
}
else if (isset($_GET['mode']))
{
   $in_mode = $_GET['mode'];
   $status_mode_found = True;
}
else
{
   $in_mode = "0";
}

//Normalize $in_mode to be an integer [0, 4].  Anything unrecognized
//gets the value 0 and is an error.
if (is_numeric($in_mode))
{
   $in_mode = (int)$in_mode;
}
else
{
   $in_mode = 0;
   $error_bad_mode = True;
}

if (($in_mode < 0) || ($in_mode > 4))
{
   $in_mode = 0;
   $error_bad_mode = True;
}

//Normalize addrhex.  Because a PHP integer is a signed 32-bit integer (not large enough), normalize
//to be a string exactly 8 characters long, consisting of only digits and upper-case letters.
if (isset($_POST['addr']))
{
   $in_addr = $_POST['addr'];
   $status_addr_found = True;
}
else if (isset($_GET['addr']))
{
   $in_addr = $_GET['addr'];
   $status_addr_found = True;
}
else
{
   $in_addr = "0";
}

//Trim the string of leading and trailing whitespace.
$in_addr = trim($in_addr);

//Trim any leading 0's, but leave the final character.
while ((strlen($in_addr) > 1) && (substr($in_addr, 0, 1) == "0"))
{
   $in_addr = substr($in_addr, 1, strlen($in_addr)-1);
}

//If the string is the empty string, it is bogus.
if (strlen($in_addr) == 0)
{
   $in_addr = "0";
   $error_bad_addr = True;
}

//If it is less than 8 characters, left-pad it.
while (strlen($in_addr) < 8)
{
   $in_addr = "0" . $in_addr;
}

//If the string is not 8 characters, it is bogus.
if (strlen($in_addr) != 8)
{
   $in_addr = "00000000";
   $error_bad_addr = True;
}

//Convert any lower-case letters to upper-case letters.
$in_addr = strtoupper($in_addr);

//Every character in the string at this point has to be in
//"0123456789ABCDEF" or the string is bogus.
for ($i=0; $i<strlen($in_addr); $i++)
{
   $c = substr($in_addr, $i, 1);

   if (strpos("0123456789ABCDEF", $c) === False)
   {
      $in_addr = "00000000";
      $error_bad_addr = True;
      break;
   }
}

//Convert the character-based address to an array of 4
//bytes.
for ($i=0; $i<4; $i++)
{
   $in_addr_array[$i] = strpos("0123456789ABCDEF", substr($in_addr, $i*2,   1)) * 16
                      + strpos("0123456789ABCDEF", substr($in_addr, $i*2+1, 1));
}

//Decide exactly what to do based on the parsed POST/GET parameters.
if ($error_bad_mode)
{
   screen_bad_mode($page_title);
}
else if ($status_addr_found && $error_bad_addr)
{
   screen_bad_addr($page_title);
}
else if ($in_mode == 0)
{
   screen_select($page_title);
}
else if ($in_mode == 1)
{
   screen_instructions($page_title);
}
else if ($in_mode == 2)
{
   screen_s_record($page_title, $in_addr_array);
}
else if ($in_mode == 3)
{
   screen_source($page_title);
}
else if ($in_mode == 4)
{
   screen_feedback($page_title);
}
else
{
   screen_bad_mode();
}
?>