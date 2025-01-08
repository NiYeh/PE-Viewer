#pragma once

#include "Stdafx.h"

#include <commctrl.h>			
#pragma comment(lib,"comctl32.lib")

VOID InitCatalogue(HWND hwndDlg, LPSTR lpszFile);

VOID InitExportTable(HWND hwndDlg, LPSTR lpszFile);

VOID InitImportTable(HWND hwndDlg, LPSTR lpszFile);

VOID InitResource(HWND hwndDlg, LPSTR lpszFile);

VOID InitRelocation(HWND hwndDlg, LPSTR lpszFile);

VOID InitBoundImport(HWND hwndDlg, LPSTR lpszFile);

VOID InitIAT(HWND hwndDlg, LPSTR lpszFile);

