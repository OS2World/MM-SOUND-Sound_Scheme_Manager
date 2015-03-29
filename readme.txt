Sound Scheme Manager 1.1 beta 3
Copyright 1996, 1997 by D.J. van Enckevort

Note: This is a limited beta, please do NOT give this program to others.
      People who are interested in this beta can apply by sending an email
      to enckevor@dds.nl

DISCLAIMER
==========

This program is a prerelease of Sound Scheme Manager, and is intended for test
purposes only. There is no warranty of fitness whatsoever. Use of this program
is on your own risk. The author cannot be held responsible for loss of data,
loss of profit, or any other loss, arising from the use or inability to use
this program.

Having said that, I don't believe this program is a bomb, but I can't run
risks.
I have tested this program on my own machine without problems, and this beta
is meant to test the program in other situations.

FILES INCLUDED IN THIS BETA
===========================

In this beta 3 files are included:
* README.TXT - This file
* SSM.EXE    - The executable
* HELP.HLP   - The help-file from version 1.0

WHAT IT DOES (AND DOESN'T)
==========================

This beta does all the basic management of Sound Schemes, you can create new
schemes, copy schemes, rename schemes and delete schemes. For all the schemes
you can change the sound of any and all actions.

On my list of functions to implement in the next betas are:
* Import / Export
* Find / Replace
* Apply sounds to system (Yes, I finaly found out how to do this!)
* Undo
* Help
* Fixes of bugs found by you, the beta-testers. :-)

DIFFERENCES FROM VERSION 1.0
============================

There are many differences from version 1.0, but most differences are hidden
from the surface. The most important difference is that this version is a
complete rewrite in C, while version 1.0 was written in REXX. There were many
reasons for rewriting it in C, among them are:
* flexibility
* speed
* easier error checking

DIFFERENCES FROM BETA 1
=======================

Since beta 1 I have changed some of the internal structures, and I have added a
few things:
* Test: Test play a complete sound scheme
* Menus: The menu is working now (however not all functions are available yet)
* Product Info Dialog:
* (Internal only) Added structures and some functions for Undo
* (Internal only) Added structures and some functions for Import/Export
* Solved bug that caused deleted structures to reappear
* Solved bug that created duplicate sections in INI file
* Solved bug that created PM_SOUNDS_ section in INI file
* Made some cosmetic changes
* Changed name on Find (file) button from Find to Locate
* New Icon and Logo (thanks to Andrea Resmini)

DIFFERENCE FROM BETA 2
======================

Since beta 2 I have changed a lot, I finally made my mind up about the internal
structures, and had to rewrite a lot of code to work with the new structures.
The new structures however lead to a reduced memory footprint and more
flexibility.
Further changes:
* Changed icons in test window
* The names of the events and the number of events isn't hardcoded into the
  program anymore.
* Made File dialog to work correctly
* Made program to switch to first copy when multiple copies are started.
* Assigned the SSM icon to the system menu
* Corrected bug in copy that could cause the wrong information to be copied to
  the new scheme
* Corrected bug that corrupted the table of events (side-benefit of the
  structural changes)
* Corrected bug that no ini file was created

REPORTING BUGS
==============

I am sure you will find bugs. You can report them by sending an email to my
email address (enckevor@dds.nl) with as subject SSM - bug report. Be sure to include in your report the following:
* Version of OS/2 (4.0 of course, but US, UK, German?) & fixpak level
* Installed hardware
* Installation drive of OS/2, MMOS/2 and SSM
* What happened, as detailed as possible
* Description how to reproduce the bug

If you can't reproduce a possible bug, but you have the suspicion it still is
one, please send an email with as subject SSM - possible bug report.

END OF BETA-TEST
================

This beta will end 28 February, or when the next beta is released,
whichever occurs first. Upon termination you have to destroy all copies of this
program.
