// stdafx.cpp : source file that includes just the standard includes
//	PEviewer.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

DWORD g_fileSize = 0;

DWORD ReadPEFile(IN LPSTR lpszFile, OUT LPVOID* pFileBuffer)
{
	FILE *pFile = NULL;	
	DWORD fileSize = 0;	
		
	//���ļ�	
    pFile = fopen(lpszFile, "rb");		
	if(!pFile)	
	{	
		MessageBox(0, TEXT("�޷��� EXE �ļ�!"), TEXT("Window"), 0);
		return 0;
	}	
    //��ȡ�ļ���С		
	fseek(pFile, 0, SEEK_END);	
	fileSize = ftell(pFile);		
	fseek(pFile, 0, SEEK_SET);		
	//���仺����	
	*pFileBuffer = malloc(fileSize);	
		
	if(!(*pFileBuffer))	
	{	
		MessageBox(0, TEXT("����ռ�ʧ��!"), TEXT("Window"), 0);
		fclose(pFile);
		return 0;
	}	
	//���ļ����ݶ�ȡ��������	
	size_t n = fread(*pFileBuffer, fileSize, 1, pFile);	
	if(!n)	
	{	
		MessageBox(0, TEXT("��ȡ����ʧ��!"), TEXT("Window"), 0);
		free(*pFileBuffer);
		fclose(pFile);
		return 0;
	}	
	//�ر��ļ�	
	fclose(pFile);
	g_fileSize = fileSize;
	return fileSize;	
}

BOOL MemeryTOFile(IN LPVOID pMemBuffer, IN size_t size, OUT LPSTR lpszFile)
{
	FILE *fp;
	fp = fopen(lpszFile, "wb");

	if (!size)
	{
		MessageBox(0, TEXT("�����ļ�ʧ��!"), TEXT("Window"), 0);
		return 0;
	}

	fwrite(pMemBuffer, size, 1, fp);
	fclose(fp);

	return size;
}

DWORD RvaToFileOffset(IN LPVOID pFileBuffer,IN DWORD dwRva)
{
	PIMAGE_DOS_HEADER pDosHeader = NULL;	
	PIMAGE_NT_HEADERS pNTHeader = NULL;	
	PIMAGE_FILE_HEADER pPEHeader = NULL;
	PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
	PIMAGE_SECTION_HEADER pSectionHeader = NULL;

	DWORD dwFOA = 0;

	//�ж��Ƿ�����Ч��MZ��־	
	if(*((PWORD)pFileBuffer) != IMAGE_DOS_SIGNATURE)	
	{	
		MessageBox(0, TEXT("������Ч��MZ��־!"), TEXT("Window"), 0);
		return dwFOA; 
	}	
	pDosHeader = (PIMAGE_DOS_HEADER)pFileBuffer;
	//�ж��Ƿ�����Ч��PE��־	
	if(*((PDWORD)((DWORD)pFileBuffer+pDosHeader->e_lfanew)) != IMAGE_NT_SIGNATURE)	
	{	
		MessageBox(0, TEXT("������Ч��MZ��־!"), TEXT("Window"), 0);
		return dwFOA;
	}	
	pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pFileBuffer+pDosHeader->e_lfanew);
	// PEͷ�ļ�
	pPEHeader = (PIMAGE_FILE_HEADER)(((DWORD)pNTHeader) + 4);	
	//��ѡPEͷ	
	pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader+IMAGE_SIZEOF_FILE_HEADER);
	// �ڱ�
	pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pPEHeader+IMAGE_SIZEOF_FILE_HEADER+pPEHeader->SizeOfOptionalHeader);

	dwFOA = dwRva;

	// 1. �ж����ֵ�䵽�ĸ��ڱ��e��
	for (WORD i=1; i<=pPEHeader->NumberOfSections; i++, pSectionHeader++)
	{
		if (dwFOA >= pSectionHeader->VirtualAddress && dwFOA < (pSectionHeader->VirtualAddress + pSectionHeader->Misc.VirtualSize))
		{
			// 2. ��ֵ��ȥ�ڱ��VirtualAddress 
			dwFOA = dwFOA - pSectionHeader->VirtualAddress;
			
			// 3. ��ڱ� ��PointerToRawData(���ļ��е�ƫ��) Ȼ�� + ��ȥVirtualAddress��ֵ = FOA
			dwFOA = dwFOA + pSectionHeader->PointerToRawData;
			
			//4. ����FOA
			return dwFOA;
		}
	}

	// 5. �ж�RVA�Ƿ�С��ͷ�ļ�
	if (dwFOA > 0 && dwFOA <= pOptionHeader->SizeOfHeaders)
	{
		return dwFOA;
	}

	return 0;
}