// ImportTable.cpp: implementation of the ImportTable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ImportTable.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

VOID InitImportListView(HWND hDlg, LPSTR lpszFile)
{
	LV_COLUMN lv;								
	HWND hListProcess;
									
	//初始化								
	memset(&lv,0,sizeof(LV_COLUMN));								
	//获取IDC_LIST_PROCESS句柄								
	hListProcess = GetDlgItem(hDlg, IDC_LIST_IMPORTLIST1);								
	//设置整行选中								
	SendMessage(hListProcess,LVM_SETEXTENDEDLISTVIEWSTYLE,LVS_EX_FULLROWSELECT,LVS_EX_FULLROWSELECT);								
									
	//第一列								
	lv.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;								
	lv.pszText = TEXT("Dll名称");			//列标题				
	lv.cx = 75;								//列宽
	lv.iSubItem = 0;								
	//ListView_InsertColumn(hListProcess, 0, &lv);								
	SendMessage(hListProcess,LVM_INSERTCOLUMN,0,(DWORD)&lv);	
	
	//第二列								
	lv.pszText = TEXT("OriginalFirstThunk");								
	lv.cx = 150;								
	lv.iSubItem = 1;								
	//ListView_InsertColumn(hListProcess, 1, &lv);								
	SendMessage(hListProcess,LVM_INSERTCOLUMN,1,(DWORD)&lv);
	
	//第三列								
	lv.pszText = TEXT("TimeDateStamp");								
	lv.cx = 125;								
	lv.iSubItem = 2;								
	ListView_InsertColumn(hListProcess, 2, &lv);
	
	//第四列								
	lv.pszText = TEXT("ForwarderChain");								
	lv.cx = 125;								
	lv.iSubItem = 3;								
	ListView_InsertColumn(hListProcess, 3, &lv);

	//第五列								
	lv.pszText = TEXT("Name");								
	lv.cx = 50;								
	lv.iSubItem = 3;								
	ListView_InsertColumn(hListProcess, 4, &lv);

	//第六列								
	lv.pszText = TEXT("FirstThunk");								
	lv.cx = 100;								
	lv.iSubItem = 3;								
	ListView_InsertColumn(hListProcess, 5, &lv);

	EnumImport(hDlg, hListProcess, lpszFile);
}

VOID InitImportModuleListView(HWND hDlg, LPSTR lpszFile)
{
	LV_COLUMN lv;								
	HWND hListProcess;
	
	//初始化								
	memset(&lv,0,sizeof(LV_COLUMN));								
	//获取IDC_LIST_PROCESS句柄								
	hListProcess = GetDlgItem(hDlg,IDC_LIST_IMPORTLIST2);								
	//设置整行选中								
	SendMessage(hListProcess,LVM_SETEXTENDEDLISTVIEWSTYLE,LVS_EX_FULLROWSELECT,LVS_EX_FULLROWSELECT);

	//第一列								
	lv.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;								
	lv.pszText = TEXT("ThunkRVA");				//列标题				
	lv.cx = 125;								//列宽
	lv.iSubItem = 0;															
	SendMessage(hListProcess,LVM_INSERTCOLUMN,0,(DWORD)&lv);

	//第二列								
	lv.pszText = TEXT("ThunkOffset");								
	lv.cx = 125;								
	lv.iSubItem = 1;															
	ListView_InsertColumn(hListProcess, 1, &lv);

	//第三列								
	lv.pszText = TEXT("ThunkValue");								
	lv.cx = 125;								
	lv.iSubItem = 2;												
	ListView_InsertColumn(hListProcess, 2, &lv);

	//第四列								
	lv.pszText = TEXT("Hint");								
	lv.cx = 50;								
	lv.iSubItem = 3;												
	ListView_InsertColumn(hListProcess, 3, &lv);

	//第五列								
	lv.pszText = TEXT("ApiName");								
	lv.cx = 100;								
	lv.iSubItem = 4;													
	ListView_InsertColumn(hListProcess, 4, &lv);
}


VOID EnumImport(HWND hwndDlg, HWND hListProcess, LPSTR lpszFile)
{
	PIMAGE_DOS_HEADER pDosHeader = NULL;
	PIMAGE_NT_HEADERS pNTHeader = NULL;
	PIMAGE_FILE_HEADER pPEHeader = NULL;
	PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
	PIMAGE_SECTION_HEADER pSectionHeader = NULL;
	PIMAGE_DATA_DIRECTORY DataDirectory = NULL;
	PIMAGE_EXPORT_DIRECTORY ExportTable = NULL;

	LPVOID pFileBuffer = NULL;
	DWORD fileSize = 0;

	PIMAGE_IMPORT_DESCRIPTOR ImportTable = NULL;
	PIMAGE_IMPORT_BY_NAME ImportByNameTable = NULL;

	DWORD EntryImportTableRVA = 0;
	DWORD EntryImportTableFOA = 0;

	DWORD DLLNameFOA = 0;
	PDWORD DLLNameAddr = NULL;

	DWORD IBNameFOA = 0; // IMPORT_BY_NAME
	PBYTE pStr = NULL;

	LV_ITEM vitem;
	TCHAR szBuffer[MAX_PATH];
	DWORD count = 0;
							
	//初始化				
	memset(szBuffer, 0, MAX_PATH);

	memset(&vitem,0,sizeof(LV_ITEM));						
	vitem.mask = LVIF_TEXT;	

	// File --> FileBuffer
	fileSize = ReadPEFile(lpszFile, &pFileBuffer);
	if (!pFileBuffer)
	{
		MessageBox(0, TEXT("文件-->缓冲区失败!"), TEXT("Window"), 0);
		return;
	}

	pDosHeader = (PIMAGE_DOS_HEADER)pFileBuffer;
	pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pFileBuffer + pDosHeader->e_lfanew);
	pPEHeader = (PIMAGE_FILE_HEADER)(((DWORD)pNTHeader) + 4);
	pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader + IMAGE_SIZEOF_FILE_HEADER);

	if (!(pOptionHeader->DataDirectory[1].VirtualAddress))
	{
		MessageBox(0, TEXT("此文件没有导入表!"), TEXT("Window"), 0);
		EndDialog(hwndDlg, 0);

		return;
	}

	// 导入表
	EntryImportTableRVA = pOptionHeader->DataDirectory[1].VirtualAddress;
	EntryImportTableFOA = RvaToFileOffset(pFileBuffer, EntryImportTableRVA);
	ImportTable = (PIMAGE_IMPORT_DESCRIPTOR)((DWORD)EntryImportTableFOA + (DWORD)pFileBuffer);

	while (1)
	{
		if (ImportTable->Name == 0)
		{
			count = 0;
			break;
		}

		// 打印dll名称
		DLLNameFOA = RvaToFileOffset(pFileBuffer, ImportTable->Name);
		DLLNameAddr = (PDWORD)((DWORD)pFileBuffer + DLLNameFOA);

		sprintf(szBuffer, "%s", DLLNameAddr);
		vitem.pszText = szBuffer;						
		vitem.iItem = count;						
		vitem.iSubItem = 0;												
		SendMessage(hListProcess, LVM_INSERTITEM, 0, (DWORD)&vitem);

		memset(szBuffer, 0, MAX_PATH);

		sprintf(szBuffer, "%x", ImportTable->OriginalFirstThunk);
		vitem.pszText = szBuffer;						
		vitem.iItem = count;						
		vitem.iSubItem = 1;												
		ListView_SetItem(hListProcess, &vitem);

		memset(szBuffer, 0, MAX_PATH);

		sprintf(szBuffer, "%x", ImportTable->TimeDateStamp);
		vitem.pszText = szBuffer;						
		vitem.iItem = count;						
		vitem.iSubItem = 2;												
		ListView_SetItem(hListProcess, &vitem);

		memset(szBuffer, 0, MAX_PATH);

		sprintf(szBuffer, "%x", ImportTable->ForwarderChain);
		vitem.pszText = szBuffer;						
		vitem.iItem = count;						
		vitem.iSubItem = 3;												
		ListView_SetItem(hListProcess, &vitem);

		memset(szBuffer, 0, MAX_PATH);

		sprintf(szBuffer, "%x", ImportTable->Name);
		vitem.pszText = szBuffer;						
		vitem.iItem = count;						
		vitem.iSubItem = 4;												
		ListView_SetItem(hListProcess, &vitem);

		memset(szBuffer, 0, MAX_PATH);

		sprintf(szBuffer, "%x", ImportTable->FirstThunk);
		vitem.pszText = szBuffer;						
		vitem.iItem = count;						
		vitem.iSubItem = 5;												
		ListView_SetItem(hListProcess, &vitem);

		ImportTable++;
		count++;
		memset(szBuffer, 0, MAX_PATH);
	}
}


VOID EnumImportModule(HWND hListModules, HWND hListImport, WPARAM wParam, LPARAM lParam, LPSTR lpszFile)
{
	PIMAGE_DOS_HEADER pDosHeader = NULL;
	PIMAGE_NT_HEADERS pNTHeader = NULL;
	PIMAGE_FILE_HEADER pPEHeader = NULL;
	PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
	PIMAGE_SECTION_HEADER pSectionHeader = NULL;
	PIMAGE_DATA_DIRECTORY DataDirectory = NULL;
	PIMAGE_EXPORT_DIRECTORY ExportTable = NULL;

	LPVOID pFileBuffer = NULL;
	DWORD fileSize = 0;

	PIMAGE_IMPORT_DESCRIPTOR ImportTable = NULL;
	PIMAGE_IMPORT_BY_NAME ImportByNameTable = NULL;

	DWORD EntryImportTableRVA = 0;
	DWORD EntryImportTableFOA = 0;

	DWORD DLLNameFOA = 0;
	PDWORD DLLNameAddr = NULL;

	PDWORD OFThunkRVA = 0;
	PDWORD OFThunkFOA = 0; // OriginalFirstThunk

	PDWORD OriginalFirstThunk = NULL;

	DWORD IBNameFOA = 0; // IMPORT_BY_NAME
	PBYTE pStr = NULL;

	DWORD count = 0;
	DWORD dwRowId;
	TCHAR szBuffer[MAX_PATH];
	LV_ITEM lv;
	LV_ITEM vitem;

	SendMessage(hListModules, LVM_DELETEALLITEMS,  0,  0);

	//初始化								
	memset(&vitem,0,sizeof(LV_ITEM));						
	vitem.mask = LVIF_TEXT;
	//初始化								
	memset(&lv,0,sizeof(LV_ITEM));
	//初始化				
	memset(szBuffer, 0, MAX_PATH);

	// 获取选择行
	dwRowId = SendMessage(hListImport, LVM_GETNEXTITEM, -1, LVNI_SELECTED);
	if (dwRowId == -1)
	{
		MessageBox(NULL, TEXT("清选择DLL模块!"), TEXT("windows"), MB_OK);
		return ;
	}

	// 获取DLL名称
	lv.iSubItem = 0;
	lv.pszText = szBuffer;
	lv.cchTextMax = 0x20;
	SendMessage(hListImport, LVM_GETITEMTEXT, dwRowId, (DWORD)&lv);

	// File --> FileBuffer
	fileSize = ReadPEFile(lpszFile, &pFileBuffer);
	if (!pFileBuffer)
	{
		MessageBox(0, TEXT("文件-->缓冲区失败!"), TEXT("Window"), 0);
		return;
	}

	pDosHeader = (PIMAGE_DOS_HEADER)pFileBuffer;
	pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pFileBuffer + pDosHeader->e_lfanew);
	pPEHeader = (PIMAGE_FILE_HEADER)(((DWORD)pNTHeader) + 4);
	pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader + IMAGE_SIZEOF_FILE_HEADER);

	if (!(pOptionHeader->DataDirectory[1].VirtualAddress))
	{
		MessageBox(0, TEXT("此文件没有导入表!"), TEXT("Window"), 0);

		return;
	}

	// 导入表
	EntryImportTableRVA = pOptionHeader->DataDirectory[1].VirtualAddress;
	EntryImportTableFOA = RvaToFileOffset(pFileBuffer, EntryImportTableRVA);
	ImportTable = (PIMAGE_IMPORT_DESCRIPTOR)((DWORD)EntryImportTableFOA + (DWORD)pFileBuffer);

	while (1)
	{
		if (ImportTable->Name == 0)
		{
			break;
		}

		// 打印dll名称
		DLLNameFOA = RvaToFileOffset(pFileBuffer, ImportTable->Name);
		DLLNameAddr = (PDWORD)((DWORD)pFileBuffer + DLLNameFOA);

		TCHAR DllName[256] = {0};
		sprintf(DllName, "%s", DLLNameAddr);

		if (!strcmp(szBuffer, DllName))
		{
			OFThunkRVA = (PDWORD)ImportTable->OriginalFirstThunk;
			OFThunkFOA = (PDWORD)RvaToFileOffset(pFileBuffer, ImportTable->OriginalFirstThunk);
			OriginalFirstThunk = (PDWORD)((DWORD)pFileBuffer + (DWORD)OFThunkFOA);

			while (1)
			{
				if (*OriginalFirstThunk == 0)
				{
					count = 0;
					break;
				}

				TCHAR sztBuffer[256] = {0};
				sprintf(sztBuffer, "%x", OFThunkRVA);

				vitem.pszText = sztBuffer;
				vitem.iItem = count;
				vitem.iSubItem = 0;
				SendMessage(hListModules, LVM_INSERTITEM, 0, (DWORD)&vitem);

				sprintf(sztBuffer, "%x", OFThunkFOA);

				vitem.pszText = sztBuffer;
				vitem.iItem = count;
				vitem.iSubItem = 1;
				ListView_SetItem(hListModules, &vitem);

				sprintf(sztBuffer, "%x", *OriginalFirstThunk);

				vitem.pszText = sztBuffer;
				vitem.iItem = count;
				vitem.iSubItem = 2;
				ListView_SetItem(hListModules, &vitem);

				if (*OriginalFirstThunk & IMAGE_ORDINAL_FLAG32) // IMAGE_ORDINAL_FLAG32 0x80000000
				{
					TCHAR sztBuffer[256] = {0};

					sprintf(sztBuffer, "-");

					vitem.pszText = sztBuffer;
					vitem.iItem = count;
					vitem.iSubItem = 3;
					ListView_SetItem(hListModules, &vitem);

					sprintf(sztBuffer, "序号导入：%xh %dd", *OriginalFirstThunk & 0x7FFFFFFF, *OriginalFirstThunk & 0x7FFFFFFF);

					vitem.pszText = sztBuffer;
					vitem.iItem = count;
					vitem.iSubItem = 4;
					ListView_SetItem(hListModules, &vitem);
				}
				else // 用名字导入
				{
					IBNameFOA = RvaToFileOffset(pFileBuffer, *OriginalFirstThunk);
					ImportByNameTable = (PIMAGE_IMPORT_BY_NAME)((DWORD)IBNameFOA + (DWORD)pFileBuffer);
					pStr = (PBYTE)ImportByNameTable->Name;

					TCHAR sztBuffer[256] = {0};

					sprintf(sztBuffer, "%x", ImportByNameTable->Hint);

					vitem.pszText = sztBuffer;
					vitem.iItem = count;
					vitem.iSubItem = 3;
					ListView_SetItem(hListModules, &vitem);

					sprintf(sztBuffer, "%s", pStr);

					vitem.pszText = sztBuffer;
					vitem.iItem = count;
					vitem.iSubItem = 4;
					ListView_SetItem(hListModules, &vitem);

					pStr = NULL;
				}
				*(OriginalFirstThunk++);
				OFThunkFOA++;
				OFThunkRVA++;
				count++;
			}
		}

		ImportTable++;
	}
}




