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
#include "acceltable.h"
#include "stringtable.h"
#include "test.h"

MRESULT EXPENTRY TestProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
USHORT ControlID, NotifyCode;
static PTESTPARAMS pTestParams;
static PTABEL Tabel;
PTABEL pTabel;
static int Aantal;
static ACTIE Actie;
char *Gebeurtenis;
switch (msg)
   {
   case WM_INITDLG:
      pTestParams=(PTESTPARAMS)PVOIDFROMMP(mp2);
      // reserveer geheugen voor het eerste record (wordt vrijgegeven in WisNaamTabel)
      DosAllocMem((void**)&Tabel, sizeof(TABEL), PAG_COMMIT | PAG_READ | PAG_WRITE);
      strcpy(Actie.Schema, pTestParams->Schema);
      Aantal=LeesNaam(Tabel, pTestParams->Info->PrfMMPM);
      WinSetWindowText(WinWindowFromID(hwnd, DLG_TEST_ST_NAME), pTestParams->Schema);
      WinSetWindowText(WinWindowFromID(hwnd, DLG_TEST_ST_EVENT), Tabel->Naam);
      break;
   case WM_COMMAND:
      ControlID = SHORT1FROMMP(mp1);
      switch (ControlID)
         {
         case DLG_TEST_PB_OK:
            WinPostMsg(hwnd, WM_CLOSE, 0L, 0L);
            break;
         case DLG_TEST_PB_PREV:
            {
            if (Actie.Index==0)
               Actie.Index=Aantal-1;
            else
               Actie.Index--;
            LeesGebeurtenis(pTestParams->Info, Tabel, &Actie);
            pTabel=Tabel;
            while (pTabel!=NULL)
               {
               if (pTabel->Index==Actie.Index)
                  break;
               pTabel=pTabel->Volgende;
               }
            WinSetWindowText(WinWindowFromID(hwnd, DLG_TEST_ST_EVENT), pTabel->Naam);
            mciPlayFile((HWND) NULL, Actie.Bestand, MCI_ASYNC, (PSZ) NULL, (HWND) NULL);
            }
            break;
         case DLG_TEST_PB_NEXT:
            {
            if (Actie.Index==Aantal-1)
               Actie.Index=0;
            else
               Actie.Index++;
            LeesGebeurtenis(pTestParams->Info, Tabel, &Actie);
            pTabel=Tabel;
            while (pTabel!=NULL)
               {
               if (pTabel->Index==Actie.Index)
                  break;
               pTabel=pTabel->Volgende;
               }
            WinSetWindowText(WinWindowFromID(hwnd, DLG_TEST_ST_EVENT), pTabel->Naam);
            mciPlayFile((HWND) NULL, Actie.Bestand, MCI_ASYNC, (PSZ) NULL, (HWND) NULL);
            }
            break;
         case DLG_TEST_PB_REPEAT:
            LeesGebeurtenis(pTestParams->Info, Tabel, &Actie);
            pTabel=Tabel;
            while (pTabel!=NULL)
               {
               if (pTabel->Index==Actie.Index)
                  break;
               pTabel=pTabel->Volgende;
               }
            WinSetWindowText(WinWindowFromID(hwnd, DLG_TEST_ST_EVENT), pTabel->Naam);
            mciPlayFile((HWND) NULL, Actie.Bestand, MCI_ASYNC, (PSZ) NULL, (HWND) NULL);
            break;
         default:
            break;
         }
      break;
   case WM_CLOSE:
      WisNaamTabel(Tabel);
      WinDismissDlg(hwnd, TRUE);
      break;
   default:
      return WinDefDlgProc(hwnd, msg, mp1, mp2);
   }
return (MRESULT)FALSE;
}

