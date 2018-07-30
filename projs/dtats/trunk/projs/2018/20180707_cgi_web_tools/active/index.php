<?php
require_once("style/std/stdwpstyle.inc");
?>
<?php
   $thispage = new StdWpStyle();

   $thispage->static_page_header_title_std("Server-Based (CGI) Calculators and Utilities",
                                           "Server-Based (CGI) Calculators and Utilities",
                                           "");
?>

<p align="center">
   This page contains calculators and utilities that run on the server side (CGI).
</p>

<?php
   $thispage->static_page_hrule_std();
?>

<p>
   <ul>
      <li>
         Microcontroller-Specific
	 <ul>
	    <li>
	       NXP	    
	       <ul>
	          <li>
		     MPC5748G
		     <ul>
		        <li>
		           <a href="ucspecific/nxp/mpc5748g/utestcensorshipsetsrec/">NXP MPC5748G PASS_LCSTAT.CNS-Clearing UTEST DCF Record S-Record Generation Utility</a>
			</li>
		     </ul>
		  </li>
	       </ul>
	    </li>
	 </ul>
      </li>
      <li>
         Number Theory
	 <ul>
	    <li>
	       <a href="num_theory/euclid_gcd/">GCD of Two Integers (Euclid's Algorithm)</a>
	    </li>
	    <li>
	       <a href="num_theory/miller_rabin/">Miller-Rabin Probable Primality Test</a>
	    </li>
	    <li>
	       <a href="num_theory/pfact18digit/">Prime Factorization of Integer (Sieve of Eratosthenes, 18 or Fewer Digits)</a>
	    </li>
	 </ul>
      </li>
      <li>
         Password Generation
	 <ul>
	    <li>
	       <a href="passwd/htpasswd_gen/"><i>htpasswd</i>-Style Hashed Password Generator</a>
	    </li>
	 </ul>
      </li>
   </ul>
</p>

<?php
   $thispage->static_page_footer_std();
?>
