<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/fboprime/sw/phplib/sess.inc 205 2018-07-15 19:00:51Z dashley $
//--------------------------------------------------------------------------------------------------------------
//sess.inc--FboPrime Session and Authentication Management Functions and Constants
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
//Implement session and authentication functions.
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
//--------------------------------------------------------------------------------------------------------------
require_once("global.inc");
require_once("log.inc");
require_once("passwd.inc");
require_once("perm.inc");
require_once("sguid.inc");
require_once("sid.inc");
require_once("strfunc.inc");
require_once("usrs.inc");
require_once("utime.inc");
//
//--------------------------------------------------------------------------------------------------------------
//Constants for database storage, software internals, function parameters, and function return values of
//this module.
//
//Session reap time, in seconds.  This is how old an inactive session must be in order to reap it by
//nightly cron job.
//
define("SESS_REAP_INACTIVE_TIME",                  172800 );  //48 hours, in seconds.                        
//
//
//Function return values.
define("SESS_RCODE_SUCCESS",                            0 );  //Successful action.
define("SESS_RCODE_SUCCESS_TEMP_PASSWORD",              1 );  //Authentication action was successful, but
                                                              //authentication was performed based on the
                                                              //temporary password.  The user should be
                                                              //prompted to change their password as soon as
                                                              //possible.
define("SESS_RCODE_FAIL_USERID_EXPIRED_INACTIVE",       2 );  //Intended action failed because the userid
                                                              //and password specified authenticated
                                                              //properly, but the underlying userid is either
                                                              //expired or inactive.  The user should be
                                                              //granted no privileges and instructed to contact
                                                              //the FBO.
define("SESS_RCODE_FAIL_USERID_NOEXIST",                3 );  //Intended action failed because specified
                                                              //userid does not exist.
define("SESS_RCODE_FAIL_PASSWD",                        4 );  //Intended action failed because the password
                                                              //supplied was incorrect.
//
//Session constants for the logical page currently being visited.
//
define("SESS_LPAGE_UNDEFINED",                          0);   //Not yet defined or invalid SQL query
                                                              //result.
define("SESS_LPAGE_SCHEDDAYVIEW",                       1);   //Day view scheduler.
define("SESS_LPAGE_SCHEDWEEKVIEW",                      2);   //Week view scheduler.
define("SESS_LPAGE_SCHEDMONTHVIEW",                     3);   //Month view scheduler.
define("SESS_LPAGE_LOGRESOURCESCHEDULER",               4);   //Log file viewing.
define("SESS_LPAGE_DBSTATS",                            5);   //Database statistics.
define("SESS_LPAGE_RESOURCELIST",                       6);   //Resource list (or all resources).    
define("SESS_LPAGE_RESOURCERENUMBER",                   7);   //Resource list.    
define("SESS_LPAGE_RESOURCEVIEW",                       8);   //Resource view (of individual resource).    
define("SESS_LPAGE_RESOURCEEDIT",                       9);   //Resource edit (of individual resource).    
define("SESS_LPAGE_RESOURCEADD",                       10);   //Resource edit (of individual resource).    
define("SESS_LPAGE_USERSACTIVELIST",                   11);   //Users list (active).
define("SESS_LPAGE_USERSINACTIVELIST",                 12);   //Users list (active).
define("SESS_LPAGE_USERSVIEW",                         13);   //User view.
define("SESS_LPAGE_USERSEDIT",                         14);   //User edit.
define("SESS_LPAGE_USERSADD",                          15);   //User add.
define("SESS_LPAGE_MYRESERVATIONSLIST",                16);   //Self-reservations list.
//
//
//--------------------------------------------------------------------------------------------------------------
//Eats the session identifier cookie, if any exists on the browser side.
//
function SESS_eat_fbopsid_cookie()
   {
   setcookie("fbopsid",                    //Cookie name.
             FALSE,                        //Value.  FALSE means eat the cookie.
             0,                            //Expire when browser closes.  The PHP documentation
                                           //suggests to set this to a time well before the current
                                           //time, but I don't believe this is necessary to eat a cookie.
             CONFIG_URL_FSPATH . "/",      //Path within the domain.
             CONFIG_URL_DOMAIN,            //Domain.
             0);                           //Don't require secure connection.
   }
//
//--------------------------------------------------------------------------------------------------------------
//Issues the SID to the browser.
//
function SESS_issue_fbopsid_cookie($sid)
   {
   setcookie("fbopsid",                    //Cookie name.
             $sid,                         //Value.  FALSE means eat the cookie.
             0,                            //Value.  0 (according to the manual) means to keep cookie
                                           //until browser closed.
             CONFIG_URL_FSPATH . "/",      //Path within the domain.
             CONFIG_URL_DOMAIN,            //Domain.
             0);                           //Don't require secure connection.
   }
//
//--------------------------------------------------------------------------------------------------------------
//Inserts a new record into the SESS database, using the passed associative array to assign the fields.
//Each element of the associative array is indexed by a field name.
//
//The function returns the integer index of the record added.
//
//This operation cannot fail.  The autoincrement index is the primary key, so no duplicates or other
//error conditions are meaningful.
//
function SESS_insert($arg)
   {
   global $GLOBAL_dbhandle;
   global $GLOBAL_dblocked;

   //Build the query string with each successive parameter.
   //
   //sguid
   //-----
   if (! isset($arg["sguid"]))
      $pushval = "";
   else
      $pushval = $arg["sguid"];
   $query_string = "INSERT INTO sess SET sguid=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"";
   //
   //ip
   //------
   if (! isset($arg["ip"]))
      $pushval = "";
   else
      $pushval = $arg["ip"];
   $query_string .= (", ip=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //sid
   //---
   if (! isset($arg["sid"]))
      $pushval = "";
   else
      $pushval = $arg["sid"];
   $query_string .= (", sid=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //revaltime
   //---------
   if (! isset($arg["revaltime"]))
      $pushval = "";
   else
      $pushval = $arg["revaltime"];
   $query_string .= (", revaltime=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //lifetime
   //--------
   if (! isset($arg["lifetime"]))
      $pushval = 0;
   else
      $pushval = $arg["lifetime"];
   $query_string .= (", lifetime=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //usrsidx
   //-------
   if (! isset($arg["usrsidx"]))
      $pushval = 0;
   else
      $pushval = $arg["usrsidx"];
   $query_string .= (", usrsidx=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //menulvl
   //-------
   if (! isset($arg["menulvl"]))
      $pushval = 0;
   else
      $pushval = $arg["menulvl"];
   $query_string .= (", menulvl=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //pagereloadtime
   //--------------
   if (! isset($arg["pagereloadtime"]))
      $pushval = 0;
   else
      $pushval = $arg["pagereloadtime"];
   $query_string .= (", pagereloadtime=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //sddt
   //----
   if (! isset($arg["sddt"]))
      $pushval = "";
   else
      $pushval = $arg["sddt"];
   $query_string .= (", sddt=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //sdtim
   //-----
   if (! isset($arg["sdtim"]))
      $pushval = "";
   else
      $pushval = $arg["sdtim"];
   $query_string .= (", sdtim=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //logicalpage
   //-----------
   if (! isset($arg["logicalpage"]))
      $pushval = 0;
   else
      $pushval = $arg["logicalpage"];
   $query_string .= (", logicalpage=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //curuser
   //-------
   if (! isset($arg["curuser"]))
      $pushval = 0;
   else
      $pushval = $arg["curuser"];
   $query_string .= (", curuser=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //curresource
   //-----------
   if (! isset($arg["curresource"]))
      $pushval = 0;
   else
      $pushval = $arg["curresource"];
   $query_string .= (", curresource=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //curreservation
   //--------------
   if (! isset($arg["curreservation"]))
      $pushval = 0;
   else
      $pushval = $arg["curreservation"];
   $query_string .= (", curreservation=\"" . mysql_real_escape_string ($pushval, $GLOBAL_dbhandle) . "\"");
   //
   //Execute the query to insert the record.
   $result = mysql_query($query_string, $GLOBAL_dbhandle);
   //
   //If the insert failed, our caller gets FALSE.
   if ($result == FALSE)
      {
      $rv = FALSE;
      }
   else
      {
      //The insert was successful.  Figure out the index that was assigned.
      $result = mysql_query("SELECT LAST_INSERT_ID()");

      //If we have a failure, the caller gets FALSE, otherwise the caller gets the
      //index.
      if ($result === FALSE)
         {
         $rv = FALSE;
         }
      else
         {
         //Pick apart the result.
         $row = mysql_fetch_array($result, MYSQL_NUM);

         //Extract the integer.
         $rv = $row[0];

         //Free the result memory.
         mysql_free_result($result);
         }
      }

   //Return the result.
   return($rv);
   }
//
//--------------------------------------------------------------------------------------------------------------
//Retrieves a two dimensional associative array corresponding to the SESS record with
//the passed SID, or FALSE if the record does not exist.
//
function SESS_retrieve_by_sid($sid)
   {
   global $GLOBAL_dbhandle;

   //Form the query string.
   $query_string = "SELECT * FROM sess WHERE sid=\""
                   .
                   mysql_real_escape_string($sid, $GLOBAL_dbhandle)
                   .
                   "\"";

   //Execute the query.
   $result = mysql_query($query_string, $GLOBAL_dbhandle);

   if ($result === FALSE)
      {
      //Unknown query failure.  Return FALSE to the caller.  No need to free,
      //as this is not a result.
      $rv = FALSE;
      }
   else
      {
      //Figure out how many rows in the result.
      $nrows = mysql_num_rows($result);

      if ($nrows == 0)
         {
         //No rows in the result.  The query failed to give us a record, but still
         //we need to free the result set.

         //Free the result.
         mysql_free_result($result);
      
         //The caller gets FALSE.  No record with that SID.
         $rv = FALSE;   
         }
      else
         {
         //We have at least one record.  Assume just one, because the SID is supposed
         //to be unique.
         $rv = mysql_fetch_assoc($result);  //Get the associative record.

         //Free the result.
         mysql_free_result($result);
         }

      //Return the value to the caller.
      return($rv);
      }
   }
//
//--------------------------------------------------------------------------------------------------------------
//Deletes the server-side session information corresponding to the passed SID, if it exists in the
//SESS table.  Returns TRUE if at least one record is deleted, or FALSE otherwise.
//
function SESS_delete_by_sid($sid)
   {
   global $GLOBAL_dbhandle;

   //Form the query string.
   $query_string = "DELETE FROM sess WHERE sid=\""
                   .
                   mysql_real_escape_string($sid, $GLOBAL_dbhandle)
                   .
                   "\"";

   //Execute the query.
   mysql_query($query_string, $GLOBAL_dbhandle);

   //Figure out how many rows were affected.
   $ar = mysql_affected_rows($GLOBAL_dbhandle);

   //Return the right value to the caller.
   if ($ar <= 0)
      return(FALSE);
   else
      return(TRUE);
   }
//
//--------------------------------------------------------------------------------------------------------------
//Description:
//  Authenticates a supplied password against the non-temporary password hash stored with the supplied
//  database record from the user information.  There is also a possibility that the non-temporary
//  hash field is the empty string, which means that no password will authenticate.
//
//  Returns TRUE if the authentication was successful or FALSE otherwise.
//
function SESS_nontemppwauth($userinfo, $password)
   {
   if (PASSWD_pwd_hash_auth($userinfo["pwhash"], $password) == 1)
      return(TRUE);
   else
      return(FALSE);
   }
//
//--------------------------------------------------------------------------------------------------------------
//Description:
//  Authenticates a supplied password against the temporary password hash stored with the supplied
//  database record from the user information.  In order to authenticate, the the temporary
//  password also must not be expired.
//
//  Returns TRUE if the authentication was successful or FALSE otherwise.
//
function SESS_temppwauth($userinfo, $password)
   {
   global $GLOBAL_utime_ut;

   if (!strlen($userinfo["lostpwgentime"]) || !strlen($userinfo["lostpwhash"]))
      {
      return(FALSE);
      }
   else
      {
      if (
         UTIME_time_diff_coarse_28($GLOBAL_utime_ut, $userinfo["lostpwgentime"])
         > //Waiting time elapsed.
         (CONFIG_LOGIN_REC_TEMP_PW_LIFETIME * 60) //*60 because constant in minutes.
         )
         {
         return(FALSE);  //Temporary password has expired, so can't authenticate.
         }
      else
         {
         if (PASSWD_pwd_hash_auth($userinfo["lostpwhash"], $password) == 1)
            return(TRUE);
         }
      }
 
   //If we're lost and get here, authentication failed.
   return(FALSE);
   }
//
//--------------------------------------------------------------------------------------------------------------
//Description:
//  Opens a new session on the server based on the passed user information and returns the
//  SID.
//
function SESS_open_new_uinfo($userinfo)
   {
   global $GLOBAL_client_ip;
   global $GLOBAL_utime_ut;

   //Populate the SGUID.
   $sess["sguid"]        = SGUID_sguid();

   //Populate the IP address.
   $sess["ip"]           = $GLOBAL_client_ip;

   //Populate the session identifier.
   $sid                  = SID_sid();
   $sess["sid"]          = $sid;

   //Populate the revalidation time.
   $sess["revaltime"]    = $GLOBAL_utime_ut;

   //Populate the lifetime.  The lifetime is either the value stored in the permission string (if it
   //exists there), or else the default value.
   $sess["lifetime"] = PERM_get_val_from_string($userinfo["perm"], "sesslifetimedefault");
   if ($sess["lifetime"] === FALSE)                      //If that permission/attribute does not exist.
      $sess["lifetime"] = CONFIG_SESS_LIFETIME_DEFAULT;

   //Populate the index of the relevant user.
   $sess["usrsidx"]      = $userinfo["idx"];

   //Insert the record into the database.
   SESS_insert($sess);

   //Return the session ID to the caller.
   return($sid);
   }
//
//--------------------------------------------------------------------------------------------------------------
//Description:
//  Authenticates a supplied userid and password, and returns result information to the caller.
//  If the userid/password authenticate, retract the old cookie, open a new session on the server side,
//  and issue a new cookie.
//
//  This function is called from the main scheduling page when a userid/password is entered.
//
//  If the userid supplied corresponds to a non-existent account:
//
//     a)Destroy any existing server-side session information based on the current SID cookie.
//     b)Eat the current SID cookie, if any, on the client side.
//     c)Set the $curuserinfo to FALSE.
//     d)Set the $cursessioninfo to FALSE.
//     e)Set the $rcode to SESS_RCODE_FAIL_USERID_NOEXIST.
//
//  Else if the userid exists and the password authenticates:
//
//     If the account is inactive or expired:
//
//        a)Destroy any existing server-side session information based on the current SID
//          cookie.
//        b)Eat the current SID cookie, if any, on the client side.
//        c)Set the $curuserinfo to FALSE.
//        d)Set the $cursessioninfo to FALSE.
//        e)Set the $rcode to SESS_RCODE_FAIL_USERID_EXPIRED_INACTIVE.
//
//     Else if authentication was successful based on a temporary password:
//
//        a)Destroy any existing server-side session information based on the current SID
//          cookie.
//        b)Open a new session on the server side.
//        c)Issue a new SID cookie to the client.
//        d)Set the $curuserinfo to the user specified.
//        e)Set the $cursessioninfo to the newly-created session.
//        f)Set the $rcode to SESS_RCODE_SUCCESS_TEMP_PASSWORD.
//
//     Else if authentication was successful:
//
//        a)Destroy any existing server-side session information based on the current SID
//          cookie.
//        b)Open a new session on the server side.
//        c)Issue a new SID cookie to the client.
//        d)Set the $curuserinfo to the user specified.
//        e)Set the $cursessioninfo to the newly-created session.
//        f)Set the $rcode to SESS_RCODE_SUCCESS.
//
//  Else if the userid exists but the password does not authenticate:
//
//     a)Destroy any existing server-side session information based on the current SID
//       cookie.
//     b)Eat the current SID cookie, if any, on the client side.
//     c)Set the $curuserinfo to FALSE.
//     d)Set the $cursessioninfo to FALSE.
//     e)Set the $rcode to SESS_RCODE_FAIL_PASSWD.
//
//Return Value:
//  $rcode          : Set to a constant defined at the start of this file to indicate
//                    what occurred.
//  $curuserinfo    : Set to an associative array containing full user information
//                    about a user who logs in, or FALSE if no user has successfully
//                    authenticated.
//  $cursessioninfo : An associative array containing the complete record for the now
//                    active session, or FALSE if no session is active.
//
function SESS_userid_pwd_authenticate_open_session($userid, $password, &$rcode, &$curuserinfo, &$cursessioninfo)
   {
   global $PAR_fbopsid;
   global $GLOBAL_stime_string; 
   global $GLOBAL_client_ip;

   //Condition the userid to exclude forbidden characters.
   $userid = STRFUNC_force_into_subset($userid, "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");

   //Convert the userid to all lower-case.  This is the canonical form for userids.
   $userid = StrToLower($userid);

   //Remove all invalid characters from the password.  However, don't convert it to lower-case.  Passwords are
   //case-sensitive.
   $password = STRFUNC_force_into_subset($password, "-0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");

   //Try to obtain the user information from the database corresponding to the userid.
   $curuserinfo =  USRS_retrieve_by_userid($userid);

   //print_r($curuserinfo);
   //return;

   //If the userid does not exist, return the correct error code.
   if ($curuserinfo === FALSE)
      {
      //Log the authentication failure.
      LOG_log(LOG_ET_LOGIN_FAIL, 
              $GLOBAL_stime_string, 
              $GLOBAL_client_ip, 
              "", 
              ($PAR_fbopsid === FALSE) ? ("") : ($PAR_fbopsid), 
              $_SERVER["PHP_SELF"],
              "",
              __FILE__,
              __LINE__,
              "Password authentication failure, non-existent userid=\"" .  $userid . "\".");

      //Destroy any existing server-side session information based on the current SID cookie.
      if ($PAR_fbopsid !== FALSE)
         SESS_delete_by_sid($PAR_fbopsid);

      //Eat the client-side cookie.
      SESS_eat_fbopsid_cookie();

      //Set the $curuserinfo to FALSE.
      $curuserinfo = FALSE;

      //Set the $cursessioninfo to FALSE.
      $cursessioninfo = FALSE;
 
      //Set the $rcode to SESS_RCODE_FAIL_USERID_NOEXIST.
      $rcode = SESS_RCODE_FAIL_USERID_NOEXIST;

      return;
      }

   //If the userid exists but is not active, refuse the authentication.
   if ($curuserinfo["status"] != USRS_STATUS_ACTIVE)
      {
      //Log the authentication failure.
      LOG_log(LOG_ET_LOGIN_FAIL, 
              $GLOBAL_stime_string, 
              $GLOBAL_client_ip, 
              "", 
              ($PAR_fbopsid === FALSE) ? ("") : ($PAR_fbopsid), 
              $_SERVER["PHP_SELF"],
              "",
              __FILE__,
              __LINE__,
              "Password authentication failure, expired or inactive userid=\"" .  $userid . "\".");

      //Destroy any existing server-side session information based on the current SID cookie.
      if ($PAR_fbopsid !== FALSE)
         SESS_delete_by_sid($PAR_fbopsid);

      //Eat the client-side cookie.
      SESS_eat_fbopsid_cookie();

      //Set the $curuserinfo to FALSE.
      $curuserinfo = FALSE;

      //Set the $cursessioninfo to FALSE.
      $cursessioninfo = FALSE;
 
      //Set the $rcode to SESS_RCODE_FAIL_USERID_EXPIRED_INACTIVE.
      $rcode = SESS_RCODE_FAIL_USERID_EXPIRED_INACTIVE;

      return;
      }

   //The user exists and the user's status is active.  Figure out if the password is consistent
   //with the stored non-temporary password.
   //
   if (SESS_nontemppwauth($curuserinfo, $password))
      {
      //The password supplied matches the non-temporary password hash in the database.
      //
      //Open a new session on the server side.
      $sid = SESS_open_new_uinfo($curuserinfo);
      //
      //Log the authentication success.
      LOG_log(LOG_ET_LOGIN_OK, 
              $GLOBAL_stime_string, 
              $GLOBAL_client_ip, 
              $userid, 
              $sid, 
              $_SERVER["PHP_SELF"],
              "",
              __FILE__,
              __LINE__,
              "Password authentication.");
      //
      //Issue the new cookie to the browser.  It isn't necessary to replace any existing old,
      //as this one will just replace it.
      SESS_issue_fbopsid_cookie($sid);
      //
      //The current user information has already been obtained.  Pull the
      //session information.
      $cursessioninfo = SESS_retrieve_by_sid($sid);
      //
      //Set the return code.
      $rcode = SESS_RCODE_SUCCESS;
      //
      return;
      }


   //The user exists and the user's status is active.  Figure out if the password is consistent
   //with the stored temporary password.
   //
   if (SESS_temppwauth($curuserinfo, $password))
      {
      //The password supplied matches the temporary password hash in the database.
      //
      //Open a new session on the server side.
      $sid = SESS_open_new_uinfo($curuserinfo);
      //
      //Log the authentication success.
      LOG_log(LOG_ET_LOGIN_OK, 
              $GLOBAL_stime_string, 
              $GLOBAL_client_ip, 
              $userid, 
              $sid, 
              $_SERVER["PHP_SELF"],
              "",
              __FILE__,
              __LINE__,
              "Temporary password authentication.");
      //
      //Issue the new cookie to the browser.  It isn't necessary to replace any existing old,
      //as this one will just replace it.
      SESS_issue_fbopsid_cookie($sid);
      //
      //The current user information has already been obtained.  Pull the
      //session information.
      $cursessioninfo = SESS_retrieve_by_sid($sid);
      //
      //Set the return code.
      $rcode = SESS_RCODE_SUCCESS_TEMP_PASSWORD;
      //
      return;
      }

   //If we're here, the userid was OK, but the password was wrong.
   //Log the authentication failure.
   LOG_log(LOG_ET_LOGIN_FAIL, 
           $GLOBAL_stime_string, 
           $GLOBAL_client_ip, 
           $userid, 
           ($PAR_fbopsid === FALSE) ? ("") : ($PAR_fbopsid),
           $_SERVER["PHP_SELF"],
           "",
           __FILE__,
           __LINE__,
           "Password authentication failure, bad password.");

   //Destroy any existing server-side session information based on the current SID cookie.
   if ($PAR_fbopsid !== FALSE)
      SESS_delete_by_sid($PAR_fbopsid);

   //Eat the client-side cookie.
   SESS_eat_fbopsid_cookie();

   //Set the $curuserinfo to FALSE.
   $curuserinfo = FALSE;

   //Set the $cursessioninfo to FALSE.
   $cursessioninfo = FALSE;
 
   //Set the $rcode to indicate simple password failure.
   $rcode = SESS_RCODE_FAIL_PASSWD;
   }
//
//--------------------------------------------------------------------------------------------------------------
//Logs out the user implied by the current SID cookie.  The specific actions are:
//  a)Destroy any existing server-side session information.
//  b)Eat the client side SID cookie.
//
//Return Values:
//   $curuserinfo        :  By the definition of this what this function does, FALSE.
//   $cursessioninfo     :  By the definition of this what this function does, FALSE.
//
function SESS_logout(&$curuserinfo, &$cursessioninfo)
   {
   global $PAR_fbopsid;
   global $GLOBAL_stime_string; 
   global $GLOBAL_client_ip;

   //Save the $sid cookie, so we can log it.
   $log_sid = $PAR_fbopsid;

   //Look up the session table entry.
   $cursessioninfo = SESS_retrieve_by_sid($log_sid);

   //Look up the user information based on the index stored with
   //the session.
   if ($cursessioninfo !== FALSE)
      {
      $curuserinfo = USRS_retrieve_by_idx($cursessioninfo["usrsidx"]);
      }
   else
      {
      $curuserinfo = FALSE;
      }

   //Swallow any session cookie.
   SESS_eat_fbopsid_cookie();

   //Destroy the server-side session state, if any.
   if ($PAR_fbopsid !== FALSE)
     SESS_delete_by_sid($PAR_fbopsid);

   //Log the voluntary logout.
   LOG_log(LOG_ET_LOGOUT_VOL, 
           $GLOBAL_stime_string, 
           $GLOBAL_client_ip, 
           ($curuserinfo !== FALSE) ? ($curuserinfo["userid"]) : (""), 
           ($log_sid === FALSE) ? ("") : ($log_sid), 
           $_SERVER["PHP_SELF"],
           "",
           __FILE__,
           __LINE__,
           "Logout.");


   //Return values are, by definition, FALSE.
   $curuserinfo    = FALSE;
   $cursessioninfo = FALSE;
   }
//
//--------------------------------------------------------------------------------------------------------------
//Revalidates the session using the current SID cookie.  The specific actions are:
//
//   If the SID does not exist on the server side:
//      a)Eat the current client SID cookie.
//   Else if the session has expired due to inactivity:
//      a)Destroy the server-side session state.
//      b)Eat the client-side SID cookie.
//   Else [if the session is still active]:
//      Obtain the user information.
//      If the user does not exist or is inactive:
//         a)Destroy the server-side session state.
//         b)Eat the client-side SID cookie.
//      Else
//         If the privilege escalation period has expired
//            Lower the privelege escalation level.
//         Update the revalidation time.
//
//Return Values:
//   $curuserinfo        :  An associative array containing the complete record for the currently
//                          authenticated user, or FALSE if no user is authenticated.
//   $cursessioninfo     :  An associative array containing the complete record for the currently
//                          active session, or FALSE if no session is active.
//
function SESS_revalidate(&$curuserinfo, &$cursessioninfo)
   {
   global $GLOBAL_dbhandle;
   global $GLOBAL_dblocked;
   global $PAR_fbopsid;
   global $GLOBAL_stime_string; 
   global $GLOBAL_client_ip;
   global $GLOBAL_utime_ut;

   $cursessioninfo = FALSE;
   $curuserinfo    = FALSE;

   //If the SID isn't defined, no user and no session.
   if ($PAR_fbopsid === FALSE)
      {
      $curuserinfo    = FALSE;
      $cursessioninfo = FALSE;
      return;
      }

   //Try to look up the session in the database.  If it does not exist
   //in the database, this is a bit suspicious but not impossible.  The database
   //could have been reaped while somebody left their browser open for a long time.
   //If this is the case, no session and no user.
   //
   $cursessioninfo = SESS_retrieve_by_sid($PAR_fbopsid);
   //
   if ($cursessioninfo === FALSE)
      {
      //It is suspicious.  Log it.
      LOG_log(LOG_ET_SEC_SID_FORGED, 
              $GLOBAL_stime_string, 
              $GLOBAL_client_ip, 
              "", 
              $PAR_fbopsid, 
              $_SERVER["PHP_SELF"],
              "",
              __FILE__,
              __LINE__,
              "SID cookie value does not exist in server database, and was possibly forged.");

      //Return value is no session and no user.
      $curuserinfo    = FALSE;
      $cursessioninfo = FALSE;
      return;
      }

   //Session exists.  Try to look up the user identified in the session.  If the user does not
   //exist, this is also suspicious.  The only scenario under which this might happen is if a
   //user is expired or deleted during a session.
   //   
   $curuserinfo    = USRS_retrieve_by_idx($cursessioninfo["usrsidx"]);
   //
   if ($curuserinfo === FALSE)
      {
      //It is suspicious.  Log it.
      LOG_log(LOG_ET_SEC_SID_FORGED, 
              $GLOBAL_stime_string, 
              $GLOBAL_client_ip, 
              "", 
              $PAR_fbopsid, 
              $_SERVER["PHP_SELF"],
              "",
              __FILE__,
              __LINE__,
              "User index pointed to by SID record does not exist (idx=" . (string)$cursessioninfo["usrsidx"] . ").");

      //Return value is no session and no user.
      $curuserinfo    = FALSE;
      $cursessioninfo = FALSE;
      return;
      }
   
   //If the user pointed to by the session isn't active, this probably means that
   //the user was expired or had the status changed manually during a session.
   //Destroy the server-side and client side session state, log it, and indicate
   //to the caller no user and no session.
   //If the userid exists but is not active, refuse the authentication.
   if ($curuserinfo["status"] != USRS_STATUS_ACTIVE)
      {
      //It is suspicious.  Log it.
      LOG_log(LOG_ET_SEC_SID_FORGED, 
              $GLOBAL_stime_string, 
              $GLOBAL_client_ip, 
              "", 
              $PAR_fbopsid, 
              $_SERVER["PHP_SELF"],
              "",
              __FILE__,
              __LINE__,
              "User pointed to by SID record has inactive status (idx=" . (string)$cursessioninfo["usrsidx"] . ").");

      //Destroy any existing server-side session information based on the current SID cookie.
      if ($PAR_fbopsid !== FALSE)
         SESS_delete_by_sid($PAR_fbopsid);

      //Eat the client-side cookie.
      SESS_eat_fbopsid_cookie();

      //Return value is no session and no user.
      $curuserinfo    = FALSE;
      $cursessioninfo = FALSE;
      return;
      }

   //If the session has expired due to time, then log it and force the user out.
   //
   if (UTIME_time_diff_coarse_28($GLOBAL_utime_ut, $cursessioninfo["revaltime"]) > (int)$cursessioninfo["lifetime"])
      {
      //Log it.
      LOG_log(LOG_ET_LOGOUT_TIME,
              $GLOBAL_stime_string, 
              $GLOBAL_client_ip,
              $curuserinfo["userid"],
              $PAR_fbopsid,
              $_SERVER["PHP_SELF"],
              "",
              __FILE__,
              __LINE__,
              "Session expired due to inactive time.");

      //Destroy any existing server-side session information based on the current SID cookie.
      if ($PAR_fbopsid !== FALSE)
         SESS_delete_by_sid($PAR_fbopsid);

      //Eat the client-side cookie.
      SESS_eat_fbopsid_cookie();

      //Return value is no session and no user.
      $curuserinfo    = FALSE;
      $cursessioninfo = FALSE;
      return;
      }

   //If the connecting IP of the session has changed, this is bad news and probably some type of
   //security issue.
   //
   if ($cursessioninfo["ip"] != $GLOBAL_client_ip)
      {
      //Log it.
      LOG_log(LOG_ET_SEC_LOGOUT_IP,
              $GLOBAL_stime_string, 
              $GLOBAL_client_ip,
              $curuserinfo["userid"],
              $PAR_fbopsid,
              $_SERVER["PHP_SELF"],
              "",
              __FILE__,
              __LINE__,
              "Stored session IP:" . $cursessioninfo["ip"] . " Current connection IP:" . $GLOBAL_client_ip . ".");

      //Destroy any existing server-side session information based on the current SID cookie.
      if ($PAR_fbopsid !== FALSE)
         SESS_delete_by_sid($PAR_fbopsid);

      //Eat the client-side cookie.
      SESS_eat_fbopsid_cookie();

      //Return value is no session and no user.
      $curuserinfo    = FALSE;
      $cursessioninfo = FALSE;
      return;
      }

   //All the error conditions have been ruled out.  Give the session a newer timestamp, log it, and return the
   //correct user and session information.
   mysql_query("UPDATE sess SET revaltime=\""
               . mysql_real_escape_string($GLOBAL_utime_ut, $GLOBAL_dbhandle)
               . "\" WHERE sid=\""
               . mysql_real_escape_string($PAR_fbopsid, $GLOBAL_dbhandle)
               . "\"",
               $GLOBAL_dbhandle);
   //
   LOG_log(LOG_ET_REVAL_OK,
           $GLOBAL_stime_string, 
           $GLOBAL_client_ip,
           $curuserinfo["userid"],
           $PAR_fbopsid,
           $_SERVER["PHP_SELF"],
           "",
           __FILE__,
           __LINE__,
           "Session revalidation.");

   //The $curuserinfo and $cursessioninfo values are OK for return.
   }
//
//--------------------------------------------------------------------------------------------------------------
//Decrements the current menu level, stores it in the correct session record of the database,
//and returns the new level, clipped to [0, 2].
//
//No mutual exclusion should be necessary, as a session is tied to one terminal IP--unless a user
//has multiple browsers open and is doing something unusual, there should be nothing noticeable.
//Even then it is iffy and there will be no ill effects.
//
function SESS_menulevel_decrement($sid_in, $menulevel_current)
   {
   global $GLOBAL_dbhandle;

   //Adjust the menulevel to be one smaller.
   if ($menulevel_current == 2)
      $menulevel_new = 1;
   else if ($menulevel_current == 1)
      $menulevel_new = 0;
   else
      $menulevel_new = 0;

   //Form a query to reflect assigning the new menu level to the session ID
   //record.
   $query_string = "UPDATE sess SET menulvl=\"" . (string)$menulevel_new . "\" WHERE sid=\"" . $sid_in . "\"";

   //Run the query.  We don't much care whether it fails or succeeds (nothing to be done, anyway).
   mysql_query($query_string, $GLOBAL_dbhandle);

   //Return the new value.
   return($menulevel_new); 
   }
//
//--------------------------------------------------------------------------------------------------------------
//Increments the current menu level, stores it in the correct session record of the database,
//and returns the new level, clipped to [0, 2].
//
//No mutual exclusion should be necessary, as a session is tied to one terminal IP--unless a user
//has multiple browsers open and is doing something unusual, there should be nothing noticeable.
//Even then it is iffy and there will be no ill effects.
//
function SESS_menulevel_increment($sid_in, $menulevel_current)
   {
   global $GLOBAL_dbhandle;

   //Adjust the menulevel to be one larger.
   if ($menulevel_current == 0)
      $menulevel_new = 1;
   else if ($menulevel_current == 1)
      $menulevel_new = 2;
   else
      $menulevel_new = 2;

   //Form a query to reflect assigning the new menu level to the session ID
   //record.
   $query_string = "UPDATE sess SET menulvl=\"" . (string)$menulevel_new . "\" WHERE sid=\"" . $sid_in . "\"";

   //Run the query.  We don't much care whether it fails or succeeds (nothing to be done, anyway).
   mysql_query($query_string, $GLOBAL_dbhandle);

   //Return the new value.
   return($menulevel_new); 
   }
//
//--------------------------------------------------------------------------------------------------------------
//Updates the SDDT and SDTIM associated with the session, session identifier passed.
//
//To update only SDDT or SDTIM, set the other parameter FALSE.
//
//If both parameters are FALSE, nothing will be updated.
//
function SESS_update_sddt_sdtim($sid_in, $sddt_in, $sdtim_in)
   {
   global $GLOBAL_dbhandle;

   //echo "<pre>\n";
   //print_r($sid_in);
   //print_r($sddt_in);
   //print_r($sdtim_in);
   //echo "</pre>\n";

   if (($sddt_in !== FALSE) && ($sdtim_in !== FALSE))
      {
      //Both parameters are specified, the most common case.
      $query_string = "UPDATE sess SET sddt=\"" 
                      . 
                      mysql_real_escape_string ((string)$sddt_in, $GLOBAL_dbhandle) 
                      . 
                      "\", sdtim=\""
                      . 
                      mysql_real_escape_string ((string)$sdtim_in, $GLOBAL_dbhandle)
                      .
                      "\" WHERE sid=\"" 
                      . 
                      $sid_in 
                      . 
                      "\"";

      //Run the query.  We don't much care whether it fails or succeeds (nothing to be done, anyway).
      mysql_query($query_string, $GLOBAL_dbhandle);
      }
   else if (($sddt_in === FALSE) && ($sdtim_in !== FALSE))
      {
      //Only time is specified.
      $query_string = "UPDATE sess SET sdtim=\""
                      . 
                      mysql_real_escape_string ((string)$sdtim_in, $GLOBAL_dbhandle)
                      .
                      "\" WHERE sid=\"" 
                      . 
                      $sid_in 
                      . 
                      "\"";

      //Run the query.  We don't much care whether it fails or succeeds (nothing to be done, anyway).
      mysql_query($query_string, $GLOBAL_dbhandle);
      }
   else if (($sddt_in !== FALSE) && ($sdtim_in === FALSE))
      {
      //Only date is specified.
      $query_string = "UPDATE sess SET sddt=\"" 
                      . 
                      mysql_real_escape_string ((string)$sddt_in, $GLOBAL_dbhandle) 
                      . 
                      "\" WHERE sid=\"" 
                      . 
                      $sid_in 
                      . 
                      "\"";

      //Run the query.  We don't much care whether it fails or succeeds (nothing to be done, anyway).
      mysql_query($query_string, $GLOBAL_dbhandle);
      }
   else
      {
      //Do nothing.  Neither parameter is specified.
      }
   }
//
//--------------------------------------------------------------------------------------------------------------
//Updates the logicalpage associated with a session.
//
function SESS_logicalpage_set($sid_in, $logicalpage_in)
   {
   global $GLOBAL_dbhandle;

   $query_string = "UPDATE sess SET logicalpage=\"" 
                   . 
                   mysql_real_escape_string ((string)$logicalpage_in, $GLOBAL_dbhandle) 
                   . 
                   "\" WHERE sid=\"" 
                   . 
                   $sid_in 
                   . 
                   "\"";

   //Run the query.  We don't much care whether it fails or succeeds (nothing to be done, anyway).
   mysql_query($query_string, $GLOBAL_dbhandle);
   }
//
//--------------------------------------------------------------------------------------------------------------
//Gets the logicalpage integer associated with a session.  Returns SESS_LPAGE_UNDEFINED if can't figure
//out what that is.
//
function SESS_logicalpage_get($sid_in)
   {
   global $GLOBAL_dbhandle;

   //Form the query string.
   $query_string = "SELECT logicalpage FROM sess WHERE sid=\""
                   .
                   mysql_real_escape_string($sid_in, $GLOBAL_dbhandle)
                   .
                   "\"";

   //Execute the query.
   $result = mysql_query($query_string, $GLOBAL_dbhandle);

   if ($result === FALSE)
      {
      //Unknown query failure.  Return a result code to the caller indicating
      //don't know.
      return(SESS_LPAGE_UNDEFINED);
      }
   else
      {
      //Get the integer result.
      $row = mysql_fetch_array($result, MYSQL_NUM);

      $rv = $row[0];

      //Free the result.
      mysql_free_result($result);

      //Return the appropriate.
      if($rv > 0)
         return($rv);
      else
         return(SESS_LPAGE_UNDEFINED);
      }
   }
//
//--------------------------------------------------------------------------------------------------------------
//End of $RCSfile: sess.inc,v $.
//--------------------------------------------------------------------------------------------------------------
?>
