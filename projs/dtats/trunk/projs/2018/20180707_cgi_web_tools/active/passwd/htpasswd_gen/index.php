<?php
require_once("style/std/stdwpstyle.inc");
//----------------------------------------------------------------------------------------------------
//Copyright (c) 2003, 2018 David T. Ashley.
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
//
function do_header(&$style)
   {
   $style->static_page_header_title_std("HTPASSWD-Style Hashed Password Generator",
			  "<i>htpasswd</i>-Style Hashed Password Generator",
			  "");
   echo "<p align=\"center\"><b><font size=\"3\">(This cgi-bin form generates password hashes which are \n";
   echo "understood by the <i>Apache</i> web server in directory access files and also by \n";
   echo "the <i>CVS</i> version control system when such entries are placed in the \n";
   echo "<i>CVSROOT/passwd</i> file. &nbsp;The algorithm used is the standard DES algorithm with \n";
   echo "randomly selected two-character salt. &nbsp;To use this password hash generator, \n";
   echo "you must normally paste the output into an <i>Apache</i> directory access file or into \n";
   echo "the <i>CVSROOT/passwd</i> file of a <i>CVS</i> repository.)</font></b></p>\n";
   $style->static_page_hrule_std();  
   echo "<p align=\"center\"><font size=\"3\" color=\"#FF0000\"><b>WARNING:</b>&nbsp; The username and ";
   echo "password you choose are ";
   echo "transmitted over the network to the server unencrypted and can be intercepted.&nbsp; ";
   echo "Use this utility ";
   echo "at your own risk.</font></p>\n";
   $style->static_page_hrule_std();  
   }  

function do_footer(&$style)
   {
   $style->static_page_footer_std();
   }

function do_form($Buttontext)
   {
   echo "<form method=post action=\"index.php\" width=\"100%\">\n";
   echo "<table align=\"center\">\n";
   echo "<tr>\n";
   echo "  <td width=\"10%\">\n";
   echo "   <p align=\"right\"><b>Username</b> (required):</td>\n";
   echo "    <td width=\"12%\"><p align=\"left\"><input type=\"text\" name=\"Username\" size=\"30\"></p></td>\n";
   echo "  </tr>\n";
   echo "  <tr>\n";
   echo "    <td width=\"10%\">\n";
   echo "   <p align=\"right\"><b>Password</b> (required):</td>\n";
   echo "    <td width=\"12%\"><p align=\"left\"><input type=\"Password\" name=\"Password\" size=\"30\"></p></td>\n";
   echo "  </tr>\n";
   echo "  <tr>\n";
   echo "    <td width=\"20%\" colspan=\"2\">\n";
   echo "      <p align=\"center\"><input type=\"submit\" value=\"";
   echo $Buttontext;
   echo "\" name=\"B1\" style=\"margin-top: 12\"></td>\n";
   echo "  </tr>\n";
   echo "</table>\n";
   echo "</form>\n";
}

function do_err_msg($Err_msg)
   {
   echo "<p align=\"center\"><b><font color=\"#FF0000\">";
   echo $Err_msg;
   echo "</font></b></p>\n";
   }

function random_salt()
   {
   //There are 64 possible values for each salt character, a-z, A-Z, 0-9, ., and /.
   //Can easily generate a suitably random value.
   $Matchstring = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";
   $Rand1 = rand(0,63);
   $Rand2 = rand(0,63);
   return(Substr($Matchstring, $Rand1, 1) . Substr($Matchstring, $Rand2, 1));
   }

//Main script begins here.
//
//
$style = new StdWpStyle;
//Assign the current style in force.  Also, starts the CPU
//usage clock.

//Do the header unconditionally.  The header is always used on this page.
do_header($style);
//
if (isset($_POST['Username']))
   $Username = $_POST['Username'];
//
if (isset($_POST['Password']))
   $Password = $_POST['Password'];

//Load up a few variables based on what username and password values were supplied.
if (isset($Username) && isset($Password))
   {
   $Usernamelen = strlen($Username);
   $Usernamevalid = 1;
   for ($i=0; $i<$Usernamelen; $i++)
      {
      $Curchar = Substr($Username, $i, 1);
      $Ord = ord($Curchar);
      if (!
            (
	       ($Ord >= ord("A") && $Ord <= ord("Z"))
               ||
	       ($Ord >= ord("a") && $Ord <= ord("z"))
               ||
	       ($Ord >= ord("0") && $Ord <= ord("9"))
            )
         )
	 {
	 $Usernamevalid = 0;
	 }
      }

   $Passwordlen = strlen($Password);
   $Passwordvalid = 1;
   for ($i=0; $i<$Passwordlen; $i++)
      {
      $Curchar = Substr($Password, $i, 1);
      $Ord = ord($Curchar);
      if (!
            (
	       ($Ord >= ord("A") && $Ord <= ord("Z"))
               ||
	       ($Ord >= ord("a") && $Ord <= ord("z"))
               ||
	       ($Ord >= ord("0") && $Ord <= ord("9"))
               ||
               ($Ord == ord("/"))
               ||
	       ($Ord == ord("."))
            )
         )
	 {
	 $Passwordvalid = 0;
	 }
      }

   }
//
//There are a few cases to break into here, and this affects the overall layout of the page.
//The header and footer are fixed, but the "guts" will change.
if (!isset($Username) || !isset($Password))
   {
   //In this case, we are probably visiting the form for the first time, and have not done a submit.
   //Just display the form itself.
   do_form("Click To Generate Hashed Password");
   }
elseif ($Usernamelen < 1 || !$Usernamevalid)
   {
   //The user name is suspicious.  Must flag it.
     do_err_msg("The <i>Username</i> you supplied is not valid. &nbsp;User names must contain at least one character and may consist only of lower-case and upper-case letters and digits. &nbsp;Please try again.");
     $style->hrule_std();  
     do_form("Click To Generate Hashed Password");
   }
elseif ($Passwordlen < 2 || !$Passwordvalid)
   {
   //The password is suspicious.  Must flag it.
   do_err_msg("The <i>Password</i> you supplied is not valid. &nbsp;Passwords must contain at least two characters and may consist only of lower-case and upper-case letters and digits and the \"/\" and \".\" characters. &nbsp;Please try again.");
   $style->static_page_hrule_std();  
   do_form("Click To Generate Hashed Password");
   }
else
   {
   //Username and password seem within minimums.  Should be clear to generate hashed password.
   $Hashedpwd = crypt($Password, random_salt());
   echo "<p align=\"left\">The hashed username/password is:</p>\n";
   echo "<p align=\"left\"><font size=\"5\">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>";
   echo $Username;
   echo ":";
   echo $Hashedpwd;
   echo "</b></font></p>\n";
   echo "<p align=\"left\">You may paste this value directly into an <i>Apache</i> directory \n";
   echo "access file or <i>CVS</i> <i>CVSROOT/passwd</i> file.  Note that if the period (\".\") \n";
   echo "character or other punctuation appears as the last character(s) of the hash above, \n";
   echo "it <i>is</i> part of the hash and \n";
   echo "must be included when copying and pasting.</p>\n";
   $style->static_page_hrule_std();  
   do_form("Click To Generate Another Hashed Password");
   }

//Now do the footer unconditionally.  The footer is always used on this web page.
do_footer($style);  
?>
