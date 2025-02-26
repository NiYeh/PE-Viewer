// DialogSection.cpp: implementation of the DialogSection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DialogSection.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

VOID InitSectionListView(HWND hDlg, LPSTR lpszFile)
{
	LV_COLUMN lv;								
	HWND hListSection;								
									
	//初始化								
	memset(&lv,0,sizeof(LV_COLUMN));								
	//获取IDC_LIST_SECTION句柄								
	hListSection = GetDlgItem(hDlg,IDC_LIST_SECTION);								
	//设置整行选中								
	SendMessage(hListSection,LVM_SETEXTENDEDLISTVIEWSTYLE,LVS_EX_FULLROWSELECT,LVS_EX_FULLROWSELECT);								
									
	// 节名								
	lv.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;								
	lv.pszText = TEXT("节名");				//列标题				
	lv.cx = 80;								//列宽
	lv.iSubItem = 0;								
	//ListView_InsertColumn(hListProcess, 0, &lv);								
	SendMessage(hListSection,LVM_INSERTCOLUMN,0,(DWORD)&lv);
	
	// 文件偏移
	lv.pszText = TEXT("文件偏移");								
	lv.cx = 120;								
	lv.iSubItem = 1;								
	//ListView_InsertColumn(hListProcess, 1, &lv);								
	SendMessage(hListSection,LVM_INSERTCOLUMN,1,(DWORD)&lv);
	
	// 文件大小
	lv.pszText = TEXT("文件大小");								
	lv.cx = 120;								
	lv.iSubItem = 2;								
	ListView_InsertColumn(hListSection, 2, &lv);
	
	// 内存偏移
	lv.pszText = TEXT("内存偏移");								
	lv.cx = 120;								
	lv.iSubItem = 3;								
	ListView_InsertColumn(hListSection, 3, &lv);		
	
	// 内存大小
	lv.pszText = TEXT("内存大小");								
	lv.cx = 120;								
	lv.iSubItem = 4;								
	ListView_InsertColumn(hListSection, 3, &lv);	

	// 节区属性
	lv.pszText = TEXT("节区属性");								
	lv.cx = 120;								
	lv.iSubItem = 5;								
	ListView_InsertColumn(hListSection, 3, &lv);	

	EnumSection(hListSection, lpszFile);
}

VOID EnumSection(HWND hListSection, LPSTR lpszFile)
{
	PIMAGE_DOS_HEADER pDosHeader = NULL;	
	PIMAGE_NT_HEADERS pNTHeader = NULL;	
	PIMAGE_FILE_HEADER pPEHeader = NULL;	
	PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
	PIMAGE_SECTION_HEADER pSectionHeader = NULL;

	LPVOID pFileBuffer = NULL;
	DWORD fileSize = 0;

	DWORD SecNum = 0;

	LV_ITEM vitem;
	
	TCHAR szFileName[256];
	memset(szFileName, 0, 256);
							
	//初始化						
	memset(&vitem,0,sizeof(LV_ITEM));						
	vitem.mask = LVIF_TEXT;

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
	pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pPEHeader+IMAGE_SIZEOF_FILE_HEADER+pPEHeader->SizeOfOptionalHeader);

	SecNum = pPEHeader->NumberOfSections;

	for (int i=0; i<SecNum; i++, pSectionHeader++)
	{
		vitem.pszText = (char*)pSectionHeader->Name;						
		vitem.iItem = i;						
		vitem.iSubItem = 0;
		SendMessage(hListSection, LVM_INSERTITEM,0,(DWORD)&vitem);
		
		sprintf(szFileName, "%x", pSectionHeader->PointerToRawData);
		vitem.pszText = szFileName;
		vitem.iItem = i;						
		vitem.iSubItem = 1;
		ListView_SetItem(hListSection, &vitem);

		sprintf(szFileName, "%x", pSectionHeader->SizeOfRawData);
		vitem.pszText = szFileName;						
		vitem.iItem = i;						
		vitem.iSubItem = 2;
		ListView_SetItem(hListSection, &vitem);

		sprintf(szFileName, "%x", pSectionHeader->VirtualAddress);
		vitem.pszText = szFileName;
		vitem.iItem = i;						
		vitem.iSubItem = 3;
		ListView_SetItem(hListSection, &vitem);

		sprintf(szFileName, "%x", pSectionHeader->Misc.VirtualSize);
		vitem.pszText = szFileName;
		vitem.iItem = i;						
		vitem.iSubItem = 4;
		ListView_SetItem(hListSection, &vitem);
	
		sprintf(szFileName, "%x", pSectionHeader->Characteristics);
		vitem.pszText = szFileName;
		vitem.iItem = i;						
		vitem.iSubItem = 5;
		ListView_SetItem(hListSection, &vitem);
	}
}