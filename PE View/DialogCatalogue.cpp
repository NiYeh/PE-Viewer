#include "DialogCatalogue.h"

VOID InitCatalogue(HWND hwndDlg, LPSTR lpszFile)
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
		return;
	}

	pDosHeader = (PIMAGE_DOS_HEADER)pFileBuffer;
	pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pFileBuffer + pDosHeader->e_lfanew);
	pPEHeader = (PIMAGE_FILE_HEADER)(((DWORD)pNTHeader) + 4);
	pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader + IMAGE_SIZEOF_FILE_HEADER);

	// 导出表
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[0].VirtualAddress);
	SendDlgItemMessage(hwndDlg, IDC_CATALOGUE_C1, WM_SETTEXT, 0, (DWORD)szFileName);
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[0].Size);
	SendDlgItemMessage(hwndDlg, IDC_CATALOGUE_C2, WM_SETTEXT, 0, (DWORD)szFileName);

	// 导入表
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[1].VirtualAddress);
	SendDlgItemMessage(hwndDlg, IDC_CATALOGUE_C3, WM_SETTEXT, 0, (DWORD)szFileName);
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[1].Size);
	SendDlgItemMessage(hwndDlg, IDC_CATALOGUE_C4, WM_SETTEXT, 0, (DWORD)szFileName);

	// 资源表
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[2].VirtualAddress);
	SendDlgItemMessage(hwndDlg, IDC_CATALOGUE_C5, WM_SETTEXT, 0, (DWORD)szFileName);
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[2].Size);
	SendDlgItemMessage(hwndDlg, IDC_CATALOGUE_C6, WM_SETTEXT, 0, (DWORD)szFileName);

	// 异常表
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[3].VirtualAddress);
	SendDlgItemMessage(hwndDlg, IDC_CATALOGUE_C7, WM_SETTEXT, 0, (DWORD)szFileName);
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[3].Size);
	SendDlgItemMessage(hwndDlg, IDC_CATALOGUE_C8, WM_SETTEXT, 0, (DWORD)szFileName);

	// 安全
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[4].VirtualAddress);
	SendDlgItemMessage(hwndDlg, IDC_CATALOGUE_C9, WM_SETTEXT, 0, (DWORD)szFileName);
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[4].Size);
	SendDlgItemMessage(hwndDlg, IDC_CATALOGUE_C10, WM_SETTEXT, 0, (DWORD)szFileName);

	// 重定位表
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[5].VirtualAddress);
	SendDlgItemMessage(hwndDlg, IDC_CATALOGUE_C11, WM_SETTEXT, 0, (DWORD)szFileName);
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[5].Size);
	SendDlgItemMessage(hwndDlg, IDC_CATALOGUE_C12, WM_SETTEXT, 0, (DWORD)szFileName);

	// 调试
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[6].VirtualAddress);
	SendDlgItemMessage(hwndDlg, IDC_CATALOGUE_C13, WM_SETTEXT, 0, (DWORD)szFileName);
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[6].Size);
	SendDlgItemMessage(hwndDlg, IDC_CATALOGUE_C14, WM_SETTEXT, 0, (DWORD)szFileName);

	// 版权
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[7].VirtualAddress);
	SendDlgItemMessage(hwndDlg, IDC_CATALOGUE_C15, WM_SETTEXT, 0, (DWORD)szFileName);
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[7].Size);
	SendDlgItemMessage(hwndDlg, IDC_CATALOGUE_C16, WM_SETTEXT, 0, (DWORD)szFileName);

	// 全局指针
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[8].VirtualAddress);
	SendDlgItemMessage(hwndDlg, IDC_CATALOGUE_C17, WM_SETTEXT, 0, (DWORD)szFileName);
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[8].Size);
	SendDlgItemMessage(hwndDlg, IDC_CATALOGUE_C18, WM_SETTEXT, 0, (DWORD)szFileName);

	// Tls
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[9].VirtualAddress);
	SendDlgItemMessage(hwndDlg, IDC_CATALOGUE_C19, WM_SETTEXT, 0, (DWORD)szFileName);
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[9].Size);
	SendDlgItemMessage(hwndDlg, IDC_CATALOGUE_C20, WM_SETTEXT, 0, (DWORD)szFileName);

	// 导入配置
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[10].VirtualAddress);
	SendDlgItemMessage(hwndDlg, IDC_CATALOGUE_C21, WM_SETTEXT, 0, (DWORD)szFileName);
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[10].Size);
	SendDlgItemMessage(hwndDlg, IDC_CATALOGUE_C22, WM_SETTEXT, 0, (DWORD)szFileName);

	// 绑定导入
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[11].VirtualAddress);
	SendDlgItemMessage(hwndDlg, IDC_CATALOGUE_C23, WM_SETTEXT, 0, (DWORD)szFileName);
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[11].Size);
	SendDlgItemMessage(hwndDlg, IDC_CATALOGUE_C24, WM_SETTEXT, 0, (DWORD)szFileName);

	// IAT
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[12].VirtualAddress);
	SendDlgItemMessage(hwndDlg, IDC_CATALOGUE_C25, WM_SETTEXT, 0, (DWORD)szFileName);
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[12].Size);
	SendDlgItemMessage(hwndDlg, IDC_CATALOGUE_C26, WM_SETTEXT, 0, (DWORD)szFileName);

	// 延迟导入
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[13].VirtualAddress);
	SendDlgItemMessage(hwndDlg, IDC_CATALOGUE_C27, WM_SETTEXT, 0, (DWORD)szFileName);
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[13].Size);
	SendDlgItemMessage(hwndDlg, IDC_CATALOGUE_C28, WM_SETTEXT, 0, (DWORD)szFileName);

	// COM
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[14].VirtualAddress);
	SendDlgItemMessage(hwndDlg, IDC_CATALOGUE_C29, WM_SETTEXT, 0, (DWORD)szFileName);
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[14].Size);
	SendDlgItemMessage(hwndDlg, IDC_CATALOGUE_C30, WM_SETTEXT, 0, (DWORD)szFileName);

	// 保留
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[15].VirtualAddress);
	SendDlgItemMessage(hwndDlg, IDC_CATALOGUE_C31, WM_SETTEXT, 0, (DWORD)szFileName);
	sprintf(szFileName, "%x", pOptionHeader->DataDirectory[15].Size);
	SendDlgItemMessage(hwndDlg, IDC_CATALOGUE_C32, WM_SETTEXT, 0, (DWORD)szFileName);
}

VOID InitExportTable(HWND hwndDlg, LPSTR lpszFile)
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

	DWORD ExportTableRVA = 0;
	DWORD ExportTableFOA = 0;

	DWORD AddressOfFunctionsFOA = 0;
	PDWORD FunctionsAddr = NULL;
	PDWORD Functions = NULL;

	DWORD AddressOfNamesFOA = 0;
	PDWORD FunNameAddr = NULL;
	PDWORD FunName = NULL;

	DWORD AddressOfNameOrdinalsFOA = 0;
	PWORD Ordinals = NULL;

	TCHAR szText[2048];
	memset(szText, 0, 2048);

	TCHAR szTempText[1024];
	memset(szTempText, 0, 1024);

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

	if (!(pOptionHeader->DataDirectory[0].VirtualAddress))
	{
		MessageBox(0, TEXT("此文件没有导出表!"), TEXT("Window"), 0);
		EndDialog(hwndDlg, 0);

		return;
	}

	ExportTableRVA = pOptionHeader->DataDirectory[0].VirtualAddress;
	ExportTableFOA = RvaToFileOffset(pFileBuffer, ExportTableRVA);

	// 导出表
	ExportTable = (PIMAGE_EXPORT_DIRECTORY)((DWORD)ExportTableFOA + (DWORD)pFileBuffer);

	// IDC_EXPORTTABLE
	sprintf(szTempText, "%s", "Offset to ExportTable = ");
	strcat(szText, szTempText);
	sprintf(szTempText, "%x\r\n", RvaToFileOffset(pFileBuffer, pOptionHeader->DataDirectory[0].VirtualAddress));
	strcat(szText, szTempText);

	sprintf(szTempText, "%s", "Characteristics = ");
	strcat(szText, szTempText);
	sprintf(szTempText, "%x\r\n", ExportTable->Characteristics);
	strcat(szText, szTempText);

	sprintf(szTempText, "%s", "Base = ");
	strcat(szText, szTempText);
	sprintf(szTempText, "%x\r\n", ExportTable->Base);
	strcat(szText, szTempText);

	sprintf(szTempText, "%s", "Name = ");
	strcat(szText, szTempText);
	sprintf(szTempText, "%x\r\n", ExportTable->Name);
	strcat(szText, szTempText);

	PBYTE t = (PBYTE)((DWORD)pFileBuffer + ExportTable->Name);
	sprintf(szTempText, "%s", "Name String = ");
	strcat(szText, szTempText);
	sprintf(szTempText, "%s\r\n", t);
	strcat(szText, szTempText);
	t = NULL;

	sprintf(szTempText, "%s", "NumberOfFunctions = ");
	strcat(szText, szTempText);
	sprintf(szTempText, "%x\r\n", ExportTable->NumberOfFunctions);
	strcat(szText, szTempText);

	sprintf(szTempText, "%s", "NumberOfNames = ");
	strcat(szText, szTempText);
	sprintf(szTempText, "%x\r\n", ExportTable->NumberOfNames);
	strcat(szText, szTempText);

	sprintf(szTempText, "%s", "AddressOfFunctions = ");
	strcat(szText, szTempText);
	sprintf(szTempText, "%x\r\n", ExportTable->AddressOfFunctions);
	strcat(szText, szTempText);

	sprintf(szTempText, "%s", "AddressOfNames = ");
	strcat(szText, szTempText);
	sprintf(szTempText, "%x\r\n", ExportTable->AddressOfNames);
	strcat(szText, szTempText);

	sprintf(szTempText, "%s", "AddressOfNameOrdinals = ");
	strcat(szText, szTempText);
	sprintf(szTempText, "%x\r\n\r\n", ExportTable->AddressOfNameOrdinals);
	strcat(szText, szTempText);


	sprintf(szTempText, "%s\r\n", "***=========AddressOfFunctions=========***");
	strcat(szText, szTempText);

	ExportTableFOA = RvaToFileOffset(pFileBuffer, ExportTable->AddressOfFunctions);

	sprintf(szTempText, "%s", "AddressOfFunctions = ");
	strcat(szText, szTempText);
	sprintf(szTempText, "%x\r\n", ExportTableFOA);
	strcat(szText, szTempText);

	for (int i = 0; i < ExportTable->NumberOfFunctions; i++)
	{
		// 找到AddressOfFunctions的地址
		AddressOfFunctionsFOA = RvaToFileOffset(pFileBuffer, ExportTable->AddressOfFunctions + i * sizeof(DWORD));
		FunctionsAddr = (PDWORD)((DWORD)pFileBuffer + AddressOfFunctionsFOA);

		if (*FunctionsAddr != 0)
		{
			sprintf(szTempText, "%s", "ExportTable->AddressOfFunctions FunctionsAddr = ");
			strcat(szText, szTempText);
			sprintf(szTempText, "%x\r\n", *FunctionsAddr);
			strcat(szText, szTempText);
		}
	}


	sprintf(szTempText, "\r\n");
	strcat(szText, szTempText);


	sprintf(szTempText, "%s\r\n", "***=========AddressOfNames=========***");
	strcat(szText, szTempText);

	ExportTableFOA = RvaToFileOffset(pFileBuffer, ExportTable->AddressOfNames);
	sprintf(szTempText, "%s", "AddressOfNames = ");
	strcat(szText, szTempText);
	sprintf(szTempText, "%x\r\n", ExportTableFOA);
	strcat(szText, szTempText);

	for (int j = 0; j < ExportTable->NumberOfNames; j++)
	{
		// 找到AddressOfNames的地址
		AddressOfNamesFOA = RvaToFileOffset(pFileBuffer, ExportTable->AddressOfNames + j * sizeof(DWORD));
		FunNameAddr = (PDWORD)((DWORD)pFileBuffer + AddressOfNamesFOA);
		FunName = (PDWORD)((DWORD)pFileBuffer + *FunNameAddr);

		sprintf(szTempText, "%s", "ExportTable->AddressOfNames FunName = ");
		strcat(szText, szTempText);
		sprintf(szTempText, "%s\r\n", FunName);
		strcat(szText, szTempText);
	}


	sprintf(szTempText, "\r\n");
	strcat(szText, szTempText);


	sprintf(szTempText, "%s\r\n", "***=========AddressOfNameOrdinals=========***");
	strcat(szText, szTempText);

	ExportTableFOA = RvaToFileOffset(pFileBuffer, ExportTable->AddressOfNameOrdinals);
	sprintf(szTempText, "%s", "AddressOfNameOrdinals =");
	strcat(szText, szTempText);
	sprintf(szTempText, "%x\r\n", ExportTableFOA);
	strcat(szText, szTempText);

	for (int k = 0; k < ExportTable->NumberOfFunctions; k++)
	{
		// 找到AddressOfNameOrdinals的地址
		AddressOfNameOrdinalsFOA = RvaToFileOffset(pFileBuffer, ExportTable->AddressOfNameOrdinals + k * sizeof(WORD));
		Ordinals = (PWORD)((DWORD)pFileBuffer + AddressOfNameOrdinalsFOA);

		// 找到AddressOfFunctions的地址
		AddressOfFunctionsFOA = RvaToFileOffset(pFileBuffer, ExportTable->AddressOfFunctions + k * sizeof(DWORD));
		FunctionsAddr = (PDWORD)((DWORD)pFileBuffer + AddressOfFunctionsFOA);

		if (*FunctionsAddr != 0)
		{
			sprintf(szTempText, "%s", "ExportTable->AddressOfNameOrdinals Ordinals = ");
			strcat(szText, szTempText);
			sprintf(szTempText, "%x\r\n", k + ExportTable->Base);
			strcat(szText, szTempText);
		}
	}

	SendDlgItemMessage(hwndDlg, IDC_EXPORTTABLE, WM_SETTEXT, 0, (DWORD)szText);
}

VOID InitImportTable(HWND hwndDlg, LPSTR lpszFile)
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

	TCHAR szText[4096];
	memset(szText, 0, 4096);

	TCHAR szTempText[1024];
	memset(szTempText, 0, 1024);

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
			break;
		}

		// 打印dll名称
		DLLNameFOA = RvaToFileOffset(pFileBuffer, ImportTable->Name);
		DLLNameAddr = (PDWORD)((DWORD)pFileBuffer + DLLNameFOA);

		sprintf(szTempText, "%s\r\n", DLLNameAddr);
		strcat(szText, szTempText);

		ImportTable++;
	}

	SendDlgItemMessage(hwndDlg, IDC_IMPORTTABLE, WM_SETTEXT, 0, (DWORD)szText);
}

VOID InitResource(HWND hwndDlg, LPSTR lpszFile)
{
	PIMAGE_DOS_HEADER pDosHeader = NULL;
	PIMAGE_NT_HEADERS pNTHeader = NULL;
	PIMAGE_FILE_HEADER pPEHeader = NULL;
	PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
	PIMAGE_SECTION_HEADER pSectionHeader = NULL;
	PIMAGE_DATA_DIRECTORY DataDirectory = NULL;
	PIMAGE_EXPORT_DIRECTORY ExportTable = NULL;

	PIMAGE_RESOURCE_DIRECTORY pResDirectory = NULL;
	PIMAGE_RESOURCE_DIRECTORY_ENTRY pResDirEntry = NULL;
	PIMAGE_DATA_DIRECTORY pResDirData = NULL;

	LPVOID pFileBuffer = NULL;
	DWORD fileSize = 0;

	DWORD ResDirFOA = 0;

	DWORD TierNum_st = 0; // 第一层结构体数量
	DWORD TierNum_nd = 0; // 第二层结构体数量
	DWORD TierNum_rd = 0; // 第三层结构体数量

	TCHAR szText[4096];
	memset(szText, 0, 4096);

	TCHAR szTempText[1024];
	memset(szTempText, 0, 1024);

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

	if (!(pOptionHeader->DataDirectory[2].VirtualAddress))
	{
		MessageBox(0, TEXT("此文件没有资源表!"), TEXT("Window"), 0);
		EndDialog(hwndDlg, 0);

		return;
	}

	// 资源表
	ResDirFOA = RvaToFileOffset(pFileBuffer, pOptionHeader->DataDirectory[2].VirtualAddress);
	pResDirectory = (PIMAGE_RESOURCE_DIRECTORY)((DWORD)pFileBuffer + ResDirFOA);

	// 第一层结构体总数
	TierNum_st = pResDirectory->NumberOfIdEntries + pResDirectory->NumberOfNamedEntries;

	// 根目录
	pResDirEntry = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)((DWORD)pResDirectory + sizeof(IMAGE_RESOURCE_DIRECTORY));

	for (int i = 0; i < TierNum_st; i++)
	{
		if (!(pResDirEntry[i].Name & 0x80000000))
		{
			sprintf(szTempText, "%s", "图标类型:");
			strcat(szText, szTempText);

			sprintf(szTempText, "%d\r\n", pResDirEntry[i].Name);
			strcat(szText, szTempText);

			sprintf(szTempText, "%s\r\n", "-------------------------------------");
			strcat(szText, szTempText);
		}

		if ((pResDirEntry[i].OffsetToData & 0x80000000))
		{
			PIMAGE_RESOURCE_DIRECTORY pResDirectory_nd = NULL;			// 第二层资源目录
			PIMAGE_RESOURCE_DIRECTORY_ENTRY pResDirEntry_nd = NULL;		// 第二层资源目录项

			pResDirectory_nd = (PIMAGE_RESOURCE_DIRECTORY)((DWORD)pResDirectory + (pResDirEntry[i].OffsetToData & 0XFFFFFFF));
			pResDirEntry_nd = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)((DWORD)pResDirectory_nd + sizeof(IMAGE_RESOURCE_DIRECTORY));

			// 第二层结构体总数
			TierNum_nd = pResDirectory_nd->NumberOfIdEntries + pResDirectory_nd->NumberOfNamedEntries;

			for (int j = 0; j < TierNum_nd; j++)
			{
				if (!(pResDirEntry_nd[j].Name & 0x80000000))
				{
					sprintf(szTempText, "%s", "图标类型:");
					strcat(szText, szTempText);

					sprintf(szTempText, "%d\r\n", pResDirEntry_nd[j].Name);
					strcat(szText, szTempText);
				}

				if ((pResDirEntry_nd[j].OffsetToData & 0x80000000))
				{
					PIMAGE_RESOURCE_DIRECTORY pResDirectory_rd = NULL;			// 第三层资源目录
					PIMAGE_RESOURCE_DIRECTORY_ENTRY pResDirEntry_rd = NULL;		// 第三层资源目录项

					pResDirectory_rd = (PIMAGE_RESOURCE_DIRECTORY)((DWORD)pResDirectory + (pResDirEntry_nd[j].OffsetToData & 0XFFFFFFF));
					pResDirEntry_rd = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)((DWORD)pResDirectory_rd + sizeof(IMAGE_RESOURCE_DIRECTORY));

					// 第三层结构体总数
					TierNum_rd = pResDirectory_rd->NumberOfIdEntries + pResDirectory_rd->NumberOfNamedEntries;

					for (int k = 0; k < TierNum_rd; k++)
					{
						if (!(pResDirEntry_rd[k].Name & 0x80000000))
						{
							sprintf(szTempText, "%s", "代码页: ");
							strcat(szText, szTempText);

							sprintf(szTempText, "%d\r\n", pResDirEntry_rd[k].Name);
							strcat(szText, szTempText);
						}

						if (pResDirEntry_rd[k].DataIsDirectory == 0)
						{
							pResDirData = (PIMAGE_DATA_DIRECTORY)((DWORD)pResDirectory + (pResDirEntry_rd[k].OffsetToData & 0XFFFFFFF));

							sprintf(szTempText, "%s", "RVA: ");
							strcat(szText, szTempText);

							sprintf(szTempText, "%x\r\n", pResDirData->VirtualAddress);
							strcat(szText, szTempText);

							sprintf(szTempText, "%s", "Offset: ");
							strcat(szText, szTempText);

							sprintf(szTempText, "%x\r\n", RvaToFileOffset(pFileBuffer, pResDirData->VirtualAddress));
							strcat(szText, szTempText);

							sprintf(szTempText, "%s", "SIZE: ");
							strcat(szText, szTempText);

							sprintf(szTempText, "%x\r\n\r\n", pResDirData->Size);
							strcat(szText, szTempText);
						}
					}
				}
			}
		}
	}

	SendDlgItemMessage(hwndDlg, IDC_RESOURCE, WM_SETTEXT, 0, (DWORD)szText);
}

VOID InitRelocation(HWND hwndDlg, LPSTR lpszFile)
{
	PIMAGE_DOS_HEADER pDosHeader = NULL;
	PIMAGE_NT_HEADERS pNTHeader = NULL;
	PIMAGE_FILE_HEADER pPEHeader = NULL;
	PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
	PIMAGE_SECTION_HEADER pSectionHeader = NULL;
	PIMAGE_DATA_DIRECTORY DataDirectory = NULL;
	PIMAGE_EXPORT_DIRECTORY ExportTable = NULL;

	PIMAGE_BASE_RELOCATION RelocationTable = NULL;

	DWORD EntryRelocationRVA = 0;
	DWORD EntryRelocationFOA = 0;

	LPVOID pFileBuffer = NULL;
	DWORD fileSize = 0;

	TCHAR szText[0x40960];
	memset(szText, 0, 0x40960);

	TCHAR szTempText[1024];
	memset(szTempText, 0, 1024);

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

	if (!(pOptionHeader->DataDirectory[5].VirtualAddress))
	{
		MessageBox(0, TEXT("此文件没有重定位表!"), TEXT("Window"), 0);
		EndDialog(hwndDlg, 0);

		return;
	}

	// 重定位表
	EntryRelocationRVA = pOptionHeader->DataDirectory[5].VirtualAddress;
	EntryRelocationFOA = RvaToFileOffset(pFileBuffer, EntryRelocationRVA);
	RelocationTable = (PIMAGE_BASE_RELOCATION)((DWORD)EntryRelocationFOA + (DWORD)pFileBuffer);
	
	while (1)
	{
		sprintf(szTempText, "%s\r\n", "********************************************************");
		strcat(szText, szTempText);

		sprintf(szTempText, "%s", "RelocationTable->VirtualAddress = ");
		strcat(szText, szTempText);

		sprintf(szTempText, "%x\r\n\r\n", RelocationTable->VirtualAddress);
		strcat(szText, szTempText);

		WORD* recAddr = (WORD *)((BYTE *)RelocationTable + 8);
		DWORD foa = RelocationTable->VirtualAddress;

		for (DWORD n = 0; n < (RelocationTable->SizeOfBlock - 0x8) / 2; n++)
		{
			DWORD offset = (recAddr[n] & 0xFFF) + foa;
			WORD type = recAddr[n] >> 12;
			if (type == 0)
			{
				sprintf(szTempText, "%s\r\n", "---------------------------- ABSOLUTE");
				strcat(szText, szTempText);
				continue;
			}
			sprintf(szTempText, "%s", "index ");
			strcat(szText, szTempText);

			sprintf(szTempText, "%d", n + 1);
			strcat(szText, szTempText);

			sprintf(szTempText, "%s", " RelocationTableADDR = ");
			strcat(szText, szTempText);

			sprintf(szTempText, "%x\r\n", offset);
			strcat(szText, szTempText);
		}
		sprintf(szTempText, "\r\n");
		strcat(szText, szTempText);

		RelocationTable = (PIMAGE_BASE_RELOCATION)((DWORD)RelocationTable + RelocationTable->SizeOfBlock);
		if (RelocationTable->VirtualAddress == 0 && RelocationTable->SizeOfBlock == 0)
		{
			break;
		}
	}

	SendDlgItemMessage(hwndDlg, IDC_RELOCATION, WM_SETTEXT, 0, (DWORD)szText);
}

VOID InitBoundImport(HWND hwndDlg, LPSTR lpszFile)
{
	PIMAGE_DOS_HEADER pDosHeader = NULL;
	PIMAGE_NT_HEADERS pNTHeader = NULL;
	PIMAGE_FILE_HEADER pPEHeader = NULL;
	PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
	PIMAGE_SECTION_HEADER pSectionHeader = NULL;
	PIMAGE_DATA_DIRECTORY DataDirectory = NULL;
	PIMAGE_EXPORT_DIRECTORY ExportTable = NULL;

	PIMAGE_BOUND_IMPORT_DESCRIPTOR BoundImportTable = NULL;
	PIMAGE_BOUND_FORWARDER_REF BoundForwarderTable = NULL;

	DWORD EntryBoundImportTableFOA = 0;

	LPVOID pFileBuffer = NULL;
	DWORD fileSize = 0;

	TCHAR szText[4096];
	memset(szText, 0, 4096);

	TCHAR szTempText[1024];
	memset(szTempText, 0, 1024);

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

	if (!(pOptionHeader->DataDirectory[11].VirtualAddress))
	{
		MessageBox(0, TEXT("此文件没有绑定导入表!"), TEXT("Window"), 0);
		EndDialog(hwndDlg, 0);

		return;
	}

	// 绑定导入表
	EntryBoundImportTableFOA = RvaToFileOffset(pFileBuffer, pOptionHeader->DataDirectory[11].VirtualAddress);
	BoundImportTable = (PIMAGE_BOUND_IMPORT_DESCRIPTOR)(EntryBoundImportTableFOA + (DWORD)pFileBuffer);

	DWORD BoundImportTableAddr = (DWORD)BoundImportTable;

	while (*(PDWORD)BoundImportTable)
	{
		sprintf(szTempText, "%s%s\r\n", "Dll Name = ", BoundImportTableAddr + BoundImportTable->OffsetModuleName);
		strcat(szText, szTempText);

		sprintf(szTempText, "%s%x\r\n", "BoundImportTable->TimeDateStamp = ", BoundImportTable->TimeDateStamp);
		strcat(szText, szTempText);

		sprintf(szTempText, "%s%x\r\n", "BoundImportTable->OffsetModuleName = ", BoundImportTable->OffsetModuleName);
		strcat(szText, szTempText);

		sprintf(szTempText, "%s%x\r\n", "BoundImportTable->NumberOfModuleForwarderRefs = ", BoundImportTable->NumberOfModuleForwarderRefs);
		strcat(szText, szTempText);

		sprintf(szTempText, "\r\n");
		strcat(szText, szTempText);

		if (BoundImportTable->NumberOfModuleForwarderRefs)
		{
			WORD temp = BoundImportTable->NumberOfModuleForwarderRefs;
			BoundImportTable++;

			while (temp > 0)
			{
				sprintf(szTempText, "%s\r\n", "--------------------REF--------------------");
				strcat(szText, szTempText);

				sprintf(szTempText, "Dll Name = %s\r\n", BoundImportTableAddr + BoundImportTable->OffsetModuleName);
				strcat(szText, szTempText);

				sprintf(szTempText, "REF->TimeDateStamp = %x\r\n", BoundImportTable->TimeDateStamp);
				strcat(szText, szTempText);

				sprintf(szTempText, "REF->OffsetModuleName = %x\r\n", BoundImportTable->OffsetModuleName);
				strcat(szText, szTempText);

				sprintf(szTempText, "REF->NumberOfModuleForwarderRefs = %x\r\n", BoundImportTable->NumberOfModuleForwarderRefs);
				strcat(szText, szTempText);

				sprintf(szTempText, "\r\n");
				strcat(szText, szTempText);

				temp--;
				BoundImportTable++;
			}
		}
		else
		{
			BoundImportTable++;
		}
	}

	SendDlgItemMessage(hwndDlg, IDC_BOUNDIMPORT, WM_SETTEXT, 0, (DWORD)szText);
}

VOID InitIAT(HWND hwndDlg, LPSTR lpszFile)
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

	DWORD OFThunkFOA = 0; // OriginalFirstThunk
	PDWORD OriginalFirstThunk = NULL;

	DWORD FThunkFOA = 0; // FirstThunk
	PDWORD FirstThunk = NULL;

	DWORD IBNameFOA = 0; // IMPORT_BY_NAME
	PBYTE pStr = NULL;

	TCHAR szText[0x8192];
	memset(szText, 0, 0x8192);

	TCHAR szTempText[1024];
	memset(szTempText, 0, 1024);

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
		MessageBox(0, TEXT("此文件没有IAT表!"), TEXT("Window"), 0);
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
			break;
		}

		DLLNameFOA = RvaToFileOffset(pFileBuffer, ImportTable->Name);
		DLLNameAddr = (PDWORD)((DWORD)pFileBuffer + DLLNameFOA);

		sprintf(szTempText, "%s", "---------------------OriginalFirstThunk: ");
		strcat(szText, szTempText);

		sprintf(szTempText, "%x", ImportTable->OriginalFirstThunk);
		strcat(szText, szTempText);

		sprintf(szTempText, "%s\r\n", "---------------------");
		strcat(szText, szTempText);

		OFThunkFOA = RvaToFileOffset(pFileBuffer, ImportTable->OriginalFirstThunk);
		OriginalFirstThunk = (PDWORD)((DWORD)pFileBuffer + OFThunkFOA);

		sprintf(szTempText, "%x --- %x\r\n", OriginalFirstThunk, *OriginalFirstThunk);
		strcat(szText, szTempText);

		while (1)
		{
			if (*OriginalFirstThunk == 0)
			{
				break;
			}

			if (*OriginalFirstThunk & IMAGE_ORDINAL_FLAG32) // IMAGE_ORDINAL_FLAG32 0x80000000
			{
				sprintf(szTempText, "%s", "序号导入:");
				strcat(szText, szTempText);

				sprintf(szTempText, "%xh %dd\r\n", *OriginalFirstThunk & 0x7FFFFFFF, *OriginalFirstThunk & 0x7FFFFFFF);
				strcat(szText, szTempText);
			}
			else // 用名字导入
			{
				IBNameFOA = RvaToFileOffset(pFileBuffer, *OriginalFirstThunk);
				ImportByNameTable = (PIMAGE_IMPORT_BY_NAME)((DWORD)IBNameFOA + (DWORD)pFileBuffer);

				pStr = (PBYTE)ImportByNameTable->Name;

				sprintf(szTempText, "%s", "按名字导入HIT/NAME:");
				strcat(szText, szTempText);

				sprintf(szTempText, "%x-%s\r\n", ImportByNameTable->Hint, pStr);
				strcat(szText, szTempText);

				pStr = NULL;
			}
			*(OriginalFirstThunk++);
		}

		sprintf(szTempText, "\r\n");
		strcat(szText, szTempText);

		sprintf(szTempText, "%s", "---------------------FirstThunk: ");
		strcat(szText, szTempText);

		sprintf(szTempText, "%x", ImportTable->FirstThunk);
		strcat(szText, szTempText);

		sprintf(szTempText, "%s\r\n", "---------------------");
		strcat(szText, szTempText);

		FThunkFOA = RvaToFileOffset(pFileBuffer, ImportTable->FirstThunk);
		FirstThunk = (PDWORD)((DWORD)pFileBuffer + FThunkFOA);

		sprintf(szTempText, "%x --- %x\r\n", FirstThunk, *FirstThunk);
		strcat(szText, szTempText);

		while (1)
		{
			if (*FirstThunk == 0)
			{
				break;
			}

			if (*FirstThunk & IMAGE_ORDINAL_FLAG32) // IMAGE_ORDINAL_FLAG32 0x80000000
			{
				sprintf(szTempText, "%s", "序号导入:");
				strcat(szText, szTempText);

				sprintf(szTempText, "%xh %dd\r\n", *FirstThunk & 0x7FFFFFFF, *FirstThunk & 0x7FFFFFFF);
				strcat(szText, szTempText);
			}
			else // 用名字导入
			{
				IBNameFOA = RvaToFileOffset(pFileBuffer, *FirstThunk);
				ImportByNameTable = (PIMAGE_IMPORT_BY_NAME)((DWORD)IBNameFOA + (DWORD)pFileBuffer);

				pStr = (PBYTE)ImportByNameTable->Name;

				sprintf(szTempText, "%s", "按名字导入HIT/NAME:");
				strcat(szText, szTempText);

				sprintf(szTempText, "%x-%s\r\n", ImportByNameTable->Hint, pStr);
				strcat(szText, szTempText);

				pStr = NULL;
			}
			*(FirstThunk++);
		}

		sprintf(szTempText, "\r\n");
		strcat(szText, szTempText);
		ImportTable++;
	}

	SendDlgItemMessage(hwndDlg, IDC_IAT, WM_SETTEXT, 0, (DWORD)szText);
}