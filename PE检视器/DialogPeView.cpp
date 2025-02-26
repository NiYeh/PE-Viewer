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
		MessageBox(0, TEXT("�ļ�-->������ʧ��!"), TEXT("Window"), 0);
		return ;
	}

	pDosHeader = (PIMAGE_DOS_HEADER)pFileBuffer;
	pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pFileBuffer+pDosHeader->e_lfanew);
	pPEHeader = (PIMAGE_FILE_HEADER)(((DWORD)pNTHeader) + 4);		
	pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader+IMAGE_SIZEOF_FILE_HEADER);

	// ��ڵ�
	sprintf(szFileName, "%x", pOptionHeader->AddressOfEntryPoint);
	SendDlgItemMessage(hDlg, IDC_PEVIEW_P1, WM_SETTEXT, 0, (DWORD)szFileName);

	// �����ַ
	sprintf(szFileName, "%x", pOptionHeader->ImageBase);
	SendDlgItemMessage(hDlg, IDC_PEVIEW_P2, WM_SETTEXT, 0, (DWORD)szFileName);

	// �����С
	sprintf(szFileName, "%x", pOptionHeader->SizeOfImage);
	SendDlgItemMessage(hDlg, IDC_PEVIEW_P3, WM_SETTEXT, 0, (DWORD)szFileName);

	// �����ַ
	sprintf(szFileName, "%x", pOptionHeader->BaseOfCode);
	SendDlgItemMessage(hDlg, IDC_PEVIEW_P4, WM_SETTEXT, 0, (DWORD)szFileName);

	// ���ݻ�ַ
	sprintf(szFileName, "%x", pOptionHeader->BaseOfData);
	SendDlgItemMessage(hDlg, IDC_PEVIEW_P5, WM_SETTEXT, 0, (DWORD)szFileName);

	// �ڴ����
	sprintf(szFileName, "%x", pOptionHeader->SectionAlignment);
	SendDlgItemMessage(hDlg, IDC_PEVIEW_P6, WM_SETTEXT, 0, (DWORD)szFileName);

	// �ļ�����
	sprintf(szFileName, "%x", pOptionHeader->FileAlignment);
	SendDlgItemMessage(hDlg, IDC_PEVIEW_P7, WM_SETTEXT, 0, (DWORD)szFileName);

	// ��־��
	sprintf(szFileName, "%x", pOptionHeader->Magic);
	SendDlgItemMessage(hDlg, IDC_PEVIEW_P8, WM_SETTEXT, 0, (DWORD)szFileName);

	// ��ϵͳ
	sprintf(szFileName, "%x", pOptionHeader->Subsystem);
	SendDlgItemMessage(hDlg, IDC_PEVIEW_P9, WM_SETTEXT, 0, (DWORD)szFileName);

	// ������Ŀ
	sprintf(szFileName, "%x", pPEHeader->NumberOfSections);
	SendDlgItemMessage(hDlg, IDC_PEVIEW_P10, WM_SETTEXT, 0, (DWORD)szFileName);

	// ʱ���
	sprintf(szFileName, "%x", pPEHeader->TimeDateStamp);
	SendDlgItemMessage(hDlg, IDC_PEVIEW_P11, WM_SETTEXT, 0, (DWORD)szFileName);

	// PEͷ��С
	sprintf(szFileName, "%x", pOptionHeader->SizeOfHeaders);
	SendDlgItemMessage(hDlg, IDC_PEVIEW_P12, WM_SETTEXT, 0, (DWORD)szFileName);

	// ����ֵ
	sprintf(szFileName, "%x", pPEHeader->Characteristics);
	SendDlgItemMessage(hDlg, IDC_PEVIEW_P13, WM_SETTEXT, 0, (DWORD)szFileName);

	// У���
	sprintf(szFileName, "%x", pOptionHeader->CheckSum);
	SendDlgItemMessage(hDlg, IDC_PEVIEW_P14, WM_SETTEXT, 0, (DWORD)szFileName);

	// ��ѡPEͷ
	sprintf(szFileName, "%x", pPEHeader->SizeOfOptionalHeader);
	SendDlgItemMessage(hDlg, IDC_PEVIEW_P15, WM_SETTEXT, 0, (DWORD)szFileName);

	// Ŀ¼����Ŀ
	sprintf(szFileName, "%x", pOptionHeader->NumberOfRvaAndSizes);
	SendDlgItemMessage(hDlg, IDC_PEVIEW_P16, WM_SETTEXT, 0, (DWORD)szFileName);
}