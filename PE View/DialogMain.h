#pragma once

#include "Stdafx.h"

#include <commctrl.h>			
#pragma comment(lib,"comctl32.lib")	

#include <tlHelp32.h>

VOID InitProcessListView(HWND hwndDlg);
VOID InitModulesListView(HWND hwndDlg);
VOID EnumProcess(HWND hListProcess);
VOID EunmModules(HWND hListModules, HWND hListProcess, WPARAM wParam, LPARAM lParam);

DWORD GetMoudleBaseAddr(DWORD dwPid, const TCHAR* szDllName);
DWORD GetMoudleBaseSizeAddr(DWORD dwPid, const TCHAR* szDllName);