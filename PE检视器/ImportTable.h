// ImportTable.h: interface for the ImportTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMPORTTABLE_H__18DAF078_6D11_4C3D_AC6F_8EF2CF3F862B__INCLUDED_)
#define AFX_IMPORTTABLE_H__18DAF078_6D11_4C3D_AC6F_8EF2CF3F862B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
#include "resource.h"

#include <commctrl.h>			
#pragma comment(lib,"comctl32.lib")

VOID InitImportListView(HWND hDlg, LPSTR lpszFile);
VOID InitImportModuleListView(HWND hDlg, LPSTR lpszFile);

VOID EnumImport(HWND hDlg, HWND hListProcess, LPSTR lpszFile);
VOID EnumImportModule(HWND hListModules, HWND hListImport, WPARAM wParam, LPARAM lParam, LPSTR lpszFile);

#endif // !defined(AFX_IMPORTTABLE_H__18DAF078_6D11_4C3D_AC6F_8EF2CF3F862B__INCLUDED_)
