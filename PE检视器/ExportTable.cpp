// ExportTable.cpp: implementation of the ExportTable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ExportTable.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


VOID InitExport(HWND hDlg, LPSTR lpszFile)
{
	LV_COLUMN lv;								
	HWND hListProcess;
									
	//��ʼ��								
	memset(&lv,0,sizeof(LV_COLUMN));								
	//��ȡIDC_LIST_PROCESS���								
	hListProcess = GetDlgItem(hDlg, IDC_LIST_EXPORTTABLE);								
	//��������ѡ��								
	SendMessage(hListProcess,LVM_SETEXTENDEDLISTVIEWSTYLE,LVS_EX_FULLROWSELECT,LVS_EX_FULLROWSELECT);								
									
	//��һ��								
	lv.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;								
	lv.pszText = TEXT("Ordinal");			//�б���				
	lv.cx = 75;								//�п�
	lv.iSubItem = 0;								
	//ListView_InsertColumn(hListProcess, 0, &lv);								
	SendMessage(hListProcess,LVM_INSERTCOLUMN,0,(DWORD)&lv);	
	
	//�ڶ���								
	lv.pszText = TEXT("RVA");								
	lv.cx = 150;								
	lv.iSubItem = 1;								
	//ListView_InsertColumn(hListProcess, 1, &lv);								
	SendMessage(hListProcess,LVM_INSERTCOLUMN,1,(DWORD)&lv);
	
	//������								
	lv.pszText = TEXT("Offset");								
	lv.cx = 125;								
	lv.iSubItem = 2;								
	ListView_InsertColumn(hListProcess, 2, &lv);
	
	//������								
	lv.pszText = TEXT("Function Name");								
	lv.cx = 125;								
	lv.iSubItem = 3;								
	ListView_InsertColumn(hListProcess, 3, &lv);


	EnumExport(hDlg, hListProcess, lpszFile);
}


VOID EnumExport(HWND hDlg, HWND hListProcess, LPSTR lpszFile)
{
	PIMAGE_DOS_HEADER pDosHeader = NULL;	
	PIMAGE_NT_HEADERS pNTHeader = NULL;	
	PIMAGE_FILE_HEADER pPEHeader = NULL;
	PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
	PIMAGE_SECTION_HEADER pSectionHeader = NULL;
	PIMAGE_DATA_DIRECTORY DataDirectory = NULL;
	PIMAGE_EXPORT_DIRECTORY ExportTable = NULL;

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

	LPVOID pFileBuffer = NULL;

	LV_ITEM vitem;
	//��ʼ��								
	memset(&vitem,0,sizeof(LV_ITEM));						
	vitem.mask = LVIF_TEXT;

	TCHAR szBuffer[256];
	memset(szBuffer, 0x0, 256);

	ReadPEFile(lpszFile, &pFileBuffer);

	//�ж��Ƿ�����Ч��MZ��־	
	if(*((PWORD)pFileBuffer) != IMAGE_DOS_SIGNATURE)	
	{
		return ; 
	}	
	pDosHeader = (PIMAGE_DOS_HEADER)pFileBuffer;
	//�ж��Ƿ�����Ч��PE��־	
	if(*((PDWORD)((DWORD)pFileBuffer+pDosHeader->e_lfanew)) != IMAGE_NT_SIGNATURE)	
	{	
		return ;
	}

	pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pFileBuffer+pDosHeader->e_lfanew);
	// PEͷ�ļ�
	pPEHeader = (PIMAGE_FILE_HEADER)(((DWORD)pNTHeader) + 4);	
	// ��ѡPEͷ	
	pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader+IMAGE_SIZEOF_FILE_HEADER);
	// DataDirectory
	DataDirectory = pOptionHeader->DataDirectory;

	ExportTableRVA = pOptionHeader->DataDirectory[0].VirtualAddress;
	ExportTableFOA = RvaToFileOffset(pFileBuffer, ExportTableRVA);

	// ������
	ExportTable = (PIMAGE_EXPORT_DIRECTORY)((DWORD)ExportTableFOA + (DWORD)pFileBuffer);


	sprintf(szBuffer, "%x", ExportTableFOA);
	SendDlgItemMessage(hDlg, IDC_EXPORTTABLE_EDIT1, WM_SETTEXT, 0, (DWORD)szBuffer);

	sprintf(szBuffer, "%x", ExportTable->Characteristics);
	SendDlgItemMessage(hDlg, IDC_EXPORTTABLE_EDIT2, WM_SETTEXT, 0, (DWORD)szBuffer);

	sprintf(szBuffer, "%x", ExportTable->Base);
	SendDlgItemMessage(hDlg, IDC_EXPORTTABLE_EDIT3, WM_SETTEXT, 0, (DWORD)szBuffer);

	sprintf(szBuffer, "%x", ExportTable->Name);
	SendDlgItemMessage(hDlg, IDC_EXPORTTABLE_EDIT4, WM_SETTEXT, 0, (DWORD)szBuffer);

	DWORD FileNameAddr = RvaToFileOffset(pFileBuffer, ExportTable->Name);
	sprintf(szBuffer, "%s", (DWORD)pFileBuffer + FileNameAddr);
	SendDlgItemMessage(hDlg, IDC_EXPORTTABLE_EDIT5, WM_SETTEXT, 0, (DWORD)szBuffer);

	sprintf(szBuffer, "%x", ExportTable->NumberOfFunctions);
	SendDlgItemMessage(hDlg, IDC_EXPORTTABLE_EDIT6, WM_SETTEXT, 0, (DWORD)szBuffer);

	sprintf(szBuffer, "%x", ExportTable->NumberOfNames);
	SendDlgItemMessage(hDlg, IDC_EXPORTTABLE_EDIT7, WM_SETTEXT, 0, (DWORD)szBuffer);

	sprintf(szBuffer, "%x", ExportTable->AddressOfFunctions);
	SendDlgItemMessage(hDlg, IDC_EXPORTTABLE_EDIT8, WM_SETTEXT, 0, (DWORD)szBuffer);

	sprintf(szBuffer, "%x", ExportTable->AddressOfNames);
	SendDlgItemMessage(hDlg, IDC_EXPORTTABLE_EDIT9, WM_SETTEXT, 0, (DWORD)szBuffer);

	sprintf(szBuffer, "%x", ExportTable->AddressOfNameOrdinals);
	SendDlgItemMessage(hDlg, IDC_EXPORTTABLE_EDIT10, WM_SETTEXT, 0, (DWORD)szBuffer);

	memset(szBuffer, 0x0, 256);

	WORD* OrdinalsArr = NULL;
	WORD* OrdinalsArr2 = NULL;

	OrdinalsArr = (PWORD)malloc(ExportTable->NumberOfNames * sizeof(WORD));
	memset(OrdinalsArr, 0x0, ExportTable->NumberOfNames);

	PWORD pO = NULL;
	pO = OrdinalsArr;

	for (int i=0; i<ExportTable->NumberOfNames; i++)
	{
		// �ҵ�AddressOfNameOrdinals�ĵ�ַ
		AddressOfNameOrdinalsFOA = RvaToFileOffset(pFileBuffer, ExportTable->AddressOfNameOrdinals + i*sizeof(WORD));
		Ordinals = (PWORD)((DWORD)pFileBuffer + AddressOfNameOrdinalsFOA);
		
		*pO = *Ordinals;
		pO++;
	}

	OrdinalsArr2 = (PWORD)malloc(ExportTable->NumberOfNames * sizeof(WORD));
	memcpy(OrdinalsArr2, OrdinalsArr, ExportTable->NumberOfNames * sizeof(WORD));
	
	BubSort(OrdinalsArr, ExportTable->NumberOfNames);
	pO = OrdinalsArr;

	for (int j=0; j<ExportTable->NumberOfNames; j++)
	{
		sprintf(szBuffer, "%x", *pO + ExportTable->Base);
		vitem.pszText = szBuffer;
		vitem.iItem = j;
		vitem.iSubItem = 0;
		SendMessage(hListProcess, LVM_INSERTITEM, i, (DWORD)&vitem);
		memset(szBuffer, 0x0, 256);

		// �ҵ�AddressOfFunctions�ĵ�ַ
		AddressOfFunctionsFOA = RvaToFileOffset(pFileBuffer, ExportTable->AddressOfFunctions + *pO * sizeof(DWORD));
		FunctionsAddr = (PDWORD)((DWORD)pFileBuffer + AddressOfFunctionsFOA);
		Functions = (PDWORD)RvaToFileOffset(pFileBuffer, *FunctionsAddr);

		sprintf(szBuffer, "%x", *FunctionsAddr);
		vitem.pszText = szBuffer;
		vitem.iItem = j;
		vitem.iSubItem = 1;
		ListView_SetItem(hListProcess, &vitem);
		memset(szBuffer, 0x0, 256);

		sprintf(szBuffer, "%x", Functions);
		vitem.pszText = szBuffer;
		vitem.iItem = j;
		vitem.iSubItem = 2;
		ListView_SetItem(hListProcess, &vitem);
		memset(szBuffer, 0x0, 256);

		// �ҵ�AddressOfNames�ĵ�ַ
		AddressOfNamesFOA = RvaToFileOffset(pFileBuffer, ExportTable->AddressOfNames);

		int Base = OrdinalsArr2[j] - ExportTable->Base;
		if (Base < 0) Base = OrdinalsArr2[j];

		FunNameAddr = (PDWORD)((DWORD)pFileBuffer + AddressOfNamesFOA + Base * sizeof(DWORD));
		FunName = (PDWORD)((DWORD)pFileBuffer + RvaToFileOffset(pFileBuffer, *FunNameAddr));

		sprintf(szBuffer, "%s", FunName);

		vitem.pszText = szBuffer;
		vitem.iItem = j;
		vitem.iSubItem = 3;
		ListView_SetItem(hListProcess, &vitem);
		memset(szBuffer, 0x0, 256);

		pO++;
	}

	pO = NULL;
	free(OrdinalsArr);
}


VOID BubSort(WORD* arr, DWORD len)
{
	int flag = 1;

	while (len-- && flag)
	{
		flag = 0;

		for (int i=0; i<len; i++)
		{
			if (arr[i] > arr[i+1])
			{
				WORD temp = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = temp;
				flag = 1;
			}
		}
	}
}




/*

	ExportTableFOA = RvaToFileOffset(pFileBuffer, ExportTable->AddressOfNameOrdinals);

	for (int i=0; i<ExportTable->NumberOfNames; i++)
	{
		// �ҵ�AddressOfNameOrdinals�ĵ�ַ
		AddressOfNameOrdinalsFOA = RvaToFileOffset(pFileBuffer, ExportTable->AddressOfNameOrdinals + i*sizeof(WORD));
		Ordinals = (PWORD)((DWORD)pFileBuffer + AddressOfNameOrdinalsFOA);
		sprintf(szBuffer, "%x", *Ordinals);

		vitem.pszText = szBuffer;
		vitem.iItem = i;
		vitem.iSubItem = 0;
		SendMessage(hListProcess, LVM_INSERTITEM, i, (DWORD)&vitem);
		memset(szBuffer, 0x0, 256);
	}

	ExportTableFOA = RvaToFileOffset(pFileBuffer, ExportTable->AddressOfFunctions);

	for (int j=0; j<ExportTable->NumberOfFunctions; j++)
	{
		// �ҵ�AddressOfFunctions�ĵ�ַ
		AddressOfFunctionsFOA = RvaToFileOffset(pFileBuffer, ExportTable->AddressOfFunctions + j*sizeof(DWORD));

		FunctionsAddr = (PDWORD)((DWORD)pFileBuffer + AddressOfFunctionsFOA);
		Functions = (PDWORD)((DWORD)pFileBuffer + *FunctionsAddr);

		sprintf(szBuffer, "%x", (DWORD)pFileBuffer + ExportTable->AddressOfFunctions + j*sizeof(DWORD));

		vitem.pszText = szBuffer;
		vitem.iItem = j;
		vitem.iSubItem = 1;
		ListView_SetItem(hListProcess, &vitem);
		memset(szBuffer, 0x0, 256);

		sprintf(szBuffer, "%x", *FunctionsAddr);

		vitem.pszText = szBuffer;
		vitem.iItem = j;
		vitem.iSubItem = 2;
		ListView_SetItem(hListProcess, &vitem);
		memset(szBuffer, 0x0, 256);
	}

	ExportTableFOA = RvaToFileOffset(pFileBuffer, ExportTable->AddressOfNames);

	for (int k=0; k<ExportTable->NumberOfNames; k++)
	{
		// �ҵ�AddressOfNames�ĵ�ַ
		AddressOfNamesFOA = RvaToFileOffset(pFileBuffer, ExportTable->AddressOfNames + k*sizeof(DWORD));

		FunNameAddr = (PDWORD)((DWORD)pFileBuffer + AddressOfNamesFOA);
		FunName = (PDWORD)((DWORD)pFileBuffer + *FunNameAddr);

		sprintf(szBuffer, "%s", FunName);

		vitem.pszText = szBuffer;
		vitem.iItem = k;
		vitem.iSubItem = 3;
		ListView_SetItem(hListProcess, &vitem);
		memset(szBuffer, 0x0, 256);
	}


*/









VOID PrintExportTable(LPVOID pFileBuffer)
{
	PIMAGE_DOS_HEADER pDosHeader = NULL;	
	PIMAGE_NT_HEADERS pNTHeader = NULL;	
	PIMAGE_FILE_HEADER pPEHeader = NULL;
	PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
	PIMAGE_SECTION_HEADER pSectionHeader = NULL;
	PIMAGE_DATA_DIRECTORY DataDirectory = NULL;
	PIMAGE_EXPORT_DIRECTORY ExportTable = NULL;

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

	//�ж��Ƿ�����Ч��MZ��־	
	if(*((PWORD)pFileBuffer) != IMAGE_DOS_SIGNATURE)	
	{	
		printf("������Ч��MZ��־\n");
		return ; 
	}	
	pDosHeader = (PIMAGE_DOS_HEADER)pFileBuffer;
	//�ж��Ƿ�����Ч��PE��־	
	if(*((PDWORD)((DWORD)pFileBuffer+pDosHeader->e_lfanew)) != IMAGE_NT_SIGNATURE)	
	{	
		printf("������Ч��PE��־\n");
		return ;
	}	
	pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pFileBuffer+pDosHeader->e_lfanew);
	// PEͷ�ļ�
	pPEHeader = (PIMAGE_FILE_HEADER)(((DWORD)pNTHeader) + 4);	
	// ��ѡPEͷ	
	pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader+IMAGE_SIZEOF_FILE_HEADER);
	// DataDirectory
	DataDirectory = pOptionHeader->DataDirectory;

	ExportTableRVA = pOptionHeader->DataDirectory[0].VirtualAddress;
	ExportTableFOA = RvaToFileOffset(pFileBuffer, ExportTableRVA);

	// ������
	ExportTable = (PIMAGE_EXPORT_DIRECTORY)((DWORD)ExportTableFOA + (DWORD)pFileBuffer);

	printf("Characteristics = %x\n", ExportTable->Characteristics);
	printf("TimeDateStamp = %x\n", ExportTable->TimeDateStamp);
	printf("MajorVersion = %x\n", ExportTable->MajorVersion);
	printf("MinorVersion = %x\n", ExportTable->MinorVersion);
	printf("Name = %x\n", ExportTable->Name);
	printf("Base = %x\n", ExportTable->Base);
	printf("NumberOfFunctions = %x\n", ExportTable->NumberOfFunctions);
	printf("NumberOfNames = %x\n", ExportTable->NumberOfNames);

	printf("***=========AddressOfFunctions=========***\n");
	ExportTableFOA = RvaToFileOffset(pFileBuffer, ExportTable->AddressOfFunctions);
	printf("AddressOfFunctions = %x\n", ExportTableFOA);
	for (int i=0; i<ExportTable->NumberOfFunctions; i++)
	{
		// �ҵ�AddressOfFunctions�ĵ�ַ
		AddressOfFunctionsFOA = RvaToFileOffset(pFileBuffer, ExportTable->AddressOfFunctions + i*sizeof(DWORD));
		// printf("ExportTable->AddressOfFunctions AddressOfFunctionsFOA = %x\n", AddressOfFunctionsFOA);
		FunctionsAddr = (PDWORD)((DWORD)pFileBuffer + AddressOfFunctionsFOA);
		printf("ExportTable->AddressOfFunctions FunctionsAddr = %x\n", *FunctionsAddr); // ������ַ
		Functions = (PDWORD)((DWORD)pFileBuffer + *FunctionsAddr);
		// printf("ExportTable->AddressOfFunctions Functions = %x\n", *Functions); // ����ֵ
	}

	printf("***=========AddressOfNames=========***\n");
	ExportTableFOA = RvaToFileOffset(pFileBuffer, ExportTable->AddressOfNames);
	printf("AddressOfNames = %x\n", ExportTableFOA);
	for (int j=0; j<ExportTable->NumberOfNames; j++)
	{
		// �ҵ�AddressOfNames�ĵ�ַ
		AddressOfNamesFOA = RvaToFileOffset(pFileBuffer, ExportTable->AddressOfNames + j*sizeof(DWORD));
		// printf("ExportTable->AddressOfNames AddressOfNamesFOA = %x\n", AddressOfNamesFOA);
		FunNameAddr = (PDWORD)((DWORD)pFileBuffer + AddressOfNamesFOA);
		// printf("ExportTable->AddressOfNames FunNameAddr = %x\n", *FunNameAddr);
		FunName = (PDWORD)((DWORD)pFileBuffer + *FunNameAddr);
		// printf("ExportTable->AddressOfNames FunName = %x\n", *FunName);
		printf("ExportTable->AddressOfNames FunName = %s\n", FunName);
	}

	printf("***=========AddressOfNameOrdinals=========***\n");
	ExportTableFOA = RvaToFileOffset(pFileBuffer, ExportTable->AddressOfNameOrdinals);
	printf("AddressOfNameOrdinals = %x\n", ExportTableFOA);
	for (int k=0; k<ExportTable->NumberOfNames; k++)
	{
		// �ҵ�AddressOfNameOrdinals�ĵ�ַ
		AddressOfNameOrdinalsFOA = RvaToFileOffset(pFileBuffer, ExportTable->AddressOfNameOrdinals + k*sizeof(WORD));
		// printf("ExportTable->AddressOfNameOrdinals AddressOfNameOrdinalsFOA = %x\n", AddressOfNameOrdinalsFOA);
		Ordinals = (PWORD)((DWORD)pFileBuffer + AddressOfNameOrdinalsFOA);
		printf("ExportTable->AddressOfNameOrdinals Ordinals = %x\n", *Ordinals);
	}
}