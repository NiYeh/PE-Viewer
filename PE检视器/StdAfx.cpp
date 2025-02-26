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
		
	//打开文件	
    pFile = fopen(lpszFile, "rb");		
	if(!pFile)	
	{	
		MessageBox(0, TEXT("无法打开 EXE 文件!"), TEXT("Window"), 0);
		return 0;
	}	
    //读取文件大小		
	fseek(pFile, 0, SEEK_END);	
	fileSize = ftell(pFile);		
	fseek(pFile, 0, SEEK_SET);		
	//分配缓冲区	
	*pFileBuffer = malloc(fileSize);	
		
	if(!(*pFileBuffer))	
	{	
		MessageBox(0, TEXT("分配空间失败!"), TEXT("Window"), 0);
		fclose(pFile);
		return 0;
	}	
	//将文件数据读取到缓冲区	
	size_t n = fread(*pFileBuffer, fileSize, 1, pFile);	
	if(!n)	
	{	
		MessageBox(0, TEXT("读取数据失败!"), TEXT("Window"), 0);
		free(*pFileBuffer);
		fclose(pFile);
		return 0;
	}	
	//关闭文件	
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
		MessageBox(0, TEXT("保存文件失败!"), TEXT("Window"), 0);
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

	//判断是否是有效的MZ标志	
	if(*((PWORD)pFileBuffer) != IMAGE_DOS_SIGNATURE)	
	{	
		MessageBox(0, TEXT("不是有效的MZ标志!"), TEXT("Window"), 0);
		return dwFOA; 
	}	
	pDosHeader = (PIMAGE_DOS_HEADER)pFileBuffer;
	//判断是否是有效的PE标志	
	if(*((PDWORD)((DWORD)pFileBuffer+pDosHeader->e_lfanew)) != IMAGE_NT_SIGNATURE)	
	{	
		MessageBox(0, TEXT("不是有效的MZ标志!"), TEXT("Window"), 0);
		return dwFOA;
	}	
	pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pFileBuffer+pDosHeader->e_lfanew);
	// PE头文件
	pPEHeader = (PIMAGE_FILE_HEADER)(((DWORD)pNTHeader) + 4);	
	//可选PE头	
	pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader+IMAGE_SIZEOF_FILE_HEADER);
	// 节表
	pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pPEHeader+IMAGE_SIZEOF_FILE_HEADER+pPEHeader->SizeOfOptionalHeader);

	dwFOA = dwRva;

	// 1. 判断这个值落到哪个节表裡了
	for (WORD i=1; i<=pPEHeader->NumberOfSections; i++, pSectionHeader++)
	{
		if (dwFOA >= pSectionHeader->VirtualAddress && dwFOA < (pSectionHeader->VirtualAddress + pSectionHeader->Misc.VirtualSize))
		{
			// 2. 把值减去节表的VirtualAddress 
			dwFOA = dwFOA - pSectionHeader->VirtualAddress;
			
			// 3. 查节表 找PointerToRawData(在文件中的偏移) 然后 + 减去VirtualAddress的值 = FOA
			dwFOA = dwFOA + pSectionHeader->PointerToRawData;
			
			//4. 返回FOA
			return dwFOA;
		}
	}

	// 5. 判断RVA是否小于头文件
	if (dwFOA > 0 && dwFOA <= pOptionHeader->SizeOfHeaders)
	{
		return dwFOA;
	}

	return 0;
}