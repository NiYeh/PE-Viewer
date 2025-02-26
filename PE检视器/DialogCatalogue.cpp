// DialogCatalogue.cpp: implementation of the DialogCatalogue class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DialogCatalogue.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

VOID InitCatalogue(HWND hDlg, LPSTR lpszFile)
{
	PIMAGE_DOS_HEADER pDosHeader = NULL;	
	PIMAGE_NT_HEADERS pNTHeader = NULL;	
	PIMAGE_FILE_HEADER pPEHeader = NULL;	
	PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
	PIMAGE_SECTION_HEADER pSectionHeader = NULL;

	LPVOID pFileBuffer = NULL;
	DWORD fileSize = 0;

	TCHAR szFileName[256];
	memset(szFileName, 0, 256);

	// File --> FileBuffer
	fileSize = ReadPEFile(lpszFile, &pFileBuffer);
	if (!pFileBuffer)
	{
		MessageBox(0, TEXT("文件-->缓冲区失败!"), TEXT("Window"), 0);
		return ;
	}

	pDosHeader = (PIMAGE_DOS_HEADER)pFileBuffer;
	pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pFileBuffer+pDosHeader->e_lfanew);
	pPEHeader = (PIMAGE_FILE_HEADER)(((DWORD)pNTHeader) + 4);		
	pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader+IMAGE_SIZEOF_FILE_HEADER);

	// 导出表
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[0].VirtualAddress);
	SendDlgItemMessage(hDlg, IDC_CATALOGUE_C1, WM_SETTEXT, 0, (DWORD)szFileName);
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[0].Size);
	SendDlgItemMessage(hDlg, IDC_CATALOGUE_C2, WM_SETTEXT, 0, (DWORD)szFileName);
	
	// 导入表
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[1].VirtualAddress);
	SendDlgItemMessage(hDlg, IDC_CATALOGUE_C3, WM_SETTEXT, 0, (DWORD)szFileName);
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[1].Size);
	SendDlgItemMessage(hDlg, IDC_CATALOGUE_C4, WM_SETTEXT, 0, (DWORD)szFileName);

	// 资源表
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[2].VirtualAddress);
	SendDlgItemMessage(hDlg, IDC_CATALOGUE_C5, WM_SETTEXT, 0, (DWORD)szFileName);
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[2].Size);
	SendDlgItemMessage(hDlg, IDC_CATALOGUE_C6, WM_SETTEXT, 0, (DWORD)szFileName);

	// 异常表
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[3].VirtualAddress);
	SendDlgItemMessage(hDlg, IDC_CATALOGUE_C7, WM_SETTEXT, 0, (DWORD)szFileName);
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[3].Size);
	SendDlgItemMessage(hDlg, IDC_CATALOGUE_C8, WM_SETTEXT, 0, (DWORD)szFileName);

	// 安全
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[4].VirtualAddress);
	SendDlgItemMessage(hDlg, IDC_CATALOGUE_C9, WM_SETTEXT, 0, (DWORD)szFileName);
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[4].Size);
	SendDlgItemMessage(hDlg, IDC_CATALOGUE_C10, WM_SETTEXT, 0, (DWORD)szFileName);
	
	// 重定位表
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[5].VirtualAddress);
	SendDlgItemMessage(hDlg, IDC_CATALOGUE_C11, WM_SETTEXT, 0, (DWORD)szFileName);
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[5].Size);
	SendDlgItemMessage(hDlg, IDC_CATALOGUE_C12, WM_SETTEXT, 0, (DWORD)szFileName);

	// 调试
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[6].VirtualAddress);
	SendDlgItemMessage(hDlg, IDC_CATALOGUE_C13, WM_SETTEXT, 0, (DWORD)szFileName);
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[6].Size);
	SendDlgItemMessage(hDlg, IDC_CATALOGUE_C14, WM_SETTEXT, 0, (DWORD)szFileName);

	// 版权
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[7].VirtualAddress);
	SendDlgItemMessage(hDlg, IDC_CATALOGUE_C15, WM_SETTEXT, 0, (DWORD)szFileName);
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[7].Size);
	SendDlgItemMessage(hDlg, IDC_CATALOGUE_C16, WM_SETTEXT, 0, (DWORD)szFileName);

	// 全局指针
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[8].VirtualAddress);
	SendDlgItemMessage(hDlg, IDC_CATALOGUE_C17, WM_SETTEXT, 0, (DWORD)szFileName);
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[8].Size);
	SendDlgItemMessage(hDlg, IDC_CATALOGUE_C18, WM_SETTEXT, 0, (DWORD)szFileName);

	// Tls
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[9].VirtualAddress);
	SendDlgItemMessage(hDlg, IDC_CATALOGUE_C19, WM_SETTEXT, 0, (DWORD)szFileName);
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[9].Size);
	SendDlgItemMessage(hDlg, IDC_CATALOGUE_C20, WM_SETTEXT, 0, (DWORD)szFileName);

	// 导入配置
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[10].VirtualAddress);
	SendDlgItemMessage(hDlg, IDC_CATALOGUE_C21, WM_SETTEXT, 0, (DWORD)szFileName);
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[10].Size);
	SendDlgItemMessage(hDlg, IDC_CATALOGUE_C22, WM_SETTEXT, 0, (DWORD)szFileName);

	// 绑定导入
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[11].VirtualAddress);
	SendDlgItemMessage(hDlg, IDC_CATALOGUE_C23, WM_SETTEXT, 0, (DWORD)szFileName);
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[11].Size);
	SendDlgItemMessage(hDlg, IDC_CATALOGUE_C24, WM_SETTEXT, 0, (DWORD)szFileName);

	// IAT
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[12].VirtualAddress);
	SendDlgItemMessage(hDlg, IDC_CATALOGUE_C25, WM_SETTEXT, 0, (DWORD)szFileName);
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[12].Size);
	SendDlgItemMessage(hDlg, IDC_CATALOGUE_C26, WM_SETTEXT, 0, (DWORD)szFileName);

	// 延迟导入
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[13].VirtualAddress);
	SendDlgItemMessage(hDlg, IDC_CATALOGUE_C27, WM_SETTEXT, 0, (DWORD)szFileName);
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[13].Size);
	SendDlgItemMessage(hDlg, IDC_CATALOGUE_C28, WM_SETTEXT, 0, (DWORD)szFileName);

	// COM
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[14].VirtualAddress);
	SendDlgItemMessage(hDlg, IDC_CATALOGUE_C29, WM_SETTEXT, 0, (DWORD)szFileName);
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[14].Size);
	SendDlgItemMessage(hDlg, IDC_CATALOGUE_C30, WM_SETTEXT, 0, (DWORD)szFileName);

	// 保留
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[15].VirtualAddress);
	SendDlgItemMessage(hDlg, IDC_CATALOGUE_C31, WM_SETTEXT, 0, (DWORD)szFileName);
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[15].Size);
	SendDlgItemMessage(hDlg, IDC_CATALOGUE_C32, WM_SETTEXT, 0, (DWORD)szFileName);
}

