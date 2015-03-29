#define INCL_MCIOS2
#define INCL_MACHDR
#define INCL_WIN
#define INCL_PM
#include <os2.h>
#include <os2me.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ssm.h"
#include "support.h"
#include "main.h"
#include "menu.h"
#include "question.h"
#include "find.h"
#include "icon.h"
#include "acceltable.h"
#include "stringtable.h"
#include "test.h"
#include "prodinfo.h"
#include "settings.h"
#include "pmtools.h"

int main(int argc, char *argv[])
{
HMQ hmq;
HWND hwndClient = NULLHANDLE,
     hwndFrame = NULLHANDLE,
     hwndMenu;
HACCEL hAccel;
QMSG qmsg;
INFO Init;
char MMOS2Pad[CCHMAXPATH],
     GeluidenPad[CCHMAXPATH],
     pcTemp[6],
     pcTitle[CCHMAXPATH],
     pcMessage[CCHMAXPATH],
     SSMPad[CCHMAXPATH],
     SchemaPad[CCHMAXPATH],
     *Programma;
HMTX hmtx;
HPOINTER Pictogram;

// Controleer of het programma al draait
hmtx=OneInstance(SEMAFOOR, TRUE);
if (hmtx==NULLHANDLE) // programma draait al
   {
   return RC_OK;
   }

// Standaard initialisatie
Init.hab = WinInitialize(0);
hmq = WinCreateMsgQueue(Init.hab, 0);

// Vraag de paden naar MMOS/2 en de geluiden op

if (VraagPadOp(&Init, MMOS2Pad, GeluidenPad)!=RC_OK)
   {
   WinDestroyMsgQueue(hmq);
   WinTerminate(Init.hab);
   return RC_ERROR;
   }

// Open MMPM.INI, en als dat niet lukt be‰indig het programma

if (OpenMMPMProfile(&Init, MMOS2Pad)!=RC_OK)
   {
   WinDestroyMsgQueue(hmq);
   WinTerminate(Init.hab);
   return RC_ERROR;
   }

// Open Scheme.INI
strcpy(SSMPad, argv[0]);
strlwr(SSMPad);
Programma=strstr(SSMPad, SSM_EXECUTABLE);
Programma[0]=0;
strcpy(SchemaPad, SSMPad);
strcat(SchemaPad, SCHEMEPROFILE);
Init.PrfScheme=PrfOpenProfile(Init.hab, SchemaPad);
if (Init.PrfScheme==NULLHANDLE)
   {
   WinLoadString(Init.hab, NULLHANDLE, NOSCHEMEINI_MESSAGE, CCHMAXPATH, pcMessage);
   WinLoadString(Init.hab, NULLHANDLE, ERROR_TITLE, CCHMAXPATH, pcTitle);
   WinMessageBox(HWND_DESKTOP, HWND_DESKTOP, pcMessage, pcTitle, 0, MB_ERROR | MB_OK);
   PrfCloseProfile(Init.PrfMMPM);
   WinDestroyMsgQueue(hmq);
   WinTerminate(Init.hab);
   return RC_ERROR;
   }

// Open SSM.INI en als dat niet lukt maak dan een nieuwe SSM.INI
if (OpenSSMProfile(&Init, GeluidenPad, SSMPad)!=RC_OK)
   {
   WinLoadString(Init.hab, NULLHANDLE, NOSSMINI_MESSAGE, CCHMAXPATH, pcMessage);
   WinLoadString(Init.hab, NULLHANDLE, ERROR_TITLE, CCHMAXPATH, pcTitle);
   WinMessageBox(HWND_DESKTOP, HWND_DESKTOP, pcMessage, pcTitle, 0, MB_ERROR | MB_OK);
   PrfCloseProfile(Init.PrfScheme);
   PrfCloseProfile(Init.PrfMMPM);
   WinDestroyMsgQueue(hmq);
   WinTerminate(Init.hab);
   return RC_ERROR;
   }

// Laad hoofdscherm, menu, pictogram en Snelkeuze toetsen
hwndFrame = WinLoadDlg(HWND_DESKTOP, HWND_DESKTOP, WinProc, (HMODULE)0, ID_WINDOW, &Init);
if (hwndFrame==NULLHANDLE)
   {
   WinDestroyMsgQueue(hmq);
   WinTerminate(Init.hab);
   return RC_OK;
   }
// Voeg het menu toe
hwndMenu = WinLoadMenu(hwndFrame, (HMODULE)0, ID_MENU);
//  Controleer of het menu geladen is
if (hwndMenu==NULLHANDLE) // Het menu is niet geladen
   {
   WinDestroyWindow(hwndFrame);
   WinDestroyMsgQueue(hmq);
   WinTerminate(Init.hab);
   return RC_OK;
   }
// Voeg het pictogram toe
Pictogram=LoadIcon(hwndFrame, NULLHANDLE, ID_ICON);

// Ververs het scherm
WinSendMsg(hwndFrame, WM_UPDATEFRAME, (MPARAM)NULL, (MPARAM)NULL);


// Laad snelkeuze toetsen
hAccel = WinLoadAccelTable(Init.hab, (HMODULE)0, ID_ACCELTABLE);
if (hAccel==NULLHANDLE) // Snelkeuze toetsen kunnen niet geladen worden
   {
   // Laad de teksten & geef een waarschuwing
   WinLoadString(Init.hab, NULLHANDLE, ACCEL_MESSAGE, CCHMAXPATH, pcMessage);
   WinLoadString(Init.hab, NULLHANDLE, WARNING_TITLE, CCHMAXPATH, pcTitle);
   WinMessageBox(HWND_DESKTOP, HWND_DESKTOP, pcMessage, pcTitle, 0, MB_WARNING | MB_OK);
   }
else
   {
   // Activeer de snelkeuze toetsen
   WinSetAccelTable(Init.hab, hAccel, hwndFrame);
   }


// Begin Message Queue
while (WinGetMsg(Init.hab, &qmsg, 0L, 0, 0))
  WinDispatchMsg(Init.hab, &qmsg);

// Sluit INI bestanden af

PrfCloseProfile(Init.PrfSSM);
PrfCloseProfile(Init.PrfMMPM);
PrfCloseProfile(Init.PrfScheme);

// Be‰indig het programma
WinDestroyWindow(hwndFrame);
WinDestroyMsgQueue(hmq);
WinTerminate(Init.hab);
return RC_OK;
}
