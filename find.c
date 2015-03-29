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

void Zoek(HWND hwnd, PTABEL Tabel)
{
char ZoekString[CCHMAXPATH];
// Doorzoek alle keys op string
// Vraag de string op uit FIND_EF_FIND
// De string mag maximaal net zo lang zijn als het langs mogelijke pad
WinQueryWindowText(WinWindowFromID(hwnd, FIND_EF_FIND), CCHMAXPATH, ZoekString);
// Ga zoeken en vul FIND_LB_RESULT met de resultaten

}

MRESULT EXPENTRY FindProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
USHORT ControlID, NotifyCode;
static PINFO pInfo;
static PTABEL Tabel;
int Aantal;

switch (msg)
   {
   case WM_INITDLG:
      pInfo=(PINFO)PVOIDFROMMP(mp2);
      // reserveer geheugen voor het eerste record (wordt vrijgegeven in WisNaamTabel)
      DosAllocMem((void**)&Tabel, sizeof(TABEL), PAG_COMMIT | PAG_READ | PAG_WRITE);
      Aantal=LeesNaam(Tabel, pInfo->PrfMMPM);
      break;
   case WM_COMMAND:
      ControlID = SHORT1FROMMP(mp1);
      switch (ControlID)
         {
         case FIND_PB_FIND:
            Zoek(hwnd, Tabel);
            break;
         case FIND_PB_REPLACE:
            // Vervang de string alle keren dat deze voorkomt door de opgegeven vervangingsstring
            // Vraag de string op uit FIND_EF_FIND
            // Vraag de string op uit FIND_EF_REPLACE
            // Ga zoeken en vervangen
            // Vul FIND_LB_RESULT met de resultaten
            break;
         case FIND_PB_CLOSE:
            WisNaamTabel(Tabel);
            WinPostMsg(hwnd, WM_CLOSE, 0L, 0L);
            break;
         default:
            break;
         }
      break;
   case WM_CLOSE:
      WinDismissDlg(hwnd, TRUE);
      break;
   default:
      return WinDefDlgProc(hwnd, msg, mp1, mp2);
   }
return (MRESULT)FALSE;
}

