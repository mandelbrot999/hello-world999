<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/fboprime/sw/phplib/config.inc 205 2018-07-15 19:00:51Z dashley $
//********************************************************************************
//config.inc--FboPrime FBO Configuration
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
//This file must be customized for each FBO.  The following information is
//customizable:
//
//   o MySQL database information (which host to connect to, which database to use, 
//     and the password to use for the database).
//
//   o FBO name, address, phone numbers, and e-mail contact information.
//
//   o Scheduling behavior parameters, such as how long information should be
//     retained, how close to a reservation time a reservation may be made or
//     canceled without contacting the FBO, how standby reservations are
//     handled, etc. 
//
//   o Colors.
//
//==============================================================================================================
//==============================================================================================================
//====  MySQL Information ======================================================================================
//==============================================================================================================
//==============================================================================================================
//MySQL connection configuration.  This information must be kept absolutely
//private (i.e. with this information, an attack could potentially be mounted).
//
define("CONFIG_MYSQL_SERVER",   "localhost");
define("CONFIG_MYSQL_DATABASE", "fboprimedevel");
define("CONFIG_MYSQL_USERNAME", "fboprimedevel");
define("CONFIG_MYSQL_PASSWORD", "quelle0");
//
//Prefix to use in the system logs when there is a database problem and a system log entry must be
//made.
//
define("CONFIG_MYSQL_ERR_SYSLOG_PREFIX", "FBO-PRIME");
//
//==============================================================================================================
//==============================================================================================================
//====  Web Location/URL/Cookie Options  =======================================================================
//==============================================================================================================
//==============================================================================================================
//These options control how certain URLs are formed, how cookies are issued, etc.  It is important to get
//these right, or logins won't work (among other things).
//
define("CONFIG_URL_DOMAIN",       "fboprimedevel.e3ft.com" ); //The server name as used in the URL.  This is
                                                              //used for cookies and to create some URLs.
define("CONFIG_URL_FSPATH",       "/flightschedule"        ); //The path within the base URL where the flight
                                                              //scheduler is.  This is used for cookies and
                                                              //to create some URLs.

//==============================================================================================================
//==============================================================================================================
//====  FBO Name, Address, and Other Information  ==============================================================
//==============================================================================================================
//==============================================================================================================
//FBO name and identity information.
//
define("CONFIG_FBO_NAME_LONG",     "Acme Aviation, LLC");     //Long name.
define("CONFIG_FBO_NAME_MEDIUM",   "Acme Aviation");          //Medium name.
define("CONFIG_FBO_NAME_SHORT",    "Acme");                   //Short name.
define("CONFIG_FBO_NAME_TINY",     "AA");                     //Tiny name, typically an acronym.
//--------------------------------------------------------------------------------------------------------------
//FBO physical address information.  The physical address is where a person would visit the FBO.
//
define("CONFIG_FBO_VADDRESS_COUNTRY",     "U.S.A.");          //Country.  Not normally displayed, so separated
                                                              //out.
define("CONFIG_FBO_VADDRESS_01", "123 Anywhere Lane");
define("CONFIG_FBO_VADDRESS_02", "Pleasantville IA 12345-6789");
define("CONFIG_FBO_VADDRESS",    CONFIG_FBO_VADDRESS_01 . "//" . CONFIG_FBO_VADDRESS_02 );
//--------------------------------------------------------------------------------------------------------------
//FBO correspondence address information.  For most FBOs, this will be the same as the physical
//address.
//
define("CONFIG_FBO_CADDRESS_COUNTRY",     CONFIG_FBO_VADDRESS_COUNTRY);
define("CONFIG_FBO_CADDRESS",             CONFIG_FBO_VADDRESS_01 . "//" . CONFIG_FBO_VADDRESS_02 );
//--------------------------------------------------------------------------------------------------------------
//FBO package delivery address information.  For most FBOs, this will be the same as the physical
//address.
//
define("CONFIG_FBO_PADDRESS_COUNTRY",     CONFIG_FBO_VADDRESS_COUNTRY);
define("CONFIG_FBO_PADDRESS",             CONFIG_FBO_VADDRESS_01 . "//" . CONFIG_FBO_VADDRESS_02 );
//--------------------------------------------------------------------------------------------------------------
//FBO phone numbers.
//
define("CONFIG_FBO_OPHONE",               "123-456-7890"   );    //The general office phone number.
define("CONFIG_FBO_SPHONE",               CONFIG_FBO_OPHONE);    //The phone number to use for scheduling matters.
define("CONFIG_FBO_FPHONE",               CONFIG_FBO_OPHONE);    //The FAX number.
define("CONFIG_FBO_PPHONE",               CONFIG_FBO_OPHONE);    //The phone number to use for package delivery.
//
//--------------------------------------------------------------------------------------------------------------
//Automatically-generated e-mail options.
//
define("CONFIG_FBO_AUTOMAIL_FROM",        "automailer@acmeaviation.com");  //Address that e-mail should be from.
define("CONFIG_FBO_AUTOMAIL_LINELENGTH",  69                           );  //Line length of automatically-generated
                                                                           //e-mail.  69 should not be exceeded
                                                                           //due to documentation of mail() function.
//
//Returns the footer text to be used in automatically-generated e-mails.  Has to be defined
//as a function to prevent evaluation of global variables before they have been set.
//
function CONFIG_fbo_automail_footer_text()
   {
   global $GLOBAL_stime_year;
   global $GLOBAL_stime_month;
   global $GLOBAL_stime_day;
   global $GLOBAL_stime_hour;
   global $GLOBAL_stime_minute;

   $hyphen_line = "";
   for ($i=0; $i<(CONFIG_FBO_AUTOMAIL_LINELENGTH + 1); $i++)
      $hyphen_line .= "-";

   return(
         $hyphen_line 
         .
         " "
         .
         "This e-mail was automatically generated by the server on "
         .
         DATEFUNC_stdlongdate_w_dow($GLOBAL_stime_year, $GLOBAL_stime_month, $GLOBAL_stime_day)
         .
         " at "
         .
         DATEFUNC_stdtimenosec($GLOBAL_stime_hour, $GLOBAL_stime_minute)
         .
         "  "
         .
         "Please contact "
         .
         CONFIG_FBO_NAME_LONG
         .
         " at "
         .
         CONFIG_FBO_OPHONE
         .
         " if you have any questions or concerns about this e-mail.  "
         .
         "Please do not reply to this e-mail, as it is "
         .
         "automatically generated and replies are not processed."
         );
   }
//
//
//==============================================================================================================
//==============================================================================================================
//====  Time Locale  ===========================================================================================
//==============================================================================================================
//==============================================================================================================
//Time locale is tricky because of U.S. daylight savings time, which is sometimes problematic because of 
//local legislation and pending legislation being inconsistent with the Linux code base.  For that reason,
//the translation between the server's time and the client local time used for scheduling is handled with a 
//function in the CONFIG file--that gives the option of making very sophisticated mappings if it ever becomes
//necessary.
//
//This mapping is provided because the server's time may be different than the time at the FBO.  It would be
//possible, for example, to have an FBO in Los Angeles, California, USA served by a server in Paris, France.
//
//If you use FBO-Prime and have developed alternate mappings, please e-mail them to the authors so they
//can be included in the documentation.
//
function CONFIG_unix_sched_time_map( $unix_seconds,         //Input, Unix server seconds, string (string to
                                                            //deal with the 2037 A.D. Unix epoch issue).
                                     $unix_nanoseconds,     //Input, Unix server nanoseconds, integer, 0-999,999,999.
                                    &$sched_year,           //Output, client locale year, integer, 2,000-2,099.
                                    &$sched_month,          //Output, client locale month, integer, 1-12.
                                    &$sched_day,            //Output, client locale day of month, integer, 1-31.
                                    &$sched_hour,           //Output, client locale hour, integer, 0-23.
                                    &$sched_minute,         //Output, client locale minute, integer, 0-59.
                                    &$sched_second,         //Output, client locale second, integer, 0-59.
                                    &$sched_microsecond,    //Output, client locale microsecond, integer, 0-999,999.
                                    &$sched_dow             //Output, day of week, integer, 0-6, 0=Sunday.
                                     )
   {
   //At the present time, should use the built-in PHP functions to convert from integer seconds to
   //the time and so on.  Later on, may do it another way.  The built-in PHP functions will probably
   //not work for anything over 2037.  Probably want to use bcmath, subtract out the GMT seconds
   //at midnight on Jan 1, 2000, etc.
   
   //Integer Unix seconds for use with PHP date() function--simple typecast should work until 2037 A.D.
   $unix_seconds_int = (int)$unix_seconds;
  
   //Integer year in locale.
   $sched_year   = (int) date("Y", $unix_seconds_int);

   //Integer month in locale.
   $sched_month  = (int) date("n", $unix_seconds_int);
   
   //Integer day in locale.
   $sched_day    = (int) date("j", $unix_seconds_int);
   
   //Integer hour in locale.
   $sched_hour   = (int) date("G", $unix_seconds_int);
   
   //Integer minute in locale.
   $sched_minute_string 
                 =       date("i", $unix_seconds_int);
   if (SubStr($sched_minute_string, 0, 1) == "0")
      $sched_minute_string = SubStr($sched_minute_string, 1, 1);
   $sched_minute = (int)$sched_minute_string;

   //Integer second in locale.
   $sched_second_string 
                 =       date("s", $unix_seconds_int);
   if (SubStr($sched_second_string, 0, 1) == "0")
      $sched_second_string = SubStr($sched_second_string, 1, 1);
   $sched_second = (int)$sched_second_string;
   
   //Integer microseconds in locale.  Since any locale can only adjust by
   //integer seconds, the fractional time is carried through.
   $sched_microsecond = $unix_nanoseconds / 1000;

   //Integer day of week in locale.
   $sched_dow  = (int) date("w", $unix_seconds_int);
   }
//
//==============================================================================================================
//==============================================================================================================
//====  Miscellaneous Global Options  ==========================================================================
//==============================================================================================================
//==============================================================================================================
//Time format.
//
define("CONFIG_TIME_FORMAT_24HR",     FALSE);  //Change to TRUE for military time.
//
//Date format.
//
define("CONFIG_DATE_FORMAT_EUROPEAN", FALSE);  //Change to TRUE to get European dates (DD/MM/YY).
//
//==============================================================================================================
//==============================================================================================================
//====  Global Appearance Options  =============================================================================
//==============================================================================================================
//==============================================================================================================
//Default color used for most backgrounds, etc. to give a consistent color scheme.
define("CONFIG_GLOBAL_COLOR_BACKGROUND",            "AAAACC");
//
//Default colors used for small banner bars, such as appear in the scheduling
//mini-calendar.
define("CONFIG_GLOBAL_BANNERBAR_MINI_A",            "ADD8E6");
define("CONFIG_GLOBAL_BANNERBAR_MINI_B",            "888888");
//
//Color used for unvisited, visited, and active links.
define("CONFIG_GLOBAL_COLOR_LINK",                 "4040C0"                      );
define("CONFIG_GLOBAL_COLOR_UVLINK",               CONFIG_GLOBAL_COLOR_LINK      );
define("CONFIG_GLOBAL_COLOR_VLINK",                CONFIG_GLOBAL_COLOR_LINK      );
define("CONFIG_GLOBAL_COLOR_ALINK",                CONFIG_GLOBAL_COLOR_LINK      );
//
//Colors used for serious error notices.
define("CONFIG_GLOBAL_COLOR_ERROR_BG",                 "FF8080"                  );
define("CONFIG_GLOBAL_COLOR_ERROR_TEXT",               "000000"                  );
//
//Whether to generate pretty HTML (pretty = formatted for human viewing).  Pretty
//HTML is good for human viewing and useful in debugging, but takes longer for the browser to load,
//especially over a slow communication channel.
define("CONFIG_HTML_PRETTY",                       TRUE);
//
//==============================================================================================================
//==============================================================================================================
//====  Scheduling Day View Appearance Options  ================================================================
//==============================================================================================================
//==============================================================================================================
//Color used for the background of the login box, choices, mini-calendars.
define("CONFIG_SCHED_COLOR_BACKGROUND",            CONFIG_GLOBAL_COLOR_BACKGROUND);
//
//Color used for the table cells displaying time.
define("CONFIG_SCHED_COLOR_TABLE_TIME_CELL",       CONFIG_GLOBAL_COLOR_BACKGROUND);
//
//Colors used for calendar dates in the mini-calendar when the day is both the current
//day and the one being viewed, the calendar day only, and the day being viewed only.
define("CONFIG_SCHED_COLOR_MINICAL_CURVIEW",       "FFFFFF"                      );
define("CONFIG_SCHED_COLOR_MINICAL_CURONLY",       "5F9EA0"                      );
define("CONFIG_SCHED_COLOR_MINICAL_VIEWONLY",      "3CB371"                      );
//
//Colors used for cells in the scheduling matrix.
define("CONFIG_SCHED_COLOR_DSMAT_THEAD",           "AAAAAA"                      );  //Top/bot column headings.
define("CONFIG_SCHED_COLOR_DSMAT_LHEAD",           "AAAAAA"                      );  //Left row headings.
define("CONFIG_SCHED_COLOR_DSMAT_RIDLE",           "FFFFFF"                      );  //Idle reservation cells.
define("CONFIG_SCHED_COLOR_DSMAT_RBANN",           "80FF80"                      );  //Banner reservation cells.
define("CONFIG_SCHED_COLOR_DSMAT_RACTV",           "8080FF"                      );  //Active reservation cells.
define("CONFIG_SCHED_COLOR_DSMAT_RSTBY",           "B0B0B0"                      );  //Standby reservation cells.
//
//==============================================================================================================
//==============================================================================================================
//====  Scheduling Behavior Options  ===========================================================================
//==============================================================================================================
//==============================================================================================================
//The number of months before and after the current date where a user is able to view and (in the future
//only) change the schedule.  The limit works in a whole month sense, i.e. either an entire month is or is
//not viewable and schedulable.  Both of these limits work in a <= or >= sense.  For the lower limit,
//   PRES   -   PAST   <=   PAST_LIMIT
//and for the upper limit,
//   FUTU   -   PRES   <=   FUTURE_LIMIT
//So, for example, a limit of one for both would allow one to view the past month and the next month.
//
define("CONFIG_SCHED_SCHEDACC_PREV_MO",            4       );
define("CONFIG_SCHED_SCHEDACC_FUTU_MO",            7       );
//
//The lockout period where a user can't make reservations any fewer than this many hours before the
//scheduled time.
define("CONFIG_SCHED_RESV_BUFF_HRS",              12       );
//
//The number of hours days that a reservation purely in the past can be modified by _anyone_.  After some
//period of time it becomes a historical record and should not be modified.
define("CONFIG_SCHED_RESV_PAST_LOCK_DAYS",         2       );
//
//The layout of the scheduling day view in terms of the hours of the day displayed.  The hours of the day
//are divided into panels, not necessarily non-overlapping.  This array defines the panels.
//The upper limits on the panels are "closed", i.e. 0,9 means midnight through 9:59 a.m.
//The paneling scheme may not have a panel that crosses midnight (reservations may cross midnight,
//of course, but one of the assumptions made in the reservation display code is that panels do not
//cross midnight).
$CONFIG_SCHED_DAY_PANELS = array(  0,   9,
                                   7,  18,
                                  14,  23 );
//
//==============================================================================================================
//==============================================================================================================
//====  Logging Options  =======================================================================================
//==============================================================================================================
//==============================================================================================================
//The number of log entries that should be retained in the log.  500,000 seems like a reasonable number.  For
//an FBO that gets 2,000 log entries per day, this gives a history of the better part of a year--seems good
//enough.  Disk space consumption has not been estimated.
//
define("CONFIG_LOG_MAX_ENTRIES", 500000);
//
//==============================================================================================================
//==============================================================================================================
//====  Login Recovery Options  ================================================================================
//==============================================================================================================
//==============================================================================================================
//The number of minutes for which temporary passwords are valid.
//
define("CONFIG_LOGIN_REC_TEMP_PW_LIFETIME", 30);
//
//==============================================================================================================
//==============================================================================================================
//====  User Creation and Privilege Options  ===================================================================
//==============================================================================================================
//==============================================================================================================
//The array below represents the pecking order at the typical FBO.  For each category of user, the array
//contains, in order:
//   a)The security level of the category.  (A smaller integer corresponds to more privilege.)
//   b)The text description of the category of user.  This is suitable for drop-down lists in web forms.
//   c)A shorter text tag of the category of user.  This must contain no spaces.
//   d)The privilege string to use when creating this category of user.
//
//Note that the integer index of the category of user is implied by its location in the table.
//
$CONFIG_FBO_USER_CATEGORIES = array(
   //--------------------------------------------------------------------------------
   //The database administrator has even more privileges than the owner/operator of the FBO.
   //There may be technical changes to the database and so on that the DB admin may make but which
   //would be dangerous for non-technical users to make.
   0,  
   "Database Administrator",                 
   "CONFIG_FBO_USR_CAT_DBADMIN",
   "",
   //--------------------------------------------------------------------------------
   //The owner/partner of the FBO has every non-technical privilege.  Additionally, because
   //they have a security level with more privilege than any other category of user, nobody at
   //the business may alter their privileges.
   1,  
   "Owner/Partner",                 
   "CONFIG_FBO_USR_CAT_OWNERPARTNER",
   "\\canviewlogentries=\"\""           .       //Can view logs.
   "\\canresetpasswords=\"\""           .       //Can reset passwords.
   "\\canviewreservationdetails=\"\""   .       //Can view reservation details.
   "\\sesslifetimedefault=\"900\"",             //15 minutes default logout time.
   //--------------------------------------------------------------------------------
   //The manager of the FBO is/are the individual(s) who run the FBO on a day-to-day
   //basis.
   2,  
   "Manager",                 
   "CONFIG_FBO_USR_CAT_MANAGER",
   "\\canviewlogentries=\"\""           .       //Can view logs.
   "\\canresetpasswords=\"\""           .       //Can reset passwords.
   "\\canviewreservationdetails=\"\""   .       //Can view reservation details.
   "\\sesslifetimedefault=\"900\"",             //15 minutes default logout time.
   //--------------------------------------------------------------------------------
   //The office manager is typically below the manager.  Just to prevent accidents,
   //this is probably the lowest-ranking employee that should be able to modify
   //resources.  Other employees are certainly trustworthy, but human curiousity
   //is what it is, and computers are what they are.
   3,  
   "Office Manager",                 
   "CONFIG_FBO_USR_CAT_OFFICEMANAGER",
   "\\canviewlogentries=\"\""           .       //Can view logs.
   "\\canresetpasswords=\"\""           .       //Can reset passwords.
   "\\canviewreservationdetails=\"\""   .       //Can view reservation details.
   "\\sesslifetimedefault=\"900\"",             //15 minutes default logout time.
   //--------------------------------------------------------------------------------
   //The flight instructors, office employees, and mechanics have quite liberal 
   //privileges, but less than the office manager (to prevent accidents).
   4,  
   "Flight Instructor",                 
   "CONFIG_FBO_USR_CAT_FLIGHTINSTRUCTOR",
   "\\canviewlogentries=\"\""           .       //Can view logs.
   "\\canresetpasswords=\"\""           .       //Can reset passwords.
   "\\canviewreservationdetails=\"\""   .       //Can view reservation details.
   "\\sesslifetimedefault=\"900\"",             //15 minutes default logout time.
   //--------------------------------------------------------------------------------
   //Office employee
   4,  
   "Office Employee",                 
   "CONFIG_FBO_USR_CAT_OFFICEEMPLOYEE",
   "\\canviewlogentries=\"\""           .       //Can view logs.
   "\\canresetpasswords=\"\""           .       //Can reset passwords.
   "\\canviewreservationdetails=\"\""   .       //Can view reservation details.
   "\\sesslifetimedefault=\"900\"",             //15 minutes default logout time.
   //--------------------------------------------------------------------------------
   //Mechanic
   4,  
   "Mechanic",                 
   "CONFIG_FBO_USR_CAT_MECHANIC",
   "\\canviewlogentries=\"\""           .       //Can view logs.
   "\\canresetpasswords=\"\""           .       //Can reset passwords.
   "\\canviewreservationdetails=\"\""   .       //Can view reservation details.
   "\\sesslifetimedefault=\"900\"",             //15 minutes default logout time.
   //--------------------------------------------------------------------------------
   //Line Employee:  Fewer privileges than flight instructors and others.
   5,  
   "Line Employee",                 
   "CONFIG_FBO_USR_CAT_LINEEMPLOYEE",
   "\\canviewlogentries=\"\""           .       //Can view logs.
   "\\canresetpasswords=\"\""           .       //Can reset passwords.
   "\\canviewreservationdetails=\"\""   .       //Can view reservation details.
   "\\sesslifetimedefault=\"900\"",             //15 minutes default logout time.
   //--------------------------------------------------------------------------------
   //Customer:  fewest privileges of all.
   20,
   "Customer",                 
   "CONFIG_FBO_USR_CAT_CUSTOMER",
   "\\sesslifetimedefault=\"1800\"",            //30 minutes default logout time.
                                   );
//The session lifetime (seconds) to use if the user who logs in does not have the necessary
//information in the permission string.
define("CONFIG_SESS_LIFETIME_DEFAULT",          1200);                           //20 minutes
//
//--------------------------------------------------------------------------------------------------------------
//End of $RCSfile: config.inc,v $.
//--------------------------------------------------------------------------------------------------------------
?>
