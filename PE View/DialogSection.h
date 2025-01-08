#pragma once

#include "Stdafx.h"

#include <commctrl.h>			
#pragma comment(lib,"comctl32.lib")

VOID InitSectionListView(HWND hwndDlg, LPSTR lpszFile);
VOID EnumSection(HWND hListSection, LPSTR lpszFile);