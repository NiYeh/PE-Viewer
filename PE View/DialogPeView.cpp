#define _CRT_SECURE_NO_WARNINGS 1
#include "Stdafx.h"
#include "DialogPeView.h"

VOID InitPeView(HWND hwndDlg, LPSTR lpszFile)
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
		return;
	}

	pDosHeader = (PIMAGE_DOS_HEADER)pFileBuffer;
	pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pFileBuffer + pDosHeader->e_lfanew);
	pPEHeader = (PIMAGE_FILE_HEADER)(((DWORD)pNTHeader) + 4);
	pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader + IMAGE_SIZEOF_FILE_HEADER);

	// ��ڵ�
	sprintf(szFileName, "%x", pOptionHeader->AddressOfEntryPoint);
	SendDlgItemMessage(hwndDlg, IDC_PEVIEW_EDIT1, WM_SETTEXT, 0, (DWORD)szFileName);

	// �����ַ
	sprintf(szFileName, "%x", pOptionHeader->ImageBase);
	SendDlgItemMessage(hwndDlg, IDC_PEVIEW_EDIT2, WM_SETTEXT, 0, (DWORD)szFileName);

	// �����С
	sprintf(szFileName, "%x", pOptionHeader->SizeOfImage);
	SendDlgItemMessage(hwndDlg, IDC_PEVIEW_EDIT3, WM_SETTEXT, 0, (DWORD)szFileName);

	// �����ַ
	sprintf(szFileName, "%x", pOptionHeader->BaseOfCode);
	SendDlgItemMessage(hwndDlg, IDC_PEVIEW_EDIT4, WM_SETTEXT, 0, (DWORD)szFileName);

	// ���ݻ�ַ
	sprintf(szFileName, "%x", pOptionHeader->BaseOfData);
	SendDlgItemMessage(hwndDlg, IDC_PEVIEW_EDIT5, WM_SETTEXT, 0, (DWORD)szFileName);

	// �ڴ����
	sprintf(szFileName, "%x", pOptionHeader->SectionAlignment);
	SendDlgItemMessage(hwndDlg, IDC_PEVIEW_EDIT6, WM_SETTEXT, 0, (DWORD)szFileName);

	// �ļ�����
	sprintf(szFileName, "%x", pOptionHeader->FileAlignment);
	SendDlgItemMessage(hwndDlg, IDC_PEVIEW_EDIT7, WM_SETTEXT, 0, (DWORD)szFileName);

	// ��־��
	sprintf(szFileName, "%x", pOptionHeader->Magic);
	SendDlgItemMessage(hwndDlg, IDC_PEVIEW_EDIT8, WM_SETTEXT, 0, (DWORD)szFileName);

	// ��ϵͳ
	sprintf(szFileName, "%x", pOptionHeader->Subsystem);
	SendDlgItemMessage(hwndDlg, IDC_PEVIEW_EDIT9, WM_SETTEXT, 0, (DWORD)szFileName);

	// ������Ŀ
	sprintf(szFileName, "%x", pPEHeader->NumberOfSections);
	SendDlgItemMessage(hwndDlg, IDC_PEVIEW_EDIT10, WM_SETTEXT, 0, (DWORD)szFileName);

	// ʱ���
	sprintf(szFileName, "%x", pPEHeader->TimeDateStamp);
	SendDlgItemMessage(hwndDlg, IDC_PEVIEW_EDIT11, WM_SETTEXT, 0, (DWORD)szFileName);

	// PEͷ��С
	sprintf(szFileName, "%x", pOptionHeader->SizeOfHeaders);
	SendDlgItemMessage(hwndDlg, IDC_PEVIEW_EDIT12, WM_SETTEXT, 0, (DWORD)szFileName);

	// ����ֵ
	sprintf(szFileName, "%x", pPEHeader->Characteristics);
	SendDlgItemMessage(hwndDlg, IDC_PEVIEW_EDIT13, WM_SETTEXT, 0, (DWORD)szFileName);

	// У���
	sprintf(szFileName, "%x", pOptionHeader->CheckSum);
	SendDlgItemMessage(hwndDlg, IDC_PEVIEW_EDIT14, WM_SETTEXT, 0, (DWORD)szFileName);

	// ��ѡPEͷ
	sprintf(szFileName, "%x", pPEHeader->SizeOfOptionalHeader);
	SendDlgItemMessage(hwndDlg, IDC_PEVIEW_EDIT15, WM_SETTEXT, 0, (DWORD)szFileName);

	// Ŀ¼����Ŀ
	sprintf(szFileName, "%x", pOptionHeader->NumberOfRvaAndSizes);
	SendDlgItemMessage(hwndDlg, IDC_PEVIEW_EDIT16, WM_SETTEXT, 0, (DWORD)szFileName);
}