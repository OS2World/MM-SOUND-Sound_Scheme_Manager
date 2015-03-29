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

MRESULT EXPENTRY ProdInfoProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
USHORT ControlID, NotifyCode;
switch (msg)
   {
   case WM_INITDLG:
      break;
   case WM_COMMAND:
      ControlID = SHORT1FROMMP(mp1);
      switch (ControlID)
         {
         case PRODINFO_PB_OK:
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