#ifndef PMTools_H
#define PMTools_H

#include <os2def.h>

void     CenterWindow( HWND hwnd );
HWND     CreateHelp( HWND hwndFrame, PSZ pszFileName, HMODULE hmod, USHORT usTableID, PSZ pszWindowTitle );
void     DestroyHelp( HWND hwndHelp );
void     SetButtonIcon( HWND hwndButton, HPOINTER hicon );
HWND     LaunchApplication( HWND hwnd, PSZ pszProgram, PSZ pszOptions, PSZ pszDirectory );
HMTX     OneInstance( PSZ pszSemName, BOOL fSwitch );
HWND     LoadMenu( HWND hwnd,HMODULE hmod, USHORT usResID );
HPOINTER LoadIcon( HWND hwnd, HMODULE hmod, USHORT usResID );
HACCEL   LoadAccelerator( HWND hwnd, HMODULE hmod, USHORT usResID );

#endif /* PMTools_H */

