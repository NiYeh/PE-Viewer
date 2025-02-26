// DialogSection.h: interface for the DialogSection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIALOGSECTION_H__275FF822_155B_4E44_A74B_F4721A9DA315__INCLUDED_)
#define AFX_DIALOGSECTION_H__275FF822_155B_4E44_A74B_F4721A9DA315__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
#include "resource.h"

#include <commctrl.h>			
#pragma comment(lib,"comctl32.lib")

VOID InitSectionListView(HWND hDlg, LPSTR lpszFile);
VOID EnumSection(HWND hListSection, LPSTR lpszFile);

#endif // !defined(AFX_DIALOGSECTION_H__275FF822_155B_4E44_A74B_F4721A9DA315__INCLUDED_)
