// ExportTable.h: interface for the ExportTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXPORTTABLE_H__9C01FC8E_AC7E_4C79_9CBD_2D12AFDFB8F1__INCLUDED_)
#define AFX_EXPORTTABLE_H__9C01FC8E_AC7E_4C79_9CBD_2D12AFDFB8F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
#include "resource.h"

#include <commctrl.h>			
#pragma comment(lib,"comctl32.lib")

VOID InitExport(HWND hDlg, LPSTR lpszFile);

VOID EnumExport(HWND hDlg, HWND hListProcess, LPSTR lpszFile);

VOID BubSort(WORD* arr, DWORD len);

#endif // !defined(AFX_EXPORTTABLE_H__9C01FC8E_AC7E_4C79_9CBD_2D12AFDFB8F1__INCLUDED_)
