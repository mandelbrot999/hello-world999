<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/fboprime/sw/phplib/schedview.inc 205 2018-07-15 19:00:51Z dashley $
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
