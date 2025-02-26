// DialogPeView.cpp: implementation of the DialogPeView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DialogPeView.h"

VOID InitPeView(HWND hDlg, LPSTR lpszFile)
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

	// 入口点
	sprintf(szFileName, "%x", pOptionHeader->AddressOfEntryPoint);
	SendDlgItemMessage(hDlg, IDC_PEVIEW_P1, WM_SETTEXT, 0, (DWORD)szFileName);

	// 镜像地址
	sprintf(szFileName, "%x", pOptionHeader->ImageBase);
	SendDlgItemMessage(hDlg, IDC_PEVIEW_P2, WM_SETTEXT, 0, (DWORD)szFileName);

	// 镜像大小
	sprintf(szFileName, "%x", pOptionHeader->SizeOfImage);
	SendDlgItemMessage(hDlg, IDC_PEVIEW_P3, WM_SETTEXT, 0, (DWORD)szFileName);

	// 代码基址
	sprintf(szFileName, "%x", pOptionHeader->BaseOfCode);
	SendDlgItemMessage(hDlg, IDC_PEVIEW_P4, WM_SETTEXT, 0, (DWORD)szFileName);

	// 数据基址
	sprintf(szFileName, "%x", pOptionHeader->BaseOfData);
	SendDlgItemMessage(hDlg, IDC_PEVIEW_P5, WM_SETTEXT, 0, (DWORD)szFileName);

	// 内存对齐
	sprintf(szFileName, "%x", pOptionHeader->SectionAlignment);
	SendDlgItemMessage(hDlg, IDC_PEVIEW_P6, WM_SETTEXT, 0, (DWORD)szFileName);

	// 文件对齐
	sprintf(szFileName, "%x", pOptionHeader->FileAlignment);
	SendDlgItemMessage(hDlg, IDC_PEVIEW_P7, WM_SETTEXT, 0, (DWORD)szFileName);

	// 标志字
	sprintf(szFileName, "%x", pOptionHeader->Magic);
	SendDlgItemMessage(hDlg, IDC_PEVIEW_P8, WM_SETTEXT, 0, (DWORD)szFileName);

	// 子系统
	sprintf(szFileName, "%x", pOptionHeader->Subsystem);
	SendDlgItemMessage(hDlg, IDC_PEVIEW_P9, WM_SETTEXT, 0, (DWORD)szFileName);

	// 区段数目
	sprintf(szFileName, "%x", pPEHeader->NumberOfSections);
	SendDlgItemMessage(hDlg, IDC_PEVIEW_P10, WM_SETTEXT, 0, (DWORD)szFileName);

	// 时间戳
	sprintf(szFileName, "%x", pPEHeader->TimeDateStamp);
	SendDlgItemMessage(hDlg, IDC_PEVIEW_P11, WM_SETTEXT, 0, (DWORD)szFileName);

	// PE头大小
	sprintf(szFileName, "%x", pOptionHeader->SizeOfHeaders);
	SendDlgItemMessage(hDlg, IDC_PEVIEW_P12, WM_SETTEXT, 0, (DWORD)szFileName);

	// 特征值
	sprintf(szFileName, "%x", pPEHeader->Characteristics);
	SendDlgItemMessage(hDlg, IDC_PEVIEW_P13, WM_SETTEXT, 0, (DWORD)szFileName);

	// 校验和
	sprintf(szFileName, "%x", pOptionHeader->CheckSum);
	SendDlgItemMessage(hDlg, IDC_PEVIEW_P14, WM_SETTEXT, 0, (DWORD)szFileName);

	// 可选PE头
	sprintf(szFileName, "%x", pPEHeader->SizeOfOptionalHeader);
	SendDlgItemMessage(hDlg, IDC_PEVIEW_P15, WM_SETTEXT, 0, (DWORD)szFileName);

	// 目录项数目
	sprintf(szFileName, "%x", pOptionHeader->NumberOfRvaAndSizes);
	SendDlgItemMessage(hDlg, IDC_PEVIEW_P16, WM_SETTEXT, 0, (DWORD)szFileName);
}