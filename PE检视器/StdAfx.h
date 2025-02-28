// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

// �{�Î�
#include <windows.h>
#include <commdlg.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>

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
BOOL MemeryTOFile(IN LPVOID pMemBuffer,IN size_t size,OUT LPSTR lpszFile);

//**************************************************************************								
//RvaToFileOffset:���ڴ�ƫ��ת��Ϊ�ļ�ƫ��
//RVA������ƫ�Ƶ�ַ FOA��F=�ļ�OA=ƫ�Ƶ�ַ
//����˵����								
//pFileBuffer �ļ�ָ��								
//dwRva RVA��ֵ								
//����ֵ˵����								
//����ת�����FOA��ֵ  ���ʧ�ܷ���0								
//**************************************************************************								
DWORD RvaToFileOffset(IN LPVOID pFileBuffer,IN DWORD dwRva);

// TODO: reference additional headers your program requires here

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
