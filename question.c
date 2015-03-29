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
#include "question.h"

MRESULT EXPENTRY DlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
USHORT              ControlID, NotifyCode;
char                Name[201];
static CREATEPARAMS *pCreateParams;
static BOOL         rc;
switch (msg)
   {
   case WM_INITDLG:
      /* Haal uit de doorgegeven structuur de titel, de statische tekst, etc. en pas de controls in het
         dialoog aan. Doe verder nog de andere initialisatie die nodig is. */
      pCreateParams=(CREATEPARAMS*)PVOIDFROMMP(mp2);
      // stel de juiste teksten in
      WinSetWindowText(WinWindowFromID(hwnd, DLG_ST_NAME), pCreateParams->StaticText);
      WinSetWindowText(hwnd, pCreateParams->Title);
      WinEnableWindow(WinWindowFromID(hwnd, DLG_PB_OK), FALSE);
      WinSendMsg(WinWindowFromID(hwnd, DLG_EF_NAME), EM_SETTEXTLIMIT, (MPARAM)200, 0L);
      break;
   case WM_COMMAND:
      ControlID = SHORT1FROMMP(mp1);
      switch (ControlID)
         {
         case DLG_PB_OK:
            WinQueryWindowText(WinWindowFromID(hwnd, DLG_EF_NAME), CCHMAXPATH, pCreateParams->SchemeName);
            pCreateParams->ok=TRUE;
            WinPostMsg(hwnd, WM_CLOSE, 0L, 0L);
            break;
         case DLG_PB_CANCEL:
            pCreateParams->ok=FALSE;
            WinPostMsg(hwnd, WM_CLOSE,0L, 0L);
            break;
         default:
            break;
         }
      break;
   case WM_CONTROL:
      ControlID = SHORT1FROMMP(mp1);
      NotifyCode = SHORT2FROMMP(mp1);
      switch (ControlID)
         {
         case DLG_EF_NAME:
            if (NotifyCode == EN_CHANGE)
               {
               WinQueryWindowText(HWNDFROMMP(mp2),201, Name);
               if (Name[0]!=0)
                  {
                  WinEnableWindow(WinWindowFromID(hwnd, DLG_PB_OK), TRUE);
                  }
               else
                  {
                  WinEnableWindow(WinWindowFromID(hwnd, DLG_PB_OK), FALSE);
                  }
               }
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