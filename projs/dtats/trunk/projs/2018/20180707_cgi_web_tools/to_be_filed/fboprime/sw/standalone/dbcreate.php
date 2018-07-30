#!/usr/bin/php -q
<?php
//$Header: /home/dashley/cvsrep/e3ft_gpl01/e3ft_gpl01/webprojs/fboprime/sw/standalone/dbcreate.php,v 1.31 2006/11/05 18:26:05 dashley Exp $
//--------------------------------------------------------------------------------
//dbcreate.php--Creates The FBO-Prime Database (Unpopulated)
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
//-------------------------------------------------------------------------------------------------
//Copyright 2006 David T. Ashley
//-------------------------------------------------------------------------------------------------
//This source code and any program in which it is compiled/used is provided under the GNU GENERAL
//PUBLIC LICENSE, Version 3, full license text below.
//-------------------------------------------------------------------------------------------------
//                    GNU GENERAL PUBLIC LICENSE
//                       Version 3, 29 June 2007
//
// Copyright (C) 2007 Free Software Foundation, Inc. <http://fsf.org/>
// Everyone is permitted to copy and distribute verbatim copies
// of this license document, but changing it is not allowed.
//
//                            Preamble
//
//  The GNU General Public License is a free, copyleft license for
//software and other kinds of works.
//
//  The licenses for most software and other practical works are designed
//to take away your freedom to share and change the works.  By contrast,
//the GNU General Public License is intended to guarantee your freedom to
//share and change all versions of a program--to make sure it remains free
//software for all its users.  We, the Free Software Foundation, use the
//GNU General Public License for most of our software; it applies also to
//any other work released this way by its authors.  You can apply it to
//your programs, too.
//
//  When we speak of free software, we are referring to freedom, not
//price.  Our General Public Licenses are designed to make sure that you
//have the freedom to distribute copies of free software (and charge for
//them if you wish), that you receive source code or can get it if you
//want it, that you can change the software or use pieces of it in new
//free programs, and that you know you can do these things.
//
//  To protect your rights, we need to prevent others from denying you
//these rights or asking you to surrender the rights.  Therefore, you have
//certain responsibilities if you distribute copies of the software, or if
//you modify it: responsibilities to respect the freedom of others.
//
//  For example, if you distribute copies of such a program, whether
//gratis or for a fee, you must pass on to the recipients the same
//freedoms that you received.  You must make sure that they, too, receive
//or can get the source code.  And you must show them these terms so they
//know their rights.
//
//  Developers that use the GNU GPL protect your rights with two steps:
//(1) assert copyright on the software, and (2) offer you this License
//giving you legal permission to copy, distribute and/or modify it.
//
//  For the developers' and authors' protection, the GPL clearly explains
//that there is no warranty for this free software.  For both users' and
//authors' sake, the GPL requires that modified versions be marked as
//changed, so that their problems will not be attributed erroneously to
//authors of previous versions.
//
//  Some devices are designed to deny users access to install or run
//modified versions of the software inside them, although the manufacturer
//can do so.  This is fundamentally incompatible with the aim of
//protecting users' freedom to change the software.  The systematic
//pattern of such abuse occurs in the area of products for individuals to
//use, which is precisely where it is most unacceptable.  Therefore, we
//have designed this version of the GPL to prohibit the practice for those
//products.  If such problems arise substantially in other domains, we
//stand ready to extend this provision to those domains in future versions
//of the GPL, as needed to protect the freedom of users.
//
//  Finally, every program is threatened constantly by software patents.
//States should not allow patents to restrict development and use of
//software on general-purpose computers, but in those that do, we wish to
//avoid the special danger that patents applied to a free program could
//make it effectively proprietary.  To prevent this, the GPL assures that
//patents cannot be used to render the program non-free.
//
//  The precise terms and conditions for copying, distribution and
//modification follow.
//
//                       TERMS AND CONDITIONS
//
//  0. Definitions.
//
//  "This License" refers to version 3 of the GNU General Public License.
//
//  "Copyright" also means copyright-like laws that apply to other kinds of
//works, such as semiconductor masks.
//
//  "The Program" refers to any copyrightable work licensed under this
//License.  Each licensee is addressed as "you".  "Licensees" and
//"recipients" may be individuals or organizations.
//
//  To "modify" a work means to copy from or adapt all or part of the work
//in a fashion requiring copyright permission, other than the making of an
//exact copy.  The resulting work is called a "modified version" of the
//earlier work or a work "based on" the earlier work.
//
//  A "covered work" means either the unmodified Program or a work based
//on the Program.
//
//  To "propagate" a work means to do anything with it that, without
//permission, would make you directly or secondarily liable for
//infringement under applicable copyright law, except executing it on a
//computer or modifying a private copy.  Propagation includes copying,
//distribution (with or without modification), making available to the
//public, and in some countries other activities as well.
//
//  To "convey" a work means any kind of propagation that enables other
//parties to make or receive copies.  Mere interaction with a user through
//a computer network, with no transfer of a copy, is not conveying.
//
//  An interactive user interface displays "Appropriate Legal Notices"
//to the extent that it includes a convenient and prominently visible
//feature that (1) displays an appropriate copyright notice, and (2)
//tells the user that there is no warranty for the work (except to the
//extent that warranties are provided), that licensees may convey the
//work under this License, and how to view a copy of this License.  If
//the interface presents a list of user commands or options, such as a
//menu, a prominent item in the list meets this criterion.
//
//  1. Source Code.
//
//  The "source code" for a work means the preferred form of the work
//for making modifications to it.  "Object code" means any non-source
//form of a work.
//
//  A "Standard Interface" means an interface that either is an official
//standard defined by a recognized standards body, or, in the case of
//interfaces specified for a particular programming language, one that
//is widely used among developers working in that language.
//
//  The "System Libraries" of an executable work include anything, other
//than the work as a whole, that (a) is included in the normal form of
//packaging a Major Component, but which is not part of that Major
//Component, and (b) serves only to enable use of the work with that
//Major Component, or to implement a Standard Interface for which an
//implementation is available to the public in source code form.  A
//"Major Component", in this context, means a major essential component
//(kernel, window system, and so on) of the specific operating system
//(if any) on which the executable work runs, or a compiler used to
//produce the work, or an object code interpreter used to run it.
//
//  The "Corresponding Source" for a work in object code form means all
//the source code needed to generate, install, and (for an executable
//work) run the object code and to modify the work, including scripts to
//control those activities.  However, it does not include the work's
//System Libraries, or general-purpose tools or generally available free
//programs which are used unmodified in performing those activities but
//which are not part of the work.  For example, Corresponding Source
//includes interface definition files associated with source files for
//the work, and the source code for shared libraries and dynamically
//linked subprograms that the work is specifically designed to require,
//such as by intimate data communication or control flow between those
//subprograms and other parts of the work.
//
//  The Corresponding Source need not include anything that users
//can regenerate automatically from other parts of the Corresponding
//Source.
//
//  The Corresponding Source for a work in source code form is that
//same work.
//
//  2. Basic Permissions.
//
//  All rights granted under this License are granted for the term of
//copyright on the Program, and are irrevocable provided the stated
//conditions are met.  This License explicitly affirms your unlimited
//permission to run the unmodified Program.  The output from running a
//covered work is covered by this License only if the output, given its
//content, constitutes a covered work.  This License acknowledges your
//rights of fair use or other equivalent, as provided by copyright law.
//
//  You may make, run and propagate covered works that you do not
//convey, without conditions so long as your license otherwise remains
//in force.  You may convey covered works to others for the sole purpose
//of having them make modifications exclusively for you, or provide you
//with facilities for running those works, provided that you comply with
//the terms of this License in conveying all material for which you do
//not control copyright.  Those thus making or running the covered works
//for you must do so exclusively on your behalf, under your direction
//and control, on terms that prohibit them from making any copies of
//your copyrighted material outside their relationship with you.
//
//  Conveying under any other circumstances is permitted solely under
//the conditions stated below.  Sublicensing is not allowed; section 10
//makes it unnecessary.
//
//  3. Protecting Users' Legal Rights From Anti-Circumvention Law.
//
//  No covered work shall be deemed part of an effective technological
//measure under any applicable law fulfilling obligations under article
//11 of the WIPO copyright treaty adopted on 20 December 1996, or
//similar laws prohibiting or restricting circumvention of such
//measures.
//
//  When you convey a covered work, you waive any legal power to forbid
//circumvention of technological measures to the extent such circumvention
//is effected by exercising rights under this License with respect to
//the covered work, and you disclaim any intention to limit operation or
//modification of the work as a means of enforcing, against the work's
//users, your or third parties' legal rights to forbid circumvention of
//technological measures.
//
//  4. Conveying Verbatim Copies.
//
//  You may convey verbatim copies of the Program's source code as you
//receive it, in any medium, provided that you conspicuously and
//appropriately publish on each copy an appropriate copyright notice;
//keep intact all notices stating that this License and any
//non-permissive terms added in accord with section 7 apply to the code;
//keep intact all notices of the absence of any warranty; and give all
//recipients a copy of this License along with the Program.
//
//  You may charge any price or no price for each copy that you convey,
//and you may offer support or warranty protection for a fee.
//
//  5. Conveying Modified Source Versions.
//
//  You may convey a work based on the Program, or the modifications to
//produce it from the Program, in the form of source code under the
//terms of section 4, provided that you also meet all of these conditions:
//
//    a) The work must carry prominent notices stating that you modified
//    it, and giving a relevant date.
//
//    b) The work must carry prominent notices stating that it is
//    released under this License and any conditions added under section
//    7.  This requirement modifies the requirement in section 4 to
//    "keep intact all notices".
//
//    c) You must license the entire work, as a whole, under this
//    License to anyone who comes into possession of a copy.  This
//    License will therefore apply, along with any applicable section 7
//    additional terms, to the whole of the work, and all its parts,
//    regardless of how they are packaged.  This License gives no
//    permission to license the work in any other way, but it does not
//    invalidate such permission if you have separately received it.
//
//    d) If the work has interactive user interfaces, each must display
//    Appropriate Legal Notices; however, if the Program has interactive
//    interfaces that do not display Appropriate Legal Notices, your
//    work need not make them do so.
//
//  A compilation of a covered work with other separate and independent
//works, which are not by their nature extensions of the covered work,
//and which are not combined with it such as to form a larger program,
//in or on a volume of a storage or distribution medium, is called an
//"aggregate" if the compilation and its resulting copyright are not
//used to limit the access or legal rights of the compilation's users
//beyond what the individual works permit.  Inclusion of a covered work
//in an aggregate does not cause this License to apply to the other
//parts of the aggregate.
//
//  6. Conveying Non-Source Forms.
//
//  You may convey a covered work in object code form under the terms
//of sections 4 and 5, provided that you also convey the
//machine-readable Corresponding Source under the terms of this License,
//in one of these ways:
//
//    a) Convey the object code in, or embodied in, a physical product
//    (including a physical distribution medium), accompanied by the
//    Corresponding Source fixed on a durable physical medium
//    customarily used for software interchange.
//
//    b) Convey the object code in, or embodied in, a physical product
//    (including a physical distribution medium), accompanied by a
//    written offer, valid for at least three years and valid for as
//    long as you offer spare parts or customer support for that product
//    model, to give anyone who possesses the object code either (1) a
//    copy of the Corresponding Source for all the software in the
//    product that is covered by this License, on a durable physical
//    medium customarily used for software interchange, for a price no
//    more than your reasonable cost of physically performing this
//    conveying of source, or (2) access to copy the
//    Corresponding Source from a network server at no charge.
//
//    c) Convey individual copies of the object code with a copy of the
//    written offer to provide the Corresponding Source.  This
//    alternative is allowed only occasionally and noncommercially, and
//    only if you received the object code with such an offer, in accord
//    with subsection 6b.
//
//    d) Convey the object code by offering access from a designated
//    place (gratis or for a charge), and offer equivalent access to the
//    Corresponding Source in the same way through the same place at no
//    further charge.  You need not require recipients to copy the
//    Corresponding Source along with the object code.  If the place to
//    copy the object code is a network server, the Corresponding Source
//    may be on a different server (operated by you or a third party)
//    that supports equivalent copying facilities, provided you maintain
//    clear directions next to the object code saying where to find the
//    Corresponding Source.  Regardless of what server hosts the
//    Corresponding Source, you remain obligated to ensure that it is
//    available for as long as needed to satisfy these requirements.
//
//    e) Convey the object code using peer-to-peer transmission, provided
//    you inform other peers where the object code and Corresponding
//    Source of the work are being offered to the general public at no
//    charge under subsection 6d.
//
//  A separable portion of the object code, whose source code is excluded
//from the Corresponding Source as a System Library, need not be
//included in conveying the object code work.
//
//  A "User Product" is either (1) a "consumer product", which means any
//tangible personal property which is normally used for personal, family,
//or household purposes, or (2) anything designed or sold for incorporation
//into a dwelling.  In determining whether a product is a consumer product,
//doubtful cases shall be resolved in favor of coverage.  For a particular
//product received by a particular user, "normally used" refers to a
//typical or common use of that class of product, regardless of the status
//of the particular user or of the way in which the particular user
//actually uses, or expects or is expected to use, the product.  A product
//is a consumer product regardless of whether the product has substantial
//commercial, industrial or non-consumer uses, unless such uses represent
//the only significant mode of use of the product.
//
//  "Installation Information" for a User Product means any methods,
//procedures, authorization keys, or other information required to install
//and execute modified versions of a covered work in that User Product from
//a modified version of its Corresponding Source.  The information must
//suffice to ensure that the continued functioning of the modified object
//code is in no case prevented or interfered with solely because
//modification has been made.
//
//  If you convey an object code work under this section in, or with, or
//specifically for use in, a User Product, and the conveying occurs as
//part of a transaction in which the right of possession and use of the
//User Product is transferred to the recipient in perpetuity or for a
//fixed term (regardless of how the transaction is characterized), the
//Corresponding Source conveyed under this section must be accompanied
//by the Installation Information.  But this requirement does not apply
//if neither you nor any third party retains the ability to install
//modified object code on the User Product (for example, the work has
//been installed in ROM).
//
//  The requirement to provide Installation Information does not include a
//requirement to continue to provide support service, warranty, or updates
//for a work that has been modified or installed by the recipient, or for
//the User Product in which it has been modified or installed.  Access to a
//network may be denied when the modification itself materially and
//adversely affects the operation of the network or violates the rules and
//protocols for communication across the network.
//
//  Corresponding Source conveyed, and Installation Information provided,
//in accord with this section must be in a format that is publicly
//documented (and with an implementation available to the public in
//source code form), and must require no special password or key for
//unpacking, reading or copying.
//
//  7. Additional Terms.
//
//  "Additional permissions" are terms that supplement the terms of this
//License by making exceptions from one or more of its conditions.
//Additional permissions that are applicable to the entire Program shall
//be treated as though they were included in this License, to the extent
//that they are valid under applicable law.  If additional permissions
//apply only to part of the Program, that part may be used separately
//under those permissions, but the entire Program remains governed by
//this License without regard to the additional permissions.
//
//  When you convey a copy of a covered work, you may at your option
//remove any additional permissions from that copy, or from any part of
//it.  (Additional permissions may be written to require their own
//removal in certain cases when you modify the work.)  You may place
//additional permissions on material, added by you to a covered work,
//for which you have or can give appropriate copyright permission.
//
//  Notwithstanding any other provision of this License, for material you
//add to a covered work, you may (if authorized by the copyright holders of
//that material) supplement the terms of this License with terms:
//
//    a) Disclaiming warranty or limiting liability differently from the
//    terms of sections 15 and 16 of this License; or
//
//    b) Requiring preservation of specified reasonable legal notices or
//    author attributions in that material or in the Appropriate Legal
//    Notices displayed by works containing it; or
//
//    c) Prohibiting misrepresentation of the origin of that material, or
//    requiring that modified versions of such material be marked in
//    reasonable ways as different from the original version; or
//
//    d) Limiting the use for publicity purposes of names of licensors or
//    authors of the material; or
//
//    e) Declining to grant rights under trademark law for use of some
//    trade names, trademarks, or service marks; or
//
//    f) Requiring indemnification of licensors and authors of that
//    material by anyone who conveys the material (or modified versions of
//    it) with contractual assumptions of liability to the recipient, for
//    any liability that these contractual assumptions directly impose on
//    those licensors and authors.
//
//  All other non-permissive additional terms are considered "further
//restrictions" within the meaning of section 10.  If the Program as you
//received it, or any part of it, contains a notice stating that it is
//governed by this License along with a term that is a further
//restriction, you may remove that term.  If a license document contains
//a further restriction but permits relicensing or conveying under this
//License, you may add to a covered work material governed by the terms
//of that license document, provided that the further restriction does
//not survive such relicensing or conveying.
//
//  If you add terms to a covered work in accord with this section, you
//must place, in the relevant source files, a statement of the
//additional terms that apply to those files, or a notice indicating
//where to find the applicable terms.
//
//  Additional terms, permissive or non-permissive, may be stated in the
//form of a separately written license, or stated as exceptions;
//the above requirements apply either way.
//
//  8. Termination.
//
//  You may not propagate or modify a covered work except as expressly
//provided under this License.  Any attempt otherwise to propagate or
//modify it is void, and will automatically terminate your rights under
//this License (including any patent licenses granted under the third
//paragraph of section 11).
//
//  However, if you cease all violation of this License, then your
//license from a particular copyright holder is reinstated (a)
//provisionally, unless and until the copyright holder explicitly and
//finally terminates your license, and (b) permanently, if the copyright
//holder fails to notify you of the violation by some reasonable means
//prior to 60 days after the cessation.
//
//  Moreover, your license from a particular copyright holder is
//reinstated permanently if the copyright holder notifies you of the
//violation by some reasonable means, this is the first time you have
//received notice of violation of this License (for any work) from that
//copyright holder, and you cure the violation prior to 30 days after
//your receipt of the notice.
//
//  Termination of your rights under this section does not terminate the
//licenses of parties who have received copies or rights from you under
//this License.  If your rights have been terminated and not permanently
//reinstated, you do not qualify to receive new licenses for the same
//material under section 10.
//
//  9. Acceptance Not Required for Having Copies.
//
//  You are not required to accept this License in order to receive or
//run a copy of the Program.  Ancillary propagation of a covered work
//occurring solely as a consequence of using peer-to-peer transmission
//to receive a copy likewise does not require acceptance.  However,
//nothing other than this License grants you permission to propagate or
//modify any covered work.  These actions infringe copyright if you do
//not accept this License.  Therefore, by modifying or propagating a
//covered work, you indicate your acceptance of this License to do so.
//
//  10. Automatic Licensing of Downstream Recipients.
//
//  Each time you convey a covered work, the recipient automatically
//receives a license from the original licensors, to run, modify and
//propagate that work, subject to this License.  You are not responsible
//for enforcing compliance by third parties with this License.
//
//  An "entity transaction" is a transaction transferring control of an
//organization, or substantially all assets of one, or subdividing an
//organization, or merging organizations.  If propagation of a covered
//work results from an entity transaction, each party to that
//transaction who receives a copy of the work also receives whatever
//licenses to the work the party's predecessor in interest had or could
//give under the previous paragraph, plus a right to possession of the
//Corresponding Source of the work from the predecessor in interest, if
//the predecessor has it or can get it with reasonable efforts.
//
//  You may not impose any further restrictions on the exercise of the
//rights granted or affirmed under this License.  For example, you may
//not impose a license fee, royalty, or other charge for exercise of
//rights granted under this License, and you may not initiate litigation
//(including a cross-claim or counterclaim in a lawsuit) alleging that
//any patent claim is infringed by making, using, selling, offering for
//sale, or importing the Program or any portion of it.
//
//  11. Patents.
//
//  A "contributor" is a copyright holder who authorizes use under this
//License of the Program or a work on which the Program is based.  The
//work thus licensed is called the contributor's "contributor version".
//
//  A contributor's "essential patent claims" are all patent claims
//owned or controlled by the contributor, whether already acquired or
//hereafter acquired, that would be infringed by some manner, permitted
//by this License, of making, using, or selling its contributor version,
//but do not include claims that would be infringed only as a
//consequence of further modification of the contributor version.  For
//purposes of this definition, "control" includes the right to grant
//patent sublicenses in a manner consistent with the requirements of
//this License.
//
//  Each contributor grants you a non-exclusive, worldwide, royalty-free
//patent license under the contributor's essential patent claims, to
//make, use, sell, offer for sale, import and otherwise run, modify and
//propagate the contents of its contributor version.
//
//  In the following three paragraphs, a "patent license" is any express
//agreement or commitment, however denominated, not to enforce a patent
//(such as an express permission to practice a patent or covenant not to
//sue for patent infringement).  To "grant" such a patent license to a
//party means to make such an agreement or commitment not to enforce a
//patent against the party.
//
//  If you convey a covered work, knowingly relying on a patent license,
//and the Corresponding Source of the work is not available for anyone
//to copy, free of charge and under the terms of this License, through a
//publicly available network server or other readily accessible means,
//then you must either (1) cause the Corresponding Source to be so
//available, or (2) arrange to deprive yourself of the benefit of the
//patent license for this particular work, or (3) arrange, in a manner
//consistent with the requirements of this License, to extend the patent
//license to downstream recipients.  "Knowingly relying" means you have
//actual knowledge that, but for the patent license, your conveying the
//covered work in a country, or your recipient's use of the covered work
//in a country, would infringe one or more identifiable patents in that
//country that you have reason to believe are valid.
//
//  If, pursuant to or in connection with a single transaction or
//arrangement, you convey, or propagate by procuring conveyance of, a
//covered work, and grant a patent license to some of the parties
//receiving the covered work authorizing them to use, propagate, modify
//or convey a specific copy of the covered work, then the patent license
//you grant is automatically extended to all recipients of the covered
//work and works based on it.
//
//  A patent license is "discriminatory" if it does not include within
//the scope of its coverage, prohibits the exercise of, or is
//conditioned on the non-exercise of one or more of the rights that are
//specifically granted under this License.  You may not convey a covered
//work if you are a party to an arrangement with a third party that is
//in the business of distributing software, under which you make payment
//to the third party based on the extent of your activity of conveying
//the work, and under which the third party grants, to any of the
//parties who would receive the covered work from you, a discriminatory
//patent license (a) in connection with copies of the covered work
//conveyed by you (or copies made from those copies), or (b) primarily
//for and in connection with specific products or compilations that
//contain the covered work, unless you entered into that arrangement,
//or that patent license was granted, prior to 28 March 2007.
//
//  Nothing in this License shall be construed as excluding or limiting
//any implied license or other defenses to infringement that may
//otherwise be available to you under applicable patent law.
//
//  12. No Surrender of Others' Freedom.
//
//  If conditions are imposed on you (whether by court order, agreement or
//otherwise) that contradict the conditions of this License, they do not
//excuse you from the conditions of this License.  If you cannot convey a
//covered work so as to satisfy simultaneously your obligations under this
//License and any other pertinent obligations, then as a consequence you may
//not convey it at all.  For example, if you agree to terms that obligate you
//to collect a royalty for further conveying from those to whom you convey
//the Program, the only way you could satisfy both those terms and this
//License would be to refrain entirely from conveying the Program.
//
//  13. Use with the GNU Affero General Public License.
//
//  Notwithstanding any other provision of this License, you have
//permission to link or combine any covered work with a work licensed
//under version 3 of the GNU Affero General Public License into a single
//combined work, and to convey the resulting work.  The terms of this
//License will continue to apply to the part which is the covered work,
//but the special requirements of the GNU Affero General Public License,
//section 13, concerning interaction through a network will apply to the
//combination as such.
//
//  14. Revised Versions of this License.
//
//  The Free Software Foundation may publish revised and/or new versions of
//the GNU General Public License from time to time.  Such new versions will
//be similar in spirit to the present version, but may differ in detail to
//address new problems or concerns.
//
//  Each version is given a distinguishing version number.  If the
//Program specifies that a certain numbered version of the GNU General
//Public License "or any later version" applies to it, you have the
//option of following the terms and conditions either of that numbered
//version or of any later version published by the Free Software
//Foundation.  If the Program does not specify a version number of the
//GNU General Public License, you may choose any version ever published
//by the Free Software Foundation.
//
//  If the Program specifies that a proxy can decide which future
//versions of the GNU General Public License can be used, that proxy's
//public statement of acceptance of a version permanently authorizes you
//to choose that version for the Program.
//
//  Later license versions may give you additional or different
//permissions.  However, no additional obligations are imposed on any
//author or copyright holder as a result of your choosing to follow a
//later version.
//
//  15. Disclaimer of Warranty.
//
//  THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY
//APPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT
//HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM "AS IS" WITHOUT WARRANTY
//OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,
//THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
//PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM
//IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF
//ALL NECESSARY SERVICING, REPAIR OR CORRECTION.
//
//  16. Limitation of Liability.
//
//  IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING
//WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MODIFIES AND/OR CONVEYS
//THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES, INCLUDING ANY
//GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE
//USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED TO LOSS OF
//DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY YOU OR THIRD
//PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER PROGRAMS),
//EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE POSSIBILITY OF
//SUCH DAMAGES.
//
//  17. Interpretation of Sections 15 and 16.
//
//  If the disclaimer of warranty and limitation of liability provided
//above cannot be given local legal effect according to their terms,
//reviewing courts shall apply local law that most closely approximates
//an absolute waiver of all civil liability in connection with the
//Program, unless a warranty or assumption of liability accompanies a
//copy of the Program in return for a fee.
//
//                     END OF TERMS AND CONDITIONS
//
//            How to Apply These Terms to Your New Programs
//
//  If you develop a new program, and you want it to be of the greatest
//possible use to the public, the best way to achieve this is to make it
//free software which everyone can redistribute and change under these terms.
//
//  To do so, attach the following notices to the program.  It is safest
//to attach them to the start of each source file to most effectively
//state the exclusion of warranty; and each file should have at least
//the "copyright" line and a pointer to where the full notice is found.
//
//    <one line to give the program's name and a brief idea of what it does.>
//    Copyright (C) <year>  <name of author>
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//Also add information on how to contact you by electronic and paper mail.
//
//  If the program does terminal interaction, make it output a short
//notice like this when it starts in an interactive mode:
//
//    <program>  Copyright (C) <year>  <name of author>
//    This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
//    This is free software, and you are welcome to redistribute it
//    under certain conditions; type `show c' for details.
//
//The hypothetical commands `show w' and `show c' should show the appropriate
//parts of the General Public License.  Of course, your program's commands
//might be different; for a GUI interface, you would use an "about box".
//
//  You should also get your employer (if you work as a programmer) or school,
//if any, to sign a "copyright disclaimer" for the program, if necessary.
//For more information on this, and how to apply and follow the GNU GPL, see
//<http://www.gnu.org/licenses/>.
//
//  The GNU General Public License does not permit incorporating your program
//into proprietary programs.  If your program is a subroutine library, you
//may consider it more useful to permit linking proprietary applications with
//the library.  If this is what you want to do, use the GNU Lesser General
//Public License instead of this License.  But first, please read
//<http://www.gnu.org/philosophy/why-not-lgpl.html>.
//-------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//Set the include file path.  This is necessary to get to the configuration
//information, including how to try to connect to the database.
set_include_path("/var/www/php_library/fboprime");
//
//Include the configuration information.
require_once("config.inc");
//
//--------------------------------------------------------------------------------
//Writes a horizontal line.
//
function hline()
   {
   for ($i=0; $i<80; $i++)
      {
      echo "-";
      }
   echo "\n";
   }
//
//--------------------------------------------------------------------------------
//Errors out.
//
function error_out()
   {
   echo "FATAL ERROR\n";
   exit(1);
   }
//
//--------------------------------------------------------------------------------
//Returns a version control string.  Used for randomness.
//
function vc_info()
   {
   return("\$Header: /home/dashley/cvsrep/e3ft_gpl01/e3ft_gpl01/webprojs/fboprime/sw/standalone/dbcreate.php,v 1.31 2006/11/05 18:26:05 dashley Exp $");
   }
//
//--------------------------------------------------------------------------------
//
function populate_db($handle, $dbdesign)
   {
   //Figure out how many tables are in the database, and get their names.
   hline();

   $result = mysql_query("show tables", $handle);

   if ($result === FALSE)
      error_out();

   //Figure out the results.
   $ntables = mysql_num_rows($result);
   for ($i=0; $i<$ntables; $i++)
      {
      $temp             = mysql_fetch_row($result);
      $tables_array[$i] = $temp[0];
      }

   //$ntables = count($tables_array);

   //Tell how many tables.
   if ($ntables > 1)
      echo $ntables . " tables found in database:\n";
   else if ($ntables == 1)
      echo $ntables . " table found in database:\n";
   else
      echo "No tables found in database.\n";

   //Emit the table names.
   for ($i = 0; $i < $ntables; $i++)
      {
      echo "   " . $tables_array[$i] . "\n";
      }

   //Loop through the necessary database design.  For any tables that do not
   //exist, create them in their entirety.  Every row in the lookup table that
   //is used (i.e. implemented) is marked by changing the fifth column
   //to "Y".
   for ($i = 0; $i < count($dbdesign); $i += 5)
      {
      if ($dbdesign[$i+4] != "Y")
         {
	   if ($ntables)
              $found = array_search($dbdesign[$i], $tables_array);
           else
	      $found = FALSE;

         if (($found === FALSE) || ($found === NULL))
            {
	    //The cited table does not exist.  Form the SQL query to make it.
	    $query = "create table " . $dbdesign[$i] . " (";
            $first = 1;

            for ($j = 0; $j < count($dbdesign); $j += 5)
	       {
	       if ($dbdesign[$j] == $dbdesign[$i])
	          {
	          if (! $first)
	             {
		     $query .= " , ";
		     }
	          else
		     {
		     $first = 0;
		     }

	          $query = $query . " " . $dbdesign[$j+1] . " " . $dbdesign[$j+2] . " " . $dbdesign[$j+3] . " ";

                  $dbdesign[$j+4] = "Y";
	          }
	       }

            $query .= " )";

            //Echo the query to the console for review.
            hline();
            echo "The table \"" . $dbdesign[$i] . "\" does not exist and will be created.  The SQL query is:\n\n";
            echo $query . "\n";

            //Run the query and bug out if it fails.
            $result = mysql_query($query, $handle);

            if ($result === FALSE)
               error_out();
	    }
         }  //end if not marked
      } // end for
   }
//
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//------  M A I N    S C R I P T  ------------------------------------------------
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//
//
//This describes the overall database design.  The parts are:
//   a)Table name.
//   b)Field name.
//   c)Field type.
//   d)Field attributes.
//
$dbdesign = array 
(
   //=====================================================================================================
   //=====================================================================================================
   //====  U S R S  ======================================================================================
   //=====================================================================================================
   //=====================================================================================================
   //One record for each user.
   //=====================================================================================================
   "usrs",            "idx",             "int",                "AUTO_INCREMENT NOT NULL PRIMARY KEY",  "",
      //The integer index of the user.  This is used as a key throughout the software to uniquely
      //identify a user (for example, in "edit user" screens and so on).  MySQL ensures that the
      //first index will be 1, so 0 can be used as an error code or for other special flags.
   "usrs",            "status",          "int",                "",                                     "",
      //An integer describing the status of the user.  This is an integer constant defined in the
      //source code.  Possible values are active or inactive.  The transition to inactive based on
      //expiration of BFR time or medical can be done only in maintenance scripts or manually--
      //automatic actions involving this kind of state change are not taken during normal
      //page viewing.
   "usrs",            "seclvl",          "int",                "",                                     "",
      //The security level of the user.  This is defined by integer constants in the CONFIG.INC file.
      //The general scheme is that a user may not modify information about a user with a security
      //integer equal to or less than the user's.  A lesser integer means a higher security level.
   "usrs",            "userid",          "varchar(20)",        "",                                     "",
      //The ID of the user when logging in.  This is stored in the database in all lower case, but in
      //logins a user may accidentally mix case, so this is treated as case-insensitive when
      //authenticating.
      //
      //Restrictions:
      //  a)Id as stored may contain only a-z and 0-9 (i.e. no weird characters).
      //  b)Must be at least of length 1.
      //  c)Must begin with a letter (not a number).
      //  d)Must be unique.
   "usrs",            "role",            "int",                "",                                     "",
      //An integer describing the role of the user (flight instructor, user, whatever).  The values
      //are defined by constants in the CONFIG.INC file.  This integer is used for description only
      //and does not affect the privileges of the user in any way.
   "usrs",            "perm",            "varchar(2000)",      "",                                     "",
      //A permission string expressing the precise database permissions the user has.  This is an
      //unordered set of values separated by backslashes.  The string format is used because it combines
      //simplicity with speed.  String operations, which call into 'C'-compiled code, are fast.
   "usrs",            "sex",             "int",                "",                                     "",
      //The gender of the user.  The possible values of this integer are defined in constants in the
      //code.
   "usrs",            "title",           "varchar(20)",        "",                                     "",
      //The title of the user (optional), including a trailing ".", if appropriate.  Titles are strings 
      //such as "Dr.", "Mr.", etc.  This may have 'a-z', 'A-Z', spaces, apostrophes, "," and ".".
   "usrs",            "fname",           "varchar(20)",        "",                                     "",
      //The first name of the user (optional).  No casing is enforced due to the possibility of foreign names such as
      //"ug Limu" (I made that up).  Spaces are allowed in the name (only one contiguously) to accommodate 
      //foreign names.  Before storage in the database:
      //  a)Must have no leading or trailing spaces.
      //  b)Must be at least of length 1.
      //  c)May contain only 'a-z', 'A-Z', spaces, and apostrophes.
      //  d)If spaces appear within the name, there can be only one contiguously.
   "usrs",            "mname",           "varchar(20)",        "",                                     "",
      //The middle name of the user (optional), or the middle initial, or the middle initial followed by
      //a period.  Characters allowed are 'a-z', 'A-Z', spaces, and apostrophes, with no more than one
      //contiguous space.
   "usrs",            "lname",           "varchar(20)",        "",                                     "",
      //The last name of the user.  No casing is enforced due to the possibility of foreign names such as
      //"de Raspide".  Spaces are allowed in the name (only one contiguously) to accommodate foreign names.
      //Before storage in the database:
      //  a)Must have no leading or trailing spaces.
      //  b)Must be at least of length 1.
      //  c)May contain only 'a-z', 'A-Z', spaces, and apostrophes.
      //  d)If spaces appear within the name, there can be only one contiguously.
   "usrs",            "suffix",          "varchar(20)",        "",                                     "",
      //The suffix, such as "Jr.", "Sr.", etc. (optional).  This may have 'a-z', 'A-Z', spaces,
      //apostrophes, commas, and periods, with no more than one contiguous space.
   "usrs",            "adl1",            "varchar(50)",        "",                                     "",
      //The first line of the street address of the user.  This may include 'a-z', 'A-Z', digits, spaces,
      //apostrophes, periods, and '#', with no more than one contiguous space.  Optional.
   "usrs",            "adl2",            "varchar(50)",        "",                                     "",
      //Second line of address.  Same rules as first.                                                    
   "usrs",            "city",            "varchar(20)",        "",                                     "",
      //City (optional).  Same rules as first name and last name.                                        
   "usrs",            "stateprovince",   "varchar(20)",        "",                                     "",
      //Same rules as last name/first name.  For someone in a foreign country, this may not be a 2-letter
      //code.  Optional.
   "usrs",            "zippostalcode",   "varchar(20)",        "",                                     "",
      //Postal code.  Same rules as address lines.  Optional.  In the case of foreign countries, the
      //zip/postal code may be longer than 9 digits or contain letters, etc.
   "usrs",            "country",         "varchar(20)",        "",                                     "",
      //The country, in English.  Same rules as first or last names.  Optional.
   "usrs",            "pwhash",          "varchar(64)",        "",                                     "",
      //The salt and hash of the primary password.  The primary password is the one the user normally 
      //uses to log in.  If both this and the lostpwhash are not set, it would not be possible to log in.
   "usrs",            "lostpwhash",      "varchar(64)",        "",                                     "",
      //The salt and hash of the password that may be e-mailed to the user if the password is lost.  
      //It is done that way to avoid e-mailing existing passwords in the clear (the password mailed
      //to the user is a randomly-generated one).
   "usrs",            "lostpwgentime",   "varchar(22)",        "",                                     "",
      //A UTIME flagging the time at which the e-mailed password was generated.  There are two behaviors
      //associated with this:
      //  a)A new password cannot be e-mailed too often (i.e. there needs to be a minimum spacing).
      //  b)A password that is e-mailed is only valid for a finite period of time.
   "usrs",            "ratings",         "varchar(200)",       "",                                     "",
      //A string describing the ratings that the user has.  The format of this is up to the FBO.
      //Generally, this would be a comma-separated list of acronyms.  For storage in the database,
      //blanks and tabs would be trimmed from both ends.
   "usrs",            "bfrlicexpdate",   "varchar(8)",         "",                                     "",
      //The date, as a DT8, on which the user's license becomes invalid if the pilot does not receive
      //a BFR.
   "usrs",            "medexpdate",      "varchar(8)",         "",                                     "",
      //The date, as a DT8, on which the user's medical becomes invalid.  The user must obtain a new
      //medical by this date or can't fly as PIC or required crewmember.
   "usrs",            "restrictions",    "varchar(2000)",      "",                                     "",
      //A textual description of the restrictions that the user is under.  A typical string might be
      //"Medical prohibits user from flying at night.".  The format of this is up to the FBO.
   "usrs",            "dayphone",        "varchar(50)",        "",                                     "",
      //The daytime phone number of the user.  This is essentially the work phone number.
      //All phone numbers are optional.  Character set and rules same as address lines.
   "usrs",            "eveningphone",    "varchar(50)",        "",                                     "",
      //The evening phone number of the user.  This is essentially the home phone number.
   "usrs",            "cellphone",       "varchar(50)",        "",                                     "",
      //The mobile phone number of the user. 
   "usrs",            "em1",             "varchar(100)",       "",                                     "",
      //First notification e-mail address of the user.                                     
   "usrs",            "em2",             "varchar(100)",       "",                                     "",
      //Second notification e-mail address of the user.                                     
   "usrs",            "acctexpdate",     "varchar(8)",         "",                                     "",
      //The date, as a DT8, on which the user's account should expire.  On this date the user becomes
      //inactive and can't log in any more.
   "usrs",            "mostrecentlogin", "varchar(8)",         "",                                     "",
      //The date on which the most recent login by the user occurred.
   "usrs",            "schedalonerscs",  "varchar(2000)",      "",                                     "",
      //A comma-separated integer list of resources that the user can schedule without a flight
      //instructor.  (All resources can be scheduled WITH a flight instructor.)  The first character
      //will be a comma and the final entry will be ended with a comma, subject to the rules of 
      //comma-separated integer lists.
   "usrs",            "fboremarks",      "varchar(4000)",      "",                                     "",
   "usrs",            "userremarks",     "varchar(4000)",      "",                                     "",
      //Remarks editable by the FBO and user respectively.  Both sets of remarks are visible by both
      //parties, but the FBO remarks can be edited only by the FBO and the user remarks can be edited
      //only by the user.
   "usrs",            "crmodsguid",      "varchar(32)",        "",                                     "",
      //The SGUID from when the record was created or last modified.  This may be used to avoid browser
      //editing collisions.  The way that collisions are avoided is that when the record is modified
      //(perhaps by another user while a given user has the record displayed in a browser form), a new
      //SGUID is placed in the record.  When a new commit of the record is attempted, the lower-level
      //functions will detect that the underlying SGUID has changed, as they will compare the
      //one provided by the browser (usually stored as a hidden field) against the one currently
      //in the database.  The two will definitely be different, as SGUIDs have guaranteed uniqueness
      //throughout the lifetime of the server.
   //=====================================================================================================
   //=====================================================================================================
   //====  R E S V  ======================================================================================
   //=====================================================================================================
   //=====================================================================================================
   //One record for each reservation.  A reservation can consist of multiple slots.
   //=====================================================================================================
   "resv",            "idx",             "int",                "AUTO_INCREMENT NOT NULL PRIMARY KEY",  "",
      //The integer index of reservation.  Used to identify it uniquely.
   "resv",            "type",            "int",                "",                                     "",
      //An integer identifying the type of the reservation.  This is defined by constants in source
      //code.  Possibilities are:
      //    0  :  Banner reservation.  This does nothing, interferes with nothing, etc.  It just
      //          displays information that is visible.
      //    1  :  Ordinary reservation that is active (not standby).
      //    2  :  Standby reservation.  This is an ordinary reservation that can't be made active
      //          because of a conflict.
   "resv",            "crsguid",         "varchar(32)",        "",                                     "",
      //An SGUID identifying the time at which the reservation was created.  This is used to break any
      //ties for priority.  Because of the way an SGUID is constructed, this is guaranteed to be
      //unique.  After the reservation is created, this SGUID is not modified 
   "resv",            "createtimest",    "varchar(22)",        "",                                     "",
      //An STIME identifying the time at which the reservation is created.  This is used for reporting
      //the date and time in human-friendly terms (but can't be used for tie-breaking).
   "resv",            "useridx",         "int",                "",                                     "",
      //An integer identifying the owner of the reservation.  As every reservation must have an owner,
      //this index must be > 0.
   "resv",            "alias",           "int",                "",                                     "",
      //Integer identifying the alias, if any.  Alias is the pseudo-name that should be displayed as the
      //owner, such as "Line", "Maintenance", etc.  A value of zero here indicates no alias to be used.
   "resv",            "finstid",         "int",                "",                                     "",
      //An integer identifying the resource record (not the user record!) corresponding to the flight 
      //instructor for the reservation.  If no flight instructor is included in the reservation, 0 is
      //stored.
   "resv",            "finsttimestart",  "varchar(22)",        "",                                     "",
      //The STIME corresponding to the start with the instructor.  If no instructor on the reservation,
      //this should be the empty string.
   "resv",            "finsttimeend",    "varchar(22)",        "",                                     "",
      //The STIME corresponding to the with the instructor.  If no instructor on the reservation,
      //this should be the empty string.
   "resv",            "acftsimid",       "int",                "",                                     "",
      //An integer identifying the resource record corresponding to the aircraft or simulator that is
      //being reserved.  If no aircraft or simulator is included in the reservation, 0 is stored.
   "resv",            "acftsimtimestart","varchar(22)",        "",                                     "",
      //The STIME corresponding to the start with the aircraft or simulator.  If no aircraft or simulator
      //is on the reservation, this should be the empty string.
   "resv",            "acftsimtimeend",  "varchar(22)",        "",                                     "",
      //The STIME corresponding to the end the aircraft or simulator.  If no aircraft or simulator is on 
      //the reservation, this should be the empty string.
   "resv",            "resvtimestart",   "varchar(22)",        "",                                     "",
      //The STIME corresponding to the start time of the reservation.  The start time is the minimum of 
      //the start of the flight instructor, if any, and the aircraft or simulator, if any.  For any
      //reservation, this always exists, because the reservation must have a flight instructor or
      //aircraft/simulator.  This database field is provided to simplify some queries.
   "resv",            "resvtimeend",     "varchar(22)",        "",                                     "",
      //The STIME corresponding to the end time of the reservation.  The start time is the maximum of 
      //the end of the flight instructor, if any, and the aircraft or simulator, if any.  For any
      //reservation, this always exists, because the reservation must have a flight instructor or
      //aircraft/simulator.  This database field is provided to simplify some queries.
   "resv",            "usrprivdesc",     "varchar(4000)",      "",                                     "",
      //User-private textual description of the appointment.  This can only appear on reservations
      //where:
      //   a)The reservation does not involve an aircraft.
      //   b)The reservation is by a flight instructor reserving the resource corresponding to
      //     themselves.
      //
      //User-private text is intended to allow for doctor's appointments, etc. and to keep the details
      //of this absolutely private to the individual private.
   "resv",            "fboprivdesc",     "varchar(4000)",      "",                                     "",
      //Description private to the FBO employees (not shared with the general user population).
      //Note that a reservation (such as a doctor's appointment) may have a certain description that is
      //user private, but a separate description for the FBO employees.
   "resv",            "comprivdesc",     "varchar(4000)",      "",                                     "",
      //Description private to the user community (those with login accounts who are logged in).
      //Note that any reservation may have an FBO-private component and a community-private
      //component.
   "resv",            "publicdesc",      "varchar(4000)",      "",                                     "",
      //Description that is fully public (visible to web page visitors who have not logged in).  
      //Currently only banner reservations support this field.
      //
   "resv",            "crmodsguid",      "varchar(32)",        "",                                     "",
      //An SGUID from whenever the reservation is created or modified.  This is used to detect editing
      //collisions.  This field is modified whenever the record is committed back (unlike the field
      //somewhat earlier in the definition that is never changed after record creation).
   //
   //=====================================================================================================
   //====  R S C S  ======================================================================================
   //=====================================================================================================
   //=====================================================================================================
   //The resources (aircraft, simulators, flight instructors).
   //=====================================================================================================
   "rscs",            "idx",             "int",                "AUTO_INCREMENT NOT NULL PRIMARY KEY",  "",
      //The integer index of the resource.  This can be a unique way to identify the record.
   "rscs",            "type",            "int",                "",                                     "",
      //The type of the resource.  This is an integer constant defined in the code.  The values may be
      //aircraft, simulator, or flight instructor.
   "rscs",            "status",          "int",                "",                                     "",
      //The status of the resource.  This is an integer constant defined in the code.  The values
      //may be online or offline.
   "rscs",            "disporder",       "int",                "",                                     "",
      //An integer used to govern the order in which resources are displayed, smallest integer first.
      //This is used (as it is also in ORS) because the preferred display order (for the scheduler
      //and other places) may not correlate with any other fields.
   "rscs",            "initials",        "varchar(25)",        "",                                     "",
      //The shortest description, i.e. "N12345" or "J.F.".
   "rscs",            "shortdesc",       "varchar(50)",        "",                                     "",
      //A shorter description, i.e. "N12345" or "J. Flightinstructor".
   "rscs",            "longdesc",        "varchar(100)",       "",                                     "",
      //The long description of the resource.
      //
      //For a flight instructor, this would normally be the full name, i.e. "Flightinstructor, Jane Q.".
      //For a simulator I'm not sure how it would typically be described.   For an aircraft, this would
      //typically be the tail number followed by the aircraft model number, i.e. "N12345 Cessna 172P".
      //
      //In any case, this field is up to the discretion of the FBO, except that it cannot contain
      //any HTML markup. 
   "rscs",            "rstdtime",        "varchar(48)",       "",                                     "",
      //An array of 48 characters, each of which should be a R or a U, and corresponding to the   
      //half-hour time slots during a day.  The first character corresponds to the slot between 
      //12:00 a.m. and 12:30 a.m., the second character to the time slot between 12:30 a.m. and 1:00 a.m.,
      //etc.  A "R" in the corresponding position indicates that the time slot is restricted and that
      //there must be some interaction with the FBO to schedule the time slot.  A "U" in the
      //position indicates that the time slot may be scheduled freely.  For flight instructors,
      //this may be set up to prevent students from arbitrarily scheduling appointments in the
      //middle of the night.  For aircraft, it is unclear how this would help.  For simulators, this
      //would prevent users from scheduling the simulator when it is unavailable (such as when the 
      //building it is in is closed for business).
   "rscs",            "schedaheadhrs",   "int",                "",                                     "",
      //For a resource, the minimum number of hours that a user must schedule it ahead of time
      //with no interaction with the FBO.  There is also a similar limit in CONFIG.INC.  The
      //scheduling software uses the more restrictive (i.e. larger) of the two.
   "rscs",            "usercorres",      "int",                "",                                     "",
      //For a resource that is a flight instructor, the index of the user corresponding to the
      //resource.  For other types of resources, this will be 0.
   "rscs",            "crmodsguid",      "varchar(32)",        "",                                     "",
      //The SGUID from when the record was created or last modified.  This may be used to avoid browser
      //editing collisions.  The way that collisions are avoided is that when the record is modified
      //(perhaps by another user while a given user has the record displayed in a browser form), a new
      //SGUID is placed in the record.  When a new commit of the record is attempted, the lower-level
      //functions will detect that the underlying SGUID has changed, as they will compare the
      //one provided by the browser (usually stored as a hidden field) against the one currently
      //in the database.  The two will definitely be different, as SGUIDs have guaranteed uniqueness
      //throughout the lifetime of the server.
   //
   //=====================================================================================================
   //=====================================================================================================
   //====  S E S S  ======================================================================================
   //=====================================================================================================
   //=====================================================================================================
   //One record for each active session.  If a user does not explicitly log out or get canned for a page
   //hit after expiry, these are reaped by cron processes.
   //=====================================================================================================
   "sess",            "idx",             "int",                "AUTO_INCREMENT NOT NULL PRIMARY KEY",  "",
      //The integer index of session.
   "sess",            "usrsidx",         "int",                "",                                     "",
      //The integer index of the user with whom the session is associated.
   "sess",            "sguid",           "char(32)",           "",                                     "",
      //An SGUID created when the session is opened.  This is guaranteed to be unique.  This is never
      //revealed to the client.  The reason it isn't revealed is that it may be used in cases
      //as part of a hash key.
   "sess",            "ip",              "varchar(32)",        "",                                     "",
      //The connecting IP as known to the server.  This is the string provided by the server.  With
      //IPV6, there can be up to 31 characters.
   "sess",            "sid",             "varchar(66)",        "",                                     "",
      //The session identifier.  This is formed when the session is opened and never changed
      //thereafter until the session is reaped.  This is provided to the user's browser as a cookie.
   "sess",            "revaltime",       "char(22)",           "",                                     "",
      //The time at which the session was created or revalidated (revalidation occurs when another page is
      //loaded with a valid SID), expressed as a UTIME.  This allows a user to continue activity 
      //and as long as there is activity the session won't expire.
   "sess",            "lifetime",        "int",                "",                                     "",
      //The lifetime of the session.  This is effectively the allowed inactivity time before an automatic
      //logout.  This lifetime could, in principle, be a function of who the user is.  In any case,
      //the lifetime can be modified in some cases to give a longer time until logout (useful for
      //line employees).
   "sess",            "loginfailures",   "int",                "",                                     "",
      //The number of consecutive times during the session that the wrong password for the userid has
      //been entered (on pages that perform sensitive operations where the operation must be
      //confirmed.  After a certain number of consecutive bad password entries, the user is forcibly
      //logged out.  The purpose of this behavior is to allow one or two typos without trashing a
      //user's typing in a form, but to not allow password guessing to go on indefinitely.  This counter
      //is reset back to zero on a successful correct password entry.
   "sess",            "menulvl",         "int",                "",                                     "",
      //The menu level at which the session is currently operating.  "0" is the default menu level, and
      //larger integers represent more options displayed on the menu.
   "sess",            "pagereloadtime",  "int",                "",                                     "",
      //If this value is >0, is the interval (in seconds) at which certain scheduling pages should be
      //automatically reloaded.  This is to assist line employees who might open the dayview scheduling
      //page and want it to refresh with changes periodically.
   "sess",            "sddt",            "varchar(8)",         "",                                     "",
      //The date, as a DT8, carried through as we decide which information to display.  This avoids
      //to tacking GET parameters on everywhere.  On the scheduler pages that will display with no user
      //logged in, the GET/POST parameters take precedence over anything stored in the session
      //state record, if any.  If this doesn't apply, the empty string is stored.
   "sess",            "sdtim",           "varchar(4)",         "",                                     "",
      //The time, as a T4, carried through as we decide which information to display.  This avoids
      //to tacking GET parameters on everywhere.  On the scheduler pages that will display with no user
      //logged in, the GET/POST parameters take precedence over anything stored in the session
      //state record, if any.  If this doesn't apply, the empty string is stored.
   "sess",            "logicalpage",     "int",                "",                                     "",
      //An enumerated constant, identifying which logical page in the tree of pages is the current page.
      //This is set on traversals by the "logpage=" GET/POST parameter.  A given physical page may
      //exist at more than location in the logical page hierarchy.  The entire hierarchy is on a
      //diagram in the documentation.  If there is no current context, the value of 0 is stored.
   "sess",            "curuser",         "int",                "",                                     "",
      //The user that is currently being edited or is otherwise of interest, by the index.  If there is
      //no user of interest, zero is stored.
   "sess",            "userlistactive",  "int",                "",                                     "",
      //1 if the user list to return to is the active user list, or 0 if the list to return to is the
      //inactive user list.
   "sess",            "curresource",     "int",                "",                                     "",
      //The resource that is currently being edited or is otherwise of interest, by the index.  If there
      //is no resource of interest, zero is stored.
   "sess",            "curreservation",     "int",             "",                                     "",
      //The reservation that is currently being edited or is otherwise of interest, by the index.  If
      //there is no reservation of interest, zero is stored.
   //=====================================================================================================
   //=====================================================================================================
   //====  L O G E  ======================================================================================
   //=====================================================================================================
   //=====================================================================================================
   //One record for each log entry.  This table should be pruned by the daily maintenance script, so that
   //it stays a reasonable size.
   //=====================================================================================================
   "loge",            "idx",             "int",                "AUTO_INCREMENT NOT NULL PRIMARY KEY",  "",
      //The integer index of the log entry.  This is used for uniqueness and to give an ordering.
      //An SGUID could also be used.
   "loge",            "type",            "int",                "",                                     "",
      //An integer (these constants are defined in log.inc and/or logview.inc) giving what type of
      //record this is.  There are many differen types.
   "loge",            "utime",           "varchar(22)",        "",                                     "",
      //A UTIME stamp gathered at the time the log entry is made.  This is a definitive reference
      //as to Unix time.  If for some reason a UTIME is not available, the empty string is used.
   "loge",            "stime",           "varchar(22)",        "",                                     "",
      //An STIME stamp gathered at the time the script starts execution.  Note that this time is more
      //sloppy than the Unix time, because it is gathered at the start of the page.  The UTIME
      //above is authoritative.  If there are any extremely weird problems (such as a page hanging
      //or executing slowly, the UTIME would give more insight than this STIME.
   "loge",            "ip",              "varchar(40)",        "",                                     "",
      //The IP address as reported by the server.  With IP version 6 coming up, the IP
      //address could be over 20 characters--define it as 40 to be safe.
   "loge",            "userid",          "varchar(20)",        "",                                     "",
      //The userid of anyone authenticated at the time the entry is made.  If nobody is
      //authenticated, the empty string is used.
   "loge",            "sid",             "varchar(66)",        "",                                     "",
      //Any session identifier that was passed in by cookie or was swapped in by authentication
      //at the time the log entry was made. 
   "loge",            "scriptfile",      "varchar(1024)",      "",                                     "",
      //The main file being executed, including the path from the document root.  This will be one
      //of the main script files of FBO-Prime.
   "loge",            "getpostpars",     "varchar(1024)",      "",                                     "",
      //The GET and/or POST parameters that are relevant to the log entry.
   "loge",            "phpfilek",        "varchar(1024)",      "",                                     "",
      //The caller's value of __FILE__ when the log-making function is called.
   "loge",            "phplinek",        "int",                "",                                     "",
      //The caller's value of __LINE__ when the log-making function is called. 
   "loge",            "logentry",        "varchar(4000)",      "",                                     ""
      //The text of the log entry.  This adds any needed description to the event.
) ;

if ($argc == 1)
   {
   //The no-parameters case, as expected.

   $handle = mysql_connect(CONFIG_MYSQL_SERVER, CONFIG_MYSQL_USERNAME, CONFIG_MYSQL_PASSWORD);
   $handle_copy = $handle;
   if ($handle === FALSE)
      {
      echo "ERROR:  Unable to connect and/or authenticate to MySQL database.\n";
      exit(1);
      }

   $result = mysql_select_db(CONFIG_MYSQL_DATABASE, $handle);
   if ($result === FALSE)
      {
      echo "ERROR:  Unable to select MySQL database \"" . CONFIG_MYSQL_DATABASE . "\".\n";
      exit(1);
      }

   populate_db($handle, $dbdesign);
   hline();

   $result = mysql_close($handle);
   if ($result === FALSE)
      {
      echo "ERROR:  Unable to close MySQL connection.\n";
      exit(1);
      }
   
   exit(0);
   }
else
   {
   echo "ERROR:  This command accepts no command-line parameters.\n";
   exit(1);
   }

//If we're here, success.  Per the standard Unix way of thinking
//say nothing.  Silence means OK.
exit(0);
//
//--------------------------------------------------------------------------------
//End of $RCSfile: dbcreate.php,v $.
//--------------------------------------------------------------------------------
?>
