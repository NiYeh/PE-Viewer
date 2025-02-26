// PEviewer.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include "DialogMain.h"
#include "DialogPeView.h"
#include "DialogSection.h"
#include "DialogCatalogue.h"
#include "ImportTable.h"

#include <commctrl.h>			
#pragma comment(lib,"comctl32.lib")			

HINSTANCE hAppInstance;

HICON hIconSmall;
HICON hIconBig;

TCHAR szFilePath[256];

BOOL CALLBACK MainDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK PeViewDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);	
BOOL CALLBACK SectionDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK CatalogueDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ImportTableDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	INITCOMMONCONTROLSEX icex;
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icex);

	hAppInstance = hInstance;

	hIconSmall = LoadIcon (hAppInstance, MAKEINTRESOURCE (IDI_ICON_SMALL));
	hIconBig = LoadIcon (hAppInstance, MAKEINTRESOURCE (IDI_ICON_BIG));

 	// TODO: Place code here.
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, MainDlgProc);



	return 0;
}

// ************************** MainDlgProc **************************
BOOL CALLBACK MainDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)			
{
	OPENFILENAME stOpenFile;
									
	switch(uMsg)								
	{								
	case WM_INITDIALOG:																				
		{
			//设置图标
			SendMessage(hDlg,WM_SETICON,ICON_BIG,(DWORD)hIconBig);
			SendMessage(hDlg,WM_SETICON,ICON_SMALL,(DWORD)hIconSmall);

			InitProcessListView(hDlg);
			InitModulesListView(hDlg);
			break;
		}

	case WM_CLOSE:
		{
			EndDialog(hDlg, 0);
			break;
		}

	case WM_NOTIFY:
		{
			NMHDR* pNMHDR = (NMHDR*)lParam;
			if (wParam == IDC_LIST_PROCESS && pNMHDR->code == NM_CLICK)
			{
				EunmModules(GetDlgItem(hDlg, IDC_LIST_MOUDLE), GetDlgItem(hDlg, IDC_LIST_PROCESS), wParam, lParam);
			}
			break;
		}
		
	case  WM_COMMAND :													
		switch (LOWORD (wParam))							
		{							
			case IDC_BUTTON_OPEN :							
				{
					TCHAR szPeFileExt[100] = "*.exe;*.dll;*.src;*.drv;*.sys";
					TCHAR szFileName[256];
					memset(szFileName, 0, 256);
					memset(szFilePath, 0, 256);
					memset(&stOpenFile, 0, sizeof(OPENFILENAME));
					stOpenFile.lStructSize = sizeof(OPENFILENAME);
					stOpenFile.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
					stOpenFile.hwndOwner = hDlg;
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
					EndDialog(hDlg, 0);
					return TRUE;
				}
		}							
		break;
    }
									
	return FALSE ;								
}

// ************************** PeViewDlgProc **************************
BOOL CALLBACK PeViewDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)			
{										
	switch(uMsg)								
	{								
		case WM_INITDIALOG:																				
			{
				//设置图标
				SendMessage(hDlg,WM_SETICON,ICON_BIG,(DWORD)hIconBig);
				SendMessage(hDlg,WM_SETICON,ICON_SMALL,(DWORD)hIconSmall);

				InitPeView(hDlg, szFilePath);
				break;
			}

		case WM_CLOSE:
			{
				EndDialog(hDlg, 0);
				break;
			}

		case  WM_COMMAND :													
			switch (LOWORD (wParam))							
			{							
				case IDC_BUTTON_CATALOGUE :							
					{
						DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_CATALOGUE), NULL, CatalogueDlgProc);
						return TRUE;
					}
					
				case IDC_BUTTON_SECTIONS:																
					{
						DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_SECTION), NULL, SectionDlgProc);
						return TRUE;
					}
					
				case IDC_BUTTON_PEVIEW_CLOSE:
					{
						EndDialog(hDlg, 0);
						return TRUE;
					}
			}
			
		break;
    }
									
	return FALSE ;								
}

// ************************** SectionDlgProc **************************
BOOL CALLBACK SectionDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)			
{										
	switch(uMsg)								
	{								
		case WM_INITDIALOG:																				
			{
				//设置图标
				SendMessage(hDlg,WM_SETICON,ICON_BIG,(DWORD)hIconBig);
				SendMessage(hDlg,WM_SETICON,ICON_SMALL,(DWORD)hIconSmall);

				InitSectionListView(hDlg, szFilePath);
				break;
			}

		case WM_CLOSE:
			{
				EndDialog(hDlg, 0);
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
BOOL CALLBACK CatalogueDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)			
{										
	switch(uMsg)								
	{								
		case WM_INITDIALOG:																				
			{
				//设置图标
				SendMessage(hDlg,WM_SETICON,ICON_BIG,(DWORD)hIconBig);
				SendMessage(hDlg,WM_SETICON,ICON_SMALL,(DWORD)hIconSmall);

				InitCatalogue(hDlg, szFilePath);
				break;
			}

		case WM_CLOSE:
			{
				EndDialog(hDlg, 0);
				break;
			}

		case WM_NOTIFY:
			{
				break;
			}

		case  WM_COMMAND:
			switch(LOWORD (wParam))
			{
				case IDC_BUTTON_CATALOGUE_CLOSE:
					{
						EndDialog(hDlg, 0);
						return TRUE;
					}

				case IDC_BUTTON_IMPORTTABLE:
					{
						DialogBox(hAppInstance, MAKEINTRESOURCE(IDC_IMPORTTABLE), NULL, ImportTableDlgProc);
						return TRUE;
					}
			}

		break;
    }
									
	return FALSE ;								
}

// ************************** AboutDlgProc **************************
BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_INITDIALOG:
		{
			//设置图标
			SendMessage(hDlg,WM_SETICON,ICON_BIG,(DWORD)hIconBig);
			SendMessage(hDlg,WM_SETICON,ICON_SMALL,(DWORD)hIconSmall);
			break;
		}

		case WM_CLOSE:
		{
			EndDialog(hDlg, 0);
			break;
		}

		break;
	}

	return FALSE;
}

// ************************** ImportTableDlgProc **************************
BOOL CALLBACK ImportTableDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_INITDIALOG:
		{
			//设置图标
			SendMessage(hDlg,WM_SETICON,ICON_BIG,(DWORD)hIconBig);
			SendMessage(hDlg,WM_SETICON,ICON_SMALL,(DWORD)hIconSmall);
			InitImportListView(hDlg, szFilePath);
			InitImportModuleListView(hDlg, szFilePath);
			break;
		}

		case WM_NOTIFY:
		{
			NMHDR* pNMHDR = (NMHDR*)lParam;
			if (wParam == IDC_LIST_IMPORTLIST1 && pNMHDR->code == NM_CLICK)
			{
				EnumImportModule(GetDlgItem(hDlg, IDC_LIST_IMPORTLIST2), GetDlgItem(hDlg, IDC_LIST_IMPORTLIST1), wParam, lParam, szFilePath);
			}
			break;
		}

		case WM_CLOSE:
		{
			EndDialog(hDlg, 0);
			break;
		}

		break;
	}

	return FALSE;
}
