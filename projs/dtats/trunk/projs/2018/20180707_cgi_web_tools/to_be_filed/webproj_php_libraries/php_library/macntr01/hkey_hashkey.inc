<?php
//------------------------------------------------------------------------
//Marshall Aviation Center FBO Management Software
//Copyright (C)2005 David T. Ashley
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
//
//The author (David T. Ashley) may be contacted by e-mail at dta@e3ft.com
//and by postal mail at P.O. Box 918, Marshall MI 49068.
//------------------------------------------------------------------------
//This file contains the hash key.  The hash key is dozens to hundreds 
//of characters of semi-randomness to use in forming MD5 hashes and other
//digests.
//
//Generally speaking, the hash key can't be changed once a site is in
//operation;  as this would invalidate all stored hashes (such as
//hashes used for passwords).
//
//------------------------------------------------------------------------
//Returns the hash key.
//
function hkey_hkey()
   {
   return(
            "hdfnviadf 1243751478176ldsflkbvkls  lskdhfthequickbrownfoxjumpedoverthe" .
            "NaseEieeFuesseAugenOhrenFingerHaende3141519336743132695709719burpbelchi" .
            "practicalhand-to-handcombatforthepoliceofficerwithC.J.CaracciAcopwillpu" .
            "thishandsoncriminalsfarmoreoftenthanhe'lldrawhisweapon,sohemustknowthep" .
            "ractical, straightforward grappling, overpowering, and arresing techniq" .
            "ues in the film to get the job done safely and effectively.772134961234"
         );
   }

//------------------------------------------------------------------------
?>
