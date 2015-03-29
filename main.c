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

MRESULT EXPENTRY WinProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
USHORT          ControlID, NotifyCode, usResult;
ULONG           ulSize, ulResult;
USHORT          Volume;
char            *buffer, *namestr, *deel2, *deel3,
                StartPad[CCHMAXPATH], Gebeurtenis[CCHMAXPATH], Temp[CCHMAXPATH];
SHORT           action, scheme;
HWND            HisHwnd, hwndFileDlg;
CREATEPARAMS    *CreateParams;
FILEDLG         FileDlg;
static PTABEL   Tabel;
PTABEL          pTabel;
static PINFO    pInfo;
TESTPARAMS      TestParams;
ACTIE           Actie;
static ACTIE    Undo;
switch (msg)
   {
   case WM_INITDLG:
      pInfo=(PINFO)PVOIDFROMMP(mp2);
      // reserveer geheugen voor het eerste record (wordt vrijgegeven in WisNaamTabel)
      DosAllocMem((void**)&Tabel, sizeof(TABEL), PAG_COMMIT | PAG_READ | PAG_WRITE);
      LeesNaam(Tabel, pInfo->PrfMMPM);
      LeesHuidigSchema(Tabel, pInfo);
      pTabel=Tabel;
      while (pTabel!=NULL)
         {
         WinSendMsg(WinWindowFromID(hwnd, LB_ACTIONS), LM_INSERTITEM, (MPARAM)pTabel->Index, (MPARAM)pTabel->Naam);
         pTabel=pTabel->Volgende;
         }
      WinSendMsg(WinWindowFromID(hwnd, EF_SOUND), EM_SETTEXTLIMIT, (MPARAM)CCHMAXPATH, 0L);
      // Laat de lijst met schema's opstellen
      WinPostMsg(hwnd, UM_UPDATE, (MPARAM)(DI_SCHEME | DI_ACTION | DI_CHANGE | DI_FIND), 0L);
      // Vertel het prikbord dat we willen weten wanneer er data op staat
      WinSetClipbrdViewer(pInfo->hab, hwnd);
      // stel de Volume Circular Slider in
      // Van 0% tot 100%
      WinSendMsg(WinWindowFromID(hwnd, CSL_VOLUME), CSM_SETRANGE, MPFROMLONG(0L), MPFROMLONG(100L));
      // Markeringen om de 10%, stapgrootte 1%
      WinSendMsg(WinWindowFromID(hwnd, CSL_VOLUME), CSM_SETINCREMENT, MPFROMLONG(1L), MPFROMLONG(10L));
      // Beginwaarde instellen (staat in pInfo->DefaultVolume)
      WinSendMsg(WinWindowFromID(hwnd, CSL_VOLUME), CSM_SETVALUE, MPFROMLONG(pInfo->DefaultVolume), NULL);
      break;
   case WM_COMMAND:
      ControlID = SHORT1FROMMP(mp1);
      switch (ControlID)
         {
         case PB_PLAY:
            WinQueryWindowText(WinWindowFromID(hwnd, EF_SOUND), CCHMAXPATH, Actie.Bestand);
            WinSendMsg(WinWindowFromID(hwnd, CSL_VOLUME), CSM_QUERYVALUE, MPFROMP(&Actie.Volume), MPARAM(0L));
            // Vraag op welk schema er geselecteerd is
            scheme=SHORT1FROMMR(WinSendMsg(WinWindowFromID(hwnd, LB_SCHEMES), LM_QUERYSELECTION, MPFROMSHORT(LIT_FIRST), (MPARAM)0L));
            // Vraag de naam van het schema op
            WinSendMsg(WinWindowFromID(hwnd, LB_SCHEMES), LM_QUERYITEMTEXT, MPFROM2SHORT(scheme,201), MPFROMP(Actie.Schema));
            // vraag de actie op
            Actie.Index=SHORT1FROMMR(WinSendMsg(WinWindowFromID(hwnd, LB_ACTIONS), LM_QUERYSELECTION, MPFROMSHORT(LIT_FIRST), (MPARAM)0L));
            WinQueryWindowText(WinWindowFromID(hwnd, EF_SOUND), CCHMAXPATH, Actie.Bestand);
            mciPlayFile((HWND) NULL, Actie.Bestand, MCI_ASYNC, (PSZ) NULL, (HWND) NULL);
            break;
         case PB_COPY:
            DosAllocMem((void **)&CreateParams, sizeof(CREATEPARAMS), PAG_COMMIT | PAG_READ | PAG_WRITE);
            // Vraag op welk schema er geselecteerd is
            scheme=SHORT1FROMMR(WinSendMsg(WinWindowFromID(hwnd, LB_SCHEMES), LM_QUERYSELECTION, MPFROMSHORT(LIT_FIRST), (MPARAM)0L));
            // Vraag de naam van het schema op
            WinSendMsg(WinWindowFromID(hwnd, LB_SCHEMES), LM_QUERYITEMTEXT, MPFROM2SHORT(scheme, 201), MPFROMP(Actie.Schema));
            // Lees titel en tekst in uit resources
            WinLoadString(pInfo->hab, NULLHANDLE, COPY_TITLE, 81, CreateParams->Title);
            WinLoadString(pInfo->hab, NULLHANDLE, COPY_TEXT, 81, CreateParams->StaticText);
            strcpy(CreateParams->SchemeName, "");
            CreateParams->ok=FALSE;
            ulResult=WinDlgBox(HWND_DESKTOP, hwnd, DlgProc, (HMODULE)0, DLG_DIALOG, CreateParams);
            if (CreateParams->ok==TRUE) // In messagebox is op Ok geklikt
               {
               KopieerSchema(Actie.Schema, CreateParams->SchemeName, pInfo, Tabel);
               WinPostMsg(hwnd, UM_UPDATE, (MPARAM)(DI_SCHEME | DI_ACTION | DI_CHANGE), 0L);
               }
            DosFreeMem(CreateParams);
            break;
         case PB_RENAME:
            DosAllocMem((void **)&CreateParams, sizeof(CREATEPARAMS), PAG_COMMIT | PAG_READ | PAG_WRITE);
            // Vraag op welk schema er geselecteerd is
            scheme=SHORT1FROMMR(WinSendMsg(WinWindowFromID(hwnd, LB_SCHEMES), LM_QUERYSELECTION, MPFROMSHORT(LIT_FIRST), (MPARAM)0L));
            // Vraag de naam van het schema op
            WinSendMsg(WinWindowFromID(hwnd, LB_SCHEMES), LM_QUERYITEMTEXT, MPFROM2SHORT(scheme, 201), MPFROMP(Actie.Schema));
            // Lees titel en tekst in uit resources
            WinLoadString(pInfo->hab, NULLHANDLE, RENAME_TITLE, 81, CreateParams->Title);
            WinLoadString(pInfo->hab, NULLHANDLE, RENAME_TEXT, 81, CreateParams->StaticText);
            CreateParams->ok=FALSE;
            ulResult=WinDlgBox(HWND_DESKTOP, hwnd, DlgProc, (HMODULE)0, DLG_DIALOG, CreateParams);
            if (CreateParams->ok==TRUE) // In messagebox is op Ok geklikt
               {
               HernoemSchema(Actie.Schema, CreateParams->SchemeName, pInfo, Tabel);
               WinPostMsg(hwnd, UM_UPDATE, (MPARAM)(DI_SCHEME | DI_ACTION | DI_CHANGE), 0L);
               }
            DosFreeMem(CreateParams);
            break;
         case PB_ADD:
            DosAllocMem((void **)&CreateParams, sizeof(CREATEPARAMS), PAG_COMMIT | PAG_READ | PAG_WRITE);
            // Lees titel en tekst in uit resources
            WinLoadString(pInfo->hab, NULLHANDLE, CREATE_TITLE, 81, CreateParams->Title);
            WinLoadString(pInfo->hab, NULLHANDLE, CREATE_TEXT, 81, CreateParams->StaticText);
            CreateParams->ok=FALSE;
            ulResult=WinDlgBox(HWND_DESKTOP, hwnd, DlgProc, (HMODULE)0, DLG_DIALOG, CreateParams);
            if (CreateParams->ok==TRUE) // In messagebox is op Ok geklikt
               {
               NieuwSchema(CreateParams->SchemeName, pInfo, Tabel);
               WinPostMsg(hwnd, UM_UPDATE, (MPARAM)(DI_SCHEME | DI_ACTION | DI_CHANGE), 0L);
               }
            DosFreeMem(CreateParams);
            break;
         case PB_DELETE:
            DosAllocMem((void **)&CreateParams, sizeof(CREATEPARAMS), PAG_COMMIT | PAG_READ | PAG_WRITE);
            // Vraag op welk schema er geselecteerd is
            scheme=SHORT1FROMMR(WinSendMsg(WinWindowFromID(hwnd, LB_SCHEMES), LM_QUERYSELECTION, MPFROMSHORT(LIT_FIRST), (MPARAM)0L));
            // Vraag de naam van het schema op
            WinSendMsg(WinWindowFromID(hwnd, LB_SCHEMES), LM_QUERYITEMTEXT, MPFROM2SHORT(scheme, 201), MPFROMP(Actie.Schema));
            // Lees titel en tekst in uit resources
            WinLoadString(pInfo->hab, NULLHANDLE, DELETE_TITLE, 81, CreateParams->Title);
            WinLoadString(pInfo->hab, NULLHANDLE, DELETE_TEXT, 81, CreateParams->StaticText);
            usResult=WinMessageBox(HWND_DESKTOP, hwnd, CreateParams->StaticText, CreateParams->Title, 0, MB_WARNING | MB_YESNO);
            if (usResult==MBID_YES)
               {
               WisSchema(Actie.Schema, pInfo, Tabel);
               WinPostMsg(hwnd, UM_UPDATE, (MPARAM)(DI_SCHEME | DI_ACTION | DI_CHANGE), 0L);
               }
            DosFreeMem(CreateParams);
            break;
         case PB_LOCATE:
            memset(&FileDlg, 0, sizeof(FILEDLG));
            FileDlg.cbSize=sizeof(FILEDLG);
            FileDlg.fl=FDS_OPEN_DIALOG | FDS_CENTER;
            strcpy(StartPad, pInfo->DefaultSoundDir);
            strcpy(FileDlg.szFullFile, StartPad);
            hwndFileDlg=WinFileDlg(HWND_DESKTOP, hwnd, &FileDlg);
            if ((hwndFileDlg!=NULLHANDLE) && (FileDlg.lReturn==DID_OK))
               {
               WinSetDlgItemText(hwnd, EF_SOUND, FileDlg.szFullFile);
               WinSetFocus(HWND_DESKTOP, WinWindowFromID(hwnd, EF_SOUND));
               }
            break;
         case PB_TEST:
            // Vraag op welk schema er geselecteerd is
            scheme=SHORT1FROMMR(WinSendMsg(WinWindowFromID(hwnd, LB_SCHEMES), LM_QUERYSELECTION, MPFROMSHORT(LIT_FIRST), (MPARAM)0L));
            // Vraag de naam van het schema op
            WinSendMsg(WinWindowFromID(hwnd, LB_SCHEMES), LM_QUERYITEMTEXT, MPFROM2SHORT(scheme, 201), MPFROMP(TestParams.Schema));
            TestParams.Info=pInfo;
            WinDlgBox(HWND_DESKTOP, hwnd, TestProc, (HMODULE)0, DLG_TEST, &TestParams);
            break;
         case PB_APPLY:
            // Vraag op welk schema er geselecteerd is
            scheme=SHORT1FROMMR(WinSendMsg(WinWindowFromID(hwnd, LB_SCHEMES), LM_QUERYSELECTION, MPFROMSHORT(LIT_FIRST), (MPARAM)0L));
            // Vraag de naam van het schema op
            WinSendMsg(WinWindowFromID(hwnd, LB_SCHEMES), LM_QUERYITEMTEXT, MPFROM2SHORT(scheme, 201), MPFROMP(Actie.Schema));
            MaakSchemaActief(Actie.Schema, Tabel, pInfo);
            break;
         case MI_PRODUCTINFO:
            ulResult=WinDlgBox(HWND_DESKTOP, hwnd, ProdInfoProc, (HMODULE)0, DLG_PRODINFO, NULL);
            break;
         case MI_FIND:
            ulResult=WinDlgBox(HWND_DESKTOP, hwnd, FindProc, (HMODULE)0, DLG_FIND, pInfo);
            break;
         case MI_CLOSE:
            WinPostMsg(hwnd, WM_CLOSE, 0L, 0L);
            break;
         case MI_COPY:
            WinPostMsg(WinWindowFromID(hwnd, EF_SOUND), EM_COPY, 0, 0);
            break;
         case MI_PASTE:
            WinPostMsg(WinWindowFromID(hwnd, EF_SOUND), EM_PASTE, 0, 0);
            break;
         case MI_CUT:
            WinPostMsg(WinWindowFromID(hwnd, EF_SOUND), EM_CUT, 0, 0);
            break;
         case MI_SETTINGS:
            ulResult=WinDlgBox(HWND_DESKTOP, hwnd, SettingsProc, (HMODULE)0, DLG_SETTINGS, NULL);
            break;
         case MI_IMPORT:
            ImportSysSchemes(Tabel, pInfo);
            // Laat de lijst met schema's opstellen
            WinPostMsg(hwnd, UM_UPDATE, (MPARAM)(DI_SCHEME | DI_ACTION | DI_CHANGE | DI_FIND), 0L);
            break;
         case MI_UNDO:
            // is hetzelfde als PB_UNDO, dus kan doorlopen in case PB_UNDO.
            // Hier dus NIKS tussen zetten!!!
         case PB_UNDO:
            WinSendMsg(WinWindowFromID(hwnd, CSL_VOLUME), CSM_SETVALUE, MPFROMLONG(Undo.Volume), NULL);
            WinSetDlgItemText(hwnd, EF_SOUND, Undo.Bestand);
            EnableItems(pInfo->hab, hwnd, DI_ACTION);
            DisableItems(pInfo->hab, hwnd, DI_CHANGE);
            break;
         case MI_RESTORE:
            LeesHuidigSchema(Tabel, pInfo);
            break;
         default:
            break;
         } // switch (ControlID)
      break; // WM_COMMAND
   case WM_CONTROL:
      ControlID = SHORT1FROMMP(mp1);
      NotifyCode = SHORT2FROMMP(mp1);
      switch (ControlID)
         {
         case EF_SOUND:
            {
            if (NotifyCode==EN_KILLFOCUS)
               {
               WinQueryWindowText(WinWindowFromID(hwnd, EF_SOUND), CCHMAXPATH, Actie.Bestand);
               WinSendMsg(WinWindowFromID(hwnd, CSL_VOLUME), CSM_QUERYVALUE, MPFROMP(&Actie.Volume), MPARAM(0L));
               // Vraag op welk schema er geselecteerd is
               scheme=SHORT1FROMMR(WinSendMsg(WinWindowFromID(hwnd, LB_SCHEMES), LM_QUERYSELECTION, MPFROMSHORT(LIT_FIRST), (MPARAM)0L));
               // Vraag de naam van het schema op
               WinSendMsg(WinWindowFromID(hwnd, LB_SCHEMES), LM_QUERYITEMTEXT, MPFROM2SHORT(scheme,201), MPFROMP(Actie.Schema));
               // vraag de actie op
               Actie.Index=SHORT1FROMMR(WinSendMsg(WinWindowFromID(hwnd, LB_ACTIONS), LM_QUERYSELECTION, MPFROMSHORT(LIT_FIRST), (MPARAM)0L));
               BewaarGebeurtenis(pInfo, Tabel, &Actie);
               }
            if (NotifyCode==EN_CHANGE)
               {
               EnableItems(pInfo->hab, hwnd, DI_CHANGE);
               }
            break;
            }
         case CSL_VOLUME:
            if ((NotifyCode==CSN_SETFOCUS) && (LONGFROMMP(mp2)==FALSE))
               {
               WinQueryWindowText(WinWindowFromID(hwnd, EF_SOUND), CCHMAXPATH, Actie.Bestand);
               WinSendMsg(WinWindowFromID(hwnd, CSL_VOLUME), CSM_QUERYVALUE, MPFROMP(&Actie.Volume), MPARAM(0L));
               // Vraag op welk schema er geselecteerd is
               scheme=SHORT1FROMMR(WinSendMsg(WinWindowFromID(hwnd, LB_SCHEMES), LM_QUERYSELECTION, MPFROMSHORT(LIT_FIRST), (MPARAM)0L));
               // Vraag de naam van het schema op
               WinSendMsg(WinWindowFromID(hwnd, LB_SCHEMES), LM_QUERYITEMTEXT, MPFROM2SHORT(scheme,201), MPFROMP(Actie.Schema));
               // vraag de actie op
               Actie.Index=SHORT1FROMMR(WinSendMsg(WinWindowFromID(hwnd, LB_ACTIONS), LM_QUERYSELECTION, MPFROMSHORT(LIT_FIRST), (MPARAM)0L));
               BewaarGebeurtenis(pInfo, Tabel, &Actie);
               }
            if (NotifyCode==CSN_CHANGED)
               {
               EnableItems(pInfo->hab, hwnd, DI_CHANGE);
               }
            break;
         case LB_SCHEMES:
            {
            if ((NotifyCode==LN_ENTER) || (NotifyCode==LN_SELECT))
               {
               // Maak de selectie van de actie ongedaan
               WinSendMsg(WinWindowFromID(hwnd, LB_ACTIONS), LM_SELECTITEM, MPFROMSHORT(LIT_NONE), MPFROMSHORT(FALSE));
               // Maak het entry field leeg
               WinSetDlgItemText(hwnd, EF_SOUND, "");
               EnableItems(pInfo->hab, hwnd, DI_SCHEME);
               DisableItems(pInfo->hab, hwnd, DI_CHANGE | DI_ACTION);
               }
            break;
            }
         case LB_ACTIONS:
            {
            if ((NotifyCode==LN_ENTER) || (NotifyCode==LN_SELECT))
               {
               // vraag de actie op
               action=SHORT1FROMMR(WinSendMsg(WinWindowFromID(hwnd, LB_ACTIONS), LM_QUERYSELECTION, MPFROMSHORT(LIT_FIRST), (MPARAM)0L));
               if (action!=LIT_NONE)
                  {
                  Actie.Index=action;
                  // Vraag op welk schema er geselecteerd is
                  scheme=SHORT1FROMMR(WinSendMsg(WinWindowFromID(hwnd, LB_SCHEMES), LM_QUERYSELECTION, MPFROMSHORT(LIT_FIRST), (MPARAM)0L));
                  // Vraag de naam van het schema op
                  WinSendMsg(WinWindowFromID(hwnd, LB_SCHEMES), LM_QUERYITEMTEXT, MPFROM2SHORT(scheme, 201), MPFROMP(Actie.Schema));
                  // zet de naam van het geluidsbestand in het invoerveld
                  LeesGebeurtenis(pInfo, Tabel, &Actie);
                  strcpy(Undo.Bestand, Actie.Bestand);
                  strcpy(Undo.Schema, Actie.Schema);
                  Undo.Volume=Actie.Volume;
                  Undo.Index=Actie.Index;
                  WinSendMsg(WinWindowFromID(hwnd, CSL_VOLUME), CSM_SETVALUE, MPFROMLONG(Actie.Volume), NULL);
                  WinSetDlgItemText(hwnd, EF_SOUND, Actie.Bestand);
                  EnableItems(pInfo->hab, hwnd, DI_ACTION);
                  DisableItems(pInfo->hab, hwnd, DI_CHANGE);
                  }
               }
            break;
            }
         default:
            return WinDefDlgProc(hwnd, msg, mp1, mp2);
         }
      break; // WM_CONTROL
   case WM_DRAWCLIPBOARD:
      WinOpenClipbrd(pInfo->hab);
      // Staat er tekst op het prikbord?
      if (WinQueryClipbrdData(pInfo->hab,CF_TEXT)!=0)
         { // Ja, maak het menu "Paste" beschikbaar
         WinSendMsg(WinWindowFromID(hwnd, FID_MENU), MM_SETITEMATTR, MPFROM2SHORT(MI_PASTE, TRUE), MPFROM2SHORT(MIA_DISABLED, ~MIA_DISABLED));
         }
      else
         { // Nee, maak het menu "Paste" niet meer beschikbaar
         WinSendMsg(WinWindowFromID(hwnd, FID_MENU), MM_SETITEMATTR, MPFROM2SHORT(MI_PASTE, TRUE), MPFROM2SHORT(MIA_DISABLED, MIA_DISABLED));
         }
      WinCloseClipbrd(pInfo->hab);
      break;
   case UM_UPDATE: // De lijst met schema's is veranderd, pas de lijst aan
       // Maak de lijst leeg
       WinSendMsg(WinWindowFromID(hwnd, LB_SCHEMES), LM_DELETEALL, (MPARAM)0L, (MPARAM)0L);
       // Vraag de lijst met schema's op
       PrfQueryProfileSize(pInfo->PrfScheme, NULL, NULL, &ulSize);
       DosAllocMem((void **)&buffer, ulSize+1, PAG_COMMIT | PAG_READ | PAG_WRITE);
       PrfQueryProfileString(pInfo->PrfScheme, NULL, NULL, NULL, (void *)buffer, ulSize+1);
       namestr=buffer;
       while (namestr[0]!=0)
          {
            WinSendMsg(WinWindowFromID(hwnd, LB_SCHEMES), LM_INSERTITEM, MPFROMSHORT(LIT_END), MPFROMP(namestr));
            namestr+=strlen(namestr)+1;
          }
       DosFreeMem(buffer);
       namestr=NULL;
       DisableItems(pInfo->hab, hwnd, (int)mp1);
       break;
    case WM_CLOSE:
       WinDismissDlg(hwnd, TRUE);
       WinPostMsg(hwnd, WM_QUIT, 0L, 0L);
       break;
    default:
       return WinDefDlgProc(hwnd, msg, mp1, mp2);
}
return (MRESULT)FALSE;
}
