.*---------------------------------------------------------------
.* Help for Sound Scheme Manager.  This file was created for David van Enckevort
.* by Project Smarts on 3 Mar 1997.
.*---------------------------------------------------------------

:userdoc.

:title.Sound Scheme Manager User Guide

.nameit symbol=product text='Sound Scheme Manager'
.nameit symbol=email text='van.enckevort@hccnet.nl'
.nameit symbol=homepage text='http&colon.//home.hccnet.nl/van.enckevort'
.nameit symbol=linkhome text='http://home.hccnet.nl/van.enckevort'
.nameit symbol=version text='version 1.1 beta 4'
.nameit symbol=scheme text='Sound Scheme'

.*--------------------------------
:h1 id=mainwin res=100.&product. product information
:i1.general help
:i1.about &product.
:p.
:hp2.&product.  1.1:ehp2.
:p.
Copyright (c) 1997-1999 David J. van Enckevort
:p.
&product. is a program to manage the &scheme.s found in OS/2 Warp 4.0 and
it can also be used to provide Sound Schemes to OS/2 Warp 3.0. I don't know
about earlier versions since I haven't tested them with &product..
This program can perform the following functions.
:ul.
:li.Create new &scheme.
:li.Import &scheme.s from the OS/2 System INI file
:li.Edit existing &scheme.s
:li.Test play sound files for use in &scheme.s
:li.Test play &scheme.s
:li.Copy &scheme.s
:li.Rename &scheme.s
:li.Delete &scheme.s
:eul.
:p.
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.
:p.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
:link reftype=hd res=130.GNU General Public License:elink. for more details.
:p.
You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
:sl.
:li.:link reftype=hd res=110.Known bugs &amp. limitations:elink.
:li.:link reftype=hd res=120.Contact information:elink.
:li.:link reftype=hd res=130.GNU General Public License:elink.
:esl.

.*--------------------------------
:h2 id=bugs res=110.Known bugs &amp. limitations
:i1.bugs
:i1.limitations
:i1.reporting bugs
:p.
This is &version. of &product.. Version 1.0 was written in VisPro REXX, but
starting with version 1.1 beta 1 this program was completely rewritten in C++.
This program is far from complete, and I am aware of the following bugs and
limitations&colon.
:ol.
:li.No checking is done on the files, it is possible to select files that
aren't WAVAudio files.
:li.Though it is possible to set the volume for a event, this setting is
ignored when using the play or test function of &product.. However it is
correctly set when applying the scheme.
:li. The following functions appear on the screen but are not implemented in
this version&colon. Export, Settings, Find, Help Index, General Help, Using
Help, Help and Apply volume to all events, as well as all the functions found
in the Settings and Find windows.
:li. Import is limited to importing all the schemes found in the OS/2 system
INI file. Selecting this function in OS/2 Warp 3.0 does not give an information
message that no schemes are found.
:li. When a new scheme is applied the old scheme is still used till the next
reboot.
:li. The order of the Schemes in the Schemes list and the order of the Events
in the Events list is dependant on the order in the MMPM INI file, and can be
different the next time you start &product..
:eol.
:p.
If you want to report bugs or if you have features requests, you can contact me
by E-Mail. Please send your E-mail to the following address: &email. Since a
short time I also have a section on my homepage which provides a feedback form
and information on where to find the latest version of &product.. My homepage
is located at :link reftype=launch object='netscape.exe' data='&linkhome.'.&homepage..:elink.
:p.
The next version is not to be expected before the end of September 1999, since
I am currently writing my final paper for university.

.*--------------------------------
:h2 id=contact res=120.Contact infromation
:i1.contacting the author
:p.
If you have any questions or remarks on this program, or if you want to report
bugs or send features requests, you can contact the author by E-Mail. Please
send your E-mail to the following address&colon. &email.
:p.
Include in your email at least the following information:
:ol.
:li.Which version of OS/2 Warp 4.0 do you use (US, UK, Dutch, German, etc.) and
which fixpaks did you apply.
:li.Installed hardware.
:li.Installation path of OS/2, MMOS/2 (multimedia), and &product..
:li.Detailed description of the problem.
:li.Instructions how to reproduce the problem.
:eol.
:p.
Or you can use the evaluation and feedback form found on my homepage at
:link reftype=launch object='netscape.exe' data='&linkhome.'.&homepage..:elink.

.*--------------------------------
:h2 id=GPL res=130.GNU General Public License
:i1.GPL
:i1.license
:i1.GNU General Public License
:p.
:hp1.GNU GENERAL PUBLIC LICENSE:ehp1.
:p.
Version 2, June 1991
:p.
Copyright (C) 1989, 1991 Free Software Foundation, Inc.
675 Mass Ave, Cambridge, MA 02139, USA
:p.
Everyone is permitted to copy and distribute verbatim copies
of this license document, but changing it is not allowed.
:p.
:hp2.Preamble:ehp2.
:p.
The licenses for most software are designed to take away your
freedom to share and change it.  By contrast, the GNU General Public
License is intended to guarantee your freedom to share and change free
software--to make sure the software is free for all its users.  This
General Public License applies to most of the Free Software
Foundation's software and to any other program whose authors commit to
using it.  (Some other Free Software Foundation software is covered by
the GNU Library General Public License instead.)  You can apply it to
your programs, too.
:p.
When we speak of free software, we are referring to freedom, not
price.  Our General Public Licenses are designed to make sure that you
have the freedom to distribute copies of free software (and charge for
this service if you wish), that you receive source code or can get it
if you want it, that you can change the software or use pieces of it
in new free programs; and that you know you can do these things.
:p.
To protect your rights, we need to make restrictions that forbid
anyone to deny you these rights or to ask you to surrender the rights.
These restrictions translate to certain responsibilities for you if you
distribute copies of the software, or if you modify it.
:p.
For example, if you distribute copies of such a program, whether
gratis or for a fee, you must give the recipients all the rights that
you have.  You must make sure that they, too, receive or can get the
source code.  And you must show them these terms so they know their
rights.
:p.
We protect your rights with two steps:
:ol.
:li.copyright the software, and
:li.offer you this license which gives you legal permission to copy,
distribute and/or modify the software.
:eol.
:p.
Also, for each author's protection and ours, we want to make certain
that everyone understands that there is no warranty for this free
software.  If the software is modified by someone else and passed on, we
want its recipients to know that what they have is not the original, so
that any problems introduced by others will not reflect on the original
authors' reputations.
:p.
Finally, any free program is threatened constantly by software
patents.  We wish to avoid the danger that redistributors of a free
program will individually obtain patent licenses, in effect making the
program proprietary.  To prevent this, we have made it clear that any
patent must be licensed for everyone's free use or not licensed at all.
:p.
The precise terms and conditions for copying, distribution and
modification follow.
:p.
:hp1.GNU GENERAL PUBLIC LICENSE:ehp1.
:p.
:hp1.TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION:ehp1.
:ol.
:li.This License applies to any program or other work which contains
a notice placed by the copyright holder saying it may be distributed
under the terms of this General Public License.  The "Program", below,
refers to any such program or work, and a "work based on the Program"
means either the Program or any derivative work under copyright law:
that is to say, a work containing the Program or a portion of it,
either verbatim or with modifications and/or translated into another
language.  (Hereinafter, translation is included without limitation in
the term "modification".)  Each licensee is addressed as "you".
:lp.:lm margin=6.
Activities other than copying, distribution and modification are not
covered by this License; they are outside its scope.  The act of
running the Program is not restricted, and the output from the Program
is covered only if its contents constitute a work based on the
Program (independent of having been made by running the Program).
Whether that is true depends on what the Program does.

:li.You may copy and distribute verbatim copies of the Program's
source code as you receive it, in any medium, provided that you
conspicuously and appropriately publish on each copy an appropriate
copyright notice and disclaimer of warranty; keep intact all the
notices that refer to this License and to the absence of any warranty;
and give any other recipients of the Program a copy of this License
along with the Program.
:lp.
You may charge a fee for the physical act of transferring a copy, and
you may at your option offer warranty protection in exchange for a fee.

:li.You may modify your copy or copies of the Program or any portion
of it, thus forming a work based on the Program, and copy and
distribute such modifications or work under the terms of Section 1
above, provided that you also meet all of these conditions:
:ol.
:li.You must cause the modified files to carry prominent notices
stating that you changed the files and the date of any change.

:li.You must cause any work that you distribute or publish, that in
whole or in part contains or is derived from the Program or any
part thereof, to be licensed as a whole at no charge to all third
parties under the terms of this License.

:li.If the modified program normally reads commands interactively
when run, you must cause it, when started running for such
interactive use in the most ordinary way, to print or display an
announcement including an appropriate copyright notice and a
notice that there is no warranty (or else, saying that you provide
a warranty) and that users may redistribute the program under
these conditions, and telling the user how to view a copy of this
License.  (Exception: if the Program itself is interactive but
does not normally print such an announcement, your work based on
the Program is not required to print an announcement.)
:eol.
:lp.
These requirements apply to the modified work as a whole.  If
identifiable sections of that work are not derived from the Program,
and can be reasonably considered independent and separate works in
themselves, then this License, and its terms, do not apply to those
sections when you distribute them as separate works.  But when you
distribute the same sections as part of a whole which is a work based
on the Program, the distribution of the whole must be on the terms of
this License, whose permissions for other licensees extend to the
entire whole, and thus to each and every part regardless of who wrote it.
:lp.
Thus, it is not the intent of this section to claim rights or contest
your rights to work written entirely by you; rather, the intent is to
exercise the right to control the distribution of derivative or
collective works based on the Program.
:lp.
In addition, mere aggregation of another work not based on the Program
with the Program (or with a work based on the Program) on a volume of
a storage or distribution medium does not bring the other work under
the scope of this License.

:li.You may copy and distribute the Program (or a work based on it,
under Section 2) in object code or executable form under the terms of
Sections 1 and 2 above provided that you also do one of the following:
:ol.
:li.Accompany it with the complete corresponding machine-readable
source code, which must be distributed under the terms of Sections
1 and 2 above on a medium customarily used for software interchange; or,

:li.Accompany it with a written offer, valid for at least three
years, to give any third party, for a charge no more than your
cost of physically performing source distribution, a complete
machine-readable copy of the corresponding source code, to be
distributed under the terms of Sections 1 and 2 above on a medium
customarily used for software interchange; or,

:li.Accompany it with the information you received as to the offer
to distribute corresponding source code.  (This alternative is
allowed only for noncommercial distribution and only if you
received the program in object code or executable form with such
an offer, in accord with Subsection b above.)
:eol.
:lp.
The source code for a work means the preferred form of the work for
making modifications to it.  For an executable work, complete source
code means all the source code for all modules it contains, plus any
associated interface definition files, plus the scripts used to
control compilation and installation of the executable.  However, as a
special exception, the source code distributed need not include
anything that is normally distributed (in either source or binary
form) with the major components (compiler, kernel, and so on) of the
operating system on which the executable runs, unless that component
itself accompanies the executable.
:lp.
If distribution of executable or object code is made by offering
access to copy from a designated place, then offering equivalent
access to copy the source code from the same place counts as
distribution of the source code, even though third parties are not
compelled to copy the source along with the object code.

:li.You may not copy, modify, sublicense, or distribute the Program
except as expressly provided under this License.  Any attempt
otherwise to copy, modify, sublicense or distribute the Program is
void, and will automatically terminate your rights under this License.
However, parties who have received copies, or rights, from you under
this License will not have their licenses terminated so long as such
parties remain in full compliance.

:li.You are not required to accept this License, since you have not
signed it.  However, nothing else grants you permission to modify or
distribute the Program or its derivative works.  These actions are
prohibited by law if you do not accept this License.  Therefore, by
modifying or distributing the Program (or any work based on the
Program), you indicate your acceptance of this License to do so, and
all its terms and conditions for copying, distributing or modifying
the Program or works based on it.

:li.Each time you redistribute the Program (or any work based on the
Program), the recipient automatically receives a license from the
original licensor to copy, distribute or modify the Program subject to
these terms and conditions.  You may not impose any further
restrictions on the recipients' exercise of the rights granted herein.
You are not responsible for enforcing compliance by third parties to
this License.

:li.If, as a consequence of a court judgment or allegation of patent
infringement or for any other reason (not limited to patent issues),
conditions are imposed on you (whether by court order, agreement or
otherwise) that contradict the conditions of this License, they do not
excuse you from the conditions of this License.  If you cannot
distribute so as to satisfy simultaneously your obligations under this
License and any other pertinent obligations, then as a consequence you
may not distribute the Program at all.  For example, if a patent
license would not permit royalty-free redistribution of the Program by
all those who receive copies directly or indirectly through you, then
the only way you could satisfy both it and this License would be to
refrain entirely from distribution of the Program.
:lp.
If any portion of this section is held invalid or unenforceable under
any particular circumstance, the balance of the section is intended to
apply and the section as a whole is intended to apply in other
circumstances.
:lp.
It is not the purpose of this section to induce you to infringe any
patents or other property right claims or to contest validity of any
such claims; this section has the sole purpose of protecting the
integrity of the free software distribution system, which is
implemented by public license practices.  Many people have made
generous contributions to the wide range of software distributed
through that system in reliance on consistent application of that
system; it is up to the author/donor to decide if he or she is willing
to distribute software through any other system and a licensee cannot
impose that choice.
:lp.
This section is intended to make thoroughly clear what is believed to
be a consequence of the rest of this License.

:li.If the distribution and/or use of the Program is restricted in
certain countries either by patents or by copyrighted interfaces, the
original copyright holder who places the Program under this License
may add an explicit geographical distribution limitation excluding
those countries, so that distribution is permitted only in or among
countries not thus excluded.  In such case, this License incorporates
the limitation as if written in the body of this License.

:li.The Free Software Foundation may publish revised and/or new versions
of the General Public License from time to time.  Such new versions will
be similar in spirit to the present version, but may differ in detail to
address new problems or concerns.
:lp.
Each version is given a distinguishing version number.  If the Program
specifies a version number of this License which applies to it and "any
later version", you have the option of following the terms and conditions
either of that version or of any later version published by the Free
Software Foundation.  If the Program does not specify a version number of
this License, you may choose any version ever published by the Free Software
Foundation.

:li.If you wish to incorporate parts of the Program into other free
programs whose distribution conditions are different, write to the author
to ask for permission.  For software which is copyrighted by the Free
Software Foundation, write to the Free Software Foundation; we sometimes
make exceptions for this.  Our decision will be guided by the two goals
of preserving the free status of all derivatives of our free software and
of promoting the sharing and reuse of software generally.
:lp.
:hp2.NO WARRANTY:ehp2.

:li.BECAUSE THE PROGRAM IS LICENSED FREE OF CHARGE, THERE IS NO WARRANTY
FOR THE PROGRAM, TO THE EXTENT PERMITTED BY APPLICABLE LAW.  EXCEPT WHEN
OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR OTHER PARTIES
PROVIDE THE PROGRAM "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED
OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE ENTIRE RISK AS
TO THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU.  SHOULD THE
PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING,
REPAIR OR CORRECTION.

:li.IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING
WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MAY MODIFY AND/OR
REDISTRIBUTE THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES,
INCLUDING ANY GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING
OUT OF THE USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED
TO LOSS OF DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY
YOU OR THIRD PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER
PROGRAMS), EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE
POSSIBILITY OF SUCH DAMAGES.
:eol.
:p.
:hp2.END OF TERMS AND CONDITIONS:ehp2.


.*--------------------------------
:h1 id=manage res=200.Managing &scheme.s with &product.
:i1.managing &scheme.s
:i1.working with &scheme.s
:p.
This section explains how to manage your &scheme.s with &product..
It is divided into the following subsections&colon.
:ol.
:li.:link reftype=hd res=210.Create a new &scheme.:elink.
:li.:link reftype=hd res=220.Assign a sound to an event:elink.
:li.:link reftype=hd res=230.Save a &scheme.:elink.
:li.:link reftype=hd res=240.Delete a &scheme.:elink.
:li.:link reftype=hd res=250.Test play an event:elink.
:li.:link reftype=hd res=260.Select another &scheme.:elink.
:eol.

.*--------------------------------
:h2 id=new res=210.Create a new &scheme.s
:i1.create a &scheme.
:i1.new &scheme.s
:p.
You can create a new Sound Scheme by executing the following steps&colon.
:ol.
:li.Press the :hp1.Add:ehp1. button
:li.Type the name of the &scheme. and press :hp1.Ok:ehp1.
:li.Assign a sound to each of the events (See :link reftype=hd res=220.assign a
sound to an event:elink.)
:eol.

.*--------------------------------
:h2 id=assign res=220.Assign a sound to an event
:i1.edit an action
:i1.assign a sound file to an event
:p.
You can easily assign a new sound file to an event, by the following steps&colon.
:ol.
:li.Select the event
:li.Type the name of the sound file in the entryfield
:li.Select the next event, and so on
:eol.

.*--------------------------------
:h2 id=save res=230.Save a &scheme.
:i1.save a sound scheme
:p.
There is no need anymore to explicitely save your &scheme.s. As soon as you
select another event or scheme, the changes are saved

.*--------------------------------
:h2 id=delete res=240.Deleting a &scheme.
:i1.delete a sound scheme
:p.
If you really hate a &scheme. you can delete it by pressing the
:hp1.Delete:ehp1.  button.  But note, once you have confirmed the deletion there
is no way back besides recreating the &scheme. manually, so don't use this
function easily.

.*--------------------------------
:h2 id=play res=250.Test play an event
:i1.test play an event
:p.
If you want to know how a sound sounds, you can press the :hp1.Play:ehp1.
button.  The program will play the file completely and at the default volume,
There is no possibilty to stop playing, except for selecting another event, and
playing the sound attached to that event, or closing the program.

.*--------------------------------
:h2 id=select res=260.Select another &scheme.
:i1.select a &scheme.
:p.
You can select a Sound Scheme by clicking on the name of the Scheme in the Sound
Scheme listbox. When you do so, changes to the previous scheme are saved.

.*--------------------------------
:h2 id=action res=270.Selecting events
:i1.selecting events
:p.
You can select events to assign a sound to by clicking on the name of the
event in the event list. If you click on an event the sound that is assign
wil appear in the sound entryfield so you can change it or test play it.

.*--------------------------------
:h1 id=actions res=300.System events
:i1.system eventss
:p.
This section explains the system events to which you can assign a sound with
&product. OS/2 Warp 4.0 supports the following system events, other events that
may appear are application events&colon.
:ul.
:li.:link reftype=hd res=310.Begin drag:elink.
:li.:link reftype=hd res=320.End drag:elink.
:li.:link reftype=hd res=330.Opening window (animated):elink.
:li.:link reftype=hd res=340.Closing window (animated):elink.
:li.:link reftype=hd res=350.System Startup:elink.
:li.:link reftype=hd res=360.System Shutdown:elink.
:li.:link reftype=hd res=370.Information:elink.
:li.:link reftype=hd res=380.Warning:elink.
:li.:link reftype=hd res=390.Error:elink.
:li.:link reftype=hd res=400.Printer Error:elink.
:li.:link reftype=hd res=410.Lockup:elink.
:li.:link reftype=hd res=420.Alarm Clock:elink.
:li.:link reftype=hd res=430.Shred:elink.
:li.:link reftype=hd res=440.<Try it>:elink.
:eul.
:p.
More events can be found in the :link reftype=hd res=500.Application events
:elink. section.

.*--------------------------------
:h2 id=drag res=310.Begin drag
:i1.begin drag event
:p.
:hp2.Begin drag:ehp2.
:p.
:parml break=all.
:pt.Key
:pd.5
:eparml.
:p.
This is the sound that you hear when you start dragging an icon on the desktop
or in a folder.

.*--------------------------------
:h2 id=drop res=320.End drag
:i1.end drag event
:p.
:hp2.End drag:ehp2.
:p.
:parml break=all.
:pt.Key
:pd.6
:eparml.
:p.
This is the sound that you hear when you drop an icon on the desktop or in a
folder.

.*--------------------------------
:h2 id=open res=330.Opening window (animated)
:i1.opening window event
:p.
:hp2.Opening window (animated):ehp2.
:p.
:parml break=all.
:pt.Key
:pd.3
:eparml.
:p.
This is the sound that you hear when you open a window (a program or a folder)
and you have enabled animations in the System properties notebook (on the window
page) in the Setup folder.

.*--------------------------------
:h2 id=close res=340.Closing window (animated)
:i1.closing window event
:p.
:hp2.Closing window (animated):ehp2.
:p.
:parml break=all.
:pt.Key
:pd.4
:eparml.
:p.
This is the sound that you hear when you close a window (a program or a folder)
and you have enabled animations in the System properties notebook (on the
window page)in the Setup folder.

.*--------------------------------
:h2 id=startup res=350.System Startup
:i1.system startup event
:p.
:hp2.System startup:ehp2.
:p.
:parml break=all.
:pt.Key
:pd.7
:eparml.
:p.
This is the sound that you hear when you turn on the computer and the desktop
appears.

.*--------------------------------
:h2 id=shutdown res=360.System Shutdown
:i1.system shutdown event
:p.
:hp2.System shutdown:ehp2.
:p.
:parml break=all.
:pt.Key
:pd.8
:eparml.
:p.
This is the sound that you hear when you shutdown the system.

.*--------------------------------
:h2 id=info res=370.Information
:i1.information event
:p.
:hp2.Information:ehp2.
:p.
:parml break=all.
:pt.Key
:pd.1
:eparml.
:p.
This is the sound that you hear when a information dialog pops up (a dialog with
a question mark or an information symbol)

.*--------------------------------
:h2 id=warning res=380.Warning
:i1.warning event
:p.
:hp2.Warning:ehp2.
:p.
:parml break=all.
:pt.Key
:pd.0
:eparml.
:p.
This is the sound that you hear when a warning dialog pops up or when you try to
do something that is impossible (like scrolling down a window when you're
already at the bottom).

.*--------------------------------
:h2 id=error res=390.Error
:i1.error event
:p.
:hp2.Error:ehp2.
:p.
:parml break=all.
:pt.Key
:pd.2
:eparml.
:p.
This is the sound that you hear when a error dialog pops up.

.*--------------------------------
:h2 id=perror res=400.Printer Error
:i1.printer error event
:p.
:hp2.Printer error:ehp2.
:p.
:parml break=all.
:pt.Key
:pd.12
:eparml.
:p.
This is the sound that you hear when the system can't send a job to the printer,
because the printer is offline or if the printer returns an error.

.*--------------------------------
:h2 id=lockup res=410.Lockup
:i1.lockup event
:p.
:hp2.Lockup:ehp2.
:p.
:parml break=all.
:pt.Key
:pd.10
:eparml.
:p.
This is the sound that you hear when you lockup (blank out the screen) the
system (select lockup now in the desktop popup meny).

.*--------------------------------
:h2 id=alarm res=420.Alarm Clock
:i1.alarm clock event
:p.
:hp2.Alarm clock:ehp2.
:p.
:parml break=all.
:pt.Key
:pd.11
:eparml.
:p.
This is the sound for the alarm of the system clock (See properties notebook of
the system clock)

.*--------------------------------
:h2 id=shred res=430.Shred
:i1.shred event.
:p.
:hp2.Shred:ehp2.
:p.
:parml break=all.
:pt.Key
:pd.9
:eparml.
:p.
This is the sound that you hear when you delete a file or drop a file on the
shredder when you have enable animations in the system properties notebook (on
the window page)

.*--------------------------------
:h2 id=try res=440.<Try it>
:i1.<Try it> event.
:p.
:hp2.<Try it>:ehp2.
:p.
:parml break=all.
:pt.Key
:pd.997
:eparml.
:p.
<Try it> is not really a event, but it a system defined entry which allows you
to try a sound without assigning it to a real event first. The system sets this
event to the Sounds subdirectory of the MMOS/2 directory. It is best to leave
this as it is. &product. allows you to set it to something different however.
No compatibility problems were reported with this event set to something else.

.*--------------------------------
:h1 id=app_events res=500.Application events
:i1.application events
:p.
:hp2.Application events:ehp2.
:p.
Some applications define their own events in the MMPM INI file. &product. is
designed to automatically and seamlessly support these application events
without the need to rewrite any part of the program.
:p.
As soon as an application configures application events in MMPM &product. will
find them upon the next start and add the new events to the list. You can add
sounds for these new events in your &scheme.s the same way as you did for the
other sounds. However as long as the event hasn't been selected in &product. no
support for the event will be added to the &scheme.. However this does not in
any way affect the functioning of &product., the event just will be ignored.
:p.
At the moment I am aware of the following application events, other application
events are automatically supported though. In the following sections I describe
these application events, providing the information to pick a free keyname for
your own application events.
:ul.
:li.:link reftype=hd res=510.Empty trash:elink.
:li.:link reftype=hd res=520.Drop trash:elink.
:eul.
:p.
If you know about other application events please send me an e-mail with the
following information so I can include it in a next release of this document.
:ul.
:li.Name of the application
:li.Name of the author
:li.Description of the application
:li.A list of all the application events, with for every event the following
information&colon.
:ul.
:li.Name of the event
:li.Description of the event
:li.Key-name in mmpm.ini
:eul.
:eul.
:p.
You can send your e-mail to the following address&colon. &email.

.*--------------------------------
:h2 id=tc_empty res=510.Empty trash
:i1.empty trash event
:p.
:hp2.Empty trash:ehp2.
:parml break=all.
:pt.Application
:pd.TrashCan
:pt.Author
:pd.Kai Sommerfeld
:pt.Key
:pd.222
:eparml.
:p.
TrashCan is a WPS class to provide a Macintosh-like trashcan to the OS/2
desktop. The empty trash event defines the sound played when you empty the
trashcan.

.*--------------------------------
:h2 id=tc_drop res=520.Drop trash
:i1.drop trash event
:p.
:hp2.Drop trash:ehp2.
:parml break=all.
:pt.Application
:pd.TrashCan
:pt.Author
:pd.Kai Sommerfeld
:pt.Key
:pd.223
:eparml.
:p.
TrashCan is a WPS class to provide a Macintosh-like trashcan to the OS/2
desktop. The drop trash event defines the sound played when you drop a file
in the trashcan.

:euserdoc.
