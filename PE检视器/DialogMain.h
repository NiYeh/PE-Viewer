// DialogMain.h: interface for the DialogMain class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIALOGMAIN_H__FF2978A7_6D79_4D86_84EB_69DDFF11E1B5__INCLUDED_)
#define AFX_DIALOGMAIN_H__FF2978A7_6D79_4D86_84EB_69DDFF11E1B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
#include "resource.h"

#include <commctrl.h>			
#pragma comment(lib,"comctl32.lib")	

#include <tlHelp32.h>

VOID InitProcessListView(HWND hDlg);
VOID InitModulesListView(HWND hDlg);
VOID EnumProcess(HWND hListProcess);
VOID EunmModules(HWND hListModules, HWND hListProcess, WPARAM wParam, LPARAM lParam);

DWORD GetMoudleBaseAddr(DWORD dwPid, const TCHAR* szDllName);
DWORD GetMoudleBaseSizeAddr(DWORD dwPid, const TCHAR* szDllName);

#endif // !defined(AFX_DIALOGMAIN_H__FF2978A7_6D79_4D86_84EB_69DDFF11E1B5__INCLUDED_)
