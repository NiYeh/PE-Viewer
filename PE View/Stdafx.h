#define _CRT_SECURE_NO_WARNINGS 1
#pragma once

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

// �{�Î�
#include <windows.h>
#include <commdlg.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <Psapi.h>

#include "resource.h"

//**************************************************************************								
//ReadPEFile:���ļ���ȡ��������								
//����˵����								
//lpszFile �ļ�·��								
//pFileBuffer ������ָ��								
//����ֵ˵����								
//��ȡʧ�ܷ���0  ���򷵻�ʵ�ʶ�ȡ�Ĵ�С								
//**************************************************************************								
DWORD ReadPEFile(IN LPSTR lpszFile, OUT LPVOID* pFileBuffer);

//**************************************************************************								
//MemeryTOFile:���ڴ��е����ݸ��Ƶ��ļ�								
//����˵����								
//pMemBuffer �ڴ������ݵ�ָ��								
//size Ҫ���ƵĴ�С								
//lpszFile Ҫ�洢���ļ�·��								
//����ֵ˵����								
//��ȡʧ�ܷ���0  ���򷵻ظ��ƵĴ�С								
//**************************************************************************								
BOOL MemeryTOFile(IN LPVOID pMemBuffer, IN size_t size, OUT LPSTR lpszFile);

//**************************************************************************								
//RvaToFileOffset:���ڴ�ƫ��ת��Ϊ�ļ�ƫ��
//RVA������ƫ�Ƶ�ַ FOA��F=�ļ�OA=ƫ�Ƶ�ַ
//����˵����								
//pFileBuffer �ļ�ָ��								
//dwRva RVA��ֵ								
//����ֵ˵����								
//����ת�����FOA��ֵ  ���ʧ�ܷ���0								
//**************************************************************************								
DWORD RvaToFileOffset(IN LPVOID pFileBuffer, IN DWORD dwRva);
