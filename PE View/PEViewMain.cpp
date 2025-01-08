#define _CRT_SECURE_NO_WARNINGS 1

#include "Stdafx.h"
#include "DialogMain.h"
#include "DialogPeView.h"
#include "DialogSection.h"
#include "DialogCatalogue.h"

#include <commctrl.h>			
#pragma comment(lib,"comctl32.lib")

HINSTANCE hAppInstance;
TCHAR szFilePath[256];

BOOL CALLBACK MainDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK PeViewDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK SectionDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK AboutDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK CatalogueDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ExportTableDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ImportTableDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ResourceDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK RelocationDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK BoundImportDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK IATDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	INITCOMMONCONTROLSEX icex;
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icex);

	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, MainDlgProc);

	return 0;
}


// ************************** MainDlgProc **************************
BOOL CALLBACK MainDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HICON hIconSmall;
	HICON hIconBig;

	OPENFILENAME stOpenFile;

	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		hIconSmall = LoadIcon(hAppInstance, MAKEINTRESOURCE(IDI_ICON_BIG));
		hIconBig = LoadIcon(hAppInstance, MAKEINTRESOURCE(IDI_ICON_SMALL));
		//设置图标
		SendMessage(hwndDlg, WM_SETICON, ICON_BIG, (DWORD)hIconBig);
		SendMessage(hwndDlg, WM_SETICON, ICON_SMALL, (DWORD)hIconSmall);
		InitProcessListView(hwndDlg);
		InitModulesListView(hwndDlg);
		break;
	}

	case WM_CLOSE:
	{
		EndDialog(hwndDlg, 0);
		break;
	}

	case WM_NOTIFY:
	{
		NMHDR* pNMHDR = (NMHDR*)lParam;
		if (wParam == IDC_LIST_PROCESS && pNMHDR->code == NM_CLICK)
		{
			EunmModules(GetDlgItem(hwndDlg, IDC_LIST_MOUDLE), GetDlgItem(hwndDlg, IDC_LIST_PROCESS), wParam, lParam);
		}

		break;
	}

	case  WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
			case IDC_BUTTON_OPEN:
			{
				TCHAR szPeFileExt[100] = "*.exe;*.dll;*.src;*.drv;*.sys";
				TCHAR szFileName[256];
				memset(szFileName, 0, 256);
				memset(szFilePath, 0, 256);
				memset(&stOpenFile, 0, sizeof(OPENFILENAME));
				stOpenFile.lStructSize = sizeof(OPENFILENAME);
				stOpenFile.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
				stOpenFile.hwndOwner = hwndDlg;
				stOpenFile.lpstrFilter = szPeFileExt;
				stOpenFile.lpstrFile = szFileName;
				stOpenFile.nMaxFile = MAX_PATH;

				GetOpenFileName(&stOpenFile);

				if (szFileName[0] == 0)
				{
					MessageBox(0, TEXT("请选择文件"), TEXT("Window"), 0);
					return TRUE;
				}

				strcpy(szFilePath, szFileName);
				DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_PEVIEW), NULL, PeViewDlgProc);

				return TRUE;
			}

			case IDC_BUTTON_ABOUT:
			{
				DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_ABOUT), NULL, AboutDlgProc);
				return TRUE;
			}

			case IDC_BUTTON_EXIT:
			{
				EndDialog(hwndDlg, 0);
				break;
			}
		}
		break;
	}
	}

	return FALSE;
}

// ************************** PeViewDlgProc **************************
BOOL CALLBACK PeViewDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		InitPeView(hwndDlg, szFilePath);
		break;
	}

	case WM_CLOSE:
	{
		EndDialog(hwndDlg, 0);
		break;
	}

	case  WM_COMMAND:
		switch (LOWORD(wParam))
		{
			case IDC_BUTTON_CATALOGUE:
			{
				DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_CATALOGUE), NULL, CatalogueDlgProc);
				return TRUE;
			}

			case IDC_BUTTON_SECTIONS:
			{
				DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_SECTION), NULL, SectionDlgProc);
				return TRUE;
			}

			case IDC_BUTTON_CLOSE_PEVIEW:
			{
				EndDialog(hwndDlg, 0);
				return TRUE;
			}
		}

		break;
	}

	return FALSE;
}

// ************************** SectionDlgProc **************************
BOOL CALLBACK SectionDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		InitSectionListView(hwndDlg, szFilePath);
		break;
	}

	case WM_CLOSE:
	{
		EndDialog(hwndDlg, 0);
		break;
	}

	case WM_NOTIFY:
	{
		break;
	}

	break;
	}

	return FALSE;
}

// ************************** CatalogueDlgProc **************************
BOOL CALLBACK CatalogueDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		InitCatalogue(hwndDlg, szFilePath);
		break;
	}

	case WM_CLOSE:
	{
		EndDialog(hwndDlg, 0);
		break;
	}

	case WM_NOTIFY:
	{
		break;
	}

	case  WM_COMMAND:
		switch (LOWORD(wParam))
		{
			case IDC_BUTTON_CATALOGUE_CLOSE:
			{
				EndDialog(hwndDlg, 0);
				return TRUE;
			}

			case IDC_BUTTON_EXPORTTABLE:
			{
				DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_EXPORTTABLE), NULL, ExportTableDlgProc);
				return TRUE;
			}

			case IDC_BUTTON_IMPORTTABLE:
			{
				DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_IMPORTTABLE), NULL, ImportTableDlgProc);
				return TRUE;
			}

			case IDC_BUTTON_RESOURCE:
			{
				DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_RESOURCE), NULL, ResourceDlgProc);
				return TRUE;
			}

			case IDC_BUTTON_RELOCATION:
			{
				DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_RELOCATION), NULL, RelocationDlgProc);
				return TRUE;
			}

			case IDC_BUTTON_IAT:
			{
				DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_IAT), NULL, IATDlgProc);
				return TRUE;
			}

			case IDC_BUTTON_BOUNDIMPORT:
			{
				DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_BOUNDIMPORT), NULL, BoundImportDlgProc);
				return TRUE;
			}
		}

		break;
	}

	return FALSE;
}

// ************************** AboutDlgProc **************************
BOOL CALLBACK AboutDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		break;
	}

	case WM_CLOSE:
	{
		EndDialog(hwndDlg, 0);
		break;
	}

	break;
	}

	return FALSE;
}

// ************************** ExportTableDlgProc **************************
BOOL CALLBACK ExportTableDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		InitExportTable(hwndDlg, szFilePath);
		break;
	}

	case WM_CLOSE:
	{
		EndDialog(hwndDlg, 0);
		break;
	}

	break;
	}

	return FALSE;
}

// ************************** ImportTableDlgProc **************************
BOOL CALLBACK ImportTableDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		InitImportTable(hwndDlg, szFilePath);
		break;
	}

	case WM_CLOSE:
	{
		EndDialog(hwndDlg, 0);
		break;
	}

	break;
	}

	return FALSE;
}

// ************************** ResourceDlgProc **************************
BOOL CALLBACK ResourceDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		InitResource(hwndDlg, szFilePath);
		break;
	}

	case WM_CLOSE:
	{
		EndDialog(hwndDlg, 0);
		break;
	}

	break;
	}

	return FALSE;
}

// ************************** RelocationDlgProc **************************
BOOL CALLBACK RelocationDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		InitRelocation(hwndDlg, szFilePath);
		break;
	}

	case WM_CLOSE:
	{
		EndDialog(hwndDlg, 0);
		break;
	}

	break;
	}

	return FALSE;
}

// ************************** BoundImportDlgProc **************************
BOOL CALLBACK BoundImportDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		InitBoundImport(hwndDlg, szFilePath);
		break;
	}

	case WM_CLOSE:
	{
		EndDialog(hwndDlg, 0);
		break;
	}

	break;
	}

	return FALSE;
}

// ************************** IATDlgProc **************************
BOOL CALLBACK IATDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		InitIAT(hwndDlg, szFilePath);
		break;
	}

	case WM_CLOSE:
	{
		EndDialog(hwndDlg, 0);
		break;
	}

	break;
	}

	return FALSE;
}